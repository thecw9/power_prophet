import pickle
from datetime import datetime

import numpy as np
from src import logger
from src.logger import Logger
from fastapi import APIRouter, Depends, HTTPException
from pydantic import BaseModel
from sqlalchemy import select
from sqlalchemy.orm import Session

from src.config import Config
from src.dependencies import get_db
from src.background.tasks.model_tasks import train_fusion_model
from src.utils import get_realtime_data
from src.orm_model import Devices, Measures

router = APIRouter()
config = Config()
logger = Logger(__name__)


# train model
class TrainModelParams(BaseModel):
    keys: list[int] = [5000000000000000, 5000000000000001, 5000000000000002]
    start_time: datetime = datetime(2021, 1, 1)
    end_time: datetime = datetime.now()


@router.post("/train")
async def train_fusion_model_background(
    params: TrainModelParams,
):
    """Train model"""
    keys = params.keys
    start_time = params.start_time
    end_time = params.end_time

    for key in keys:
        train_fusion_model.delay(key, start_time, end_time)

    return {"code": 200, "message": "Model training started", "data": None}


class PredictParams(BaseModel):
    keys: list[int] = [5000000000000000, 5000000000000001, 5000000000000002]


@router.post("/predict")
async def predict_fusion_model(
    params: PredictParams,
    db: Session = Depends(get_db),
):
    """
    Predict
    """
    # TODO: need to optimize
    return_data = []
    for key in params.keys:
        # get device by key
        device = db.execute(
            select(Devices).where(Devices.key == key)
        ).scalar_one_or_none()
        if not device:
            continue

        # get data
        if not device.measure_keys:
            return_data.append(
                {
                    "key": key,
                    "time": datetime.now(),
                    "status": config.ALARM_STATUS["UNKNOWN"],
                    "type": 1,
                }
            )
            continue
        data = get_realtime_data(device.measure_keys, db)
        data = [data[key] for key in device.measure_keys]
        data = np.array(data)

        # load model
        if not device.model:
            return_data.append(
                {
                    "key": key,
                    "time": datetime.now(),
                    "status": config.ALARM_STATUS["UNKNOWN"],
                    "type": 1,
                }
            )
            continue
        model = pickle.loads(device.model)
        data = data.reshape(1, -1)
        predict_result = model.predict(data)
        status = (
            config.ALARM_STATUS["NORMAL"]
            if predict_result[0] == 0
            else config.ALARM_STATUS["ALARM"]
        )
        return_data.append(
            {
                "key": key,
                "time": datetime.now(),
                "status": status,
                "type": 1,
            }
        )

    return {
        "code": 200,
        "message": "Predict success",
        "data": return_data,
    }

from fastapi import FastAPI, APIRouter, WebSocket
from fastapi.responses import StreamingResponse
from typing import Generator
from src.consumer import Consumer
from src.config import Config
import numpy as np

app = FastAPI()
config = Config()
consumer = Consumer(bootstrap_servers=config.BOOTSTRAP_SERVERS, topic=config.TOPIC)


def yield_stream_data():
    for data in consumer.consume_iter():
        yield data.tobytes()


router = APIRouter()


@router.get("/ping")
async def ping():
    return {"code": 200, "message": "pong"}


@router.get("/stream")
async def stream():
    return StreamingResponse(yield_stream_data(), media_type="application/octet-stream")


@router.get("/batch")
async def batch():
    batch = consumer.consume_one()
    return {"batch": batch.tolist()}


app.include_router(router, prefix="/sensor-service")

if __name__ == "__main__":
    import uvicorn

    uvicorn.run(app, host="0.0.0.0", port=8000)

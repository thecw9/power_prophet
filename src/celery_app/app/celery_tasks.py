from celery import Task
from app.celery_app import app
from app.utils.request import (
    get_keys_from_nrmock_service,
    get_realtime_data_from_nrmock_service,
    store_realtime_data,
    model_predict,
    store_alarm_data,
)


class MyTask(Task):
    def on_failure(self, exc, task_id, args, kwargs, einfo):
        print("Task failed: {0!r}".format(exc))
        # self.update_state(task_id=task_id, state="FAILURE", meta={"exc": str(exc)})


import time


@app.task(base=MyTask)
def pull_oil_chromatography():
    keys = get_keys_from_nrmock_service(include=["油色谱"])
    data = get_realtime_data_from_nrmock_service(keys)
    response = store_realtime_data(data)
    data = model_predict(data)
    response = store_alarm_data(data)
    return {
        "status": "success",
        "message": "油色谱数据拉取成功",
    }


@app.task(base=MyTask)
def pull_part_discharge():
    keys_1 = get_keys_from_nrmock_service(include=["局部放电"])
    keys_2 = get_keys_from_nrmock_service(include=["局放"])
    keys = keys_1 + keys_2
    data = get_realtime_data_from_nrmock_service(keys)
    response = store_realtime_data(data)
    data = model_predict(data)
    response = store_alarm_data(data)
    return {
        "status": "success",
        "message": "局放数据拉取成功",
    }


@app.task(base=MyTask)
def pull_iron_core():
    keys = get_keys_from_nrmock_service(include=["接地电流"])
    data = get_realtime_data_from_nrmock_service(keys)
    response = store_realtime_data(data)
    data = model_predict(data)
    response = store_alarm_data(data)
    return {
        "status": "success",
        "message": "接地电流数据拉取成功",
    }

from app.config import Config
from app.logger import Logger
from celery import states
from celery.signals import task_failure

from celery import Celery
from celery.schedules import crontab

config = Config()
logger = Logger(__name__)

app = Celery(
    "tasks",
    broker=config.CELERY_BROKER_URL,
    backend=config.CELERY_RESULT_BACKEND,
    include=["app.celery_tasks"],
    # broker_connection_retry_on_startup=True,
)

app.conf.update(
    broker_connection_retry_on_startup=True,
    timezone="Asia/Shanghai",
    enable_utc=True,
)


app.conf.beat_schedule = {
    # every 1 minute
    "pull_oil_chromatography": {
        "task": "app.celery_tasks.pull_oil_chromatography",
        # "schedule": crontab(minute=1),
        "schedule": crontab(hour="*/1"),
    },
    "pull_part_discharge": {
        "task": "app.celery_tasks.pull_part_discharge",
        # "schedule": crontab(minute=1),
        "schedule": crontab(hour="*/1"),
    },
    "pull_iron_core": {
        "task": "app.celery_tasks.pull_iron_core",
        # "schedule": crontab(minute=1),
        "schedule": crontab(hour="*/1"),
    },
}


if __name__ == "__main__":
    app.start()

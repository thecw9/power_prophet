from pathlib import Path
import numpy as np
import logging
from src.config import Config
from src.storer import WavStorer
from src.consumer import Consumer
import os
import sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))


config = Config()

if __name__ == "__main__":
    if not config.BOOTSTRAP_SERVERS or not config.TOPIC:
        logging.error(
            "Please set the BOOTSTRAP_SERVERS and TOPIC environment variables before running the consumer."
        )
        exit(1)
    if not config.STORE_DIR:
        logging.error(
            "Please set the STORE_DIR environment variable before running the consumer."
        )
        exit(1)
    if not config.DEVICE or not config.SAMPLE_RATE:
        logging.error(
            "Please set the DEVICE and SAMPLE_RATE environment variables before running the consumer."
        )
        exit(1)

    consumer = Consumer(bootstrap_servers=config.BOOTSTRAP_SERVERS, topic=config.TOPIC)
    storer = WavStorer(
        base_path=Path(config.STORE_DIR),
        sample_rate=int(config.SAMPLE_RATE),
        device=config.DEVICE,
    )

    for data in consumer.consume_iter():
        storer.store(data)

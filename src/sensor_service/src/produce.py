from kafka import KafkaProducer
import numpy as np
import time
import logging
from lib.pydaq.base import BaseDevice
from src.config import Config
from lib.pydaq.microphone import Microphone
from src.producer import Producer
import os
import sys


sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
config = Config()


if __name__ == "__main__":
    # logging.basicConfig(level=logging.INFO)
    if not config.BOOTSTRAP_SERVERS or not config.TOPIC:
        logging.error(
            "Please set the BOOTSTRAP_SERVERS and TOPIC environment variables before running the producer."
        )
        exit(1)
    if not config.DEVICE or not config.SAMPLE_RATE:
        logging.error(
            "Please set the DEVICE and SAMPLE_RATE environment variables before running the producer."
        )
        exit(1)

    producer = Producer(bootstrap_servers=config.BOOTSTRAP_SERVERS, topic=config.TOPIC)
    device = Microphone(
        device=config.DEVICE, channels=1, sample_rate=int(config.SAMPLE_RATE)
    )
    while True:
        data = device.read(num_samples=1000)
        data = data.squeeze()
        producer.send(data)

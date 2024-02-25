from kafka import KafkaProducer
import numpy as np
import time
import logging
from lib.pydaq.base import BaseDevice
from src.config import Config
from lib.pydaq.microphone import Microphone

config = Config()


class Producer:
    def __init__(self, bootstrap_servers: str, topic: str) -> None:
        self.bootstrap_servers = bootstrap_servers
        self.topic = topic
        self._connect_to_kafka()

    def send(self, data: np.ndarray):
        try:
            self.producer.send(self.topic, data.tobytes())
            self.producer.flush()
        except Exception as e:
            logging.error(
                f"Failed to send data to Kafka topic: {self.topic}\nError: {e}"
            )

    def _connect_to_kafka(self):
        while True:
            try:
                self.producer = KafkaProducer(bootstrap_servers=self.bootstrap_servers)
                logging.info(f"Connected to Kafka broker(s): {self.bootstrap_servers}")
                break
            except Exception as e:
                logging.error(
                    f"Failed to connect to Kafka broker(s): {self.bootstrap_servers}\n"
                    f"Make sure that Kafka is running and that the broker(s) are reachable from this host.\n"
                    f"Error: {e}"
                )
                logging.info("Retrying to connect to Kafka broker(s) in 5 seconds...")
                time.sleep(5)


if __name__ == "__main__":
    # logging.basicConfig(level=logging.INFO)
    if not config.BOOTSTRAP_SERVERS or not config.TOPIC:
        logging.error(
            "Please set the BOOTSTRAP_SERVERS and TOPIC environment variables before running the producer."
        )
        exit(1)
    producer = Producer(bootstrap_servers=config.BOOTSTRAP_SERVERS, topic=config.TOPIC)
    device = Microphone(device="USB_MIC", channels=1)
    while True:
        data = device.read(num_samples=1000)
        data = data.squeeze()
        producer.send(data)

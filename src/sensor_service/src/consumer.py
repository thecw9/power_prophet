from kafka import KafkaConsumer
from typing import Generator
import time
import numpy as np

import logging
from src.config import Config

config = Config()


class Consumer:
    def __init__(self, bootstrap_servers: str, topic: str) -> None:
        self.bootstrap_servers = bootstrap_servers
        self.topic = topic
        self._connect_to_kafka()

    def _connect_to_kafka(self):
        while True:
            try:
                self.consumer = KafkaConsumer(
                    self.topic,
                    bootstrap_servers=self.bootstrap_servers,
                    auto_offset_reset="latest",
                )
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

    def consume_iter(self) -> Generator[np.ndarray, None, None]:
        try:
            for message in self.consumer:
                yield np.frombuffer(message.value, dtype=np.float32)
        except Exception as e:
            logging.error(
                f"Failed to consume data from Kafka topic: {self.topic}\nError: {e}"
            )

    def consume_one(self) -> np.ndarray:
        message = next(self.consumer)
        return np.frombuffer(message.value, dtype=np.float32)


if __name__ == "__main__":
    if not config.BOOTSTRAP_SERVERS or not config.TOPIC:
        logging.error(
            "Please set the BOOTSTRAP_SERVERS and TOPIC environment variables before running the consumer."
        )
        exit(1)
    consumer = Consumer(bootstrap_servers=config.BOOTSTRAP_SERVERS, topic=config.TOPIC)
    for message in consumer.consume_iter():
        print(message)

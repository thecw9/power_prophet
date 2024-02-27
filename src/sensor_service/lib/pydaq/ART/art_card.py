import atexit
import os
import subprocess
import warnings
from pathlib import Path

import numpy as np


class ARTCard:
    def __init__(self):
        warnings.warn(
            "Because of the ART card's limitations, this class is deprecated. ",
            DeprecationWarning,
        )
        current_dir = Path(os.path.dirname(os.path.realpath(__file__)))
        process_path = current_dir / "c" / "main"
        self.daq_process = subprocess.Popen([process_path], shell=True)
        # check if fifo exists
        self.fifo_path = Path("acts3100.pipe")
        if not os.path.exists(self.fifo_path):
            os.mkfifo(self.fifo_path)
        self.fifo = os.open(self.fifo_path, os.O_RDONLY)
        self.data = None
        atexit.register(self.close)

    def read(self, num_samples=44100):
        # channels * bytes per sample
        bytes_per_sample = 8 * 8
        # total bytes to read
        bytes_to_read = num_samples * bytes_per_sample
        if bytes_to_read <= 65536:
            data = os.read(self.fifo, bytes_to_read)
        else:
            data = b""
            for i in range(bytes_to_read // 65536):
                data += os.read(self.fifo, 65536)
            data += os.read(self.fifo, bytes_to_read % 65536)
        if not data:
            return None
        self.data = np.frombuffer(data, dtype=np.float64).reshape(-1, 8)
        return self.data

    def close(self):
        # os.close(self.fifo)
        self.daq_process.kill()


if __name__ == "__main__":
    reader = ARTCard()
    import time

    while True:
        start = time.time()
        data = reader.read(num_samples=44100)
        end = time.time()
        print("Time taken: ", end - start)
        if data is not None:
            print(data.shape)
            print(data)

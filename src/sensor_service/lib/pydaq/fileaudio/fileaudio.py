import time
from pathlib import Path
from typing import Union

import numpy as np
import soundfile as sf


class FileAudio:
    def __init__(
        self,
        dir: Union[str, Path],
        channels: int = 1,
        samplerate=48000,
        recursive: bool = True,
    ):
        """
        Read audio data from WAV files in a directory recursively.

        Args:
            dir: Directory to read WAV files from.
            channels: Number of channels to read from the WAV files.
            samplerate: Sample rate of the WAV files.
            recursive: Whether to read WAV files recursively.
        """
        self.dir = dir
        self.channels = channels
        self.sample_rate = samplerate
        self.recursive = recursive
        self.files = sorted(Path(dir).glob("*.wav"))
        self.current_file_index = 0
        self.current_file_data = None
        self.current_position = 0

        if not self.files:
            print("No WAV files found in the directory")

    def _read_file(self, file: Path):
        """
        Read a WAV file.
        """
        print(f"Reading {file}")
        data, samplerate = sf.read(file)
        if samplerate != self.sample_rate:
            print(f"Sample rate of {file} is {samplerate}, expected {self.sample_rate}")
        if data.ndim == 1:
            data = data[:, np.newaxis]
        if data.ndim == 2:
            data = data[:, : self.channels]
        return data

    def read(self, num_samples) -> np.ndarray:
        # block to mock the read time
        time.sleep(num_samples / self.sample_rate)

        if self.current_file_data is None or (
            self.current_position + num_samples > len(self.current_file_data)
        ):
            self.current_file_index += 1
            if self.current_file_index >= len(self.files):
                print("Reached the end of the WAV files")
                if self.recursive:
                    self.current_file_index = 0
                else:
                    print("Not recursive, returning None")
                    return np.array([])

            self.current_file_data = self._read_file(
                self.files[self.current_file_index]
            )
            self.current_position = 0

        data = self.current_file_data[
            self.current_position : self.current_position + num_samples
        ]
        self.current_position += num_samples
        return data

    def close(self):
        pass

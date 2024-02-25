import numpy as np
from datetime import datetime
import soundfile as sf
from pathlib import Path


class WavStorer:
    def __init__(
        self, base_path: Path, sample_rate: int = 48000, device: str = "default"
    ):
        """
        :param base_path: Path to the directory where the files are stored
        :param sample_rate: Sample rate of the audio
        :param device: Name of the device, used to create a subfolder to store the files
        """
        self.base_path = base_path
        self.store_dir = base_path / device
        now = datetime.now()
        self.time_state = now.strftime("%Y-%m-%d_%H")
        self._current_filepath = self.generate_filepath(self.store_dir)
        self.file = sf.SoundFile(
            self._current_filepath, mode="w", samplerate=sample_rate, channels=1
        )

    def generate_filepath(self, base_path: Path) -> Path:
        now = datetime.now()
        additional_path = now.strftime("%Y-%m-%d")
        path = base_path / additional_path
        path.mkdir(parents=True, exist_ok=True)
        filename = now.strftime("%Y-%m-%d_%H") + ".wav"
        return Path(path / filename)

    def store(self, data: np.ndarray):
        """
        Store the data in the file

        :param data: Data to store with shape (n_samples,)
        """
        if data.ndim > 1:
            raise ValueError("Data should have only one dimension")

        now = datetime.now()
        if self.time_state != now.strftime("%Y-%m-%d_%H"):
            self.file.close()
            self.time_state = now.strftime("%Y-%m-%d_%H")
            self.file = sf.SoundFile(
                self.generate_filepath(self.store_dir),
                mode="w",
                samplerate=48000,
                channels=1,
            )
        self.file.write(data)

import numpy as np


class BaseDevice:
    def read(self) -> np.ndarray:
        raise NotImplementedError

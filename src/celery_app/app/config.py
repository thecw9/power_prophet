import abc
import os
from pathlib import Path

from dotenv import load_dotenv


def is_running_in_docker():
    # Check if the /proc/1/cgroup file exists
    return (
        os.path.exists("/.dockerenv")
        or os.path.isfile("/proc/1/cgroup")
        and any("docker" in line for line in open("/proc/1/cgroup"))
    )


current_dir = Path(__file__).parent
if is_running_in_docker():
    print("Running in docker")
    load_dotenv(dotenv_path=current_dir.parent / ".dockerenv")
else:
    print("Running locally")
    load_dotenv(dotenv_path=current_dir.parent / ".env")


class Singleton(abc.ABCMeta, type):
    """
    Singleton metaclass for ensuring only one instance of a class.
    """

    _instances = {}

    def __call__(cls, *args, **kwargs):
        """Call method for the singleton metaclass."""
        if cls not in cls._instances:
            cls._instances[cls] = super(Singleton, cls).__call__(*args, **kwargs)
        return cls._instances[cls]


class AbstractSingleton(abc.ABC, metaclass=Singleton):
    """
    Abstract singleton class for ensuring only one instance of a class.
    """

    pass


class Config(metaclass=Singleton):
    CELERY_BROKER_URL = os.getenv("CELERY_BROKER_URL")
    CELERY_RESULT_BACKEND = os.getenv("CELERY_RESULT_BACKEND")
    NRMOCK_SERVICE_URL = os.getenv("NRMOCK_SERVICE_URL")
    BACKEND_SERVICE_URL = os.getenv("DATA_SERVICE_URL")


class APPState(metaclass=Singleton):
    """
    Singleton class for storing application state.
    """

    def __init__(self):
        self._state = {}

    def set(self, key, value):
        """Set a key value pair in the state."""
        self._state[key] = value

    def get(self, key):
        """Get a value from the state."""
        return self._state.get(key)

    def delete(self, key):
        """Delete a key value pair from the state."""
        if key in self._state:
            del self._state[key]

    def clear(self):
        """Clear the state."""
        self._state.clear()

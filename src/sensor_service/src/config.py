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
    print("Running in Docker")
    load_dotenv(dotenv_path=current_dir.parent / ".dockerenv")
else:
    print("Running locally")
    load_dotenv(dotenv_path=current_dir.parent / ".env")


class Config:
    DEVICE = os.getenv("DEVICE")
    SAMPLE_RATE = os.getenv("SAMPLE_RATE")
    BOOTSTRAP_SERVERS = os.environ["BOOTSTRAP_SERVERS"]
    TOPIC = os.environ["TOPIC"]
    STORE_DIR = os.getenv("STORE_DIR")

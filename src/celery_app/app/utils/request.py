import requests

from app.config import Config

config = Config()


def get_keys_from_nrmock_service(
    include: list[str], exclude: list[str] = []
) -> list[int]:
    """Get keys from the API.

    Args:
        include (list[str]): List of keys to include.
        exclude (list[str], optional): List of keys to exclude. Defaults to [].

    Returns:
        list[int]: List of keys.
    """
    if not config.NRMOCK_SERVICE_URL:
        raise ValueError("NRMOCK_SERVICE_URL is not set.")

    url = config.NRMOCK_SERVICE_URL + "/nrmock-service/keys"
    params = {"include": include, "exclude": exclude}
    response = requests.post(url, json=params)
    response = response.json()
    keys = [d["id"] for d in response["data"]]

    return keys


def get_realtime_data_from_nrmock_service(keys: list[int]) -> list[dict]:
    """Get realtime data by key.

    Args:
        key (int): Key of the data.

    Returns:
        dict: Realtime data.
    """
    if not config.NRMOCK_SERVICE_URL:
        raise ValueError("NRMOCK_SERVICE_URL is not set.")

    url = config.NRMOCK_SERVICE_URL + "/nrmock-service/realtime/mock"
    str_keys = [str(k) for k in keys]
    params = {"keys": str_keys}
    response = requests.post(url, json=params).json()
    data = [
        {
            "key": d["attr_oid"],
            "value": d["fvalue"],
            "time": d["attr_time"],
        }
        for d in response["data"]
    ]

    return data


def store_realtime_data(data: list[dict]) -> dict:
    """Store realtime data.

    Args:
        data (dict): Realtime data.

    Returns:
        dict: Response data.
    """
    if not config.BACKEND_SERVICE_URL:
        raise ValueError("DATA_SERVICE_URL is not set.")

    url = config.BACKEND_SERVICE_URL + "/measures-service/realtime/store"
    response = requests.post(url, json=data).json()

    return response


def model_predict(data: list[dict]) -> list[dict]:
    if not config.BACKEND_SERVICE_URL:
        raise ValueError("DATA_SERVICE_URL is not set.")

    url = config.BACKEND_SERVICE_URL + "/model-service/predict"
    try:
        response = requests.post(url, json=data).json()
    except Exception as e:
        raise ValueError(str(e))

    if not response["code"] == 200:
        raise ValueError(response["message"])

    return response["data"]


def store_alarm_data(data: list[dict]):
    if not config.BACKEND_SERVICE_URL:
        raise ValueError("DATA_SERVICE_URL is not set.")

    url = config.BACKEND_SERVICE_URL + "/alarm-service/status/store"
    response = requests.post(url, json=data).json()

    return response


if __name__ == "__main__":
    keys = get_keys_from_nrmock_service(include=["高抗A相", "油色谱"])
    print(keys)

    data = get_realtime_data_from_nrmock_service(keys)
    from pprint import pprint

    pprint(data)

    response = store_realtime_data(data)
    data = model_predict(data)
    response = store_alarm_data(data)

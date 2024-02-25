import axios from "@/utils/csustRequest";

export function trainModel(keys, startTrain, endTrain) {
  const data = {
    keys: keys,
    start_time: startTrain,
    end_time: endTrain,
  };
  return axios.post("/model-service/train", data, {
    headers: {
      "Content-Type": "application/json",
    },
  });
}

// predict
export function modelPredict(data) {
  return axios.post("/model-service/predict", data, {
    headers: {
      "Content-Type": "application/json",
    },
  });
}

// describe
export function modelDescribe(key) {
  const data = {
    key: key,
  };
  return axios.post("/model-service/describe", data, {
    headers: {
      "Content-Type": "application/json",
    },
  });
}

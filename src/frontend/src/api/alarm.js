import axios from "@/utils/csustRequest";

// 通过时间获取历史数据
export function getHistoryAlarmByTime(
  startTime = null,
  endTime = null,
  page = null,
  size = null,
) {
  const data = {
    start_time: startTime,
    end_time: endTime,
    page: page,
    size: size,
  };
  return axios.post("/alarm-service/history", data, {
    headers: {
      Accept: "application/json",
      "Content-Type": "application/json",
    },
  });
}

<script setup>
import { ref, reactive, onMounted, watch, onBeforeUnmount, provide } from "vue";
import { getDevicesInfo } from "@/api/devices";
import { getDeviceHistoryAlarm } from "@/api/alarm";
import WindTurbine from "./components/WindTurbine.vue";
import TrainAllButton from "@/components/TrainAllButton.vue";

const device = ref("1000kV潇江Ⅰ线/高抗B相");

const devices = ref([]);
const alarmMessages = ref([]);

const setData = async () => {
  await getDevicesInfo("").then((res) => {
    if (res.code === 200) {
      devices.value = res.data
        .map((item) => {
          return {
            key: item.key,
            path: item.path.split("/").slice(2).join("/"),
            status:
              item.status === 0
                ? "未知"
                : item.status === 1
                  ? "正常"
                  : item.status === 2
                    ? "预警"
                    : item.status === 3
                      ? "报警"
                      : "未知",
          };
        })
        .sort((a, b) => a.key - b.key);
    }
  });
};

const setAlarmData = async () => {
  await getDeviceHistoryAlarm(
    new Date() - 1000 * 60 * 60 * 24 * 7,
    new Date(),
    1,
    20,
  ).then((res) => {
    if (res.code === 200) {
      alarmMessages.value = res.data.map((item) => {
        return {
          key: item.key,
          path: item.path.split("/")[item.path.split("/").length - 2],
          time: item.service_time?.replace("T", " ").split(".")[0],
          status:
            item.status === 0
              ? "模型未训练"
              : item.status === 1
                ? "正常"
                : item.status === 2
                  ? "预警"
                  : item.status === 3
                    ? "报警"
                    : "未知",
        };
      });
    }
  });
};

const className = (status) => {
  if (status === "正常") {
    return "success-row";
  } else if (status === "报警" || status === "异常") {
    return "error-row";
  }
  return "warning-row";
};

let interval = null;
onMounted(() => {
  setData();
  setAlarmData();
  interval = setInterval(() => {
    setData();
    setAlarmData();
  }, 5000);
});

onBeforeUnmount(() => {
  clearInterval(interval);
});
</script>

<template>
  <el-row>
    <el-col :span="8">
      <h1>告警信息</h1>
      <el-table :data="alarmMessages" style="width: 100%" height="630">
        <el-table-column
          prop="path"
          label="设备编号"
          width="100"
        ></el-table-column>
        <el-table-column prop="time" label="时间" width="180"></el-table-column>
        <el-table-column
          prop="status"
          label="状态"
          width="100"
        ></el-table-column>
      </el-table>
    </el-col>

    <el-col :span="16">
      <div class="train-all">
        <el-select
          v-model="device"
          placeholder="请选择设备"
          clearable
          style="width: 270px"
        >
         <!-- for loop devices -->
          <el-option
            v-for="item in devices"
            :key="item.key"
            :label="item.path"
            :value="item.path"
          ></el-option>
        </el-select>
        <div>
          <TrainAllButton :data="devices" :fusion="true" @set-data="setData" />
        </div>
      </div>
      <div class="box">
        <wind-turbine
          v-for="item in devices"
          :key="item.key"
          :id="item.key"
          :status="item.status"
          :path="item.path"
        ></wind-turbine>
      </div>
    </el-col>
  </el-row>
</template>

<style scoped>
.box {
  width: 100%;
  height: 100%;
  display: flex;
  flex-wrap: wrap;
}

.train-all {
  display: flex;
  margin-bottom: 15px;
  margin-right: 15px;
  justify-content: space-between;
}

h1 {
  font-size: 20px;
  margin-bottom: 20px;
}
</style>

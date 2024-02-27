<script setup>
import { ref, reactive } from "vue";
import { trainModel, modelDescribe } from "@/api/model";
import { getHistoryDataByTime, getMeasuresInfoByKey } from "@/api/measures";
import { ElNotification, ElMessage } from "element-plus";
import * as echarts from "echarts";

const emit = defineEmits(["setData"]);

const key_store = ref("");

const modelDetailDrawer = ref(false);
const historyDataDrawer = ref(false);
// last 30 days
const historyDataTimeRange = ref([
  new Date(new Date().getTime() - 3600 * 1000 * 24 * 30),
  new Date(),
]);
const trainDataTimeRange = ref([
  new Date(new Date().getTime() - 3600 * 1000 * 24 * 30),
  new Date(),
]);

const shortcuts = [
  {
    text: "Today",
    value: () => {
      const end = new Date();
      const start = new Date();
      start.setHours(0);
      start.setMinutes(0);
      start.setSeconds(0);
      return [start, end];
    },
  },
  {
    text: "Last 1 day",
    value: () => {
      const end = new Date();
      const start = new Date();
      start.setTime(start.getTime() - 3600 * 1000 * 24);
      return [start, end];
    },
  },
  {
    text: "Last week",
    value: () => {
      const end = new Date();
      const start = new Date();
      start.setTime(start.getTime() - 3600 * 1000 * 24 * 7);
      return [start, end];
    },
  },
  {
    text: "Last month",
    value: () => {
      const end = new Date();
      const start = new Date();
      start.setTime(start.getTime() - 3600 * 1000 * 24 * 30);
      return [start, end];
    },
  },
  {
    text: "Last 3 months",
    value: () => {
      const end = new Date();
      const start = new Date();
      start.setTime(start.getTime() - 3600 * 1000 * 24 * 90);
      return [start, end];
    },
  },
];
const probsChart = ref();
const trainDataChart = ref();
const historyDataChart = ref();
let probsChartInstance = null;
let trainDataChartInstance = null;
let historyDataChartInstance = null;
const modelDetailDrawerData = reactive({
  key: "",
  model_name: "",
  model_is_trained: "",
  model_updated_at: "",
  model_version: "",
  train_data_total: "",
  time: "",
  status: "",
  value: null,
});
const historyDataDrawerData = reactive({
  data: [],
});

const props = defineProps({
  title: {
    type: String,
    default: "",
  },
  data: {
    type: Object,
    default: () => [],
  },
});

const tableRowClassName = ({ row, rowIndex }) => {
  if (row.status === "正常") {
    return "success-row";
  } else if (row.status === "报警" || row.status === "异常") {
    return "error-row";
  }
  return "warning-row";
};

const handleTrain = async (key) => {
  const res = await trainModel(
    [key],
    trainDataTimeRange.value[0],
    trainDataTimeRange.value[1],
  );
  if (res.code === 200) {
    ElNotification({
      title: "模型训练",
      message: "模型开始训练",
      type: "success",
    });
    // sleep 1s
    await new Promise((resolve) => {
      setTimeout(() => {
        resolve();
      }, 500);
    });
    emit("setData");
  } else {
    ElMessage.error("失败");
  }
};

const handleOpenModelDetailDrawer = () => {
  probsChartInstance = echarts.init(probsChart.value);
  trainDataChartInstance = echarts.init(trainDataChart.value);
  window.addEventListener("resize", () => {
    probsChartInstance.resize();
    trainDataChartInstance.resize();
  });
};

const handleOpenHistoryDataDrawer = () => {
  historyDataChartInstance = echarts.init(historyDataChart.value);
  window.addEventListener("resize", () => {
    historyDataChartInstance.resize();
  });
};

const handleCloseModelDetailDrawer = () => {
  probsChartInstance.dispose();
  trainDataChartInstance.dispose();
};

const handleCloseHistoryDataDrawer = () => {
  historyDataChartInstance.dispose();
};

const handleViewModelDetailDrawer = async (key) => {
  modelDetailDrawer.value = true;
  const res = await getMeasuresInfoByKey(key);
  if (res.code === 200) {
    modelDetailDrawerData.key = res.data.key;
    modelDetailDrawerData.model_name = res.data.model_name;
    modelDetailDrawerData.model_is_trained = res.data.model_is_trained
      ? "已训练"
      : "未训练";
    modelDetailDrawerData.model_updated_at = res.data.model_updated_at;
    modelDetailDrawerData.model_version = res.data.model_version;
    modelDetailDrawerData.train_data_total = res.data.train_data_total;
    modelDetailDrawerData.time = res.data.time;
    modelDetailDrawerData.status = res.data.status;
    modelDetailDrawerData.value = res.data.value;
  }

  await modelDescribe(key).then((res) => {
    if (res.code === 200) {
      const train_data = res.data.description.X_train;
      const probs_density = res.data.description.probs_density;
      probsChartInstance.setOption({
        title: {
          text: "概率密度分布",
          left: "center",
          textStyle: {
            color: "#ccc",
            fontSize: 16,
          },
        },
        tooltip: {
          trigger: "axis",
          axisPointer: {
            type: "cross",
          },
        },
        xAxis: [
          {
            type: "category",
            data: probs_density.map((item) => item[0]),
          },
          {
            type: "value",
            min: probs_density[0][0],
            max: probs_density[probs_density.length - 1][0],
            splitLine: {
              show: false,
            },
            show: false,
            xAxisIndex: 1,
          },
        ],
        yAxis: {
          type: "value",
          splitLine: {
            show: false,
          },
          gridIndex: 0,
        },
        grid: {
          top: "10%",
          left: "3%",
          right: "4%",
          bottom: "3%",
          containLabel: true,
        },
        series: [
          {
            data: probs_density.map((item) => item[1]),
            type: "line",
            smooth: true,
          },
          {
            symbolSize: 3,
            data: train_data.map((item) => [item, 0]),
            type: "scatter",
            xAxisIndex: 1,
          },
        ],
      });
      trainDataChartInstance.setOption({
        title: {
          text: "训练数据",
          left: "center",
          textStyle: {
            color: "#ccc",
            fontSize: 16,
          },
        },
        tooltip: {
          trigger: "axis",
          axisPointer: {
            type: "cross",
          },
        },
        xAxis: {
          type: "value",
          splitLine: {
            show: false,
          },
        },
        yAxis: {
          type: "value",
          min:
            Math.min(...train_data) -
            (Math.max(...train_data) - Math.min(...train_data)) * 0.2,
          max:
            Math.max(...train_data) +
            (Math.max(...train_data) - Math.min(...train_data)) * 0.2,
          splitLine: {
            show: false,
          },
        },
        series: [
          {
            data: train_data.map((item, index) => [index, item]),
            symbolSize: 3,
            type: "scatter",
          },
        ],
      });
    }
  });
};

const handleViewHistoryDataDrawer = async (key) => {
  historyDataDrawer.value = true;
  key_store.value = key;
  setHistoryData();
};

const setHistoryData = async () => {
  const res = await getHistoryDataByTime(
    [key_store.value],
    historyDataTimeRange.value[0],
    historyDataTimeRange.value[1],
  );
  if (res.code === 200) {
    const historyData = res.data
      .filter((item) => item.key === key_store.value)[0]
      .data.map((item) => {
        return {
          time: item.time?.replace("T", " ").split(".")[0],
          service_time: item.service_time?.replace("T", " ").split(".")[0],
          value: item.value,
        };
      })
      .sort((a, b) => {
        return new Date(a.service_time) - new Date(b.service_time);
      });
    historyDataDrawerData.data = historyData;
    historyDataChartInstance.setOption({
      title: {
        text: "历史数据",
        left: "center",
        textStyle: {
          color: "#ccc",
          fontSize: 16,
        },
      },
      tooltip: {
        trigger: "axis",
        axisPointer: {
          type: "cross",
        },
      },
      xAxis: {
        type: "category",
        data: historyData.map((item) => item.time),
      },
      yAxis: {
        type: "value",
        min:
          Math.min(...historyData.map((item) => item.value)) -
          (Math.max(...historyData.map((item) => item.value)) -
            Math.min(...historyData.map((item) => item.value))) *
            0.2,
        max:
          Math.max(...historyData.map((item) => item.value)) +
          (Math.max(...historyData.map((item) => item.value)) -
            Math.min(...historyData.map((item) => item.value))) *
            0.2,
        splitLine: {
          show: false,
        },
      },
      series: [
        {
          data: historyData.map((item) => item.value),
          type: "line",
          smooth: true,
        },
      ],
    });
  }
};
</script>

<template>
  <div>
    <h1>{{ props.title }}</h1>
    <el-table
      :data="props.data"
      border
      style="width: 100%"
      :row-class-name="tableRowClassName"
    >
      <el-table-column prop="key" label="测点编号" align="center" width="170" />
      <el-table-column prop="path" label="测点" align="center" width="230" />
      <el-table-column prop="time" label="时间" align="center" width="180" />
      <el-table-column prop="value" label="值" align="center" width="120" />
      <el-table-column prop="unit" label="单位" align="center" width="80" />
      <el-table-column prop="status" label="状态" align="center" width="110" />
      <el-table-column label="操作" align="center" fixed="right" width="320">
        <template #default="scope">
          <el-button type="danger" @click="handleTrain(scope.row.key)"
            >训练模型</el-button
          >
          <el-button @click="handleViewModelDetailDrawer(scope.row.key)"
            >模型详情</el-button
          >
          <el-button @click="handleViewHistoryDataDrawer(scope.row.key)"
            >历史数据</el-button
          >
        </template>
      </el-table-column>
    </el-table>

    <!-- 模型详情抽屉 -->
    <el-drawer
      v-model="modelDetailDrawer"
      title="模型详情"
      size="40%"
      @open="handleOpenModelDetailDrawer"
      @closed="handleCloseModelDetailDrawer"
    >
      <span style="margin-bottom: 10px; font-size: 18px"
        >选择训练数据时间范围：</span
      >
      <el-date-picker
        v-model="trainDataTimeRange"
        type="datetimerange"
        :shortcuts="shortcuts"
        range-separator="To"
        start-placeholder="Start date"
        end-placeholder="End date"
      />
      <el-button @click="handleTrain(modelDetailDrawerData.key)"
        >训练模型</el-button
      >
      <el-divider></el-divider>
      <span>测点编号：{{ modelDetailDrawerData.key }}</span>
      <span>模型名称：{{ modelDetailDrawerData.model_name }}</span>
      <span>模型是否训练：{{ modelDetailDrawerData.model_is_trained }}</span>
      <span>模型更新时间：{{ modelDetailDrawerData.model_updated_at }}</span>
      <span>模型版本：{{ modelDetailDrawerData.model_version }}</span>
      <span>训练数据总数：{{ modelDetailDrawerData.train_data_total }}</span>
      <span>时间：{{ modelDetailDrawerData.time }}</span>
      <span>当前测点状态：{{ modelDetailDrawerData.status }}</span>
      <span>当前测点值：{{ modelDetailDrawerData.value }}</span>
      <div ref="probsChart" style="width: 100%; height: 300px"></div>
      <div ref="trainDataChart" style="width: 100%; height: 300px"></div>
    </el-drawer>

    <!-- 历史数据抽屉 -->
    <el-drawer
      v-model="historyDataDrawer"
      title="历史数据"
      size="40%"
      @open="handleOpenHistoryDataDrawer"
      @closed="handleCloseHistoryDataDrawer"
    >
      <el-date-picker
        v-model="historyDataTimeRange"
        type="datetimerange"
        :shortcuts="shortcuts"
        range-separator="To"
        start-placeholder="Start date"
        end-placeholder="End date"
      />
      <el-button @click="setHistoryData">查询</el-button>
      <el-divider></el-divider>
      <div ref="historyDataChart" style="width: 100%; height: 300px"></div>
      <el-table
        :data="historyDataDrawerData.data"
        border
        style="width: 100%"
        height="650"
      >
        <el-table-column prop="time" label="时间" align="center" />
        <el-table-column prop="service_time" label="业务时间" align="center" />
        <el-table-column prop="value" label="值" align="center" />
      </el-table>
    </el-drawer>
  </div>
</template>

<style scoped>
span {
  display: flex;
  font-size: 16px;
}
</style>

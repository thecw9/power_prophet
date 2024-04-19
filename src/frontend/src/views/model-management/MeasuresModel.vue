<script setup>
import { ref, reactive, onMounted } from "vue";
import { getMeasuresInfo } from "@/api/measures";
import { trainModel, modelDescribe } from "@/api/model";
import { ElNotification, ElMessage } from "element-plus";
import { formatNumber } from "@/utils/index";
import TrainAllButton from "@/components/TrainAllButton.vue";
import * as echarts from "echarts";

const data = ref([]);
const drawer = ref(false);
const form = reactive({
  include: "潇江Ⅰ线 油色谱",
  exclude: "",
});
const probsChart = ref();
const trainDataChart = ref();
let probsChartInstance = null;
let trainDataChartInstance = null;
const drawerData = reactive({
  model_updated_at: "",
  model_version: "",
  time: "",
  status: "",
  value: null,
});

const setData = async () => {
  await getMeasuresInfo(
    form.include.replace(" ", "&"),
    form.exclude.replace(" ", "&"),
  ).then((res) => {
    if (res.code === 200) {
      data.value = res.data.map((item) => {
        return {
          key: item.key,
          path: item.path,
          value: item.value,
          time: item.time.replace("T", " ").split(".")[0],
          model_name: item.model_name,
          is_trained: item.model_is_trained ? "是" : "否",
          model_updated_at: item.model_updated_at
            ?.replace("T", " ")
            .split(".")[0],
          model_version: item.model_version,
          status: item.model_is_trained
            ? item.status === 1
              ? "正常"
              : "异常"
            : "模型未训练",
        };
      });
      ElNotification({
        title: "查询成功",
        message: "数据查询成功",
        type: "success",
      });
    }
  });
};

const tableRowClassName = ({ row, rowIndex }) => {
  if (row.status === "正常") {
    return "success-row";
  } else if (row.status === "异常") {
    return "error-row";
  }
  return "warning-row";
};
onMounted(() => {
  setData();
});

const handleTrain = async (row) => {
  const res = await trainModel([row.key]);
  if (res.code === 200) {
    ElNotification({
      title: "模型训练",
      message: "模型开始训练",
      type: "success",
    });
  } else {
    ElMessage.error("模型训练失败");
  }
};

const handleViewTrainProgress = () => {
  window.open("http://127.0.0.1:5555");
};

const handleTrainAll = async () => {
  const res = await trainModel(data.value.map((item) => item.key));
  if (res.code === 200) {
    ElNotification({
      title: "训练成功",
      message: "模型训练成功",
      type: "success",
    });
  } else {
    ElMessage.error("模型训练失败");
  }
};

const handleOpenDrawer = () => {
  probsChartInstance = echarts.init(probsChart.value);
  trainDataChartInstance = echarts.init(trainDataChart.value);
};

const handleCloseDrawer = () => {
  probsChartInstance.dispose();
  trainDataChartInstance.dispose();
};

const handleView = async (row) => {
  drawer.value = true;
  const model_key = row.key;
  drawerData.model_updated_at = row.model_updated_at;
  drawerData.model_version = row.model_version;
  drawerData.time = row.time;
  drawerData.status = row.status;
  drawerData.value = row.value;
  await modelDescribe(model_key).then((res) => {
    if (res.code === 200) {
      const train_data = res.data.description.X_train;
      const probs_density = res.data.description.probs_density;
      console.log(train_data);
      console.log(probs_density);
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
          },
        ],
        yAxis: {
          type: "value",
          splitLine: {
            show: false,
          },
        },
        series: [
          {
            data: probs_density.map((item) => item[1]),
            type: "line",
            smooth: true,
          },
          {
            symbolSize: 5,
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
</script>

<template>
  <!-- 搜索框 -->
  <div class="input_box">
    <el-form :inline="true" :model="form" class="demo-form-inline">
      <el-form-item label="包含">
        <el-input
          style="width: 270px"
          v-model="form.include"
          placeholder="请输入include关键字"
        ></el-input>
      </el-form-item>
      <el-form-item label="排除">
        <el-input
          style="width: 270px"
          v-model="form.exclude"
          placeholder="请输入exclude关键字"
        ></el-input>
      </el-form-item>
      <el-form-item>
        <el-button type="primary" @click="setData">更新数据</el-button>
        <TrainAllButton :data="data" :set-data="setData" />
      </el-form-item>
    </el-form>
  </div>
  <!-- 数据展示 -->
  <h1 style="text-align: center; font-size: 24px; font-weight: 600">
    {{ form.include }}模型管理
  </h1>
  <el-table :data="data" border style="width: 100%">
    <el-table-column prop="path" label="测点" width="450" align="center" />
    <el-table-column prop="is_trained" label="模型是否训练" align="center" />
    <el-table-column prop="model_name" label="模型名称" />
    <el-table-column prop="model_updated_at" label="模型更新时间" />
    <el-table-column prop="value" label="测点值" />
    <el-table-column label="操作" align="center" width="160">
      <template #default="scope">
        <el-button type="danger" @click="handleTrain(scope.row)"
          >训练</el-button
        >
        <el-button @click="handleView(scope.row)">查看</el-button>
      </template>
    </el-table-column>
  </el-table>

  <!-- 抽屉 -->
  <el-drawer
    v-model="drawer"
    title="模型详情"
    size="40%"
    @open="handleOpenDrawer"
    @closed="handleCloseDrawer"
  >
    <span>模型更新时间：{{ drawerData.model_updated_at }}</span>
    <span>模型版本：{{ drawerData.model_version }}</span>
    <span>时间：{{ drawerData.time }}</span>
    <span>当前测点状态：{{ drawerData.status }}</span>
    <span>当前测点值：{{ drawerData.value }}</span>
    <div ref="probsChart" style="width: 100%; height: 300px"></div>
    <div ref="trainDataChart" style="width: 100%; height: 300px"></div>
  </el-drawer>
</template>

<style scoped lang="scss">
.input_box {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 20px;
}

.el-input {
  width: 300px;
  margin-right: 15px;
}

.pagination {
  display: flex;
  justify-content: flex-end;
  margin-top: 5px;
}

.el-select {
  width: 300px;
}

span {
  display: flex;
  font-size: 16px;
}
</style>

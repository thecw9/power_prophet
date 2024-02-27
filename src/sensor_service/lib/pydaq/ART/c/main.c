// 本程序演示AI连续采样原码数据过程

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <stdlib.h>

#include "./lib/ACTS3100.h" // 驱动程序头文件，在您的工程代码中包含此文件即可使用驱动函数


#define CH_PERCHAN 102400
F64 fVoltArray[ACTS3100_AI_MAX_CHANNELS * CH_PERCHAN];

int main(int argc, char* argv[])
{
    ACTS3100_AI_PARAM AIParam;
    U32 nReadSampsPerChan = CH_PERCHAN;	// 每通道读取点数
    U32 nSampsPerChanRead = 0;
    F64 fTimeout = 1.0; // 1秒钟超时
    U32 nReadableSamps = 0;
    HANDLE hDevice = NULL;
    ACTS3100_MAIN_INFO MainInfo;
    U32 nChannel = 0;

    // 第一步 创建设备对象
    hDevice = ACTS3100_DEV_Create(0, 0);
    if (hDevice == NULL)
    {
        printf("DEV_Create Error\n");
        getc(stdin);
        return 1;
    }

    ACTS3100_GetMainInfo(hDevice, &MainInfo);			// DDR2的长度(单位：MB)
    switch (MainInfo.nDeviceType >> 16)
    {
    case 0x2012:
        printf("PXIE%04X\n", MainInfo.nDeviceType & 0xFFFF);
        break;
    case 0x2011:
        printf("PCIE%04X\n", MainInfo.nDeviceType & 0xFFFF);
        break;
    default:
        printf("ACTS3100-%04X\n", MainInfo.nDeviceType);
    }

    memset(&AIParam, 0, sizeof(ACTS3100_AI_PARAM));

    // 通道参数
    AIParam.nSampChanCount = 8;
    for (nChannel = 0; nChannel < MainInfo.nAIChannelCount; nChannel++)
    {
        AIParam.CHParam[nChannel].bChannelEn = 1;
        AIParam.CHParam[nChannel].nSampleRange = ACTS3100_AI_SAMPRANGE_N10_P10V;
        AIParam.CHParam[nChannel].nRefGround = ACTS3100_AI_REFGND_RSE;
        AIParam.CHParam[nChannel].nReserved0 = 0;
        AIParam.CHParam[nChannel].nReserved1 = 0;
        AIParam.CHParam[nChannel].nReserved2 = 0;
    }
    AIParam.nSampleSignal = 0;	// ACTS3100_AI_SAMPSIGNAL_0V

    // 时钟参数
    AIParam.fSampleRate = 50000.0;
    AIParam.nSampleMode = ACTS3100_AI_SAMPMODE_CONTINUOUS;
    AIParam.nSampsPerChan = 1024;
    AIParam.nSampClkSource = ACTS3100_AIO_SAMPCLKSRC_LOCAL;
    AIParam.nClockOutput = ACTS3100_AIO_CLKOUT_DISABLE;
    AIParam.StartTrig.nSyncTSOut = ACTS3100_AIO_STSO_DISABLE;

    // 触发参数
    AIParam.StartTrig.nTriggerType = ACTS3100_AI_START_TRIGTYPE_NONE;
    AIParam.StartTrig.nTriggerSource = ACTS3100_AI_TRIG_SRC_FIRST;
    AIParam.StartTrig.nTriggerDir = ACTS3100_AI_TRIGDIR_FALLING;
    AIParam.StartTrig.fTriggerLevelTop = 1.0;
    AIParam.StartTrig.fTriggerLevelBtm = 0.0;
    AIParam.StartTrig.nTriggerSens = 0;
    AIParam.StartTrig.nDelaySamps = 0;
    AIParam.StartTrig.nReTrigger = 0;

    AIParam.PauseTrig.nTriggerType = ACTS3100_AI_START_TRIGTYPE_NONE;
    AIParam.PauseTrig.nTriggerSource = ACTS3100_AI_TRIG_SRC_FIRST;
    AIParam.PauseTrig.nTriggerDir = ACTS3100_AI_TRIGDIR_FALLING;
    AIParam.PauseTrig.fTriggerLevelTop = 1.0;
    AIParam.PauseTrig.fTriggerLevelBtm = 0.0;
    AIParam.PauseTrig.nTriggerSens = 0;


    // 其他参数
    AIParam.nReserved1 = 0;
    AIParam.nReserved2 = 0;
    AIParam.nReserved3 = 0;

    if (!ACTS3100_AI_VerifyParam(hDevice, &AIParam))
    {
        printf("Wrong parameter, it has been adjusted to legal value，Please check the log file acts3100.log and press any key to continue...\n");
        getc(stdin);
    }

    // 第二步 初始化AI采集任务
    if (!ACTS3100_AI_InitTask(hDevice, &AIParam))
    {
        printf("AI_InitTask Error,Please refer to log file\n");
        getc(stdin);
        ACTS3100_DEV_Release(hDevice);
        return 1;
    }

    // 第三步 开始AI采集任务
    if (!ACTS3100_AI_StartTask(hDevice))
    {
        printf("AI_StartTask Error\n");
        getc(stdin);
    }

    // 第四步 发送软件触发事件(硬件外触发时不需要)
    if (!ACTS3100_AI_SendSoftTrig(hDevice))
    {
        printf("AI_SendSoftTrig Error\n");
        getc(stdin);
    }
    
    // Create a named pipe
    // get the file absolute path and create a named pipe in the same directory
    char *pipeName = "acts3100.pipe";
    mkfifo(pipeName, 0666);

    // Open the pipe for writing
    int pipe_fd = open(pipeName, O_WRONLY);
    if (pipe_fd == -1)
    {
        printf("Error opening pipe\n");
        return 1;
    }

    printf("Wait...\n");
    // 第五步 循环读取AI数据
    // while (!kbhit())
    while (1)
    {
        if (!ACTS3100_AI_ReadAnalog(hDevice, fVoltArray, nReadSampsPerChan, &nSampsPerChanRead, &nReadableSamps, fTimeout))
        {
            printf("Timeout nSampsPerChanRead=%d\n", nSampsPerChanRead);
            getc(stdin);
        }

        if (nSampsPerChanRead <= 0)
        {
            continue;
        }

        //printf(".\n");
        // printf("nSampsPerChanRead=%d\n", nSampsPerChanRead);

        // Write the data to the pipe 
        write(pipe_fd, fVoltArray, nSampsPerChanRead * sizeof(F64) * AIParam.nSampChanCount);
        printf("write %d samples\n", nSampsPerChanRead);

        // if (kbhit()) goto Exit;

    }

Exit:
    printf("\nPress any key to quit...\n");
    getc(stdin);

    // 第六步 停止AI采集任务
    if (!ACTS3100_AI_StopTask(hDevice))
    {
        printf("AI_StopTask Error\n");
        getc(stdin);
    }

    // 第七步 释放AI采集任务
    if (!ACTS3100_AI_ReleaseTask(hDevice))
    {
        printf("AI_ReleaseTask Error\n");
        getc(stdin);
    }

    // 第八步 释放设备对象
    if (!ACTS3100_DEV_Release(hDevice))
    {
        printf("DEV_Release Error\n");
        getc(stdin);
    }

    // Close the pipe 
    close(pipe_fd);

    return 0;
}


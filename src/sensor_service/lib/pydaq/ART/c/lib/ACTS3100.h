#ifndef _ACTS3100_DEVICE_
#define _ACTS3100_DEVICE_

#ifndef _ART_LINUX_DEF
#define _ART_LINUX_DEF
#include <stdint.h>
typedef uint8_t     UINT8;
typedef uint16_t    UINT16;
typedef uint32_t    UINT32;
typedef uint64_t    UINT64;
typedef int8_t      INT8;
typedef int16_t     INT16;
typedef int32_t     INT32;
typedef int64_t     INT64;

typedef int8_t		I8;		// 8位有符号整型数据
typedef uint8_t		U8;		// 8位无符号整型数据
typedef int16_t		I16;	// 16位有符号整型数据
typedef uint16_t	U16;	// 16位无符号整型数据
typedef int32_t		I32;	// 32位有符号整型数据
typedef uint32_t	U32;	// 32位无符号整型数据
typedef int64_t		I64;	// 64位有符号整型数据
typedef uint64_t	U64;	// 64位无符号整型数据
typedef float		F32;	// 32位浮点数据(单精度,同为labVIEW中的SGL)
typedef double		F64;	// 64位浮点数据(双精度,同为labVIEW中的DBL)

typedef void*       HANDLE;
typedef int         BOOL;
typedef void*       PVOID;
typedef INT32 LONG;
typedef INT32* PLONG;
typedef UINT32* PULONG;
typedef INT32 BOOL;
typedef UINT32 ULONG;
typedef UINT8 BYTE;
typedef UINT8* PBYTE;
typedef UINT8 UCHAR;
typedef UINT8* PUCHAR;
typedef UINT16 WORD;
typedef UINT16 USHORT;
typedef UINT32 UINT;
typedef UINT32 DWORD;
#endif  // _ART_LINUX_DEF

#define TRUE 1
#define FALSE 0


// ########################## 设备功能指标 ########################
#define ACTS3100_AI_MAX_CHANNELS		64	// 本程序最多支持64路模拟量单端输入通道
#define ACTS3100_AO_MAX_CHANNELS		4	// 本程序最多支持4个模拟量输出通道
#define ACTS3100_CTR_MAX_CHANNELS		2	// 本程序最多支持2个计数器
#define ACTS3100_DIO_MAX_PORTS			4	// 本程序最多支持4个数字量端口
#define ACTS3100_DIO_PORT0_MAX_LINES	32	// 数字量端口0最多支持32条线输入\输出,方向可控,Port0只能为DIO
#define ACTS3100_DIO_PORT1_MAX_LINES	8	// 数字量端口1支持8条线输入\输出,方向可控,PFI0~7
#define ACTS3100_DIO_PORT2_MAX_LINES	8	// 数字量端口2支持8条线输入\输出,方向可控,PFI8~15
#define ACTS3100_DIO_PORT3_MAX_LINES	8	// 数字量端口3支持8条线输入\输出,方向可控,PFI16~24/PXI0~PXI7

#define ACTS3100_AI_DATA_WIDTH			4	// AI采样数据宽度(字节数)16位以上精度为2
#define ACTS3100_AO_DATA_WIDTH			2	// AO采样数据宽度(字节数)
#define ACTS3100_DI_DATA_WIDTH			4	// DI采样数据宽度(字节数)8线为1,16线为2,32线为4
#define ACTS3100_DO_DATA_WIDTH			4	// DO采样数据宽度(字节数)8线为1,16线为2,32线为4
#define ACTS3100_CI_DATA_WIDTH			4	// CI采样数据宽度(字节数)
#define ACTS3100_CO_DATA_WIDTH			8	// CO采样数据宽度(字节数)

#define ACTS3100_AI_MAX_RANGES			4	// AI采样范围档位数

// 共用常量
#if 1
// #################### 主要信息结构体(ACTS3100_MAIN_INFO) #######################
typedef struct _ACTS3100_MAIN_INFO
{
	U32 nDeviceType;			// 总线类型\设备类型0x20125620 20115620...2012(PXIE)2011(PCIE)
	U32 nAIChannelCount;		// AI通道数量

	U32 nAISampRangeCount;		// AI采样范围挡位数量
	U32 nAISampRangeVal[9];		// AI各采样范围对应档位值

	U32 nAISampSignalCount;		// AI采样信号数量
	U32 nAISampSignalVal[17];	// AI各采样信号对应值

	U32 nAIOSampClockCount;		// AI AO采样时钟信号数量
	U32 nAIOSampClockVal[33];	// AI AO采样时钟信号对应值

	U32 nAIOClockOutputCount;	// AI AO时钟输出选项数量
	U32 nAIOClockOutputVal[33];	// AI AO时钟输出输入对应值

	U32 nAIOSyncTSOutCount;		// AI AO 开始触发源 同步发信号输出数量
	U32 nAIOSyncTSOutVal[33];	// AI AO 开始触发源 同步信号输出对应值

	U32 nAITrigSrcCount;		// AI 开始触发源 暂停触发源选项数量
	U32 nAITrigSrcVal[33];		// AI 开始触发源 暂停触发源选项对应值

	U32 nAOTrigSrcCount;		// AO 开始触发源 暂停触发源选项数量
	U32 nAOTrigSrcVal[33];		// AO 开始触发源 暂停触发源选项对应值

	U32 nDIOCTRClkTrigCount;	// DI DO CTR 采样时钟、开始触发源、暂停触发源、计数复位信号源 选项数量
	U32 nDIOCTRClkTrigVal[33];	// DI DO CTR 采样时钟、开始触发源、暂停触发源、计数复位信号源 选项对应值

	U32 nCTRTerminalCount;		// 脉冲测量、脉冲输出 类型为时钟滴答时 选项数量
	U32 nCTRTerminalVal[33];	// 脉冲测量、脉冲输出 类型为时钟滴答时 选项对应值

	U32 nAISampGainCount;		// AI采样增益挡位数量(保留)
	U32 nAICouplingCount;		// AI耦合挡位数量

	U32 nAIImpedanceCount;		// AI阻抗的挡位数量
	U32 nAIDepthOfMemory;		// AI板载存储器深度(点数)

	U32	nAICodeType;			// AI码值类型(如=0表示原码; =1表示补码)
	U32 nAISampResolution;		// AI采样分辨率(如=8表示8Bit; =12表示12Bit; =14表示14Bit; =16表示16Bit)

	U32 nAISampCodeCount;		// AI采样编码数量(如256, 4096, 16384, 65536)
	U32 nAISupportAPFI0;		// AI是否支持APFI0,范围±10V,AI和AO共用APFI，同一时刻只能有一个功能使用同一APFI

	U32 nAISupportAPFI1;		// AI是否支持APFI1,范围±10V,,AI和AO共用APFI，同一时刻只能有一个功能使用同一APFI
	U32 nAITrigLvlResolution;	// AI触发电平分辨率(如=8表示8Bit; =12表示12Bit; =16表示16Bit)

	U32 nAITrigLvlCodeCount;	// AI触发电平编码数量(如256, 4096)
	U32 nAIBaseRate;			// AI基准频率Hz

	U32 nAIMaxRate;				// AI最大频率Hz

	U32 nReserved0;				// 保留字段(暂未定义)
	U32 nReserved1;				// 保留字段(暂未定义)
	U32 nReserved2;				// 保留字段(暂未定义)
	U32 nReserved3;				// 保留字段(暂未定义)

	U32 nAOChannelCount;		// AO通道数量
	U32 nAOSampRangeCount;		// AO采样范围挡位数量
	U32 nAOSampRangeVal[8];		// AO各采样范围对应档位值
	U32 nAOSampGainCount;		// AO增益挡位数量
	U32 nAOCouplingCount;		// AO耦合挡位数量
	U32 nAOImpedanceCount;		// AO阻抗的挡位数量
	U32 nAODepthOfMemory;		// AO板载存储器深度(点数)
	U32 nAOSampResolution;		// AO采样分辨率(如=8表示8Bit; =12表示12Bit; =14表示14Bit; =16表示16Bit)
	U32 nAOSampCodeCount;		// AO采样编码数量(如256, 4096, 16384, 65536)
	U32 nAOSupportAPFI0;		// AO是否支持APFI0(ATR触发下的方式,AO只支持APFI触发,如果AO不支持APFI即不支持ATR触发)
	U32 nAOSupportAPFI1;		// AO是否支持APFI1,范围±10V,,AI和AO共用APFI，同一时刻只能有一个功能使用同一APFI
	U32 nAOTrigLvlResolution;	// AO触发电平分辨率(如=8表示8Bit; =12表示12Bit; =16表示16Bit)
	U32 nAOTrigLvlCodeCount;	// AO触发电平编码数量(如256, 4096)
	U32 nAOBaseRate;			// AO基准频率Hz
	U32 nAOGSingleMaxRate;		// AO组内单通道最大频率Hz(一般板卡如果有4通道,0 2为一组,1 3为一组)
	U32 nAOGMultiMaxRate;		// AO组内多通道最大频率Hz(一般板卡如果有2通道,0 1为一组)
								// 5731,4个通道为一组，单通道1M,2通道每通道700K,3通道每通道500k,4通道每通道350K

	U32 nReserved4;				// 保留字段(暂未定义)
	U32 nReserved5;				// 保留字段(暂未定义)
	U32 nReserved6;				// 保留字段(暂未定义)
	U32 nReserved7;				// 保留字段(暂未定义)

	U32 nCTRChannelCount;		// CTR通道数量
	U32 nReserved8;				// 保留字段(暂未定义)

	U32 nDIOPortCfg[ACTS3100_DIO_MAX_PORTS];			// DIO Port配置, 0:不支持 1:支持
	U32 nDIOPortLines[ACTS3100_DIO_MAX_PORTS];			// DIO 各端口线数
	U32	nCalibrationType;		// 校准类型(如=0数字校准; =1模拟校准)
	U32 nCalibrationResolution;	// 校准分辨率(如=8表示8Bit; =12表示12Bit; =16表示16Bit)

	U32 nReserved9;				// 保留字段(暂未定义)
	U32 nReserved10;			// 保留字段(暂未定义)
	U32 nReserved11;			// 保留字段(已使用)
	U32 nReserved12;			// 保留字段(暂未定义)
} ACTS3100_MAIN_INFO, * PACTS3100_MAIN_INFO;

// AI硬件参数结构体ACTS3100_AI_PARAM中的nSampClkSource时钟源所使用的选项
// AO硬件参数结构体ACTS3100_AO_PARAM中的nSampClkSource时钟源所使用的选项
#define ACTS3100_AIO_SAMPCLKSRC_LOCAL			 0 // 本地时钟(通常为本地晶振时钟OSCCLK),也叫内部时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI00			 1 // PFI00输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI01			 2 // PFI01输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI02			 3 // PFI02输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI03			 4 // PFI03输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI04			 5 // PFI04输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI05			 6 // PFI05输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI06			 7 // PFI06输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI07			 8 // PFI07输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI08			 9 // PFI08输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI09			10 // PFI09输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI10			11 // PFI10输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI11			12 // PFI11输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI12			13 // PFI12输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI13			14 // PFI13输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI14			15 // PFI14输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI15			16 // PFI15输入时钟
#define ACTS3100_AIO_SAMPCLKSRC_PFI16			17 // PFI16输入时钟(PXIE设备为PXI0)
#define ACTS3100_AIO_SAMPCLKSRC_PFI17			18 // PFI17输入时钟(PXIE设备为PXI1)
#define ACTS3100_AIO_SAMPCLKSRC_PFI18			19 // PFI18输入时钟(PXIE设备为PXI2)
#define ACTS3100_AIO_SAMPCLKSRC_PFI19			20 // PFI19输入时钟(PXIE设备为PXI3)
#define ACTS3100_AIO_SAMPCLKSRC_PFI20			21 // PFI20输入时钟(PXIE设备为PXI4)
#define ACTS3100_AIO_SAMPCLKSRC_PFI21			22 // PFI21输入时钟(PXIE设备为PXI5)
#define ACTS3100_AIO_SAMPCLKSRC_PFI22			23 // PFI22输入时钟(PXIE设备为PXI6)
#define ACTS3100_AIO_SAMPCLKSRC_PFI23			24 // PFI23输入时钟(PXIE设备为PXI7)
#define ACTS3100_AIO_SAMPCLKSRC_PXISTAR			25 // PXI_STAR输入时钟(仅PXIE设备支持)


// AI硬件参数结构体ACTS3100_AI_PARAM中的nClockOutput时钟输出所使用的选项
// AO硬件参数结构体ACTS3100_AO_PARAM中的nClockOutput时钟输出所使用的选项
#define ACTS3100_AIO_CLKOUT_DISABLE			 0 // 禁止输出
#define ACTS3100_AIO_CLKOUT_PFI00			 1 // PFI00输出时钟
#define ACTS3100_AIO_CLKOUT_PFI01			 2 // PFI01输出时钟
#define ACTS3100_AIO_CLKOUT_PFI02			 3 // PFI02输出时钟
#define ACTS3100_AIO_CLKOUT_PFI03			 4 // PFI03输出时钟
#define ACTS3100_AIO_CLKOUT_PFI04			 5 // PFI04输出时钟
#define ACTS3100_AIO_CLKOUT_PFI05			 6 // PFI05输出时钟
#define ACTS3100_AIO_CLKOUT_PFI06			 7 // PFI06输出时钟
#define ACTS3100_AIO_CLKOUT_PFI07			 8 // PFI07输出时钟
#define ACTS3100_AIO_CLKOUT_PFI08			 9 // PFI08输出时钟
#define ACTS3100_AIO_CLKOUT_PFI09			10 // PFI09输出时钟
#define ACTS3100_AIO_CLKOUT_PFI10			11 // PFI10输出时钟
#define ACTS3100_AIO_CLKOUT_PFI11			12 // PFI11输出时钟
#define ACTS3100_AIO_CLKOUT_PFI12			13 // PFI12输出时钟
#define ACTS3100_AIO_CLKOUT_PFI13			14 // PFI13输出时钟
#define ACTS3100_AIO_CLKOUT_PFI14			15 // PFI14输出时钟
#define ACTS3100_AIO_CLKOUT_PFI15			16 // PFI15输出时钟
#define ACTS3100_AIO_CLKOUT_PFI16			17 // PFI16输出时钟(PXIE设备为PXI0)
#define ACTS3100_AIO_CLKOUT_PFI17			18 // PFI17输出时钟(PXIE设备为PXI1)
#define ACTS3100_AIO_CLKOUT_PFI18			19 // PFI18输出时钟(PXIE设备为PXI2)
#define ACTS3100_AIO_CLKOUT_PFI19			20 // PFI19输出时钟(PXIE设备为PXI3)
#define ACTS3100_AIO_CLKOUT_PFI20			21 // PFI20输出时钟(PXIE设备为PXI4)
#define ACTS3100_AIO_CLKOUT_PFI21			22 // PFI21输出时钟(PXIE设备为PXI5)
#define ACTS3100_AIO_CLKOUT_PFI22			23 // PFI22输出时钟(PXIE设备为PXI6)
#define ACTS3100_AIO_CLKOUT_PFI23			24 // PFI23输出时钟(PXIE设备为PXI7)


// AI硬件参数结构体ACTS3100_AI_START_TRIG中的nSyncTSOut开始触发 同步信号输出通道所使用的选项
// AO硬件参数结构体ACTS3100_AO_START_TRIG中的nSyncTSOut开始触发 同步信号输出通道所使用的选项
#define ACTS3100_AIO_STSO_DISABLE		 0 // 禁止同步触发信号
#define ACTS3100_AIO_STSO_PFI00			 1 // PFI00输出同步触发信号
#define ACTS3100_AIO_STSO_PFI01			 2 // PFI01输出同步触发信号
#define ACTS3100_AIO_STSO_PFI02			 3 // PFI02输出同步触发信号
#define ACTS3100_AIO_STSO_PFI03			 4 // PFI03输出同步触发信号
#define ACTS3100_AIO_STSO_PFI04			 5 // PFI04输出同步触发信号
#define ACTS3100_AIO_STSO_PFI05			 6 // PFI05输出同步触发信号
#define ACTS3100_AIO_STSO_PFI06			 7 // PFI06输出同步触发信号
#define ACTS3100_AIO_STSO_PFI07			 8 // PFI07输出同步触发信号
#define ACTS3100_AIO_STSO_PFI08			 9 // PFI08输出同步触发信号
#define ACTS3100_AIO_STSO_PFI09			10 // PFI09输出同步触发信号
#define ACTS3100_AIO_STSO_PFI10			11 // PFI10输出同步触发信号
#define ACTS3100_AIO_STSO_PFI11			12 // PFI11输出同步触发信号
#define ACTS3100_AIO_STSO_PFI12			13 // PFI12输出同步触发信号
#define ACTS3100_AIO_STSO_PFI13			14 // PFI13输出同步触发信号
#define ACTS3100_AIO_STSO_PFI14			15 // PFI14输出同步触发信号
#define ACTS3100_AIO_STSO_PFI15			16 // PFI15输出同步触发信号
#define ACTS3100_AIO_STSO_PFI16			17 // PFI16输出同步触发信号(PXIE设备为PXI0)
#define ACTS3100_AIO_STSO_PFI17			18 // PFI17输出同步触发信号(PXIE设备为PXI1)
#define ACTS3100_AIO_STSO_PFI18			19 // PFI18输出同步触发信号(PXIE设备为PXI2)
#define ACTS3100_AIO_STSO_PFI19			20 // PFI19输出同步触发信号(PXIE设备为PXI3)
#define ACTS3100_AIO_STSO_PFI20			21 // PFI20输出同步触发信号(PXIE设备为PXI4)
#define ACTS3100_AIO_STSO_PFI21			22 // PFI21输出同步触发信号(PXIE设备为PXI5)
#define ACTS3100_AIO_STSO_PFI22			23 // PFI22输出同步触发信号(PXIE设备为PXI6)
#define ACTS3100_AIO_STSO_PFI23			24 // PFI23输出同步触发信号(PXIE设备为PXI7)

// AI硬件参数结构体 开始触发源、暂停触发源使用的选项
#define ACTS3100_AI_TRIG_SRC_FIRST			 0 // 选择AI首通道作为触发源(数字模式不可选)(暂停触发不可选)
#define ACTS3100_AI_TRIG_SRC_APFI0			 1 // 选择APFI0作为触发源(数字模式不可选)
#define ACTS3100_AI_TRIG_SRC_APFI1			 2 // 选择APFI1作为触发源(数字模式不可选)
#define ACTS3100_AI_TRIG_SRC_PFI00			 3 // PFI00触发
#define ACTS3100_AI_TRIG_SRC_PFI01			 4 // PFI01触发
#define ACTS3100_AI_TRIG_SRC_PFI02			 5 // PFI02触发
#define ACTS3100_AI_TRIG_SRC_PFI03			 6 // PFI03触发
#define ACTS3100_AI_TRIG_SRC_PFI04			 7 // PFI04触发
#define ACTS3100_AI_TRIG_SRC_PFI05			 8 // PFI05触发
#define ACTS3100_AI_TRIG_SRC_PFI06			 9 // PFI06触发
#define ACTS3100_AI_TRIG_SRC_PFI07			10 // PFI07触发
#define ACTS3100_AI_TRIG_SRC_PFI08			11 // PFI08触发
#define ACTS3100_AI_TRIG_SRC_PFI09			12 // PFI09触发
#define ACTS3100_AI_TRIG_SRC_PFI10			13 // PFI10触发
#define ACTS3100_AI_TRIG_SRC_PFI11			14 // PFI11触发
#define ACTS3100_AI_TRIG_SRC_PFI12			15 // PFI12触发
#define ACTS3100_AI_TRIG_SRC_PFI13			16 // PFI13触发
#define ACTS3100_AI_TRIG_SRC_PFI14			17 // PFI14触发
#define ACTS3100_AI_TRIG_SRC_PFI15			18 // PFI15触发
#define ACTS3100_AI_TRIG_SRC_PFI16			19 // PFI16触发(PXIE设备为PXI0)
#define ACTS3100_AI_TRIG_SRC_PFI17			20 // PFI17触发(PXIE设备为PXI1)
#define ACTS3100_AI_TRIG_SRC_PFI18			21 // PFI18触发(PXIE设备为PXI2)
#define ACTS3100_AI_TRIG_SRC_PFI19			22 // PFI19触发(PXIE设备为PXI3)
#define ACTS3100_AI_TRIG_SRC_PFI20			23 // PFI20触发(PXIE设备为PXI4)
#define ACTS3100_AI_TRIG_SRC_PFI21			24 // PFI21触发(PXIE设备为PXI5)
#define ACTS3100_AI_TRIG_SRC_PFI22			25 // PFI22触发(PXIE设备为PXI6)
#define ACTS3100_AI_TRIG_SRC_PFI23			26 // PFI23触发(PXIE设备为PXI7)
#define ACTS3100_AI_TRIG_SRC_PXISTAR		27 // PXI_STAR触发(仅PXIE设备支持)

// AO硬件参数结构体 开始触发源、暂停触发源使用的选项
#define ACTS3100_AO_TRIG_SRC_APFI0			 0 // 选择APFI0作为触发源(数字模式不可选)
#define ACTS3100_AO_TRIG_SRC_APFI1			 1 // 选择APFI1作为触发源(数字模式不可选)
#define ACTS3100_AO_TRIG_SRC_PFI00			 2 // PFI00触发
#define ACTS3100_AO_TRIG_SRC_PFI01			 3 // PFI01触发
#define ACTS3100_AO_TRIG_SRC_PFI02			 4 // PFI02触发
#define ACTS3100_AO_TRIG_SRC_PFI03			 5 // PFI03触发
#define ACTS3100_AO_TRIG_SRC_PFI04			 6 // PFI04触发
#define ACTS3100_AO_TRIG_SRC_PFI05			 7 // PFI05触发
#define ACTS3100_AO_TRIG_SRC_PFI06			 8 // PFI06触发
#define ACTS3100_AO_TRIG_SRC_PFI07			 9 // PFI07触发
#define ACTS3100_AO_TRIG_SRC_PFI08			10 // PFI08触发
#define ACTS3100_AO_TRIG_SRC_PFI09			11 // PFI09触发
#define ACTS3100_AO_TRIG_SRC_PFI10			12 // PFI10触发
#define ACTS3100_AO_TRIG_SRC_PFI11			13 // PFI11触发
#define ACTS3100_AO_TRIG_SRC_PFI12			14 // PFI12触发
#define ACTS3100_AO_TRIG_SRC_PFI13			15 // PFI13触发
#define ACTS3100_AO_TRIG_SRC_PFI14			16 // PFI14触发
#define ACTS3100_AO_TRIG_SRC_PFI15			17 // PFI15触发
#define ACTS3100_AO_TRIG_SRC_PFI16			18 // PFI16触发(PXIE设备为PXI0)
#define ACTS3100_AO_TRIG_SRC_PFI17			19 // PFI17触发(PXIE设备为PXI1)
#define ACTS3100_AO_TRIG_SRC_PFI18			20 // PFI18触发(PXIE设备为PXI2)
#define ACTS3100_AO_TRIG_SRC_PFI19			21 // PFI19触发(PXIE设备为PXI3)
#define ACTS3100_AO_TRIG_SRC_PFI20			22 // PFI20触发(PXIE设备为PXI4)
#define ACTS3100_AO_TRIG_SRC_PFI21			23 // PFI21触发(PXIE设备为PXI5)
#define ACTS3100_AO_TRIG_SRC_PFI22			24 // PFI22触发(PXIE设备为PXI6)
#define ACTS3100_AO_TRIG_SRC_PFI23			25 // PFI23触发(PXIE设备为PXI7)
#define ACTS3100_AO_TRIG_SRC_PXISTAR		26 // PXI_STAR触发(仅PXIE设备支持)

// DI DO CTR 采样时钟、开始触发源、暂停触发源、计数复位信号源使用的选项
#define ACTS3100_DI_DO_CTR_CLK_TRIG_NONE	 0 // 无选择(DI DO采样时钟下为 内时钟)
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI00	 1 // 选择PFI00
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI01	 2 // 选择PFI01	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI02	 3 // 选择PFI02	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI03	 4 // 选择PFI03	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI04	 5 // 选择PFI04	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI05	 6 // 选择PFI05	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI06	 7 // 选择PFI06	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI07	 8 // 选择PFI07	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI08	 9 // 选择PFI08
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI09	 10 // 选择PFI09	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI10	 11 // 选择PFI10	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI11	 12 // 选择PFI11	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI12	 13 // 选择PFI12	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI13	 14 // 选择PFI13	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI14	 15 // 选择PFI14	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI15	 16 // 选择PFI15	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI16	 17 // 选择PFI16(PXIE设备为PXI0)
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI17	 18 // 选择PFI17(PXIE设备为PXI1)	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI18	 19 // 选择PFI18(PXIE设备为PXI2)	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI19	 20 // 选择PFI19(PXIE设备为PXI3)	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI20	 21 // 选择PFI20(PXIE设备为PXI4)	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI21	 22 // 选择PFI21(PXIE设备为PXI5)	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI22	 23 // 选择PFI22(PXIE设备为PXI6)	
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PFI23	 24 // 选择PFI23(PXIE设备为PXI7)
#define ACTS3100_DI_DO_CTR_CLK_TRIG_PXISTAR	 25 // 选择PXI_STAR(仅PXIE设备支持)

// 脉冲测量、脉冲输出 类型为时钟滴答时使用的选项
// 函数CI_CreatePulseChanTicks()/CO_CreatePulseChanTicks()中的nSourceTerminal源接线端所使用时钟基准选项
#define ACTS3100_CTR_TIMEBASE_100MHz		0 // 内部100MHz时钟基准
#define ACTS3100_CTR_TIMEBASE_20MHz			1 // 内部20MHz时钟基准
#define ACTS3100_CTR_TIMEBASE_10MHz			2 // 内部10MHz时钟基准
#define ACTS3100_CTR_TIMEBASE_100KHz		3 // 内部100KHz时钟基准
#define ACTS3100_CTR_TIMEBASE_PFI00			4 // 从PFI0输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI01			5 // 从PFI1输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI02			6 // 从PFI2输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI03			7 // 从PFI3输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI04			8 // 从PFI4输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI05			9 // 从PFI5输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI06			10 // 从PFI6输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI07			11 // 从PFI7输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI08			12 // 从PFI8输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI09			13 // 从PFI9输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI10			14 // 从PFI10输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI11			15 // 从PFI11输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI12			16 // 从PFI12输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI13			17 // 从PFI13输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI14			18 // 从PFI14输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI15			19 // 从PFI15输入外部时基
#define ACTS3100_CTR_TIMEBASE_PFI16			20 // 从PFI16输入外部时基(PXIE设备为PXI0)
#define ACTS3100_CTR_TIMEBASE_PFI17			21 // 从PFI17输入外部时基(PXIE设备为PXI1)
#define ACTS3100_CTR_TIMEBASE_PFI18			22 // 从PFI18输入外部时基(PXIE设备为PXI2)
#define ACTS3100_CTR_TIMEBASE_PFI19			23 // 从PFI19输入外部时基(PXIE设备为PXI3)
#define ACTS3100_CTR_TIMEBASE_PFI20			24 // 从PFI20输入外部时基(PXIE设备为PXI4)
#define ACTS3100_CTR_TIMEBASE_PFI21			25 // 从PFI21输入外部时基(PXIE设备为PXI5)
#define ACTS3100_CTR_TIMEBASE_PFI22			26 // 从PFI22输入外部时基(PXIE设备为PXI6)
#define ACTS3100_CTR_TIMEBASE_PFI23			27 // 从PFI23输入外部时基(PXIE设备为PXI7)
#define ACTS3100_CTR_TIMEBASE_PXISTAR		28 // 从PXI_STAR输入外部时基(仅PXIE设备支持)

#endif
// AI
#if 1
// ############# AI工作参数结构体ACTS3100_AI_PARAM描述 #############
typedef struct _ACTS3100_AI_CH_PARAM // AI通道参数结构体
{
	U32 bChannelEn;			// 通道使能,1:使能 0:不使能
	U32 nSampleRange;		// 采样范围(Sample Range)档位选择, 具体见下面常量名定义(此参数在单点采样有效,未此注明的参数则在单点采样模式中无效)

	U32 nRefGround;			// 地参考方式

	U32 nReserved0;			// 保留(未用)
	U32 nReserved1;			// 保留(未用)
	U32 nReserved2;			// 保留(未用)
} ACTS3100_AI_CH_PARAM, * PACTS3100_AI_CH_PARAM;

// AI硬件参数结构体ACTS3100_AI_CH_PARAM中的nSampleRange参数所使用的采样范围挡位选项
#define ACTS3100_AI_SAMPRANGE_N10_P10V			0 // ±10V
#define ACTS3100_AI_SAMPRANGE_N5_P5V			1 // ±5V
#define ACTS3100_AI_SAMPRANGE_N2_P2V			2 // ±2V
#define ACTS3100_AI_SAMPRANGE_N1_P1V			3 // ±1V

// AI硬件通道参数结构体ACTS3100_AI_CH_PARAM中的nRefGround参数所使用的地参考选项
#define ACTS3100_AI_REFGND_RSE			0 // 接地参考单端(Referenced Single Endpoint)(保留)
#define ACTS3100_AI_REFGND_DIFF			1 // 差分(Differential)

typedef struct _ACTS3100_AI_START_TRIG // 开始触发参数
{
	U32 nTriggerType;		// 触发类型
	U32 nTriggerSource;		// 触发源, 详见(AI硬件参数结构体 开始触发源、暂停触发源使用的选项)
	U32 nTriggerDir;	    // 触发方向(Trigger Direction)
	F32 fTriggerLevelTop;	// 触发窗顶部(边沿触发电平)
	F32 fTriggerLevelBtm;	// 触发窗底部
	U32 nTriggerSens;		// 触发灵敏度(Trigger Sensitive for Digital and Analog trigger),单位：微秒(uS)，取值范围[0, 1638]
	U32 nDelaySamps;		// 触发延迟点数, 单位：采样点，取值范围32位有效[0, 4294967295]，0:Post Trigger, >0:Delay Trigger
	U32 nReTrigger;			// 重触发使能, 1:使能
	U32 nSyncTSOut;			// 同步触发信号输出通道选择, 详见下面常量定义
	U32 nReserved0;			// 保留字段(暂未定义)
	U32 nReserved1;			// 保留字段(暂未定义)
	U32 nReserved2;			// 保留字段(暂未定义)
} ACTS3100_AI_START_TRIG, * PACTS3100_AI_START_TRIG;

typedef struct _ACTS3100_AI_PAUSE_TRIG // 暂停触发参数
{
	U32 nTriggerType;		// 触发类型
	U32 nTriggerSource;		// 触发源, 详见(AI硬件参数结构体 开始触发源、暂停触发源使用的选项)
	U32 nTriggerDir;	    // 触发方向(Trigger Direction)
	F32 fTriggerLevelTop;	// 触发窗顶部(边沿触发电平)
	F32 fTriggerLevelBtm;	// 触发窗底部
	U32 nTriggerSens;		// 触发灵敏度(Trigger Sensitive for Digital and Analog trigger),单位：微秒(uS)，取值范围[0, 1638]
	U32 nReserved0;			// 保留字段(暂未定义)
	U32 nReserved1;			// 保留字段(暂未定义)
} ACTS3100_AI_PAUSE_TRIG, * PACTS3100_AI_PAUSE_TRIG;

// AI开始触发参数结构体ACTS3100_AI_START_TRIG中的nTriggerType触发类型所使用的选项
#define ACTS3100_AI_START_TRIGTYPE_NONE				0 // 无触发(等同于软件强制触发)
#define ACTS3100_AI_START_TRIGTYPE_ANALOG_EDGE		1 // 模拟边沿触发类型
#define ACTS3100_AI_START_TRIGTYPE_ANALOG_WIN		2 // 模拟窗触发类型
#define ACTS3100_AI_START_TRIGTYPE_DIGIT_EDGE		3 // 数字边沿触发类型
#define ACTS3100_AI_START_TRIGTYPE_DIGIT_PATTERN	4 // 数字模式触发类型(保留,未提供)

// AI开始触发参数结构体ACTS3100_AI_PAUSE_TRIG中的nTriggerType触发类型所使用的选项
#define ACTS3100_AI_PAUSE_TRIGTYPE_NONE				0 // 无触发(禁用暂停触发)
#define ACTS3100_AI_PAUSE_TRIGTYPE_ANALOG_LVL		1 // 模拟电平发类型
#define ACTS3100_AI_PAUSE_TRIGTYPE_ANALOG_WIN		2 // 模拟窗触发类型
#define ACTS3100_AI_PAUSE_TRIGTYPE_DIGIT_LVL		3 // 数字电平触发类型
#define ACTS3100_AI_PAUSE_TRIGTYPE_DIGIT_PATTERN	4 // 数字模式触发类型(保留,未提供)

// AI开始触发参数结构体ACTS3100_AI_START_TRIG中的nTriggerDir触发方向所使用的选项
// AI暂停触发参数结构体ACTS3100_AI_PAUSE_TRIG中的nTriggerDir触发方向所使用的选项
// 当为模拟边沿触发(nTriggerType = TRIGTYPE_ANALOG_EDGE):
// 当为数字边沿触发(nTriggerType = TRIGTYPE_DIGIT_EDGE):
#define ACTS3100_AI_TRIGDIR_FALLING			0 // 下降沿/低电平
#define ACTS3100_AI_TRIGDIR_RISING			1 // 上升沿/高电平
#define ACTS3100_AI_TRIGDIR_CHANGING		2 // 变化(即上下边沿/高低电平均有效)(暂停触发下无此项)

// 当开始触发的类型为模拟窗触发(即nTriggerType = TRIGTYPE_ANALOG_WIN)时其nTriggerDir触发方向所用的选项
#define ACTS3100_AI_TRIGDIR_EnteringWin		0 // 入窗
#define ACTS3100_AI_TRIGDIR_LeavingWin		1 // 出窗
#define ACTS3100_AI_TRIGDIR_LeavingEnterWin	2 // 变化(出入窗均有效)

// 当暂停触发的类型为模拟窗触发(nTriggerType = TRIGTYPE_ANALOG_WIN)时其nTriggerDir触发方向所用的选项
#define ACTS3100_AI_TRIGDIR_InsideWin		0 // 窗内
#define ACTS3100_AI_TRIGDIR_OutsideWin		1 // 窗外

typedef struct _ACTS3100_AI_PARAM // 跟整个AI有关的硬件工作参数(简称AI工作参数)
{
	// 通道参数
	ACTS3100_AI_CH_PARAM CHParam[ACTS3100_AI_MAX_CHANNELS]; // 通道参数配置(此参数在单点采样有效,未此注明的参数则在单点采样模式中无效)
	U32 nSampChanCount;     // 采样通道总数[1, 64](此参数在单点采样有效,未此注明的参数则在单点采样模式中无效)
	U32 nSampleSignal;		// 采样信号(Sample Signal), 详见下面常量定义

	// 时钟参数
	U32 nSampleMode;		// 采样模式, 0=单点采样(按需), 2=有限点采样, 3=连续采样
	U32 nSampsPerChan;		// 每个通道采样点数(也是每通道待读取点数),取值范围为单点采样模式时应等于1,有限点或连续采样时为[2, n]	
	F64 fSampleRate;		// 采样速率(Sample Rate), 单位为sps,取值范围为[1000sps, 500000sps],它是每个采样通道的采样速率, 它与nChannelCount的乘积不能大于最大AI采样率
	U32 nSampClkSource;		// 采样时钟信号选择, 详见下面常量定义
	U32 nExtSampClkEdge;	// 外部采样时钟边沿, 0=下降沿, 1=上升沿(仅当nSampClkSource非内时钟源时有效)
	U32 nClockOutput;		// 采样时钟输出选择, 详见下面常量定义
	U32 nReserved0;			// 保留字段(暂未定义)

	ACTS3100_AI_START_TRIG StartTrig; // 开始触发参数
	ACTS3100_AI_PAUSE_TRIG PauseTrig; // 暂停触发参数

	// 其他方面	
	U32 nReserved1;			// 保留字段(暂未定义)
	U32 nReserved2;			// 保留字段(暂未定义)
	U32 nReserved3;			// 保留字段(暂未定义)
	U32 nReserved4;			// 保留字段(暂未定义)
} ACTS3100_AI_PARAM, * PACTS3100_AI_PARAM;

// AI硬件参数结构体ACTS3100_AI_PARAM中的nSampleSignal采样信号所使用的选项
#define ACTS3100_AI_SAMPSIGNAL_AI			0 // AI通道输入信号
#define ACTS3100_AI_SAMPSIGNAL_0V			1 // 0V(AGND)
#define ACTS3100_AI_SAMPSIGNAL_1V			2 // 1V(DC)
#define ACTS3100_AI_SAMPSIGNAL_2D5V			3 // 2.5V(DC)
#define ACTS3100_AI_SAMPSIGNAL_4V			4 // 4V(DC)
#define ACTS3100_AI_SAMPSIGNAL_5V			5 // 5V(DC)
#define ACTS3100_AI_SAMPSIGNAL_AO0			6 // AO0(DC)
#define ACTS3100_AI_SAMPSIGNAL_AO1			7 // AO1(DC)
#define ACTS3100_AI_SAMPSIGNAL_AO2			8 // AO2(DC)
#define ACTS3100_AI_SAMPSIGNAL_AO3			9 // AO3(DC)

// AI硬件参数结构体ACTS3100_AI_PARAM中的nSampleMode采样模式所使用的选项
#define ACTS3100_AI_SAMPMODE_ONE_DEMAND		0 // 软件按需单点采样
#define ACTS3100_AI_SAMPMODE_FINITE			2 // 有限点采样
#define ACTS3100_AI_SAMPMODE_CONTINUOUS		3 // 连续采样

// AI硬件参数结构体ACTS3100_AI_PARAM中的nExtSampClkEdge外部采样时钟边沿所使用的选项
#define ACTS3100_AI_EXTSAMPCLK_EDGE_FALLING		0 // 下降沿
#define ACTS3100_AI_EXTSAMPCLK_EDGE_RISING		1 // 上升沿

// #################### AI工作状态结构体ACTS3100_AI_STATUS描述 #####################
typedef struct _ACTS3100_AI_STATUS
{
	U32 bTaskDone;				// 采集任务完成标志, =TRUE:表示采集任务完成, =FALSE:表示采集任务未完成,正在进行中
	U32 bTriggered;				// 触发标志, =TRUE:表示已被触发, =FALSE:表示未被触发(即正等待触发)

	U32 nTaskState;				// 采集任务状态, =1:正常, 其它值表示有异常情况
	U32 nAvailSampsPerChan;		// 每通道有效点数,只有它大于当前指定读数长度时才能调用AI_ReadAnalog()立即读取指定长度的采样数据
	U32 nMaxAvailSampsPerChan;	// 自AI_StartTask()后每通道出现过的最大有效点数,状态值范围[0, nBufSampsPerChan],它是为监测采集软件性能而提供,如果此值越趋近于1,则表示意味着性能越高,越不易出现溢出丢点的可能
	U32 nBufSampsPerChan;		// 每通道缓冲区大小(采样点数)
	I64 nSampsPerChanAcquired;	// 每通道已采样点数(自开始AI_StartTask()之后所采样的点数),这个只是给用户的统计数据

	U32 nHardOverflowCnt;		// 硬件溢出计数(在不溢出情况下恒等于0)
	U32 nSoftOverflowCnt;		// 软件溢出计数(在不溢出情况下恒等于0)
	U32 nInitTaskCnt;			// 初始化采集任务的次数(即调用AI_InitTask()的次数)
	U32 nReleaseTaskCnt;		// 释放采集任务的次数(即调用AI_ReleaseTask()的次数)
	U32 nStartTaskCnt;			// 开始采集任务的次数(即调用AI_StartTask()的次数)
	U32 nStopTaskCnt;			// 停止采集任务的次数(即调用AI_StopTask()的次数)
	U32 nTransRate;				// 传输速率, 即每秒每通道传输点数(sps),作为应用软件传输性能的监测信息

	U32 nReserved0;				// 保留字段(暂未定义)
	U32 nReserved1;				// 保留字段(暂未定义)
	U32 nReserved2;				// 保留字段(暂未定义)
} ACTS3100_AI_STATUS, * PACTS3100_AI_STATUS;


// #################### AI电压范围信息结构体(ACTS3100_AI_VOLT_RANGE_INFO) #######################
typedef struct _ACTS3100_AI_VOLT_RANGE_INFO
{
	U32 nSampleRange;		// 当前采样范围挡位号
	U32 nReserved0;			// 保留字段(暂未定义)
	F64 fMaxVolt;			// 采样范围的最大电压值,单位:伏(V)
	F64 fMinVolt;			// 采样范围的最小电压值,单位:伏(V)
	F64 fAmplitude;			// 采样范围幅度,单位:伏(V)
	F64 fHalfOfAmp;			// 采样范围幅度的二分之一,单位:伏(V)
	F64 fCodeWidth;			// 编码宽度,单位:伏(V), 即每个单位码值所分配的电压值
	F64 fOffsetVolt;		// 偏移电压,单位:伏(V),一般用于零偏校准
	F64 fOffsetCode;		// 偏移码值,一般用于零偏校准,它代表的电压值等价于fOffsetVolt
	F64 fNeadCode;			// 电压换算所需码值，双极性为-2048(12位精度),单级性为0
	char strDesc[16];		// 采样范围字符描述,如"±10V", "0-10V"等

	U32 nPolarity;			// 采样范围的极性(0=双极性BiPolar, 1=单极性UniPolar)
	U32 nCodeCount;			// 原码数量
	I32 nMaxCode;			// 原码最大值
	I32 nMinCode;	        // 原码最小值

	U32 nReserved1;			// 保留字段(暂未定义)
	U32 nReserved2;			// 保留字段(暂未定义)
	U32 nReserved3;			// 保留字段(暂未定义)
	U32 nReserved4;			// 保留字段(暂未定义)
} ACTS3100_AI_VOLT_RANGE_INFO, * PACTS3100_AI_VOLT_RANGE_INFO;

// 结构体AI_VOLT_RANGE_INFO的数据成员nPolarity所用的采样范围极性选项
#define ACTS3100_AI_POLAR_BIPOLAR	0 // 双极性
#define ACTS3100_AI_POLAR_UNIPOLAR	1 // 单极性


// #################### AI速率信息结构体(ACTS3100_AI_SAMP_RATE_INFO) #######################
typedef struct _ACTS3100_AI_SAMP_RATE_INFO
{
	F64 fMaxRate;		// 通道最大采样速率(sps)
	F64 fMinRate;		// 通道最小采样速率(sps)
	F64 fTimerBase;		// 时钟基准(即板载晶振频率)单位:Hz
	U32 nDivideMode;	// 分频模式,0=整数分频(INTDIV), 1=DDS分频(DDSDIV)
	U32 nRateType;		// 速率类型,指fMaxRate和fMinRate的类型, =0:表示为所有采样通道的总速率, =1:表示为每个采样通道的速率

	U32 nReserved0;		// 保留字段(暂未定义)
	U32 nReserved1;		// 保留字段(暂未定义)
} ACTS3100_AI_SAMP_RATE_INFO, * PACTS3100_AI_SAMP_RATE_INFO;
#endif
// AO
#if 1
typedef struct _ACTS3100_AO_START_TRIG // 开始触发参数
{
	U32 nTriggerType;		// 触发类型, 
	U32 nTriggerSource;		// 触发源, 详见(AO硬件参数结构体 开始触发源、暂停触发源使用的选项)
	U32 nTriggerDir;	    // 触发方向(Trigger Direction)
	F32 fTriggerLevelTop;	// 触发窗顶部（边沿触发电平）
	F32 fTriggerLevelBtm;	// 触发窗底部
	U32 nTriggerSens;		// 触发灵敏度(Trigger Sensitive for Digital and Analog trigger),单位：微秒(uS)，取值范围[0, 1638]
	U32 nDelaySamps;		// 触发延迟点数, 单位：采样点，取值范围32位有效[0, 4294967295]，0:Post Trigger, >0:Delay Trigger
	U32 nReTrigger;			// 重触发使能, 1:使能
	U32 nSyncTSOut;			// 同步触发信号输出通道选择, 详见下面常量定义

	U32 nReserved0;			// 保留字段(暂未定义)
	U32 nReserved1;			// 保留字段(暂未定义)
	U32 nReserved2;			// 保留字段(暂未定义)
} ACTS3100_AO_START_TRIG, * PACTS3100_AO_START_TRIG;

typedef struct _ACTS3100_AO_PAUSE_TRIG // 暂停触发参数
{
	U32 nTriggerType;		// 触发类型, 
	U32 nTriggerSource;		// 触发源, 详见(AO硬件参数结构体 开始触发源、暂停触发源使用的选项)
	U32 nTriggerDir;	    // 触发方向(Trigger Direction)
	F32 fTriggerLevelTop;	// 触发窗顶部（边沿触发电平）
	F32 fTriggerLevelBtm;	// 触发窗底部
	U32 nTriggerSens;		// 触发灵敏度(Trigger Sensitive for Digital and Analog trigger),单位：微秒(uS)，取值范围[0, 1638]
	U32 nReserved0;			// 保留字段(暂未定义)
	U32 nReserved1;			// 保留字段(暂未定义)
} ACTS3100_AO_PAUSE_TRIG, * PACTS3100_AO_PAUSE_TRIG;


// AO开始触发参数结构体ACTS3100_AO_START_TRIG中的nTriggerType触发类型所使用的选项
#define ACTS3100_AO_START_TRIGTYPE_NONE				0 // 无触发(等同于软件强制触发)
#define ACTS3100_AO_START_TRIGTYPE_ANALOG_EDGE		1 // 模拟边沿触发类型
#define ACTS3100_AO_START_TRIGTYPE_ANALOG_WIN		2 // 模拟窗触发类型(保留,未提供)
#define ACTS3100_AO_START_TRIGTYPE_DIGIT_EDGE		3 // 数字边沿触发类型
#define ACTS3100_AO_START_TRIGTYPE_DIGIT_PATTERN	4 // 数字模式触发类型(保留,未提供)

// AO暂停触发参数结构体ACTS3100_AO_PAUSE_TRIG中的nTriggerType触发类型所使用的选项
#define ACTS3100_AO_PAUSE_TRIGTYPE_NONE				0 // 无触发(禁用暂停触发)
#define ACTS3100_AO_PAUSE_TRIGTYPE_ANALOG_LVL		1 // 模拟电平发类型
#define ACTS3100_AO_PAUSE_TRIGTYPE_ANALOG_WIN		2 // 模拟窗触发类型(保留,未提供)
#define ACTS3100_AO_PAUSE_TRIGTYPE_DIGIT_LVL		3 // 数字电平触发类型
#define ACTS3100_AO_PAUSE_TRIGTYPE_DIGIT_PATTERN	4 // 数字模式触发类型(保留,未提供)

// AO开始触发参数结构体ACTS3100_AO_START_TRIG中的nTriggerDir触发方向所使用的选项
// AO暂停触发参数结构体ACTS3100_AO_PAUSE_TRIG中的nTriggerDir触发方向所使用的选项
// 当为模拟边沿触发(nTriggerType = TRIGTYPE_ANALOG_EDGE):
// 当为数字边沿触发(nTriggerType = TRIGTYPE_DIGIT_EDGE):
#define ACTS3100_AO_TRIGDIR_FALLING			0 // 下降沿/低电平
#define ACTS3100_AO_TRIGDIR_RISING			1 // 上升沿/高电平
#define ACTS3100_AO_TRIGDIR_CHANGING		2 // 变化(即上下边沿/高低电平均有效)(暂停触发下无此项)


// ##################### AO工作参数结构体ACTS3100_AO_PARAM描述 ###################
typedef struct _ACTS3100_AO_CH_PARAM // AI通道参数结构体
{
	U32 bChannelEn;			// 通道采样允许
	U32 nSampleRange;		// 采样范围,具体定义请参考下面常量定义
	// 此参数需传实际值,假如当前卡只有正负5V量程，此参数只能为ACTS3100_AO_SAMPRANGE_N5_P5V(1)
	// ACTS3100_MAIN_INFO中的返回值:nAOSampRangeCount=1， nAOSampRangeVal[0]=1;



	U32 nReserved0;			// 保留(未用)
	U32 nReserved1;			// 保留(未用)
	U32 nReserved2;			// 保留(未用)
	U32 nReserved3;			// 保留(未用)
} ACTS3100_AO_CH_PARAM, * PACTS3100_AO_CH_PARAM;

// AO硬件参数结构体ACTS3100_AO_CH_PARAM中的nSampleRange参数所使用的模拟量输入采样范围挡位选项
#define ACTS3100_AO_SAMPRANGE_N10_P10V			0 // ±10V
#define ACTS3100_AO_SAMPRANGE_N5_P5V			1 // ±5V
#define ACTS3100_AO_SAMPRANGE_N2D5_P2D5V		2 // ±2.5V
#define ACTS3100_AO_SAMPRANGE_N2D5_P7D5V		3 // -2.5~7.5V
#define ACTS3100_AO_SAMPRANGE_0_P10V			4 // 0~10V
#define ACTS3100_AO_SAMPRANGE_0_P5V				5 // 0~5V

typedef struct _ACTS3100_AO_PARAM // 跟整个AO有关的硬件工作参数(简称AO工作参数)
{
	// 通道参数
	U32 nSampChanCount;     // 采样通道总数[1, 4](只读参数, 它的取值由各通道参数CHParam[n].bChannelEn决定)
	U32 nReserved0;			// 保留字段(暂未定义)
	ACTS3100_AO_CH_PARAM CHParam[4]; // 通道参数(通道使能,采样范围)

	// 时钟参数
	U32 nSampleMode;		// 采样模式, 0=单点采样(按需), 1、硬件定时单点(暂不支持),2=有限点采样, 3=连续采样
	U32 nSampsPerChan;		// 有限点每通道采生成点数(字)
	F64 fSampleRate;		// 采样速率(Sample Rate), 单位为sps,取值范围为[1sps, 500000sps],它是每个采样通道的采样速率
	U32 nSampClkSource;		// 采样时钟信号选择, 详见下面常量定义
	U32 nExtSampClkEdge;	// 外部采样时钟边沿, 0=下降沿, 1=上升沿(仅当nSampClkSource非内时钟源时有效)
	U32 nClockOutput;		// 采样时钟输出选择,详见上面常量定义
	U32 bRegenModeEn;		// 波形重生成模式允许
	U32 nReserved1;			// 保留字段(暂未定义)	
	U32 nReserved2;			// 保留字段(暂未定义)	

	ACTS3100_AO_START_TRIG StartTrig; // 开始触发参数
	ACTS3100_AO_PAUSE_TRIG PauseTrig; // 暂停触发参数


	// 其他参数
	U32 nReserved3;			// 保留字段(暂未定义)
	U32 nReserved4;			// 保留字段(暂未定义)
	U32 nReserved5;			// 保留字段(暂未定义)
	U32 nReserved6;			// 保留字段(暂未定义)
} ACTS3100_AO_PARAM, * PACTS3100_AO_PARAM;

// AO硬件参数结构体ACTS3100_AO_PARAM中的nSampleMode采样模式所使用的选项
#define ACTS3100_AO_SAMPMODE_ONE_DEMAND		0 // 单点采样(按需)
#define ACTS3100_AO_SAMPMODE_ONE_HWTIMED	1 // 单点采样(硬件定时,Hardware Timed, 本设备暂时不支持)
#define ACTS3100_AO_SAMPMODE_FINITE			2 // 有限点采样
#define ACTS3100_AO_SAMPMODE_CONTINUOUS		3 // 连续采样

// AO硬件参数结构体ACTS3100_AO_PARAM中的nExtSampClkEdge外部采样时钟边沿所使用的选项
#define ACTS3100_AO_EXTSAMPCLK_EDGE_FALLING		0 // 下降沿
#define ACTS3100_AO_EXTSAMPCLK_EDGE_RISING		1 // 上升沿

// #################### AO工作状态结构体ACTS3100_AO_STATUS描述 #####################
typedef struct _ACTS3100_AO_STATUS
{
	U32 bTaskDone;				// 生成任务完成标志, =TRUE:表示生成任务完成, =FALSE:表示生成任务未完成,正在进行中
	U32 bTriggered;				// 触发标志, =TRUE:表示已被触发, =FALSE:表示未被触发(即正等待触发)

	U32 nTaskState;			// 生成任务状态, =1:正常, 其它值表示有异常情况
	U32 nAvailSampsPerChan;		// 可写点数,最好等它大于参数nWriteSampsPerChan时才能调用AO_WriteAnalog()写入采样数据
	U32 nMaxAvailSampsPerChan;	// 自AO_StartTask()后出现过的最大可写点数,状态值范围[0, nBufSampsPerChan],它是为监测采集软件性能而提供,如果此值越趋近于1,则表示意味着性能越高,越不易出现溢出丢点的可能
	U32 nBufSampsPerChan;		// 每通道缓冲区大小(点数)
	U64 nSampsPerChanAcquired;	// 每通道已采样点数(自开始AO_StartTask()之后所采样的点数),这个只是给用户的统计数据

	U32 nHardUnderflowCnt;		// 硬件缓冲下溢次数(在不下溢情况下恒等于0)
	U32 nSoftUnderflowCnt;		// 软件缓冲下溢次数(在不下溢情况下恒等于0)
	U32 nInitTaskCnt;			// 初始化生成任务的次数(即调用AO_InitTask()的次数)
	U32 nReleaseTaskCnt;		// 释放生成任务的次数(即调用AO_ReleaseTask()的次数)
	U32 nStartTaskCnt;			// 开始生成任务的次数(即调用AO_StartTask()的次数)
	U32 nStopTaskCnt;			// 停止生成任务的次数(即调用AO_StopTask()的次数)
	U32 nTransRate;				// 传输速率, 即每秒每通道传输点数(sps),作为USB及应用软件传输性能的监测信息

	U32 nReserved0;				// 保留字段(暂未定义)
	U32 nReserved1;				// 保留字段(暂未定义)
	U32 nReserved2;				// 保留字段(暂未定义)
	U32 nReserved3;				// 保留字段(暂未定义)
	U32 nReserved4;				// 保留字段(暂未定义)
} ACTS3100_AO_STATUS, * PACTS3100_AO_STATUS;

// #################### AO采样范围信息结构体(ACTS3100_AO_VOLT_RANGE_INFO) #######################
typedef struct _ACTS3100_AO_VOLT_RANGE_INFO
{
	U32 nSampleRange;		// 当前采样范围挡位号
	U32 nReserved0;			// 保留字段(暂未定义)
	F64 fMaxVolt;			// 采样范围的最大电压值,单位:伏(V)
	F64 fMinVolt;			// 采样范围的最小电压值,单位:伏(V)
	F64 fAmplitude;			// 采样范围幅度,单位:伏(V)
	F64 fHalfOfAmp;			// 采样范围幅度的二分之一,单位:伏(V)
	F64 fCodeWidth;			// 编码宽度,单位:伏(V), 即每个单位码值所分配的电压值
	F64 fOffsetVolt;		// 偏移电压,单位:伏(V),一般用于零偏校准
	F64 fOffsetCode;		// 偏移码值,一般用于零偏校准,它代表的电压值等价于fOffsetVolt
	char strDesc[16];		// 采样范围字符描述,如"±10V", "0-10V"等

	U32 nPolarity;			// 采样范围的极性(0=双极性BiPolar, 1=单极性UniPolar)
	U32 nCodeCount;			// 原码数量
	I32 nMaxCode;			// 原码最大值
	I32 nMinCode;	        // 原码最小值

	U32 nReserved1;			// 保留字段(暂未定义)
	U32 nReserved2;			// 保留字段(暂未定义)
	U32 nReserved3;			// 保留字段(暂未定义)
	U32 nReserved4;			// 保留字段(暂未定义)
} ACTS3100_AO_VOLT_RANGE_INFO, * PACTS3100_AO_VOLT_RANGE_INFO;

// 结构体AO_VOLT_RANGE_INFO的数据成员Polarity所用的采样范围极性选项
#define ACTS3100_AO_POLAR_BIPOLAR	0 // 双极性
#define ACTS3100_AO_POLAR_UNIPOLAR	1 // 单极性

// #################### AO速率信息结构体(ACTS3100_AO_SAMP_RATE_INFO) #######################
typedef struct _ACTS3100_AO_SAMP_RATE_INFO
{
	F64 fGSingleMaxRate;	// AO组内单通道最大频率Hz(一般板卡如果有4通道,0 2为一组,1 3为一组)
	F64 fGMultiMaxRate;		// AO组内多通道最大频率Hz(一般板卡如果有2通道,0 1为一组)
							// 5731,4个通道为一组，单通道1M,2通道每通道700K,3通道每通道500k,4通道每通道350K

	F64 fMinRate;		// 最小采样速率(sps)
	F64 fTimerBase;		// 时钟基准(即板载晶振频率)单位:Hz
	U32 nDivideMode;	// 分频模式,0=整数分频(INTDIV), 1=DDS分频(DDSDIV)
	U32 nRateType;		// 速率类型,指fMaxRate和fMinRate的类型, =0:表示为所有采样通道的总速率, =1:表示为每个采样通道的速率

	U32 nReserved0;		// 保留字段(暂未定义)
	U32 nReserved1;		// 保留字段(暂未定义)
} ACTS3100_AO_SAMP_RATE_INFO, * PACTS3100_AO_SAMP_RATE_INFO;

// AO_GetVoltRangeInfo()函数的参数nSampleRange所用的采样范围挡位选项
#define ACTS3100_AO_SAMPRANGE_FROM_DEVICE 0xFFFFFFFF	// 来自设备当前的采样范围挡位

#endif
#if 1
//////////////////////// DI ///////////////////////////////
typedef struct _ACTS3100_DI_START_TRIG // 开始触发参数
{
	U32 nTriggerType;		// 触发类型, 
	U32 nTriggerSource;		// 触发源, 详见(DI DO CTR 采样时钟、开始触发源、暂停触发源、计数复位信号源使用的选项)
	U32 nTriggerDir;	    // 触发方向(Trigger Direction)
	F32 fTriggerLevelTop;	// 触发窗顶部（边沿触发电平）
	F32 fTriggerLevelBtm;	// 触发窗底部
	U32 nTriggerSens;		// 触发灵敏度(Trigger Sensitive for Digital and Analog trigger),单位：微秒(uS)，取值范围[0, 1638]
	U32 nDelaySamps;		// 触发延迟点数, 单位：采样点，取值范围32位有效[0, 4294967295]，0:Post Trigger, >0:Delay Trigger
	U32 nReTrigger;			// 重触发使能, 1:使能

	U32 nReserved0;			// 保留字段(暂未定义)
	U32 nReserved1;			// 保留字段(暂未定义)
} ACTS3100_DI_START_TRIG, * PACTS3100_DI_START_TRIG;

typedef struct _ACTS3100_DI_PAUSE_TRIG // 暂停触发参数
{
	U32 nTriggerType;		// 触发类型, 
	U32 nTriggerSource;		// 触发源, 详见(DI DO CTR 采样时钟、开始触发源、暂停触发源、计数复位信号源使用的选项)
	U32 nTriggerDir;	    // 触发方向(Trigger Direction)
	F32 fTriggerLevelTop;	// 触发窗顶部（边沿触发电平）
	F32 fTriggerLevelBtm;	// 触发窗底部
	U32 nTriggerSens;		// 触发灵敏度(Trigger Sensitive for Digital and Analog trigger),单位：微秒(uS)，取值范围[0, 1638]

	U32 nReserved0;			// 保留字段(暂未定义)
	U32 nReserved1;			// 保留字段(暂未定义)
} ACTS3100_DI_PAUSE_TRIG, * PACTS3100_DI_PAUSE_TRIG;

// DI开始触发参数结构体ACTS3100_DI_START_TRIG中的nTriggerType触发类型所使用的选项
#define ACTS3100_DI_START_TRIGTYPE_NONE				0 // 无触发(等同于软件强制触发)
#define ACTS3100_DI_START_TRIGTYPE_ANALOG_EDGE		1 // 模拟边沿触发类型(保留,未提供)
#define ACTS3100_DI_START_TRIGTYPE_ANALOG_WIN		2 // 模拟窗触发类型(保留,未提供)
#define ACTS3100_DI_START_TRIGTYPE_DIGIT_EDGE		3 // 数字边沿触发类型
#define ACTS3100_DI_START_TRIGTYPE_DIGIT_PATTERN	4 // 数字模式触发类型(保留,未提供)

// DI开始触发参数结构体ACTS3100_DI_PAUSE_TRIG中的nTriggerType触发类型所使用的选项
#define ACTS3100_DI_PAUSE_TRIGTYPE_NONE				0 // 无触发(禁用暂停触发)
#define ACTS3100_DI_PAUSE_TRIGTYPE_ANALOG_LVL		1 // 模拟电平发类型(保留,未提供)
#define ACTS3100_DI_PAUSE_TRIGTYPE_ANALOG_WIN		2 // 模拟窗触发类型(保留,未提供)
#define ACTS3100_DI_PAUSE_TRIGTYPE_DIGIT_LVL		3 // 数字电平触发类型
#define ACTS3100_DI_PAUSE_TRIGTYPE_DIGIT_PATTERN	4 // 数字模式触发类型(保留,未提供)

// DI开始触发参数结构体ACTS3100_DI_START_TRIG中的nTriggerDir触发方向所使用的选项
// DI暂停触发参数结构体ACTS3100_DI_PAUSE_TRIG中的nTriggerDir触发方向所使用的选项
// 当为模拟边沿触发(nTriggerType = TRIGTYPE_ANALOG_EDGE):
#define ACTS3100_DI_TRIGDIR_FALLING			0 // 下降沿/低电平
#define ACTS3100_DI_TRIGDIR_RISING			1 // 上升沿/高电平
#define ACTS3100_DI_TRIGDIR_CHANGING		2 // 变化(即上下边沿/高低电平均有效)

// 当为模拟窗触发(nTriggerType = TRIGTYPE_ANALOG_WIN):
#define ACTS3100_DI_TRIGDIR_EnteringWin		0 // 入窗
#define ACTS3100_DI_TRIGDIR_LeavingWin		1 // 出窗
#define ACTS3100_DI_TRIGDIR_LeavingEnterWin	2 // 变化(出入窗均有效)

typedef struct _ACTS3100_DI_PARAM // 跟整个DI有关的硬件工作参数(简称DI工作参数)
{
	// 通道参数
	U32 nSampLineCount;     // 采样线总数[1, 32](此参数为只读，当执行DI_InitTask()后会返回实际的线数量,它是根据bLineEn[]的线使能情况统计的)
	U32 nReserved0;			// 保留字段(暂未定义)
	U8 bLineEn[32];			// 线号使能(Line Enable),仅针对于Port0有效,可通过ACTS3100_MAIN_INFO的nDIOPortLines[0]查看Port0线数

	// 时钟参数
	U32 nSampleMode;		// 采样模式, 0=单点采样(按需)， 1、硬件定时单点(暂不支持)，2=有限点采样， 3=连续采样
	U32 nSampsPerChan;		// 每个通道采样点数(也是每通道待读取点数),取值范围为单点采样模式时应等于1，有限点或连续采样时为[2, 1024*1024]
	F64 fSampleRate;		// 采样速率(Sample Rate), 单位为sps，取值范围为[1sps, 10000000sps]
	U32 nSampClkSource;		// 采样时钟源(请详见下面的常量定义)
	U32 nExtSampClkEdge;	// 外部采样时钟边沿, 0=下降沿, 1=上升沿(仅当nSampClkSource外部采样时钟源时有效)
	U32 nReserved1;			// 保留字段(暂未定义)
	U32 nReserved2;			// 保留字段(暂未定义)

	// 触发参数
	ACTS3100_DI_START_TRIG StartTrig; // 开始触发参数
	ACTS3100_DI_PAUSE_TRIG PauseTrig; // 暂停触发参数

	// 其他参数
	U32 nReserved3;			// 保留字段(暂未定义)
	U32 nReserved4;			// 保留字段(暂未定义)
	U32 nReserved5;			// 保留字段(暂未定义)
	U32 nReserved6;			// 保留字段(暂未定义)
} ACTS3100_DI_PARAM, * PACTS3100_DI_PARAM;

// ################################ DIO函数参数常量定义 ################################
// DI硬件参数结构体ACTS3100_DI_PARAM中的nSampleMode采样模式所使用的选项
#define ACTS3100_DI_SAMPMODE_ONE_DEMAND	0 // 单点采样(按需)
#define ACTS3100_DI_SAMPMODE_ONE_HWTIMED	1 // 单点采样(硬件定时,Hardware Timed, 本设备暂时不支持)
#define ACTS3100_DI_SAMPMODE_FINITE		2 // 有限点采样
#define ACTS3100_DI_SAMPMODE_CONTINUOUS	3 // 连续采样

// DI硬件参数结构体ACTS3100_DI_PARAM中的nExtSampClkEdge外部采样时钟边沿所使用的选项
#define ACTS3100_DI_EXTSAMPCLK_EDGE_FALLING		0 // 下降沿
#define ACTS3100_DI_EXTSAMPCLK_EDGE_RISING		1 // 上升沿

// #################### DI工作状态结构体ACTS3100_DI_STATUS描述 #####################
typedef struct _ACTS3100_DI_STATUS
{
	U32 bTaskDone;				// 采集任务完成标志, =TRUE:表示采集任务完成, =FALSE:表示采集任务未完成，正在进行中
	U32 bTriggered;				// 触发标志, =TRUE:表示已被触发, =FALSE:表示未被触发(即正等待触发)

	U32 nTaskState;				// 采集任务状态, =1:正常, 其它值表示有异常情况
	U32 nAvailSampsPerChan;		// 每通道有效点数，只有它大于当前指定读数长度时才能调用DI_ReadDigitalU8立即读取指定长度的采样数据
	U32 nMaxAvailSampsPerChan;	// 自DI_StartTask()后每通道出现过的最大有效点数，状态值范围[0, nBufSampsPerChan],它是为监测采集软件性能而提供，如果此值越趋近于1，则表示意味着性能越高，越不易出现溢出丢点的可能
	U32 nBufSampsPerChan;		// 每通道缓冲区大小(采样点数)。
	I64 nSampsPerChanAcquired;	// 每通道已采样点数(自开始采集任务(DI_StartTask())之后所采样的点数)，这个只是给用户的统计数据

	U32 nHardOverflowCnt;		// 硬件溢出计数(在不溢出情况下恒等于0)
	U32 nSoftOverflowCnt;		// 软件溢出计数(在不溢出情况下恒等于0)
	U32 nInitTaskCnt;			// 初始化采集任务的次数(即调用DI_InitTask()的次数)
	U32 nReleaseTaskCnt;		// 释放采集任务的次数(即调用DI_ReleaseTask()的次数)
	U32 nStartTaskCnt;			// 开始采集任务的次数(即调用DI_StartTask()的次数)
	U32 nStopTaskCnt;			// 停止采集任务的次数(即调用DI_StopTask()的次数)
	U32 nTransRate;				// 传输速率, 即每秒传输点数(sps)，作为USB及应用软件传输性能的监测信息

	U32 nReserved0;				// 保留字段(暂未定义)
	U32 nReserved1;				// 保留字段(暂未定义)
	U32 nReserved2;				// 保留字段(暂未定义)
	U32 nReserved3;				// 保留字段(暂未定义)
	U32 nReserved4;				// 保留字段(暂未定义)
} ACTS3100_DI_STATUS, * PACTS3100_DI_STATUS;

// #################### DI主要信息结构体(ACTS3100_DI_MAIN_INFO) #######################
typedef struct _ACTS3100_DI_MAIN_INFO
{
	U32 nPortCount;			// 端口数量
	U32 nReserved0;			// 保留字段(暂未定义)
	U32 nLineCount[4];		// 各个DI端口的线数量(线数量)
	U32 nImpedanceCount;	// DI阻抗的挡位数量
	U32 nDepthOfMemory;		// DI板载存储器深度(点数)

	U32 nReserved1;			// 保留字段(暂未定义)
	U32 nReserved2;			// 保留字段(暂未定义)
	U32 nReserved3;			// 保留字段(暂未定义)
	U32 nReserved4;			// 保留字段(暂未定义)
} ACTS3100_DI_MAIN_INFO, * PACTS3100_DI_MAIN_INFO;

// #################### DI速率信息结构体(ACTS3100_DI_SAMP_RATE_INFO) #######################
typedef struct _ACTS3100_DI_SAMP_RATE_INFO
{
	F64 fMaxRate;		// 单通道最大采样速率(sps)
	F64 fMinRate;		// 单通道最小采样速率(sps)
	F64 fTimerBase;		// 时钟基准（即板载晶振频率）单位：Hz
	U32 nDivideMode;	// 分频模式，0=整数分频(INTDIV), 1=DDS分频(DDSDIV)
	U32 nRateType;		// 速率类型,指fMaxRate和fMinRate的类型, =0:表示为所有采样通道的总速率, =1:表示为每个采样通道的速率

	U32 nReserved0;		// 保留字段(暂未定义)
	U32 nReserved1;		// 保留字段(暂未定义)
} ACTS3100_DI_SAMP_RATE_INFO, * PACTS3100_DI_SAMP_RATE_INFO;

#endif
#if 1
typedef struct _ACTS3100_DO_START_TRIG // 开始触发参数
{
	U32 nTriggerType;		// 触发类型, 
	U32 nTriggerSource;		// 触发源, 详见(DI DO CTR 采样时钟、开始触发源、暂停触发源、计数复位信号源使用的选项)
	U32 nTriggerDir;	    // 触发方向(Trigger Direction)
	F32 fTriggerLevelTop;	// 触发窗顶部（边沿触发电平）
	F32 fTriggerLevelBtm;	// 触发窗底部
	U32 nTriggerSens;		// 触发灵敏度(Trigger Sensitive for Digital and Analog trigger),单位：微秒(uS)，取值范围[0, 1638]
	U32 nDelaySamps;		// 触发延迟点数, 单位：采样点，取值范围32位有效[0, 4294967295]，0:Post Trigger, >0:Delay Trigger
	U32 nReTrigger;			// 重触发使能, 1:使能
	U32 nReserved0;			// 保留字段(暂未定义)
	U32 nReserved1;			// 保留字段(暂未定义)
} ACTS3100_DO_START_TRIG, * PACTS3100_DO_START_TRIG;

typedef struct _ACTS3100_DO_PAUSE_TRIG // 暂停触发参数
{
	U32 nTriggerType;		// 触发类型, 
	U32 nTriggerSource;		// 触发源, 详见(DI DO CTR 采样时钟、开始触发源、暂停触发源、计数复位信号源使用的选项)
	U32 nTriggerDir;	    // 触发方向(Trigger Direction)
	F32 fTriggerLevelTop;	// 触发窗顶部（边沿触发电平）
	F32 fTriggerLevelBtm;	// 触发窗底部
	U32 nTriggerSens;		// 触发灵敏度(Trigger Sensitive for Digital and Analog trigger),单位：微秒(uS)，取值范围[0, 1638]
	U32 nReserved0;			// 保留字段(暂未定义)
	U32 nReserved1;			// 保留字段(暂未定义)
} ACTS3100_DO_PAUSE_TRIG, * PACTS3100_DO_PAUSE_TRIG;

// DO开始触发参数结构体ACTS3100_DO_START_TRIG中的nTriggerType触发类型所使用的选项
#define ACTS3100_DO_START_TRIGTYPE_NONE				0 // 无触发(等同于软件强制触发)
#define ACTS3100_DO_START_TRIGTYPE_ANALOG_EDGE		1 // 模拟边沿触发类型(保留,未提供)
#define ACTS3100_DO_START_TRIGTYPE_ANALOG_WIN		2 // 模拟窗触发类型(保留,未提供)
#define ACTS3100_DO_START_TRIGTYPE_DIGIT_EDGE		3 // 数字边沿触发类型
#define ACTS3100_DO_START_TRIGTYPE_DIGIT_PATTERN		4 // 数字模式触发类型(保留,未提供)

// DO开始触发参数结构体ACTS3100_DO_PAUSE_TRIG中的nTriggerType触发类型所使用的选项
#define ACTS3100_DO_PAUSE_TRIGTYPE_NONE				0 // 无触发(禁用暂停触发)
#define ACTS3100_DO_PAUSE_TRIGTYPE_ANALOG_LVL		1 // 模拟电平发类型(保留,未提供)
#define ACTS3100_DO_PAUSE_TRIGTYPE_ANALOG_WIN		2 // 模拟窗触发类型(保留,未提供)
#define ACTS3100_DO_PAUSE_TRIGTYPE_DIGIT_LVL			3 // 数字电平触发类型
#define ACTS3100_DO_PAUSE_TRIGTYPE_DIGIT_PATTERN		4 // 数字模式触发类型(保留,未提供)

// DO开始触发参数结构体ACTS3100_DO_START_TRIG中的nTriggerDir触发方向所使用的选项
// DO暂停触发参数结构体ACTS3100_DO_PAUSE_TRIG中的nTriggerDir触发方向所使用的选项
// 当为模拟边沿触发(nTriggerType = TRIGTYPE_ANALOG_EDGE):
#define ACTS3100_DO_TRIGDIR_FALLING			0 // 下降沿/低电平
#define ACTS3100_DO_TRIGDIR_RISING			1 // 上升沿/高电平
#define ACTS3100_DO_TRIGDIR_CHANGING			2 // 变化(即上下边沿/高低电平均有效)

// 当为模拟窗触发(nTriggerType = TRIGTYPE_ANALOG_WIN):
#define ACTS3100_DO_TRIGDIR_EnteringWin		0 // 入窗
#define ACTS3100_DO_TRIGDIR_LeavingWin		1 // 出窗
#define ACTS3100_DO_TRIGDIR_LeavingEnterWin	2 // 变化(出入窗均有效)

typedef struct _ACTS3100_DO_PARAM // 跟整个DO有关的硬件工作参数(简称DO工作参数)
{
	// 通道参数
	U32 nSampLineCount;     // 采样线总数[1, 32](此参数为只读，当执行DO_InitTask()后会返回实际的线数量,它是根据bLineEn[]的线使能情况统计的)
	U32 nReserved0;
	U8 bLineEn[32];			// 线号使能(Line Enable),仅针对于Port0有效,可通过ACTS3100_MAIN_INFO的nDIOPortLines[0]查看Port0线数

	// 时钟参数
	U32 nSampleMode;		// 采样模式, 0=单点采样(按需)， 1、硬件定时单点(暂不支持)，2=有限点采样， 3=连续采样
	U32 nSampsPerChan;		// 每个通道采样点数(也是每通道待读取点数),取值范围为单点采样模式时应等于1，有限点或连续采样时为[2, 1024*1024]
	F64 fSampleRate;		// 采样速率(Sample Rate), 单位为sps，取值范围为[1sps, 10000000sps]
	U32 nSampClkSource;		// 采样时钟源(请详见下面的常量定义)
	U32 nExtSampClkEdge;	// 外部采样时钟边沿, 0=下降沿, 1=上升沿(仅当nSampClkSource外部采样时钟源时有效)
	U32 bRegenModeEn;		// 波形重生成模式允许, =TRUE:只是对开始生成任前写入任务中的波形段数据进行循环重复生成，=FALSE:禁止重生成模式，在开始生成任务后，还要不断的往任务中写入新的波形数据
	U32 nReserved1;			// 保留字段(暂未定义)

	ACTS3100_DO_START_TRIG StartTrig; // 开始触发参数
	ACTS3100_DO_PAUSE_TRIG PauseTrig; // 暂停触发参数

	// 其他方面
	U32 nReserved2;			// 保留字段(暂未定义)
	U32 nReserved3;			// 保留字段(暂未定义)
	U32 nReserved4;			// 保留字段(暂未定义)
	U32 nReserved5;			// 保留字段(暂未定义)
} ACTS3100_DO_PARAM, * PACTS3100_DO_PARAM;

// DO硬件参数结构体ACTS3100_DO_PARAM中的nSampleMode采样模式所使用的选项
#define ACTS3100_DO_SAMPMODE_ONE_DEMAND	0 // 单点采样(按需)
#define ACTS3100_DO_SAMPMODE_ONE_HWTIMED	1 // 单点采样(硬件定时,Hardware Timed, 本设备暂时不支持)
#define ACTS3100_DO_SAMPMODE_FINITE		2 // 有限点采样
#define ACTS3100_DO_SAMPMODE_CONTINUOUS	3 // 连续采样

// DO硬件参数结构体ACTS3100_DO_PARAM中的nExtSampClkEdge外部采样时钟边沿所使用的选项
#define ACTS3100_DO_EXTSAMPCLK_EDGE_FALLING		0 // 下降沿
#define ACTS3100_DO_EXTSAMPCLK_EDGE_RISING		1 // 上升沿

// #################### DO工作状态结构体ACTS3100_DO_STATUS描述 #####################
typedef struct _ACTS3100_DO_STATUS
{
	U32 bTaskDone;				// 采集任务完成标志, =TRUE:表示采集任务完成, =FALSE:表示采集任务未完成，正在进行中
	U32 bTriggered;				// 触发标志, =TRUE:表示已被触发, =FALSE:表示未被触发(即正等待触发)

	U32 nTaskState;				// 采集任务状态, =1:正常, 其它值表示有异常情况
	U32 nAvailSampsPerChan;		// 每通道有效点数，只有它大于当前指定读数长度时才能调用DO_ReadDigitalLines立即读取指定长度的采样数据
	U32 nMaxAvailSampsPerChan;	// 自DO_StartTask()后每通道出现过的最大有效点数，状态值范围[0, nBufSampsPerChan],它是为监测采集软件性能而提供，如果此值越趋近于1，则表示意味着性能越高，越不易出现溢出丢点的可能
	U32 nBufSampsPerChan;		// 每通道缓冲区大小(采样点数)。
	I64 nSampsPerChanAcquired;	// 每通道已采样点数(自开始采集任务(DO_StartTask())之后所采样的点数)，这个只是给用户的统计数据

	U32 nHardUnderflowCnt;		// 硬件缓冲下溢次数(在不下溢情况下恒等于0)
	U32 nSoftUnderflowCnt;		// 软件缓冲下溢次数(在不下溢情况下恒等于0)
	U32 nInitTaskCnt;			// 初始化采集任务的次数(即调用DO_InitTask()的次数)
	U32 nReleaseTaskCnt;		// 释放采集任务的次数(即调用DO_ReleaseTask()的次数)
	U32 nStartTaskCnt;			// 开始采集任务的次数(即调用DO_StartTask()的次数)
	U32 nStopTaskCnt;			// 停止采集任务的次数(即调用DO_StopTask()的次数)
	U32 nTransRate;				// 传输速率, 即每秒传输点数(sps)，作为USB及应用软件传输性能的监测信息

	U32 nReserved0;				// 保留字段(暂未定义)
	U32 nReserved1;				// 保留字段(暂未定义)
	U32 nReserved2;				// 保留字段(暂未定义)
	U32 nReserved3;				// 保留字段(暂未定义)
	U32 nReserved4;				// 保留字段(暂未定义)
} ACTS3100_DO_STATUS, * PACTS3100_DO_STATUS;

// #################### DO主要信息结构体(ACTS3100_DO_MAIN_INFO) #######################
typedef struct _ACTS3100_DO_MAIN_INFO
{
	U32 nPortCount;			// 端口数量
	U32 nReserved0;			// 保留字段(暂未定义)
	U32 nChannelCount[4];	// 各个DI端口的通道数量(线数量)
	U32 nImpedanceCount;	// DI阻抗的挡位数量
	U32 nDepthOfMemory;		// DI板载存储器深度(点数)

	U32 nReserved1;			// 保留字段(暂未定义)
	U32 nReserved2;			// 保留字段(暂未定义)
	U32 nReserved3;			// 保留字段(暂未定义)
	U32 nReserved4;				// 保留字段(暂未定义)
} ACTS3100_DO_MAIN_INFO, * PACTS3100_DO_MAIN_INFO;

// #################### DO速率信息结构体(ACTS3100_DO_SAMP_RATE_INFO) #######################
typedef struct _ACTS3100_DO_SAMP_RATE_INFO
{
	F64 fMaxRate;		// 单通道最大采样速率(sps)，多通道时各通道平分最大采样率
	F64 fMinRate;		// 单通道最小采样速率(sps)，多通道时各通道平分最小采样率
	F64 fTimerBase;		// 时钟基准（即板载晶振频率）单位：Hz
	U32 nDivideMode;	// 分频模式，0=整数分频(INTDIV), 1=DDS分频(DDSDIV)
	U32 nRateType;		// 速率类型,指fMaxRate和fMinRate的类型, =0:表示为所有采样通道的总速率, =1:表示为每个采样通道的速率

	U32 nReserved0;		// 保留字段(暂未定义)
	U32 nReserved1;		// 保留字段(暂未定义)
} ACTS3100_DO_SAMP_RATE_INFO, * PACTS3100_DO_SAMP_RATE_INFO;

#endif
#if 1
// ################################ CI函数参数常量定义 ################################
// 函数CI_CreateFreqChan()/CI_CreatePeriodChan()的参数nEdge所用的边沿类型
#define ACTS3100_CI_EDGE_FALLING		0	// 下降沿测量
#define ACTS3100_CI_EDGE_RISING		1	// 上升沿测量

// 函数CI_CreateFreqChan()/CI_CreatePeriodChan()的参数nMeasMethod所用的测量方法
#define ACTS3100_CI_LOWFREQ		0	// 低频测量,将计数器与待测信号和时基一起使用，待测信号作为门控信号，时基作为源,等同于单周期测量的逆操作
#define ACTS3100_CI_HIGHFREQ		1	// 高频测量,在指定的时间范围内对信号的脉冲进行计数。一个内置计数器实现fMeasTime指定的时间(提供门控信号)，该计数器在指定时间内对被测信号进行计数
#define ACTS3100_CI_LARGERNG		2	// 宽范围测量,使用内置计数器将输入信号的频率除以除数(nDivisor)，生成一个该计数器更易于测量的低频信号。测量时间fMeasTime由内部时基实现

// 函数CI_CreateCountEdgesChan()的参数nCountDirection所用的计数方向
#define ACTS3100_CI_COUNT_DOWN		0	// 减值计数（递减计数）
#define ACTS3100_CI_COUNT_UP			1	// 升值计数（递增计数）
#define ACTS3100_CI_COUNT_EXT_CTRL	2	// 外部控制, 数字线的状态控制计数方向(来自AUX)

// 函数CI_CreateLinEncoderChan()的参数nDecodingType所用的解码类型
#define ACTS3100_CI_DECODING_TYPE_X1			0		// X1
#define ACTS3100_CI_DECODING_TYPE_X2			1		// X2
#define ACTS3100_CI_DECODING_TYPE_X4			2		// X4
#define ACTS3100_CI_DECODING_TYPE_TWO_PULSE	3		// 双脉冲解码
#define ACTS3100_CI_DECODING_TYPE_SINGLE_PULSE	4	// 单脉冲解码

// 函数CI_CreateLinEncoderChan()的参数nZidxPhase所用的Z索引相位
#define ACTS3100_CI_ZIDX_PHASE_AHighBHigh	0	// A高B高
#define ACTS3100_CI_ZIDX_PHASE_AHighBLow		1	// A高B低
#define ACTS3100_CI_ZIDX_PHASE_ALowBHigh		2	// A低B高
#define ACTS3100_CI_ZIDX_PHASE_ALowBLow		3	// A低B低

// 函数CI_CreateFreqChan()的参数nUnits所用的频率单位
#define ACTS3100_CI_FREQ_UINTS_Hz			0	// 赫兹
#define ACTS3100_CI_FREQ_UINTS_Ticks		1	// 时钟滴答计数

// 函数CI_CreatePeriodChan()/CI_CreateSemiPeriodChan()/CI_CreatePulseWidthChan()/CI_CreateTwoEdgeSepChan()/CI_SetDigitalFilter()的参数nUnits所用的时间单位
#define ACTS3100_CI_TIME_UINTS_Seconds		0	// 秒
#define ACTS3100_CI_TIME_UINTS_Ticks		1	// 时钟滴答计数

// 函数CI_CreateLinEncoderChan()的参数nUnits所用的线性编码器单位
#define ACTS3100_CI_LIN_ENDCODER_UINTS_Meters	0	// 米
#define ACTS3100_CI_LIN_ENDCODER_UINTS_Inches	1	// 英寸
#define ACTS3100_CI_LIN_ENDCODER_UINTS_Ticks	2	// 时钟滴答计数

// 函数CI_CreateAngEncoderChan()的参数nUnits所用的线性编码器单位
#define ACTS3100_CI_ANG_ENDCODER_UINTS_Degrees	0	// 度
#define ACTS3100_CI_ANG_ENDCODER_UINTS_Radians	1	// 弧度
#define ACTS3100_CI_ANG_ENDCODER_UINTS_Ticks	2	// 时钟滴答计数

// 函数CI_SetDigitalFilter()的参数nSignal所用的滤波信号源选择
#define ACTS3100_CI_FILTER_SIGNAL_Src	0	// 滤波信号源为Src输入
#define ACTS3100_CI_FILTER_SIGNAL_Gate	1	// 滤波信号源为Gate输入
#define ACTS3100_CI_FILTER_SIGNAL_Aux	2	// 滤波信号源为Aux输入

// ################################ CO函数参数常量定义 ################################
// 函数CO_CreatePulseChanTime()的参数nIdleState所用的空闲状态
#define ACTS3100_CO_IDLE_STATE_Low				0	// 低
#define ACTS3100_CO_IDLE_STATE_High				1	// 高

// 函数CO_CreatePulseChanTime()的参数nUnits所用的时间单位
#define ACTS3100_CO_TIME_UINTS_Seconds			0	// 秒
#define ACTS3100_CO_TIME_UINTS_Milliseconds		1	// 毫秒
#define ACTS3100_CO_TIME_UINTS_Microseconds		2	// 微秒

// 函数CO_CreatePulseChanFreq()的参数nUnits所用的频率单位
#define ACTS3100_CO_FREQ_UINTS_Hz				0	// 赫兹
#define ACTS3100_CO_FREQ_UINTS_KHz				1	// 千赫兹
#define ACTS3100_CO_FREQ_UINTS_MHz				2	// 兆赫兹

// 函数CTR_CfgSampClkTiming()/CTR_CfgImplicitTiming()的参数nSampleMode所用的采样模式
#define ACTS3100_CTR_SAMPMODE_ONE_DEMAND		0 // 单点采样(按需)
#define ACTS3100_CTR_SAMPMODE_ONE_HWTIMED		1 // 单点采样(硬件定时,Hardware Timed, 本设备暂时不支持)
#define ACTS3100_CTR_SAMPMODE_FINITE			2 // 有限点采样
#define ACTS3100_CTR_SAMPMODE_CONTINUOUS		3 // 连续采样

// 函数CTR_CfgSampClkTiming()/CTR_CfgImplicitTiming()的参数nActiveEdge所用的有效边沿
#define ACTS3100_CTR_EDGE_FALLING				0	// 下降边沿
#define ACTS3100_CTR_EDGE_RISING				1	// 上升边沿

// CTR开始触发参数结构体ACTS3100_CTR_START_TRIG中的nTriggerDir触发方向所使用的选项
// 当为模拟边沿触发(nTriggerType = TRIGTYPE_ANALOG_EDGE):
#define ACTS3100_CTR_TRIGDIR_FALLING			0 // 下降沿/低电平
#define ACTS3100_CTR_TRIGDIR_RISING				1 // 上升沿/高电平
#define ACTS3100_CTR_TRIGDIR_CHANGING			2 // 变化(即上下边沿/高低电平均有效)

// 函数CTR_SetExportedOutEventParam()的参数nBehavior所使用行为参数
#define ACTS3100_CTR_Behavior_Pulse				0 // 脉冲行为
#define ACTS3100_CTR_Behavior_Toggle			1 // 反转行为

// 函数CTR_SetExportedOutEventParam()的参数nPolarity所使用参数（当nBehavior＝Pulse时有效）
#define ACTS3100_CTR_PulsePolarity_ActiveLow	0 // 低脉冲
#define ACTS3100_CTR_PulsePolarity_ActiveHigh	1 // 高脉冲

// 函数CTR_SetExportedOutEventParam()的参数nIdleState所使用参数（当nBehavior＝Toggle时有效）
#define ACTS3100_CTR_ToggleIdleState_Low		0 // 低电平
#define ACTS3100_CTR_ToggleIdleState_High		1 // 高电平

#endif
// ################################ 函数错误信息 ################################
#define ERROR_NO_AVAILABLE_SAMPS	(0xE0000000+1)	// 无有效点数
#define ERROR_TASK_FAIL				(0xE0000000+2)  // 任务失败
#define ERROR_RATE_OVER_RANGE		(0xE0000000+3)	// 采样速率超限



//***********************************************************
// ACTS3100_WaitForIntEvent函数返回值
#define ART_STATUS_OK                       0   // 成功
#define ART_STATUS_FAILED                   -1  // 失败
#define ART_STATUS_TIMEOUT                  -2  // 超时

#ifdef __cplusplus
extern "C"{
#endif
// 用户函数接口

		//######################## 设备对象管理函数 ##############################
    HANDLE ACTS3100_DEV_Create(				// 创建设备对象句柄(hDevice), 成功返回实际句柄,失败则返回INVALID_HANDLE_VALUE(-1)
		U32 nIndex,				// 设备序号(逻辑序号,物理序号,具体使用哪种序号由参数nIndexType指定)
		BOOL nIndexType);		// 设备序号类型, =0:使用逻辑号; =1:使用物理序号;

    LONG ACTS3100_DEV_GetCount();				// 取得设备总台数
    BOOL ACTS3100_DEV_GetCurrentIdx(HANDLE hDevice,		// 取得当前设备相应的ID号
		PLONG DeviceLgcID,					// 设备的逻辑索引号
		PLONG DevicePhysID);				// 备的物理索引号
    BOOL ACTS3100_GetMainInfo(							// 获得板卡主要信息
		HANDLE hDevice,						// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_MAIN_INFO pMainInfo);		// 获得AI主要信息

    BOOL ACTS3100_DEV_SetReferenceClock(					// 设置板卡参考时钟(仅支持PXIE板卡)
		HANDLE hDevice,						//设备对象句柄,它由DEV_Create()函数创建
		LONG nReferenceClock);				// 0:板载10M 1:PXI_10M 2:PXIe_100M

    BOOL ACTS3100_DEV_Release(HANDLE hDevice);			// 仅释放设备对象

	// ################################ AI模拟量输入实现函数 ################################
    BOOL ACTS3100_AI_InitTask(				// 初始化AI采集任务(Initialize Task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_AI_PARAM pAIParam); // AI工作参数, 它仅在此函数中决定硬件初始状态和各工作模式,可以事先由AI_VerifyParam()进行参数校验

    BOOL ACTS3100_AI_GetParam(					// 取得AI工作参数表,可在AI_InitTask()前调用它取得默认参数表，然后修改必要的一些参数后就可以初始化任务了
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_AI_PARAM pAIParam);// 取得时钟输出允许, =0:表示禁止时钟输出,=1:表示允许时钟输出到指定的接线端

    BOOL ACTS3100_AI_StartTask(				// 开始采集任务
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

    BOOL ACTS3100_AI_SendSoftTrig(			// 发送软件触发事件(Send Software Trigger)
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

    BOOL ACTS3100_AI_GetStatus(HANDLE hDevice, PACTS3100_AI_STATUS pAIStatus);   // 取得AI各种状态

    BOOL ACTS3100_AI_ReadAnalog(				// 从采集任务中读取采样数据(电压数据序列)(Read analog data from the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		F64 fAnlgArray[],		// 模拟数据数组(电压数组),用于返回采样的电压数据,取值区间由各通道采样时的采样范围决定(单位:V)
		U32 nReadSampsPerChan,	// 每通道请求读取的点数(单位:点)
		U32* pSampsPerChanRead,	// 返回每通道实际读取的点数(单位:点)
		U32* pAvailSampsPerChan,// 任务中还存在的可读点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间,单位:秒(S)

	BOOL ACTS3100_AI_ReadBinaryU16(				// 从采集任务中读取采样数据(原码数据序列)(Continuous Read All Channels for Code),单个点占用2字节使用
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U16 nBinArray[],		// 二进制数据数组(原码数组),用于返回采样的原码数据,12位精度取值区间为[0, 4095]
		U32 nReadSampsPerChan,	// 每通道请求读取的点数(单位:点)
		U32* pSampsPerChanRead,	// 返回每通道实际读取的点数(单位:点)
		U32* pAvailSampsPerChan,// 任务中还存在的可读点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间,单位:秒(S)

	BOOL ACTS3100_AI_ReadBinaryU32(				// 从采集任务中读取采样数据(原码数据序列)(Continuous Read All Channels for Code),,单个点占用4字节使用
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nBinArray[],		// 二进制数据数组(原码数组),用于返回采样的原码数据,18位精度取值区间为[0, 262143]
		U32 nReadSampsPerChan,	// 每通道请求读取的点数(单位:点)
		U32* pSampsPerChanRead,	// 返回每通道实际读取的点数(单位:点)
		U32* pAvailSampsPerChan,// 任务中还存在的可读点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间,单位:秒(S)

    BOOL ACTS3100_AI_StopTask(HANDLE hDevice);	// 停止采集任务

    BOOL ACTS3100_AI_ReleaseTask(HANDLE hDevice); // 释放采集任务

	// ========================= AI辅助操作函数 =========================
    BOOL ACTS3100_AI_GetVoltRangeInfo(			// 获得采样范围的各种信息(幅度、分辨率、极性)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// AI物理通道号
		U32 nSampleRange,		// 采样范围选择[0, 3],此参数需传实际值,操作同ACTS3100_AO_CH_PARAM的nSampleRange
		PACTS3100_AI_VOLT_RANGE_INFO pRangeInfo); // 采样范围信息

    BOOL ACTS3100_AI_GetRateInfo(				// 获得采样速率信息
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_AI_SAMP_RATE_INFO pRateInfo); // 采样速率信息

	BOOL ACTS3100_AI_ScaleBinToVoltU16(			// 根据指定采样范围将单个通道的采样原码数据量化成电压数据,单个点占用2字节使用
		PACTS3100_AI_VOLT_RANGE_INFO pRangeInfo, // 当前转换数据需要的采样范围信息
		PVOID pGainInfo,		// 当前转换数据需要的采样增益信息(若于=NULL,表示不使用增益)
		F64 fVoltArray[],		// 电压数据数组,用于返回量化后的电压数据,单位V
		U16 nBinArray[],		// 二进制原码数组,用于传入量化前的原码数据,12位精度取值区间为[0, 4095], (单指某个通道的连续数据),
		U32 nScaleSamps,		// 请求量化的采样点数
		U32* pSampsScaled);		// 返回实际量化的采样点数, =NULL,表示无须返回

	BOOL ACTS3100_AI_ScaleVoltToBinU16(			// 根据指定采样范围将单个通道的电压数据量化成二进制原码数据,单个点占用2字节使用
		PACTS3100_AI_VOLT_RANGE_INFO pRangeInfo, // 当前转换数据需要的采样范围信息
		PVOID pGainInfo,   // 当前转换数据需要的采样增益信息(若于=NULL,表示不使用增益)
		U16 nBinArray[],		// 原码缓冲区,用于返回量化后的原码数据,12位精度取值区间为[0, 4095], (单指某个通道的连续数据)
		F64 fVoltArray[],		// 电压缓冲区,用于传入量化前的电压数据,单位V
		U32 nScaleSamps,		// 请求量化的采样点数
		U32* pSampsScaled);		// 返回实际量化的采样点数, =NULL,表示无须返回

	BOOL ACTS3100_AI_ScaleBinToVoltU32(			// 根据指定采样范围将单个通道的采样原码数据量化成电压数据,单个点占用4字节使用
		PACTS3100_AI_VOLT_RANGE_INFO pRangeInfo, // 当前转换数据需要的采样范围信息
		PVOID pGainInfo,		// 当前转换数据需要的采样增益信息(若于=NULL,表示不使用增益)
		F64 fVoltArray[],		// 电压数据数组,用于返回量化后的电压数据,单位V
		U32 nBinArray[],		// 二进制原码数组,用于传入量化前的原码数据,18位精度取值区间为[0, 262143], (单指某个通道的连续数据),
		U32 nScaleSamps,		// 请求量化的采样点数
		U32* pSampsScaled);		// 返回实际量化的采样点数, =NULL,表示无须返回

	BOOL ACTS3100_AI_ScaleVoltToBinU32(			// 根据指定采样范围将单个通道的电压数据量化成二进制原码数据,单个点占用4字节使用
		PACTS3100_AI_VOLT_RANGE_INFO pRangeInfo, // 当前转换数据需要的采样范围信息
		PVOID pGainInfo,   // 当前转换数据需要的采样增益信息(若于=NULL,表示不使用增益)
		U32 nBinArray[],		// 原码缓冲区,用于返回量化后的原码数据,18位精度取值区间为[0, 262143], (单指某个通道的连续数据)
		F64 fVoltArray[],		// 电压缓冲区,用于传入量化前的电压数据,单位V
		U32 nScaleSamps,		// 请求量化的采样点数
		U32* pSampsScaled);		// 返回实际量化的采样点数, =NULL,表示无须返回

    BOOL ACTS3100_AI_VerifyParam(				// 校验AI工作参数(Verify Parameter),建议在初始化AI参数前调用此函数校验各参数合法性
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_AI_PARAM pAIParam);// 待校验的AI工作参数

    BOOL ACTS3100_AI_ResetParam(HANDLE hDevice, PACTS3100_AI_PARAM pAIParam); // 将当前AI参数复位至出厂值

	// ################################ AO模拟量输出实现函数 ################################
    BOOL ACTS3100_AO_InitTask(					// 初始化生成任务(Initialize Task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_AO_PARAM pAOParam); // AO工作参数, 它仅在此函数中决定硬件初始状态和各工作模式,可以事先由AI_VerifyParam()进行参数校验

    BOOL ACTS3100_AO_GetParam(				// 取得AO工作参数表,可在AO_InitTask()前调用它取得默认参数表，然后修改必要的一些参数后就可以初始化任务了
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_AO_PARAM pAOParam);// 取得AO工作参数

    BOOL ACTS3100_AO_StartTask(				// 开始生成任务(Start Task)
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

    BOOL ACTS3100_AO_SendSoftTrig(			// 发送软件触发事件(Send Software Trigger)
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

    BOOL ACTS3100_AO_GetStatus(HANDLE hDevice, PACTS3100_AO_STATUS pAOStatus);   // 取得AO各种状态

    BOOL ACTS3100_AO_WaitUntilTaskDone(		// 生成任务结束前等待,返回TRUE表示生成任务结束
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		F64 fTimeout);			// 超时时间,单位:秒(S)

    BOOL ACTS3100_AO_WriteAnalog(				// 向生成任务中写入AO输出的模拟量电压数据(Write analog data to the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		F64 fAnlgArray[],		// AO0、AO1电压混合缓冲区,存放AO的模拟(电压)数据,取值区间由各通道采样时的采样范围决定(单位:V)
		U32 nWriteSampsPerChan,	// 每通道请求写入的点数(单位:点)
		U32* pSampsPerChanWritten,// 返回每通道实际写入的点数(单位:点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 返回当前可写入的采样点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间,单位:秒(S)

    BOOL ACTS3100_AO_WriteBinary(				// 向生成任务中写入AO输出的二进制原码数据(Write binary data to the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U16 nBinArray[],		// AO0、AO1原码混合缓冲区,用于输出生成的原码数据,12位精度取值区间为[0, 4095]
		U32 nWriteSampsPerChan,	// 每通道请求写入的点数(单位:点), =NULL,表示无须返回
		U32* pSampsPerChanWritten,// 返回每通道实际写入的点数(单位:点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 返回当前可写入的采样点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间,单位:秒(S)

    BOOL ACTS3100_AO_ReadbackAnalog(			// 回读所有AO通道的当前生成的模拟量数据(电压数据序列)(Read back analog data from the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		F64 fAnlgArray[4]);		// fAnlgArray[0]=AO0电压数据,fAnlgArray[1]=AO1电压数据, 取值区间由相应通道的采样范围决定

    BOOL ACTS3100_AO_ReadbackBinary(			// 回读所有AO通道的当前生成的模拟量数据(二进制原码数据序列)(Read back binary data from the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U16 nBinArray[4]);		// nBinArray[0]=AO0原码数据,nBinArray[1]=AO1原码数据, 取值区间[0, 4095]

    BOOL ACTS3100_AO_StopTask(HANDLE hDevice);// 停止生成任务

    BOOL ACTS3100_AO_ReleaseTask(HANDLE hDevice);// 释放生成任务

	// ========================= AO辅助操作函数 =========================
    BOOL ACTS3100_AO_GetVoltRangeInfo(		// 获得采样范围的各种信息(幅度、分辨率、极性)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// AO物理通道号[0, 3],nSampleRange等于AO_SAMPRANGE_FROM_DEVICE时此参数起作用
		U32 nSampleRange,		// 由用户指定的采样范围挡位号[0, 5],若=AO_SAMPRANGE_FROM_DEVICE(0xFFFFFFFF),表示依据设备当前的挡位号取得采样范围信息,此参数需传实际值,操作同ACTS3100_AO_CH_PARAM的nSampleRange
		PACTS3100_AO_VOLT_RANGE_INFO pRangeInfo); // 采样范围信息

    BOOL ACTS3100_AO_GetRateInfo(				// 获得采样速率信息
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_AO_SAMP_RATE_INFO pRateInfo); // 采样速率信息

    BOOL ACTS3100_AO_ScaleBinToVolt(			// 根据指定采样范围将单个通道的采样原码数据量化成电压数据,返回实际量化的点数
		PACTS3100_AO_VOLT_RANGE_INFO pRangeInfo, // 当前转换数据需要的采样范围信息
		F64 fVoltArray[],		// 电压缓冲区,用于返回量化后的电压数据,单位V
		U16 nBinArray[],		// 二进制原码缓冲区,用于传入量化前的原码数据,取值区间为[0, nAOSampCodeCount-1], (单指某个通道的连续数据)
		U32 nScaleSamps,		// 请求量化的采样点数
		U32* pSampsScaled);		// 返回实际量化的采样点数

    BOOL ACTS3100_AO_ScaleVoltToBin(			// 根据指定采样范围将单个通道的电压数据量化成采样原码数据,返回实际量化的点数
		PACTS3100_AO_VOLT_RANGE_INFO pRangeInfo,// 当前转换数据需要的采样范围信息
		U16 nBinArray[],		// 原码缓冲区,用于返回量化后的原码数据,取值区间为[0, nAOSampCodeCount-1], (单指某个通道的连续数据)
		F64 fVoltArray[],		// 电压缓冲区,用于传入量化前的电压数据,单位V
		U32 nScaleSamps,		// 请求量化的采样点数
		U32* pSampsScaled);		// 返回实际量化的采样点数

    BOOL ACTS3100_AO_VerifyParam(					// 校验AO工作参数(Verify Parameter),建议在初始化AO参数前调用此函数校验各参数合法性
		HANDLE hDevice,					// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_AO_PARAM pAOParam);	// 待校验的AO工作参数

    BOOL ACTS3100_AO_ResetParam(HANDLE hDevice, PACTS3100_AO_PARAM pAOParam); // 将当前AO参数复位至出厂值

	// ############################ DI数字量输入实现函数 ############################
    BOOL ACTS3100_DI_InitTask(					// 初始化DI采集任务(仅基于Port0)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_DI_PARAM pDIParam); // DI工作参数, 决定硬件初始状态和各工作模式,可以事先由DI_VerifyParam()进行参数校验

    BOOL ACTS3100_DI_GetParam(					// 取得DI工作参数表,可在DI_InitTask()前调用它取得默认参数表，然后修改必要的一些参数后就可以初始化任务了
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_DI_PARAM pDIParam);// 取得时钟输出允许, =0:表示禁止时钟输出,=1:表示允许时钟输出到指定的接线端

    BOOL ACTS3100_DI_GetStatus(				// 获取DI状态
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_DI_STATUS pDIStatus);// 取得DI各种状态

    BOOL ACTS3100_DI_WaitUntilTaskDone(		// Port0采集任务结束前等待,返回TRUE表示采集任务结束
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		F64 fTimeout);			// 用于等待的时间，单位：秒(S)

    BOOL ACTS3100_DI_StartTask(				// 启动Port0采集任务
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

    BOOL ACTS3100_DI_SendSoftTrig(				// 发送软件触发事件(Send Software Trigger),软件触发也叫强制触发
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

    BOOL ACTS3100_DI_ReadDigitalU8(			// 从Port0采集任务中读取采样数据(原码数据序列)(Read port data from the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U8 nPortDataArray[],	// 端口数据缓冲，装载采样的数据
		U32 nReadSampsPerChan,	// 每通道请求读取的点数(单位：点)
		U32* pSampsPerChanRead,	// 返回每通道实际读取的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 任务中还存在的可读点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

	BOOL ACTS3100_DI_ReadDigitalU16(			// 从Port0采集任务中读取采样数据(原码数据序列)(Read port data from the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U16 nPortDataArray[],	// 端口数据缓冲，装载采样的数据
		U32 nReadSampsPerChan,	// 每通道请求读取的点数(单位：点)
		U32* pSampsPerChanRead,	// 返回每通道实际读取的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 任务中还存在的可读点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

	BOOL ACTS3100_DI_ReadDigitalU32(			// 从Port0采集任务中读取采样数据(原码数据序列)(Read port data from the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPortDataArray[],	// 端口数据缓冲，装载采样的数据
		U32 nReadSampsPerChan,	// 每通道请求读取的点数(单位：点)
		U32* pSampsPerChanRead,	// 返回每通道实际读取的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 任务中还存在的可读点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_DI_ReadDigitalOneU32(		// 将使能的线置为输入,读取单点采样数据(端口数据)(Read port data to the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPort,				// 端口号[0, 3]
		U32 nLineEn,			// 线号使能, Bit[31,0]分别控制Line[31,0]的使能, 0=禁止，1=使能
		U32* nData);				// 返回采样的数据， Bit[31,0]分别确定Line[31, 0]的数据位值

    BOOL ACTS3100_DI_ReadDigitalOneLines(		// 将使能的线置为输入,读取单点采样数据(多线数据)(Read port data to the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPort,				// 端口号[0, 3]
		U8 bLineEn[32],			// 线号使能, bLineEn[31,0]分别控制Line[31,0]的使能, 0=禁止，1=使能
		U8 bLineDataArray[32]);	// 返回采样的数据， nLineDataArray[31,0]分别确定Line[31, 0]的数据位值

    BOOL ACTS3100_DI_ReadDigitalOneLine(		// 将该线置为输入,读取单点采样数据(单线数据)(Read port data to the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPort,				// 端口号[0, 3]
		U32 nLine,				// 线号[0, 7]
		U8* bLineData);			// 返回单线的采样数据

    BOOL ACTS3100_DI_StopTask(					// 停止Port0采样任务
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

    BOOL ACTS3100_DI_ReleaseTask(				// 释放Port0采样任务
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

    BOOL ACTS3100_DI_VerifyParam(				// 校验DI工作参数(Verify Parameter),建议在初始化DI参数前调用此函数校验各参数合法性
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_DI_PARAM pDIParam);// 待校验的DI工作参数

    BOOL ACTS3100_DI_ResetParam(HANDLE hDevice, PACTS3100_DI_PARAM pDIParam); // 将当前DI参数复位至出厂值

	// ========================= DI辅助操作函数 =========================
    BOOL ACTS3100_DI_GetMainInfo(				// 获得DI的主要信息
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_DI_MAIN_INFO pMainInfo); // 获得DI主要信息

    BOOL ACTS3100_DI_GetRateInfo(				// 获得采样速率信息
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_DI_SAMP_RATE_INFO pRateInfo); // 采样速率信息

    BOOL ACTS3100_DIO_ReadbackDigitalOneU8(	// 回读各线的方向和值
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPort,				// 端口号[0, 3]
		U8 nLineDir[32],		// 返回线方向, nLineDir[0]=1表示Line0输出, =0:表示Line0为输入; nLineDir[1]=1表示Line0输出, =0:表示Line1为输入
		U8 bLineDataArray[32]);	// 多线数据缓冲，返回回读的数据

    BOOL ACTS3100_DIO_ReadbackDigitalOneU32(		// 回读各线的方向和值
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPort,				// 端口号[0, 3]
		U32* nLineDir,			// 返回线方向, Bit[31,0]分别返回Line[31,0]的方向, 0=输入，1=输出
		U32* nData);			// 端口数据， Bit[31,0]分别确定Line[31, 0]的数据位值

// ############################ DO数字量输出实现函数 ############################
    BOOL ACTS3100_DO_InitTask(					// 初始化DO生成任务(仅基于Port0)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_DO_PARAM pDOParam);

    BOOL ACTS3100_DO_GetParam(					// 取得DO工作参数表,可在DO_InitTask()前调用它取得默认参数表，然后修改必要的一些参数后就可以初始化任务了
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_DO_PARAM pDOParam);// 取得时钟输出允许, =0:表示禁止时钟输出,=1:表示允许时钟输出到指定的接线端

    BOOL ACTS3100_DO_SetDigitalDirU32(			// 将nLineEn指定的线配置为nDir指定的方向
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32    nPort,			// 指定操作的端口
		U32	   nLineEn,			// 线使能标志，bit[31:0]对应line[31:0]（实际线数量以板卡说明书为准，最多支持32线）
		U32    bOutputEn);		// 0：禁止输出，即为输入	1：允许输出

    BOOL ACTS3100_DO_GetStatus(				// 获取DO状态
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_DO_STATUS pDOStatus);// 取得DO各种状态

    BOOL ACTS3100_DO_WaitUntilTaskDone(		// Port0生成任务结束前等待,返回TRUE表示生成任务结束
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		F64 fTimeout);			// 用于等待的时间，单位：秒(S)

    BOOL ACTS3100_DO_StartTask(				// 启动Port0生成任务
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

    BOOL ACTS3100_DO_SendSoftTrig(				// 发送软件触发事件(Send Software Trigger),软件触发也叫强制触发
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

	BOOL ACTS3100_DO_WriteDigitalU8(			// 向生成任务中写入DO输出的二进制原码数据(Write port data to the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U8 nPortDataArray[],	// 写端口数据缓冲区,存放的是整个端口的多点数据，位宽8位,每个位分别对应各个线值.
		U32 nWriteSampsPerChan,	// 每个通道请求写入的点数(单位：点)
		U32* pSampsPerChanWritten,// 每个通道实际写入的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 返回当前可写入的采样点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

	BOOL ACTS3100_DO_WriteDigitalU16(			// 向生成任务中写入DO输出的二进制原码数据(Write port data to the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U16 nPortDataArray[],	// 写端口数据缓冲区,存放的是整个端口的多点数据，位宽8位,每个位分别对应各个线值.
		U32 nWriteSampsPerChan,	// 每个通道请求写入的点数(单位：点)
		U32* pSampsPerChanWritten,// 每个通道实际写入的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 返回当前可写入的采样点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

	BOOL ACTS3100_DO_WriteDigitalU32(			// 向生成任务中写入DO输出的二进制原码数据(Write port data to the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPortDataArray[],	// 写端口数据缓冲区,存放的是整个端口的多点数据，位宽8位,每个位分别对应各个线值.
		U32 nWriteSampsPerChan,	// 每个通道请求写入的点数(单位：点)
		U32* pSampsPerChanWritten,// 每个通道实际写入的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 返回当前可写入的采样点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_DO_WriteDigitalOneU32(		// 将使能的线置为输出,写入单点生成数据(端口数据)(Write port data to the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPort,				// 端口号[0, 3]
		U32 nLineEn,			// 线号使能, Bit[31,0]分别控制Line[31,0]的使能, 0=禁止，1=使能
		U32 nData);				// 输出的采样数据， Bit[31,0]分别确定Line[31, 0]的数据位值

    BOOL ACTS3100_DO_WriteDigitalOneLines(	// 将使能的线置为输出,写入单点生成数据(多线数据)(Write port data to the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPort,				// 端口号[0, 3]
		U8 bLineEn[32],			// 线号使能, bLineEn[31,0]分别控制Line[31,0]的使能, 0=禁止，1=使能
		U8 bLineDataArray[32]);	// 输出的采样数据， nLineDataArray[31,0]分别确定Line[31, 0]的数据位值

    BOOL ACTS3100_DO_WriteDigitalOneLine(		// 将该线置为输出,写入单点生成数据(单线数据)(Write port data to the task)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPort,				// 端口号[0, 3]
		U32 nLine,				// 线号[0, 7]
		U8 bLineData);			// 输出的单线的采样数据

    BOOL ACTS3100_DO_StopTask(					// 停止采样任务
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

    BOOL ACTS3100_DO_ReleaseTask(				// 释放DO任务
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

    BOOL ACTS3100_DO_VerifyParam(				// 校验DO工作参数(Verify Parameter),建议在初始化DO参数前调用此函数校验各参数合法性
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_DO_PARAM pDOParam);// 待校验的DO工作参数

    BOOL ACTS3100_DO_ResetParam(HANDLE hDevice, PACTS3100_DO_PARAM pDOParam); // 将当前DO参数复位至出厂值

	// ========================= DO辅助操作函数 =========================
    BOOL ACTS3100_DO_GetMainInfo(				// 获得DO的主要信息
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_DO_MAIN_INFO pMainInfo); // 获得DO主要信息

    BOOL ACTS3100_DO_GetRateInfo(				// 获得采样速率信息
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		PACTS3100_DO_SAMP_RATE_INFO pRateInfo); // 采样速率信息

// ############################ CI、CO计数器输入输出实现函数 ############################
///////////////////////////////////// 测量功能通道 ///////////////////////////////////
    BOOL ACTS3100_CI_CreateFreqChan(			// 创建频率测量通道, GATE:被测信号输入引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fMinVal,			// 最小值是换算后测量的预期最小值。单位：默认为Hz, 另支持时钟滴答计数
		F64 fMaxVal,			// 最大值是换算后测量的预期最大值。单位：默认为Hz, 另支持时钟滴答计数
		U32 nUnits,				// 换算后的单位是要被使用的单位。单位：频率赫兹或时钟滴答,它不仅决定着fMinVal和fMaxVal的单位类型，同时也决定着测量结果的单位类型。
		U32 nEdge,				// 被测信号的边沿，=0:下降沿测量，=1:上升沿测量
		U32 nMeasMethod,		// 测量方法,=0:低频测量, =1:高频测量, =2:宽范围测量
		F64 fMeasTime,			// 测量时间,单位：秒(S),仅当测量方法为高频测量(nMeasMethod=1)时有效,取值范围[0.00000002, 42.94967295]
		U32 nDivisor);			// 分频器，仅当测量方法为宽范围测量(nMeasMethod=2)时有效,取值范围[2, 4294967295]

    BOOL ACTS3100_CI_CreatePeriodChan(			// 创建周期测量通道，获得脉冲的周期时间。GATE:被测信号输入引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建	
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fMinVal,			// 最小值是换算后测量的预期最小值。单位：默认为秒, 另支持时钟滴答计数
		F64 fMaxVal,			// 最大值是换算后测量的预期最大值。单位：默认为秒, 另支持时钟滴答计数
		U32 nUnits,				// 换算后的单位是要被使用的单位。单位：时间秒或时钟滴答,它不仅决定着fMinVal和fMaxVal的单位类型，同时也决定着测量结果的单位类型
		U32 nEdge,				// 被测信号的边沿，=0:下降沿测量，=1:上升沿测量,详见上面的参数值常量定义
		U32 nMeasMethod,		// 测量方法,=0:低频测量, =1:高频测量, =2:宽范围测量
		F64 fMeasTime,			// 测量时间,单位：秒(S),仅当测量方法为高频测量(nMeasMethod=1)时有效,取值范围[0.00000002, 42.94967295]
		U32 nDivisor);			// 分频器，仅当测量方法为宽范围测量(nMeasMethod=2)时有效,取值范围[2, 4294967295]

    BOOL ACTS3100_CI_CreateCountEdgesChan(		// 创建边沿计数通道。 SRC:边沿计数的源输入引脚; GATE:控制是否暂停输入引脚; AUX:控制计数方向输入引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nEdge,				// 被测信号的边沿，=0:下降沿测量，=1:上升沿测量,详见上面的参数值常量定义
		U32 nInitialCount,		// 初始计数值, 取值范围为[0, 2^32-1]
		U32 nCountDirection);   // 计数方向, =0:减计数，=1:加计数, =2:外部控制(来自AUX),详见上面的参数值常量定义

    BOOL ACTS3100_CI_CreateTwoEdgeSepChan(		// 创建两边沿间隔测量通道(Two Edge Separation)，获得两个边沿之间的时间间隔, AUX:第一个有效边沿输入引脚; GATE:第二个有效边沿输入引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fMinVal,			// 最小值是换算后测量的预期最小值。单位：默认为秒, 另支持时钟滴答计数
		F64 fMaxVal,			// 最大值是换算后测量的预期最大值。单位：默认为秒, 另支持时钟滴答计数
		U32 nUnits,				// 换算后的单位是要被使用的单位。单位：时间秒或时钟滴答,它不仅决定着fMinVal和fMaxVal的单位类型，同时也决定着测量结果的单位类型。
		U32 nFirstEdge,			// 测量时的第一个信号(即启动信号,来自SRC)的边沿, =0:下降沿， =1:上升沿
		U32 nSecondEdge);		// 测量时的第二个信号(即停止信号,来自GATE)的边沿, =0:下降沿， =1:上升沿

    BOOL ACTS3100_CI_CreatePulseWidthChan(		// 创建脉冲宽度测量通道,获得脉冲的低电平或高电平的宽度(时间或时钟滴答计数), GATE:被测信号输入引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fMinVal,			// 最小值是换算后测量的预期最小值。单位：默认为秒, 另支持时钟滴答计数
		F64 fMaxVal,			// 最大值是换算后测量的预期最大值。单位：默认为秒, 另支持时钟滴答计数
		U32 nUnits,				// 换算后的单位是要被使用的单位。单位：时间秒或时钟滴答,它不仅决定着fMinVal和fMaxVal的单位类型，同时也决定着测量结果的单位类型。
		U32 nStartingEdge);		// 开始边沿, =0:测量脉冲的低电平时间(或滴答数), =1:测量脉冲的高电平时间(或滴答数) 

    BOOL ACTS3100_CI_CreateSemiPeriodChan(		// 创建半周期测量通道，半周期测量是对两个连续边沿的时间间隔进行测量，对于每个脉冲即有两个半周期存在，从上升沿开始测量。GATE:被测信号输入引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fMinVal,			// 最小值是换算后测量的预期最小值。单位：默认为秒, 另支持时钟滴答计数
		F64 fMaxVal,			// 最大值是换算后测量的预期最大值。单位：默认为秒, 另支持时钟滴答计数
		U32 nUnits);			// 换算后的单位是要被使用的单位。单位：时间秒或时钟滴答,它不仅决定着fMinVal和fMaxVal的单位类型，同时也决定着测量结果的单位类型。

    BOOL ACTS3100_CI_CreatePulseChanFreq(		// 创建脉冲测量通道(基于频率),获得脉冲的成对的频率和占空比。GATE:被测信号输入引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fMinVal,			// 最小值是换算后测量的预期最小值。单位：默认为赫兹(Hz)
		F64 fMaxVal,			// 最大值是换算后测量的预期最大值。单位：默认为Hz
		U32 nUnits);			// 单位：赫兹(Hz)(仅支持赫兹)

    BOOL ACTS3100_CI_CreatePulseChanTime(		// 创建脉冲测量通道(基于时间),获得脉冲的成对的高电平时间和低电平时间。GATE:被测信号输入引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fMinVal,			// 最小值是换算后测量的预期最小值。单位：默认为s, 它依赖于nUnits的指定
		F64 fMaxVal,			// 最大值是换算后测量的预期最大值。单位：默认为s, 它依赖于nUnits的指定
		U32 nUnits);			// 单位: 秒(S)(仅支持秒)

    BOOL ACTS3100_CI_CreatePulseChanTicks(		// 创建脉冲测量通道(基于时钟滴答),获得脉冲的成对的高电平的时钟滴数量和低电平的时钟滴数量。GATE:被测信号输入引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nSourceTerminal,	// 基准时钟源, 此参数需传实际值,操作同ACTS3100_AO_CH_PARAM的nSampleRange
		F64 fMinVal,			// 最小值是换算后测量的预期最小值。单位：个
		F64 fMaxVal);			// 最大值是换算后测量的预期最大值。单位：个

    BOOL ACTS3100_CI_CreateLinEncoderChan(		// 创建线性编码器测量通道。A:编码器通道A输入引脚; B:编码器通道B输入引脚; Z:编码器通道Z输入引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nDecodingType,		// 解码类型, 0=X1, 1=X2, 2=X4, 3=双脉冲，4＝单脉冲
		BOOL bZidxEnable,		// 启用Z索引指定了是否为测量启用z索引。=TRUE:启动, =FALSE:禁用，如果启用的话，信号来自Z输入引脚
		F64 fZidxVal,			// Z索引值, Z索引值指定当信号Z为高且信号A和信号B处于Z索引相位中指定的状态时测量的值，使用单位(nUnits)中指定的单位。
		U32 nZidxPhase,			// Z索引相位, 详见上面的常量定义
		U32 nUnits,				// 换算后的单位指定用于测量的单位。详见上面的常量定义
		F64 fDistPerPulse,		// 脉冲间隔是编码器生成的每个脉冲之间的距离。该值使用由单位(nUnits)所指定的单位。 
		F64 fInitialPos);		// 初始位置是测量开始时编码器的位置。该值的单位由单位(nUnits)指定。

    BOOL ACTS3100_CI_CreateAngEncoderChan(		// 创建角度编码器测量通道。A:编码器通道A输入引脚; B:编码器通道B输入引脚; Z:编码器通道Z输入引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nDecodingType,		// 解码类型, 0=X1, 1=X2, 2=X4, 3=双脉冲，4＝单脉冲
		BOOL bZidxEnable,		// 启用Z索引指定了是否为测量启用z索引。=TRUE:启动, =FALSE:禁用，如果启用的话，信号来自Z输入引脚
		F64 fZidxVal,			// Z索引值, Z索引值指定当信号Z为高且信号A和信号B处于Z索引相位中指定的状态时测量的值，使用单位(nUnits)中指定的单位。
		U32 nZidxPhase,			// Z索引相位, 详见上面的常量定义
		U32 nUnits,				// 换算后的单位指定用于测量的单位。详见上面的常量定义
		U32 nPulsesPerRev,		// 编码器每转一圈所生成脉冲的数量。该值是A信号或B信号上的脉冲数量，而不是A信号与B信号上总的脉冲数量。
		F64 fInitialAngle);		// 初始角是编码器在开始时的角度。该值的单位由单位(nUnits)指定。

    BOOL ACTS3100_CI_ReadCounterU32(			// 读取缓冲测量结果(整型数据),主要应用于有限点和连续等缓冲采样中
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nBinArray[],		// 数据缓冲，装载采样的整型数据
		U32 nReadSampsPerChan,	// 每通道请求读取的点数(单位：点)
		U32* pSampsPerChanRead,	// 返回每通道实际读取的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 任务中还存在的可读点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_CI_ReadCounterF64(			// 读取缓冲测量结果(浮点数据),主要应用于有限点和连续等缓冲采样中
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fAnlgArray[],		// 数据缓冲，装载采样的浮点数据
		U32 nReadSampsPerChan,	// 每通道请求读取的点数(单位：点)
		U32* pSampsPerChanRead,	// 返回每通道实际读取的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 任务中还存在的可读点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_CI_ReadCounterScalarU32(		// 读取经过换算后的计数器结果数据(原码数据)，比如脉冲计数结果,主要应用于单点采样中(超时返回FALSE)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32* pValue,			// 返回经过换算后的单点测量数据
		U32* pReserved,			// 保留(仅在半周期测量中返回低电平的时间宽度)
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_CI_ReadCounterScalarF64(		// 读取经过换算后的计数器结果数据(物理量)，比如频率、周期测量结果,主要应用于单点采样中(超时返回FALSE)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CI物理通道号[0, 1]
		F64* pValue,			// 返回经过换算后单点测量结果数据
		F64* pReserved,			// 保留(仅在半周期测量中返回低电平的时间宽度)
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_CI_ReadCtrFreq(				// 读取缓冲测量结果(频率和占空比),主要应用于有限点和连续等缓冲采样中
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fFreqArray[],		// 频率缓冲区,单位由函数CI_CreatePulseChanFreq()的参数nUnits决定
		F64 fDutyCycleArray[],	// 占空比缓冲区，取值范围(0.0, 1.0),是脉冲的高电平时间除以脉冲周期的结果
		U32 nReadSampsPerChan,	// 每通道请求读取的点数(单位：点)
		U32* pSampsPerChanRead,	// 返回每通道实际读取的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 任务中还存在的可读点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_CI_ReadCtrTime(				// 读取缓冲测量结果(高电平和低电平时间),主要应用于有限点和连续等缓冲采样中
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fHighTimeArray[],	// 高电平时间缓冲区,单位由函数CI_CreatePulseChanTime()的参数nUnits决定
		F64 fLowTimeArray[],	// 低电平时间缓冲区，单位由函数CI_CreatePulseChanTime()的参数nUnits决定
		U32 nReadSampsPerChan,	// 每通道请求读取的点数(单位：点)
		U32* pSampsPerChanRead,	// 返回每通道实际读取的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 任务中还存在的可读点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_CI_ReadCtrTicks(				// 读取缓冲测量结果(高电平和低电平时钟滴答),主要应用于有限点和连续等缓冲采样中
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nHighTicksArray[],	// 高电平滴答缓冲区
		U32 nLowTicksArray[],	// 低电平滴答缓冲区
		U32 nReadSampsPerChan,	// 每通道请求读取的点数(单位：点)
		U32* pSampsPerChanRead,	// 返回每通道实际读取的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 任务中还存在的可读点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_CI_ReadCtrFreqScalar(		// 读取经过换算后的计数器结果数据(频率和占空比)(超时返回FALSE)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CI物理通道号[0, 3]
		F64* pFrequency,		// 返回单点的频率值,单位由函数CI_CreatePulseChanFreq()的参数nUnits决定
		F64* pDutyCycle,		// 返回单点的占空比，取值范围(0.0, 1.0),是脉冲的高电平时间除以脉冲周期的结果
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_CI_ReadCtrTimeScalar(		// 读取经过换算后的计数器结果数据((高电平和低电平时钟滴答))(超时返回FALSE)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CI物理通道号[0, 3]
		F64* pHighTime,			// 返回单点的高电平时间,单位由函数CI_CreatePulseChanTime()的参数nUnits决定
		F64* pLowTime,			// 返回单点的低电平时间,单位由函数CI_CreatePulseChanTime()的参数nUnits决定
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_CI_ReadCtrTicksScalar(		// 读取经过换算后的计数器结果数据(高电平和低电平时钟滴答)(超时返回FALSE)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CI物理通道号[0, 3]
		U32* pHighTicks,		// 返回单点的高电平滴答
		U32* pLowTicks,			// 返回单点的低电平滴答
		F64 fTimeout);			// 超时时间，单位：秒(S), 大于0.0表示指定超时时间且等待，若完成，等于0.0表示不使用超时等待立即执行并返回，小于0.0表示不指定超时间且等待直到请求被执行完成后返回

    BOOL ACTS3100_CI_SetDigitalFilter(			// 设置CI数字滤波
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nSignal,			// 信号选择，0=Src，1=Gate, 2=Aux,详见前面的常量定义
		F64 fFilter,			// Src滤波值,可由nUnits参数指定其单位类型,若等于0.0则表示禁止数字滤波
		U32 nUnits);			// 指定滤波值fFilter的单位。详见上面的常量定义


    BOOL ACTS3100_CI_SetCountEdgesCountResetParam(		// 设置CI边沿计数复位参数
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		BOOL bResetEnable,		// 重置使能：0=Disable, 1=Enable
		U32 nActiveEdge,		// 有效边沿：0=Falling edge, 1=Rising edge
		U32 nResetCount,		// 复位计数值，32Bit有效
		U32 nResetTerm,			// 复位信号接入端子，, 详见(DI DO CTR 采样时钟、开始触发源、暂停触发源、计数复位信号源使用的选项)
		F64 fDigFltrMinPulseWidth);	// 数字滤波最小脉冲宽度,单位：秒(S)，取值[0,42.94967295]

    BOOL ACTS3100_CI_GetCountEdgesCountResetParam(		// 获得CI边沿计数复位参数
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		BOOL* pResetEnable,		// 重置使能：0=Disable, 1=Enable, =NULL可以忽略此参数
		U32* pActiveEdge,		// 有效边沿：0=Falling edge, 1=Rising edge, =NULL可以忽略此参数
		U32* pResetCount,		// 复位计数值，32Bit有效, =NULL可以忽略此参数
		U32* pResetTerm,		// 复位信号接入端子，详见(DI DO CTR 采样时钟、开始触发源、暂停触发源、计数复位信号源使用的选项)
		F64* pDigFltrMinPulseWidth);// 数字滤波最小脉冲宽度,单位：秒(S), =NULL可以忽略此参数

    BOOL ACTS3100_CO_CreatePulseChanFreq(		// 创建脉冲频率生成通道。OUT:脉冲输出引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nUnits,				// 指定参数fFreq的单位，默认为Hz
		U32 nIdleState,			// 空闲时的状态，即在StartTask()前和StopTask()后的状态，=0:低电平, =1:高电平
		F64 fInitialDelay,		// 初始延迟时间，即在StartTask()开始往后到输出脉冲之间的时间值(单位：秒)
		F64 fFreq,				// 生成脉冲的频率
		F64 fDutyCycle);		// 生成脉冲的占空比，取值范围[0.01-0.99]

    BOOL ACTS3100_CO_CreatePulseChanTime(		// 创建脉冲时间生成通道。OUT:脉冲输出引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nUnits,				// 指定参数fLowTime和fHighTime的单位，默认为:秒
		U32 nIdleState,			// 空闲时的状态，即在StartTask()前和StopTask()后的状态，=0:低电平, =1:高电平
		F64 fInitialDelay,		// 初始延迟时间，即在StartTask()开始往后到输出脉冲之间的时间值,单位：秒
		F64 fLowTime,			// 脉冲低电平的时间,时间单位由nUnits指定
		F64 fHighTime);			// 脉冲高电平的时间,时间单位由nUnits指定

    BOOL ACTS3100_CO_CreatePulseChanTicks(		// 创建脉冲滴答生成通道。OUT:脉冲输出引脚
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nSourceTerminal,	// 基准时钟源, 此参数需传实际值,操作同ACTS3100_AO_CH_PARAM的nSampleRange
		U32 nIdleState,			// 空闲时的状态，即在StartTask()前和StopTask()后的状态，=0:低电平, =1:高电平
		U32 nInitialDelay,		// 初始延迟滴答，即在StartTask()开始往后到输出脉冲之间的滴答值
		U32 nLowTicks,			// 低电平的时钟滴答计数
		U32 nHighTicks);		// 高电平的时钟滴答计数

    BOOL ACTS3100_CO_WriteFreq(				// 向生成任务中写入可变频率数据序列(Write variable frequency data to the task),事先得由CO_CreatePulseChanFreq()创建频率输出通道
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fFreqArray[],		// 频率数据缓冲区,存放若干点的频率数据,单位由函数CO_CreatePulseChanFreq()的参数nUnits指定
		F64 fDutyCycleArray[],	// 占空比数据缓冲区,存放若干点的占空比数据，取值范围[0.01-0.99]
		U32 nWriteSampsPerChan,	// 每通道请求写入的点数(单位：样点)
		U32* pSampsPerChanWritten,// 返回每通道实际写入的点数(单位：样点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 返回当前可写入的采样点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_CO_WriteTime(				// 向生成任务中写入可变时间数据序列(Write variable time data to the task),事先得由CO_CreatePulseChanTime()创建时间输出通道
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fHighTimeArray[],	// 高电平时间数据缓冲区,存放若干点的时间数据,单位由函数CO_CreatePulseChanTime()的参数nUnits指定
		F64 fLowTimeArray[],	// 低电平时间数据缓冲区,存放若干点的时间数据,单位由函数CO_CreatePulseChanTime()的参数nUnits指定
		U32 nWriteSampsPerChan,	// 每通道请求写入的点数(单位：点)
		U32* pSampsPerChanWritten,// 返回每通道实际写入的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 返回当前可写入的采样点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_CO_WriteTicks(				// 向生成任务中写入可变时钟滴答数据序列(Write variable ticks data to the task),事先得由CO_CreatePulseChanTicks()创建时钟滴答输出通道
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nHighTicksArray[],	// 高电平的时钟滴答数据缓冲区,存放若干点的时钟滴答数据
		U32 nLowTicksArray[],	// 低电平的时钟滴答数据缓冲区,存放若干点的时钟滴答数据
		U32 nWriteSampsPerChan,	// 每通道请求写入的点数(单位：点)
		U32* pSampsPerChanWritten,// 返回每通道实际写入的点数(单位：点), =NULL,表示无须返回
		U32* pAvailSampsPerChan,// 返回当前可写入的采样点数, =NULL,表示无须返回
		F64 fTimeout);			// 超时时间，单位：秒(S)

    BOOL ACTS3100_CO_GetCountVal(				// 取得CO的当前输出计数值
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32* pCountVal);		// 返回当前CO的输出计数值

    BOOL ACTS3100_CO_GetOutputState(			// 取得CO当前的输出状态
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32* pOutputState);		// 返回CO当前输出状态, 0=Low, 1=High

    BOOL ACTS3100_CO_SetEnableInitialDelayOnRetrigger(	// 设置在触发中是否有延时状态
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		BOOL bEnableInitialDelayOnRetrigger);// 是否允许在触发后延时

    BOOL ACTS3100_CTR_CfgSampClkTiming(		// 配置采样时钟及采样模式(显式时钟)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nSampClkSource,		// 采样时钟源,详见上面的nSampClkSource选项定义
		F64 fSampleRate,		// 采样速率,单位：Hz
		U32 nActiveEdge,		// 有效边沿,0=下降沿,1=上升沿
		U32 nSampleMode,		// 采样模式
		U32 nSampsPerChan);		// 每通道采样点数

    BOOL ACTS3100_CTR_CfgImplicitTiming(		// 配置隐式时钟(无须指定时钟源和采样速率,如半周期测量、频率测量,内部使用固定的基准时钟)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		I32 nSampleMode,		// 采样模式
		U64 nSampsPerChan);		// 每通道采样点数

    BOOL ACTS3100_CTR_WaitUntilTaskDone(		// 采样任务结束前等待,返回TRUE表示采样任务结束
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64 fTimeout);			// 用于等待的时间，单位：秒(S)

    BOOL ACTS3100_CTR_DisableStartTrig(		// 禁止开始触发
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel);			// CTR物理通道号[0, 1]

    BOOL ACTS3100_CTR_CfgDigEdgeStartTrig(		// 配置开始触发(数字边沿)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nTriggerSource,		// 数字触发源, 详见(DI DO CTR 采样时钟、开始触发源、暂停触发源、计数复位信号源使用的选项)
		U32 nTriggerEdge,		// 数字触发边沿
		F64 fTriggerSens);		// 触发敏灵度,单位：秒(S)，取值[0,42.94967295]);

    BOOL ACTS3100_CTR_SetStartTrigRetriggerable(// 允许开始触发的重触发
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		BOOL bRetriggerable);	// 允许重触发, =FALSE:禁止重触发(默认), =TRUE:允许重触发

    BOOL ACTS3100_CTR_DisablePauseTrig(		// 禁止暂停触发
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel);			// CTR物理通道号[0, 1]

    BOOL ACTS3100_CTR_CfgDigLvlPauseTrig(		// 配置暂停触发(数字边沿)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		U32 nTriggerSource,		// 数字触发源, 详见(DI DO CTR 采样时钟、开始触发源、暂停触发源、计数复位信号源使用的选项)
		U32 nTriggerWhen,		// 数字触发时机，0=低电平暂停触发，1=高电平暂停触发
		F64 fTriggerSens);		// 触发敏灵度,单位：秒(S)，取值[0,42.94967295]);

    BOOL ACTS3100_CTR_SendSoftTrig(			// 发送软件触发事件(Send Software Trigger),软件触发也叫强制触发
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel);			// CTR物理通道号[0, 1]

    BOOL ACTS3100_CTR_SetExportedOutEventParam(// 设置CTR导出输出事件参数(即在CI边沿计数和角度线性测量溢出时输出状态至OUT)
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		BOOL bEnable,			// 导出输出事件使能：0=Disable, 1=Enable
		U32 nBehavior,			// 导出行为，0=Pulse(脉冲)，1=Toggle(反转)
		U32 nPolarity,			// 脉冲极性，0=Low(低)，1=High(高),当nBehavior=Pulse时该参数有效
		U32 nIdleState);		// 空闲状态，0=Low(低)，1=High(高),当nBehavior=Toggle时该参数有效

    BOOL ACTS3100_CTR_GetExportedOutEventParam(// 获取CTR导出输出事件参数
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		BOOL* pEnable,			// 导出输出事件使能：0=Disable, 1=Enable,=NULL可以忽略此参数
		U32* pBehavior,			// 导出行为，0=Pulse(脉冲)，1=Toggle(反转),=NULL可以忽略此参数
		U32* pPolarity,			// 脉冲极性，0=Low(低)，1=High(高),=NULL可以忽略此参数
		U32* pIdleState);		// 空闲状态，0=Low(低)，1=High(高),=NULL可以忽略此参数

    BOOL ACTS3100_CTR_StartTask(				// 启动采样任务
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel);			// CTR物理通道号[0, 1]

    BOOL ACTS3100_CTR_StopTask(				// 停止采样任务
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel);			// CTR物理通道号[0, 1]

    BOOL ACTS3100_CTR_ReleaseTask(				// 释放采样任务
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel);			// CTR物理通道号[0, 1]

	// ========================= CI辅助操作函数 =========================
    BOOL ACTS3100_CTR_GetTimeBaseRate(				// 获得CI基准频率
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nChannel,			// CTR物理通道号[0, 1]
		F64* fTimeBaseRate);	// 返回基准频率,100M、100K、0，0表示选择为外部时基


	// ################################ 其它函数 ################################

	UINT64 GetTickCount();
	int kbhit();
	

#ifdef __cplusplus
}
#endif

#endif // _ACTS3100_DEVICE_

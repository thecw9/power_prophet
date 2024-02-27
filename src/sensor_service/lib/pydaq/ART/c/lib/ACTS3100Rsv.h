// 保留的头文件, 这是为用户和厂商提供的一种特殊的、增值的,额外的服务
// 绝大多数情况下,我们建议您优先使用ACTS3100.h中的接口函数(RSV=Reserve)
// 本头文件中的内容,我们不提供额外的技术支持

#ifndef _ACTS3100RSV_DEVICE_
#define _ACTS3100RSV_DEVICE_

#include "ACTS3100.h"

// 函数DIO_SetPowerOnState()的参数nState所用的状态类型
#define ACTS3100_DIO_POWERUPSTATE_DI			0 // 上电配置为输入
#define ACTS3100_DIO_POWERUPSTATE_LOW		1 // 上电配置为输出低
#define ACTS3100_DIO_POWERUPSTATE_HIGH		2 // 上电配置为输出高


#ifdef __cplusplus
extern "C" {
#endif

	BOOL ACTS3100_DEV_GetCalDate(					// 校准日期,未校准时返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U64* pCalDate);			// 返回最后校准日期

// ################################ AI校准函数 ################################
	BOOL ACTS3100_AI_IsCaled(						// AI是否已被自我校准过, 如果已校准过，则返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		BOOL* pCaled);			// 是否已经被校准，=TRUE:表示已经被校准过, =FALSE:表示未被校准过

	BOOL ACTS3100_AI_SelfCal(						// AI自我校准, 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建

// ################################ AO校准函数 ################################
	BOOL ACTS3100_AO_IsCaled(						// AO是否已被自我校准过, 如果已校准过，则返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		BOOL* pCaled);			// 是否已经被校准，=TRUE:表示已经被校准过, =FALSE:表示未被校准过

	BOOL ACTS3100_AO_SelfCal(						// AO自我校准, 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice);		// 设备对象句柄,它由DEV_Create()函数创建


// ############################# DIO辅助函数 ##############################
	BOOL ACTS3100_DIO_SetPowerOnState(				// 设置上电状态
		HANDLE hDevice,				// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPort,					// 端口号, 取值范围为[0, 3]
		U8 nState[32]);				// 状态值，详见上述定义, nState[0]表示line0...	

	BOOL ACTS3100_DIO_GetPowerOnState(				// 获取上电状态
		HANDLE hDevice,				// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPort,					// 端口号, 取值范围为[0, 3]
		U8 nState[32]);				// 状态值，详见上述定义, nState[0]表示line0...


// ################################ 设备信息函数 ################################
	BOOL ACTS3100_DEV_GetPhysIdx(					// 获得物理序号, 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32* pPhysIdx);			// 返回的物理序号

	BOOL ACTS3100_DEV_SetPhysIdx(					// 设置物理序号, 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nPhysIdx);			// 物理序号

	BOOL ACTS3100_DEV_GetVersion(					// 获得设备版本信息, 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32* pDllVer,			// 返回的动态库(.dll)版本号
		U32* pDriverVer,		// 返回的驱动(.sys)版本号
		U32* pFirmwareVer);		// 返回的固件版本号

	BOOL ACTS3100_DEV_GetSerialNum(				// 获得序列号, 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32* pSerialNum);		// 返回的序列号

	BOOL ACTS3100_DEV_GetUserPID(					// 获得用户产品ID号(User Product Identification), 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32* pUserPID);			// 返回的用户产品ID

	BOOL ACTS3100_DEV_SetUserPID(					// 设置用户产品ID号(User Product Identification), 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nUserPID);			// 用户产品ID

	BOOL ACTS3100_DEV_SetPower5VState(			// 设置+5V电源输出状态, 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		BOOL bEnable);			// 允许输出, =TRUE:表示允许输出, =FALSE:表示禁止输出

	BOOL ACTS3100_DEV_GetPower5VState(			// 获取+5V电源输出状态, 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		BOOL* pEnabled,			// 是否已允许输出, =TRUE:表示已允许输出, =FALSE:表示已禁止输出
		BOOL* pOverload);		// 是否过载, =TRUE:表示过载, =FALSE:表示未过载（正常）

	BOOL ACTS3100_DEV_Set5VPowerOnState(			// 设置+5V电源上电状态, 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		BOOL bEnable);			// 上电输出, =TRUE:表示上电输出, =FALSE:表示禁止上电输出

	BOOL ACTS3100_DEV_Get5VPowerOnState(			// 获取+5V电源上电状态, 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		BOOL* pEnabled);		// 上电输出, =TRUE:表示上电输出, =FALSE:表示禁止上电输出


// ################################ 密码函数 ################################
	BOOL ACTS3100_SetPassword(HANDLE hDevice, U32 nPassword);

	// ################################ 设备信息函数 ################################
	BOOL ACTS3100_DEV_SetSerialNum(				// 设置序列号, 成功时返回TRUE,否则返回FALSE
		HANDLE hDevice,			// 设备对象句柄,它由DEV_Create()函数创建
		U32 nSerialNum);		// 序列号



#ifdef __cplusplus
}
#endif

#endif // _ACTS3100RSV_DEVICE_
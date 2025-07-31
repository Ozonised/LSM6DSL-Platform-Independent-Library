/*
 * lsm6dsl.h
 *
 *  Created on: Jul 28, 2025
 *      Author: farhan
 */

#ifndef LSM6DSL_H_
#define LSM6DSL_H_

#include <stdint.h>
#include <stddef.h>
#include "lsm6dsl_port.h"

typedef LSM6DSL_INTF_RET_TYPE (*LSM6DSL_ReadFuncPtr)(void *hinterface,
		uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len);

typedef LSM6DSL_INTF_RET_TYPE (*LSM6DSL_WriteFuncPtr)(void *hinterface,
		uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len);

typedef void (*LSM6DSL_DelayMsFuncPtr)(void *hInterface, uint32_t ms);

typedef struct LSM6DSL_DEV
{
	void *hInterface;				// Interface handle for I2C
	LSM6DSL_ReadFuncPtr read; 		// Bus read function pointer
	LSM6DSL_WriteFuncPtr write;		// Bus write function pointer
	LSM6DSL_DelayMsFuncPtr delayMs; // delay in millisecond function pointer
	uint8_t chipAddr;				// IMU address

} LSM6DSL;

enum LSM6DSL_XL_FS_Range
{
	XL_FS_2G = 0, XL_FS_16G, XL_FS_4G, XL_FS_8G
};

enum LSM6DSL_XL_ODR
{
	XL_ODR_POWER_DOWN = 0,
	XL_ODR_12_5Hz,
	XL_ODR_26Hz,
	XL_ODR_52Hz,
	XL_ODR_104Hz,
	XL_ODR_208Hz,
	XL_ODR_416Hz,
	XL_ODR_833Hz,
	XL_ODR_1_66kHz,
	XL_ODR_3_33kHz,
	XL_ODR_6_66kHz,
	XL_ODR_1_6Hz
};

enum LSM6DSL_XL_G_PowerMode
{
	POWER_DOWN = 0, DEFAULT, HIGH_PERFORMANCE
};

enum LSM6DSL_G_FS_Range
{
	G_FS_250DPS = 0, G_FS_500DPS, G_FS_1000DPS, G_FS_2000DPS, G_FS_125DPS
};

enum LSM6DSL_G_ODR
{
	G_ODR_POWER_DOWN = 0,
	G_ODR_12_5Hz,
	G_ODR_26Hz,
	G_ODR_52Hz,
	G_ODR_104Hz,
	G_ODR_208Hz,
	G_ODR_416Hz,
	G_ODR_833Hz,
	G_ODR_1_66kHz,
	G_ODR_3_33kHz,
	G_ODR_6_66kHz,
};

/*
 * @brief Checks if the LSM6DSL is present on the bus
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS device is present
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE absent, error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_IsPresent(LSM6DSL *dev);

/*
 * @brief Sets Accelerometers ODR
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] m one of LSM6DSL_XL_ODR values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelODR(LSM6DSL *dev, enum LSM6DSL_XL_ODR m);

/*
 * @brief Sets Accelerometers Full Scale Range
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] r one of LSM6DSL_XL_FS_Range values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelFSRange(LSM6DSL *dev,
		enum LSM6DSL_XL_FS_Range r);

/*
 * @brief Sets Gyros ODR
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] m one of enum LSM6DSL_G_ODR values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_setGyroODR(LSM6DSL *dev, enum LSM6DSL_G_ODR m);

/*
 * @brief Sets Gyro Full Scale Range
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] r one of LSM6DSL_G_FS_Range values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_setGyroFSRange(LSM6DSL *dev,
		enum LSM6DSL_G_FS_Range r);

#endif /* LSM6DSL_LSM6DSL_H_ */

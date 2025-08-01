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

enum LSM6DSL_XL_G_HM_MODE
{
	XL_G_HM_MODE_ON = 0, XL_G_HM_MODE_OFF
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

enum LSM6DSL_INT1_Sources
{
	INT1_DRDY_NONE = 0,
	INT1_DRDY_XL = (1 << 0),
	INT1_DRDY_G = (1 << 1),
	INT1_BOOT = (1 << 2),
	INT1_FTH = (1 << 3),
	INT1_FIFO_OVR = (1 << 4),
	INT1_FULL_FLAG = (1 << 5),
	INT1_SIGN_MOT = (1 << 6),
	INT1_STEP_DETECTOR = (1 << 7),
};

enum LSM6DSL_INT2_Sources
{
	INT2_DRDY_NONE = 0,
	INT2_DRDY_XL = (1 << 0),
	INT2_DRDY_G = (1 << 1),
	INT2_DRDY_TEMP = (1 << 2),
	INT2_FTH = (1 << 3),
	INT2_FIFO_OVR = (1 << 4),
	INT2_FULL_FLAG = (1 << 5),
	INT2_STEP_COUNT_OV = (1 << 6),
	INT2_STEP_DELTA = (1 << 7),
};

struct AccelData
{
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
};

struct GyroData
{
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
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
 * @brief Enable/Disable INT1 IRQ sources
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] s values from LSM6DSL_INT1_Sources
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @note This function overwrites the INT1_CTRL reg with value of s.
 * 		 To enable multiple sources the values of LSM6DSL_INT1_Sources should be ORed.
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_INT1SourceConfig(LSM6DSL *dev,
		enum LSM6DSL_INT1_Sources s);

/*
 * @brief Enable/Disable INT2 IRQ sources
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] s values from LSM6DSL_INT2_Sources
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @note This function overwrites the INT2_CTRL reg with value of s.
 * 	   	 To enable multiple sources the values of LSM6DSL_INT2_Sources should be ORed.
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_INT2SourceConfig(LSM6DSL *dev,
		enum LSM6DSL_INT2_Sources s);

/*
 * @brief Maps IRQs on INT2 pin to INT1 pin
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] en 1 to enable, 0 to disable
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_setAllIRQonINT1(LSM6DSL *dev, uint8_t en);

/*
 * @brief Enable/Disable block update mode(BDU)
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] m 1 to enable, 0 to disable
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_toggleBlockDataUpdate(LSM6DSL *dev, uint8_t m);

/*
 * @brief Sets Accelerometers ODR
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] m one of LSM6DSL_XL_ODR values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @see Table 12 & 13 of AN5040 for number of samples to discard.
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
 * @brief Checks if accelerometer data is available
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS available
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE unavailable, error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_isAccelDataAvailabe(LSM6DSL *dev);

/*
 * @brief Enable/disable accelerometers high performance mode
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] m one of LSM6DSL_XL_G_HM_MODE values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @see Table 12 & 13 of AN5040 for number of samples to discard.
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelHighPerfMode(LSM6DSL *dev,
		enum LSM6DSL_XL_G_HM_MODE m);

/*
 * @brief Read accelerometer
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] xl pointer to AccelData structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS reading successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_readAccelData(LSM6DSL *dev, struct AccelData *xl);

/*
 * @brief Sets Gyros ODR
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] m one of enum LSM6DSL_G_ODR values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @see Table 14, 15 & 16 of AN5040 for number of samples to discard.
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

/*
 * @brief Checks if gyroscope data is available
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS available
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE unavailable, error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_isGyroDataAvailabe(LSM6DSL *dev);

/*
 * @brief Enable/disable gyroscope high performance mode
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] m one of LSM6DSL_XL_G_HM_MODE values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @see Table 14, 15 & 16 of AN5040 for number of samples to discard.
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_setGyroHighPerfMode(LSM6DSL *dev,
		enum LSM6DSL_XL_G_HM_MODE m);

/*
 * @brief Read gyroscope
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] gy pointer to GyroData structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS reading successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_readGyroData(LSM6DSL *dev, struct GyroData *gy);

/*
 * @brief Checks if temperature data is available
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS available
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE unavailable, error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_isTempDataAvailabe(LSM6DSL *dev);

#endif /* LSM6DSL_LSM6DSL_H_ */

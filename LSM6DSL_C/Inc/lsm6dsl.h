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
#include <string.h>
#include <stdlib.h>
#include "lsm6dsl_port.h"

typedef LSM6DSL_INTF_RET_TYPE (*LSM6DSL_ReadFuncPtr)(void *hinterface, uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len);

typedef LSM6DSL_INTF_RET_TYPE (*LSM6DSL_WriteFuncPtr)(void *hinterface, uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len);

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
	LSM6DSL_XL_FS_2G = 0, LSM6DSL_XL_FS_16G, LSM6DSL_XL_FS_4G, LSM6DSL_XL_FS_8G
};

enum LSM6DSL_XL_FS_Sensitivity
{
	// divide the values by 1000 to get the actual value as in the datasheet
	LSM6DSL_XL_FS_2G_SENS = 61,
	LSM6DSL_XL_FS_4G_SENS = 122,
	LSM6DSL_XL_FS_8G_SENS = 244,
	LSM6DSL_XL_FS_16G_SENS = 488
};

enum LSM6DSL_XL_ODR
{
	LSM6DSL_XL_ODR_POWER_DOWN = 0,
	LSM6DSL_XL_ODR_12_5Hz,
	LSM6DSL_XL_ODR_26Hz,
	LSM6DSL_XL_ODR_52Hz,
	LSM6DSL_XL_ODR_104Hz,
	LSM6DSL_XL_ODR_208Hz,
	LSM6DSL_XL_ODR_416Hz,
	LSM6DSL_XL_ODR_833Hz,
	LSM6DSL_XL_ODR_1_66kHz,
	LSM6DSL_XL_ODR_3_33kHz,
	LSM6DSL_XL_ODR_6_66kHz,
	LSM6DSL_XL_ODR_1_6Hz
};

enum LSM6DSL_XL_LPF_ODR
{
	LSM6DSL_XL_LPF_ODR_2 = 0,
	LSM6DSL_XL_LPF_ODR_4,
	LSM6DSL_XL_LPF_ODR_50,
	LSM6DSL_XL_LPF_ODR_100,
	LSM6DSL_XL_LPF_ODR_9,
	LSM6DSL_XL_LPF_ODR_400,
};

enum LSM6DSL_XL_HPF_ODR
{
	LSM6DSL_XL_HPF_ODR_4 = 0,
	LSM6DSL_XL_HPF_ODR_100,
	LSM6DSL_XL_HPF_ODR_9,
	LSM6DSL_XL_HPF_ODR_400,
};

enum LSM6DSL_XL_G_HM_MODE
{
	LSM6DSL_XL_G_HM_MODE_ON = 0, LSM6DSL_XL_G_HM_MODE_OFF
};

enum LSM6DSL_G_FS_Range
{
	LSM6DSL_G_FS_250DPS = 0,
	LSM6DSL_G_FS_500DPS,
	LSM6DSL_G_FS_1000DPS,
	LSM6DSL_G_FS_2000DPS,
	LSM6DSL_G_FS_125DPS
};

enum LSM6DSL_G_FS_Sensitivity
{
	// divide the values by 1000 to get the actual value as in the datasheet
	LSM6DSL_G_FS_125_SENS = 4375,
	LSM6DSL_G_FS_250_SENS = 8750,
	LSM6DSL_G_FS_500_SENS = 17500,
	LSM6DSL_G_FS_1000_SENS = 35000,
	LSM6DSL_G_FS_2000_SENS = 70000
};

enum LSM6DSL_G_ODR
{
	LSM6DSL_G_ODR_POWER_DOWN = 0,
	LSM6DSL_G_ODR_12_5Hz,
	LSM6DSL_G_ODR_26Hz,
	LSM6DSL_G_ODR_52Hz,
	LSM6DSL_G_ODR_104Hz,
	LSM6DSL_G_ODR_208Hz,
	LSM6DSL_G_ODR_416Hz,
	LSM6DSL_G_ODR_833Hz,
	LSM6DSL_G_ODR_1_66kHz,
	LSM6DSL_G_ODR_3_33kHz,
	LSM6DSL_G_ODR_6_66kHz,
};

enum LSM6DSL_INT1_Sources
{
	LSM6DSL_INT1_DRDY_NONE = 0,
	LSM6DSL_INT1_DRDY_XL = (1 << 0),
	LSM6DSL_INT1_DRDY_G = (1 << 1),
	LSM6DSL_INT1_BOOT = (1 << 2),
	LSM6DSL_INT1_FTH = (1 << 3),
	LSM6DSL_INT1_FIFO_OVR = (1 << 4),
	LSM6DSL_INT1_FULL_FLAG = (1 << 5),
	LSM6DSL_INT1_SIGN_MOT = (1 << 6),
	LSM6DSL_INT1_STEP_DETECTOR = (1 << 7),
};

enum LSM6DSL_INT2_Sources
{
	LSM6DSL_INT2_DRDY_NONE = 0,
	LSM6DSL_INT2_DRDY_XL = (1 << 0),
	LSM6DSL_INT2_DRDY_G = (1 << 1),
	LSM6DSL_INT2_DRDY_TEMP = (1 << 2),
	LSM6DSL_INT2_FTH = (1 << 3),
	LSM6DSL_INT2_FIFO_OVR = (1 << 4),
	LSM6DSL_INT2_FULL_FLAG = (1 << 5),
	LSM6DSL_INT2_STEP_COUNT_OV = (1 << 6),
	LSM6DSL_INT2_STEP_DELTA = (1 << 7),
};

typedef struct
{
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
} LSM6DSL_AccelData;

typedef struct
{
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
} LSM6DSL_GyroData;

enum LSM6DSL_ENDIAN
{
	LSM6DSL_LITTLE_ENDIAN = 0, LSM6DSL_BIG_ENDIAN
};

typedef struct
{
	float celsius;
	int16_t regData;
} LSM6DSL_TempData;

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
 * @brief Set imu's data registers endianess
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] end one of LSM6DSL_ENDIAN values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @see section 4.5 of AN5040
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_setBigLittleEndian(LSM6DSL *dev, enum LSM6DSL_ENDIAN end);

/*
 * @brief Initialize LSM6DSL structure and configure imu's endianess
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] interfacePtr pointer to the interface handle
 * @param[in] imuAddr LSM6DSL I2c address
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_Init(LSM6DSL *dev, void *interfacePtr, uint8_t imuAddr);

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
LSM6DSL_INTF_RET_TYPE LSM6DSL_INT1SourceConfig(LSM6DSL *dev, enum LSM6DSL_INT1_Sources s);

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
LSM6DSL_INTF_RET_TYPE LSM6DSL_INT2SourceConfig(LSM6DSL *dev, enum LSM6DSL_INT2_Sources s);

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
 * @brief Enable/Disable data ready (DRDY) mask functionality
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] m 1 to enable, 0 to disable
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @note Data ready mask only works for accelerometer LPF1 and gyroscope's LPF2 digital filters.
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_toggleDataReadyMask(LSM6DSL *dev, uint8_t m);

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
LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelFSRange(LSM6DSL *dev, enum LSM6DSL_XL_FS_Range r);

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
LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelHighPerfMode(LSM6DSL *dev, enum LSM6DSL_XL_G_HM_MODE m);

/*
 * @brief Read accelerometer
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[out] xl pointer to AccelData structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS reading successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_readAccelData(LSM6DSL *dev, LSM6DSL_AccelData *xl);

/*
 * @brief Performs acceleromter self test
 *
 * @attention device must be kept still during self test
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS pass
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE fail
 *
 * @note This function modifies the Accel and Gyro settings.
 * 		 Overwrites the registers CTRL1_XX(10h) to CTRL10_XX(19).
 * 		 Therefore, use it at startup prior to initialization.
 *
 * @see Figure 36 of AN5040 for the self procedure
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_selfTestAccel(LSM6DSL *dev);

/*
 * @brief Set accelerometer analog chain bandwidth for ODR >= 1.67kHz
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] m 0 for 1.5kHZ BW, 1 for 400Hz BW
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS pass
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE fail
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelAnalogChainBW(LSM6DSL *dev, uint8_t m);

/*
 * @brief Configure accelerometer digital low pass filter
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] odr one of LSM6DSL_XL_LPF_ODR values
 * @param[in] LNLL input composite value, 1 = low noise & 0 = low latency
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS pass
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE fail
 *
 * @see table 9 of AN5040 for samples to discard, alternatively use LSM6DSL_setDRDYMask() for ODR/2 & ODR/4
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_configAccelDigitalLPF(LSM6DSL *dev, enum LSM6DSL_XL_LPF_ODR odr, uint8_t LNLL);

/*
 * @brief Configure accelerometer digital high pass filter
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[in] odr one of LSM6DSL_XL_HPF_ODR values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS pass
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE fail
 *
 * @see table 9 of AN5040 for samples to discard
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_configAccelDigitalHPF(LSM6DSL *dev, enum LSM6DSL_XL_HPF_ODR odr);

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
LSM6DSL_INTF_RET_TYPE LSM6DSL_setGyroFSRange(LSM6DSL *dev, enum LSM6DSL_G_FS_Range r);

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
LSM6DSL_INTF_RET_TYPE LSM6DSL_setGyroHighPerfMode(LSM6DSL *dev, enum LSM6DSL_XL_G_HM_MODE m);

/*
 * @brief Read gyroscope
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[out] gy pointer to GyroData structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS reading successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_readGyroData(LSM6DSL *dev, LSM6DSL_GyroData *gy);

/*
 * @brief Performs gyroscope self test
 *
 * @attention device must be kept still during self test
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS pass
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE fail
 *
 * @note This function modifies the Accel and Gyro settings.
 * 		 Overwrites the registers CTRL1_XX(10h) to CTRL10_XX(19).
 * 		 Therefore, use it at startup prior to initialization.
 *
 * @see Figure 37 of AN5040 for the self procedure
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_selfTestGyro(LSM6DSL *dev);

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

/*
 * @brief Read temperature data
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 * @param[out] t Pointer to LSM6DSL_TempData structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS reading successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_readTemperature(LSM6DSL *dev, LSM6DSL_TempData *t);

#endif /* LSM6DSL_LSM6DSL_H_ */

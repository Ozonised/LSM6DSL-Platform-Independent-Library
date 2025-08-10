/*
 * lsm6dsl.h
 *
 *  Created on: Jul 28, 2025
 *      Author: farhan
 */

#ifndef LSM6DSL_HPP_
#define LSM6DSL_HPP_

#include "lsm6dsl_port.hpp"
#include "lsm6dsl_reg.hpp"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <cstdlib>

enum LSM6DSL_XL_FS_Range : uint8_t
{
	LSM6DSL_XL_FS_2G = 0, LSM6DSL_XL_FS_16G, LSM6DSL_XL_FS_4G, LSM6DSL_XL_FS_8G
};

namespace LSM6DSL_XL_FS_Sensitivity
{
	// sensitivity in mg/LSB
	constexpr float FS_2G_SENS = 0.061;
	constexpr float FS_4G_SENS = 0.122;
	constexpr float FS_8G_SENS = 0.244;
	constexpr float FS_16G_SENS = 0.488;
}

enum LSM6DSL_XL_ODR : uint8_t
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

enum LSM6DSL_XL_LPF_BW : uint8_t
{
	LSM6DSL_XL_LPF_BW_ODR_2 = 0,
	LSM6DSL_XL_LPF_BW_ODR_4,
	LSM6DSL_XL_LPF_BW_ODR_50,
	LSM6DSL_XL_LPF_BW_ODR_100,
	LSM6DSL_XL_LPF_BW_ODR_9,
	LSM6DSL_XL_LPF_BW_ODR_400,
};

enum LSM6DSL_XL_HPF_BW : uint8_t
{
	LSM6DSL_XL_HPF_BW_ODR_4 = 0,
	LSM6DSL_XL_HPF_BW_ODR_100,
	LSM6DSL_XL_HPF_BW_ODR_9,
	LSM6DSL_XL_HPF_BW_ODR_400,
};

enum LSM6DSL_XL_G_HM_MODE : uint8_t
{
	LSM6DSL_XL_G_HM_MODE_ON = 0, LSM6DSL_XL_G_HM_MODE_OFF
};

enum LSM6DSL_G_FS_Range : uint8_t
{
	LSM6DSL_G_FS_250DPS = 0,
	LSM6DSL_G_FS_500DPS,
	LSM6DSL_G_FS_1000DPS,
	LSM6DSL_G_FS_2000DPS,
	LSM6DSL_G_FS_125DPS
};

namespace LSM6DSL_G_FS_Sensitivity
{
	// sensitivity in mdps/LSB
	constexpr float FS_125DPS_SENS = 4.375;
	constexpr float FS_250DPS_SENS = 8.75;
	constexpr float FS_500DPS_SENS = 17.5;
	constexpr float FS_1000DPS_SENS = 35;
	constexpr float FS_2000DPS_SENS = 70;
}

enum LSM6DSL_G_ODR : uint8_t
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

enum LSM6DSL_INT1_Sources : uint8_t
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

enum LSM6DSL_INT2_Sources : uint8_t
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

struct LSM6DSL_AccelRawData
{
		int16_t x;
		int16_t y;
		int16_t z;
};

struct LSM6DSL_GyroRawData
{
		int16_t x;
		int16_t y;
		int16_t z;
};

enum LSM6DSL_ENDIAN : uint8_t
{
	LSM6DSL_LITTLE_ENDIAN = 0, LSM6DSL_BIG_ENDIAN
};

struct LSM6DSL_TempData
{
		float celsius;
		int16_t regData;
};

class LSM6DSL
{
	private:
		void *hInterface;			// Reference to interface handle for I2C
		uint8_t chipAddr;			// IMU address

		LSM6DSL_INTF_RET_TYPE read(uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len); // Bus read function
		LSM6DSL_INTF_RET_TYPE write(uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len); // Bus write function
		void delayMs(uint32_t ms); // delay in millisecond function
		LSM6DSL_INTF_RET_TYPE ModifyReg(uint8_t regAddr, uint8_t *val);

	public:
		LSM6DSL(void *intrf, uint8_t chipAddr) :
				hInterface(intrf), chipAddr(chipAddr)
		{
		}

		LSM6DSL_INTF_RET_TYPE isPresent();

		LSM6DSL_INTF_RET_TYPE setBigLittleEndian(enum LSM6DSL_ENDIAN end);

		LSM6DSL_INTF_RET_TYPE setAllIRQonINT1(uint8_t en);

		LSM6DSL_INTF_RET_TYPE INT1SourceConfig(enum LSM6DSL_INT1_Sources s);

		LSM6DSL_INTF_RET_TYPE INT2SourceConfig(enum LSM6DSL_INT2_Sources s);

		LSM6DSL_INTF_RET_TYPE toggleBlockDataUpdate(uint8_t m);

		LSM6DSL_INTF_RET_TYPE toggleDataReadyMask(uint8_t m);

		LSM6DSL_INTF_RET_TYPE setAccelODR(enum LSM6DSL_XL_ODR m);

		LSM6DSL_INTF_RET_TYPE setAccelFSRange(enum LSM6DSL_XL_FS_Range r);

		LSM6DSL_INTF_RET_TYPE isAccelDataAvailabe();

		LSM6DSL_INTF_RET_TYPE setAccelHighPerfMode(enum LSM6DSL_XL_G_HM_MODE m);

		LSM6DSL_INTF_RET_TYPE readAccelData(LSM6DSL_AccelRawData *xl);

		LSM6DSL_INTF_RET_TYPE selfTestAccel();

		LSM6DSL_INTF_RET_TYPE setAccelAnalogChainBW(uint8_t m);

		LSM6DSL_INTF_RET_TYPE configAccelDigitalLPF(enum LSM6DSL_XL_LPF_BW odr, uint8_t LNLL);

		LSM6DSL_INTF_RET_TYPE configAccelDigitalHPF(enum LSM6DSL_XL_HPF_BW odr);

		LSM6DSL_INTF_RET_TYPE setGyroODR(enum LSM6DSL_G_ODR m);

		LSM6DSL_INTF_RET_TYPE setGyroFSRange(enum LSM6DSL_G_FS_Range r);

		LSM6DSL_INTF_RET_TYPE isGyroDataAvailabe();

		LSM6DSL_INTF_RET_TYPE setGyroHighPerfMode(enum LSM6DSL_XL_G_HM_MODE m);

		LSM6DSL_INTF_RET_TYPE readGyroData(LSM6DSL_GyroRawData *gy);

		LSM6DSL_INTF_RET_TYPE selfTestGyro();

		LSM6DSL_INTF_RET_TYPE isTempDataAvailabe();

		LSM6DSL_INTF_RET_TYPE readTemperature(LSM6DSL_TempData *t);
};

#endif /* LSM6DSL_HPP_ */

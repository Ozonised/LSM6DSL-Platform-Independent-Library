/*
 * lsm6dsl.c
 *
 *  Created on: Jul 28, 2025
 *      Author: farhan
 */

#include "lsm6dsl_reg.h"
#include "lsm6dsl.h"
#include "lsm6dsl_port.h"

const int16_t MIN_ST = 90, MAX_ST = 1700;

static LSM6DSL_INTF_RET_TYPE LSM6DSL_ModifyReg(LSM6DSL *dev, uint8_t regAddr, uint8_t *val)
{
	if (dev != NULL && val != NULL)
	{
		uint8_t reg;
		if (dev->write(dev->hInterface, dev->chipAddr, regAddr, val,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			// verify the written value
			if ((dev->read(dev->hInterface, dev->chipAddr, regAddr, &reg, 1)
					== LSM6DSL_INTF_RET_TYPE_SUCCESS) && (reg == *val))
				return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_IsPresent(LSM6DSL *dev)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, WHO_AM_I, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (t == WHO_AM_I_VAL)
				return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setBigLittleEndian(LSM6DSL *dev, enum LSM6DSL_ENDIAN end)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL3_C, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			switch (end)
			{
			case LSM6DSL_LITTLE_ENDIAN:
				t &= ~BLE;
				break;

			case LSM6DSL_BIG_ENDIAN:
				t |= BLE;
				break;

			default:
				// incorrect value
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			return LSM6DSL_ModifyReg(dev, CTRL3_C, &t);
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_Init(LSM6DSL *dev, void *interfacePtr, uint8_t imuAddr)
{
	if (dev != NULL && interfacePtr != NULL)
	{
		dev->hInterface = interfacePtr;
		dev->chipAddr = imuAddr;
		dev->read = LSM6DSL_PortI2CReadReg;
		dev->write = LSM6DSL_PortI2CWriteReg;
		dev->delayMs = LSM6DSL_PortDelayMs;
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAllIRQonINT1(LSM6DSL *dev, uint8_t en)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL4_C, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (en)
				t |= INT2_on_INT1;
			else
				t &= ~INT2_on_INT1;

			return LSM6DSL_ModifyReg(dev, CTRL4_C, &t);
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelODR(LSM6DSL *dev, enum LSM6DSL_XL_ODR m)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL1_XL, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			t &= 0x0F;	// clear the ODR_XLn bits
			switch (m)
			{
			case LSM6DSL_XL_ODR_POWER_DOWN:
				break;
			case LSM6DSL_XL_ODR_12_5Hz:
			case LSM6DSL_XL_ODR_26Hz:
			case LSM6DSL_XL_ODR_52Hz:
			case LSM6DSL_XL_ODR_104Hz:
			case LSM6DSL_XL_ODR_208Hz:
			case LSM6DSL_XL_ODR_416Hz:
			case LSM6DSL_XL_ODR_833Hz:
			case LSM6DSL_XL_ODR_1_66kHz:
			case LSM6DSL_XL_ODR_3_33kHz:
			case LSM6DSL_XL_ODR_6_66kHz:
			case LSM6DSL_XL_ODR_1_6Hz:
				t |= (m << ODR_XL0_Pos );
				break;

			default:
				// incorrect values
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			return LSM6DSL_ModifyReg(dev, CTRL1_XL, &t);
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_isAccelDataAvailabe(LSM6DSL *dev)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, STATUS_REG, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (t & XLDA)
				return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setGyroODR(LSM6DSL *dev, enum LSM6DSL_G_ODR m)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL2_G, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			t &= 0x0E;	// clear the ODR_Gn bits
			switch (m)
			{
			case LSM6DSL_G_ODR_POWER_DOWN:
				break;
			case LSM6DSL_G_ODR_12_5Hz:
			case LSM6DSL_G_ODR_26Hz:
			case LSM6DSL_G_ODR_52Hz:
			case LSM6DSL_G_ODR_104Hz:
			case LSM6DSL_G_ODR_208Hz:
			case LSM6DSL_G_ODR_416Hz:
			case LSM6DSL_G_ODR_833Hz:
			case LSM6DSL_G_ODR_1_66kHz:
			case LSM6DSL_G_ODR_3_33kHz:
			case LSM6DSL_G_ODR_6_66kHz:
				t |= (m << ODR_G0_Pos );
				break;

			default:
				// incorrect values
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			return LSM6DSL_ModifyReg(dev, CTRL2_G, &t);
		}
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelFSRange(LSM6DSL *dev, enum LSM6DSL_XL_FS_Range r)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL1_XL, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			t &= 0xF3;	// clear the FS_XLn bits
			switch (r)
			{
			case LSM6DSL_XL_FS_2G:
				break;
			case LSM6DSL_XL_FS_4G:
			case LSM6DSL_XL_FS_8G:
			case LSM6DSL_XL_FS_16G:
				t |= (r << FS_XL0_Pos );
				break;
			default:
				// incorrect values
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			return LSM6DSL_ModifyReg(dev, CTRL1_XL, &t);
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setGyroFSRange(LSM6DSL *dev, enum LSM6DSL_G_FS_Range r)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL2_G, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			t &= 0xF0;	// clear the FS_Gn and FS_G125 bits
			switch (r)
			{
			case LSM6DSL_G_FS_250DPS:
				break;
			case LSM6DSL_G_FS_500DPS:
			case LSM6DSL_G_FS_1000DPS:
			case LSM6DSL_G_FS_2000DPS:
				t |= (r << FS_G0_Pos );
				break;

			case LSM6DSL_G_FS_125DPS:
				t |= FS_125;
				break;
			default:
				// incorrect values
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			return LSM6DSL_ModifyReg(dev, CTRL2_G, &t);
		}
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelHighPerfMode(LSM6DSL *dev, enum LSM6DSL_XL_G_HM_MODE m)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL6_C, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (LSM6DSL_XL_G_HM_MODE_ON)
				t &= ~XL_HM_MODE;
			else
				t |= XL_HM_MODE;

			return LSM6DSL_ModifyReg(dev, CTRL6_C, &t);
		}

	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setGyroHighPerfMode(LSM6DSL *dev, enum LSM6DSL_XL_G_HM_MODE m)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL7_G, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (LSM6DSL_XL_G_HM_MODE_ON)
				t &= ~G_HM_MODE;
			else
				t |= G_HM_MODE;

			return LSM6DSL_ModifyReg(dev, CTRL7_G, &t);
		}

	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_isGyroDataAvailabe(LSM6DSL *dev)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, STATUS_REG, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (t & GDA)
				return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_isTempDataAvailabe(LSM6DSL *dev)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, STATUS_REG, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (t & TDA)
				return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_INT1SourceConfig(LSM6DSL *dev, enum LSM6DSL_INT1_Sources s)
{
	if (dev != NULL)
	{
		if (s >= 0 && s <= 255)
		{
			return LSM6DSL_ModifyReg(dev, INT1_CTRL, &s);
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_INT2SourceConfig(LSM6DSL *dev, enum LSM6DSL_INT2_Sources s)
{
	if (dev != NULL)
	{
		if (s >= 0 && s <= 255)
		{
			return LSM6DSL_ModifyReg(dev, INT2_CTRL, &s);
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_toggleBlockDataUpdate(LSM6DSL *dev, uint8_t m)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL3_C, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (m)
				t |= BDU;
			else
				t &= ~BDU;

			return LSM6DSL_ModifyReg(dev, CTRL3_C, &t);
		}
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_readAccelData(LSM6DSL *dev, LSM6DSL_AccelData *xl)
{
	if (dev != NULL && xl != NULL)
	{
		uint8_t buf[6];
		if (dev->read(dev->hInterface, dev->chipAddr, OUTX_L_XL, buf,
				6) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			xl->accel_x = (buf[1] << 8) | buf[0];
			xl->accel_y = (buf[3] << 8) | buf[2];
			xl->accel_z = (buf[5] << 8) | buf[4];

			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_readGyroData(LSM6DSL *dev, LSM6DSL_GyroData *gy)
{
	if (dev != NULL && gy != NULL)
	{
		uint8_t buf[6];
		if (dev->read(dev->hInterface, dev->chipAddr, OUTX_L_G, buf,
				6) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			gy->gyro_x = (buf[1] << 8) | buf[0];
			gy->gyro_y = (buf[3] << 8) | buf[2];
			gy->gyro_z = (buf[5] << 8) | buf[4];

			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_selfTestAccel(LSM6DSL *dev)
{
	if (dev != NULL)
	{
		// the test procedure is described in figure 36 of AN5040
		LSM6DSL_AccelData currentAccel, StAccel, noStAccel;
		uint8_t ptr[10] = { 0x38, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00 };

		if (dev->write(dev->hInterface, dev->chipAddr, CTRL1_XL, ptr,
				10) == LSM6DSL_INTF_RET_TYPE_FAILURE)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;

		dev->delayMs(dev->hInterface, 100);

		memset((void*) &noStAccel, 0, sizeof(noStAccel));
		// self test disable
		for (uint8_t i = 0; i <= 5; i++)
		{
			if (LSM6DSL_isAccelDataAvailabe(
					dev) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			{
				// discard the first sample
				if (i == 0)
				{
					LSM6DSL_readAccelData(dev, &currentAccel);
					continue;
				}

				LSM6DSL_readAccelData(dev, &currentAccel);
				// average 5 samples
				noStAccel.accel_x += currentAccel.accel_x / 5;
				noStAccel.accel_y += currentAccel.accel_y / 5;
				noStAccel.accel_z += currentAccel.accel_z / 5;
			}
		}

		// self test enable
		uint8_t st = 0x01;
		if (LSM6DSL_ModifyReg(dev, CTRL5_C,
				&st) == LSM6DSL_INTF_RET_TYPE_FAILURE)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;

		dev->delayMs(dev->hInterface, 100);
		memset((void*) &StAccel, 0, sizeof(StAccel));

		for (uint8_t i = 0; i <= 5; i++)
		{
			if (LSM6DSL_isAccelDataAvailabe(
					dev) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			{
				// discard the first sample
				if (i == 0)
				{
					LSM6DSL_readAccelData(dev, &currentAccel);
					continue;
				}

				LSM6DSL_readAccelData(dev, &currentAccel);
				// average 5 samples
				StAccel.accel_x += currentAccel.accel_x / 5;
				StAccel.accel_y += currentAccel.accel_y / 5;
				StAccel.accel_z += currentAccel.accel_z / 5;
			}
		}

		// store the difference between the value of x, y and z with and without self test
		currentAccel.accel_x = ((StAccel.accel_x - noStAccel.accel_x)
				* LSM6DSL_XL_FS_4G_SENS) / 1000;
		currentAccel.accel_y = ((StAccel.accel_y - noStAccel.accel_y)
				* LSM6DSL_XL_FS_4G_SENS) / 1000;
		currentAccel.accel_z = ((StAccel.accel_z - noStAccel.accel_z)
				* LSM6DSL_XL_FS_4G_SENS) / 1000;

		if (abs(currentAccel.accel_x) >= abs(MIN_ST)
				&& abs(currentAccel.accel_x) <= abs(MAX_ST)
				&& abs(currentAccel.accel_y) >= abs(MIN_ST)
				&& abs(currentAccel.accel_y) <= abs(MAX_ST)
				&& abs(currentAccel.accel_z) >= abs(MIN_ST)
				&& abs(currentAccel.accel_z) <= abs(MAX_ST))
		{
			// disable self test and accelerometer
			st = 0x00;
			if (LSM6DSL_ModifyReg(dev, CTRL5_C,
					&st) == LSM6DSL_INTF_RET_TYPE_SUCCESS && LSM6DSL_ModifyReg(dev, CTRL1_XL,
							&st) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
				return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			else
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
		}

		if (LSM6DSL_ModifyReg(dev, CTRL5_C,
				&st) != LSM6DSL_INTF_RET_TYPE_SUCCESS && LSM6DSL_ModifyReg(dev, CTRL1_XL,
						&st) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

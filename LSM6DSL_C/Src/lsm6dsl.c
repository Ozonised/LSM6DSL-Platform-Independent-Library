/*
 * lsm6dsl.c
 *
 *  Created on: Jul 28, 2025
 *      Author: farhan
 */

#include "lsm6dsl.h"

const int16_t MIN_ST_XL = 90, MAX_ST_XL = 1700;
const uint32_t MIN_ST_G_250FS = 20, MIN_ST_G_2000FS = 150, MAX_ST_G_250FS = 80,
		MAX_ST_G_2000FS = 700;

const float LSM6DSL_XL_FS_Sensitivity[] = { 0.61, 0.122, 0.244, 0.488 };
const float LSM6DSL_G_FS_Sensitivity[] = { 8.75, 17.5, 35, 70, 4.375 };

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
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_WHO_AM_I, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (t == LSM6DSL_WHO_AM_I_VAL)
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
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL3_C, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			switch (end)
			{
			case LSM6DSL_LITTLE_ENDIAN:
				t &= ~LSM6DSL_BLE;
				break;

			case LSM6DSL_BIG_ENDIAN:
				t |= LSM6DSL_BLE;
				break;

			default:
				// incorrect value
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL3_C, &t);
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

		return LSM6DSL_INTF_RET_TYPE_SUCCESS;
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAllIRQonINT1(LSM6DSL *dev, uint8_t en)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL4_C, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (en)
				t |= LSM6DSL_INT2_on_INT1;
			else
				t &= ~LSM6DSL_INT2_on_INT1;

			return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL4_C, &t);
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelODR(LSM6DSL *dev, enum LSM6DSL_XL_ODR m)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL1_XL, &t,
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
				t |= (m << LSM6DSL_ODR_XL0_Pos );
				break;

			default:
				// incorrect values
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL1_XL, &t);
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_isAccelDataAvailabe(LSM6DSL *dev)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_STATUS_REG, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (t & LSM6DSL_XLDA)
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
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL2_G, &t,
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
				t |= (m << LSM6DSL_ODR_G0_Pos );
				break;

			default:
				// incorrect values
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL2_G, &t);
		}
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelFSRange(LSM6DSL *dev, enum LSM6DSL_XL_FS_Range r)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL1_XL, &t,
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
				t |= (r << LSM6DSL_FS_XL0_Pos );
				break;
			default:
				// incorrect values
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL1_XL, &t);
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setGyroFSRange(LSM6DSL *dev, enum LSM6DSL_G_FS_Range r)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL2_G, &t,
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
				t |= (r << LSM6DSL_FS_G0_Pos );
				break;

			case LSM6DSL_G_FS_125DPS:
				t |= LSM6DSL_FS_125;
				break;
			default:
				// incorrect values
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL2_G, &t);
		}
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelHighPerfMode(LSM6DSL *dev, enum LSM6DSL_XL_G_HM_MODE m)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL6_C, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (LSM6DSL_XL_G_HM_MODE_ON)
				t &= ~LSM6DSL_XL_HM_MODE;
			else
				t |= LSM6DSL_XL_HM_MODE;

			return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL6_C, &t);
		}

	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setGyroHighPerfMode(LSM6DSL *dev, enum LSM6DSL_XL_G_HM_MODE m)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL7_G, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (LSM6DSL_XL_G_HM_MODE_ON)
				t &= ~LSM6DSL_G_HM_MODE;
			else
				t |= LSM6DSL_G_HM_MODE;

			return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL7_G, &t);
		}

	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_isGyroDataAvailabe(LSM6DSL *dev)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_STATUS_REG, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (t & LSM6DSL_GDA)
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
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_STATUS_REG, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (t & LSM6DSL_TDA)
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
			return LSM6DSL_ModifyReg(dev, LSM6DSL_INT1_CTRL, &s);
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
			return LSM6DSL_ModifyReg(dev, LSM6DSL_INT2_CTRL, &s);
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_toggleBlockDataUpdate(LSM6DSL *dev, uint8_t m)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL3_C, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (m)
				t |= LSM6DSL_BDU;
			else
				t &= ~LSM6DSL_BDU;

			return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL3_C, &t);
		}
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_readAccelData(LSM6DSL *dev, LSM6DSL_AccelRawData *xl)
{
	if (dev != NULL && xl != NULL)
	{
		uint8_t buf[6];
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_OUTX_L_XL, buf,
				6) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			xl->x = (buf[1] << 8) | buf[0];
			xl->y = (buf[3] << 8) | buf[2];
			xl->z = (buf[5] << 8) | buf[4];

			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_readGyroData(LSM6DSL *dev, LSM6DSL_GyroRawData *gy)
{
	if (dev != NULL && gy != NULL)
	{
		uint8_t buf[6];
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_OUTX_L_G, buf,
				6) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			gy->x = (buf[1] << 8) | buf[0];
			gy->y = (buf[3] << 8) | buf[2];
			gy->z = (buf[5] << 8) | buf[4];

			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

float convertAccelRawDataTomS2(int16_t axisN, enum LSM6DSL_XL_FS_Range r)
{
	return ((axisN * LSM6DSL_XL_FS_Sensitivity[r]) * 9.8) / 1000.0;
}

float convertGyroRawDataToDPS(int16_t axisN, enum LSM6DSL_G_FS_Range r)
{
	return (axisN * LSM6DSL_G_FS_Sensitivity[r]) / 1000.0;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_selfTestAccel(LSM6DSL *dev)
{
	if (dev != NULL)
	{
		// the test procedure is described in figure 36 of AN5040
		LSM6DSL_AccelRawData currentAccel, StAccel, noStAccel;
		float deltaAccelX, deltaAccelY, deltaAccelZ;
		uint8_t ptr[10] = { 0x38, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00 };

		if (dev->write(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL1_XL, ptr,
				10) == LSM6DSL_INTF_RET_TYPE_FAILURE)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;

		dev->delayMs(dev->hInterface, 100);

		memset((void*) &noStAccel, 0, sizeof(noStAccel));
		// self test disable
		for (uint8_t i = 0; i <= 5; i++)
		{
			while (LSM6DSL_isAccelDataAvailabe(dev)
					!= LSM6DSL_INTF_RET_TYPE_SUCCESS);

			// discard the first sample
			if (i == 0)
			{
				LSM6DSL_readAccelData(dev, &currentAccel);
				continue;
			}

			LSM6DSL_readAccelData(dev, &currentAccel);
			// average 5 samples
			noStAccel.x += currentAccel.x / 5;
			noStAccel.y += currentAccel.y / 5;
			noStAccel.z += currentAccel.z / 5;

		}

		// self test enable
		uint8_t st = 0x01;
		if (LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL5_C,
				&st) == LSM6DSL_INTF_RET_TYPE_FAILURE)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;

		dev->delayMs(dev->hInterface, 100);
		memset((void*) &StAccel, 0, sizeof(StAccel));

		for (uint8_t i = 0; i <= 5; i++)
		{
			while (LSM6DSL_isAccelDataAvailabe(dev)
					!= LSM6DSL_INTF_RET_TYPE_SUCCESS);

			// discard the first sample
			if (i == 0)
			{
				LSM6DSL_readAccelData(dev, &currentAccel);
				continue;
			}

			LSM6DSL_readAccelData(dev, &currentAccel);
			// average 5 samples
			StAccel.x += currentAccel.x / 5;
			StAccel.y += currentAccel.y / 5;
			StAccel.z += currentAccel.z / 5;

		}

		// store the difference between the value of x, y and z with and without self test
		deltaAccelX = ((StAccel.x - noStAccel.x)
				* LSM6DSL_XL_FS_Sensitivity[LSM6DSL_XL_FS_4G]);
		deltaAccelY = ((StAccel.y - noStAccel.y)
				* LSM6DSL_XL_FS_Sensitivity[LSM6DSL_XL_FS_4G]);
		deltaAccelZ = ((StAccel.z - noStAccel.z)
				* LSM6DSL_XL_FS_Sensitivity[LSM6DSL_XL_FS_4G]);

		st = 0x00;
		if (abs(deltaAccelX) >= abs(MIN_ST_XL)
				&& abs(deltaAccelX) <= abs(MAX_ST_XL)
				&& abs(deltaAccelY) >= abs(MIN_ST_XL)
				&& abs(deltaAccelY) <= abs(MAX_ST_XL)
				&& abs(deltaAccelZ) >= abs(MIN_ST_XL)
				&& abs(deltaAccelZ) <= abs(MAX_ST_XL))
		{
			// disable self test and accelerometer
			if (LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL5_C,
					&st) == LSM6DSL_INTF_RET_TYPE_SUCCESS && LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL1_XL,
							&st) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
				return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			else
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
		}

		if (LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL5_C,
				&st) != LSM6DSL_INTF_RET_TYPE_SUCCESS && LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL1_XL,
						&st) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_selfTestGyro(LSM6DSL *dev)
{
	if (dev != NULL)
	{
		// the test procedure is described in figure 37 of AN5040
		LSM6DSL_GyroRawData currentGyro, StGyro, noStGyro;
		long deltaGyroX, deltaGyroY, deltaGyroZ;
		uint8_t ptr[10] = { 0x00, 0x50, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00 };

		if (dev->write(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL1_XL, ptr,
				10) == LSM6DSL_INTF_RET_TYPE_FAILURE)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;

		dev->delayMs(dev->hInterface, 150);

		memset((void*) &noStGyro, 0, sizeof(noStGyro));
		// self test disable
		for (uint8_t i = 0; i <= 5; i++)
		{
			while (LSM6DSL_isGyroDataAvailabe(dev)
					!= LSM6DSL_INTF_RET_TYPE_SUCCESS);

			// discard the first sample
			if (i == 0)
			{
				LSM6DSL_readGyroData(dev, &currentGyro);
				continue;
			}

			LSM6DSL_readGyroData(dev, &currentGyro);
			// average 5 samples
			noStGyro.x += currentGyro.x / 5;
			noStGyro.y += currentGyro.y / 5;
			noStGyro.z += currentGyro.z / 5;

		}

		// self test enable
		uint8_t st = 0x04;
		if (LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL5_C,
				&st) == LSM6DSL_INTF_RET_TYPE_FAILURE)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;

		dev->delayMs(dev->hInterface, 50);
		memset((void*) &StGyro, 0, sizeof(StGyro));

		for (uint8_t i = 0; i <= 5; i++)
		{
			while (LSM6DSL_isGyroDataAvailabe(dev)
					!= LSM6DSL_INTF_RET_TYPE_SUCCESS);

			// discard the first sample
			if (i == 0)
			{
				LSM6DSL_readGyroData(dev, &currentGyro);
				continue;
			}

			LSM6DSL_readGyroData(dev, &currentGyro);
			// average 5 samples
			StGyro.x += currentGyro.x / 5;
			StGyro.y += currentGyro.y / 5;
			StGyro.z += currentGyro.z / 5;

		}

		// store the difference between the value of x, y and z with and without self test
		deltaGyroX = ((StGyro.x - noStGyro.x)
				* LSM6DSL_G_FS_Sensitivity[LSM6DSL_G_FS_250DPS]) / 1000;
		deltaGyroY = ((StGyro.y - noStGyro.y)
				* LSM6DSL_G_FS_Sensitivity[LSM6DSL_G_FS_250DPS]) / 1000;
		deltaGyroZ = ((StGyro.z - noStGyro.z)
				* LSM6DSL_G_FS_Sensitivity[LSM6DSL_G_FS_250DPS]) / 1000;
		st = 0x00;
		if (abs(deltaGyroX) >= abs(MIN_ST_G_250FS)
				&& abs(deltaGyroX) <= abs(MAX_ST_G_250FS)
				&& abs(deltaGyroY) >= abs(MIN_ST_G_250FS)
				&& abs(deltaGyroY) <= abs(MAX_ST_G_250FS)
				&& abs(deltaGyroZ) >= abs(MIN_ST_G_250FS)
				&& abs(deltaGyroZ) <= abs(MAX_ST_G_250FS))
		{
			// disable self test and gyroscope
			if (LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL5_C,
					&st) == LSM6DSL_INTF_RET_TYPE_SUCCESS && LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL2_G,
							&st) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
				return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			else
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
		}

		if (LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL5_C,
				&st) != LSM6DSL_INTF_RET_TYPE_SUCCESS && LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL2_G,
						&st) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_readTemperature(LSM6DSL *dev, LSM6DSL_TempData *t)
{
	if (dev != NULL && t != NULL)
	{
		uint8_t buf[2];
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_OUT_TEMP_L, buf,
				2) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			t->regData = buf[1] << 8 | buf[0];
			// 1 degree celsius = 256 LSB
			t->celsius = 25.0 + t->regData / 256;
			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelAnalogChainBW(LSM6DSL *dev, uint8_t m)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL1_XL, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (m)
				t |= LSM6DSL_BW0_XL;
			else
				t &= ~LSM6DSL_BW0_XL;

			return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL1_XL, &t);
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_configAccelDigitalLPF(LSM6DSL *dev, enum LSM6DSL_XL_LPF_BW bw, uint8_t LNLL)
{
	if (dev != NULL)
	{
		uint8_t ctrl8_xl, ctrl1_xl;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL8_XL,
				&ctrl8_xl, 1) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;

		if (LNLL)
			ctrl8_xl |= LSM6DSL_INPUT_COMPOSITE; // low noise
		else
			ctrl8_xl &= ~LSM6DSL_INPUT_COMPOSITE; // low latency

		// disable high pass path
		ctrl8_xl &= ~LSM6DSL_HP_SLOPE_XL_EN;
		if (LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL8_XL,
				&ctrl8_xl) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;

		switch (bw)
		{
		case LSM6DSL_XL_LPF_BW_ODR_2:
		case LSM6DSL_XL_LPF_BW_ODR_4:

			// disable LPF2 path
			ctrl8_xl &= ~(LSM6DSL_LPF2_XL_EN );
			if (LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL8_XL,
					&ctrl8_xl) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
				return LSM6DSL_INTF_RET_TYPE_FAILURE;

			if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL1_XL,
					&ctrl1_xl, 1) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
				return LSM6DSL_INTF_RET_TYPE_FAILURE;

			if (bw == LSM6DSL_XL_LPF_BW_ODR_4)
				ctrl1_xl |= LSM6DSL_LPF1_BW_SEL;
			else
				ctrl1_xl &= ~(LSM6DSL_LPF1_BW_SEL );

			return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL1_XL, &ctrl1_xl);

			break;

		case LSM6DSL_XL_LPF_BW_ODR_50:

			ctrl8_xl |= LSM6DSL_LPF2_XL_EN;
			ctrl8_xl &= ~(LSM6DSL_HPCF_XL1 | LSM6DSL_HPCF_XL0 );
			break;

		case LSM6DSL_XL_LPF_BW_ODR_100:
			ctrl8_xl |= LSM6DSL_LPF2_XL_EN | LSM6DSL_HPCF_XL0;
			ctrl8_xl &= ~(LSM6DSL_HPCF_XL1 );
			break;

		case LSM6DSL_XL_LPF_BW_ODR_9:
			ctrl8_xl |= LSM6DSL_LPF2_XL_EN | LSM6DSL_HPCF_XL1;
			ctrl8_xl &= ~(LSM6DSL_HPCF_XL0 );
			break;

		case LSM6DSL_XL_LPF_BW_ODR_400:
			ctrl8_xl |= LSM6DSL_LPF2_XL_EN | LSM6DSL_HPCF_XL1 | LSM6DSL_HPCF_XL0;
			break;

		default:
			// incorrect value
			return LSM6DSL_INTF_RET_TYPE_FAILURE;
			break;
		}
		return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL8_XL, &ctrl8_xl);
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_configAccelDigitalHPF(LSM6DSL *dev, enum LSM6DSL_XL_HPF_BW bw)
{
	if (dev != NULL)
	{
		uint8_t ctrl8_xl;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL8_XL,
				&ctrl8_xl, 1) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;

		ctrl8_xl &= ~LSM6DSL_INPUT_COMPOSITE; // low latency

		switch (bw)
		{
		case LSM6DSL_XL_HPF_BW_ODR_4:
			ctrl8_xl &= ~(LSM6DSL_HPCF_XL1 | LSM6DSL_HPCF_XL0 );
			break;

		case LSM6DSL_XL_HPF_BW_ODR_100:
			ctrl8_xl |= (LSM6DSL_HPCF_XL0 );
			ctrl8_xl &= ~(LSM6DSL_HPCF_XL1 );
			break;

		case LSM6DSL_XL_HPF_BW_ODR_9:
			ctrl8_xl |= (LSM6DSL_HPCF_XL1 );
			ctrl8_xl &= ~(LSM6DSL_HPCF_XL0 );
			break;

		case LSM6DSL_XL_HPF_BW_ODR_400:
			ctrl8_xl |= (LSM6DSL_HPCF_XL0 | LSM6DSL_HPCF_XL1 );
			break;

		default:
			// incorrect value
			return LSM6DSL_INTF_RET_TYPE_FAILURE;
			break;
		}

		return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL8_XL, &ctrl8_xl);
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_configGyroHPF(LSM6DSL *dev, enum LSM6DSL_G_HPF_BW bw)
{
	uint8_t ctrl7_G;

	if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL7_G, &ctrl7_G,
			1) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
		return LSM6DSL_INTF_RET_TYPE_FAILURE;

	ctrl7_G &= ~(LSM6DSL_HPM0_G | LSM6DSL_HPM1_G );

	switch (bw)
	{
	case LSM6DSL_G_HPF_BW_0_016Hz:
		break;

	case LSM6DSL_G_HPF_BW_0_065Hz:
		ctrl7_G |= LSM6DSL_HPM0_G;
		break;

	case LSM6DSL_G_HPF_BW_0_260Hz:
		ctrl7_G |= LSM6DSL_HPM1_G;
		break;

	case LSM6DSL_G_HPF_BW_1_04Hz:
		ctrl7_G |= LSM6DSL_HPM0_G | LSM6DSL_HPM1_G;
		break;

	default:
		// incorrect value
		return LSM6DSL_INTF_RET_TYPE_FAILURE;
		break;
	}

	return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL7_G, &ctrl7_G);
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_toggleDataReadyMask(LSM6DSL *dev, uint8_t m)
{
	if (dev != NULL)
	{
		uint8_t ctrl4_c;
		if (dev->read(dev->hInterface, dev->chipAddr, LSM6DSL_CTRL4_C, &ctrl4_c,
				1) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;

		if (m)
			ctrl4_c |= LSM6DSL_DRDY_MASK;
		else
			ctrl4_c &= ~LSM6DSL_DRDY_MASK;

		return LSM6DSL_ModifyReg(dev, LSM6DSL_CTRL4_C, &ctrl4_c);
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

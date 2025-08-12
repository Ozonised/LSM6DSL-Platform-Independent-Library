/*
 * lsm6dsl.c
 *
 *  Created on: Jul 28, 2025
 *      Author: farhan
 */

#include "lsm6dsl.hpp"

static constexpr int16_t MIN_ST_XL = 90, MAX_ST_XL = 1700;
static constexpr uint16_t MIN_ST_G_250FS = 20, MIN_ST_G_2000FS = 150,
		MAX_ST_G_250FS = 80, MAX_ST_G_2000FS = 700;

// sensitivity in mg/LSB
const float LSM6DSL_XL_FS_Sensitivity[] = { 0.061, 0.122, 0.244, 0.488 };
// sensitivity in mdps/LSB
const float LSM6DSL_G_FS_Sensitivity[5] = { 8.75, 17.5, 35, 70, 4.375 };

LSM6DSL_INTF_RET_TYPE LSM6DSL::ModifyReg(uint8_t regAddr, uint8_t *val)
{
	if (val != NULL)
	{
		uint8_t reg;
		if (write(chipAddr, regAddr, val, 1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			// verify the written value
			if ((read(chipAddr, regAddr, &reg, 1)
					== LSM6DSL_INTF_RET_TYPE_SUCCESS) && (reg == *val))
				return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Checks if the LSM6DSL is present on the bus
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS device is present
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE absent, error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::isPresent()
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::WHO_AM_I, &t,
			1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
	{
		if (t == LSM6DSL_REG::WHO_AM_I_VAL)
			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Set imu's data registers endianess
 *
 * @param[in] end one of LSM6DSL_ENDIAN values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @see section 4.5 of AN5040
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::setBigLittleEndian(enum LSM6DSL_ENDIAN end)
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::CTRL3_C, &t,
			1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
	{
		switch (end)
		{
		case LSM6DSL_LITTLE_ENDIAN:
			t &= ~LSM6DSL_REG::BLE;
			break;

		case LSM6DSL_BIG_ENDIAN:
			t |= LSM6DSL_REG::BLE;
			break;

		default:
			// incorrect value
			return LSM6DSL_INTF_RET_TYPE_FAILURE;
			break;
		}

		return ModifyReg(LSM6DSL_REG::CTRL3_C, &t);
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Maps IRQs on INT2 pin to INT1 pin
 *
 * @param[in] en 1 to enable, 0 to disable
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::setAllIRQonINT1(uint8_t en)
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::CTRL4_C, &t,
			1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
	{
		if (en)
			t |= LSM6DSL_REG::INT2_on_INT1;
		else
			t &= ~LSM6DSL_REG::INT2_on_INT1;

		return ModifyReg(LSM6DSL_REG::CTRL4_C, &t);
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Sets Accelerometers ODR
 *
 * @param[in] m one of LSM6DSL_XL_ODR values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @see Table 12 & 13 of AN5040 for number of samples to discard.
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::setAccelODR(enum LSM6DSL_XL_ODR m)
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::CTRL1_XL, &t,
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
			t |= (m << LSM6DSL_REG::ODR_XL0_Pos);
			break;

		default:
			// incorrect values
			return LSM6DSL_INTF_RET_TYPE_FAILURE;
			break;
		}

		return ModifyReg(LSM6DSL_REG::CTRL1_XL, &t);
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Checks if accelerometer data is available
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS available
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE unavailable, error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::isAccelDataAvailabe()
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::STATUS_REG, &t,
			1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
	{
		if (t & LSM6DSL_REG::XLDA)
			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Sets Gyros ODR
 *
 * @param[in] m one of enum LSM6DSL_G_ODR values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @see Table 14, 15 & 16 of AN5040 for number of samples to discard.
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::setGyroODR(enum LSM6DSL_G_ODR m)
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::CTRL2_G, &t,
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
			t |= (m << LSM6DSL_REG::ODR_G0_Pos);
			break;

		default:
			// incorrect values
			return LSM6DSL_INTF_RET_TYPE_FAILURE;
			break;
		}

		return ModifyReg(LSM6DSL_REG::CTRL2_G, &t);
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Sets Accelerometers Full Scale Range
 *
 * @param[in] r one of LSM6DSL_XL_FS_Range values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::setAccelFSRange(enum LSM6DSL_XL_FS_Range r)
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::CTRL1_XL, &t,
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
			t |= (r << LSM6DSL_REG::FS_XL0_Pos);
			break;
		default:
			// incorrect values
			return LSM6DSL_INTF_RET_TYPE_FAILURE;
			break;
		}

		return ModifyReg(LSM6DSL_REG::CTRL1_XL, &t);
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Sets Gyro Full Scale Range
 *
 * @param[in] r one of LSM6DSL_G_FS_Range values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::setGyroFSRange(enum LSM6DSL_G_FS_Range r)
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::CTRL2_G, &t,
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
			t |= (r << LSM6DSL_REG::FS_G0_Pos);
			break;

		case LSM6DSL_G_FS_125DPS:
			t |= LSM6DSL_REG::FS_125;
			break;
		default:
			// incorrect values
			return LSM6DSL_INTF_RET_TYPE_FAILURE;
			break;
		}

		return ModifyReg(LSM6DSL_REG::CTRL2_G, &t);
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Enable/disable accelerometers high performance mode
 *
 * @param[in] m one of LSM6DSL_XL_G_HM_MODE values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @see Table 12 & 13 of AN5040 for number of samples to discard.
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::setAccelHighPerfMode(enum LSM6DSL_XL_G_HM_MODE m)
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::CTRL6_C, &t,
			1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
	{
		if (LSM6DSL_XL_G_HM_MODE_ON)
			t &= ~LSM6DSL_REG::XL_HM_MODE;
		else
			t |= LSM6DSL_REG::XL_HM_MODE;

		return LSM6DSL::ModifyReg(LSM6DSL_REG::CTRL6_C, &t);
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Enable/disable gyroscope high performance mode
 *
 * @param[in] m one of LSM6DSL_XL_G_HM_MODE values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @see Table 14, 15 & 16 of AN5040 for number of samples to discard.
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::setGyroHighPerfMode(enum LSM6DSL_XL_G_HM_MODE m)
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::CTRL7_G, &t,
			1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
	{
		if (LSM6DSL_XL_G_HM_MODE_ON)
			t &= ~LSM6DSL_REG::G_HM_MODE;
		else
			t |= LSM6DSL_REG::G_HM_MODE;

		return ModifyReg(LSM6DSL_REG::CTRL7_G, &t);
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Checks if gyroscope data is available
 *
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS available
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE unavailable, error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::isGyroDataAvailabe()
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::STATUS_REG, &t,
			1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
	{
		if (t & LSM6DSL_REG::GDA)
			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Checks if temperature data is available
 *
 * @attention either the accelerometer or the gyroscope must be enabled for the temperature sensor to work
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS available
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE unavailable, error
 *
 * @see Refer to section 9 of the application note AN5040 for the max ODR
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::isTempDataAvailabe()
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::STATUS_REG, &t,
			1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
	{
		if (t & LSM6DSL_REG::TDA)
			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Enable/Disable INT1 IRQ sources
 *
 * @param[in] s values from LSM6DSL_INT1_Sources
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @note This function overwrites the INT1_CTRL reg with value of s.
 * 		 To enable multiple sources the values of LSM6DSL_INT1_Sources should be ORed.
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::INT1SourceConfig(enum LSM6DSL_INT1_Sources s)
{
	if (s >= 0 && s <= 255)
	{
		return ModifyReg(LSM6DSL_REG::INT1_CTRL, (uint8_t*) &s);
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Enable/Disable INT2 IRQ sources
 *
 * @param[in] s values from LSM6DSL_INT2_Sources
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @note This function overwrites the INT2_CTRL reg with value of s.
 * 	   	 To enable multiple sources the values of LSM6DSL_INT2_Sources should be ORed.
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::INT2SourceConfig(enum LSM6DSL_INT2_Sources s)
{
	if (s >= 0 && s <= 255)
	{
		return ModifyReg(LSM6DSL_REG::INT2_CTRL, (uint8_t*) &s);
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Enable/Disable block update mode(BDU)
 *
 * @param[in] m 1 to enable, 0 to disable
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::toggleBlockDataUpdate(uint8_t m)
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::CTRL3_C, &t,
			1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
	{
		if (m)
			t |= LSM6DSL_REG::BDU;
		else
			t &= ~LSM6DSL_REG::BDU;

		return ModifyReg(LSM6DSL_REG::CTRL3_C, &t);
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Read accelerometer
 *
 * @param[out] xl pointer to LSM6DSL_AccelRawData structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS reading successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::readAccelData(LSM6DSL_AccelRawData *xl)
{
	if (xl != NULL)
	{
		uint8_t buf[6];
		if (read(chipAddr, LSM6DSL_REG::OUTX_L_XL, buf,
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

/*
 * @brief Read gyroscope
 *
 * @param[out] gy pointer to LSM6DSL_GyroRawData structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS reading successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::readGyroData(LSM6DSL_GyroRawData *gy)
{
	if (gy != NULL)
	{
		uint8_t buf[6];
		if (read(chipAddr, LSM6DSL_REG::OUTX_L_G, buf,
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

/*
 * @brief Converts accelerometer raw data into meter per second squared
 *
 * This function converts a raw accelerometer reading from a given axis
 * into acceleration in meters per second squared, based on the configured
 * full-scale range.
 *
 * @param[in] axisN accelerometer's raw n axis value (e.g x, y or z)
 * @param[in] r accelerometer full scale range (one of LSM6DSL_XL_FS_Range)
 *
 * @return float acceleration in meters per second squared
 */
float convertAccelRawDataTomS2(int16_t axisN, LSM6DSL_XL_FS_Range r)
{
	return ((axisN * LSM6DSL_XL_FS_Sensitivity[r]) * 9.8) / 1000.0;
}

/*
 * @brief Converts gyroscope raw data into degrees per second (dps)
 *
 * This function converts a raw gyroscope reading from a given axis
 * into degrees per second, based on the configured
 * full-scale range.
 *
 * @param[in] axisN gyroscope's raw n axis value (e.g x, y or z)
 * @param[in] r gyroscope's full scale range (one of LSM6DSL_G_FS_Range)
 *
 * @return float rotation speed in degrees per second
 */
float convertGyroRawDataToDPS(int16_t axisN, LSM6DSL_G_FS_Range r)
{
	return (axisN * LSM6DSL_G_FS_Sensitivity[r]) / 1000.0;
}

/*
 * @brief Performs accelerometer self test
 *
 * @attention device must be kept still during self test
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
LSM6DSL_INTF_RET_TYPE LSM6DSL::selfTestAccel()
{
	// the test procedure is described in figure 36 of AN5040
	LSM6DSL_AccelRawData currentAccel, StAccel, noStAccel;
	float accelX, accelY, accelZ;
	uint8_t ptr[10] = { 0x38, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00 };

	if (write(chipAddr, LSM6DSL_REG::CTRL1_XL, ptr,
			10) == LSM6DSL_INTF_RET_TYPE_FAILURE)
		return LSM6DSL_INTF_RET_TYPE_FAILURE;

	delayMs(100);

	memset((void*) &noStAccel, 0, sizeof(noStAccel));
	// self test disable
	for (uint8_t i = 0; i <= 5; i++)
	{
		while (isAccelDataAvailabe() != LSM6DSL_INTF_RET_TYPE_SUCCESS);

		// discard the first sample
		if (i == 0)
		{
			readAccelData(&currentAccel);
			continue;
		}

		readAccelData(&currentAccel);
		// average 5 samples
		noStAccel.x += currentAccel.x / 5;
		noStAccel.y += currentAccel.y / 5;
		noStAccel.z += currentAccel.z / 5;

	}

	// self test enable
	uint8_t st = 0x01;
	if (ModifyReg(LSM6DSL_REG::CTRL5_C, &st) == LSM6DSL_INTF_RET_TYPE_FAILURE)
		return LSM6DSL_INTF_RET_TYPE_FAILURE;

	delayMs(100);
	memset((void*) &StAccel, 0, sizeof(StAccel));

	for (uint8_t i = 0; i <= 5; i++)
	{
		while (isAccelDataAvailabe() != LSM6DSL_INTF_RET_TYPE_SUCCESS);

		// discard the first sample
		if (i == 0)
		{
			readAccelData(&currentAccel);
			continue;
		}

		readAccelData(&currentAccel);
		// average 5 samples
		StAccel.x += currentAccel.x / 5;
		StAccel.y += currentAccel.y / 5;
		StAccel.z += currentAccel.z / 5;

	}

	// store the difference between the value of x, y and z with and without self test
	accelX = static_cast<float>((StAccel.x - noStAccel.x)
			* LSM6DSL_XL_FS_Sensitivity[LSM6DSL_XL_FS_Range::LSM6DSL_XL_FS_4G]);
	accelY = static_cast<float>((StAccel.y - noStAccel.y)
			* LSM6DSL_XL_FS_Sensitivity[LSM6DSL_XL_FS_Range::LSM6DSL_XL_FS_4G]);
	accelZ = static_cast<float>((StAccel.z - noStAccel.z)
			* LSM6DSL_XL_FS_Sensitivity[LSM6DSL_XL_FS_Range::LSM6DSL_XL_FS_4G]);

	st = 0x00;
	if (std::abs(accelX) >= std::abs(MIN_ST_XL)
			&& std::abs(accelX) <= std::abs(MAX_ST_XL)
			&& std::abs(accelY) >= std::abs(MIN_ST_XL)
			&& std::abs(accelY) <= std::abs(MAX_ST_XL)
			&& std::abs(accelZ) >= std::abs(MIN_ST_XL)
			&& std::abs(accelZ) <= std::abs(MAX_ST_XL))
	{
		// disable self test and accelerometer
		if (ModifyReg(LSM6DSL_REG::CTRL5_C,
				&st) == LSM6DSL_INTF_RET_TYPE_SUCCESS && ModifyReg(LSM6DSL_REG::CTRL1_XL,
						&st) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		else
			return LSM6DSL_INTF_RET_TYPE_FAILURE;
	}

	if (ModifyReg(LSM6DSL_REG::CTRL5_C, &st) != LSM6DSL_INTF_RET_TYPE_SUCCESS
			&& ModifyReg(LSM6DSL_REG::CTRL1_XL, &st)
					!= LSM6DSL_INTF_RET_TYPE_SUCCESS)
		return LSM6DSL_INTF_RET_TYPE_FAILURE;

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Performs gyroscope self test
 *
 * @attention device must be kept still during self test
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
LSM6DSL_INTF_RET_TYPE LSM6DSL::selfTestGyro()
{
	// the test procedure is described in figure 37 of AN5040
	LSM6DSL_GyroRawData currentGyro, StGyro, noStGyro;
	float deltaGyroX, deltaGyroY, deltaGyroZ;
	uint8_t ptr[10] = { 0x00, 0x50, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00 };

	if (write(chipAddr, LSM6DSL_REG::CTRL1_XL, ptr,
			10) == LSM6DSL_INTF_RET_TYPE_FAILURE)
		return LSM6DSL_INTF_RET_TYPE_FAILURE;

	delayMs(150);

	memset((void*) &noStGyro, 0, sizeof(noStGyro));
	// self test disable
	for (uint8_t i = 0; i <= 5; i++)
	{
		while (isGyroDataAvailabe() != LSM6DSL_INTF_RET_TYPE_SUCCESS);

		// discard the first sample
		if (i == 0)
		{
			readGyroData(&currentGyro);
			continue;
		}

		readGyroData(&currentGyro);
		// average 5 samples
		noStGyro.x += currentGyro.x / 5;
		noStGyro.y += currentGyro.y / 5;
		noStGyro.z += currentGyro.z / 5;

	}

	// self test enable
	uint8_t st = 0x04;
	if (ModifyReg(LSM6DSL_REG::CTRL5_C, &st) == LSM6DSL_INTF_RET_TYPE_FAILURE)
		return LSM6DSL_INTF_RET_TYPE_FAILURE;

	delayMs(50);
	memset((void*) &StGyro, 0, sizeof(StGyro));

	for (uint8_t i = 0; i <= 5; i++)
	{
		while (isGyroDataAvailabe() != LSM6DSL_INTF_RET_TYPE_SUCCESS);

		// discard the first sample
		if (i == 0)
		{
			readGyroData(&currentGyro);
			continue;
		}

		readGyroData(&currentGyro);
		// average 5 samples
		StGyro.x += currentGyro.x / 5;
		StGyro.y += currentGyro.y / 5;
		StGyro.z += currentGyro.z / 5;

	}

	// store the difference between the value of x, y and z with and without self test
	deltaGyroX = static_cast<float>((StGyro.x - noStGyro.x)
			* LSM6DSL_G_FS_Sensitivity[LSM6DSL_G_FS_Range::LSM6DSL_G_FS_250DPS])
			/ 1000;
	deltaGyroY = static_cast<float>((StGyro.y - noStGyro.y)
			* LSM6DSL_G_FS_Sensitivity[LSM6DSL_G_FS_Range::LSM6DSL_G_FS_250DPS])
			/ 1000;
	deltaGyroZ = static_cast<float>((StGyro.z - noStGyro.z)
			* LSM6DSL_G_FS_Sensitivity[LSM6DSL_G_FS_Range::LSM6DSL_G_FS_250DPS])
			/ 1000;

	st = 0x00;
	if (std::abs(deltaGyroX) >= std::abs(MIN_ST_G_250FS)
			&& std::abs(deltaGyroX) <= std::abs(MAX_ST_G_250FS)
			&& std::abs(deltaGyroY) >= std::abs(MIN_ST_G_250FS)
			&& std::abs(deltaGyroY) <= std::abs(MAX_ST_G_250FS)
			&& std::abs(deltaGyroZ) >= std::abs(MIN_ST_G_250FS)
			&& std::abs(deltaGyroZ) <= std::abs(MAX_ST_G_250FS))
	{
		// disable self test and gyroscope
		if (ModifyReg(LSM6DSL_REG::CTRL5_C,
				&st) == LSM6DSL_INTF_RET_TYPE_SUCCESS && ModifyReg(LSM6DSL_REG::CTRL2_G,
						&st) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		else
			return LSM6DSL_INTF_RET_TYPE_FAILURE;
	}

	if (ModifyReg(LSM6DSL_REG::CTRL5_C, &st) != LSM6DSL_INTF_RET_TYPE_SUCCESS
			&& ModifyReg(LSM6DSL_REG::CTRL2_G, &st)
					!= LSM6DSL_INTF_RET_TYPE_SUCCESS)
		return LSM6DSL_INTF_RET_TYPE_FAILURE;

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Read temperature data
 *
 * @param[out] t Pointer to LSM6DSL_TempData structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS reading successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::readTemperature(LSM6DSL_TempData *t)
{
	if (t != NULL)
	{
		uint8_t buf[2];
		if (read(chipAddr, LSM6DSL_REG::OUT_TEMP_L, buf,
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

/*
 * @brief Set accelerometer analog chain bandwidth for ODR >= 1.67kHz
 *
 * @param[in] m 0 for 1.5kHZ BW, 1 for 400Hz BW
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS pass
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE fail
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::setAccelAnalogChainBW(uint8_t m)
{
	uint8_t t;
	if (read(chipAddr, LSM6DSL_REG::CTRL1_XL, &t,
			1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
	{
		if (m)
			t |= LSM6DSL_REG::BW0_XL;
		else
			t &= ~LSM6DSL_REG::BW0_XL;

		return ModifyReg(LSM6DSL_REG::CTRL1_XL, &t);
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Configure accelerometer digital low pass filter
 *
 * @param[in] bw one of LSM6DSL_XL_LPF_BW values
 * @param[in] LNLL input composite value, 1 = low noise & 0 = low latency
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS pass
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE fail
 *
 * @see table 9 of AN5040 for samples to discard, alternatively use LSM6DSL_setDRDYMask() for ODR/2 & ODR/4
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::configAccelDigitalLPF(LSM6DSL_XL_LPF_BW bw, uint8_t LNLL)
{
	uint8_t ctrl8_xl, ctrl1_xl;
	if (read(chipAddr, LSM6DSL_REG::CTRL8_XL, &ctrl8_xl,
			1) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
		return LSM6DSL_INTF_RET_TYPE_FAILURE;

	if (LNLL)
		ctrl8_xl |= LSM6DSL_REG::INPUT_COMPOSITE; // low noise
	else
		ctrl8_xl &= ~LSM6DSL_REG::INPUT_COMPOSITE; // low latency

	// disable high pass path
	ctrl8_xl &= ~LSM6DSL_REG::HP_SLOPE_XL_EN;
	if (ModifyReg(LSM6DSL_REG::CTRL8_XL,
			&ctrl8_xl) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
		return LSM6DSL_INTF_RET_TYPE_FAILURE;

	switch (bw)
	{
	case LSM6DSL_XL_LPF_BW_ODR_2:
	case LSM6DSL_XL_LPF_BW_ODR_4:

		// disable LPF2 path
		ctrl8_xl &= ~(LSM6DSL_REG::LPF2_XL_EN);
		if (ModifyReg(LSM6DSL_REG::CTRL8_XL,
				&ctrl8_xl) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;

		if (read(chipAddr, LSM6DSL_REG::CTRL1_XL, &ctrl1_xl,
				1) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
			return LSM6DSL_INTF_RET_TYPE_FAILURE;

		if (odr == LSM6DSL_XL_LPF_BW_ODR_4)
			ctrl1_xl |= LSM6DSL_REG::LPF1_BW_SEL;
		else
			ctrl1_xl &= ~(LSM6DSL_REG::LPF1_BW_SEL);

		return ModifyReg(LSM6DSL_REG::CTRL1_XL, &ctrl1_xl);

		break;

	case LSM6DSL_XL_LPF_BW_ODR_50:

		ctrl8_xl |= LSM6DSL_REG::LPF2_XL_EN;
		ctrl8_xl &= ~(LSM6DSL_REG::HPCF_XL1 | LSM6DSL_REG::HPCF_XL0);

		return ModifyReg(LSM6DSL_REG::CTRL8_XL, &ctrl8_xl);
		break;

	case LSM6DSL_XL_LPF_BW_ODR_100:
		ctrl8_xl |= LSM6DSL_REG::LPF2_XL_EN | LSM6DSL_REG::HPCF_XL0;
		ctrl8_xl &= ~(LSM6DSL_REG::HPCF_XL1);

		return ModifyReg(LSM6DSL_REG::CTRL8_XL, &ctrl8_xl);
		break;

	case LSM6DSL_XL_LPF_BW_ODR_9:
		ctrl8_xl |= LSM6DSL_REG::LPF2_XL_EN | LSM6DSL_REG::HPCF_XL1;
		ctrl8_xl &= ~(LSM6DSL_REG::HPCF_XL0);

		return ModifyReg(LSM6DSL_REG::CTRL8_XL, &ctrl8_xl);
		break;

	case LSM6DSL_XL_LPF_BW_ODR_400:
		ctrl8_xl |= LSM6DSL_REG::LPF2_XL_EN | LSM6DSL_REG::HPCF_XL1
				| LSM6DSL_REG::HPCF_XL0;

		return ModifyReg(LSM6DSL_REG::CTRL8_XL, &ctrl8_xl);
		break;
	default:
		// incorrect value
		return LSM6DSL_INTF_RET_TYPE_FAILURE;
		break;
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

/*
 * @brief Configure accelerometer digital high pass filter
 *
 * @param[in] bw one of LSM6DSL_XL_HPF_BW values
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS pass
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE fail
 *
 * @see table 9 of AN5040 for samples to discard
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::configAccelDigitalHPF(LSM6DSL_XL_HPF_BW bw)
{
	uint8_t ctrl8_xl;
	if (read(chipAddr, LSM6DSL_REG::CTRL8_XL, &ctrl8_xl,
			1) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
		return LSM6DSL_INTF_RET_TYPE_FAILURE;

	ctrl8_xl &= ~LSM6DSL_REG::INPUT_COMPOSITE; // low latency

	switch (bw)
	{
	case LSM6DSL_XL_HPF_BW_ODR_4:
		ctrl8_xl &= ~(LSM6DSL_REG::HPCF_XL1 | LSM6DSL_REG::HPCF_XL0);
		break;

	case LSM6DSL_XL_HPF_BW_ODR_100:
		ctrl8_xl |= (LSM6DSL_REG::HPCF_XL0);
		ctrl8_xl &= ~(LSM6DSL_REG::HPCF_XL1);
		break;

	case LSM6DSL_XL_HPF_BW_ODR_9:
		ctrl8_xl |= (LSM6DSL_REG::HPCF_XL1);
		ctrl8_xl &= ~(LSM6DSL_REG::HPCF_XL0);
		break;

	case LSM6DSL_XL_HPF_BW_ODR_400:
		ctrl8_xl |= (LSM6DSL_REG::HPCF_XL0 | LSM6DSL_REG::HPCF_XL1);
		break;

	default:
		// incorrect value
		return LSM6DSL_INTF_RET_TYPE_FAILURE;
		break;
	}

	return ModifyReg(LSM6DSL_REG::CTRL8_XL, &ctrl8_xl);

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL::configGyroHPF(LSM6DSL_G_HPF_BW bw)
{
	uint8_t ctrl7_G;

	if (read(chipAddr, LSM6DSL_REG::CTRL7_G, &ctrl7_G,
			1) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
		return LSM6DSL_INTF_RET_TYPE_FAILURE;

	ctrl7_G &= ~(LSM6DSL_REG::HPM0_G | LSM6DSL_REG::HPM1_G);

	switch (bw)
	{
	case LSM6DSL_G_HPF_BW_0_016Hz:
		break;

	case LSM6DSL_G_HPF_BW_0_065Hz:
		ctrl7_G |= LSM6DSL_REG::HPM0_G;
		break;

	case LSM6DSL_G_HPF_BW_0_260Hz:
		ctrl7_G |= LSM6DSL_REG::HPM1_G;
		break;

	case LSM6DSL_G_HPF_BW_1_04Hz:
		ctrl7_G |= LSM6DSL_REG::HPM0_G | LSM6DSL_REG::HPM1_G;
		break;

	default:
		// incorrect value
		return LSM6DSL_INTF_RET_TYPE_FAILURE;
		break;
	}

	return ModifyReg(LSM6DSL_REG::CTRL7_G, &ctrl7_G);
}

/*
 * @brief Enable/Disable data ready (DRDY) mask functionality
 *
 * @param[in] m 1 to enable, 0 to disable
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - LSM6DSL_INTF_RET_TYPE_SUCCESS setting successful
 * 		   - LSM6DSL_INTF_RET_TYPE_FAILURE error
 *
 * @note Data ready mask only works for accelerometer LPF1 and gyroscope's LPF2 digital filters.
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL::toggleDataReadyMask(uint8_t m)
{
	uint8_t ctrl4_c;
	if (read(chipAddr, LSM6DSL_REG::CTRL4_C, &ctrl4_c,
			1) != LSM6DSL_INTF_RET_TYPE_SUCCESS)
		return LSM6DSL_INTF_RET_TYPE_FAILURE;

	if (m)
		ctrl4_c |= LSM6DSL_REG::DRDY_MASK;
	else
		ctrl4_c &= ~LSM6DSL_REG::DRDY_MASK;

	return ModifyReg(LSM6DSL_REG::CTRL4_C, &ctrl4_c);

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

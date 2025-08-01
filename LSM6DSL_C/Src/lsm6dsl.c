/*
 * lsm6dsl.c
 *
 *  Created on: Jul 28, 2025
 *      Author: farhan
 */

#include "lsm6dsl_reg.h"
#include "lsm6dsl.h"
#include "lsm6dsl_port.h"

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

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAllIRQonINT1(LSM6DSL *dev, uint8_t en)
{
	if (dev != NULL)
	{
		uint8_t t, reg;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL4_C, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (en)
				t |= INT2_on_INT1;
			else
				t &= ~INT2_on_INT1;

			if (dev->write(dev->hInterface, dev->chipAddr, CTRL4_C, &t,
					1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			{
				// verify the written value
				if ((dev->read(dev->hInterface, dev->chipAddr, CTRL4_C, &reg, 1)
						== LSM6DSL_INTF_RET_TYPE_SUCCESS) && (reg == t))
					return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			}
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelODR(LSM6DSL *dev, enum LSM6DSL_XL_ODR m)
{
	if (dev != NULL)
	{
		uint8_t t, reg;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL1_XL, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			t &= 0x0F;	// clear the ODR_XLn bits
			switch (m)
			{
			case XL_ODR_POWER_DOWN:
				break;
			case XL_ODR_12_5Hz:
			case XL_ODR_26Hz:
			case XL_ODR_52Hz:
			case XL_ODR_104Hz:
			case XL_ODR_208Hz:
			case XL_ODR_416Hz:
			case XL_ODR_833Hz:
			case XL_ODR_1_66kHz:
			case XL_ODR_3_33kHz:
			case XL_ODR_6_66kHz:
			case XL_ODR_1_6Hz:
				t |= (m << ODR_XL0_Pos );
				break;

			default:
				// incorrect values
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			if (dev->write(dev->hInterface, dev->chipAddr, CTRL1_XL, &t,
					1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			{
				// verify the written value
				if ((dev->read(dev->hInterface, dev->chipAddr, CTRL1_XL, &reg,
						1) == LSM6DSL_INTF_RET_TYPE_SUCCESS) && (reg == t))
					return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			}
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
		uint8_t t, reg;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL2_G, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			t &= 0x0E;	// clear the ODR_Gn bits
			switch (m)
			{
			case G_ODR_POWER_DOWN:
				break;
			case G_ODR_12_5Hz:
			case G_ODR_26Hz:
			case G_ODR_52Hz:
			case G_ODR_104Hz:
			case G_ODR_208Hz:
			case G_ODR_416Hz:
			case G_ODR_833Hz:
			case G_ODR_1_66kHz:
			case G_ODR_3_33kHz:
			case G_ODR_6_66kHz:
				t |= (m << ODR_G0_Pos );
				break;

			default:
				// incorrect values
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			if (dev->write(dev->hInterface, dev->chipAddr, CTRL2_G, &t,
					1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			{
				// verify the written value
				if ((dev->read(dev->hInterface, dev->chipAddr, CTRL2_G, &reg, 1)
						== LSM6DSL_INTF_RET_TYPE_SUCCESS) && (reg == t))
					return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			}
		}
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelFSRange(LSM6DSL *dev,
		enum LSM6DSL_XL_FS_Range r)
{
	if (dev != NULL)
	{
		uint8_t t, reg;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL1_XL, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			t &= 0xF3;	// clear the FS_XLn bits
			switch (r)
			{
			case XL_FS_2G:
				break;
			case XL_FS_4G:
			case XL_FS_8G:
			case XL_FS_16G:
				t |= (r << FS_XL0_Pos );
				break;
			default:
				// incorrect values
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			if (dev->write(dev->hInterface, dev->chipAddr, CTRL1_XL, &t,
					1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			{
				// verify the written value
				if ((dev->read(dev->hInterface, dev->chipAddr, CTRL1_XL, &reg,
						1) == LSM6DSL_INTF_RET_TYPE_SUCCESS) && (reg == t))
					return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			}
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setGyroFSRange(LSM6DSL *dev,
		enum LSM6DSL_G_FS_Range r)
{
	if (dev != NULL)
	{
		uint8_t t, reg;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL2_G, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			t &= 0xF0;	// clear the FS_Gn and FS_G125 bits
			switch (r)
			{
			case G_FS_250DPS:
				break;
			case G_FS_500DPS:
			case G_FS_1000DPS:
			case G_FS_2000DPS:
				t |= (r << FS_G0_Pos );
				break;

			case G_FS_125DPS:
				t |= FS_125;
				break;
			default:
				// incorrect values
				return LSM6DSL_INTF_RET_TYPE_FAILURE;
				break;
			}

			if (dev->write(dev->hInterface, dev->chipAddr, CTRL2_G, &t,
					1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			{
				// verify the written value
				if ((dev->read(dev->hInterface, dev->chipAddr, CTRL2_G, &reg, 1)
						== LSM6DSL_INTF_RET_TYPE_SUCCESS) && (reg == t))
					return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			}
		}
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelHighPerfMode(LSM6DSL *dev,
		enum LSM6DSL_XL_G_HM_MODE m)
{
	if (dev != NULL)
	{
		uint8_t t, reg;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL6_C, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (XL_G_HM_MODE_ON)
				t &= ~XL_HM_MODE;
			else
				t |= XL_HM_MODE;

			if (dev->write(dev->hInterface, dev->chipAddr, CTRL6_C, &t,
					1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			{
				// verify the written value
				if ((dev->read(dev->hInterface, dev->chipAddr, CTRL6_C, &reg, 1)
						== LSM6DSL_INTF_RET_TYPE_SUCCESS) && (reg == t))
					return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			}
		}

	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_setGyroHighPerfMode(LSM6DSL *dev,
		enum LSM6DSL_XL_G_HM_MODE m)
{
	if (dev != NULL)
	{
		uint8_t t, reg;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL7_G, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (XL_G_HM_MODE_ON)
				t &= ~G_HM_MODE;
			else
				t |= G_HM_MODE;

			if (dev->write(dev->hInterface, dev->chipAddr, CTRL7_G, &t,
					1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			{
				// verify the written value
				if ((dev->read(dev->hInterface, dev->chipAddr, CTRL7_G, &reg, 1)
						== LSM6DSL_INTF_RET_TYPE_SUCCESS) && (reg == t))
					return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			}
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

LSM6DSL_INTF_RET_TYPE LSM6DSL_INT1SourceConfig(LSM6DSL *dev,
		enum LSM6DSL_INT1_Sources s)
{
	if (dev != NULL)
	{
		uint8_t reg;
		if (s >= 0 && s <= 255)
		{
			if (dev->write(dev->hInterface, dev->chipAddr, INT1_CTRL, &s,
					1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			{
				// verify the written value
				if ((dev->read(dev->hInterface, dev->chipAddr, INT1_CTRL, &reg,
						1) == LSM6DSL_INTF_RET_TYPE_SUCCESS) && (reg == s))
					return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			}
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_INT2SourceConfig(LSM6DSL *dev,
		enum LSM6DSL_INT2_Sources s)
{
	if (dev != NULL)
	{
		uint8_t reg;
		if (s >= 0 && s <= 255)
		{
			if (dev->write(dev->hInterface, dev->chipAddr, INT2_CTRL, &s,
					1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			{
				// verify the written value
				if ((dev->read(dev->hInterface, dev->chipAddr, INT2_CTRL, &reg,
						1) == LSM6DSL_INTF_RET_TYPE_SUCCESS) && (reg == s))
					return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			}
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_toggleBlockDataUpdate(LSM6DSL *dev, uint8_t m)
{
	if (dev != NULL)
	{
		uint8_t t, reg;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL3_C, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (m)
				t |= BDU;
			else
				t &= ~BDU;

			if (dev->write(dev->hInterface, dev->chipAddr, CTRL3_C, &t,
					1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
			{
				// verify the written value
				if ((dev->read(dev->hInterface, dev->chipAddr, CTRL3_C, &reg, 1)
						== LSM6DSL_INTF_RET_TYPE_SUCCESS) && (reg == t))
					return LSM6DSL_INTF_RET_TYPE_SUCCESS;
			}
		}
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_readAccelData(LSM6DSL *dev, struct AccelData *xl)
{
	if (dev != NULL && xl != NULL)
	{
		if (dev->read(dev->hInterface, dev->chipAddr, OUTX_L_XL, xl,
				6) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_readGyroData(LSM6DSL *dev, struct GyroData *gy)
{
	if (dev != NULL && gy != NULL)
	{
		if (dev->read(dev->hInterface, dev->chipAddr, OUTX_L_G, gy,
				6) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			return LSM6DSL_INTF_RET_TYPE_SUCCESS;
		}
	}
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

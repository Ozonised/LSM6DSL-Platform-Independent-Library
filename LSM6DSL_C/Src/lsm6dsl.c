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

LSM6DSL_INTF_RET_TYPE LSM6DSL_setAccelODR(LSM6DSL *dev, enum LSM6DSL_XL_ODR m)
{
	if (dev != NULL)
	{
		uint8_t t;
		if (dev->read(dev->hInterface, dev->chipAddr, CTRL1_XL, &t,
				1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			switch (m)
			{
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
				t &= 0x0F;	// clear the ODR_XLn bits
				t |= (m << ODR_XL0_Pos );

				if (dev->write(dev->hInterface, dev->chipAddr, CTRL1_XL, &t,
						1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
					return LSM6DSL_INTF_RET_TYPE_SUCCESS;
				break;

			default:
				break;
			}
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
			switch (m)
			{
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
				t &= 0x0E;	// clear the ODR_Gn bits
				t |= (m << ODR_G0_Pos );

				if (dev->write(dev->hInterface, dev->chipAddr, CTRL2_G, &t,
						1) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
					return LSM6DSL_INTF_RET_TYPE_SUCCESS;
				break;

			default:
				break;
			}
		}
	}

	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}


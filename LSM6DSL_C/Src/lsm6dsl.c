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
		if (dev->read(dev->hInterface, dev->chipAddr, WHO_AM_I, &t, 1)
				== LSM6DSL_INTF_RET_TYPE_SUCCESS)
		{
			if (t == WHO_AM_I_VAL)
				return 1;
		}
	}
	return 0;
}

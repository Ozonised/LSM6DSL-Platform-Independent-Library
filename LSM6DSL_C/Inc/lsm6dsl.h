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

/*
 * @brief Checks if the LSM6DSL is present on the bus
 *
 * @param[in] dev Pointer to the LSM6DSL structure
 *
 * @return LSM6DSL_INTF_RET_TYPE
 * 		   - 1 if the device is present
 * 		   - 0 absent, error
 */
LSM6DSL_INTF_RET_TYPE LSM6DSL_IsPresent(LSM6DSL *dev);
#endif /* LSM6DSL_LSM6DSL_H_ */

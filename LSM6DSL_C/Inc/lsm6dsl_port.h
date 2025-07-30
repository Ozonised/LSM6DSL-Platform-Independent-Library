/*
 * lsm6dsl_port.h
 *
 *  Created on: Jul 28, 2025
 *      Author: farhan
 */

#ifndef LSM6DSL_PORT_H_
#define LSM6DSL_PORT_H_
#include <stdint.h>

#ifndef LSM6DSL_INTF_RET_TYPE
#define LSM6DSL_INTF_RET_TYPE int8_t
#endif

#ifndef LSM6DSL_INTF_RET_TYPE_SUCCESS
#define LSM6DSL_INTF_RET_TYPE_SUCCESS 0
#endif

LSM6DSL_INTF_RET_TYPE LSM6DSL_PortI2CReadReg(void *hinterface, uint8_t chipAddr,
		uint8_t RegAddr, uint8_t *buf, uint16_t len);

LSM6DSL_INTF_RET_TYPE LSM6DSL_PortI2CWriteReg(void *hinterface,
		uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len);

void LSM6DSL_PortDelayMs(void *hinterface, uint32_t ms);

#endif /* LSM6DSL_LSM6DSL_PORT_H_ */

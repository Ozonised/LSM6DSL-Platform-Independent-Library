/*
 * lsm6dsl_port.cpp
 *
 *  Created on: Aug 9, 2025
 *      Author: farhan
 */

#include "lsm6dsl_port.hpp"
#include "lsm6dsl.hpp"

__attribute__((weak)) LSM6DSL_INTF_RET_TYPE LSM6DSL::read(uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len)
{
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

__attribute__((weak)) LSM6DSL_INTF_RET_TYPE LSM6DSL::write(uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len)
{
	return LSM6DSL_INTF_RET_TYPE_FAILURE;
}

__attribute__((weak)) void LSM6DSL::delayMs(uint32_t ms)
{

}


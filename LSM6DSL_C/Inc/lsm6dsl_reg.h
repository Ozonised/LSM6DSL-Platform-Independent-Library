/*
 * lsm6dsl_reg.h
 *
 *  Created on: Jul 28, 2025
 *      Author: farhan
 */

#ifndef LSM6DSL_REG_H_
#define LSM6DSL_REG_H_

#include <stdint.h>

#define FUNC_CFG_ACCESS           (uint8_t)0x01
#define SENSOR_SYNC_TIME_FRAME    (uint8_t)0x04
#define SENSOR_SYNC_RES_RATIO     (uint8_t)0x05
#define FIFO_CTRL1                (uint8_t)0x06
#define FIFO_CTRL2                (uint8_t)0x07
#define FIFO_CTRL3                (uint8_t)0x08
#define FIFO_CTRL4                (uint8_t)0x09
#define FIFO_CTRL5                (uint8_t)0x0A
#define DRDY_PULSE_CFG_G          (uint8_t)0x0B
#define INT1_CTRL                 (uint8_t)0x0D
#define INT2_CTRL                 (uint8_t)0x0E
#define WHO_AM_I                  (uint8_t)0x0F
#define CTRL1_XL                  (uint8_t)0x10
#define CTRL2_G                   (uint8_t)0x11
#define CTRL3_C                   (uint8_t)0x12
#define CTRL4_C                   (uint8_t)0x13
#define CTRL5_C                   (uint8_t)0x14
#define CTRL6_C                   (uint8_t)0x15
#define CTRL7_G                   (uint8_t)0x16
#define CTRL8_XL                  (uint8_t)0x17
#define CTRL9_XL                  (uint8_t)0x18
#define CTRL10_C                  (uint8_t)0x19
#define MASTER_CONFIG             (uint8_t)0x1A
#define WAKE_UP_SRC               (uint8_t)0x1B
#define TAP_SRC                   (uint8_t)0x1C
#define D6D_SRC                   (uint8_t)0x1D
#define STATUS_REG                (uint8_t)0x1E
#define OUT_TEMP_L                (uint8_t)0x20
#define OUT_TEMP_H                (uint8_t)0x21
#define OUTX_L_G                  (uint8_t)0x22
#define OUTX_H_G                  (uint8_t)0x23
#define OUTY_L_G                  (uint8_t)0x24
#define OUTY_H_G                  (uint8_t)0x25
#define OUTZ_L_G                  (uint8_t)0x26
#define OUTZ_H_G                  (uint8_t)0x27
#define OUTX_L_XL                 (uint8_t)0x28
#define OUTX_H_XL                 (uint8_t)0x29
#define OUTY_L_XL                 (uint8_t)0x2A
#define OUTY_H_XL                 (uint8_t)0x2B
#define OUTZ_L_XL                 (uint8_t)0x2C
#define OUTZ_H_XL                 (uint8_t)0x2D
#define SENSORHUB1_REG            (uint8_t)0x2E
#define SENSORHUB2_REG            (uint8_t)0x2F
#define SENSORHUB3_REG            (uint8_t)0x30
#define SENSORHUB4_REG            (uint8_t)0x31
#define SENSORHUB5_REG            (uint8_t)0x32
#define SENSORHUB6_REG            (uint8_t)0x33
#define SENSORHUB7_REG            (uint8_t)0x34
#define SENSORHUB8_REG            (uint8_t)0x35
#define SENSORHUB9_REG            (uint8_t)0x36
#define SENSORHUB10_REG           (uint8_t)0x37
#define SENSORHUB11_REG           (uint8_t)0x38
#define SENSORHUB12_REG           (uint8_t)0x39
#define FIFO_STATUS1              (uint8_t)0x3A
#define FIFO_STATUS2              (uint8_t)0x3B
#define FIFO_STATUS3              (uint8_t)0x3C
#define FIFO_STATUS4              (uint8_t)0x3D
#define FIFO_DATA_OUT_L           (uint8_t)0x3E
#define FIFO_DATA_OUT_H           (uint8_t)0x3F
#define TIMESTAMP0_REG            (uint8_t)0x40
#define TIMESTAMP1_REG            (uint8_t)0x41
#define TIMESTAMP2_REG            (uint8_t)0x42
#define STEP_TIMESTAMP_L          (uint8_t)0x49
#define STEP_TIMESTAMP_H          (uint8_t)0x4A
#define STEP_COUNTER_L            (uint8_t)0x4B
#define STEP_COUNTER_H            (uint8_t)0x4C
#define SENSORHUB13_REG           (uint8_t)0x4D
#define SENSORHUB14_REG           (uint8_t)0x4E
#define SENSORHUB15_REG           (uint8_t)0x4F
#define SENSORHUB16_REG           (uint8_t)0x50
#define SENSORHUB17_REG           (uint8_t)0x51
#define SENSORHUB18_REG           (uint8_t)0x52
#define FUNC_SRC1                 (uint8_t)0x53
#define FUNC_SRC2                 (uint8_t)0x54
#define WRIST_TILT_IA             (uint8_t)0x55
#define TAP_CFG                   (uint8_t)0x58
#define TAP_THS_6D                (uint8_t)0x59
#define INT_DUR2                  (uint8_t)0x5A
#define WAKE_UP_THS               (uint8_t)0x5B
#define WAKE_UP_DUR               (uint8_t)0x5C
#define FREE_FALL                 (uint8_t)0x5D
#define MD1_CFG                   (uint8_t)0x5E
#define MD2_CFG                   (uint8_t)0x5F
#define MASTER_CMD_CODE           (uint8_t)0x60
#define SENS_SYNC_SPI_ERROR_CODE  (uint8_t)0x61
#define OUT_MAG_RAW_X_L           (uint8_t)0x66
#define OUT_MAG_RAW_X_H           (uint8_t)0x67
#define OUT_MAG_RAW_Y_L           (uint8_t)0x68
#define OUT_MAG_RAW_Y_H           (uint8_t)0x69
#define OUT_MAG_RAW_Z_L           (uint8_t)0x6A
#define OUT_MAG_RAW_Z_H           (uint8_t)0x6B
#define X_OFS_USR                 (uint8_t)0x73
#define Y_OFS_USR                 (uint8_t)0x74
#define Z_OFS_USR                 (uint8_t)0x75

#define WHO_AM_I_VAL			  (uint8_t)0x6A

#endif /* LSM6DSL_LSM6DSL_REG_H_ */

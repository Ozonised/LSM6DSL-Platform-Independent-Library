/*
 * lsm6dsl_reg.h
 *
 *  Created on: Jul 28, 2025
 *      Author: farhan
 */

#ifndef LSM6DSL_REG_H_
#define LSM6DSL_REG_H_

#include <stdint.h>

/*
 * Register Definiton
 */
#define LSM6DSL_FUNC_CFG_ACCESS           (uint8_t)0x01
#define LSM6DSL_SENSOR_SYNC_TIME_FRAME    (uint8_t)0x04
#define LSM6DSL_SENSOR_SYNC_RES_RATIO     (uint8_t)0x05
#define LSM6DSL_FIFO_CTRL1                (uint8_t)0x06
#define LSM6DSL_FIFO_CTRL2                (uint8_t)0x07
#define LSM6DSL_FIFO_CTRL3                (uint8_t)0x08
#define LSM6DSL_FIFO_CTRL4                (uint8_t)0x09
#define LSM6DSL_FIFO_CTRL5                (uint8_t)0x0A
#define LSM6DSL_DRDY_PULSE_CFG_G          (uint8_t)0x0B
#define LSM6DSL_INT1_CTRL                 (uint8_t)0x0D
#define LSM6DSL_INT2_CTRL                 (uint8_t)0x0E
#define LSM6DSL_WHO_AM_I                  (uint8_t)0x0F
#define LSM6DSL_CTRL1_XL                  (uint8_t)0x10
#define LSM6DSL_CTRL2_G                   (uint8_t)0x11
#define LSM6DSL_CTRL3_C                   (uint8_t)0x12
#define LSM6DSL_CTRL4_C                   (uint8_t)0x13
#define LSM6DSL_CTRL5_C                   (uint8_t)0x14
#define LSM6DSL_CTRL6_C                   (uint8_t)0x15
#define LSM6DSL_CTRL7_G                   (uint8_t)0x16
#define LSM6DSL_CTRL8_XL                  (uint8_t)0x17
#define LSM6DSL_CTRL9_XL                  (uint8_t)0x18
#define LSM6DSL_                  (uint8_t)0x19
#define LSM6DSL_MASTER_CONFIG             (uint8_t)0x1A
#define LSM6DSL_WAKE_UP_SRC               (uint8_t)0x1B
#define LSM6DSL_TAP_SRC                   (uint8_t)0x1C
#define LSM6DSL_D6D_SRC                   (uint8_t)0x1D
#define LSM6DSL_STATUS_REG                (uint8_t)0x1E
#define LSM6DSL_OUT_TEMP_L                (uint8_t)0x20
#define LSM6DSL_OUT_TEMP_H                (uint8_t)0x21
#define LSM6DSL_OUTX_L_G                  (uint8_t)0x22
#define LSM6DSL_OUTX_H_G                  (uint8_t)0x23
#define LSM6DSL_OUTY_L_G                  (uint8_t)0x24
#define LSM6DSL_OUTY_H_G                  (uint8_t)0x25
#define LSM6DSL_OUTZ_L_G                  (uint8_t)0x26
#define LSM6DSL_OUTZ_H_G                  (uint8_t)0x27
#define LSM6DSL_OUTX_L_XL                 (uint8_t)0x28
#define LSM6DSL_OUTX_H_XL                 (uint8_t)0x29
#define LSM6DSL_OUTY_L_XL                 (uint8_t)0x2A
#define LSM6DSL_OUTY_H_XL                 (uint8_t)0x2B
#define LSM6DSL_OUTZ_L_XL                 (uint8_t)0x2C
#define LSM6DSL_OUTZ_H_XL                 (uint8_t)0x2D
#define LSM6DSL_SENSORHUB1_REG            (uint8_t)0x2E
#define LSM6DSL_SENSORHUB2_REG            (uint8_t)0x2F
#define LSM6DSL_SENSORHUB3_REG            (uint8_t)0x30
#define LSM6DSL_SENSORHUB4_REG            (uint8_t)0x31
#define LSM6DSL_SENSORHUB5_REG            (uint8_t)0x32
#define LSM6DSL_SENSORHUB6_REG            (uint8_t)0x33
#define LSM6DSL_SENSORHUB7_REG            (uint8_t)0x34
#define LSM6DSL_SENSORHUB8_REG            (uint8_t)0x35
#define LSM6DSL_SENSORHUB9_REG            (uint8_t)0x36
#define LSM6DSL_SENSORHUB10_REG           (uint8_t)0x37
#define LSM6DSL_SENSORHUB11_REG           (uint8_t)0x38
#define LSM6DSL_SENSORHUB12_REG           (uint8_t)0x39
#define LSM6DSL_FIFO_STATUS1              (uint8_t)0x3A
#define LSM6DSL_FIFO_STATUS2              (uint8_t)0x3B
#define LSM6DSL_FIFO_STATUS3              (uint8_t)0x3C
#define LSM6DSL_FIFO_STATUS4              (uint8_t)0x3D
#define LSM6DSL_FIFO_DATA_OUT_L           (uint8_t)0x3E
#define LSM6DSL_FIFO_DATA_OUT_H           (uint8_t)0x3F
#define LSM6DSL_TIMESTAMP0_REG            (uint8_t)0x40
#define LSM6DSL_TIMESTAMP1_REG            (uint8_t)0x41
#define LSM6DSL_TIMESTAMP2_REG            (uint8_t)0x42
#define LSM6DSL_STEP_TIMESTAMP_L          (uint8_t)0x49
#define LSM6DSL_STEP_TIMESTAMP_H          (uint8_t)0x4A
#define LSM6DSL_STEP_COUNTER_L            (uint8_t)0x4B
#define LSM6DSL_STEP_COUNTER_H            (uint8_t)0x4C
#define LSM6DSL_SENSORHUB13_REG           (uint8_t)0x4D
#define LSM6DSL_SENSORHUB14_REG           (uint8_t)0x4E
#define LSM6DSL_SENSORHUB15_REG           (uint8_t)0x4F
#define LSM6DSL_SENSORHUB16_REG           (uint8_t)0x50
#define LSM6DSL_SENSORHUB17_REG           (uint8_t)0x51
#define LSM6DSL_SENSORHUB18_REG           (uint8_t)0x52
#define LSM6DSL_FUNC_SRC1                 (uint8_t)0x53
#define LSM6DSL_FUNC_SRC2                 (uint8_t)0x54
#define LSM6DSL_WRIST_TILT_IA_0             (uint8_t)0x55
#define LSM6DSL_TAP_CFG                   (uint8_t)0x58
#define LSM6DSL_TAP_THS_6D                (uint8_t)0x59
#define LSM6DSL_INT_DUR2                  (uint8_t)0x5A
#define LSM6DSL_WAKE_UP_THS               (uint8_t)0x5B
#define LSM6DSL_WAKE_UP_DUR               (uint8_t)0x5C
#define LSM6DSL_FREE_FALL                 (uint8_t)0x5D
#define LSM6DSL_MD1_CFG                   (uint8_t)0x5E
#define LSM6DSL_MD2_CFG                   (uint8_t)0x5F
#define LSM6DSL_MASTER_CMD_CODE           (uint8_t)0x60
#define LSM6DSL_SENS_SYNC_SPI_ERROR_CODE  (uint8_t)0x61
#define LSM6DSL_OUT_MAG_RAW_X_L           (uint8_t)0x66
#define LSM6DSL_OUT_MAG_RAW_X_H           (uint8_t)0x67
#define LSM6DSL_OUT_MAG_RAW_Y_L           (uint8_t)0x68
#define LSM6DSL_OUT_MAG_RAW_Y_H           (uint8_t)0x69
#define LSM6DSL_OUT_MAG_RAW_Z_L           (uint8_t)0x6A
#define LSM6DSL_OUT_MAG_RAW_Z_H           (uint8_t)0x6B
#define LSM6DSL_X_OFS_USR                 (uint8_t)0x73
#define LSM6DSL_Y_OFS_USR                 (uint8_t)0x74
#define LSM6DSL_Z_OFS_USR                 (uint8_t)0x75

#define LSM6DSL_WHO_AM_I_VAL			  (uint8_t)0x6A

/*
 *	Registers Bit positions
 */

// FUNC_CFG_ACCESS
#define LSM6DSL_FUNC_CFG_EN (uint8_t)(1 << 7)
#define FUNC_CFG_EN_B (uint8_t) (1 << 5)

// SENSOR_SYNC_TIME_FRAME
#define LSM6DSL_TPH_0 (uint8_t) (1 << 0)
#define LSM6DSL_TPH_1 (uint8_t) (1 << 1)
#define LSM6DSL_TPH_2 (uint8_t) (1 << 2)
#define LSM6DSL_TPH_3 (uint8_t) (1 << 3)

// SENSOR_SYNC_RES_RATIO
#define LSM6DSL_RR_0 (uint8_t) (1 << 0)
#define LSM6DSL_RR_1 (uint8_t) (1 << 1)

// FIFO_CTRL1
#define LSM6DSL_FTH_0 (uint8_t) (1 << 0)
#define LSM6DSL_FTH_1 (uint8_t) (1 << 1)
#define LSM6DSL_FTH_2 (uint8_t) (1 << 2)
#define LSM6DSL_FTH_3 (uint8_t) (1 << 3)
#define LSM6DSL_FTH_4 (uint8_t) (1 << 4)
#define LSM6DSL_FTH_5 (uint8_t) (1 << 5)
#define LSM6DSL_FTH_6 (uint8_t) (1 << 6)
#define LSM6DSL_FTH_7 (uint8_t) (1 << 7)

// FIFO_CTRL2
#define LSM6DSL_FTH_8 (uint8_t) (1 << 0)
#define LSM6DSL_FTH_9 (uint8_t) (1 << 1)
#define LSM6DSL_FTH_10 (uint8_t) (1 << 2)
#define LSM6DSL_TIMER_PEDO_FIFO_DRDY (uint8_t) (1 << 6)
#define LSM6DSL_TIMER_PEDO_FIFO_EN (uint8_t) (1 << 7)

// FIFO_CTRL3
#define LSM6DSL_DEC_FIFO_XL0 (uint8_t) (1 << 0)
#define LSM6DSL_DEC_FIFO_XL1 (uint8_t) (1 << 1)
#define LSM6DSL_DEC_FIFO_XL2 (uint8_t) (1 << 2)
#define LSM6DSL_DEC_FIFO_GYRO0 (uint8_t) (1 << 3)
#define LSM6DSL_DEC_FIFO_GYRO1 (uint8_t) (1 << 4)
#define LSM6DSL_DEC_FIFO_GYRO2 (uint8_t) (1 << 5)

// FIFO_CTRL4
#define LSM6DSL_DEC_DS3_FIFO0 (uint8_t) (1 << 0)
#define LSM6DSL_DEC_DS3_FIFO1 (uint8_t) (1 << 1)
#define LSM6DSL_DEC_DS3_FIFO2 (uint8_t) (1 << 2)
#define LSM6DSL_DEC_DS4_FIFO0 (uint8_t) (1 << 3)
#define LSM6DSL_DEC_DS4_FIFO1 (uint8_t) (1 << 4)
#define LSM6DSL_DEC_DS4_FIFO2 (uint8_t) (1 << 5)
#define LSM6DSL_ONLY_HIGH_DATA (uint8_t) (1 << 6)
#define LSM6DSL_STOP_ON_FTH (uint8_t) (1 << 7)

// FIFO_CTRL5
#define LSM6DSL_FIFO_MODE_0 (uint8_t) (1 << 0)
#define LSM6DSL_FIFO_MODE_1 (uint8_t) (1 << 1)
#define LSM6DSL_FIFO_MODE_2 (uint8_t) (1 << 2)
#define LSM6DSL_ODR_FIFO_0 (uint8_t) (1 << 3)
#define LSM6DSL_ODR_FIFO_1 (uint8_t) (1 << 4)
#define LSM6DSL_ODR_FIFO_2 (uint8_t) (1 << 5)
#define LSM6DSL_ODR_FIFO_3 (uint8_t) (1 << 6)

// DRDY_PULSE_CFG_G
#define LSM6DSL_INT2_WRIST_TILT (uint8_t) (1 << 0)
#define LSM6DSL_DRDY_PULSED (uint8_t) (1 << 7)

// INT1_CTRL
//#define INT1_DRDY_XL (uint8_t) (1 << 0)
//#define INT1_DRDY_G (uint8_t) (1 << 1)
//#define INT1_BOOT (uint8_t) (1 << 2)
//#define INT1_FTH (uint8_t) (1 << 3)
//#define INT1_FIFO_OVR (uint8_t) (1 << 4)
//#define INT1_FULL_FLAG (uint8_t) (1 << 5)
//#define INT1_SIGN_MOT (uint8_t) (1 << 6)
//#define INT1_STEP_DETECTOR (uint8_t) (1 << 7)

// INT2_CTRL
//#define INT2_DRDY_XL        (uint8_t)(1 << 0)
//#define INT2_DRDY_G         (uint8_t)(1 << 1)
//#define INT2_DRDY_TEMP      (uint8_t)(1 << 2)
//#define INT2_FTH            (uint8_t)(1 << 3)
//#define INT2_FIFO_OVR       (uint8_t)(1 << 4)
//#define INT2_FULL_FLAG      (uint8_t)(1 << 5)
//#define INT2_STEP_COUNT_OV  (uint8_t)(1 << 6)
//#define INT2_STEP_DELTA     (uint8_t)(1 << 7)

// CTRL1_XL
#define LSM6DSL_BW0_XL         (uint8_t)(1 << 0)
#define LSM6DSL_LPF1_BW_SEL    (uint8_t)(1 << 1)
#define LSM6DSL_FS_XL0_Pos 	   (uint8_t) (2)
#define LSM6DSL_FS_XL0         (uint8_t)(1 << 2)
#define LSM6DSL_FS_XL1         (uint8_t)(1 << 3)
#define LSM6DSL_ODR_XL0_Pos    (uint8_t) (4)
#define LSM6DSL_ODR_XL0        (uint8_t)(1 << 4)
#define LSM6DSL_ODR_XL2        (uint8_t)(1 << 5)
#define LSM6DSL_ODR_XL3        (uint8_t)(1 << 6)

// CTRL2_G
#define LSM6DSL_FS_125_Pos  (uint8_t)(1)
#define LSM6DSL_FS_125		(uint8_t)(1 << 1)
#define LSM6DSL_FS_G0_Pos   (uint8_t)(2)
#define LSM6DSL_FS_G0       (uint8_t)(1 << 2)
#define LSM6DSL_FS_G1       (uint8_t)(1 << 3)
#define LSM6DSL_ODR_G0_Pos  (uint8_t)(4)
#define LSM6DSL_ODR_G0      (uint8_t)(1 << 4)
#define LSM6DSL_ODR_G1      (uint8_t)(1 << 5)
#define LSM6DSL_ODR_G2      (uint8_t)(1 << 6)
#define LSM6DSL_ODR_G3      (uint8_t)(1 << 7)

// CTRL3_C
#define LSM6DSL_SW_RESET    (uint8_t)(1 << 0)
#define LSM6DSL_BLE         (uint8_t)(1 << 1)
#define LSM6DSL_IF_INC      (uint8_t)(1 << 2)
#define LSM6DSL_SIM         (uint8_t)(1 << 3)
#define LSM6DSL_PP_OD       (uint8_t)(1 << 4)
#define LSM6DSL_H_LACTIVE   (uint8_t)(1 << 5)
#define LSM6DSL_BDU         (uint8_t)(1 << 6)
#define LSM6DSL_BOOT        (uint8_t)(1 << 7)

// CTRL4_C
#define LSM6DSL_LPF1_SEL_G          (uint8_t)(1 << 1)
#define LSM6DSL_I2C_disable         (uint8_t)(1 << 2)
#define LSM6DSL_DRDY_MASK           (uint8_t)(1 << 3)
#define LSM6DSL_DEN_DRDY_INT1       (uint8_t)(1 << 4)
#define LSM6DSL_INT2_on_INT1        (uint8_t)(1 << 5)
#define LSM6DSL_SLEEP               (uint8_t)(1 << 6)
#define LSM6DSL_DEN_XL_EN           (uint8_t)(1 << 7)

// CTRL5_C
#define LSM6DSL_ST0_XL              (uint8_t)(1 << 0)
#define LSM6DSL_ST1_XL              (uint8_t)(1 << 1)
#define LSM6DSL_ST0_G               (uint8_t)(1 << 2)
#define LSM6DSL_ST1_G               (uint8_t)(1 << 3)
#define LSM6DSL_DEN_LH              (uint8_t)(1 << 4)
#define LSM6DSL_ROUNDING0           (uint8_t)(1 << 5)
#define LSM6DSL_ROUNDING1           (uint8_t)(1 << 6)
#define LSM6DSL_ROUNDING2           (uint8_t)(1 << 7)

// CTRL6_C
#define LSM6DSL_FTYPE_0             (uint8_t)(1 << 0)
#define LSM6DSL_FTYPE_1             (uint8_t)(1 << 1)
#define LSM6DSL_USR_OFF_W           (uint8_t)(1 << 3)
#define LSM6DSL_XL_HM_MODE          (uint8_t)(1 << 4)
#define LSM6DSL_LVL2_EN             (uint8_t)(1 << 5)
#define LSM6DSL_LVL1_EN             (uint8_t)(1 << 6)
#define LSM6DSL_TRIG_EN             (uint8_t)(1 << 7)

// CTRL7_G
#define LSM6DSL_ROUNDING_STATUS		(uint8_t)(1 << 2)
#define LSM6DSL_HPM0_G              (uint8_t)(1 << 4)
#define LSM6DSL_HPM1_G              (uint8_t)(1 << 5)
#define LSM6DSL_HP_G_EN             (uint8_t)(1 << 6)
#define LSM6DSL_G_HM_MODE           (uint8_t)(1 << 7)

// CTRL8_XL
#define LSM6DSL_LOW_PASS_ON_6D      (uint8_t)(1 << 0)
#define LSM6DSL_HP_SLOPE_XL_EN      (uint8_t)(1 << 2)
#define LSM6DSL_INPUT_COMPOSITE     (uint8_t)(1 << 3)
#define LSM6DSL_HP_REF_MODE         (uint8_t)(1 << 4)
#define LSM6DSL_HPCF_XL0            (uint8_t)(1 << 5)
#define LSM6DSL_HPCF_XL1            (uint8_t)(1 << 6)
#define LSM6DSL_LPF2_XL_EN          (uint8_t)(1 << 7)

// CTRL9_XL
#define LSM6DSL_SIGN_MOTION_EN      (uint8_t)(1 << 0)
#define LSM6DSL_PEDO_RST_STEP       (uint8_t)(1 << 1)
#define LSM6DSL_SOFT_EN             (uint8_t)(1 << 3)
#define LSM6DSL_DEN_XL_G            (uint8_t)(1 << 4)
#define LSM6DSL_DEN_Z               (uint8_t)(1 << 5)
#define LSM6DSL_DEN_Y               (uint8_t)(1 << 6)
#define LSM6DSL_DEN_X               (uint8_t)(1 << 7)

// CTRL10_C
#define LSM6DSL_FUNC_EN             (uint8_t)(1 << 2)
#define LSM6DSL_TILT_EN             (uint8_t)(1 << 3)
#define LSM6DSL_PEDO_EN             (uint8_t)(1 << 4)
#define LSM6DSL_TIMER_EN            (uint8_t)(1 << 5)
#define LSM6DSL_WRIST_TILT_EN       (uint8_t)(1 << 7)

// MASTER_CONFIG
#define LSM6DSL_MASTER_ON           (uint8_t)(1 << 0)
#define LSM6DSL_IRON_EN             (uint8_t)(1 << 1)
#define LSM6DSL_PASS_THROUGH_MODE   (uint8_t)(1 << 2)
#define LSM6DSL_PULL_UP_EN          (uint8_t)(1 << 3)
#define LSM6DSL_START_CONFIG        (uint8_t)(1 << 4)
#define LSM6DSL_DATA_VALID_SEL_FIFO (uint8_t)(1 << 6)
#define LSM6DSL_DRDY_ON_INT1        (uint8_t)(1 << 7)

// TAP_SRC
#define LSM6DSL_TAP_Z               (uint8_t)(1 << 0)
#define LSM6DSL_TAP_Y               (uint8_t)(1 << 1)
#define LSM6DSL_TAP_X               (uint8_t)(1 << 2)
#define LSM6DSL_TAP_SIGN            (uint8_t)(1 << 3)
#define LSM6DSL_DOUBLE_TAP          (uint8_t)(1 << 4)
#define LSM6DSL_SINGLE_TAP          (uint8_t)(1 << 5)
#define LSM6DSL_TAP_IA              (uint8_t)(1 << 6)

// D6D_SRC
#define LSM6DSL_XL                  (uint8_t)(1 << 0)
#define LSM6DSL_XH                  (uint8_t)(1 << 1)
#define LSM6DSL_YL                  (uint8_t)(1 << 2)
#define LSM6DSL_YH                  (uint8_t)(1 << 3)
#define LSM6DSL_ZL                  (uint8_t)(1 << 4)
#define LSM6DSL_ZH                  (uint8_t)(1 << 5)
#define LSM6DSL_D6D_IA              (uint8_t)(1 << 6)
#define LSM6DSL_DEN_DRDY			(uint8_t)(1 << 7)

// STATUS_REG
#define LSM6DSL_XLDA       			(uint8_t)(1 << 0)
#define LSM6DSL_GDA        			(uint8_t)(1 << 1)
#define LSM6DSL_TDA        			(uint8_t)(1 << 2)

// FUNC_SRC1
#define LSM6DSL_SENSORHUB_END_OP    (uint8_t)(1 << 0)
#define LSM6DSL_SI_END_OP           (uint8_t)(1 << 1)
#define LSM6DSL_HI_FAIL             (uint8_t)(1 << 2)
#define LSM6DSL_STEP_OVERFLOW       (uint8_t)(1 << 3)
#define LSM6DSL_STEP_DETECTED       (uint8_t)(1 << 4)
#define LSM6DSL_TILT_IA             (uint8_t)(1 << 5)
#define LSM6DSL_SIGN_MOTION_IA      (uint8_t)(1 << 6)
#define LSM6DSL_STEP_COUNT_DELTA_IA (uint8_t)(1 << 7)

// FUNC_SRC2
#define LSM6DSL_WRIST_TILT_IA       (uint8_t)(1 << 0)
#define LSM6DSL_SLAVE0_NACK         (uint8_t)(1 << 3)
#define LSM6DSL_SLAVE1_NACK         (uint8_t)(1 << 4)
#define LSM6DSL_SLAVE2_NACK         (uint8_t)(1 << 5)
#define LSM6DSL_SLAVE3_NACK         (uint8_t)(1 << 6)

// WRIST_TILT_IA
#define LSM6DSL_WRIST_TILT_IA_Zneg  (uint8_t)(1 << 2)
#define LSM6DSL_WRIST_TILT_IA_Zpos  (uint8_t)(1 << 3)
#define LSM6DSL_WRIST_TILT_IA_Yneg  (uint8_t)(1 << 4)
#define LSM6DSL_WRIST_TILT_IA_Ypos  (uint8_t)(1 << 5)
#define LSM6DSL_WRIST_TILT_IA_Xneg  (uint8_t)(1 << 6)
#define LSM6DSL_WRIST_TILT_IA_Xpos  (uint8_t)(1 << 7)

// TAP_CFG
#define LSM6DSL_LIR                 (uint8_t)(1 << 0)
#define LSM6DSL_TAP_Z_EN            (uint8_t)(1 << 1)
#define LSM6DSL_TAP_Y_EN            (uint8_t)(1 << 2)
#define LSM6DSL_TAP_X_EN            (uint8_t)(1 << 3)
#define LSM6DSL_SLOPE_FDS           (uint8_t)(1 << 4)
#define LSM6DSL_INACT_EN0           (uint8_t)(1 << 5)
#define LSM6DSL_INACT_EN1           (uint8_t)(1 << 6)
#define LSM6DSL_INTERRUPTS_ENABLE   (uint8_t)(1 << 7)

// TAP_THS_6D
#define LSM6DSL_TAP_THS0            (uint8_t)(1 << 0)
#define LSM6DSL_TAP_THS1            (uint8_t)(1 << 1)
#define LSM6DSL_TAP_THS2            (uint8_t)(1 << 2)
#define LSM6DSL_TAP_THS3            (uint8_t)(1 << 3)
#define LSM6DSL_TAP_THS4            (uint8_t)(1 << 4)
#define LSM6DSL_SIXD_THS0           (uint8_t)(1 << 5)
#define LSM6DSL_SIXD_THS1           (uint8_t)(1 << 6)
#define LSM6DSL_D4D_EN              (uint8_t)(1 << 7)

// INT_DUR2
#define LSM6DSL_SHOCK0              (uint8_t)(1 << 0)
#define LSM6DSL_SHOCK1              (uint8_t)(1 << 1)
#define LSM6DSL_QUIET0              (uint8_t)(1 << 2)
#define LSM6DSL_QUIET1              (uint8_t)(1 << 3)
#define LSM6DSL_DUR0                (uint8_t)(1 << 4)
#define LSM6DSL_DUR1                (uint8_t)(1 << 5)
#define LSM6DSL_DUR2                (uint8_t)(1 << 6)
#define LSM6DSL_DUR3                (uint8_t)(1 << 7)

// WAKE_UP_THS
#define LSM6DSL_WK_THS0             (uint8_t)(1 << 1)
#define LSM6DSL_WK_THS1             (uint8_t)(1 << 2)
#define LSM6DSL_WK_THS2             (uint8_t)(1 << 3)
#define LSM6DSL_WK_THS3             (uint8_t)(1 << 4)
#define LSM6DSL_WK_THS4             (uint8_t)(1 << 5)
#define LSM6DSL_WK_THS5             (uint8_t)(1 << 6)
#define LSM6DSL_SINGLE_DOUBLE_TAP   (uint8_t)(1 << 7)

// WAKE_UP_DUR
#define LSM6DSL_SLEEP_DUR0          (uint8_t)(1 << 0)
#define LSM6DSL_SLEEP_DUR1          (uint8_t)(1 << 1)
#define LSM6DSL_SLEEP_DUR2          (uint8_t)(1 << 2)
#define LSM6DSL_SLEEP_DUR3          (uint8_t)(1 << 3)
#define LSM6DSL_TIMER_HR            (uint8_t)(1 << 4)
#define LSM6DSL_WAKE_DUR0           (uint8_t)(1 << 5)
#define LSM6DSL_WAKE_DUR1           (uint8_t)(1 << 6)
#define LSM6DSL_FF_DUR5             (uint8_t)(1 << 7)

// FREE_FALL
#define LSM6DSL_FF_THS0             (uint8_t)(1 << 0)
#define LSM6DSL_FF_THS1             (uint8_t)(1 << 1)
#define LSM6DSL_FF_THS2             (uint8_t)(1 << 2)
#define LSM6DSL_FF_DUR0             (uint8_t)(1 << 3)
#define LSM6DSL_FF_DUR1             (uint8_t)(1 << 4)
#define LSM6DSL_FF_DUR2             (uint8_t)(1 << 5)
#define LSM6DSL_FF_DUR3             (uint8_t)(1 << 6)
#define LSM6DSL_FF_DUR4             (uint8_t)(1 << 7)

// MD1_CFG
#define LSM6DSL_INT1_TIMER          (uint8_t)(1 << 0)
#define LSM6DSL_INT1_TILT           (uint8_t)(1 << 1)
#define LSM6DSL_INT1_6D             (uint8_t)(1 << 2)
#define LSM6DSL_INT1_DOUBLE_TAP     (uint8_t)(1 << 3)
#define LSM6DSL_INT1_FF             (uint8_t)(1 << 4)
#define LSM6DSL_INT1_WU             (uint8_t)(1 << 5)
#define LSM6DSL_INT1_SINGLE_TAP     (uint8_t)(1 << 6)
#define LSM6DSL_INT1_INACT_STATE    (uint8_t)(1 << 7)

// MD2_CFG
#define LSM6DSL_INT2_IRON           (uint8_t)(1 << 0)
#define LSM6DSL_INT2_TILT           (uint8_t)(1 << 1)
#define LSM6DSL_INT2_6D             (uint8_t)(1 << 2)
#define LSM6DSL_INT2_DOUBLE_TAP     (uint8_t)(1 << 3)
#define LSM6DSL_INT2_FF             (uint8_t)(1 << 4)
#define LSM6DSL_INT2_WU             (uint8_t)(1 << 5)
#define LSM6DSL_INT2_SINGLE_TAP     (uint8_t)(1 << 6)
#define LSM6DSL_INT2_INACT_STATE    (uint8_t)(1 << 7)

// X_OFS_USR
#define LSM6DSL_X_OFS_USR_0         (uint8_t)(1 << 0)
#define LSM6DSL_X_OFS_USR_1         (uint8_t)(1 << 1)
#define LSM6DSL_X_OFS_USR_2         (uint8_t)(1 << 2)
#define LSM6DSL_X_OFS_USR_3         (uint8_t)(1 << 3)
#define LSM6DSL_X_OFS_USR_4         (uint8_t)(1 << 4)
#define LSM6DSL_X_OFS_USR_5         (uint8_t)(1 << 5)
#define LSM6DSL_X_OFS_USR_6         (uint8_t)(1 << 6)
#define LSM6DSL_X_OFS_USR_7         (uint8_t)(1 << 7)

// Y_OFS_USR
#define LSM6DSL_Y_OFS_USR_0         (uint8_t)(1 << 0)
#define LSM6DSL_Y_OFS_USR_1         (uint8_t)(1 << 1)
#define LSM6DSL_Y_OFS_USR_2         (uint8_t)(1 << 2)
#define LSM6DSL_Y_OFS_USR_3         (uint8_t)(1 << 3)
#define LSM6DSL_Y_OFS_USR_4         (uint8_t)(1 << 4)
#define LSM6DSL_Y_OFS_USR_5         (uint8_t)(1 << 5)
#define LSM6DSL_Y_OFS_USR_6         (uint8_t)(1 << 6)
#define LSM6DSL_Y_OFS_USR_7         (uint8_t)(1 << 7)

// Z_OFS_USR
#define LSM6DSL_Z_OFS_USR_0         (uint8_t)(1 << 0)
#define LSM6DSL_Z_OFS_USR_1         (uint8_t)(1 << 1)
#define LSM6DSL_Z_OFS_USR_2         (uint8_t)(1 << 2)
#define LSM6DSL_Z_OFS_USR_3         (uint8_t)(1 << 3)
#define LSM6DSL_Z_OFS_USR_4         (uint8_t)(1 << 4)
#define LSM6DSL_Z_OFS_USR_5         (uint8_t)(1 << 5)
#define LSM6DSL_Z_OFS_USR_6         (uint8_t)(1 << 6)
#define LSM6DSL_Z_OFS_USR_7         (uint8_t)(1 << 7)

#endif /* LSM6DSL_LSM6DSL_REG_H_ */

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
#define WRIST_TILT_IA_0             (uint8_t)0x55
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

/*
 *	Registers Bit positions
 */

// FUNC_CFG_ACCESS
#define FUNC_CFG_EN (uint8_t)(1 << 7)
#define FUNC_CFG_EN_B (uint8_t) (1 << 5)

// SENSOR_SYNC_TIME_FRAME
#define TPH_0 (uint8_t) (1 << 0)
#define TPH_1 (uint8_t) (1 << 1)
#define TPH_2 (uint8_t) (1 << 2)
#define TPH_3 (uint8_t) (1 << 3)

// SENSOR_SYNC_RES_RATIO
#define RR_0 (uint8_t) (1 << 0)
#define RR_1 (uint8_t) (1 << 1)

// FIFO_CTRL1
#define FTH_0 (uint8_t) (1 << 0)
#define FTH_1 (uint8_t) (1 << 1)
#define FTH_2 (uint8_t) (1 << 2)
#define FTH_3 (uint8_t) (1 << 3)
#define FTH_4 (uint8_t) (1 << 4)
#define FTH_5 (uint8_t) (1 << 5)
#define FTH_6 (uint8_t) (1 << 6)
#define FTH_7 (uint8_t) (1 << 7)

// FIFO_CTRL2
#define FTH_8 (uint8_t) (1 << 0)
#define FTH_9 (uint8_t) (1 << 1)
#define FTH_10 (uint8_t) (1 << 2)
#define TIMER_PEDO_FIFO_DRDY (uint8_t) (1 << 6)
#define TIMER_PEDO_FIFO_EN (uint8_t) (1 << 7)

// FIFO_CTRL3
#define DEC_FIFO_XL0 (uint8_t) (1 << 0)
#define DEC_FIFO_XL1 (uint8_t) (1 << 1)
#define DEC_FIFO_XL2 (uint8_t) (1 << 2)
#define DEC_FIFO_GYRO0 (uint8_t) (1 << 3)
#define DEC_FIFO_GYRO1 (uint8_t) (1 << 4)
#define DEC_FIFO_GYRO2 (uint8_t) (1 << 5)

// FIFO_CTRL4
#define DEC_DS3_FIFO0 (uint8_t) (1 << 0)
#define DEC_DS3_FIFO1 (uint8_t) (1 << 1)
#define DEC_DS3_FIFO2 (uint8_t) (1 << 2)
#define DEC_DS4_FIFO0 (uint8_t) (1 << 3)
#define DEC_DS4_FIFO1 (uint8_t) (1 << 4)
#define DEC_DS4_FIFO2 (uint8_t) (1 << 5)
#define ONLY_HIGH_DATA (uint8_t) (1 << 6)
#define STOP_ON_FTH (uint8_t) (1 << 7)

// FIFO_CTRL5
#define FIFO_MODE_0 (uint8_t) (1 << 0)
#define FIFO_MODE_1 (uint8_t) (1 << 1)
#define FIFO_MODE_2 (uint8_t) (1 << 2)
#define ODR_FIFO_0 (uint8_t) (1 << 3)
#define ODR_FIFO_1 (uint8_t) (1 << 4)
#define ODR_FIFO_2 (uint8_t) (1 << 5)
#define ODR_FIFO_3 (uint8_t) (1 << 6)

// DRDY_PULSE_CFG_G
#define INT2_WRIST_TILT (uint8_t) (1 << 0)
#define DRDY_PULSED (uint8_t) (1 << 7)

// INT1_CTRL
#define INT1_DRDY_XL (uint8_t) (1 << 0)
#define INT1_DRDY_G (uint8_t) (1 << 1)
#define INT1_BOOT (uint8_t) (1 << 2)
#define INT1_FTH (uint8_t) (1 << 3)
#define INT1_FIFO_OVR (uint8_t) (1 << 4)
#define INT1_FULL_FLAG (uint8_t) (1 << 5)
#define INT1_SIGN_MOT (uint8_t) (1 << 6)
#define INT1_STEP_DETECTOR (uint8_t) (1 << 7)

// INT2_CTRL
#define INT2_DRDY_XL        (uint8_t)(1 << 0)
#define INT2_DRDY_G         (uint8_t)(1 << 1)
#define INT2_DRDY_TEMP      (uint8_t)(1 << 2)
#define INT2_FTH            (uint8_t)(1 << 3)
#define INT2_FIFO_OVR       (uint8_t)(1 << 4)
#define INT2_FULL_FLAG      (uint8_t)(1 << 5)
#define INT2_STEP_COUNT_OV  (uint8_t)(1 << 6)
#define INT2_STEP_DELTA     (uint8_t)(1 << 7)

// CTRL1_XL
#define BW0_XL         (uint8_t)(1 << 0)
#define LPF1_BW_SEL    (uint8_t)(1 << 1)
#define FS_XL0_Pos 	   (uint8_t) (2)
#define FS_XL0         (uint8_t)(1 << 2)
#define FS_XL1         (uint8_t)(1 << 3)
#define ODR_XL0_Pos    (uint8_t) (4)
#define ODR_XL0        (uint8_t)(1 << 4)
#define ODR_XL2        (uint8_t)(1 << 5)
#define ODR_XL3        (uint8_t)(1 << 6)

// CTRL2_G
#define FS_125_Pos  (uint8_t)(1)
#define FS_125		(uint8_t)(1 << 1)
#define FS_G0_Pos   (uint8_t)(2)
#define FS_G0       (uint8_t)(1 << 2)
#define FS_G1       (uint8_t)(1 << 3)
#define ODR_G0_Pos  (uint8_t)(4)
#define ODR_G0      (uint8_t)(1 << 4)
#define ODR_G1      (uint8_t)(1 << 5)
#define ODR_G2      (uint8_t)(1 << 6)
#define ODR_G3      (uint8_t)(1 << 7)

// CTRL3_C
#define SW_RESET    (uint8_t)(1 << 0)
#define BLE         (uint8_t)(1 << 1)
#define IF_INC      (uint8_t)(1 << 2)
#define SIM         (uint8_t)(1 << 3)
#define PP_OD       (uint8_t)(1 << 4)
#define H_LACTIVE   (uint8_t)(1 << 5)
#define BDU         (uint8_t)(1 << 6)
#define BOOT        (uint8_t)(1 << 7)

// CTRL4_C
#define LPF1_SEL_G          (uint8_t)(1 << 1)
#define I2C_disable         (uint8_t)(1 << 2)
#define DRDY_MASK           (uint8_t)(1 << 3)
#define DEN_DRDY_INT1       (uint8_t)(1 << 4)
#define INT2_on_INT1        (uint8_t)(1 << 5)
#define SLEEP               (uint8_t)(1 << 6)
#define DEN_XL_EN           (uint8_t)(1 << 7)

// CTRL5_C
#define ST0_XL              (uint8_t)(1 << 0)
#define ST1_XL              (uint8_t)(1 << 1)
#define ST0_G               (uint8_t)(1 << 2)
#define ST1_G               (uint8_t)(1 << 3)
#define DEN_LH              (uint8_t)(1 << 4)
#define ROUNDING0           (uint8_t)(1 << 5)
#define ROUNDING1           (uint8_t)(1 << 6)
#define ROUNDING2           (uint8_t)(1 << 7)

// CTRL6_C
#define FTYPE_0             (uint8_t)(1 << 0)
#define FTYPE_1             (uint8_t)(1 << 1)
#define USR_OFF_W           (uint8_t)(1 << 3)
#define XL_HM_MODE          (uint8_t)(1 << 4)
#define LVL2_EN             (uint8_t)(1 << 5)
#define LVL1_EN             (uint8_t)(1 << 6)
#define TRIG_EN             (uint8_t)(1 << 7)

// CTRL7_G
#define HPM0_G              (uint8_t)(1 << 4)
#define HPM1_G              (uint8_t)(1 << 5)
#define HP_G_EN             (uint8_t)(1 << 6)
#define G_HM_MODE           (uint8_t)(1 << 7)

// CTRL8_XL
#define LOW_PASS_ON_6D      (uint8_t)(1 << 0)
#define HP_SLOPE_XL_EN      (uint8_t)(1 << 2)
#define INPUT_COMPOSITE     (uint8_t)(1 << 3)
#define HP_REF_MODE         (uint8_t)(1 << 4)
#define HPCF_XL0            (uint8_t)(1 << 5)
#define HPCF_XL1            (uint8_t)(1 << 6)
#define LPF2_XL_EN          (uint8_t)(1 << 7)

// CTRL9_XL
#define SIGN_MOTION_EN      (uint8_t)(1 << 0)
#define PEDO_RST_STEP       (uint8_t)(1 << 1)
#define SOFT_EN             (uint8_t)(1 << 3)
#define DEN_XL_G            (uint8_t)(1 << 4)
#define DEN_Z               (uint8_t)(1 << 5)
#define DEN_Y               (uint8_t)(1 << 6)
#define DEN_X               (uint8_t)(1 << 7)

// CTRL10_C
#define FUNC_EN             (uint8_t)(1 << 2)
#define TILT_EN             (uint8_t)(1 << 3)
#define PEDO_EN             (uint8_t)(1 << 4)
#define TIMER_EN            (uint8_t)(1 << 5)
#define WRIST_TILT_EN       (uint8_t)(1 << 7)

// MASTER_CONFIG
#define MASTER_ON           (uint8_t)(1 << 0)
#define IRON_EN             (uint8_t)(1 << 1)
#define PASS_THROUGH_MODE   (uint8_t)(1 << 2)
#define PULL_UP_EN          (uint8_t)(1 << 3)
#define START_CONFIG        (uint8_t)(1 << 4)
#define DATA_VALID_SEL_FIFO (uint8_t)(1 << 6)
#define DRDY_ON_INT1        (uint8_t)(1 << 7)

// TAP_SRC
#define TAP_Z               (uint8_t)(1 << 0)
#define TAP_Y               (uint8_t)(1 << 1)
#define TAP_X               (uint8_t)(1 << 2)
#define TAP_SIGN            (uint8_t)(1 << 3)
#define DOUBLE_TAP          (uint8_t)(1 << 4)
#define SINGLE_TAP          (uint8_t)(1 << 5)
#define TAP_IA              (uint8_t)(1 << 6)

// D6D_SRC
#define XL                  (uint8_t)(1 << 0)
#define XH                  (uint8_t)(1 << 1)
#define YL                  (uint8_t)(1 << 2)
#define YH                  (uint8_t)(1 << 3)
#define ZL                  (uint8_t)(1 << 4)
#define ZH                  (uint8_t)(1 << 5)
#define D6D_IA              (uint8_t)(1 << 6)

// FUNC_SRC1
#define SENSORHUB_END_OP    (uint8_t)(1 << 0)
#define SI_END_OP           (uint8_t)(1 << 1)
#define HI_FAIL             (uint8_t)(1 << 2)
#define STEP_OVERFLOW       (uint8_t)(1 << 3)
#define STEP_DETECTED       (uint8_t)(1 << 4)
#define TILT_IA             (uint8_t)(1 << 5)
#define SIGN_MOTION_IA      (uint8_t)(1 << 6)
#define STEP_COUNT_DELTA_IA (uint8_t)(1 << 7)

// FUNC_SRC2
#define WRIST_TILT_IA       (uint8_t)(1 << 0)
#define SLAVE0_NACK         (uint8_t)(1 << 3)
#define SLAVE1_NACK         (uint8_t)(1 << 4)
#define SLAVE2_NACK         (uint8_t)(1 << 5)
#define SLAVE3_NACK         (uint8_t)(1 << 6)

// WRIST_TILT_IA
#define WRIST_TILT_IA_Zneg  (uint8_t)(1 << 2)
#define WRIST_TILT_IA_Zpos  (uint8_t)(1 << 3)
#define WRIST_TILT_IA_Yneg  (uint8_t)(1 << 4)
#define WRIST_TILT_IA_Ypos  (uint8_t)(1 << 5)
#define WRIST_TILT_IA_Xneg  (uint8_t)(1 << 6)
#define WRIST_TILT_IA_Xpos  (uint8_t)(1 << 7)

// TAP_CFG
#define LIR                 (uint8_t)(1 << 0)
#define TAP_Z_EN            (uint8_t)(1 << 1)
#define TAP_Y_EN            (uint8_t)(1 << 2)
#define TAP_X_EN            (uint8_t)(1 << 3)
#define SLOPE_FDS           (uint8_t)(1 << 4)
#define INACT_EN0           (uint8_t)(1 << 5)
#define INACT_EN1           (uint8_t)(1 << 6)
#define INTERRUPTS_ENABLE   (uint8_t)(1 << 7)

// TAP_THS_6D
#define TAP_THS0            (uint8_t)(1 << 0)
#define TAP_THS1            (uint8_t)(1 << 1)
#define TAP_THS2            (uint8_t)(1 << 2)
#define TAP_THS3            (uint8_t)(1 << 3)
#define TAP_THS4            (uint8_t)(1 << 4)
#define SIXD_THS0           (uint8_t)(1 << 5)
#define SIXD_THS1           (uint8_t)(1 << 6)
#define D4D_EN              (uint8_t)(1 << 7)

// INT_DUR2
#define SHOCK0              (uint8_t)(1 << 0)
#define SHOCK1              (uint8_t)(1 << 1)
#define QUIET0              (uint8_t)(1 << 2)
#define QUIET1              (uint8_t)(1 << 3)
#define DUR0                (uint8_t)(1 << 4)
#define DUR1                (uint8_t)(1 << 5)
#define DUR2                (uint8_t)(1 << 6)
#define DUR3                (uint8_t)(1 << 7)

// WAKE_UP_THS
#define WK_THS0             (uint8_t)(1 << 1)
#define WK_THS1             (uint8_t)(1 << 2)
#define WK_THS2             (uint8_t)(1 << 3)
#define WK_THS3             (uint8_t)(1 << 4)
#define WK_THS4             (uint8_t)(1 << 5)
#define WK_THS5             (uint8_t)(1 << 6)
#define SINGLE_DOUBLE_TAP   (uint8_t)(1 << 7)

// WAKE_UP_DUR
#define SLEEP_DUR0          (uint8_t)(1 << 0)
#define SLEEP_DUR1          (uint8_t)(1 << 1)
#define SLEEP_DUR2          (uint8_t)(1 << 2)
#define SLEEP_DUR3          (uint8_t)(1 << 3)
#define TIMER_HR            (uint8_t)(1 << 4)
#define WAKE_DUR0           (uint8_t)(1 << 5)
#define WAKE_DUR1           (uint8_t)(1 << 6)
#define FF_DUR5             (uint8_t)(1 << 7)

// FREE_FALL
#define FF_THS0             (uint8_t)(1 << 0)
#define FF_THS1             (uint8_t)(1 << 1)
#define FF_THS2             (uint8_t)(1 << 2)
#define FF_DUR0             (uint8_t)(1 << 3)
#define FF_DUR1             (uint8_t)(1 << 4)
#define FF_DUR2             (uint8_t)(1 << 5)
#define FF_DUR3             (uint8_t)(1 << 6)
#define FF_DUR4             (uint8_t)(1 << 7)

// MD1_CFG
#define INT1_TIMER          (uint8_t)(1 << 0)
#define INT1_TILT           (uint8_t)(1 << 1)
#define INT1_6D             (uint8_t)(1 << 2)
#define INT1_DOUBLE_TAP     (uint8_t)(1 << 3)
#define INT1_FF             (uint8_t)(1 << 4)
#define INT1_WU             (uint8_t)(1 << 5)
#define INT1_SINGLE_TAP     (uint8_t)(1 << 6)
#define INT1_INACT_STATE    (uint8_t)(1 << 7)

// MD2_CFG
#define INT2_IRON           (uint8_t)(1 << 0)
#define INT2_TILT           (uint8_t)(1 << 1)
#define INT2_6D             (uint8_t)(1 << 2)
#define INT2_DOUBLE_TAP     (uint8_t)(1 << 3)
#define INT2_FF             (uint8_t)(1 << 4)
#define INT2_WU             (uint8_t)(1 << 5)
#define INT2_SINGLE_TAP     (uint8_t)(1 << 6)
#define INT2_INACT_STATE    (uint8_t)(1 << 7)

// X_OFS_USR
#define X_OFS_USR_0         (uint8_t)(1 << 0)
#define X_OFS_USR_1         (uint8_t)(1 << 1)
#define X_OFS_USR_2         (uint8_t)(1 << 2)
#define X_OFS_USR_3         (uint8_t)(1 << 3)
#define X_OFS_USR_4         (uint8_t)(1 << 4)
#define X_OFS_USR_5         (uint8_t)(1 << 5)
#define X_OFS_USR_6         (uint8_t)(1 << 6)
#define X_OFS_USR_7         (uint8_t)(1 << 7)

// Y_OFS_USR
#define Y_OFS_USR_0         (uint8_t)(1 << 0)
#define Y_OFS_USR_1         (uint8_t)(1 << 1)
#define Y_OFS_USR_2         (uint8_t)(1 << 2)
#define Y_OFS_USR_3         (uint8_t)(1 << 3)
#define Y_OFS_USR_4         (uint8_t)(1 << 4)
#define Y_OFS_USR_5         (uint8_t)(1 << 5)
#define Y_OFS_USR_6         (uint8_t)(1 << 6)
#define Y_OFS_USR_7         (uint8_t)(1 << 7)

// Z_OFS_USR
#define Z_OFS_USR_0         (uint8_t)(1 << 0)
#define Z_OFS_USR_1         (uint8_t)(1 << 1)
#define Z_OFS_USR_2         (uint8_t)(1 << 2)
#define Z_OFS_USR_3         (uint8_t)(1 << 3)
#define Z_OFS_USR_4         (uint8_t)(1 << 4)
#define Z_OFS_USR_5         (uint8_t)(1 << 5)
#define Z_OFS_USR_6         (uint8_t)(1 << 6)
#define Z_OFS_USR_7         (uint8_t)(1 << 7)

#endif /* LSM6DSL_LSM6DSL_REG_H_ */

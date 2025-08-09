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

namespace LSM6DSL_REG
{
	const uint8_t FUNC_CFG_ACCESS = 0x01;
	const uint8_t SENSOR_SYNC_TIME_FRAME = 0x04;
	const uint8_t SENSOR_SYNC_RES_RATIO = 0x05;
	const uint8_t FIFO_CTRL1 = 0x06;
	const uint8_t FIFO_CTRL2 = 0x07;
	const uint8_t FIFO_CTRL3 = 0x08;
	const uint8_t FIFO_CTRL4 = 0x09;
	const uint8_t FIFO_CTRL5 = 0x0A;
	const uint8_t DRDY_PULSE_CFG_G = 0x0B;
	const uint8_t INT1_CTRL = 0x0D;
	const uint8_t INT2_CTRL = 0x0E;
	const uint8_t WHO_AM_I = 0x0F;
	const uint8_t CTRL1_XL = 0x10;
	const uint8_t CTRL2_G = 0x11;
	const uint8_t CTRL3_C = 0x12;
	const uint8_t CTRL4_C = 0x13;
	const uint8_t CTRL5_C = 0x14;
	const uint8_t CTRL6_C = 0x15;
	const uint8_t CTRL7_G = 0x16;
	const uint8_t CTRL8_XL = 0x17;
	const uint8_t CTRL9_XL = 0x18;
	const uint8_t CTRL10_C = 0x19;
	const uint8_t MASTER_CONFIG = 0x1A;
	const uint8_t WAKE_UP_SRC = 0x1B;
	const uint8_t TAP_SRC = 0x1C;
	const uint8_t D6D_SRC = 0x1D;
	const uint8_t STATUS_REG = 0x1E;
	const uint8_t OUT_TEMP_L = 0x20;
	const uint8_t OUT_TEMP_H = 0x21;
	const uint8_t OUTX_L_G = 0x22;
	const uint8_t OUTX_H_G = 0x23;
	const uint8_t OUTY_L_G = 0x24;
	const uint8_t OUTY_H_G = 0x25;
	const uint8_t OUTZ_L_G = 0x26;
	const uint8_t OUTZ_H_G = 0x27;
	const uint8_t OUTX_L_XL = 0x28;
	const uint8_t OUTX_H_XL = 0x29;
	const uint8_t OUTY_L_XL = 0x2A;
	const uint8_t OUTY_H_XL = 0x2B;
	const uint8_t OUTZ_L_XL = 0x2C;
	const uint8_t OUTZ_H_XL = 0x2D;
	const uint8_t SENSORHUB1_REG = 0x2E;
	const uint8_t SENSORHUB2_REG = 0x2F;
	const uint8_t SENSORHUB3_REG = 0x30;
	const uint8_t SENSORHUB4_REG = 0x31;
	const uint8_t SENSORHUB5_REG = 0x32;
	const uint8_t SENSORHUB6_REG = 0x33;
	const uint8_t SENSORHUB7_REG = 0x34;
	const uint8_t SENSORHUB8_REG = 0x35;
	const uint8_t SENSORHUB9_REG = 0x36;
	const uint8_t SENSORHUB10_REG = 0x37;
	const uint8_t SENSORHUB11_REG = 0x38;
	const uint8_t SENSORHUB12_REG = 0x39;
	const uint8_t FIFO_STATUS1 = 0x3A;
	const uint8_t FIFO_STATUS2 = 0x3B;
	const uint8_t FIFO_STATUS3 = 0x3C;
	const uint8_t FIFO_STATUS4 = 0x3D;
	const uint8_t FIFO_DATA_OUT_L = 0x3E;
	const uint8_t FIFO_DATA_OUT_H = 0x3F;
	const uint8_t TIMESTAMP0_REG = 0x40;
	const uint8_t TIMESTAMP1_REG = 0x41;
	const uint8_t TIMESTAMP2_REG = 0x42;
	const uint8_t STEP_TIMESTAMP_L = 0x49;
	const uint8_t STEP_TIMESTAMP_H = 0x4A;
	const uint8_t STEP_COUNTER_L = 0x4B;
	const uint8_t STEP_COUNTER_H = 0x4C;
	const uint8_t SENSORHUB13_REG = 0x4D;
	const uint8_t SENSORHUB14_REG = 0x4E;
	const uint8_t SENSORHUB15_REG = 0x4F;
	const uint8_t SENSORHUB16_REG = 0x50;
	const uint8_t SENSORHUB17_REG = 0x51;
	const uint8_t SENSORHUB18_REG = 0x52;
	const uint8_t FUNC_SRC1 = 0x53;
	const uint8_t FUNC_SRC2 = 0x54;
	const uint8_t WRIST_TILT_IA_0 = 0x55;
	const uint8_t TAP_CFG = 0x58;
	const uint8_t TAP_THS_6D = 0x59;
	const uint8_t INT_DUR2 = 0x5A;
	const uint8_t WAKE_UP_THS = 0x5B;
	const uint8_t WAKE_UP_DUR = 0x5C;
	const uint8_t FREE_FALL = 0x5D;
	const uint8_t MD1_CFG = 0x5E;
	const uint8_t MD2_CFG = 0x5F;
	const uint8_t MASTER_CMD_CODE = 0x60;
	const uint8_t SENS_SYNC_SPI_ERROR_CODE = 0x61;
	const uint8_t OUT_MAG_RAW_X_L = 0x66;
	const uint8_t OUT_MAG_RAW_X_H = 0x67;
	const uint8_t OUT_MAG_RAW_Y_L = 0x68;
	const uint8_t OUT_MAG_RAW_Y_H = 0x69;
	const uint8_t OUT_MAG_RAW_Z_L = 0x6A;
	const uint8_t OUT_MAG_RAW_Z_H = 0x6B;
	const uint8_t X_OFS_USR = 0x73;
	const uint8_t Y_OFS_USR = 0x74;
	const uint8_t Z_OFS_USR = 0x75;

	const uint8_t WHO_AM_I_VAL = 0x6A;

	/*
	 *	Registers Bit positions
	 */

// FUNC_CFG_ACCESS
	const uint8_t FUNC_CFG_EN = (1 << 7);
	const uint8_t FUNC_CFG_EN_B = (1 << 5);

// SENSOR_SYNC_TIME_FRAME
	const uint8_t TPH_0 = (1 << 0);
	const uint8_t TPH_1 = (1 << 1);
	const uint8_t TPH_2 = (1 << 2);
	const uint8_t TPH_3 = (1 << 3);

// SENSOR_SYNC_RES_RATIO
	const uint8_t RR_0 = (1 << 0);
	const uint8_t RR_1 = (1 << 1);

// FIFO_CTRL1
	const uint8_t FTH_0 = (1 << 0);
	const uint8_t FTH_1 = (1 << 1);
	const uint8_t FTH_2 = (1 << 2);
	const uint8_t FTH_3 = (1 << 3);
	const uint8_t FTH_4 = (1 << 4);
	const uint8_t FTH_5 = (1 << 5);
	const uint8_t FTH_6 = (1 << 6);
	const uint8_t FTH_7 = (1 << 7);

// FIFO_CTRL2
	const uint8_t FTH_8 = (1 << 0);
	const uint8_t FTH_9 = (1 << 1);
	const uint8_t FTH_10 = (1 << 2);
	const uint8_t TIMER_PEDO_FIFO_DRDY = (1 << 6);
	const uint8_t TIMER_PEDO_FIFO_EN = (1 << 7);

// FIFO_CTRL3
	const uint8_t DEC_FIFO_XL0 = (1 << 0);
	const uint8_t DEC_FIFO_XL1 = (1 << 1);
	const uint8_t DEC_FIFO_XL2 = (1 << 2);
	const uint8_t DEC_FIFO_GYRO0 = (1 << 3);
	const uint8_t DEC_FIFO_GYRO1 = (1 << 4);
	const uint8_t DEC_FIFO_GYRO2 = (1 << 5);

// FIFO_CTRL4
	const uint8_t DEC_DS3_FIFO0 = (1 << 0);
	const uint8_t DEC_DS3_FIFO1 = (1 << 1);
	const uint8_t DEC_DS3_FIFO2 = (1 << 2);
	const uint8_t DEC_DS4_FIFO0 = (1 << 3);
	const uint8_t DEC_DS4_FIFO1 = (1 << 4);
	const uint8_t DEC_DS4_FIFO2 = (1 << 5);
	const uint8_t ONLY_HIGH_DATA = (1 << 6);
	const uint8_t STOP_ON_FTH = (1 << 7);

// FIFO_CTRL5
	const uint8_t FIFO_MODE_0 = (1 << 0);
	const uint8_t FIFO_MODE_1 = (1 << 1);
	const uint8_t FIFO_MODE_2 = (1 << 2);
	const uint8_t ODR_FIFO_0 = (1 << 3);
	const uint8_t ODR_FIFO_1 = (1 << 4);
	const uint8_t ODR_FIFO_2 = (1 << 5);
	const uint8_t ODR_FIFO_3 = (1 << 6);

// DRDY_PULSE_CFG_G
	const uint8_t INT2_WRIST_TILT = (1 << 0);
	const uint8_t DRDY_PULSED = (1 << 7);

// INT1_CTRL
//#define INT1_DRDY_XL =  (1 << 0);
//#define INT1_DRDY_G =  (1 << 1);
//#define INT1_BOOT =  (1 << 2);
//#define INT1_FTH =  (1 << 3);
//#define INT1_FIFO_OVR =  (1 << 4);
//#define INT1_FULL_FLAG =  (1 << 5);
//#define INT1_SIGN_MOT =  (1 << 6);
//#define INT1_STEP_DETECTOR =  (1 << 7);

// INT2_CTRL
//#define INT2_DRDY_XL        = (1 << 0);
//#define INT2_DRDY_G         = (1 << 1);
//#define INT2_DRDY_TEMP      = (1 << 2);
//#define INT2_FTH            = (1 << 3);
//#define INT2_FIFO_OVR       = (1 << 4);
//#define INT2_FULL_FLAG      = (1 << 5);
//#define INT2_STEP_COUNT_OV  = (1 << 6);
//#define INT2_STEP_DELTA     = (1 << 7);

// CTRL1_XL
	const uint8_t BW0_XL = (1 << 0);
	const uint8_t LPF1_BW_SEL = (1 << 1);
	const uint8_t FS_XL0_Pos = (2);
	const uint8_t FS_XL0 = (1 << 2);
	const uint8_t FS_XL1 = (1 << 3);
	const uint8_t ODR_XL0_Pos = (4);
	const uint8_t ODR_XL0 = (1 << 4);
	const uint8_t ODR_XL2 = (1 << 5);
	const uint8_t ODR_XL3 = (1 << 6);

// CTRL2_G
	const uint8_t FS_125_Pos = (1);
	const uint8_t FS_125 = (1 << 1);
	const uint8_t FS_G0_Pos = (2);
	const uint8_t FS_G0 = (1 << 2);
	const uint8_t FS_G1 = (1 << 3);
	const uint8_t ODR_G0_Pos = (4);
	const uint8_t ODR_G0 = (1 << 4);
	const uint8_t ODR_G1 = (1 << 5);
	const uint8_t ODR_G2 = (1 << 6);
	const uint8_t ODR_G3 = (1 << 7);

// CTRL3_C
	const uint8_t SW_RESET = (1 << 0);
	const uint8_t BLE = (1 << 1);
	const uint8_t IF_INC = (1 << 2);
	const uint8_t SIM = (1 << 3);
	const uint8_t PP_OD = (1 << 4);
	const uint8_t H_LACTIVE = (1 << 5);
	const uint8_t BDU = (1 << 6);
	const uint8_t BOOT = (1 << 7);

// CTRL4_C
	const uint8_t LPF1_SEL_G = (1 << 1);
	const uint8_t I2C_disable = (1 << 2);
	const uint8_t DRDY_MASK = (1 << 3);
	const uint8_t DEN_DRDY_INT1 = (1 << 4);
	const uint8_t INT2_on_INT1 = (1 << 5);
	const uint8_t SLEEP = (1 << 6);
	const uint8_t DEN_XL_EN = (1 << 7);

// CTRL5_C
	const uint8_t ST0_XL = (1 << 0);
	const uint8_t ST1_XL = (1 << 1);
	const uint8_t ST0_G = (1 << 2);
	const uint8_t ST1_G = (1 << 3);
	const uint8_t DEN_LH = (1 << 4);
	const uint8_t ROUNDING0 = (1 << 5);
	const uint8_t ROUNDING1 = (1 << 6);
	const uint8_t ROUNDING2 = (1 << 7);

// CTRL6_C
	const uint8_t FTYPE_0 = (1 << 0);
	const uint8_t FTYPE_1 = (1 << 1);
	const uint8_t USR_OFF_W = (1 << 3);
	const uint8_t XL_HM_MODE = (1 << 4);
	const uint8_t LVL2_EN = (1 << 5);
	const uint8_t LVL1_EN = (1 << 6);
	const uint8_t TRIG_EN = (1 << 7);

// CTRL7_G
	const uint8_t ROUNDING_STATUS = (1 << 2);
	const uint8_t HPM0_G = (1 << 4);
	const uint8_t HPM1_G = (1 << 5);
	const uint8_t HP_G_EN = (1 << 6);
	const uint8_t G_HM_MODE = (1 << 7);

// CTRL8_XL
	const uint8_t LOW_PASS_ON_6D = (1 << 0);
	const uint8_t HP_SLOPE_XL_EN = (1 << 2);
	const uint8_t INPUT_COMPOSITE = (1 << 3);
	const uint8_t HP_REF_MODE = (1 << 4);
	const uint8_t HPCF_XL0 = (1 << 5);
	const uint8_t HPCF_XL1 = (1 << 6);
	const uint8_t LPF2_XL_EN = (1 << 7);

// CTRL9_XL
	const uint8_t SIGN_MOTION_EN = (1 << 0);
	const uint8_t PEDO_RST_STEP = (1 << 1);
	const uint8_t SOFT_EN = (1 << 3);
	const uint8_t DEN_XL_G = (1 << 4);
	const uint8_t DEN_Z = (1 << 5);
	const uint8_t DEN_Y = (1 << 6);
	const uint8_t DEN_X = (1 << 7);

// CTRL10_C
	const uint8_t FUNC_EN = (1 << 2);
	const uint8_t TILT_EN = (1 << 3);
	const uint8_t PEDO_EN = (1 << 4);
	const uint8_t TIMER_EN = (1 << 5);
	const uint8_t WRIST_TILT_EN = (1 << 7);

// MASTER_CONFIG
	const uint8_t MASTER_ON = (1 << 0);
	const uint8_t IRON_EN = (1 << 1);
	const uint8_t PASS_THROUGH_MODE = (1 << 2);
	const uint8_t PULL_UP_EN = (1 << 3);
	const uint8_t START_CONFIG = (1 << 4);
	const uint8_t DATA_VALID_SEL_FIFO = (1 << 6);
	const uint8_t DRDY_ON_INT1 = (1 << 7);

// TAP_SRC
	const uint8_t TAP_Z = (1 << 0);
	const uint8_t TAP_Y = (1 << 1);
	const uint8_t TAP_X = (1 << 2);
	const uint8_t TAP_SIGN = (1 << 3);
	const uint8_t DOUBLE_TAP = (1 << 4);
	const uint8_t SINGLE_TAP = (1 << 5);
	const uint8_t TAP_IA = (1 << 6);

// D6D_SRC
	const uint8_t XL = (1 << 0);
	const uint8_t XH = (1 << 1);
	const uint8_t YL = (1 << 2);
	const uint8_t YH = (1 << 3);
	const uint8_t ZL = (1 << 4);
	const uint8_t ZH = (1 << 5);
	const uint8_t D6D_IA = (1 << 6);
	const uint8_t DEN_DRDY = (1 << 7);

// STATUS_REG
	const uint8_t XLDA = (1 << 0);
	const uint8_t GDA = (1 << 1);
	const uint8_t TDA = (1 << 2);

// FUNC_SRC1
	const uint8_t SENSORHUB_END_OP = (1 << 0);
	const uint8_t SI_END_OP = (1 << 1);
	const uint8_t HI_FAIL = (1 << 2);
	const uint8_t STEP_OVERFLOW = (1 << 3);
	const uint8_t STEP_DETECTED = (1 << 4);
	const uint8_t TILT_IA = (1 << 5);
	const uint8_t SIGN_MOTION_IA = (1 << 6);
	const uint8_t STEP_COUNT_DELTA_IA = (1 << 7);

// FUNC_SRC2
	const uint8_t WRIST_TILT_IA = (1 << 0);
	const uint8_t SLAVE0_NACK = (1 << 3);
	const uint8_t SLAVE1_NACK = (1 << 4);
	const uint8_t SLAVE2_NACK = (1 << 5);
	const uint8_t SLAVE3_NACK = (1 << 6);

// WRIST_TILT_IA
	const uint8_t WRIST_TILT_IA_Zneg = (1 << 2);
	const uint8_t WRIST_TILT_IA_Zpos = (1 << 3);
	const uint8_t WRIST_TILT_IA_Yneg = (1 << 4);
	const uint8_t WRIST_TILT_IA_Ypos = (1 << 5);
	const uint8_t WRIST_TILT_IA_Xneg = (1 << 6);
	const uint8_t WRIST_TILT_IA_Xpos = (1 << 7);

// TAP_CFG
	const uint8_t LIR = (1 << 0);
	const uint8_t TAP_Z_EN = (1 << 1);
	const uint8_t TAP_Y_EN = (1 << 2);
	const uint8_t TAP_X_EN = (1 << 3);
	const uint8_t SLOPE_FDS = (1 << 4);
	const uint8_t INACT_EN0 = (1 << 5);
	const uint8_t INACT_EN1 = (1 << 6);
	const uint8_t INTERRUPTS_ENABLE = (1 << 7);

// TAP_THS_6D
	const uint8_t TAP_THS0 = (1 << 0);
	const uint8_t TAP_THS1 = (1 << 1);
	const uint8_t TAP_THS2 = (1 << 2);
	const uint8_t TAP_THS3 = (1 << 3);
	const uint8_t TAP_THS4 = (1 << 4);
	const uint8_t SIXD_THS0 = (1 << 5);
	const uint8_t SIXD_THS1 = (1 << 6);
	const uint8_t D4D_EN = (1 << 7);

// INT_DUR2
	const uint8_t SHOCK0 = (1 << 0);
	const uint8_t SHOCK1 = (1 << 1);
	const uint8_t QUIET0 = (1 << 2);
	const uint8_t QUIET1 = (1 << 3);
	const uint8_t DUR0 = (1 << 4);
	const uint8_t DUR1 = (1 << 5);
	const uint8_t DUR2 = (1 << 6);
	const uint8_t DUR3 = (1 << 7);

// WAKE_UP_THS
	const uint8_t WK_THS0 = (1 << 1);
	const uint8_t WK_THS1 = (1 << 2);
	const uint8_t WK_THS2 = (1 << 3);
	const uint8_t WK_THS3 = (1 << 4);
	const uint8_t WK_THS4 = (1 << 5);
	const uint8_t WK_THS5 = (1 << 6);
	const uint8_t SINGLE_DOUBLE_TAP = (1 << 7);

// WAKE_UP_DUR
	const uint8_t SLEEP_DUR0 = (1 << 0);
	const uint8_t SLEEP_DUR1 = (1 << 1);
	const uint8_t SLEEP_DUR2 = (1 << 2);
	const uint8_t SLEEP_DUR3 = (1 << 3);
	const uint8_t TIMER_HR = (1 << 4);
	const uint8_t WAKE_DUR0 = (1 << 5);
	const uint8_t WAKE_DUR1 = (1 << 6);
	const uint8_t FF_DUR5 = (1 << 7);

// FREE_FALL
	const uint8_t FF_THS0 = (1 << 0);
	const uint8_t FF_THS1 = (1 << 1);
	const uint8_t FF_THS2 = (1 << 2);
	const uint8_t FF_DUR0 = (1 << 3);
	const uint8_t FF_DUR1 = (1 << 4);
	const uint8_t FF_DUR2 = (1 << 5);
	const uint8_t FF_DUR3 = (1 << 6);
	const uint8_t FF_DUR4 = (1 << 7);

// MD1_CFG
	const uint8_t INT1_TIMER = (1 << 0);
	const uint8_t INT1_TILT = (1 << 1);
	const uint8_t INT1_6D = (1 << 2);
	const uint8_t INT1_DOUBLE_TAP = (1 << 3);
	const uint8_t INT1_FF = (1 << 4);
	const uint8_t INT1_WU = (1 << 5);
	const uint8_t INT1_SINGLE_TAP = (1 << 6);
	const uint8_t INT1_INACT_STATE = (1 << 7);

// MD2_CFG
	const uint8_t INT2_IRON = (1 << 0);
	const uint8_t INT2_TILT = (1 << 1);
	const uint8_t INT2_6D = (1 << 2);
	const uint8_t INT2_DOUBLE_TAP = (1 << 3);
	const uint8_t INT2_FF = (1 << 4);
	const uint8_t INT2_WU = (1 << 5);
	const uint8_t INT2_SINGLE_TAP = (1 << 6);
	const uint8_t INT2_INACT_STATE = (1 << 7);

// X_OFS_USR
	const uint8_t X_OFS_USR_0 = (1 << 0);
	const uint8_t X_OFS_USR_1 = (1 << 1);
	const uint8_t X_OFS_USR_2 = (1 << 2);
	const uint8_t X_OFS_USR_3 = (1 << 3);
	const uint8_t X_OFS_USR_4 = (1 << 4);
	const uint8_t X_OFS_USR_5 = (1 << 5);
	const uint8_t X_OFS_USR_6 = (1 << 6);
	const uint8_t X_OFS_USR_7 = (1 << 7);

// Y_OFS_USR
	const uint8_t Y_OFS_USR_0 = (1 << 0);
	const uint8_t Y_OFS_USR_1 = (1 << 1);
	const uint8_t Y_OFS_USR_2 = (1 << 2);
	const uint8_t Y_OFS_USR_3 = (1 << 3);
	const uint8_t Y_OFS_USR_4 = (1 << 4);
	const uint8_t Y_OFS_USR_5 = (1 << 5);
	const uint8_t Y_OFS_USR_6 = (1 << 6);
	const uint8_t Y_OFS_USR_7 = (1 << 7);

// Z_OFS_USR
	const uint8_t Z_OFS_USR_0 = (1 << 0);
	const uint8_t Z_OFS_USR_1 = (1 << 1);
	const uint8_t Z_OFS_USR_2 = (1 << 2);
	const uint8_t Z_OFS_USR_3 = (1 << 3);
	const uint8_t Z_OFS_USR_4 = (1 << 4);
	const uint8_t Z_OFS_USR_5 = (1 << 5);
	const uint8_t Z_OFS_USR_6 = (1 << 6);
	const uint8_t Z_OFS_USR_7 = (1 << 7);

}  // namespace LSM6DSL

#endif /* LSM6DSL_LSM6DSL_REG_H_ */

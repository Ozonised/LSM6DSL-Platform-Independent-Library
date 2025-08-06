# LSM6DSL library for STM32, PICs, AVR
This is a platform independent I2C library for LSM6DSL 6 axis imu.
The LSM6DSL is a 3D digital accelerometer and 3D digital gyroscope system-in-package with a digital I2C/SPI serial interface standard output, performing at 0.65 mA in combo High-Performance mode.
The device has a dynamic user-selectable full-scale acceleration range of ±2/±4/±8/±16 g and an angular rate range of ±125/±250/±500/±1000/±2000 dps.

## Supported Features:
- Checking for device presence.
- Setting endianess for output registers.
- Setting output data rate and full scale range for accelerometer and gyroscope.
- Enabling accelerometer and gyroscope high performance mode.
- Reading accelerometer, gyroscope and temperature data.
- Performing gyroscope and accelerometer self test.
- Configuring accelerometer's digital high pass and low pass filters.
- Configuring interrupts for INT1 and INT2 pins.
- Setting block updata mode.

### Note:
Refer to [lsm6dsl.h](LSM6DSL_C/Inc/lsm6dsl.h) for all the implemented features.

## Do I use it with my favourite microcontroller?
To use it with your favourite microcontroller, you simply need to define the 3 functions declared in [lsm6dsl_port.h](LSM6DSL_C/Inc/lsm6dsl_port.h).

The function are:
1. ```LSM6DSL_INTF_RET_TYPE LSM6DSL_PortI2CReadReg(void *hinterface, uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len)``` : function to read the device registers.
2. ```LSM6DSL_INTF_RET_TYPE LSM6DSL_PortI2CWriteReg(void *hinterface, uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len)``` : function to write to device registers.
3. ```void LSM6DSL_PortDelayMs(void *hinterface, uint32_t ms)``` : function to delay in milliseconds.

Don't worry, I will show you an example.

### Porting to STM32 using ST HAL framework:
Initialise the I2C peripheral. This will create a ```I2C_HandleTypedef hi2c```;

Now in the main file, create the definitions for the above function:

```C
LSM6DSL_INTF_RET_TYPE LSM6DSL_PortI2CReadReg(void *hinterface, uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len)
{
	I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef*) hinterface;
	return HAL_I2C_Mem_Read(hi2c, chipAddr << 1, RegAddr, I2C_MEMADD_SIZE_8BIT, buf, len, 50);
}

LSM6DSL_INTF_RET_TYPE LSM6DSL_PortI2CWriteReg(void *hinterface, uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len)
{
	I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef*) hinterface;
	return HAL_I2C_Mem_Write(hi2c, chipAddr << 1, RegAddr, I2C_MEMADD_SIZE_8BIT, buf, len, 50);
}

void LSM6DSL_PortDelayMs(void *hinterface, uint32_t ms)
{
	(void) hinterface;
	HAL_Delay(ms);
}
```

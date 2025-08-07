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
Initialise the I2C peripheral. This will create a ```I2C_HandleTypedef hi2cx```;

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
## Examples:

### 1. Read acclerometer and gyroscope data
```C
#include "lsm6dsl.h"

#define LSM6DSL_ADDR 0x6A
LSM6DSL imu; // create LSM6DSL object
LSM6DSL_AccelData accel; // object to hold accelerometer data
LSM6DSL_GyroData gyro;	 // object to hold gyroscope data
	.
	.
	.
wait(20); 						// delay for 20 ms as the imu performs a 15ms boot up procedure
LSM6DSL_Init(&imu, (void *) i2cHandle, LSM6DSL_ADDR);	// initialise the struct
LSM6DSL_setAccelFSRange(&imu, LSM6DSL_XL_FS_4G);	// set the accelerometer full scale range
LSM6DSL_setAccelODR(&imu, LSM6DSL_XL_ODR_416Hz);	// set the accelerometer output data rate
LSM6DSL_setGyroFSRange(&imu, LSM6DSL_G_FS_500DPS);	// set the gyroscope full scale range
LSM6DSL_setGyroODR(&imu, LSM6DSL_G_ODR_416Hz);		// set the gyroscope output data rate
	.
	.
	.
if (LSM6DSL_isAccelDataAvailabe(&imu) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
{
	LSM6DSL_readAccelData(&imu, &accel);
	printf("%d,%d,%d\n", accel.x, accel.y, accel.z);
}

if (LSM6DSL_isGyroDataAvailabe(&imu) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
{
	LSM6DSL_readGyroData(&imu, &gyro);
	printf("%d,%d,%d\n", gyro.x, gyro.y, gyro.z);
}
```
### 2. Read temperature data
To activate the temperature, either the accelerometer, gyroscope, or both must be enabled. Refer to section 9 of the application note [AN5040](/Datasheet/an5040-lsm6dsl-alwayson-3d-accelerometer-and-3d-gyroscope-stmicroelectronics.pdf) for output data rate (max 52Hz).

```C
#include "lsm6dsl.h"

#define LSM6DSL_ADDR 0x6A
LSM6DSL imu; // create LSM6DSL object
LSM6DSL_TempData t;	// object to hold temperature data
	.
	.
	.
wait(20); 						// delay for 20 ms as the imu performs a 15ms boot up procedure
LSM6DSL_Init(&imu, (void *) i2cHandle, LSM6DSL_ADDR);	// initialise the struct
LSM6DSL_setAccelFSRange(&imu, LSM6DSL_XL_FS_4G);	// set the accelerometer full scale range
LSM6DSL_setAccelODR(&imu, LSM6DSL_XL_ODR_416Hz);	// set the accelerometer output data rate
	.
	.
	.
if (LSM6DSL_isTempDataAvailabe(&imu) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
{
	LSM6DSL_readTemperature(&imu, &t);
	printf("Raw data: %d, Celsius: %f\n", t.regData, t.celsius);
}
```

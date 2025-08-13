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
To use it with your favourite microcontroller, you simply need to define the 3 functions declared in [lsm6dsl_port.h](LSM6DSL_C/Inc/lsm6dsl_port.h) (for C) or [lsm6dsl_port.hpp](LSM6DSL_CPP/Inc/lsm6dsl_reg.hpp) (for C++).

The functions for C are:
1. ```LSM6DSL_INTF_RET_TYPE LSM6DSL_PortI2CReadReg(void *hinterface, uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len)``` : function to read the device registers.
2. ```LSM6DSL_INTF_RET_TYPE LSM6DSL_PortI2CWriteReg(void *hinterface, uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len)``` : function to write to device registers.
3. ```void LSM6DSL_PortDelayMs(void *hinterface, uint32_t ms)``` : function to delay in milliseconds.

The functions for C++ are:
1. ```LSM6DSL_INTF_RET_TYPE LSM6DSL::read(uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len)``` : function to read the device registers.
2. ```LSM6DSL_INTF_RET_TYPE LSM6DSL::write(uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len)``` : function to write to device registers.
3. ```void LSM6DSL::delayMs(uint32_t ms)``` : function to delay in milliseconds.

Don't worry, I will show you an example.

### Porting to Arduino Framework:
To use the library with the arduino framwork, inlude the cpp files from [LSM6DSL_CPP](/LSM6DSL_CPP) into your project.
Now, from the [lsm6dsl_port.hpp](LSM6DSL_CPP/Inc/lsm6dsl_reg.hpp) copy these function into your main file and write their definition as shown below:

```CPP
LSM6DSL_INTF_RET_TYPE LSM6DSL::read(uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len) {
  TwoWire *i2c = (TwoWire *)hInterface;
  uint8_t i = 0;
  i2c->beginTransmission(chipAddr);
  i2c->write(RegAddr);
  if (i2c->endTransmission() != 0) return LSM6DSL_INTF_RET_TYPE_FAILURE;

  i2c->requestFrom(chipAddr, len);
  while (i < len) {
    if (i2c->available()) {
      buf[i++] = i2c->read();
    }
  }
  return LSM6DSL_INTF_RET_TYPE_SUCCESS;
}

LSM6DSL_INTF_RET_TYPE LSM6DSL::write(uint8_t chipAddr, uint8_t RegAddr, uint8_t *buf, uint16_t len) {
  TwoWire *i2c = (TwoWire *)hInterface;
  uint8_t i = 0;
  i2c->beginTransmission(chipAddr);
  i2c->write(RegAddr);
  while (i < len) {
    i2c->write(buf[i++]);
  }
  if (i2c->endTransmission() != 0) return LSM6DSL_INTF_RET_TYPE_FAILURE;
  return LSM6DSL_INTF_RET_TYPE_SUCCESS;
}

void LSM6DSL::delayMs(uint32_t ms) {
  delay(ms);
}
```
### Porting to STM32 using ST HAL framework:
To use use the library with ST HAL's framework, include the files from [LSM6DSL_C](/LSM6DSL_C) into your project
Now in the main file, create the definitions for the functions in [lsm6dsl_port.h](LSM6DSL_C/Inc/lsm6dsl_reg.h) as shown below:

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
Not all the features of this library is discussed in the example, but enough to get you started.

### 1. Read acclerometer and gyroscope data
#### C
```C
#include "lsm6dsl.h"

#define LSM6DSL_ADDR 0x6A
LSM6DSL imu; // create LSM6DSL object
LSM6DSL_AccelRawData accelRaw; 		// object to hold accelerometer's raw data
LSM6DSL_GyroRawData gyroRaw;	 	// object to hold gyroscope's raw data
	.
	.
	.
wait(20); 						// delay for 20 ms as the imu performs a 15ms boot up procedure
LSM6DSL_Init(&imu, (void *) &i2cHandle, LSM6DSL_ADDR);	// initialise the struct
LSM6DSL_setAccelFSRange(&imu, LSM6DSL_XL_FS_4G);	// set the accelerometer full scale range
LSM6DSL_setAccelODR(&imu, LSM6DSL_XL_ODR_416Hz);	// set the accelerometer output data rate
LSM6DSL_setGyroFSRange(&imu, LSM6DSL_G_FS_500DPS);	// set the gyroscope full scale range
LSM6DSL_setGyroODR(&imu, LSM6DSL_G_ODR_416Hz);		// set the gyroscope output data rate
	.
	.
	.
if (LSM6DSL_isAccelDataAvailabe(&imu) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
{
	LSM6DSL_readAccelData(&imu, &accelRaw);
	printf("%d,%d,%d\n", accelRaw.x, accelRaw.y, accelRaw.z);
}

if (LSM6DSL_isGyroDataAvailabe(&imu) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
{
	LSM6DSL_readGyroData(&imu, &gyroRaw);
	printf("%d,%d,%d\n", gyroRaw.x, gyroRaw.y, gyroRaw.z);
}
```
#### CPP
```CPP
#include "lsm6dsl.hpp"

#define LSM6DSL_ADDR 0x6A
LSM6DSL imu(static_cast<void*>(&hI2Chandle), 0x6A);
LSM6DSL_AccelRawData xl;					// object to hold accelerometer's raw data
LSM6DSL_GyroRawData gy;						// object to hold gyroscope's raw data
	.
	.
	.
delay(20);									// delay for 20 ms as the imu performs a 15ms boot up procedure
imu.setAccelFSRange(LSM6DSL_XL_FS_4G);		// set the accelerometer full scale range
imu.setAccelODR(LSM6DSL_XL_ODR_416Hz);		// set the accelerometer output data rate
imu.setGyroFSRange(LSM6DSL_G_FS_1000DPS);	// set the gyroscope full scale range
imu.setGyroODR(LSM6DSL_G_ODR_416Hz);		// set the gyroscope output data rate
	.
	.
	.
if (imu.isAccelDataAvailabe() == LSM6DSL_INTF_RET_TYPE_SUCCESS)
{
	imu.readAccelData(&xl);
	printf("%d,%d,%d\n", accelRaw.x, accelRaw.y, accelRaw.z);
}

if (imu.isGyroDataAvailabe() == LSM6DSL_INTF_RET_TYPE_SUCCESS)
{
	imu.readGyroData(&gy);
	printf("%d,%d,%d\n", gyroRaw.x, gyroRaw.y, gyroRaw.z);
}
```
### Note:
To convert the gyroscope and accelerometer raw values into degrees per second (dps) and meters per second squared (m/s^2), use the following two functions: 
 1. ```float convertGyroRawDataToDPS(int16_t axisN, LSM6DSL_G_FS_Range r);``` : convert raw gyroscope value into dps
 2. ```float convertAccelRawDataTomS2(int16_t axisN, LSM6DSL_XL_FS_Range r);``` : convert raw accelerometer value in m/s^2

```C
float accelX, accelY, accelZ, gyroX, gyroY, gyroZ;

accelX = convertAccelRawDataTomS2(xl.x, LSM6DSL_XL_FS_4G);
accelY = convertAccelRawDataTomS2(xl.y, LSM6DSL_XL_FS_4G);
accelZ = convertAccelRawDataTomS2(xl.z, LSM6DSL_XL_FS_4G);

gyroX = convertGyroRawDataToDPS(gy.x, LSM6DSL_G_FS_1000DPS);
gyroY = convertGyroRawDataToDPS(gy.y, LSM6DSL_G_FS_1000DPS);
gyroZ = convertGyroRawDataToDPS(gy.z, LSM6DSL_G_FS_1000DPS);
```

### 2. Read temperature data
To activate the temperature, either the accelerometer, gyroscope, or both must be enabled. Refer to section 9 of the application note [AN5040](/Datasheet/an5040-lsm6dsl-alwayson-3d-accelerometer-and-3d-gyroscope-stmicroelectronics.pdf) for output data rate (max 52Hz).

#### C
```C
#include "lsm6dsl.h"

#define LSM6DSL_ADDR 0x6A
LSM6DSL imu; // create LSM6DSL object
LSM6DSL_TempData t;	// object to hold temperature data
	.
	.
	.
wait(20); 						// delay for 20 ms as the imu performs a 15ms boot up procedure
LSM6DSL_Init(&imu, (void *) &i2cHandle, LSM6DSL_ADDR);	// initialise the struct
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
#### CPP
```CPP
#include "lsm6dsl.hpp"

#define LSM6DSL_ADDR 0x6A
LSM6DSL imu(static_cast<void*>(&hI2Chandle), 0x6A);
LSM6DSL_TempData t;	// object to hold temperature data
	.
	.
	.
delay(20);									// delay for 20 ms as the imu performs a 15ms boot up procedure
imu.setAccelFSRange(LSM6DSL_XL_FS_4G);		// set the accelerometer full scale range
imu.setAccelODR(LSM6DSL_XL_ODR_416Hz);		// set the accelerometer output data rate
	.
	.
	.
if (imu.isTempDataAvailabe() == LSM6DSL_INTF_RET_TYPE_SUCCESS)
{
	imu.readTemperature(&t);
	printf("Raw data: %d, Celsius: %f\n", t.regData, t.celsius);
}
```

### 3. Perform self test
The device must be kept steady during the self test procedure.
#### C
```C
#include "lsm6dsl.h"

#define LSM6DSL_ADDR 0x6A
LSM6DSL imu; // create LSM6DSL object
LSM6DSL_AccelData accelRaw; // object to hold accelerometer's raw data
LSM6DSL_GyroData gyroRaw;	 // object to hold gyroscope's raw data
	.
	.
	.
wait(20); 						// delay for 20 ms as the imu performs a 15ms boot up procedure
LSM6DSL_Init(&imu, (void *) &i2cHandle, LSM6DSL_ADDR);	// initialise the struct

uint8_t xlStState, gyStState;
xlStState = LSM6DSL_selfTestAccel(&imu);
gyStState = LSM6DSL_selfTestGyro(&imu);
	.
	.
LSM6DSL_setAccelFSRange(&imu, LSM6DSL_XL_FS_4G);	// set the accelerometer full scale range
LSM6DSL_setAccelODR(&imu, LSM6DSL_XL_ODR_416Hz);	// set the accelerometer output data rate
LSM6DSL_setGyroFSRange(&imu, LSM6DSL_G_FS_500DPS);	// set the gyroscope full scale range
LSM6DSL_setGyroODR(&imu, LSM6DSL_G_ODR_416Hz);		// set the gyroscope output data rate
	.
	.
	.
if (xlStState == LSM6DSL_INTF_RET_TYPE_SUCCESS && LSM6DSL_isAccelDataAvailabe(&imu) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
{
	LSM6DSL_readAccelData(&imu, &accelRaw);
	printf("%d,%d,%d\n", accelRaw.x, accelRaw.y, accelRaw.z);
}

if (gyStState == LSM6DSL_INTF_RET_TYPE_SUCCESS && LSM6DSL_isGyroDataAvailabe(&imu) == LSM6DSL_INTF_RET_TYPE_SUCCESS)
{
	LSM6DSL_readGyroData(&imu, &gyro);
	printf("%d,%d,%d\n", gyroRaw.x, gyroRaw.y, gyroRaw.z);
}
```
#### CPP
```CPP
#include "lsm6dsl.hpp"

#define LSM6DSL_ADDR 0x6A
LSM6DSL imu(static_cast<void*>(&hI2Chandle), 0x6A);
LSM6DSL_AccelRawData xl;					// object to hold accelerometer's raw data
LSM6DSL_GyroRawData gy;						// object to hold gyroscope's raw data
	.
	.
	.
delay(20);									// delay for 20 ms as the imu performs a 15ms boot up procedure
uint8_t xlStState, gyStState;
xlStState = imu.selfTestAccel();
gyStState = imu.selfTestGyro();
	.
	.
	.
imu.setAccelFSRange(LSM6DSL_XL_FS_4G);		// set the accelerometer full scale range
imu.setAccelODR(LSM6DSL_XL_ODR_416Hz);		// set the accelerometer output data rate
imu.setGyroFSRange(LSM6DSL_G_FS_1000DPS);	// set the gyroscope full scale range
imu.setGyroODR(LSM6DSL_G_ODR_416Hz);		// set the gyroscope output data rate
	.
	.
	.
if (xlStState == LSM6DSL_INTF_RET_TYPE_SUCCESS && imu.isAccelDataAvailabe() == LSM6DSL_INTF_RET_TYPE_SUCCESS)
{
	imu.readAccelData(&xl);
	printf("%d,%d,%d\n", accelRaw.x, accelRaw.y, accelRaw.z);
}

if (gyStState == LSM6DSL_INTF_RET_TYPE_SUCCESS && imu.isGyroDataAvailabe() == LSM6DSL_INTF_RET_TYPE_SUCCESS)
{
	imu.readGyroData(&gy);
	printf("%d,%d,%d\n", gyroRaw.x, gyroRaw.y, gyroRaw.z);
}
```

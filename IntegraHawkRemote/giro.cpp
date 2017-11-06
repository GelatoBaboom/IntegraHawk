/*
  The following are your pin connections for a GY-521 breakout board to Arduino UNO or NANO:
  MPU6050  UNO/NANO
  VCC      +5v
  GND      GND (duh)
  SCL      A5
  SDA      A4
  MPU6050 Address: "0x68"
*/

//Código do MPU6050.
#include "giro.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
MPU6050 mpu;
uint8_t mpuIntStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];
Quaternion q;
VectorFloat gravity;
float ypr[3];
volatile bool mpuInterrupt = false;
void dmpDataReady() {
	mpuInterrupt = true;
}
Giro::Giro()
{
}
void Giro::init()
{

	Wire.begin();
	TWBR = 24;
	mpu.initialize();
	mpu.dmpInitialize();
	mpu.setDMPEnabled(true);
	attachInterrupt(0, dmpDataReady, RISING);
	mpuIntStatus = mpu.getIntStatus();
	packetSize = mpu.dmpGetFIFOPacketSize();

}
Angle Giro::GetAnglesSecure()
{
	Angle ang = GetAngles();
	while (ang.HasAngle == false)
	{
		ang = GetAngles();
	}
	return ang;
}
Angle Giro::GetAngles()
{
	double AngX, AngY;
	bool hasAngle = false;
	//while (!mpuInterrupt && fifoCount < packetSize) {  }

	//Código do MPU6050.
	mpuInterrupt = false;
	mpuIntStatus = mpu.getIntStatus();
	fifoCount = mpu.getFIFOCount();
	if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
		mpu.resetFIFO();
		//COMENTAR_OFICIAL
		Serial.println(F("FIFO overflow!"));
	}
	else if (mpuIntStatus & 0x02) {
		while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
		mpu.getFIFOBytes(fifoBuffer, packetSize);
		fifoCount -= packetSize;
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

		AngX = ypr[2] * 180.0 / M_PI;
		AngY = ypr[1] * 180.0 / M_PI;
		hasAngle = true;
		//COMENTAR_OFICIAL
		//    Serial.print("ypr\t");
		//    Serial.print(ypr[0] * 180 / M_PI);
		//    Serial.print("\t");
		//    Serial.print(ypr[1] * 180 / M_PI);
		//    Serial.print("\t");
		//    Serial.print(ypr[2] * 180 / M_PI);
		//    Serial.println();

	}
	return Angle(AngX, AngY, hasAngle);
}




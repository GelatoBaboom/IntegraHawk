// 
// 
// 

#include "Antenna.h"
uint32_t timeout;
char data[5];
bool done = false;
int datapos = 0;
//#include <SoftwareSerial.h>
//SoftwareSerial antSerial(2, 3);
void Antenna::begin(int baudrate)
{
	//aca segun los baudrates deberia reconfigurar la antena
	//para que tenga logica que lo pase como parametro
	//antSerial.begin(baudrate);
	Serial.begin(baudrate);
	//Serial.setTimeout(80);
}
void Antenna::sendData(String data)
{
	Serial.println(data);
}
String Antenna::receive()
{
	String data = "";
	if (((micros() - timeout) / 1000) > 50)
	{
		Serial.flush();
		timeout = micros();
	}
	char c = '0';
	while (Serial.available() && ((c != '\r') || (c != '\n'))) {
		c = (char)Serial.read();
		data += c;
	}
	Serial.flush();
	return data;
}
Angle a = Angle(0, 0, 0);
Angle Antenna::receiveData()
{

	char c = '1';
	//int pos = 1;
	//bool takeTooLong = false;
	a.HasAngle = false;
	if (Serial.available() > 4) {
		char buff[5];
		int pos = 0;
		//Serial.readBytes(&buff[pos], 1);
		Serial.readBytes(buff, 5);
		while (pos < 5) {
			if (datapos < 1)
			{
				if ((int)buff[pos] < -126)
				{
					data[datapos] = buff[pos];
					datapos = 1;
					//Serial.println("pos1: " + String((int)buff[pos]));
				}
			}
			else  if (datapos > 0 && datapos < 4)
			{
				if ((int)buff[pos] > -127 && (int)buff[pos] < 127)
				{
					data[datapos] = buff[pos];
					datapos = datapos + 1;
					//Serial.println("pos23: " + String((int)buff[pos]));
				}
			}
			else if (datapos > 3)
			{
				if ((int)buff[pos] > 126)
				{
					data[datapos] = buff[pos];
					datapos = 0;
					done = true;
					//Serial.println("pos4: " + String((int)buff[pos]));
					pos = 4;
				}
			}
			pos = pos + 1;
		}
		//Serial.println("data: " + String((int)buff[0]) + " " + String((int)buff[1]) + " " + String((int)buff[2]) + " " + String((int)buff[3]) + " " + String((int)buff[4]));
		if (done == true)
		{
			a.AngleX = map((int)data[1], -127, 127, -45, 45);
			a.AngleY = map((int)data[2], -127, 127, -45, 45);
			a.ESC = map((int)data[3], -127, 127, 1000, 2000);
			done = false;
			a.HasAngle = true;
			//clean buffer fast
			char buff[100];
			int buffCount = Serial.available();
			Serial.readBytes(buff, buffCount > 100 ? 100 : buffCount);

		}

		//timeout = micros();
		//	if (((micros() - timeout) / 1000) > 50)
		//	{
		//		Serial.flush();
		//		takeTooLong = true;
		//		//Serial.println("take toolong: " + String((int)c));

		//	}
		//}
		//timeout = micros();
	}
	return a;
}






// 
// 
// 

#include "Antenna.h"
uint32_t timeout;
char data[4];
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
Angle Antenna::receiveData()
{

	char c = '1';
	//int pos = 1;
	//bool takeTooLong = false;
	Angle a = Angle(0, 0, 0);
	a.HasAngle = false;
	if (Serial.available() > 3) {
		char buff[4];
		int pos = 0;
		//Serial.readBytes(&buff[pos], 1);
		Serial.readBytes(buff, 4);
		while (pos < 4) {
			if (datapos < 1)
			{
				if ((int)buff[pos] < -126)
				{
					data[datapos] = buff[pos];
					datapos = 1;
					//Serial.println("pos1: " + String((int)buff[pos]));
				}
			}else  if (datapos > 0 && datapos < 3)
			{
				if ((int)buff[pos] > -127 && (int)buff[pos] < 127)
				{
					data[datapos] = buff[pos];
					datapos = datapos + 1;
					//Serial.println("pos23: " + String((int)buff[pos]));
				}
			}else if (datapos > 2)
			{
				if ((int)buff[pos] > 126)
				{
					data[datapos] = buff[pos];
					datapos = 0;
					done = true;
					//Serial.println("pos4: " + String((int)buff[pos]));
					pos = 3;
				}
			}
			pos = pos + 1;
		}
		//Serial.println("data: " + String((int)buff[0]) + " " + String((int)buff[1]) + " " + String((int)buff[2]) + " " + String((int)buff[3]));
		if (done == true)
		{
			a.AngleX = map((int)data[1], -127, 127, -45, 45 );
			a.AngleY = map((int)data[2], -127, 127, -45, 45);
			done = false;
			a.HasAngle = true;
			while (Serial.available() > 0) {
				char t = Serial.read();
			}
			//Serial.println(a.toString());
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






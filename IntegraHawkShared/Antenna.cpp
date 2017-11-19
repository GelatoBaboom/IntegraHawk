// 
// 
// 

#include "Antenna.h"
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
	char c = '0';
	while (Serial.available()) {
		if ((c == '\r') || (c == '\n')) { break; }
		else {
			c = (char)Serial.read();
			data += c;
		}
	}
	return data;
}






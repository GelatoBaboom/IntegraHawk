// 
// 
// 

#include "Antenna.h"
#include <SoftwareSerial.h>
SoftwareSerial antSerial(2, 3);
void Antenna::begin(int baudrate)
{
	//aca segun los baudrates deberia reconfigurar la antena
	//para que tenga logica que lo pase como parametro
	antSerial.begin(baudrate);
}
void Antenna::send(String data)
{
	antSerial.println(data);
}
String Antenna::receive()
{
	String data = "";
	while (antSerial.available()) {
		char c = antSerial.read();
		data += c;
	}
	return data;
}






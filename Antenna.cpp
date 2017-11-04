// 
// 
// 

#include "Antenna.h"
#include <SoftwareSerial.h>
SoftwareSerial antSerial(2, 3);
void Antenna::init()
{
	antSerial.begin(9600);

}
void Antenna::send(String data)
{
	antSerial.println(data);
}




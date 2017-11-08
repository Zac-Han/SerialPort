#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H
#include <fstream>
#include <cstdlib>
#include <SerialStream.h>

using namespace LibSerial;

class MySerialPort : public SerialStream
{
public:
    MySerialPort();
};

#endif // MYSERIALPORT_H

#include <iostream>
#include <string.h>
#include "myserialport.h"

int main()
{
    MySerialPort sp;
    sp.Open("/dev/ttyUSB0");
    sp.initPort(SerialStreamBuf::BAUD_115200,
                SerialStreamBuf::CHAR_SIZE_8,
                SerialStreamBuf::PARITY_NONE,
                SerialStreamBuf::FLOW_CONTROL_NONE,
                1);

    // Writing data to the port

    unsigned char WriteBuffer[] = {0x30, 0x30, 0x10, 0xAF, 0x03, 0x41,
                                   0x42, 0x43, 0x3F, 0x48, 0x49, 0x4A
                                   };
    sp.sendMsg(WriteBuffer, sizeof(WriteBuffer));

    // Reading data from the port
//    MySerialPort sp;
//    sp.Open("/dev/ttyUSB1");
//    sp.initDefault();
//    sp.readMsg();
    sp.Close();

    return 0;
}

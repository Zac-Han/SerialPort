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

    unsigned char buffer[] = {0x68, 0x64, 0x31, 0x64, 0x0A, 0x91, 0x4E};
    int i = 0;
    std::cout << sizeof(buffer) << std::endl;
    while(i < sizeof(buffer))
    {
        sp.put(buffer[i]);
        i++;
    }

    sp.Close();

    return 0;
}

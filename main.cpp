#include <iostream>
#include "myserialport.h"


int main()
{
    MySerialPort sp;
    sp.Open("/dev/ttyUSB1");
    sp.SetBaudRate(SerialStreamBuf::BAUD_115200);
    sp.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
    sp.SetFlowControl(SerialStreamBuf::FLOW_CONTROL_NONE);
    sp.SetParity(SerialStreamBuf::PARITY_NONE);
    sp.SetNumOfStopBits(1);

    char next_char[1000] = "";
    sp.read(next_char, 1000);
    std::cout << next_char << std::endl;



    sp.Close();

    return 0;
}

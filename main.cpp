#include <iostream>
#include <fstream>
#include <cstdlib>
#include <SerialStream.h>

using namespace LibSerial;
using namespace std;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <data>" << endl;
        return 1;
    }

    const char* const Serial_Port = "/dev/ttyUSB0";

    SerialStream serial_stream;
    serial_stream.Open(Serial_Port);

    if(!serial_stream.good())
    {
        cerr << "Error: Could not open serial port "
                  << Serial_Port
                  << endl;
        exit(1);
    }

    serial_stream.SetBaudRate(SerialStreamBuf::BAUD_9600);
    serial_stream.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
    serial_stream.SetParity(SerialStreamBuf::PARITY_NONE);
    serial_stream.SetNumOfStopBits(1);
    serial_stream.SetFlowControl(SerialStreamBuf::FLOW_CONTROL_NONE);

    if(!serial_stream.good())
    {
        cerr << "Error: Could not configure serial port "
                  << endl;
        exit(1);
    }

    serial_stream << "Test: "
                  << argv[1]
                  << endl;
    serial_stream.Close();
    return EXIT_SUCCESS;

}

#include <iostream>
#include <string.h>
#include "myserialport.h"

int main()
{
//    MySerialPort sp;
//    sp.Open("/dev/ttyUSB0");
//    sp.initPort(SerialStreamBuf::BAUD_115200,
//                SerialStreamBuf::CHAR_SIZE_8,
//                SerialStreamBuf::PARITY_NONE,
//                SerialStreamBuf::FLOW_CONTROL_NONE,
//                1);

//    // Writing data to the port

//    unsigned char WriteBuffer[] = {0x30, 0x30, 0x10, 0xAF, 0x33, 0x41,
//                                   0x42, 0x43, 0x3F, 0x48, 0x41, 0x4E
//                                   };
//    sp.SendMsg(WriteBuffer, sizeof(WriteBuffer));

    // Reading data from the port
    MySerialPort sp;
    sp.Open("/dev/ttyUSB1");
    sp.initDefault();
    unsigned char nextByte;
    unsigned char ReadBuffer[256] = {0x00};
    unsigned char MsgBuffer[] = {0};
    std::cout << "Receiving bytes from /dev/ttyUSB1: " << ReadBuffer << std::endl;
    int index = 0;
    while(1)
    {
        std::cout << "**************************buffering**********************"
                  << std::endl;
        sp.readByte(nextByte);
        ReadBuffer[index++] = nextByte;
        if (nextByte == sp.START_BYTE_1)
        {
            sp.readByte(nextByte);
            ReadBuffer[index++] = nextByte;

            if (nextByte == sp.START_BYTE_2)
            {
                std::cout << "buffer after finding start bytes: "
                          << ReadBuffer << std::endl;

                sp.readByte(nextByte);
                ReadBuffer[index++] = nextByte;
                int startIndex = index - 3;
                int length = sp.readLengthByte(nextByte);
                //sp.read(reinterpret_cast<char*>(buffer), length);
                for (int i=0; i<(length+1); i++)
                {
                    sp.readByte(nextByte);
                    ReadBuffer[index++] = nextByte;
                }
                std::cout << "buffer after reading length of the message (plus 1 CRC byte): "
                          << ReadBuffer << std::endl;

                std::fill(MsgBuffer, MsgBuffer+sizeof(MsgBuffer), 0x00);

                memcpy(MsgBuffer, ReadBuffer+startIndex, startIndex+3+length);
                std::cout << "valid message buffer: "
                          << MsgBuffer
                          << std::endl;

                index = 0;
                std::fill(ReadBuffer, ReadBuffer+256, 0x00);
                std::cout << "buffer after reset: " << ReadBuffer << std::endl;
            }
        }
    }
    sp.Close();

    return 0;
}

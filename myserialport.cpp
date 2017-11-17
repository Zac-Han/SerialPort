#include "myserialport.h"
#include <iostream>

MySerialPort::MySerialPort()
{

}

void MySerialPort::initDefault()
{
    MySerialPort::SetBaudRate(SerialStreamBuf::BAUD_115200);
    MySerialPort::SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
    MySerialPort::SetFlowControl(SerialStreamBuf::FLOW_CONTROL_NONE);
    MySerialPort::SetParity(SerialStreamBuf::PARITY_NONE);
    MySerialPort::SetNumOfStopBits(1);
    if (!MySerialPort::good())
        std::cerr << "Initialization failed!" << std::endl;

}

void MySerialPort::initPort(SerialStreamBuf::BaudRateEnum baudRate,
              SerialStreamBuf::CharSizeEnum charSize,
              SerialStreamBuf::ParityEnum parityType,
              SerialStreamBuf::FlowControlEnum flowControlType,
              short Stopbit)
{
    MySerialPort::SetBaudRate(baudRate);
    MySerialPort::SetCharSize(charSize);
    MySerialPort::SetParity(parityType);
    MySerialPort::SetFlowControl(flowControlType);
    MySerialPort::SetNumOfStopBits(Stopbit);
    if (!MySerialPort::good())
        std::cerr << "Initialization failed!" << std::endl;

}

void MySerialPort::readByte(unsigned char &nextByte)
{
    MySerialPort::read(reinterpret_cast<char*>(&nextByte), 1);
}

//int MySerialPort::readLengthByte(unsigned char &nextByte)
//{
//    switch (nextByte) {
//    case 0x31:
//        return 1;
//        break;
//    case 0x32:
//        return 2;
//        break;
//    case 0x33:
//        return 3;
//        break;
//    case 0x34:
//        return 4;
//        break;
//    case 0x35:
//        return 5;
//        break;
//    case 0x36:
//        return 6;
//        break;
//    case 0x37:
//        return 7;
//        break;
//    case 0x38:
//        return 8;
//        break;
//    case 0x39:
//        return 9;
//        break;
//    default:
//        std::cerr << "Length byte not correct! No valid message found!" << std::endl;
//        return 0;
//        break;
//    }
//}

void MySerialPort::sendMsg(unsigned char *buffer, int length)
{
    int i = 0;
    std::cout << "Sending following "
              << length
              << " bytes to /dev/ttyUSB0: "
              << buffer << std::endl;
    while(i < length)
    {
        MySerialPort::put(buffer[i]);
        i++;
    }
}

void MySerialPort::readMsg()
{
    unsigned char nextByte;
    unsigned char ReadBuffer[256] = {0x00};
    unsigned char MsgBuffer[] = {0};
    std::cout << "Receiving bytes from /dev/ttyUSB1: " << ReadBuffer << std::endl;
    int index = 0;
    while(1)
    {
        MySerialPort::readByte(nextByte);
        std::cout << "**************************received 1 byte**********************"
                  << std::endl;
        ReadBuffer[index++] = nextByte;
        if (nextByte == START_BYTE_1)
        {
            MySerialPort::readByte(nextByte);
            std::cout << "**************************received 1 byte**********************"
                      << std::endl;
            ReadBuffer[index++] = nextByte;

            if (nextByte == START_BYTE_2)
            {
                std::cout << "Read buffer after finding start bytes: "
                          << ReadBuffer << std::endl;

                MySerialPort::readByte(nextByte);
                std::cout << "**************************received 1 byte**********************"
                          << std::endl;
                ReadBuffer[index++] = nextByte;
                int startIndex = index - 3;
                int length = nextByte;
                //sp.read(reinterpret_cast<char*>(buffer), length);
                for (int i=0; i<(length+1); i++)
                {
                    MySerialPort::readByte(nextByte);
                    std::cout << "**************************received 1 byte**********************"
                              << std::endl;
                    ReadBuffer[index++] = nextByte;
                }
                std::cout << "Read buffer after reading length of the message (plus 1 CRC byte): "
                          << ReadBuffer << std::endl;

                std::fill(MsgBuffer, MsgBuffer+sizeof(MsgBuffer), 0x00);

                memcpy(MsgBuffer, ReadBuffer+startIndex, startIndex+3+length);
                std::cout << "valid message buffer: "
                          << MsgBuffer
                          << std::endl;

                index = 0;
                std::fill(ReadBuffer, ReadBuffer+sizeof(ReadBuffer), 0x00);
                std::cout << "Read buffer after reset: " << ReadBuffer << std::endl;
            }
        }
    }
}

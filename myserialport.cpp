#include "myserialport.h"
#include <iostream>
#include <vector>

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

void MySerialPort::initPort(const std::string fileName, const SerialStreamBuf::BaudRateEnum baudRate,
              const SerialStreamBuf::CharSizeEnum charSize,
              const SerialStreamBuf::ParityEnum parityType,
              const SerialStreamBuf::FlowControlEnum flowControlType,
              const short Stopbit)
{
    MySerialPort::Open(fileName);
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
    std::vector<unsigned char> ReadBuffer;
    std::vector<unsigned char> MsgBuffer;
    std::cout << "Receiving bytes from /dev/ttyUSB1: " << std::endl;
    for(std::vector<unsigned char>::iterator iter = ReadBuffer.begin(); iter != ReadBuffer.end(); iter++)
    {
        std::cout << *iter;
    }
    std::cout << std::endl;
    int index = 0;
    while(1)
    {
        MySerialPort::readByte(nextByte);
        std::cout << "**************************received 1 byte**********************"
                  << std::endl;
        ReadBuffer.push_back(nextByte);
        index++;
        if (nextByte == START_BYTE_1)
        {
            MySerialPort::readByte(nextByte);
            std::cout << "**************************received 1 byte**********************"
                      << std::endl;
            ReadBuffer.push_back(nextByte);
            index++;

            if (nextByte == START_BYTE_2)
            {
                std::cout << "Read buffer after finding start bytes: "
                          << std::endl;
                for(std::vector<unsigned char>::iterator iter = ReadBuffer.begin(); iter != ReadBuffer.end(); iter++)
                {
                    std::cout << *iter;
                }
                std::cout << std::endl;


                MySerialPort::readByte(nextByte);
                std::cout << "**************************received 1 byte**********************"
                          << std::endl;
                ReadBuffer.push_back(nextByte);
                index++;
                int startIndex = index - 3;
                int length = nextByte;
                //sp.read(reinterpret_cast<char*>(buffer), length);
                for (int i=0; i<(length+1); i++)
                {
                    MySerialPort::readByte(nextByte);
                    std::cout << "**************************received 1 byte**********************"
                              << std::endl;
                    ReadBuffer.push_back(nextByte);
                    index++;
                }
                std::cout << "Read buffer after reading length of the message (plus 1 CRC byte): "
                          << std::endl;
                for(std::vector<unsigned char>::iterator iter = ReadBuffer.begin(); iter != ReadBuffer.end(); iter++)
                {
                    std::cout << *iter;
                }
                std::cout << std::endl;

                //MsgBuffer.clear();

                //MsgBuffer.assign(ReadBuffer.begin()+startIndex, ReadBuffer.end());
                MsgBuffer.insert(MsgBuffer.end(), ReadBuffer.begin()+startIndex, ReadBuffer.end());

                std::cout << "valid message buffer: "
                          << std::endl;
                for(std::vector<unsigned char>::iterator iter = MsgBuffer.begin(); iter != MsgBuffer.end(); iter++)
                {
                    std::cout << *iter;
                }
                std::cout << std::endl;

                index = 0;
                ReadBuffer.clear();
                std::cout << "Read buffer after reset: " << std::endl;
                for(std::vector<unsigned char>::iterator iter = ReadBuffer.begin(); iter != ReadBuffer.end(); iter++)
                {
                    std::cout << *iter;
                }
                std::cout << std::endl;
            }
        }
    }
}

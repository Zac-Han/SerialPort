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
    if (!MySerialPort::IsOpen() | !MySerialPort::good())
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
    if (!MySerialPort::IsOpen() | !MySerialPort::good())
        std::cerr << "Initialization failed!" << std::endl;

}

void MySerialPort::readByte()
{
    unsigned char nextByte;
    if(!MySerialPort::IsOpen() | !MySerialPort::good())
    {
        std::cout << "Unable to read from the serial port!" << std::endl;
        return;
    }
    MySerialPort::read(reinterpret_cast<char*>(&nextByte), 1);
    ReadBuffer.push_back(nextByte);
    std::cout << "**************************received 1 byte**********************"
              << std::endl;
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
    std::cout << "Receiving bytes from /dev/ttyUSB1: " << std::endl;
    printBuffer(ReadBuffer);
    while(1)
    {
        MySerialPort::readByte();
        MySerialPort::getMsg(ReadBuffer);
    }
}

bool MySerialPort::getMsg(std::vector<unsigned char> &ReadBuffer)
{
    if (ReadBuffer.empty()) {
        std::cout << "No bytes read from the serial port!" << std::endl;
        return false;
    }

    if (ReadBuffer.back() == START_BYTE_1) {
        std::cout << "Found first start byte" << std::endl;
        MySerialPort::readByte();
        if (ReadBuffer.back() == START_BYTE_2) {
            std::cout << "Found second start byte" << std::endl;
            std::cout << "Read buffer after finding start bytes: "
                      << std::endl;
            printBuffer(ReadBuffer);
            MySerialPort::readByte();
            int length = ReadBuffer.back();
            for (int i=0; i!=(length+1); i++)
            {
                MySerialPort::readByte();
            }
            std::cout << "Read buffer after reading length of the message (plus 1 CRC byte): "
                      << std::endl;
            printBuffer(ReadBuffer);
            MsgBuffer.insert(MsgBuffer.end(), ReadBuffer.end()-length-4, ReadBuffer.end());

            std::cout << "valid message buffer: "
                      << std::endl;
            printBuffer(MsgBuffer);
            ReadBuffer.clear();
        }
    }
}


void MySerialPort::printBuffer(std::vector<unsigned char> Buffer){
    for(std::vector<unsigned char>::iterator iter = Buffer.begin(); iter != Buffer.end(); iter++)
    {
        std::cout << *iter;
    }
    std::cout << std::endl;
}

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

int MySerialPort::readLengthByte(unsigned char &nextByte)
{
    switch (nextByte) {
    case 0x31:
        return 1;
        break;
    case 0x32:
        return 2;
        break;
    case 0x33:
        return 3;
        break;
    case 0x34:
        return 4;
        break;
    case 0x35:
        return 5;
        break;
    case 0x36:
        return 6;
        break;
    case 0x37:
        return 7;
        break;
    case 0x38:
        return 8;
        break;
    case 0x39:
        return 9;
        break;
    default:
        std::cerr << "Length byte not correct! No valid message found!" << std::endl;
        return 0;
        break;
    }
}

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

}

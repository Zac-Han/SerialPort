#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H
#include <fstream>
#include <cstdlib>
#include <SerialStream.h>

using namespace LibSerial;

class MySerialPort : public SerialStream
{
public:
    MySerialPort();

    /* Initialization of the serial port with default paremeters:
     * Baudrate:    115200
     * Char_Size:   8
     * Parity:      None
     * Flowcontrol: None
     * Stopbit:     1
     */
    void initDefault();

    /* Initialization of the serial port with individual paremeters,
     * Baudrate, Char_Size, Parity_Type, Flowcontrol_Type and Number of Stopbit
     */
    void initPort(SerialStreamBuf::BaudRateEnum baudRate,
                  SerialStreamBuf::CharSizeEnum charSize,
                  SerialStreamBuf::ParityEnum parityType,
                  SerialStreamBuf::FlowControlEnum flowControlType,
                  short Stopbit);
};

#endif // MYSERIALPORT_H

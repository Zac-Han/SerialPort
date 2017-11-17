#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <SerialStream.h>

using namespace LibSerial;

class MySerialPort : public SerialStream
{
public:
    MySerialPort();

    /* Start bytes
     */
    const unsigned char START_BYTE_1 = 0x10;
    const unsigned char START_BYTE_2 = 0xAF;



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

    /* Read next byte from the serial port
     */
    void readByte(unsigned char &nextByte);

//    /* After finding the start bytes read the next byte,
//     * which indicate the length of the valid message,
//     * and then return it
//     * ???What kind of value will be received here???
//     */
//    int readLengthByte(unsigned char &nextByte);

    /* Send message to the port
     */
    void sendMsg(unsigned char* buffer, int length);

    /* Read message from the port
     */
    void readMsg();

};

#endif // MYSERIALPORT_H

//=================================================================================================
///@file
///@brief
///@since
///@author
///
///@attention
///
///
//=================================================================================================

//========================================== Includes =============================================
#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <SerialStream.h>

//=========================================== Defines =============================================
#define MAX_MSG_LENGTH 45

//========================================== Typedefs =============================================
//<none>

//========================================= Constants =============================================
// Global -----------------------------------------------------------------------------------------
const unsigned char START_BYTE_1 = 0x10;
const unsigned char START_BYTE_2 = 0xAF;

// Local ------------------------------------------------------------------------------------------
// <none>

//========================================= Variables =============================================
// Global -----------------------------------------------------------------------------------------
// <none>

// Local ------------------------------------------------------------------------------------------
// <none>

//========================================== Prototypes ===========================================
// Global -----------------------------------------------------------------------------------------
// <none>

// Local ------------------------------------------------------------------------------------------
// <none>

//============================================ Code ===============================================
using namespace LibSerial;

struct MsgFromSp{
unsigned char nachricht[MAX_MSG_LENGTH];
};

/**
 * @brief The MySerialPort class
 */
class MySerialPort : public SerialStream
{
public:
    MySerialPort();

    void initDefault();

    /**
     * @brief initPort
     * @param fileName
     * @param baudRate
     * @param charSize
     * @param parityType
     * @param flowControlType
     * @param Stopbit
     */
    void initPort(const std::string fileName,
                  const SerialStreamBuf::BaudRateEnum baudRate,
                  const SerialStreamBuf::CharSizeEnum charSize,
                  const SerialStreamBuf::ParityEnum parityType,
                  const SerialStreamBuf::FlowControlEnum flowControlType,
                  const short Stopbit);

    void readByte(unsigned char &nextByte);

    void sendMsg(unsigned char* buffer, int length);

    void readMsg();

};

#endif // MYSERIALPORT_H

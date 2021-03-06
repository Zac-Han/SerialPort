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
unsigned char Msg[MAX_MSG_LENGTH];
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

    void readByte();

    void sendMsg(unsigned char* buffer, int length);

    void printBuffer(std::vector<unsigned char> Buffer);

    void printBuffer(std::vector<struct MsgFromSp> Buffer);

    bool MsgTask();

    struct MsgFromSp getMsg();

private:
    std::vector<unsigned char> ReadBuffer;
    std::vector<struct MsgFromSp> MsgBuffer;


};

#endif // MYSERIALPORT_H

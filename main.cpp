#include <iostream>
#include <string.h>
#include "myserialport.h"

int main()
{
    //Communication
    MySerialPort sp;
    sp.initPort("/dev/ttyUSB0",
                SerialStreamBuf::BAUD_115200,
                SerialStreamBuf::CHAR_SIZE_8,
                SerialStreamBuf::PARITY_NONE,
                SerialStreamBuf::FLOW_CONTROL_NONE,
                1);
    if (sp.IsOpen())
        std::cout << "/dev/ttyUSB0 is opened" << std::endl;
    else
        std::cout << "/dev/ttyUSB0 is NOT opened" << std::endl;

    sp.readMsg();

//    // Writing data to the port

//    unsigned char WriteBuffer[] = {0x30, 0x30, 0x10, 0xAF, 0x03, 0x41,
//                                   0x42, 0x43, 0x3F, 0x48, 0x49, 0x4A
//                                   };

//    while (conditional) {
//        sp.ReadByteTask(); // Liest immer ein BYte aus
//        sp.MsgTask(); // Buffer auswerten ob nachricht im Buffer vorhanden.
//                      // Wenn ja in einem zweiten Vector ablegen wo alle gültigen nachrichten vorhanden sind
//        struktur msg = sp.GetMsg(); // Rückgabe eines Telegrams
//        if (msg) {
//            // TODO:
//            // Nachricht bearbeiten
//        }

//    }
//    sp.sendMsg(WriteBuffer, sizeof(WriteBuffer));

    // Reading data from the port
//    MySerialPort sp;
//    sp.Open("/dev/ttyUSB1");
//    sp.initDefault();
//    sp.readMsg();
    sp.Close();

    return 0;
}

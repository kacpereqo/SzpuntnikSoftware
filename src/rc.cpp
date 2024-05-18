// #include "rc.hpp"
// #include <Arduino.h>
// #include <RadioLib.h>

// volatile bool receivedFlag = false;

// static nRF24 foooooo = new Module(10, 2, 3);

// void setFlag()
// {

//     // Serial.println("sex!");
//     receivedFlag = true;
// }

// RC::RC()
// {

//     // Serial.print(F("[nRF24] Initializing ... "));
//     int state = foooooo.begin();
//     if (state == RADIOLIB_ERR_NONE)
//     {
//         // Serial.println(F("success!"));
//     }
//     else
//     {
//         // Serial.print(F("failed, code "));
//         // Serial.println(state);
//         while (true)
//             ;
//     }

//     // set receive pipe 0 address
//     // NOTE: address width in bytes MUST be equal to the
//     //       width set in begin() or setAddressWidth()
//     //       methods (5 by default)
//     // Serial.print(F("[nRF24] Setting address for receive pipe 0 ... "));
//     byte addr[] = {0x01, 0x23, 0x45, 0x67, 0x89};
//     state = foooooo.setReceivePipe(0, addr);
//     if (state == RADIOLIB_ERR_NONE)
//     {
//         // Serial.println(F("success!"));
//     }
//     else
//     {
//         // Serial.print(F("failed, code "));
//         // Serial.println(state);
//         while (true)
//             ;
//     }

//     // set the function that will be called
//     // when new packet is received
//     foooooo.setPacketReceivedAction(setFlag);

//     // start listening
//     // Serial.print(F("[nRF24] Starting to listen ... "));
//     state = foooooo.startReceive();
//     if (state == RADIOLIB_ERR_NONE)
//     {
//         // Serial.println(F("success!"));
//     }
//     else
//     {
//         // Serial.print(F("failed, code "));
//         // Serial.println(state);
//         while (true)
//             ;
//     }
// }

// void RC::update()
// {
//     // if (receivedFlag)
//     // {

//     //     receivedFlag = false;

//     //     String str;
//     //     int state = radio.readData(str);

//     //     if (state == RADIOLIB_ERR_NONE)
//     //     {
//     //         // Serial.println(F("[nRF24] Received packet!"));

//     //         // Serial.print(F("[nRF24] Data:\t\t"));
//     //         // Serial.println(str);

//     //         switch1 = str[0] == '1';
//     //         switch2 = str[1] == '1';
//     //         switch3 = str[2] == '1';
//     //         switch4 = str[3] == '1';
//     //     }
//     //     else
//     //     {
//     //         // Serial.print(F("[nRF24] Failed, code "));
//     //         // Serial.println(state);
//     //     }

//     //     radio.startReceive();
//     // }
//     // check if the flag is set
//     if (receivedFlag)
//     {

//         receivedFlag = false;

//         String str;
//         int state = foooooo.readData(str);

//         if (state == RADIOLIB_ERR_NONE)
//         {
//             // packet was successfully received
//             // Serial.println(F("[nRF24] Received packet!"));

//             // print data of the packet
//             // Serial.print(F("[nRF24] Data:\t\t"));
//             // Serial.println(str);
//         }
//         else
//         {
//             // some other error occurred
//             // Serial.print(F("[nRF24] Failed, code "));
//             // Serial.println(state);
//         }

//         // put module back to listen mode
//         // Serial.print(F("[nRF24] Starting to listen ... "));
//         foooooo.startReceive();
//     }
// }

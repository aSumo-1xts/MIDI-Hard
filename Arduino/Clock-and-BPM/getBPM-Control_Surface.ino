/**
 * @file        getBPM-Control_Surface.ino
 * @author      aSumo (1xtelescope@gmail.com)
 * @brief       rx MIDI from DAW → detect Clock → convert to BPM
 * @version     1.0
 * @date        2024-06-16
 * @copyright   GPL-3.0
 * @details     This sketch can get BPM from Clock sent by DAW, with Library "Control_Surface.h".
 * @n           I use Arduino ProMicro and have verified it with AbletonLive 12 and StudioOne 6.
 */



#include <Control_Surface.h>
USBMIDI_Interface midi;



// #define LEDpin X
/*
↑If necessary, use with "digitalWrite(LEDpin, LOW);"
    and "digitalWrite(LEDpin, HIGH);" described below.
X may be 13 if you use UNO R3.
*/



uint16_t  BPM       = 0;  //!< global BPM
uint8_t   ppqn      = 0;  //!< 24 Pulses Per Quarter Note
uint32_t  startTime = 0;  //!< for Timer



/**
 * @brief         I don't know the details, but it is an alternative to "setHandleClock". 
 * @n             Closing the serial monitor may also stop the program.
 * @param rt      a mystery parameter
 * @return true   When you indicate that handling is done,
 * @n               and Control_Surface shouldn't handle it anymore.
 * @return false  When you want Control_Surface to handle it as well.
 */
bool realTimeMessageCallback(RealTimeMessage rt) {
    float preBPM = 0;                   // temporary BPM as a result of a single calculation

    if (ppqn == 0) {                    // the first Clock
        startTime = micros();           // start Timer
        // digitalWrite(LEDpin, LOW);   // Sync LED: OFF
    }

    ppqn++;                             // count up Clock

    if (ppqn > 24) {                    // 24 Clocks = 1 bar
        preBPM  = 6.0e+07 / float(micros() - startTime);    // stop Timer, calculate BPM
        if(20 <= preBPM && preBPM <= 999) {                 // adopt if reasonable
            BPM = round(preBPM);
        }
        Serial.println(BPM);            // or just "Serial.println(preBPM)"
        // digitalWrite(LEDpin, HIGH);  // Sync LED: ON
        ppqn = 0;                       // reset Clock
    }

    return true;
}



/**
 * @brief setup()
 */
void setup() {
    Control_Surface.begin();
    Control_Surface.setMIDIInputCallbacks(nullptr, nullptr, nullptr, realTimeMessageCallback);
}



/**
 * @brief loop()
 */
void loop() {
    Control_Surface.loop();
}
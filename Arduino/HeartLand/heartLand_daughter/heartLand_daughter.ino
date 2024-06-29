/**
 * @file        heartLand_daughter.ino
 * @author      aSumo (1xtelescope@gmail.com)
 * @brief       a sketch for ProMicro in USB-MIDI Controller "HeartLand"
 * @version     1.0
 * @date        2024-06-26
 * @copyright   GPL-3.0
 * @details     just send serial MIDI message from TX0
 */

#include <Control_Surface.h>

SerialMIDI_Interface<decltype(Serial)> midi_ser {Serial, MIDI_BAUD};    //!< 単純なシリアル通信のためのインスタンス

/* ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ variable to change ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ */

uint8_t ch[3] = {2, 3, 4};  //!< MIDIチャンネルの管理

/* ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ variable to change ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ */





CCButton sws[] = {
    {2,  {MIDI_CC::General_Purpose_Controller_3, Channel::createChannel(ch[1])}, }, // Solo01
    {3,  {MIDI_CC::General_Purpose_Controller_6, Channel::createChannel(ch[1])}, }, // Solo02
    {5,  {MIDI_CC::General_Purpose_Controller_3, Channel::createChannel(ch[2])}, }, // Solo03
    {7,  {MIDI_CC::General_Purpose_Controller_6, Channel::createChannel(ch[2])}, }, // Solo04
};





CCPotentiometer pots[] = {
    {A6,  {MIDI_CC::General_Purpose_Controller_1, Channel::createChannel(ch[1])}, }, // Pan01
    {A0,  {MIDI_CC::General_Purpose_Controller_2, Channel::createChannel(ch[1])}, }, // Vol01
    {A7,  {MIDI_CC::General_Purpose_Controller_4, Channel::createChannel(ch[1])}, }, // Pan02
    {A1,  {MIDI_CC::General_Purpose_Controller_5, Channel::createChannel(ch[1])}, }, // Vol02
    {A8,  {MIDI_CC::General_Purpose_Controller_1, Channel::createChannel(ch[2])}, }, // Pan03
    {A2,  {MIDI_CC::General_Purpose_Controller_2, Channel::createChannel(ch[2])}, }, // Vol03
    {A9,  {MIDI_CC::General_Purpose_Controller_4, Channel::createChannel(ch[2])}, }, // Pan04
    {A3,  {MIDI_CC::General_Purpose_Controller_5, Channel::createChannel(ch[2])}, }, // Vol04
    {A10, {MIDI_CC::Balance,                      Channel::createChannel(ch[0])}, }, // A x B
};

//! @brief 可変抵抗によるCCの値をすべて読み取って送る。
void initPot(uint8_t pinNum, uint8_t ccNum, uint8_t chNum) {
    float primPotCC = analogRead(pinNum) * 128 / 1023;
    midi_ser.sendControlChange({ccNum, Channel::createChannel(chNum)}, round(primPotCC));
}





//! @brief setup関数
void setup() {
    Control_Surface.begin();

    initPot(18, 17, 1);
    initPot(19, 80, 1);
    initPot(20, 17, 2);
    initPot(21, 80, 2);
    initPot(4,  16, 1);
    initPot(6,  19, 1);
    initPot(8,  18, 2);
    initPot(9,  19, 2);
    initPot(10, 8,  0);
}

//! @brief loop関数
void loop() {
    Control_Surface.loop();
}
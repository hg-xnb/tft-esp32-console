#ifndef SERIAL_UTILS_H
#define SERIAL_UTILS_H


#include "Arduino.h"

#ifndef LOG
    #define LOG true
#endif

void printRightAligned(int value, int width) {
    char buffer[12]; // Buffer large enough for number + brackets + spaces
    sprintf(buffer, "[%*d]", width - 2, value); // -2 accounts for [ and ]
    Serial.println(buffer);
}


template<class Tmsg>
void msg2ser(Tmsg msg){
    #if LOG == true
        Serial.println(String(msg));
    #endif
}

template<class Tmsg, class... Tmsgs>
void msg2ser(Tmsg msg, Tmsgs... msgs){
    #if LOG == true
        Serial.print(msg);
        msg2ser(msgs...);
    #endif
}

template<class... Tmsgs>
void log2ser(Tmsgs... msgs){
    #if LOG == true
        static char buffer[12]; // Buffer large enough for number + brackets + spaces
        sprintf(buffer, "[%*d]", /*width*/ 12, millis()); // -2 accounts for [ and ]

        msg2ser(buffer, " ", msgs...);
    #endif
}

template<class... Tmsgs>
void info(Tmsgs... msgs){
    #if LOG == true
        msg2ser("[", millis(), "] ", "info\t",msgs...);
    #endif
}

template<class... Tmsgs>
void call(Tmsgs... msgs){
    #if LOG == true
        msg2ser("[", millis(), "] ", "call\t",msgs...);
    #endif
}

void init_serial(){
    #if LOG == true
        Serial.begin(115200);
        log2ser("Hello from ngxxfus (aka hg.xnb)");
    #endif
}

#endif
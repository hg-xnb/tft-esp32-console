#include "Arduino.h"
/// Global var 
String label[]={
    "Humid",
    "Temp",
    "DEV-0",
    "DEV-1",
    "DEV-2",
    "DEV-3"
};

float ENV_STAT[2];
bool DEV_STAT[4];

/// Include 
#include "firebase_utils.h"
#include "tft_utils.h"
#include "serial_utils.h"
#include "DHT.h"

/// Others
#define DHTTYPE DHT11
#define DHT_DAT_PIN 16
DHT dht(DHT_DAT_PIN, DHTTYPE);

CANVAS<uint16_t> canvas;

void init_canvas(){
    canvas.initialize(220, 172, 0, 0);
    canvas.insert_text(POINT<>(90, 20),  "~Hello! #HAHA~", 0xFFFF);
    canvas.insert_text(POINT<>(125, 19), "This is a gift", 0xFFFF);
    canvas.insert_text(POINT<>(145, 19), "from ngxxfus :>", 0xFFFF);
    canvas.show(true);
    canvas.refill(0xFFFF);
}



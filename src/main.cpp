// /// NOTES --------------------------------------------------------------- ///
// // Firebase tree:
// /*
//     /
//     ├── devices-1
//     │   ├── 0 : true/false
//     │   ├── 1 : true/false
//     │   ├── 2 : true/false
//     │   └── 3 : true/false
//     └── env_info
//         ├── humid : "ab.cd"
//         └── temp : "ab.cd"
// */

// // Path:
// /*
//     All root paths must be formed with prefix and suffix is "/". 
//     E.g: "/devices-1/"
// */

// /// INCLUDES ------------------------------------------------------------- ///
// #include "Arduino.h"
// /// Global var 
// String label[]={
//     "Humid",
//     "Temp",
//     "DEV-0",
//     "DEV-1",
//     "DEV-2",
//     "DEV-3"
// };

// float ENV_STAT[2];
// bool DEV_STAT[4];

// /// FOR DEBUG ------------------------------------------------------------ ///
// #ifndef LOG
// #define LOG true
// #endif

// template<class Tmsg>
// void msg2ser(Tmsg msg){
//     #if LOG == true
//         Serial.println(String(msg));
//     #endif
// }

// template<class Tmsg, class... Tmsgs>
// void msg2ser(Tmsg msg, Tmsgs... msgs){
//     #if LOG == true
//         Serial.print(msg);
//         msg2ser(msgs...);
//     #endif
// }

// template<class... Tmsgs>
// void log2ser(Tmsgs... msgs){
//     #if LOG == true
//         msg2ser("[", millis(), "] ", msgs...);
//     #endif
// }

// void init_serial(){
//     #if LOG == true
//         Serial.begin(115200);
//         log2ser("Hello from ngxxfus (aka hg.xnb)");
//     #endif
// }

// /// FOR FIREBASE AND WIFI ------------------------------------------------ ///
// #define WIFI_SSID "hg.xnb"
// #define WIFI_PWD "nGXXFUS@3204"
// #include "WiFi.h"

// #define DATABASE_URL "https://lab3-itfa-default-rtdb.firebaseio.com/"
// #define API_KEY "AIzaSyBMq4aT1Jx6nICW4yuYtTSIU9QSzIa1vmk"
// #define EMAIL "ngxxfus@lab3-itfa.iam.gserviceaccount.com"
// #define PASSWORD "nGXXFUS@3204"

// #include "Firebase_ESP_Client.h"

// FirebaseData firebaseData;
// FirebaseAuth auth;
// FirebaseConfig config;

// void init_wifi(){
//     if(WiFi.status() == WL_CONNECTED) return;
//     WiFi.mode(WIFI_STA); 
//     WiFi.disconnect();
//     WiFi.begin(WIFI_SSID, WIFI_PWD);
//     do{
//         log2ser("WiFi-Status: ", WiFi.status());
//         log2ser("Connecting to Wi-fi...");
//         delay(2000);
//     }while(WiFi.status() != WL_CONNECTED);
//     log2ser("Connected to Wi-fi!");
//     log2ser("IP-Addr: ", WiFi.localIP().toString());
// }


// uint16_t fetch_fb(bool* DEV, uint16_t num, String root = "/"){
//     uint16_t failed = 0;
//     String path = "";
//     for(uint16_t i = 0; i < num; ++i){
//         path  = root; path.concat(i);
//         if( !Firebase.RTDB.getBool(&firebaseData, path) ){
//             log2ser("Failed to get data from ", path, "!");
//             ++failed;
//         }else{
//             DEV[i] = firebaseData.boolData();
//         }
//     }
//     return failed;
// }

// uint16_t upload_fb(float humidity, float temperature, String root="/"){
//     uint16_t failed = 0;
    
//     if(isnan(humidity)) humidity = -1.0f;
//     if(isnan(temperature)) temperature = -1.0f;

//     String path  = root;    path.concat("humid");
//     if( !Firebase.RTDB.setString(&firebaseData, path, String(humidity)) ){
//         log2ser("Failed to set humidity value!");
//         ++failed;
//     }

//     path  = root;    path.concat("temp");
//     if( !Firebase.RTDB.setString(&firebaseData, path, String(temperature)) ){
//         log2ser("Failed to set temperature value!");
//         ++failed;
//     }

//     return failed;
// }

// void init_firebase() {
//     log2ser("Connecting to Firebase...");
//     config.api_key = API_KEY;
//     config.database_url = DATABASE_URL;
//     auth.user.email = EMAIL;
//     auth.user.password = PASSWORD;
//     do Firebase.begin(&config, &auth);
//     while(!Firebase.ready());
//     Firebase.reconnectWiFi(true);
//     log2ser("Connected to Firebase!");
// }

// /// FOR DHT-11 ----------------------------------------------------------- ///

// #include "DHT.h"
// #define DHTTYPE DHT11
// #define DHT_DAT_PIN 16
// DHT dht(DHT_DAT_PIN, DHTTYPE);

// /// FOR I/O CONTROL ------------------------------------------------------ ///

// void init_io(){
//     /// call for initialize GPIO ports
// }

// void update_io(){
//     /// call for set GPIO ports
// }

// /// SETUP ---------------------------------------------------------------- ///

// void setup(){
//     init_serial();
//     init_io();
//     init_wifi();
//     init_firebase();
//     log2ser("System initialed!");
// }

// /// LOOP ----------------------------------------------------------------- ///

// void loop(){
//     float humid = dht.readHumidity(),
//           temp  = dht.readTemperature();

//     /// update ENV_STAT
//     if((ENV_STAT[0] != humid) || (ENV_STAT[1] != temp)){
//         ENV_STAT[0] = humid; ENV_STAT[1] = temp;
//         upload_fb(ENV_STAT[0], ENV_STAT[1], "/env_info/");
//     }

//     /// fetch data from RTDB
//     fetch_fb(DEV_STAT, 4, "/devices-1/");
    
//     /// update gpio state
//     update_io();

//     /// draw one new 
//     for(uint8_t i = 0; i < 6; i++){
//         if (i < 2){
//             log2ser(label[i], ": ", ENV_STAT[i]);
//         }else{
//             log2ser(label[i], ": ", String(DEV_STAT[i-2]?"ON":"OFF"));
//         }
//     }
//     log2ser();
// }







/// TEST CONSOLE ------------------------------------------------------------------- ///

/// NOTES --------------------------------------------------------------- ///
// Firebase tree:
/*
    /
    ├── devices-1
    │   ├── 0 : true/false
    │   ├── 1 : true/false
    │   ├── 2 : true/false
    │   └── 3 : true/false
    └── env_info
        ├── humid : "ab.cd"
        └── temp : "ab.cd"
*/

// Path:
/*
    All root paths must be formed with prefix and suffix is "/". 
    E.g: "/devices-1/"
*/

/// INCLUDES ------------------------------------------------------------- ///

#include "Arduino.h"
#include "console.h"

/// Global var ----------------------------------------------------------- ///
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

/// FOR SERIAL COM ------------------------------------------------------- ///

#ifndef LOG
    #define LOG true
#endif

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
        msg2ser("[", millis(), "] ", msgs...);
    #endif
}

void init_serial(){
    #if LOG == true
        Serial.begin(115200);
        log2ser("Hello from ngxxfus (aka hg.xnb)");
    #endif
}
/// FOR DEBUG ------------------------------------------------------------ ///
#define PRINT_MSG log2screen
#ifndef PRINT_MSG
    #define PRINT_MSG log2ser
#endif

/// FOR FIREBASE AND WIFI ------------------------------------------------ ///
#define WIFI_SSID "hg.xnb"
#define WIFI_PWD "nGXXFUS@3204"
#include "WiFi.h"

#define DATABASE_URL "https://lab3-itfa-default-rtdb.firebaseio.com/"
#define API_KEY "AIzaSyBMq4aT1Jx6nICW4yuYtTSIU9QSzIa1vmk"
#define EMAIL "ngxxfus@lab3-itfa.iam.gserviceaccount.com"
#define PASSWORD "nGXXFUS@3204"

#include "Firebase_ESP_Client.h"

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

void init_wifi(){
    if(WiFi.status() == WL_CONNECTED) return;
    WiFi.mode(WIFI_STA); 
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PWD);
    do{
        PRINT_MSG("WiFi-Status: ", WiFi.status());
        PRINT_MSG("Connecting to Wi-fi...");
        delay(2000);
    }while(WiFi.status() != WL_CONNECTED);
    PRINT_MSG("Connected to Wi-fi!");
    PRINT_MSG("IP-Addr: ", WiFi.localIP().toString());
}


uint16_t fetch_fb(bool* DEV, uint16_t num, String root = "/"){
    uint16_t failed = 0;
    String path = "";
    for(uint16_t i = 0; i < num; ++i){
        path  = root; path.concat(i);
        if( !Firebase.RTDB.getBool(&firebaseData, path) ){
            PRINT_MSG("Failed to get data from ", path, "!");
            ++failed;
        }else{
            DEV[i] = firebaseData.boolData();
        }
    }
    return failed;
}

uint16_t upload_fb(float humidity, float temperature, String root="/"){
    uint16_t failed = 0;
    
    if(isnan(humidity)) humidity = -1.0f;
    if(isnan(temperature)) temperature = -1.0f;

    String path  = root;    path.concat("humid");
    if( !Firebase.RTDB.setString(&firebaseData, path, String(humidity)) ){
        PRINT_MSG("Failed to set humidity value!");
        ++failed;
    }

    path  = root;    path.concat("temp");
    if( !Firebase.RTDB.setString(&firebaseData, path, String(temperature)) ){
        PRINT_MSG("Failed to set temperature value!");
        ++failed;
    }

    return failed;
}

void init_firebase() {
    PRINT_MSG("Connecting to Firebase...");
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    auth.user.email = EMAIL;
    auth.user.password = PASSWORD;
    do Firebase.begin(&config, &auth);
    while(!Firebase.ready());
    Firebase.reconnectWiFi(true);
    PRINT_MSG("Connected to Firebase!");
}

/// FOR DHT-11 ----------------------------------------------------------- ///

#include "DHT.h"
#define DHTTYPE DHT11
#define DHT_DAT_PIN 16
DHT dht(DHT_DAT_PIN, DHTTYPE);

/// MAIN CODE ----------------------------------------------------------- ///

void setup(){
    init_serial();
    init_tft_screen();

    clear_canvas();
    show_canvas(true);
    
    init_wifi();
    init_firebase();
}

void loop(){
    PRINT_MSG("Getting Humid and Temp...");
    float humid = dht.readHumidity(),
          temp  = dht.readTemperature();

    PRINT_MSG("Uploading to RTDB...");
    /// update ENV_STAT
    if((ENV_STAT[0] != humid) || (ENV_STAT[1] != temp)){
        ENV_STAT[0] = humid; ENV_STAT[1] = temp;
        upload_fb(ENV_STAT[0], ENV_STAT[1], "/env_info/");
    }

    PRINT_MSG("Fetching data from RTDB...");
    /// fetch data from RTDB
    fetch_fb(DEV_STAT, 4, "/devices-1/");
    
    PRINT_MSG("DONE. Result:");
    /// draw one new 
    for(uint8_t i = 0; i < 6; i++){
        if (i < 2){
            PRINT_MSG(label[i], ": ", ENV_STAT[i]);
        }else{
            PRINT_MSG(label[i], ": ", String(DEV_STAT[i-2]?"ON":"OFF"));
        }
    }
    PRINT_MSG();
};
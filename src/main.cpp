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

/// FOR DEBUG ------------------------------------------------------------ ///
#define PRINT_MSG log2screen2
#ifndef PRINT_MSG
    #define PRINT_MSG2 log2ser
#endif

#define PRINT_MSG2 log2screen2
#ifndef PRINT_MSG2
    #define PRINT_MSG2 log2ser
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
        PRINT_MSG2("WiFi-Status: ", WiFi.status());
        PRINT_MSG2("Connecting to Wi-fi...");
        delay(2000);
    }while(WiFi.status() != WL_CONNECTED);
    PRINT_MSG2("Connected to Wi-fi!");
    PRINT_MSG2("IP-Addr: ", WiFi.localIP().toString());
}


uint16_t fetch_fb(bool* DEV, uint16_t num, String root = "/"){
    uint16_t failed = 0;
    String path = "";
    for(uint16_t i = 0; i < num; ++i){
        path  = root; path.concat(i);
        if( !Firebase.RTDB.getBool(&firebaseData, path) ){
            PRINT_MSG2("Failed to get data from ", path, "!");
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
        PRINT_MSG2("Upload `humid`: Failed!");
        ++failed;
    }

    path  = root;    path.concat("temp");
    if( !Firebase.RTDB.setString(&firebaseData, path, String(temperature)) ){
        PRINT_MSG2("Upload `temp`: Failed!");
        ++failed;
    }

    return failed;
}

void init_firebase() {
    PRINT_MSG2("Connecting to Firebase...");
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    auth.user.email = EMAIL;
    auth.user.password = PASSWORD;
    do Firebase.begin(&config, &auth);
    while(!Firebase.ready());
    Firebase.reconnectWiFi(true);
    PRINT_MSG2("Connected to Firebase!");
}

/// FOR DHT-11 ----------------------------------------------------------- ///
#include "DHT.h"
#define DHTTYPE DHT11
#define DHT_DAT_PIN 16
DHT dht(DHT_DAT_PIN, DHTTYPE);

/// MAIN CODE ----------------------------------------------------------- ///
void setup(){
    init_tft_screen();

    clear_canvas();
    show_canvas(true);
    
    init_wifi();
    init_firebase();
}

void loop(){
    PRINT_MSG("Getting Humid & Temp...");
    float humid = dht.readHumidity(),
          temp  = dht.readTemperature();

    PRINT_MSG("DONE! Result:");
    PRINT_MSG(label[0], ": ", ENV_STAT[0]);
    PRINT_MSG(label[1], ": ", ENV_STAT[1]);

    PRINT_MSG("Uploading data...");
    if((ENV_STAT[0] != humid) || (ENV_STAT[1] != temp)){
        ENV_STAT[0] = humid; ENV_STAT[1] = temp;
        upload_fb(ENV_STAT[0], ENV_STAT[1], "/env_info/");
    }

    PRINT_MSG("Fetching data...");
    fetch_fb(DEV_STAT, 4, "/devices-1/");
    
    PRINT_MSG("DONE! Result:");
    for(uint8_t i = 2; i < 6; i++){
        PRINT_MSG(label[i], ": ", String(DEV_STAT[i-2]?"ON":"OFF"));
    }
    PRINT_MSG();
};
#include "Arduino.h"
#include "serial_utils.h"

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
        log2ser("WiFi-Status: ", WiFi.status());
        log2ser("Connecting to Wi-fi...");
        delay(2000);
    }while(WiFi.status() != WL_CONNECTED);
    log2ser("Connected to Wi-fi!");
    log2ser("IP-Addr: ", WiFi.localIP().toString());
}


uint16_t fetch_fb(bool* DEV, uint16_t num, String root = "/"){
    uint16_t failed = 0;
    String path = "";
    for(uint16_t i = 0; i < num; ++i){
        path  = root; path.concat(i);
        if( !Firebase.RTDB.getBool(&firebaseData, path) ){
            log2ser("Failed to get data from ", path, "!");
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
        log2ser("Failed to push humidity value!");
        ++failed;
    }

    path  = root;    path.concat("temp");
    if( !Firebase.RTDB.setString(&firebaseData, path, String(temperature)) ){
        log2ser("Failed to push temperature value!");
        ++failed;
    }

    return failed;
}

void init_firebase() {
    log2ser("Connecting to Firebase...");
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    auth.user.email = EMAIL;
    auth.user.password = PASSWORD;
    do Firebase.begin(&config, &auth);
    while(!Firebase.ready());
    Firebase.reconnectWiFi(true);
    log2ser("Connected to Firebase!");
}
#include "main.h"

void setup(){
    init_serial();
    init_canvas();
    init_wifi();
    init_firebase();
    log2ser("System initialed!");
}

void loop(){
    ENV_STAT[0] = dht.readHumidity();
    ENV_STAT[1] = dht.readTemperature();
    
    canvas.refill(0xFFFF);
    
    upload_fb(ENV_STAT[0], ENV_STAT[1], "/env_info/");
    fetch_fb(DEV_STAT, 4, "/devices-1/");
    
    
    for(uint8_t i = 0; i < 6; i++){
        canvas.insert_text(POINT<>(30+25*(i), 5), label[i], 0x0);
        if (i < 2){
            log2ser(label[i], ": ", ENV_STAT[0]);
            canvas.insert_text(POINT<>(30+25*(i), 75), String(ENV_STAT[i]), 0);
        }else{
            log2ser(label[i], ": ", DEV_STAT[i-2]?"ON":"OFF");
            canvas.insert_text(POINT<>(30+25*(i), 75), String(DEV_STAT[i-2]?"ON":"OFF"), 0x0);
        }
    }
    canvas.show();
}














#include "main.h"

void setup(){
    init_serial();
    init_canvas();
    init_wifi();
    init_firebase();
    log2ser("System initialed!");
}

void loop(){
    float humid = dht.readHumidity(),
          temp  = dht.readTemperature();

    /// undo what drawn :v bcz of the background is 0xFFFF
    for(uint8_t i = 0; i < 6; i++){
        canvas.insert_text(POINT<>(30+25*(i), 5), label[i], 0xFFFF);
        if (i < 2){
            canvas.insert_text(POINT<>(30+25*(i), 75), String(ENV_STAT[i]), 0xFFFF);
        }else
            canvas.insert_text(POINT<>(30+25*(i), 75), String(DEV_STAT[i-2]?"ON":"OFF"), 0xFFFF);
    }

    /// update ENV_STAT
    if((ENV_STAT[0] != humid) || (ENV_STAT[1] != temp)){
        ENV_STAT[0] = humid; ENV_STAT[1] = temp;
        upload_fb(ENV_STAT[0], ENV_STAT[1], "/env_info/");
    }

    /// fetch data from RTDB
    fetch_fb(DEV_STAT, 4, "/devices-1/");
    
    /// draw one new 
    for(uint8_t i = 0; i < 6; i++){
        canvas.insert_text(POINT<>(30+25*(i), 5), label[i], 0x0);
        if (i < 2){
            canvas.insert_text(POINT<>(30+25*(i), 75), String(ENV_STAT[i]), 0);
        }else{
            canvas.insert_text(POINT<>(30+25*(i), 75), String(DEV_STAT[i-2]?"ON":"OFF"), 0x0);
        }
    }
    canvas.show();
}



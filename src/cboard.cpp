#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED_SCL -> PIN 19
// OLED_SDA -> PIN 20

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define BTN_OK 2
#define BTN_UP 3
#define BTN_DOWN 4

Adafruit_SSD1306 display(
    SCREEN_WIDTH, 
    SCREEN_HEIGHT, 
    &Wire, 
    -1
);

// Page indexes:
// 0 -> home
// 1 -> menu
// 2 -> ble devices

int page_index = 0;

void setup(){
    Serial.begin(9600);
    Wire.begin();

    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(BTN_OK, INPUT_PULLUP);


    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
        Serial.println("failed to init display module.");
    }
    Serial.println("display initialized");


    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

}

void draw_home(){
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("CONNECTION STAT: ");
    display.display();
}

void draw_menu(){
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("MENU ");
    display.display();
}

void loop(){
    int btn_ok = digitalRead(BTN_OK);
    // int btn_up = digitalRead(BTN_UP);
    // int btn_down = digitalRead(BTN_DOWN);

    if(btn_ok == LOW){
        Serial.println("OK Cliked");
        // is at home
        if(page_index == 0){
            page_index = 1;
        }

        if(page_index == 1){
            page_index = 0;
        }
    }

    switch(page_index){

        case 0:
            draw_home();
            break;

        case 1:
            draw_menu();
            break;

        default:
            draw_home();
            Serial.println("defualt");
            break;
    }
}

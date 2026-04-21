#include <Wire.h>
#include <string.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED_SCL -> PIN 19
// OLED_SDA -> PIN 20

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define BTN_OK 2
#define BTN_DOWN 3
#define BTN_UP 4

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1);

// Page indexes:
// 0 -> home
// 1 -> menu
// 2 -> ble devices

int page_index = 0;

// menu
const char *items[] = {"DEVICES", "DISCONNECT", "BACK"};
const int menu_item_spacing = 15;
int active_item = 0; // devices -> 0, disconnect -> 1, back -> 2
size_t item_len = strlen(*items);

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(BTN_OK, INPUT_PULLUP);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("failed to init display module.");
    }
    Serial.println("display initialized");

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
}

void draw_home()
{
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("CONNECTION STAT: ");
    display.display();
}

void draw_menu(int active_item)
{
    display.clearDisplay();
    display.setCursor((SCREEN_WIDTH / 2) - strlen("MENU"), 0);
    display.fillRect(0, 0, SCREEN_WIDTH, 10, WHITE);
    display.setTextColor(SSD1306_BLACK);
    display.println("MENU");

    int prev_y = 5; // padding
    for (int i = 0; i < strlen(*items); i++)
    {
        prev_y += menu_item_spacing;
        display.setCursor(0, prev_y);

        display.setTextColor(SSD1306_WHITE);

        if (i == active_item)
        {
            display.fillRect(0, prev_y,
                             SCREEN_WIDTH, 10, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
        }
        display.println(items[i]);
        display.setTextColor(SSD1306_WHITE);
    }
    display.display();
}

void loop()
{

    int btn_ok = digitalRead(BTN_OK);
    int btn_down = digitalRead(BTN_DOWN);
    int btn_up = digitalRead(BTN_UP);

    switch (page_index)
    {
    case 0:
        draw_home();
        break;

    case 1:
        draw_menu(active_item);
        break;

    default:
        break;
    }

    if (btn_ok == LOW)
    {
        switch (page_index)
        {
        case 0:
            page_index = 1;
            draw_menu(active_item);
            break;

        case 1:
            // get the active item
            Serial.println(items[active_item]);
            break;

        default:
            break;
        }
    }

    if (btn_down == LOW)
    {
        switch (page_index)
        {
        case 0:
            break;

        case 1:
            active_item -= 1;
            if(active_item < 0){
                active_item = 0;
            }
            break;

        default:
            break;
        }
    }

    // btn down
    if (btn_up == LOW)
    {
        switch (page_index)
        {
        case 0:
            break;

        case 1:
            active_item += 1;
            if(active_item > 2){
                active_item = 0;
            }
            draw_menu(active_item);

        default:
            break;
        }
    }
}

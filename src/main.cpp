#include <Wire.h>
#include <Adafruit_SH110X.h>

#include "core/Stack.h"
#include "core/Graphics.h"
#include "widgets/Screen.h"
#include "core/OLEDisplayX.h"
#include "layouts/Column.h"
#include "layouts/Row.h"
#include "widgets/Label.h"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

#define SDA 8
#define SCK 4

Adafruit_SH1106G oled = Adafruit_SH1106G(
  DISPLAY_WIDTH, 
  DISPLAY_HEIGHT,
  &Wire,
  -1
);

OLEDisplayX display(
  DISPLAY_WIDTH,
  DISPLAY_HEIGHT,
  &oled
);

Graphics gfx(&display);

Stack app(display, gfx);
Screen home_screen(
  &display,
  "Home"
);
Row root_layout(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT - 10);
Row temp_container(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT - 10);
Label itemp_label(20, 10, "Temp: ", {255, 255, 255});
Label temp_val(10, 10, "0", {255, 255, 255});

void setup(){
  Serial.begin(115200);
  Wire.begin(SDA, SCK);
  Wire.setClock(400000);

  temp_container.addChild(&itemp_label);
  temp_container.addChild(&temp_val);
  root_layout.addChild(&temp_container);
  home_screen.addChild(&root_layout);

  app.addScreen(home_screen);
  
  if(!oled.begin(0x3C, true)){
    while(1);
  }

  oled.setTextSize(2);

  display.clear();
  app.goTo(display, home_screen, gfx);
  display.flush();
}


void loop(){
  app.renderApp(gfx);
  display.flush();
}
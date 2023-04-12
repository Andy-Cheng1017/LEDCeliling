#include <Arduino.h>
#line 1 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"


// Example sketch which shows how to display some patterns
// on a 64x32 LED matrix
//
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>

#include "USB.h"

#define R1_PIN 4
#define G1_PIN 5
#define B1_PIN 6
#define R2_PIN 7
#define G2_PIN 15
#define B2_PIN 16
#define A_PIN 18
#define B_PIN 8
#define C_PIN 3
#define D_PIN 9
#define E_PIN 17
#define CLK_PIN 14
#define LAT_PIN 21
#define OE_PIN 47

#define PANEL_RES_X 64  // Number of pixels wide of each INDIVIDUAL panel module.
#define PANEL_RES_Y 64  // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 3   // Total number of panels chained one to another
#define PANE_WIDTH PANEL_WIDTH *PANELS_NUMBER
#define PANE_HEIGHT PANEL_HEIGHT

#define PIXEL_COLOR_DEPTH_BITS 1

// MatrixPanel_I2S_DMA dma_display;
MatrixPanel_I2S_DMA *dma_display = nullptr;

uint16_t myBLACK = dma_display->color565(0, 0, 0);
uint16_t myWHITE = dma_display->color565(255, 255, 255);
uint16_t myRED = dma_display->color565(255, 0, 0);
uint16_t myGREEN = dma_display->color565(0, 255, 0);
uint16_t myBLUE = dma_display->color565(0, 0, 255);

// USBCDC Serial;

#line 45 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
void setup();
#line 112 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
void loop();
#line 45 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
void setup() {
    // Module configuration
    HUB75_I2S_CFG::i2s_pins _pins = {
        R1_PIN,
        G1_PIN,
        B1_PIN,
        R2_PIN,
        G2_PIN,
        B2_PIN,
        A_PIN,
        B_PIN,
        C_PIN,
        D_PIN,
        E_PIN,
        LAT_PIN,
        OE_PIN,
        CLK_PIN};
    HUB75_I2S_CFG mxconfig(
        PANEL_RES_X,  // module width
        PANEL_RES_Y,  // module height
        PANEL_CHAIN,  // Chain length
        _pins);

    Serial.begin(115200);
    // USB.begin();
    // Serial1.setDebugOutput(true);
    // mxconfig.gpio.e = 18;
    // mxconfig.clkphase = false;
    mxconfig.driver = HUB75_I2S_CFG::FM6124;

    // Display Setup
    dma_display = new MatrixPanel_I2S_DMA(mxconfig);
    dma_display->begin();
    dma_display->setBrightness8(255);  // 0-255
    dma_display->clearScreen();
    // USB.begin();
    // dma_display->fillScreen(myWHITE);

    // fix the screen with green
    // dma_display->fillRect(0, 0, dma_display->width(), dma_display->height(), dma_display->color444(0, 15, 0));
    // delay(500);

    // // draw a box in yellow
    // dma_display->drawRect(0, 0, dma_display->width(), dma_display->height(), dma_display->color444(15, 15, 0));
    // delay(500);

    // // draw an 'X' in red
    // dma_display->drawLine(0, 0, dma_display->width()-1, dma_display->height()-1, dma_display->color444(15, 0, 0));
    // dma_display->drawLine(dma_display->width()-1, 0, 0, dma_display->height()-1, dma_display->color444(15, 0, 0));
    // delay(500);

    // // draw a blue circle
    // dma_display->drawCircle(10, 10, 10, dma_display->color444(0, 0, 15));
    // delay(500);

    // fill a violet circle
    // dma_display->drawPixelRGB888(32, 32, 255, 255, 255);
    // delay(500);

    // fill the screen with 'black'
    // dma_display->fillScreen(dma_display->color444(0, 0, 0));

    // drawText(0);
}
int R = 20;
long t = 0;
// uint8_t wheelval = 0;
void loop() {
    // animate by going through the colour wheel for the first two lines
    // drawText(wheelval);
    // wheelval +=1;
    // while (1)
    // t = micros();
    // dma_display->fillCircle(32, 32, 10, dma_display->color444(15, 15, 15));
    // Serial.println(micros() - t);
    for (int i = 0; i <= 128; i++) {
        t = micros();
        Serial.print("fillCircle: ");
        dma_display->fillCircle(32 + i, 32, 10, dma_display->color444(15, 15, 15));
        Serial.println(micros() - t);
        t = micros();
        Serial.print("delay: ");
        delay(10);
        Serial.println(micros() - t);
        t = micros();
        Serial.print("clearScreen: ");
        dma_display->clearScreen();
        Serial.println(micros() - t);
    }
    // for (int i = 0; i <= 128; i++) {
    //     dma_display->fillCircle(160 - i, 32, 10, dma_display->color444(15, 15, 15));
    //     delay(10);
    //     dma_display->clearScreen();
    // }
    // Serial.println(millis() - t);
    // for (int i = 0; i <= 360; i += 1) {
    //     dma_display->fillCircle(32 + (int)(R * sin(i * PI / 180)), 32 + (int)(R * cos(i * PI / 180)), 5, dma_display->color444(15, 15, 15));
    //     //     dma_display->drawPixelRGB888(32 + (int)(R * sin(i * PI / 180)), 32 + (int)(R * cos(i * PI / 180)), 255, 255, 255);
    //     delay(10);
    //     dma_display->clearScreen();

    //     //     dma_display->drawPixelRGB888(32 + (int)(R * sin(i * PI / 180)), 32 + (int)(R * cos(i * PI / 180)), 0, 0, 0);
    // }
    // Serial.println("OK");
    // for (int i = 44; i >= 20; i--) {
    //     dma_display->drawPixelRGB888(i, i, 255, 255, 255);
    //     delay(50);
    //     dma_display->drawPixelRGB888(i, i, 0, 0, 0);
    // }

    //   drawText(0);
    //   delay(2000);
    //   dma_display->clearScreen();
    //   dma_display->fillScreen(myBLACK);
    // delay(2000);
    // dma_display->fillScreen(myBLUE);
    // delay(1000);
    // dma_display->fillScreen(myRED);
    // delay(1000);
    // dma_display->fillScreen(myGREEN);
    //   delay(1000);
    //   dma_display->fillScreen(myWHITE);
    //   dma_display->clearScreen();
}


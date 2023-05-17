#include <Arduino.h>
#line 1 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
// #include <ESP32-VirtualMatrixPanel-I2S-DMA.h>

#define PANEL_POSITION 7

#define R1_PIN 4    // Red 1
#define G1_PIN 5    // Green 1
#define B1_PIN 6    // Blue 1
#define R2_PIN 7    // Red 2
#define G2_PIN 15   // Green 2
#define B2_PIN 16   // Blue 2
#define A_PIN 18    // Address 1
#define B_PIN 8     // Address 2
#define C_PIN 3     // Address 3
#define D_PIN 9     // Address 4
#define E_PIN 17    // Address 5
#define CLK_PIN 14  // Clock
#define LAT_PIN 21  // Latch
#define OE_PIN 47   // Output Enable

#define PANEL_RES_X 64  // Number of pixels wide of each INDIVIDUAL panel module.
#define PANEL_RES_Y 64  // Number of pixels tall of each INDIVIDUAL panel module.
#define PANEL_CHAIN 3   // Total number of panels chained one to another
// #define PANE_WIDTH PANEL_WIDTH *PANELS_NUMBER
// #define VIRTUAL_MATRIX_CHAIN_TYPE CHAIN_BOTTOM_LEFT_UP

#define PIXEL_COLOR_DEPTH_BITS 1

// MatrixPanel_I2S_DMA dma_display;
MatrixPanel_I2S_DMA *dma_display = nullptr;

#line 32 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
void setup();
#line 65 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
void loop();
#line 32 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
void setup() {
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

    // mxconfig.driver = HUB75_I2S_CFG::FM6124;

    // Display Setup
    dma_display = new MatrixPanel_I2S_DMA(mxconfig);
    dma_display->begin();
    dma_display->setBrightness8(100);  // 0-255
    dma_display->clearScreen();
}

int Pos[6];
void loop() {
    if (Serial.available() > 0) {
        dma_display->clearScreen();
        String msg = Serial.readStringUntil('\n');
        Serial.read();
        char msgChar[msg.length() + 1];
        msg.toCharArray(msgChar, msg.length() + 1);
        char *token = strtok(msgChar, " ");
        int i = 0;
        while (token != NULL) {
            Pos[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");
        }
        // Serial.flush();
        // Serial.printf("X: %d Y: %d\n", Pos[0], Pos[1]);
    }
    // dma_display->fillCircle(Pos[0], Pos[1], 10, dma_display->color444(15, 15, 15));
    // dma_display->clearScreen();
    dma_display->fillCircle(191 - Pos[1], 64 * (PANEL_POSITION + 1) - Pos[0] - 1, 10, dma_display->color444(15, 15, 15));
    dma_display->fillCircle(191 - Pos[3], 64 * (PANEL_POSITION + 1) - Pos[2] - 1, 2, dma_display->color444(15, 15, 15));
    dma_display->fillCircle(191 - Pos[5], 64 * (PANEL_POSITION + 1) - Pos[4] - 1, 2, dma_display->color444(15, 15, 15));
    // delay(10);
}


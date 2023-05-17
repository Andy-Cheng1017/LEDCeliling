# 1 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
# 2 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino" 2
// #include <ESP32-VirtualMatrixPanel-I2S-DMA.h>
# 24 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
// #define PANE_WIDTH PANEL_WIDTH *PANELS_NUMBER
// #define VIRTUAL_MATRIX_CHAIN_TYPE CHAIN_BOTTOM_LEFT_UP



// MatrixPanel_I2S_DMA dma_display;
MatrixPanel_I2S_DMA *dma_display = nullptr;

void setup() {
    HUB75_I2S_CFG::i2s_pins _pins = {
        4 /* Red 1*/,
        5 /* Green 1*/,
        6 /* Blue 1*/,
        7 /* Red 2*/,
        15 /* Green 2*/,
        16 /* Blue 2*/,
        18 /* Address 1*/,
        8 /* Address 2*/,
        3 /* Address 3*/,
        9 /* Address 4*/,
        17 /* Address 5*/,
        21 /* Latch*/,
        47 /* Output Enable*/,
        14 /* Clock*/};
    HUB75_I2S_CFG mxconfig(
        64 /* Number of pixels wide of each INDIVIDUAL panel module.*/, // module width
        64 /* Number of pixels tall of each INDIVIDUAL panel module.*/, // module height
        3 /* Total number of panels chained one to another*/, // Chain length
        _pins);
    Serial.begin(115200);

    // mxconfig.driver = HUB75_I2S_CFG::FM6124;

    // Display Setup
    dma_display = new MatrixPanel_I2S_DMA(mxconfig);
    dma_display->begin();
    dma_display->setBrightness8(100); // 0-255
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
        while (token != 
# 74 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino" 3 4
                       __null
# 74 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
                           ) {
            Pos[i] = atoi(token);
            i++;
            token = strtok(
# 77 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino" 3 4
                          __null
# 77 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
                              , " ");
        }
        // Serial.flush();
        // Serial.printf("X: %d Y: %d\n", Pos[0], Pos[1]);
    }
    // dma_display->fillCircle(Pos[0], Pos[1], 10, dma_display->color444(15, 15, 15));
    // dma_display->clearScreen();
    dma_display->fillCircle(191 - Pos[1], 64 * (7 + 1) - Pos[0] - 1, 10, dma_display->color444(15, 15, 15));
    dma_display->fillCircle(191 - Pos[3], 64 * (7 + 1) - Pos[2] - 1, 2, dma_display->color444(15, 15, 15));
    dma_display->fillCircle(191 - Pos[5], 64 * (7 + 1) - Pos[4] - 1, 2, dma_display->color444(15, 15, 15));
    // delay(10);
}

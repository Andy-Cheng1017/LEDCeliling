# 1 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"

# 3 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino" 2
# 4 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino" 2
# 5 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino" 2





Scheduler userScheduler; // to control your personal task
painlessMesh mesh;

// Define the pins used by the LED matrix
# 33 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
// #define VIRTUAL_MATRIX_CHAIN_TYPE CHAIN_BOTTOM_LEFT_UP



// MatrixPanel_I2S_DMA dma_display;
MatrixPanel_I2S_DMA *dma_display = nullptr;
int Pos[2];
// This is the color palette for the display
uint16_t myBLACK = dma_display->color565(0, 0, 0);
uint16_t myWHITE = dma_display->color565(255, 255, 255);
uint16_t myRED = dma_display->color565(255, 0, 0);
uint16_t myGREEN = dma_display->color565(0, 255, 0);
uint16_t myBLUE = dma_display->color565(0, 0, 255);
unsigned long lastTime = 0;
void receivedCallback(uint32_t from, String &msg) {
    Serial.println(millis() - lastTime);
    lastTime = millis();
    char msgChar[msg.length() + 1];
    msg.toCharArray(msgChar, msg.length() + 1);
    char *token = strtok(msgChar, ",");
    Pos[2];
    int i = 0;
    while (token != 
# 55 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino" 3 4
                   __null
# 55 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
                       ) {
        Pos[i] = atoi(token);
        i++;
        token = strtok(
# 58 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino" 3 4
                      __null
# 58 "d:\\work\\LEDCeliling\\LEDControl\\LEDControl.ino"
                          , ",");
    }
    Serial.printf("X: %d Y: %d\n", Pos[0], Pos[1]);
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
    Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

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
        14 /* Clock*/,
    };
    HUB75_I2S_CFG mxconfig(
        64 /* Number of pixels wide of each INDIVIDUAL panel module.*/, // module width
        64 /* Number of pixels tall of each INDIVIDUAL panel module.*/, // module height
        3 /* Total number of panels chained one to another*/, // Chain length
        _pins
        // HUB75_I2S_CFG::FM6124,
        // HUB75_I2S_CFG::HZ_20M
    );
    mesh.onNewConnection(&newConnectionCallback);
    mesh.onChangedConnections(&changedConnectionCallback);
    mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
    Serial.begin(115200);

    // mxconfig.driver = HUB75_I2S_CFG::FM6124;

    // Display Setup
    dma_display = new MatrixPanel_I2S_DMA(mxconfig);
    dma_display->begin();
    dma_display->setBrightness8(100); // 0-255
    dma_display->clearScreen();
    mesh.init("ChengMesh", "0928192448", &userScheduler, 555);
    mesh.onReceive(&receivedCallback);
}

// int R = 20;
long t = 0;
int i;
// uint8_t wheelval = 0;
void loop() {
    // dma_display->drawPixel(0, 0, dma_display->color444(15, 15, 15));
    dma_display->clearScreen();
    dma_display->fillCircle(191 - Pos[1], 64 * (0 + 1) - Pos[0] - 1, 10, dma_display->color444(15, 15, 15));
    // Serial.print("OK");
    mesh.update();
    // animate by going through the colour wheel for the first two lines
    // drawText(wheelval);
    // wheelval +=1;
    // while (1)
    // t = micros();
    // dma_display->fillCircle(32, 32, 10, dma_display->color444(15, 15, 15));
    // Serial.println(micros() - t);
    // for (int i = 0; i <= 128; i++) {                                                 // 迴圈 1~128
    //     t = micros();                                                                // 取得當前時間
    //     Serial.print("fillCircle: ");                                                // 顯示文字
    //     dma_display->fillCircle(32 + i, 32, 10, dma_display->color444(15, 15, 15));  // 畫圓
    //     Serial.println(micros() - t);                                                // 顯示時間
    //     t = micros();                                                                // 取得當前時間
    //     Serial.print("delay: ");                                                     // 顯示文字
    //     delay(10);                                                                   // 延遲10ms
    //     Serial.println(micros() - t);                                                // 顯示時間
    //     t = micros();                                                                // 取得當前時間
    //     Serial.print("clearScreen: ");                                               // 顯示文字
    //     dma_display->clearScreen();                                                  // 清除螢幕
    //     Serial.println(micros() - t);                                                // 顯示時間
    // }
    // if (millis() - t > 10) {
    //     t = millis();
    //     i++;
    //     dma_display->clearScreen();
    //     dma_display->fillCircle(160 - i, 32, 10, dma_display->color444(15, 15, 15));
    //     if (i >= 128) {
    //         i = 0;
    //     }
    // }
    // for (int i = 0; i <= 128; i++) {

    // delay(10);
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

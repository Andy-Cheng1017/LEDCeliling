#include <Arduino.h>
#line 1 "d:\\work\\LEDCeliling\\CamreaScript\\CameraScript.ino"
#include "esp_camera.h"
// #include "namedMesh.h"

#define Camera_Position
#include "camera_pins.h"

// #define MESH_NAME "Camera2"
// #define MESH_PREFIX "ChengMesh"
// #define MESH_PASSWORD "0928192448"
// #define MESH_PORT 555

// Scheduler userScheduler;
// namedMesh mesh;
// String nodeName = MESH_NAME;

#line 16 "d:\\work\\LEDCeliling\\CamreaScript\\CameraScript.ino"
void setup();
#line 97 "d:\\work\\LEDCeliling\\CamreaScript\\CameraScript.ino"
void loop();
#line 16 "d:\\work\\LEDCeliling\\CamreaScript\\CameraScript.ino"
void setup() {
    delay(1000);
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    Serial.println();

    // mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);
    // mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
    // mesh.setName(nodeName);
    // mesh.setContainsRoot(true);

    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.frame_size = FRAMESIZE_240X240;
    config.pixel_format = PIXFORMAT_GRAYSCALE;  // for streaming
    config.grab_mode = CAMERA_GRAB_LATEST;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    // config.jpeg_quality = 12;
    config.fb_count = 2;

    // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
    //  for larger pre-allocated frame buffer.
    if (config.pixel_format == PIXFORMAT_JPEG) {
        if (psramFound()) {
            config.jpeg_quality = 10;
            config.fb_count = 2;
            config.grab_mode = CAMERA_GRAB_LATEST;
        } else {
            // Limit the frame size when PSRAM is not available
            config.frame_size = FRAMESIZE_SVGA;
            config.fb_location = CAMERA_FB_IN_DRAM;
        }
    } else {
        // Best option for face detection/recognition
        config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
        config.fb_count = 2;
#endif
    }

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }

    sensor_t *s = esp_camera_sensor_get();
    // initial sensors are flipped vertically and colors are a bit saturated
    s->set_brightness(s, -2);  // up the brightness just a bit
    s->set_saturation(s, -2);  // lower the saturation
    s->set_gain_ctrl(s, 0);
    s->set_awb_gain(s, 0);
    // drop down frame size for higher initial frame rate
    // if (config.pixel_format == PIXFORMAT_JPEG) {
    //     s->set_framesize(s, FRAMESIZE_QVGA);
    // }
    Serial.println("Camera Ready!");
}

int ThreadValue = 250;
unsigned int LastTime = 0;

void loop() {
    if (millis() - LastTime > 20) {
        camera_fb_t *fb = esp_camera_fb_get();
        const char *data = (const char *)fb->buf;
        size_t size = fb->len;
        unsigned int XAccumulate = 0;
        unsigned int YAccumulate = 0;
        int XOffest = 0;
        int YOffest = 0;
        int Count = 0;
        for (int i = 0; i < size; i++) {
            if (data[i] > ThreadValue) {
                XAccumulate += int(i % 239);
                YAccumulate += int(i / 240);
                Count++;
            }
        }
        esp_camera_fb_return(fb);
        if (Count > 20 && Count < 1500) {
            XOffest = XAccumulate / Count - 120;
            YOffest = YAccumulate / Count - 120;
        }
        String msg = String(XOffest) + ' ' + String(YOffest);
        Serial.println(msg);
        // Serial.println(Count);
        // String to = "Root";
        // Serial.print(mesh.sendSingle(to, msg));
    }
    // mesh.update();
}


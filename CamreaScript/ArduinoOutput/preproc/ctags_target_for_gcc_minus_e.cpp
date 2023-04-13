# 1 "d:\\work\\LEDCeliling\\CamreaScript\\CameraScript.ino"
# 2 "d:\\work\\LEDCeliling\\CamreaScript\\CameraScript.ino" 2
# 3 "d:\\work\\LEDCeliling\\CamreaScript\\CameraScript.ino" 2


# 6 "d:\\work\\LEDCeliling\\CamreaScript\\CameraScript.ino" 2

// ===========================
// Enter your WiFi credentials
// ===========================
const char* ssid = "ChengComputer";
const char* password = "0928192448";

void startCameraServer();
void setupLedFlash(int pin);

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();


  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 9;
  config.pin_d1 = 11;
  config.pin_d2 = 12;
  config.pin_d3 = 10;
  config.pin_d4 = 3;
  config.pin_d5 = 18;
  config.pin_d6 = 17;
  config.pin_d7 = 15;
  config.pin_xclk = 16;
  config.pin_pclk = 8;
  config.pin_vsync = 6;
  config.pin_href = 7;
  config.pin_sscb_sda = 4;
  config.pin_sscb_scl = 5;
  config.pin_pwdn = 1;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.frame_size = FRAMESIZE_UXGA;
  config.pixel_format = PIXFORMAT_JPEG; // for streaming
  //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if(config.pixel_format == PIXFORMAT_JPEG){
    if(psramFound()){
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

    config.fb_count = 2;

  }






  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != 0 /*!< esp_err_t value indicating success (no error) */) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1); // flip it back
    s->set_brightness(s, 1); // up the brightness just a bit
    s->set_saturation(s, -2); // lower the saturation
  }
  // drop down frame size for higher initial frame rate
  if(config.pixel_format == PIXFORMAT_JPEG){
    s->set_framesize(s, FRAMESIZE_QVGA);
  }
# 103 "d:\\work\\LEDCeliling\\CamreaScript\\CameraScript.ino"
// Setup LED FLash if LED pin is defined in camera_pins.h




  WiFi.begin(ssid, password);
  WiFi.setSleep(false);
  Serial.println("Begin!!");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
}

void loop() {
  // Do nothing. Everything is done in another task by the web server
  delay(10000);
  Serial.println("OK");
}

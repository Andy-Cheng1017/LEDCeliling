# 1 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
# 2 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino" 2






Scheduler userScheduler; // to control your personal task
// painlessMesh mesh;
namedMesh mesh;

String nodeName = "Root";

unsigned int PuckXPosition = 4000;
unsigned int PuckYPosition = 0;

unsigned int Player1StickXPosition = 1000;
unsigned int Player1StickYPosition = 0;

unsigned int Player2StickXPosition = 7000;
unsigned int Player2StickYPosition = 0;

void ReciveCallback(String &from, String &msg) {
    char msgChar[msg.length() + 1];
    msg.toCharArray(msgChar, msg.length() + 1);
    char *token = strtok(msgChar, " ");
    int Pos[3];
    int i = 0;
    while (token != 
# 29 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino" 3 4
                   __null
# 29 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
                       ) {
        Pos[i] = atoi(token);
        i++;
        token = strtok(
# 32 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino" 3 4
                      __null
# 32 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
                          , " ");
    }
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
    Serial.begin(115200);

    // mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
    mesh.setDebugMsgTypes(
        ERROR | STARTUP | CONNECTION |
        DEBUG); // set before init() so that you can see startup messages
    mesh.setRoot(true);
    mesh.init("ChengMesh", "0928192448", &userScheduler, 555);
    mesh.setName(nodeName);
    mesh.onReceive(&ReciveCallback);
    mesh.onNewConnection(&newConnectionCallback);
    mesh.onChangedConnections(&changedConnectionCallback);
    mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
    mesh.setContainsRoot(true);
}

void loop() {
    if (Serial.available() > 0) {
        String msg = Serial.readStringUntil('\n');
        Serial.flush();
        char msgChar[msg.length() + 1];
        msg.toCharArray(msgChar, msg.length() + 1);
        char *token = strtok(msgChar, " ");
        int Pos[2];
        int i = 0;
        while (token != 
# 74 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino" 3 4
                       __null
# 74 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
                           ) {
            Pos[i] = atoi(token);
            i++;
            token = strtok(
# 77 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino" 3 4
                          __null
# 77 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
                              , " ");
        }
        // Serial.printf("startHere Message: %d, %d\n", Pos[0], Pos[1]);
        Pos[0] += 4000;
        Pos[1] += 1500;
        PuckXPosition = map(Pos[0], 0, 8000, 0, 511);
        PuckYPosition = map(Pos[1], 0, 3000, 0, 191);
        String Cmsg = String(PuckXPosition) + " " + String(PuckYPosition);
        if (!mesh.sendBroadcast(Cmsg)) {
            Serial.println("Broadcast failed");
        }
    }
    // char a[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    // Serial.print(a);
    // Serial.flush();
    mesh.update();
    // delay(10);
}

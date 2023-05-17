#include <Arduino.h>
#line 1 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
#include "namedMesh.h"

#define MESH_NAME "Root"
#define MESH_PREFIX "ChengMesh"
#define MESH_PASSWORD "0928192448"
#define MESH_PORT 555

Scheduler userScheduler;  // to control your personal task
// painlessMesh mesh;
namedMesh mesh;

String nodeName = MESH_NAME;

unsigned int PuckXPosition = 4000;
unsigned int PuckYPosition = 0;

unsigned int Player1StickXPosition = 1000;
unsigned int Player1StickYPosition = 0;

unsigned int Player2StickXPosition = 7000;
unsigned int Player2StickYPosition = 0;

#line 23 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
void ReciveCallback(String &from, String &msg);
#line 36 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
void newConnectionCallback(uint32_t nodeId);
#line 40 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
void changedConnectionCallback();
#line 44 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
void nodeTimeAdjustedCallback(int32_t offset);
#line 48 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
void setup();
#line 65 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
void loop();
#line 23 "d:\\work\\LEDCeliling\\Broadcast\\Broadcast.ino"
void ReciveCallback(String &from, String &msg) {
    char msgChar[msg.length() + 1];
    msg.toCharArray(msgChar, msg.length() + 1);
    char *token = strtok(msgChar, " ");
    int Pos[3];
    int i = 0;
    while (token != NULL) {
        Pos[i] = atoi(token);
        i++;
        token = strtok(NULL, " ");
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
        DEBUG);  // set before init() so that you can see startup messages
    mesh.setRoot(true);
    mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
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
        while (token != NULL) {
            Pos[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");
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


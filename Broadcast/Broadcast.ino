#include "painlessMesh.h"
#define MESH_PREFIX "ChengMesh"
#define MESH_PASSWORD "0928192448"
#define MESH_PORT 555

Scheduler userScheduler;  // to control your personal task
painlessMesh mesh;

// Needed for painless library
void receivedCallback(uint32_t from, String &msg) {
    Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
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
    mesh.setDebugMsgTypes(ERROR | STARTUP);  // set before init() so that you can see startup messages

    mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
    mesh.onReceive(&receivedCallback);
    mesh.onNewConnection(&newConnectionCallback);
    mesh.onChangedConnections(&changedConnectionCallback);
    mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
}

void loop() {
    if (Serial.available() > 0) {
        String msg = Serial.readStringUntil('\n');
        Serial.flush();
        char msgChar[msg.length() + 1];
        msg.toCharArray(msgChar, msg.length() + 1);
        char *token = strtok(msgChar, ",");
        int Pos[2];
        int i = 0;
        while (token != NULL) {
            Pos[i] = atoi(token);
            i++;
            token = strtok(NULL, ",");
        }
        // Serial.printf("startHere Message: %d, %d\n", Pos[0], Pos[1]);
        Pos[0] += 4000;
        Pos[1] += 1500;
        unsigned int XPosition = map(Pos[0], 0, 8000, 0, 511);
        unsigned int YPosition = map(Pos[1], 0, 3000, 0, 191);
        String Cmsg = String(XPosition) + "," + String(YPosition);
        mesh.sendBroadcast(Cmsg);
    }
    // char a[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    // Serial.print(a);
    // Serial.flush();
    mesh.update();
    // delay(10);
}

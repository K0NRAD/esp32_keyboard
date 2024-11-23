#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "BLE2902.h"
#include "BLEHIDDevice.h"
#include "HIDTypes.h"
#include "HIDKeyboardTypes.h"

// HID report descriptor für eine standard Tastatur
static const uint8_t hidReportDescriptor[] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0x01,                    //   REPORT_ID (1)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    
    0xc0                           // END_COLLECTION
};

BLEHIDDevice* hid;
BLECharacteristic* input;
BLECharacteristic* output;

bool connected = false;

class MyCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* server) {
        connected = true;
        Serial.println("Client verbunden!");
    }

    void onDisconnect(BLEServer* server) {
        connected = false;
        Serial.println("Client getrennt!");
        // Starte Advertising neu wenn getrennt
        BLEDevice::startAdvertising();
    }
};

void setup() {
    Serial.begin(115200);
    Serial.println("ESP32 BLE Keyboard startet...");

    // Initialisiere BLE
    BLEDevice::init("ESP32 Keyboard");
    BLEServer *server = BLEDevice::createServer();
    server->setCallbacks(new MyCallbacks());

    // Erstelle HID Device
    hid = new BLEHIDDevice(server);
    input = hid->inputReport(1);
    output = hid->outputReport(1);

    // Setze Manufacturer
    hid->manufacturer()->setValue("Espressif");
    
    // Setze HID Info
    hid->pnp(0x02, 0xe502, 0xa111, 0x0210);
    hid->hidInfo(0x00,0x01);

    // Setze HID Report Descriptor
    hid->reportMap((uint8_t*)hidReportDescriptor, sizeof(hidReportDescriptor));
    hid->startServices();

    // Start Advertising
    BLEAdvertising *advertising = server->getAdvertising();
    advertising->setAppearance(HID_KEYBOARD);
    advertising->addServiceUUID(hid->hidService()->getUUID());
    advertising->start();

    Serial.println("Warte auf Bluetooth-Verbindung...");
}

// Funktion zum Senden eines einzelnen Tastendrucks
void sendKey(uint8_t key) {
    if (!connected) return;

    uint8_t msg[] = {0x00, 0x00, key, 0x00, 0x00, 0x00, 0x00, 0x00};
    input->setValue(msg, sizeof(msg));
    input->notify();

    // Taste loslassen
    uint8_t msg_release[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    input->setValue(msg_release, sizeof(msg_release));
    input->notify();
    
    delay(50); // Kleine Verzögerung zwischen Tastendrücken
}

void loop() {
    if(connected) {
        // Beispiel: Sende periodisch den Buchstaben 'a' (Keycode 0x04)
        sendKey(0x04);
        delay(2000); // Warte 2 Sekunden zwischen den Tastendrücken
    }
    delay(50);
}

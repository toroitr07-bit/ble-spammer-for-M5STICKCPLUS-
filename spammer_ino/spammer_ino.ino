#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

BLEAdvertising* pAdvertising;
bool spamming = false;

void setup() {
  Serial.begin(115200);
  Serial.println("BLE Spammer READY");
  
  BLEDevice::init("GhostDevice");
  pAdvertising = BLEDevice::getAdvertising();
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == '1') {
      spamming = true;
      Serial.println("START SPAMMING");
    } else if (cmd == '0') {
      spamming = false;
      Serial.println("STOP SPAMMING");
    }
  }
  
  if (spamming) {
    String name = "Device_" + String(random(10000));
    
    BLEAdvertisementData advertisementData;
    advertisementData.setName(name.c_str());
    advertisementData.setFlags(0x06);
    
    pAdvertising->setAdvertisementData(advertisementData);
    pAdvertising->start();
    
    Serial.print("Spamming: ");
    Serial.println(name);
    
    delay(300);
    pAdvertising->stop();
    delay(200);
  }
  
  delay(10);
}
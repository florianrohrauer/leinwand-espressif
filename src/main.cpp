#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Effect.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic *pCharacteristic;
std::string effect = "pacifica";

class CharacteristicCallback : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pCharacteristic, esp_ble_gatts_cb_param_t* param) {
    std::string value = pCharacteristic->getValue();
    Serial.print("value received: ");
    Serial.println(value.c_str());

    effect = value;
  }
};

void setup() {
  Serial.begin(9600);

  BLEDevice::init("Leinwand");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristic->setCallbacks(new CharacteristicCallback());
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Effect::init();
}

void loop() {
  Effect::apply(effect);
}
#include <WifiEspNowBroadcast.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

void processRx(const uint8_t mac[6], const uint8_t* buf, size_t count, void* cbarg) {
  for (int i = 0; i < count; ++i) {
  }
//  digitalWrite(LED_PIN, ledState);
//  ledState = 1 - ledState;
}

void setup() {
//pinMode(LED_PIN, OUTPUT);
  WiFi.persistent(false);
  bool ok = WifiEspNowBroadcast.begin("ESPNOW", 3);
  if (!ok) {
    ESP.restart();
  }
  WifiEspNowBroadcast.onReceive(processRx, nullptr);
}

void sendMessage() {
  char msg[60];
  int len = snprintf(msg, sizeof(msg), "hello ESP-NOW from %s at %lu", WiFi.softAPmacAddress().c_str(), millis());
  WifiEspNowBroadcast.send(reinterpret_cast<const uint8_t*>(msg), len);
  const int MAX_PEERS = 20;
  WifiEspNowPeerInfo peers[MAX_PEERS];
  int nPeers = std::min(WifiEspNow.listPeers(peers, MAX_PEERS), MAX_PEERS);
  for (int i = 0; i < nPeers; ++i) {
  }
}

void loop() {
  sendMessage();
  WifiEspNowBroadcast.loop();
  delay(1000);
}

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiUdp.h>
#include <Keypad.h>

#define UDP_MAX_LEN 1024

const char* mqttServer = "dakotarowland.duckdns.org";
const int mqttPort = 1883;
String msg = ""; 

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // LCD object

int numCoins = 0;

char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[4] = {14, 27, 26, 25};
byte colPins[4] = {13, 21, 22, 23};

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

const char *ssid = "JackoAmo-2G";
const char *password = "Billiam1!";
const char *serverIP = "dakotarowland.duckdns.org";
const int serverPort = 8080;

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 is ready!");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);

  while (!mqttClient.connected()) {
    if (mqttClient.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
      mqttClient.subscribe("description");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying MQTT connection in 5 seconds...");
      delay(5000);
    }
  }

  Wire.begin(13, 14);
  //lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.print("starting game");
  udp.begin(serverPort); // Start listening on the specified port
}

void loop() {

  updateLCD();
  char keyPressed = myKeypad.getKey();
  
  if (keyPressed != NO_KEY) {
    keypadActions(keyPressed);
  }

  mqttClient.loop();
  
}

void sendMessage(const char *message) {
  udp.beginPacket(serverIP, serverPort);
  udp.print(message);
  udp.endPacket();
}
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);

  payload[length] = '\0'; // Terminate the string
  Serial.println((char*)payload);

  msg = "";
    for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
   // Check if the message is "Coin Room"
  if (msg.equals("Coin Room")) {
      numCoins++; // Increment the number of coins
  }
  Serial.println(msg);
  updateLCD();
}

void updateLCD(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Coins: ");
  lcd.print(numCoins);
  lcd.setCursor(0, 1);
  lcd.print("message");
}
void sendMovement(const char *movement) {
  sendMessage(movement);
}

void keypadActions(char keyPressed) {
  switch (keyPressed) {
    case '2':
      sendMovement("north");
      Serial.println("sent north");
      break;
    case '6':
      sendMovement("east");
      Serial.println("sent east");
      break;
    case '8':
      sendMovement("south");
      Serial.println("sent south");
      break;
    case '4':
      sendMovement("west");
      Serial.println("sent west");
      break;
    default:
      Serial.println("Invalid Key");
      break;
  }
}

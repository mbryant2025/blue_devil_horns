#include <WiFiNINA.h>
#include <SPI.h>

char ssid[] = "NEVER GONNA GIVE YOU UP 2.4";
char pass[] = "60029454";
int status = WL_IDLE_STATUS;
WiFiServer server(80); // Create a server on port 80
char status = "0";

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.println("You're connected to the network");
  Serial.println("---------------------------------------");

  digitalWrite(LED_BUILTIN, LOW);

  server.begin(); // Start the server
}

void loop() {
  WiFiClient client = server.available(); // Check if a client has connected

  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '4') {
          digitalWrite(2, HIGH);
          delay(1000);
          digitalWrite(3, LOW);
          delay(1000);
          status = '4';
        } else if (c == '3') {
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          status = '3';
        } else if (c == '2') {
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          status = '2';
        } else if (c == '1') {
          digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
          status = '1';
        } else if (c == '0') {
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          status = '0';
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
  if (status == '4' ){
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(3, LOW);
    delay(1000);
  }
}
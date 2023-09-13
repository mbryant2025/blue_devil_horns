#include <WiFiNINA.h>
#include <SPI.h>

char ssid[] = "NEVER GONNA GIVE YOU UP 2.4";
char pass[] = "60029454";
int status = WL_IDLE_STATUS;
WiFiServer server(80); // Create a server on port 80

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

        if (c == '1') {
          digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
        } else if (c == '0') {
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
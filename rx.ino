#include <WiFiNINA.h>
#include <SPI.h>

char ssid[] = "NEVER GONNA GIVE YOU UP 2.4";
char pass[] = "60029454";
int status = WL_IDLE_STATUS;
WiFiServer server(80); // Create a server on port 80

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(LED_BUILTIN, OUTPUT);

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.println("You're connected to the network");
  Serial.println("---------------------------------------");

  server.begin(); // Start the server
}

void loop() {
  WiFiClient client = server.available(); // Check if a client has connected

  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); // Read data from the client
        Serial.write(c); // Send data to the serial monitor

        // You can process the received data here
        // For example, you can toggle the LED based on received data
        if (c == '1') {
          digitalWrite(LED_BUILTIN, HIGH);
        } else if (c == '0') {
          digitalWrite(LED_BUILTIN, LOW);
        }
      }
    }
    client.stop(); // Close the connection
    Serial.println("Client disconnected");
  }
}

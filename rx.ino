#include <WiFiNINA.h>
#include <SPI.h>

char ssid[] = "NEVER GONNA GIVE YOU UP 2.4";
char pass[] = "60029454";
int status = WL_IDLE_STATUS;
WiFiServer server(80); // Create a server on port 80
int toggle_blink = 0;
double last_blink_check = millis();
bool led1 = false;

void setup() {

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  
  digitalWrite(LED_BUILTIN, LOW);

  server.begin(); // Start the server
}

void loop() {
  WiFiClient client = server.available(); // Check if a client has connected

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        toggle_blink = 0;

        if (c == '4') {
          toggle_blink = 1;
        } else if (c == '3') {
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
        } else if (c == '2') {
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
        } else if (c == '1') {
          digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
        } else if (c == '0') {
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
        }
      }

    }
    client.stop();
  }
  //blink
  if (toggle_blink) {

    // Once a second
    if (millis() - last_blink_check > 1000) {

      last_blink_check = millis();

      if (led1) {
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
      } else {
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
      }

      led1 = !led1;

    }


  }
}
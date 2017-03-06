
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "Your Ssid";
const char* password = "Your Password";
const char* mqtt_server = "Your server Ip address";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
pinMode(16, OUTPUT);
digitalWrite(16,LOW);// Initialize the BUILTIN_LED pin as an output
Serial.begin(9600);
setup_wifi();
client.setServer(mqtt_server, 1883);
client.setCallback(callback);
client.publish("outTopic", "hello world");
}

void setup_wifi() {

delay(10);
// We start by connecting to a WiFi network
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}

Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
Serial.print("Message arrived [");
Serial.print(topic);
Serial.print("] ");
for (int i = 0; i < length; i++) {
Serial.print((char)payload[i]);
}
Serial.println();

// Switch on the LED if an 1 was received as first character
if ((char)payload[0] == '1') {
digitalWrite(16, HIGH); // Turn the LED on (Note that LOW is the voltage level
// but actually the LED is on; this is because
Serial.print("its on ");
//delay(30000);
//delay(30000);
delay(30000);// it is acive low on the ESP-01)
digitalWrite(16, LOW);
Serial.println("its off");
} else {
digitalWrite(16, LOW); // Turn the LED off by making the voltage HIGH
Serial.println("its off");
}

}

void reconnect() {
// Loop until we're reconnected
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");
// Attempt to connect
if (client.connect("ESP8266Client")) {
Serial.println("connected");
// Once connected, publish an announcement...
client.publish("outTopic", "hello world");
// ... and resubscribe
client.subscribe("plants");
} else {
Serial.print("failed, rc=");
Serial.print(client.state());
Serial.println(" try again in 5 seconds");
// Wait 5 seconds before retrying
delay(5000);
}
}
}
void loop() {

if (!client.connected()) {
reconnect();
}
client.loop();

//long now = millis();
//if (now - lastMsg > 2000) {
//lastMsg = now;
//++value;
//snprintf (msg, 75, "hello world #%ld", value);
//Serial.print("Publish message: ");
//Serial.println(msg);
//client.publish("outTopic", msg);
//}
}

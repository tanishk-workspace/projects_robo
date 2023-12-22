#include <ESP8266WiFi.h>
#include <Servo.h>
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;

const int unt=10;
int pos0=90;
int pos1=90;
int pos2=90;
int pos3=0;

#define servo0_pin 1
#define servo1_pin 2
#define servo2_pin 3
#define servo3_pin 4


const char* ssid = "Your SSID";
const char* password = "Your Wifi Password";  

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  servo0.attach(servo0_pin);
  servo1.attach(servo1_pin);
  servo2.attach(servo2_pin);
  servo3.attach(servo3_pin);
  // Connect to WiFi network

  servo0.write(pos0);
  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);

  Serial.println();
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
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address on serial monitor
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");    //URL IP to be typed in mobile/desktop browser
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

 int value = 0;
 // Match the request

if (request.indexOf("/Req=1") != -1)  {
  if(pos0<=180){
  pos0+=unt;
  }
  servo0.write(pos0);
}
if (request.indexOf("/Req=2") != -1)  {
  if(pos0>=0){
  pos0-=unt;
  servo0.write(pos0);
  }
}


if (request.indexOf("/Req=3") != -1)  {
  if(pos1<=180){
  pos1+=unt;
  servo1.write(pos1);
  }
}
if (request.indexOf("/Req=4") != -1)  {
  if(pos1>=0){
  pos1-=unt;
  servo1.write(pos1);
  }
}


if (request.indexOf("/Req=5") != -1)  {
  if(pos2<=180){
  pos2+=unt;
  servo2.write(pos2);
  }
}
if (request.indexOf("/Req=6") != -1)  {
  if(pos2>=0){
  pos2-=unt;
  servo2.write(pos2);
  }
}

if (request.indexOf("/Req=7") != -1)  {
  if(pos3<180){
  pos3=0;
  servo3.write(pos3);
  }
}
if (request.indexOf("/Req=8") != -1)  {
  if(pos3>0){
  pos3=180;
  servo3.write(pos3);
  }
}


  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE html>");
client.println("<html lang='en'>");
client.println("<head>");
    client.println("<meta charset='utf-8' />");
    client.println("<title></title>");
client.println("</head>");
client.println("<body style="">");
    client.println("<h1>");
        client.println("web page");
    client.println("</h1>");
    client.println("<div>");
        client.println("<a href=\"/Req=3\"\"> <button> left clockwise</button></a>");
       client.println("<a href=\"/Req=4\"\"> <button> left anticlockwiaw </button></a>");
    client.println("</div>");
    client.println("<div>");
        client.println("<a href=\"/Req=5\"\"> <button> right clockwise</button></a>");
       client.println("<a href=\"/Req=6\"\"> <button> right anticlockwise</button></a>");
    client.println("</div>");
    client.println("<div>");
    client.println("<a href=\"/Req=1\"\"> <button> motar 1 right</button></a>");
    client.println("<a href=\"/Req=2\"\"><button> motar 1 left</button>");   
    client.println("</div>");
    client.println("</div>");
    client.println("<div>");
    client.println("<a href=\"/Req=7\"\"> <button> claw grab</button></a>");
        client.println("<a href=\"/Req=8\"\"> <button>claw drop</button></a>");
    client.println("</div>");
client.println("</body>");
client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}

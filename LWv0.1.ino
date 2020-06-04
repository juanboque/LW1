/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/home-automation-using-esp8266/
*********/

// Including the ESP8266 WiFi library
#include <ESP8266WiFi.h>

// Replace with your network details
const char* ssid = "www.XKEMATIC.com";
const char* password = "info@XKEMATIC.com";

// Web Server on port 8888
WiFiServer server(8888);

// variables
String header;
String gpio5_state = "Off"; //D1
String gpio4_state = "Off"; //D2
String gpio16_state = "Off"; //D0
String gpio0_state = "Off"; //D3
String gpio2_state = "Off"; //D4
String gpio15_state = "Off"; //D8
String gpio14_D5_RED_state = "Off";
String gpio12_D6_GREEN_state = "Off";
String gpio13_D7_BLUE_state = "Off";
String LAMP_state = "Off";

int gpio5_pin = 5;
int gpio4_pin = 4;
int gpio16_pin = 16;
int gpio0_pin = 0; //D3
int gpio2_pin = 2; //D4
int gpio15_pin = 15; //D8
int gpio14_D5_RED_pin = 14;     //pwm to control red led
int gpio12_D6_GREEN_pin = 12;   //pwm to control green led
int gpio13_D7_BLUE_pin = 13;    //pwm to control blue led

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// only runs once
void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(115200);
  delay(10);

  // preparing GPIOs
  pinMode(gpio5_pin, OUTPUT);
  digitalWrite(gpio5_pin, LOW);
  pinMode(gpio4_pin, OUTPUT);
  digitalWrite(gpio4_pin, LOW);
  pinMode(gpio14_D5_RED_pin, OUTPUT);
  digitalWrite(gpio14_D5_RED_pin, LOW);
  pinMode(gpio12_D6_GREEN_pin, OUTPUT);
  digitalWrite(gpio12_D6_GREEN_pin, LOW);
  pinMode(gpio13_D7_BLUE_pin, OUTPUT);
  digitalWrite(gpio13_D7_BLUE_pin, LOW);
  pinMode(gpio16_pin, OUTPUT);
  digitalWrite(gpio16_pin, LOW);
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, LOW);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
  pinMode(gpio15_pin, OUTPUT);
  digitalWrite(gpio15_pin, LOW);

  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Starting the web server
  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  delay(5000);

  // Printing the ESP IP address
  Serial.print("Go to: http://");
  Serial.print(IP);//WiFi.localIP());
  Serial.println(":8888");
}

// runs over and over again
void loop() {
  // Listenning for new clients
  WiFiClient client = server.available();

  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New client");
    // boolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
        if (client.available()) {
          char c = client.read();
          header += c;

          if (c == '\n' && blank_line) {

            // checking if header is valid
            // dXNlcjpwYXNz = 'user:pass' (user:pass) base64 encode

            Serial.print(header);

            // Finding the right credential string
            if(header.indexOf("SnVhbkFsYmVydG86TWFyaUNhcm1lbg==") >= 0) {
              //successful login
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("Connection: close");
              client.println();
              // turns the GPIOs on and off
              if(header.indexOf("GET / HTTP/1.1") >= 0) {
                Serial.println("Main Web Page");
              }
              else if(header.indexOf("GET /gpio5on HTTP/1.1") >= 0){
                Serial.println("GPIO 5 On");
                gpio5_state = "On";
                digitalWrite(gpio5_pin, HIGH);
              }
              else if(header.indexOf("GET /gpio5off HTTP/1.1") >= 0){
                Serial.println("GPIO 5 Off");
                gpio5_state = "Off";
                digitalWrite(gpio5_pin, LOW);
              }
              else if(header.indexOf("GET /gpio4on HTTP/1.1") >= 0){
                Serial.println("GPIO 4 On");
                gpio4_state = "On";
                digitalWrite(gpio4_pin, HIGH);
              }
              else if(header.indexOf("GET /gpio4off HTTP/1.1") >= 0){
                Serial.println("GPIO 4 Off");
                gpio4_state = "Off";
                digitalWrite(gpio4_pin, LOW);
              }
              else if(header.indexOf("GET /gpio14on HTTP/1.1") >= 0){
                Serial.println("GPIO 14 On");
                gpio14_D5_RED_state = "On";
                digitalWrite(gpio14_D5_RED_pin, HIGH);
              }
              else if(header.indexOf("GET /gpio14off HTTP/1.1") >= 0){
                Serial.println("GPIO 14 Off");
                gpio14_D5_RED_state = "Off";
                digitalWrite(gpio14_D5_RED_pin, LOW);
              }
              else if(header.indexOf("GET /gpio12on HTTP/1.1") >= 0){
                Serial.println("GPIO 12 On");
                gpio12_D6_GREEN_state = "On";
                digitalWrite(gpio12_D6_GREEN_pin, HIGH);
              }
              else if(header.indexOf("GET /gpio12off HTTP/1.1") >= 0){
                Serial.println("GPIO 12 Off");
                gpio12_D6_GREEN_state = "Off";
                digitalWrite(gpio12_D6_GREEN_pin, LOW);
              }
              else if(header.indexOf("GET /gpio13on HTTP/1.1") >= 0){
                Serial.println("GPIO 13 On");
                gpio13_D7_BLUE_state = "On";
                digitalWrite(gpio13_D7_BLUE_pin, HIGH);
              }
              else if(header.indexOf("GET /gpio13off HTTP/1.1") >= 0){
                Serial.println("GPIO 13 Off");
                gpio13_D7_BLUE_state = "Off";
                digitalWrite(gpio13_D7_BLUE_pin, LOW);
              }
              else if(header.indexOf("GET /gpio16on HTTP/1.1") >= 0){
                Serial.println("GPIO 16 On");
                gpio16_state = "On";
                digitalWrite(gpio16_pin, HIGH);
              }    
              else if(header.indexOf("GET /gpio16off HTTP/1.1") >= 0){
                Serial.println("GPIO 16 Off");
                gpio16_state = "Off";
                digitalWrite(gpio16_pin, LOW);
              }
              else if(header.indexOf("GET /gpio0on HTTP/1.1") >= 0){
                Serial.println("GPIO 0 On");
                gpio0_state = "On";
                digitalWrite(gpio0_pin, HIGH);
              }    
              else if(header.indexOf("GET /gpio0off HTTP/1.1") >= 0){
                Serial.println("GPIO 0 Off");
                gpio0_state = "Off";
                digitalWrite(gpio0_pin, LOW);
              }
              else if(header.indexOf("GET /gpio2on HTTP/1.1") >= 0){
                Serial.println("GPIO 2 On");
                gpio2_state = "On";
                digitalWrite(gpio2_pin, HIGH);
              }    
              else if(header.indexOf("GET /gpio2off HTTP/1.1") >= 0){
                Serial.println("GPIO 2 Off");
                gpio2_state = "Off";
                digitalWrite(gpio2_pin, LOW);
              }
              else if(header.indexOf("GET /gpio15on HTTP/1.1") >= 0){
                Serial.println("GPIO 15 On");
                gpio15_state = "On";
                digitalWrite(gpio15_pin, HIGH);
              }    
              else if(header.indexOf("GET /gpio15off HTTP/1.1") >= 0){
                Serial.println("GPIO 15 Off");
                gpio15_state = "Off";
                digitalWrite(gpio15_pin, LOW);
              }
              else if(header.indexOf("GET /LAMPon HTTP/1.1") >= 0){
                Serial.println("LAMPARA On");
                LAMP_state = "On";
                digitalWrite(gpio5_pin, HIGH);
                delay(75);
                digitalWrite(gpio4_pin, HIGH);
                delay(75);
                digitalWrite(gpio16_pin, HIGH);
                delay(75);
                digitalWrite(gpio0_pin, HIGH);
                delay(75);
                digitalWrite(gpio2_pin, HIGH);
                delay(75);
                digitalWrite(gpio15_pin, HIGH);
                delay(75);
                analogWrite(gpio14_D5_RED_pin, 255);
                delay(75);
                analogWrite(gpio12_D6_GREEN_pin, 255);
                delay(75);
                analogWrite(gpio13_D7_BLUE_pin, 255);
              }    
              else if(header.indexOf("GET /LAMPoff HTTP/1.1") >= 0){
                Serial.println("LAMPARA Off");
                LAMP_state = "Off";
                digitalWrite(gpio5_pin, LOW);
                digitalWrite(gpio4_pin, LOW);
                analogWrite(gpio14_D5_RED_pin, 0);
                analogWrite(gpio12_D6_GREEN_pin, 0);
                analogWrite(gpio13_D7_BLUE_pin, 0);
                digitalWrite(gpio16_pin, LOW);
                digitalWrite(gpio0_pin, LOW);
                digitalWrite(gpio2_pin, LOW);
                digitalWrite(gpio15_pin, LOW);
              }

              // your web page
              client.println("<!DOCTYPE HTML>");
              client.println("<html>");
              client.println("<head>");
              client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
              client.println("<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">");
              client.println("</head><div class=\"container\">");
              client.println("<h1>Web Server</h1>");
              client.println("<h2>FOCO 1 - Estado: " + gpio5_state);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio5on\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio5off\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
              client.println("</div>");
              client.println("<h2>LAMPARA - Estado: " + LAMP_state);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/LAMPon\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/LAMPoff\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
              client.println("</div>");
              client.println("<h2>FOCO 6 - Estado: " + gpio0_state);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio15on\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio15off\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
              client.println("</div>");
              client.println("<h2>FOCO 5 - Estado: " + gpio0_state);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio2on\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio2off\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
              client.println("</div>");
              client.println("<h2>FOCO 4 - Estado: " + gpio0_state);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio0on\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio0off\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
              client.println("</div>");
              client.println("<h2>FOCO 3 - Estado: " + gpio16_state);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio16on\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio16off\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
              client.println("</div>");
              client.println("<h2>LED ROJO - Estado: " + gpio14_D5_RED_state);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio14on\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio14off\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
              client.println("</div>");
              client.println("<h2>LED VERDE - Estado: " + gpio12_D6_GREEN_state);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio12on\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio12off\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
              client.println("</div>");
              client.println("<h2>LED AZUL - Estado: " + gpio13_D7_BLUE_state);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio13on\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio13off\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
              client.println("</div>");
              client.println("<h2>FOCO 2 - Estado: " + gpio4_state);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio4on\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio4off\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
              client.println("</div></div></html>");
            }
          // wrong user or passm, so http request fails...
          else {
            client.println("HTTP/1.1 401 Unauthorized");
            client.println("WWW-Authenticate: Basic realm=\"Secure\"");
            client.println("Content-Type: text/html");
            client.println();
            client.println("<html>Authentication failed</html>");
          }
          header = "";
          break;
          }
          if (c == '\n') {
            // when starts reading a new line
            blank_line = true;
          }
          else if (c != '\r') {
            // when finds a character on the current line
            blank_line = false;
          }
      }
    }
    // closing the client connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}


/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/home-automation-using-esp8266/
*********/

#include <Adafruit_NeoPixel.h>
// Including the ESP8266 WiFi library
#include <ESP8266WiFi.h>

#define MAXLED 50
//#define PIN 15
#define DELAY 5

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
String gpio12_D6_GREEN_state = "Off";
String LAMP_state = "Off";
String sPIN = "OFF";
String sLedColores = "off";

int gpio5_pin = 5;                //FUNICIONA PARA LAMPARA FOCO 1 D1 GPIO 5
int gpio4_pin = 4;                //FUNICIONA PARA LAMPARA FOCO 2 D2 GPIO 4
int gpio16_pin = 16;              //FUNICIONA PARA LAMPARA FOCO 3 D0 GPIO 16
int gpio0_pin = 0; //D3           //FUNICIONA PARA LAMPARA FOCO 4 D3 GPIO 0
int gpio2_pin = 2; //D4           //FUNICIONA PARA LAMPARA FOCO 5 D4 GPIO 2
int gpio12_D6_GREEN_pin = 12;   //FUNICIONA PARA LAMPARA FOCO 6 D6 GPIO 12
int gpio15_LED = 14;            //FUNCIONA PARA LED??


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(MAXLED, gpio15_LED, NEO_GRB + NEO_KHZ800);
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
  digitalWrite(gpio5_pin, HIGH);
  pinMode(gpio4_pin, OUTPUT);
  digitalWrite(gpio4_pin, HIGH);
  pinMode(gpio16_pin, OUTPUT);
  digitalWrite(gpio16_pin, HIGH);
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, HIGH);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, HIGH);
  pinMode(gpio12_D6_GREEN_pin, OUTPUT);
  digitalWrite(gpio12_D6_GREEN_pin, HIGH);
  pinMode(gpio15_LED, OUTPUT);
  SetLED(MAXLED,255,255,255,DELAY);

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

  pixels.begin(); // This initializes the NeoPixel library.
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
              }//gpio12_D6_GREEN_state = "Off"
              else if(header.indexOf("GET /gpio12_D6_GREEN_state_on HTTP/1.1") >= 0){
                //Serial.println("GPIO 2 On");
                gpio12_D6_GREEN_state = "On";
                digitalWrite(gpio12_D6_GREEN_pin, HIGH);
              }    
              else if(header.indexOf("GET /gpio12_D6_GREEN_state_off HTTP/1.1") >= 0){
                //Serial.println("GPIO 2 Off");
                gpio12_D6_GREEN_state = "Off";
                digitalWrite(gpio12_D6_GREEN_pin, LOW);
              }
              else if(header.indexOf("GET /LAMPon HTTP/1.1") >= 0){
                Serial.println("LAMPARA On");
                LAMP_state = "On";
                digitalWrite(gpio5_pin, HIGH);
                digitalWrite(gpio4_pin, HIGH);
                digitalWrite(gpio16_pin, HIGH);
                digitalWrite(gpio0_pin, HIGH);
                digitalWrite(gpio2_pin, HIGH);
                digitalWrite(gpio12_D6_GREEN_pin, HIGH);
                SetLED(MAXLED,255,255,255,DELAY);
              }    
              else if(header.indexOf("GET /LAMPoff HTTP/1.1") >= 0){
                Serial.println("LAMPARA Off");
                LAMP_state = "Off";
                digitalWrite(gpio5_pin, LOW);
                digitalWrite(gpio4_pin, LOW);
                digitalWrite(gpio16_pin, LOW);
                digitalWrite(gpio0_pin, LOW);
                digitalWrite(gpio2_pin, LOW);
                digitalWrite(gpio12_D6_GREEN_pin, LOW);
                SetLED(MAXLED,0,0,0,DELAY);
              }
              else if (header.indexOf("GET /LEDoff HTTP/1.1") >= 0)
              {
                SetLED(MAXLED,0,0,0,DELAY);
                sPIN = "Off";
              }
              else if (header.indexOf("GET /LEDon HTTP/1.1") >= 0)
              {
                SetLED(MAXLED,255,255,255,DELAY);
                sPIN = "On";
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
              client.println("<h2>FOCO 6 - Estado: " + gpio12_D6_GREEN_state);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio12_D6_GREEN_state_on\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio12_D6_GREEN_state_off\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
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
              client.println("<h2>FOCO 2 - Estado: " + gpio4_state);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio4on\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/gpio4off\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
              client.println("</div></div></html>");
              client.println("<h2>LED - Estado: " + sPIN);
              client.println("<div class=\"row\">");
              client.println("<div class=\"col-md-2\"><a href=\"/LEDon\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              client.println("<div class=\"col-md-2\"><a href=\"/LEDoff\" class=\"btn btn-block btn-lg btn-danger\" role=\"button\">OFF</a></div>");
              client.println("</div></div></html>");
              /************************************************************************************************************************************************************************/
              /************************************************************************************************************************************************************************/
              /************************************************************************************************************************************************************************/
              /************************************************************************************************************************************************************************/
              /************************************************************************************************************************************************************************/
              /************************************************************************************************************************************************************************/
              //client.println("<div class=\"col-md-2\"><a href=\"/LEDon\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ON</a></div>");
              //client.println("<form action=\"/LEDonRojo\"><input type=\"text\" name=\"scale\"/><input type=\"text\" name=\"color\"/><input type=\"submit\" value=\"Aplicar\"/></form>");
              /************************************************************************************************************************************************************************/
              /************************************************************************************************************************************************************************/
              /************************************************************************************************************************************************************************/
              /************************************************************************************************************************************************************************/
              /************************************************************************************************************************************************************************/
              client.println("<h2>LED Colores - Estado: " + sLedColores);  
              client.println("<div class=\"col-md-2\"><a href=\"/LED_R_V_A\" class=\"btn btn-block btn-lg btn-success\" role=\"button\">ROJO, VERDE y AZUL</a></div>");
              client.println("<form action=\"/LEDvalores\"><input type=\"text\" name=\"rojo\"/><input type=\"text\" name=\"verde\"/><input type=\"text\" name=\"azul\"/><input type=\"submit\" value=\"Aplicar\"/></form>");
              /************************************************************************************************************************************************************************/
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


void SetLED(int iNumLED,int iR, int iB,int iG, int iDelay)
{
  int led;
  for(led=0; led <= MAXLED; led++)
  {
//    setColor(led,iR,iB,iG,iDelay);
    pixels.setPixelColor(led, pixels.Color(iR, iB, iG)); 
  }
  pixels.show();
}

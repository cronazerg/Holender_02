#include <WiFiClient.h>
#include "ESP32WebServer.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#define DIODA 33

const char *ssid = "";
const char *password = "";
ESP32WebServer server(80);
bool DIODAstatus = LOW;
String tekst;
String input_password;
const String good = "good";
const String bad = "bad";
const String noinfo = "noinfo";
const String password_1 = "6901";

String SendHTML()
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 10px 10px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button:active {background-color: #2c3e50;}\n";
  ptr += ".center {text-align: center; color: #ff0000; font-size: 26px; font-weight: bold; margin-bottom: 50px;}\n";
  ptr += ".reset {background-color: #FF0000; margin: auto; color: #ffffff; margin-top: 20px;}\n";
  ptr += ".container {margin: auto; width: 520px; border: 3px solid green; padding: 10px; display: flex; justify-content: center; align-items: center; flex-wrap: wrap;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP32 Zamek Szyfrowy</h1>\n";

  ptr += "<div class=\"container\">\n";
    ptr += "<a class=\"button\" href=\"/key1\">1</a>\n";
    ptr += "<a class=\"button\" href=\"/key2\">2</a>\n";
    ptr += "<a class=\"button\" href=\"/key3\">3</a>\n";
    ptr += "<a class=\"button\" href=\"/key4\">4</a>\n";
    ptr += "<a class=\"button\" href=\"/key5\">5</a>\n";
    ptr += "<a class=\"button\" href=\"/key6\">6</a>\n";
    ptr += "<a class=\"button\" href=\"/key7\">7</a>\n";
    ptr += "<a class=\"button\" href=\"/key8\">8</a>\n";
    ptr += "<a class=\"button\" href=\"/key9\">9</a>\n";
    ptr += "<a class=\"button\" href=\"/key0\">0</a>\n";
  ptr += "</div>\n";

  ptr += "<a class=\"button reset\" href=\"/reset\">RESET</a>\n";
  
  if (tekst == good)
    ptr += "<p class=\"center\"> Nieporpawnie wpisany pin</p>\n";
  else if (tekst == bad)
    ptr += "<p class=\"center\"> Poprawnie wpisany pin</p>\n";
  else if (tekst == noinfo)
    ptr += "<p class=\"center\"></p>\n";

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

void handleRoot()
{
  server.send(200, "text/html", SendHTML());
}

void handleNotFound()
{
  String message = "Brak pliku\n\n";
  server.send(404, "text/plain", message);
}

void hehe() {
  if (input_password == password_1) {
    DIODAstatus = HIGH;
    digitalWrite(DIODA, LOW);
    input_password = "";
    tekst = good;
    Serial.println(tekst);
  } else if (input_password.length() >= 4) {
    DIODAstatus = LOW;
    digitalWrite(DIODA, HIGH);
    input_password = "";
    tekst = bad;
    Serial.println(tekst);
  }
}

void reset() {
  input_password = "";
  digitalWrite(DIODA, HIGH);
  server.send(200, "text/html", SendHTML());
  tekst = noinfo;
  Serial.println(tekst);
}

void handle_key1()
{
  input_password += 1;
  server.send(200, "text/html", SendHTML());
  hehe();
}

void handle_key2()
{
  input_password += 2;
  server.send(200, "text/html", SendHTML());
  hehe();
}

void handle_key3()
{
  input_password += 3;
  server.send(200, "text/html", SendHTML());
  hehe();
}

void handle_key4()
{
  input_password += 4;
  server.send(200, "text/html", SendHTML());
  hehe();
}

void handle_key5()
{
  input_password += 5;
  server.send(200, "text/html", SendHTML());
  hehe();
}

void handle_key6()
{
  input_password += 6;
  server.send(200, "text/html", SendHTML());
  hehe();
}

void handle_key7()
{
  input_password += 7;
  server.send(200, "text/html", SendHTML());
  hehe();
}

void handle_key8()
{
  input_password += 8;
  server.send(200, "text/html", SendHTML());
  hehe();
}

void handle_key9()
{
  input_password += 9;
  server.send(200, "text/html", SendHTML());
  hehe();
}

void handle_key0()
{
  input_password += 0;
  server.send(200, "text/html", SendHTML());
  hehe();
}


void setup(void)
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Połączono do ");
  Serial.println(ssid);
  Serial.print("Adres IP: ");
  Serial.println(WiFi.localIP());

  digitalWrite(DIODA, HIGH);

  if (MDNS.begin("esp32"))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.on("/key1", handle_key1);
  server.on("/key2", handle_key2);
  server.on("/key3", handle_key3);
  server.on("/key4", handle_key4);
  server.on("/key5", handle_key5);
  server.on("/key6", handle_key6);
  server.on("/key7", handle_key7);
  server.on("/key8", handle_key8);
  server.on("/key9", handle_key9);
  server.on("/key0", handle_key0);

  server.on("/reset", reset);

  server.begin();
  Serial.println("Start serwera HTTP");
  pinMode(DIODA, OUTPUT);
}

void loop(void)
{
  server.handleClient();
}

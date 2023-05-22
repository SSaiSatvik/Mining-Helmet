#include <WiFi.h>
#include "HTTPClient.h"
#include "time.h"
#include <ArduinoJson.h>

int buzzer=33;

WiFiClient WIFI_CLIENT;

char ssid[] = "Nothing" ;
char password[] = "nothing0";


String cse_ip = "192.168.32.2"; // YOUR IP from ipconfig/ifconfig
String cse_port = "8080";
String server = "http://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";


String ae = "Project";
String cnt1 = "Data_crash";
String cnt2 = "Data_temperature";
String cnt3 = "Data_humidity";
String cnt4 = "Data_pressure";

float getdatapressure(){
  StaticJsonDocument<500> doc;

  HTTPClient http;
  http.begin(server + ae + "/" + cnt4 + "/la");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json");

  int code = http.GET();

  if (code == -1)
  {
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  String json;
  json = http.getString();
  auto error = deserializeJson(doc, json.c_str());
  if (error)
  {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    return 0;
  }
  String temp = doc["m2m:cin"]["con"];
  http.end();

  float val=temp.toFloat();

  return val;
}


float getdatahumidity(){
  StaticJsonDocument<500> doc;

  HTTPClient http;
  http.begin(server + ae + "/" + cnt3 + "/la");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json");

  int code = http.GET();

  if (code == -1)
  {
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  String json;
  json = http.getString();
  auto error = deserializeJson(doc, json.c_str());
  if (error)
  {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    return 0;
  }
  String temp = doc["m2m:cin"]["con"];
  http.end();

  float val=temp.toFloat();

  return val;
}

float getdatatemperature(){
  StaticJsonDocument<500> doc;

  HTTPClient http;
  http.begin(server + ae + "/" + cnt2 + "/la");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json");

  int code = http.GET();

  if (code == -1)
  {
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  String json;
  json = http.getString();
  auto error = deserializeJson(doc, json.c_str());
  if (error)
  {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    return 0;
  }
  String temp = doc["m2m:cin"]["con"];
  http.end();

  float val=temp.toFloat();

  return val;
}


String getdatacrash(){
  StaticJsonDocument<500> doc;

  HTTPClient http;
  http.begin(server + ae + "/" + cnt1 + "/la");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json");

  int code = http.GET();

  if (code == -1)
  {
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  String json;
  json = http.getString();
  auto error = deserializeJson(doc, json.c_str());
  if (error)
  {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    String s="0";
    return s;
  }
  String temp = doc["m2m:cin"]["con"];
  http.end();

  return temp;
}


void setup() {
  pinMode(33,OUTPUT);
  Serial.begin(9600);
  digitalWrite(33,HIGH);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
  }
  Serial.println("WiFi connected to IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
 String crashvalintake=getdatacrash();
 float temperatureinCintake=getdatatemperature();
 float humidityintake=getdatahumidity();
 float pressureintake=getdatapressure();
 

  Serial.print("Intake of crash sensor: ");
  Serial.println(crashvalintake);
  Serial.print("Intake of temperature: ");
  Serial.println(temperatureinCintake);
  Serial.print("Intake of humidity: ");
  Serial.println(humidityintake);
  Serial.print("Intake of pressure: ");
  Serial.println(pressureintake);
  

  String ans="";
  
if (crashvalintake == "collision_detected")
  {
    Serial.println("CRASH");
    digitalWrite(buzzer, LOW);
    delay(800);
    crashvalintake=getdatacrash();
    Serial.println("CRASHVALINTAKE");
    Serial.println(crashvalintake);
    while (crashvalintake == "no_collision")
    {
      digitalWrite(buzzer, LOW);
      delay(500);

    crashvalintake=getdatacrash();
    humidityintake=getdatahumidity();
    temperatureinCintake=getdatatemperature();
    pressureintake=getdatapressure();
    

  Serial.print("Intake of crash sensor: ");
  Serial.println(crashvalintake);
  Serial.print("Intake of humidity: ");
  Serial.println(humidityintake);
  Serial.print("Intake of temperature: ");
  Serial.println(temperatureinCintake);
  Serial.print("Intake of pressure: ");
  Serial.println(pressureintake);

    if(temperatureinCintake > 35)
    {
      Serial.println("High temperature");
    }

    if(humidityintake > 90)
    {
      Serial.println("High humidity");
    }

    if(pressureintake > 960)
    {
      Serial.println("High pressure");
    }
    Serial.println("CRASH INTAKE END1");
    Serial.println(crashvalintake);
   }
  }

  digitalWrite(buzzer,HIGH);

  while (temperatureinCintake > 35 || humidityintake > 75 || pressureintake > 960)
  {
    digitalWrite(buzzer, LOW);
    delay(500);

    crashvalintake=getdatacrash();
    temperatureinCintake=getdatatemperature();
    humidityintake=getdatahumidity();
    pressureintake=getdatapressure();
    
  Serial.print("Intake of crash sensor: ");
  Serial.println(crashvalintake);
  Serial.print("Intake of temperature: ");
  Serial.println(temperatureinCintake);
  Serial.print("Intake of humidity: ");
  Serial.println(humidityintake);
  Serial.print("Intake of pressure: ");
  Serial.println(pressureintake);
  
  

    if(temperatureinCintake > 35)
    {
      Serial.println("High temperature");
    }

    if(humidityintake > 90)
    {
      Serial.println("High humidity");
    }

    if(pressureintake > 960)
    {
      Serial.println("High pressure");
    }

    digitalWrite(buzzer,HIGH);
  }
  digitalWrite(buzzer,HIGH);
}

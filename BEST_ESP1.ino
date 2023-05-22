#define BLYNK_TEMPLATE_ID "TMPLIPjSJZcN"
#define BLYNK_DEVICE_NAME "IoT project "
#define BLYNK_AUTH_TOKEN "9GqUnFq7eMqW06FiPXs4SgFI_QgcqAyN"
char auth[] = BLYNK_AUTH_TOKEN  ;

#include "DHT.h"
#include <WiFi.h>
#include "HTTPClient.h"
#include "time.h"
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include "ThingSpeak.h"
#include <PubSubClient.h>
#include <BlynkSimpleEsp32.h>

//#define BLYNK_PRINT Serial
#define DHTTYPE DHT11

int crashsen = 33;

int buzzer = 32;

int DHTsen = 14;
int DHTpwr=26;
int DHTgnd=27;

int bmp_I2C_SDA = 21;
int bmp_I2C_SCL = 22;
int bmpgnd=23;
int bmppwr=19;


BlynkTimer timer;

DHT dht(DHTsen, DHTTYPE);

TwoWire I2CBMP = TwoWire(0);
Adafruit_BMP280 bmp(&I2CBMP);

#define SEALEVELPRESSURE_HPA (1013.25)

char mqttPass[] = "mvKmAMvQt4uthNctXt5FeQ97";
#define SECRET_CH_ID 1781929     // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "BJU45OI1JDT0BHOA"   // replace XYZ with your channel write API Key

unsigned long myChannelNumber = SECRET_CH_ID;
char * myWriteAPIKey = SECRET_WRITE_APIKEY;


WiFiClient WIFI_CLIENT;


char ssid[] = "Nothing" ;
char password[] = "nothing0";


String cse_ip = "192.168.32.2"; // YOUR IP from ipconfig/ifconfig
String cse_port = "8080";
String server = "http://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";

const char* Server ="mqtt3.thingspeak.com";

String ae = "Project";
String cnt1 = "Data_crash";
String cnt2 = "Data_temperature";
String cnt3 = "Data_humidity";
String cnt4 = "Data_pressure";

// Initialize our values
float number1 = 0;
float number2 = 0;
float number3 = 0;
float number4 = 0;
String N1 = "";
String N2 = "";
String N3 = "";
String N4 = "";

String myStatus = "";

char mqttUserName[] = "AjUZDT0IAhwRPDsGDx8ZIAM";
String topicString ="";
String dataString="69";
float dataArray[1] = {69};

PubSubClient mqttClient(Server, 1883, WIFI_CLIENT );

void mqttPublish1(long pubChannelID, char* pubWriteAPIKey, float dataArray[], int fieldArray[])
{
  int index=0;
  
  while(index < 7){
      if(index == 0){
         topicString = "";
         topicString += "channels/" + String(pubChannelID) + "/publish" ;
      }
      index++;
  }
  String payload = "field1=";
  payload += dataString;
  mqttClient.publish(topicString.c_str(),payload.c_str());
}

void mqttPublish2(long pubChannelID, char* pubWriteAPIKey, float dataArray[], int fieldArray[])
{
  int index=0;
  
  while(index < 7){
      if(index == 0){
         topicString = "";
         topicString += "channels/" + String(pubChannelID) + "/publish" ;
      }
      index++;
  }
  String payload = "field2=";
  payload += dataString;
  mqttClient.publish(topicString.c_str(),payload.c_str());
}

void mqttPublish3(long pubChannelID, char* pubWriteAPIKey, float dataArray[], int fieldArray[])
{
  int index=0;
  
  while(index < 7){
      if(index == 0){
         topicString = "";
         topicString += "channels/" + String(pubChannelID) + "/publish" ;
      }
      index++;
  }
  String payload = "field3=";
  payload += dataString;
  mqttClient.publish(topicString.c_str(),payload.c_str());
}

void mqttPublish4(long pubChannelID, char* pubWriteAPIKey, float dataArray[], int fieldArray[])
{
  int index=0;
  
  while(index < 7){
      if(index == 0){
         topicString = "";
         topicString += "channels/" + String(pubChannelID) + "/publish" ;
      }
      index++;
  }
  String payload = "field4=";
  payload += dataString;
  mqttClient.publish(topicString.c_str(),payload.c_str());
}


float getdatapressure(){
  StaticJsonDocument<500> doc;

  HTTPClient http;
  http.begin(server + ae + "/" + cnt4+ "/la");
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


float getdatahumidty(){
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
    String s="";
    return s;
  }
  String temp = doc["m2m:cin"]["con"];
  http.end();

  return temp;
}

void createCI4(String &val) {
  HTTPClient http;
  http.begin(server + ae + "/" + cnt4 + "/");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");
  Serial.println(code);
  if (code == -1) {
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
}


void createCI3(String &val) {
  HTTPClient http;
  http.begin(server + ae + "/" + cnt3 + "/");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");
  Serial.println(code);
  if (code == -1) {
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
}


void createCI2(String &val) {
  HTTPClient http;
  http.begin(server + ae + "/" + cnt2 + "/");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");
  Serial.println(code);
  if (code == -1) {
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
}


void createCI1(String val) {
  HTTPClient http;
  http.begin(server + ae + "/" + cnt1 + "/");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  
  String data_con  = "{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " ;
  data_con += "\"" + val + "\""; 
  data_con += "}}";
  int code = http.POST(data_con);
  Serial.println(code);
  if (code == -1) {
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
}

void sendSensor(){
    
  int crashval = digitalRead(crashsen);
  Serial.println("fgh");
  
  Blynk.virtualWrite(V1, crashval);
  
  if(crashval == 0){
    Blynk.email("st545362@gmail.com", "Alert", "There is a collision");
    Blynk.logEvent("crash","There is a collision");
  }
}
  
void setup() {

  
  Serial.begin(9600);
  pinMode(crashsen, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(DHTsen, INPUT);
  pinMode(DHTpwr, OUTPUT);
  pinMode(DHTgnd, OUTPUT);
  pinMode(bmpgnd, OUTPUT);
  pinMode(bmppwr, OUTPUT);
  
  digitalWrite(buzzer, HIGH);

  digitalWrite(DHTpwr, HIGH);
  digitalWrite(DHTgnd, LOW);

  digitalWrite(bmpgnd, LOW);
  digitalWrite(bmppwr, HIGH);

  I2CBMP.begin(bmp_I2C_SDA, bmp_I2C_SCL, 100000);
  bool status;

  status = bmp.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
  }
  Serial.print("WiFi connected to IP: ");
  Serial.println(WiFi.localIP());

  dht.begin();

  mqttClient.setServer ( Server, 1883 );

  mqttClient.connect(mqttUserName,mqttUserName,mqttPass) ;
  while(mqttClient.connected()== false)
  {
    Serial.println("Attempting to connect to MQTT");
    mqttClient.connect(mqttUserName,mqttUserName,mqttPass) ;
    delay(1000);
  }
  Serial.println("You're connected to the network");

  Blynk.begin(auth,ssid,password);
  timer.setInterval(2500L,sendSensor);
}



void loop() {
  Blynk.run();
  timer.run();
  
   
  while(mqttClient.connected()== false)
  {
    Serial.println("Attempting to connect to MQTT");
    mqttClient.connect(mqttUserName,mqttUserName,mqttPass) ;
  }
  
  digitalWrite(buzzer, HIGH);
  
  String ans="";
  
  
  float temperatureinC = dht.readTemperature();
  ans = String(temperatureinC);
  createCI2(ans);
  float humidity = dht.readHumidity();
  ans = String(humidity);
  createCI3(ans);
  float temperatureinF = dht.readTemperature(true);
  float pressure = bmp.readPressure() / 100.0F;
  ans = String(pressure);
  createCI4(ans);

  int crashval = digitalRead(crashsen);
  if (crashval == 0)
  {
    String ans = "collision_detected";
    createCI1(ans);
    Serial.println(ans);
  }
  else
  {
    String ans = "no_collision"; 
    createCI1(ans);
    Serial.println(ans);
  }

  Serial.print("TEMPERATURE IN C : ");
  Serial.println(temperatureinC);

  Serial.print("TEMPERATURE IN F : ");
  Serial.println(temperatureinF);

  Serial.print("HUMIDITY : ");
  Serial.println(humidity);

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");
        
  String res="";

  number4=pressure;
  number3=temperatureinC;
  number2=humidity;
  if(crashval==1)
  {
      N1="no_collison";
  }
  else if(crashval==0)
  {
      N1="collision_detected";
  }
  N4=String(pressure,3);
  N3=String(temperatureinC,3);
  N2=String(humidity,3);
  
  mqttClient.loop();

  if(pressure>900){
      int fieldsToPublish[8] = {1,0,0,0,0,0,0,0};
      dataString=N4;
      mqttPublish1( myChannelNumber, myWriteAPIKey,dataArray, fieldsToPublish );
  }
  
  if(!isnan(number3)){
    int fieldsToPublish[8] = {1,0,0,0,0,0,0,0};
      dataString=N3;
      mqttPublish2( myChannelNumber, myWriteAPIKey,dataArray, fieldsToPublish );
  }
  
  if(!isnan(number2)){
      int fieldsToPublish[8] = {1,0,0,0,0,0,0,0};
      dataString=N2;
      mqttPublish3( myChannelNumber, myWriteAPIKey,dataArray, fieldsToPublish );
  }
  
  int fieldsToPublish[8] = {1,0,0,0,0,0,0,0};
  if(crashval==0)
  {
    dataString="1";
  }
  else
  {
    dataString="0";
  }
  mqttPublish4( myChannelNumber, myWriteAPIKey,dataArray, fieldsToPublish );

 String crashvalintake=getdatacrash();
 float humidityintake=getdatahumidty();
 float temperatureinCintake=getdatatemperature();
 float pressureintake=getdatapressure();
 

  Serial.print("Intake of crash sensor: ");
  Serial.println(crashvalintake);
  Serial.print("Intake of humidity: ");
  Serial.println(humidityintake);
  Serial.print("Intake of temperature: ");
  Serial.println(temperatureinCintake);
  Serial.print("Intake of pressure: ");
  Serial.println(pressureintake);
  
 
  if (crashvalintake == "collision_detected")
  {
    Serial.println("CRASH");
    digitalWrite(buzzer, LOW);
    delay(1000);
    crashval = digitalRead(crashsen);
      if (crashval == 0)
      {
           ans = "collision_detected";
           createCI1(ans);
      }
      else
      {
            ans = "no_collision";
            createCI1(ans);
      }
    crashvalintake=getdatacrash();
    Serial.println("CRASHVALINTAKE");
    Serial.println(crashvalintake);
    while (crashvalintake == "no_collision")
    {
      digitalWrite(buzzer, LOW);
      delay(100);
      crashval = digitalRead(crashsen);
      if (crashval == 0)
      {
           ans = "collision_detected";
           createCI1(ans);
      }
      else
      {
            ans = "no_collision";
            createCI1(ans);
      }

    crashvalintake=getdatacrash();
    humidityintake=getdatahumidty();
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

    
      humidity = dht.readHumidity();
      ans = String(humidity);
      createCI3(ans);
      temperatureinC = dht.readTemperature();
      ans = String(temperatureinC);
      createCI2(ans);
      pressure = bmp.readPressure() / 100.0F;
      ans = String(pressure);
      createCI4(ans);

    Serial.print("HUMIDITY is : ");
    Serial.println(humidity);
    Serial.print("TEMPERATURE In C : ");
    Serial.println(temperatureinC);
    Serial.print("PRESSURE is : ");
    Serial.println(pressure);

    if(temperatureinCintake > 35)
    {
      Serial.println("High temperature");
    }

    if(humidityintake > 75)
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
    
    crashval = digitalRead(crashsen);
      if (crashval == 0)
      {
           ans = "collision_detected";
           Serial.println("CRASH");
           createCI1(ans);
      }
      else
      {
            ans = "no_collision";
            createCI1(ans);
      }

      
    humidity = dht.readHumidity();
    ans = String(humidity);
    createCI3(ans);
    temperatureinC = dht.readTemperature();
    ans = String(temperatureinC);
    createCI2(ans);
    pressure = bmp.readPressure() / 100.0F;
    ans = String(pressure);
    createCI4(ans);

    Serial.print("HUMIDITY is : ");
    Serial.println(humidity); 
    Serial.print("TEMPERATURE In C : ");
    Serial.println(temperatureinC);
    Serial.print("PRESSURE is : ");
    Serial.println(pressure);

    crashvalintake=getdatacrash();
    temperatureinCintake=getdatatemperature();
    pressureintake=getdatapressure();
    humidityintake=getdatahumidty();

  Serial.print("Intake of crash sensor: ");
  Serial.println(crashvalintake);
  Serial.print("Intake of temperature: ");
  Serial.println(temperatureinCintake);
  Serial.print("Intake of pressure: ");
  Serial.println(pressureintake);
  Serial.print("Intake of humidity: ");
  Serial.println(humidityintake);

  
  number4=pressure;
  number3=temperatureinC;
  number2=humidity;
  if(crashval==1)
  {
      N1="no_collision";
  }
  else if(crashval==0)
  {
      N1="collision_detected";
  }
  N4=String(pressure,3);
  N3=String(temperatureinC,3);
  N2=String(humidity,3);

  
    mqttClient.loop();

    
    if(pressure>900){
      int fieldsToPublish[8] = {1,0,0,0,0,0,0,0};
      dataString=N4;
      mqttPublish1( myChannelNumber, myWriteAPIKey,dataArray, fieldsToPublish );
      }
  
    if(!isnan(number3)){
    int fieldsToPublish[8] = {1,0,0,0,0,0,0,0};
      dataString=N3;
      mqttPublish2( myChannelNumber, myWriteAPIKey,dataArray, fieldsToPublish );
      }
  
    if(!isnan(number2)){
      int fieldsToPublish[8] = {1,0,0,0,0,0,0,0};
      dataString=N2;
      mqttPublish3( myChannelNumber, myWriteAPIKey,dataArray, fieldsToPublish );
      }

  
  int fieldsToPublish[8] = {1,0,0,0,0,0,0,0};
  if(crashval==0)
  {
    dataString="1";
  }
  else
  {
    dataString="0";
  }
  mqttPublish4( myChannelNumber, myWriteAPIKey,dataArray, fieldsToPublish );

      
    if(humidityintake > 75)
    {
      Serial.println("High humidity");
    }
    
    if(temperatureinCintake > 35)
    {
      Serial.println("High temperature");
    }
    
    if(pressureintake > 960)
    {
      Serial.println("High pressure");
    }

    digitalWrite(buzzer,HIGH);
    Serial.println("CRASH INTAKE END2");
    Serial.println(crashvalintake);
  }
}

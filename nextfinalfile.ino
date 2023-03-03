#define BLYNK_TEMPLATE_ID "TMPLYCHwWgCF"
#define BLYNK_DEVICE_NAME "nextgeir"
#define BLYNK_AUTH_TOKEN "8MDQw3PnZHgBN_vfwDaBYTMPctDQFwvU"
#include "Arduino.h"
#include <DFRobot_DHT11.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

DFRobot_DHT11 DHT;  
char ssid[] = "UBUNTU";
char pass[] = "#Rishabh16";
int soilpin = A0;  
int motorpin = 12 ;
int motorpin2 = 0;  


#define DHT11_PIN 13

void setup()
{   
    Serial.begin(115200);
     WiFi.begin(ssid,pass);
  
    while (WiFi.status() != WL_CONNECTED){
    Serial.println("trying to connect....");
    delay(200);
  };
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(motorpin,OUTPUT);
  pinMode(motorpin2,OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  digitalWrite(motorpin,LOW);
   digitalWrite(motorpin2,LOW);
  Blynk.run();
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  int temp = DHT.temperature;
  delay(1000);
  Serial.print(temp);
  Blynk.virtualWrite(V0,temp);
  Serial.print(" humi:");
  
  int humi = DHT.humidity;
  delay(1000);
  Serial.println(humi);
   Blynk.virtualWrite(V1,humi);
  
  // high humidity warning
if(humi>50){
    Serial.print("HIGH humidity detected");
    Blynk.logEvent("highhumidity", "High humidity detected!");
   
   
  }
  else{digitalWrite(motorpin2,HIGH);}
  
  //high temp warning
    if(35<temp)
  {
    
    Serial.print("  temperature is too high!");
    Blynk.logEvent("highTemp", "High temperature detected!");
     digitalWrite(motorpin2,HIGH);
    }

   int moisture_percentage = ( 100.00 - ( (analogRead(soilpin)/1023.00) * 100.00 ) );

  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Blynk.virtualWrite(V3,moisture_percentage);
  Serial.println("%");

    //motor
    if(moisture_percentage<40){
      digitalWrite(motorpin,HIGH);
      }
      else{
        digitalWrite(motorpin,LOW);
      }
}
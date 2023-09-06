#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>




// WiFi credentials
char ssid[] = "HaoNguyen";
char password[] = "eeaciu19005";

// Blynk authentication token
char auth[] = "kxxTV2gSfpArhhRrU40emh9bRpwpMvkg";

int MoistureReadAnalog = A0;
int moisture;
float percent_wet;
float percent_dry;
int Button_Pump;



BLYNK_WRITE(V1)
{
  int buttonState = param.asInt();
  if (buttonState == 1)
  {
    Button_Pump=1; // Start the pump
  }
  else
  {
    Button_Pump=0; // Stop the pump
  }
}
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);
  pinMode(MoistureReadAnalog, INPUT);
  pinMode(D1,OUTPUT);
  // put your setup code here, to run once:

}

int moisture_value(){
  moisture = analogRead(MoistureReadAnalog);
  
  delay(1000);
  percent_dry = moisture*100/1024;
  percent_wet = 100 - percent_dry;
  Blynk.virtualWrite(V0, percent_wet);
  return percent_wet;
}


void loop() {
  Blynk.run();
//  moisture = analogRead(MoistureReadAnalog);
//  percent_dry = moisture*100/1024;
//  percent_wet = 100 - percent_dry;
  percent_wet= moisture_value();
  Serial.println(percent_wet);

 
  if (percent_wet < 30 && Button_Pump == 1){
    digitalWrite(D1,HIGH);
  }
  else{
    digitalWrite(D1,LOW);
  }

}

#include<WiFi.h>
#include<PubSubClient.h>
#include <ThingSpeak.h>

const char *ssid = "Enter SSID here" ;
const char *password = "Enter Password Here" ;

const long CHANNEL =  ; //channel ID
const char *WRITE_API = ""; //write api key

WiFiClient client ;
int interval = 15*1000;

long now = 0 ;

void connect_wifi()
{
  Serial.print("Connecting to ") ;
  Serial.println(ssid) ;
  WiFi.begin(ssid,password) ;
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500) ;
    Serial.print(".") ;
  }
  Serial.print("Connection successful!") ;
  Serial.print("IP Address : ") ;
  Serial.println(WiFi.localIP()) ;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200) ;
  connect_wifi() ;
  ThingSpeak.begin(client);
}



void loop() 
{
  // put your main code here, to run repeatedly:
  int h = 0 ;
  if (millis() - now > interval)
  {
    h = hallRead() ;
    ThingSpeak.setField(1, h);
    int status1 =  ThingSpeak.writeFields(CHANNEL, WRITE_API); //get response, if response is 200, then values have been updated successfully!
     if (status1 == 200) 
     {
        Serial.println("Updated values successfully");
     }
     else 
     {
        Serial.println("Error Occured. HTTP error code " + String(status1));
     }
    now = millis() ;
  }  
}

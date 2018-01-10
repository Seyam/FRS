/*                  (____/ 
 * Use NodeMCU to drive DHT11 and send temperature/humidity value to MQTT server
 * Tutorial URL http://osoyoo.com/2016/11/24/use-nodemcu-to-send-temperaturehumidity-data-to-mqtt-iot-broker/
 * CopyRight John Yu
 */
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const int led = D0; // ONBOARD LED D0 WORKS OPPOSITE
//const int ledPin2 = D2; // Pin


// Update these with values suitable for your network.
const char* ssid = "DataSoft_WiFi";
const char* password = "support123";
//const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* mqtt_server = "182.48.84.180";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[5];
//int value = 0;


unsigned long lastTime = 0;

void setup() {
  
  
  pinMode(led,OUTPUT);

  
  delay(100);
  Serial.begin(9600);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}//setup ends here

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  checkTime();
  
//  long now = millis();
//  // read DHT11 sensor every 10 seconds
//  if (now - lastMsg > 3000) {
//     lastMsg = now;
//     
//     //Write code here 
//     //sendStatus();
//  }
}//loop ends here





void setup_wifi() {
    delay(1000);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Topic : ");
  Serial.print(topic);
  Serial.print("  Data : ");
  //int p =(char)payload[0]-'0';
  //Serial.println(p);

    // char receivedChar;
    
    


        if (strcmp(topic,"ds/frs")==0){

          char receivedChar;
          
          for (int i=0;i<length;i++) {
              receivedChar = (char)payload[i];
              Serial.print(receivedChar);
              
            //  if (receivedChar == '0'){
            //    Serial.println("Got 0");
            //  }
            //  
            //  if (receivedChar == '1')
            //   Serial.println("Got 1");
          }

          
        // whatever you want for this topic
              // if MQTT comes a 0 message, show humidity
          if(receivedChar=='0') 
          {
              
              setAlarmOn();
//              unsigned long currentTime = millis();
//
//              if(currentTime-lastTime > 2000){
//                   setAlarmOff();
//              }
          } 
          // if MQTT comes a 1 message, show temperature
          if(receivedChar=='1')
          {
              setAlarmOff();            
          }
       

      }
  

   Serial.println();

} //end callback







void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
     //once connected to MQTT broker, subscribe command if any
      
      client.subscribe("ds/frs/test");
      Serial.println("Subscribed to the topic:    ds/frs");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 6 seconds before retrying
      delay(6000);
    }
  }
} //end reconnect()


void setAlarmOn(){

    digitalWrite(led,HIGH);
    Serial.println("Pin HIGH");
    
  
}


void checkTime(){

    if(){

        unsigned long currentTime = millis();
    
        if(currentTime - lastTime> 2000){
             lastTime = currentTime;
             setAlarmOff();
        }
      
    }

 
  
}




void setAlarmOff(){
    digitalWrite(led,LOW);
    Serial.println("Pin LOW");
}


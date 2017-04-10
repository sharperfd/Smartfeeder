#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

const int BUFSIZE = 50; //size off ssid and password
char buf[BUFSIZE];
char buf2[BUFSIZE];
char buf3[BUFSIZE];
const int EEPROM_MIN_ADDR = 0;
const int EEPROM_MAX_ADDR = 511;

boolean eeprom_is_addr_ok(int addr) {
    return ((addr >= EEPROM_MIN_ADDR) && (addr <= EEPROM_MAX_ADDR));
}

String data1,data2,data3;   

const char* ssid = " "; 
const char* password = "  "; 

#define mqtt_server "m11.cloudmqtt.com" //edit
#define mqtt_port 10169 //edit
#define mqtt_user " " //edit
#define mqtt_password " " //edit

#define PubTopic1 "/BT1"
#define SubTopic1 "/TOKEN"


const int motorPin1 = D1;
const int motorPin2 = D2;
const int motorPinEnablePWM = D5;

String LINE_TOKEN = "4YmQSoBzrZYQffL6mI8iJLUH8Js7KcIdz55i2QiyxA3"; //edit
String message = "%F0%9F%98%BD%20%20%E0%B8%81%E0%B8%B4%E0%B8%99%E0%B8%82%E0%B9%89%E0%B8%B2%E0%B8%A7%E0%B9%81%E0%B8%A5%E0%B9%89%E0%B8%A7%E0%B8%99%E0%B8%B0%E0%B9%80%E0%B8%AB%E0%B8%A1%E0%B8%B5%E0%B9%8A%E0%B8%A2%E0%B8%A7%20";

const int buttonPin = D3;
const int ledPin = 13;

String Status="";
String TimeForNow ="";
int count = 0;
int CheckLogin = 0;
WiFiClient espClient;
PubSubClient client(espClient);

boolean eeprom_write_bytes(int startAddr, const byte* array, int numBytes) {
// counter
    int i;
// both first byte and last byte addresses must fall within
// the allowed range 
    if (!eeprom_is_addr_ok(startAddr) || !eeprom_is_addr_ok(startAddr + numBytes)) {
      return false;
    }
    for (i = 0; i < numBytes; i++) {
      EEPROM.write(startAddr + i, array[i]);
    }
    EEPROM.commit();
    return true;
}


boolean eeprom_write_string(int addr, const char* string) {
    int numBytes; // actual number of bytes to be written
    //write the string contents plus the string terminator byte (0x00)
    numBytes = strlen(string) + 1;
    return eeprom_write_bytes(addr, (const byte*)string, numBytes);
}


boolean eeprom_read_string(int addr, char* buffer, int bufSize) {
    byte ch; // byte read from eeprom
    int bytesRead; // number of bytes read so far
    if (!eeprom_is_addr_ok(addr)) { // check start address
      return false;
    }

    if (bufSize == 0) { // how can we store bytes in an empty buffer ?
     return false;
    }
    // is there is room for the string terminator only, no reason to go further
    if (bufSize == 1) {
      buffer[0] = 0;
      return true;
    }
    bytesRead = 0; // initialize byte counter
    ch = EEPROM.read(addr + bytesRead); // read next byte from eeprom
    buffer[bytesRead] = ch; // store it into the user buffer
    bytesRead++; // increment byte counter
    // stop conditions:
    // - the character just read is the string terminator one (0x00)
    // - we have filled the user buffer
    // - we have reached the last eeprom address
    while ( (ch != 0x00) && (bytesRead < bufSize) && ((addr + bytesRead) <= EEPROM_MAX_ADDR) ) {
      // if no stop condition is met, read the next byte from eeprom
      ch = EEPROM.read(addr + bytesRead);
      buffer[bytesRead] = ch; // store it into the user buffer
      bytesRead++; // increment byte counter
    }
    // make sure the user buffer has a string terminator, (0x00) as its last byte
    if ((ch != 0x00) && (bytesRead >= 1)) {
      buffer[bytesRead - 1] = 0;
    }
    return true;
}



void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);

  eeprom_read_string(5, buf, BUFSIZE);
  eeprom_read_string(60, buf2, BUFSIZE);
  eeprom_read_string(200, buf3, BUFSIZE);

  ssid=buf; //set data from eeprom address 5 to password
  password=buf2;
  LINE_TOKEN=buf3;
  
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(buttonPin, HIGH);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPinEnablePWM, OUTPUT);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    if(count==10){
      break;
    }
    delay(500);
    Serial.print(".");
    count++;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("LINE TOKEN : ");
  Serial.println(LINE_TOKEN);

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String msg = "";
  int i=0;
  while (i<length) {
     msg += (char)payload[i++];
  }
  Serial.println(msg);
   
   if (msg == "GETFOOD") {
      analogWrite(motorPinEnablePWM, 450);
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, HIGH); 
      delay(500);
      //analogWrite(motorPinEnablePWM, 0);
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW); 
      delay(500);
      analogWrite(motorPinEnablePWM, 450);
      digitalWrite(motorPin1, HIGH);
      digitalWrite(motorPin2, LOW); 
      delay(480);//Time to back spin
      //analogWrite(motorPinEnablePWM, 0);
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      Serial.println("Food have feeder already by yourself !");

      if(WiFi.status() == WL_CONNECTED){          
          Serial.println("Online !!");
          client.setServer(mqtt_server, mqtt_port);
          client.publish(PubTopic1,"eat");  
          Serial.println("Data eat sent to MQTT!!"); 
          Line_Notify(message);
          
          if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
            Serial.println("connected_MQTT");
          }   
      }   
  }
  else{ 
    for (int i = 170; i < 512; i++)
    {
      EEPROM.write(i, 0);   //clear eeprom 
    }
    strcpy(buf3, msg.c_str()); //copy TokenLine to buf3 
    eeprom_write_string(200, buf3); // write buf to eeprom address 200  
    LINE_TOKEN = msg;
  }
  
}

void loop() {
  if(Serial.available()){
    data1  = Serial.readStringUntil(',');
    Serial.read(); //next character is comma, so skip it using this
    data2  = Serial.readStringUntil('\0');
    reConnect();
  }
  int buttonVal = digitalRead(buttonPin);
  if(buttonVal == LOW) {
    Serial.println("The cat eats the food !!");
    analogWrite(motorPinEnablePWM, 450);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH); 
    delay(500);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW); 
    delay(500);
    analogWrite(motorPinEnablePWM, 450);
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW); 
    delay(480);//Time to back spin
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    if(WiFi.status() == WL_CONNECTED){
      
      if(CheckLogin == 1){
        Serial.println("Online !!");
        client.setServer(mqtt_server, mqtt_port);
        client.publish(PubTopic1,"eat");  
        Serial.println("Data eat sent to MQTT!!"); 
        Line_Notify(message);
      }
      
      if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
        Serial.println("connected_MQTT");
      } 
      client.publish(PubTopic1,"eat");
      Serial.println("Data eat sent to MQTT!!");
      Line_Notify(message);
      CheckLogin=0;
        
    }
    if (WiFi.status() != WL_CONNECTED){
      CheckLogin = 1;
    }
    delay(1000);
  }
  
  if(WiFi.status() == WL_CONNECTED){
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      client.subscribe(SubTopic1);            
    } 
  }
  client.loop(); 
  delay(13);
}

void reConnect(){
  EEPROM.begin(512);
  WiFi.disconnect();
  const char* ssid2=data1.c_str(); 
  const char* pass2=data2.c_str();
  for (int i = 0; i < 170; i++)
  {
    EEPROM.write(i, 0);   //clear eeprom 
  }
  strcpy(buf, data1.c_str()); //copy ssid to buf
  Serial.print(buf);
  eeprom_write_string(5, buf);  //write buf to eeprom address 5
  strcpy(buf2, data2.c_str()); //copy password to buf2
  Serial.print(buf2);
  eeprom_write_string(60, buf2); // write buf to eeprom address 60
  
  int x=0;
  WiFi.begin(ssid2, pass2);
  while (WiFi.status() != WL_CONNECTED) {
            x=x+1;
            delay(1000);
            Serial.print(".");
            if (x==15) //wait for reconnect 15 second
            {
              break;
            }
  }
}

void Line_Notify(String message) {
  WiFiClientSecure client2;

  if (!client2.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;   
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  client2.print(req);
    
  delay(20);

  while(client2.connected()) {
    String line = client2.readStringUntil('\n');
    if (line == "\r") {
      break;
    }  
  } 
}



#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
#include<BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPL35L_E6ssn"
#define BLYNK_DEVICE_NAME "robot"
#define BLYNK_AUTH_TOKEN "KMWqBuFPn8KNdBQlmebMZFy0T37rxFtt"

#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5

#define trigPin D6   
#define echoPin  D7 
#define trigPin1 D8   
#define echoPin1  D10 
 
int forward=0;
int backward=0;
 int left=0;
 int right=0;
 int Stop=0;
 int Speed=255;
 char ssid[]="V2027";
 char pass[]="ayushi47";

   long dur;
  int dist;
  long duration ;  
 int distance; 
 void setup(){
  Serial.begin(115200);
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN,ssid,pass);
  
  }
  BLYNK_WRITE(V0){
    forward=param.asInt();
    }
      BLYNK_WRITE(V1){
    backward=param.asInt();
    }
  BLYNK_WRITE(V2){
    left=param.asInt();
    }
  BLYNK_WRITE(V3){
    right=param.asInt();
    }
  BLYNK_WRITE(V4){
    Stop=param.asInt();
    }

 void ultrasonic(){
      digitalWrite(trigPin, LOW);  
 delay(2);  
  
 digitalWrite(trigPin, HIGH);  
 delay(10);  
 digitalWrite(trigPin, LOW);  
  
 duration = pulseIn(echoPin, HIGH);  
 
 distance= duration*0.034/2;  
  
 Serial.print("Distance: ");  
 Serial.println(distance);  

  }

    void sonic(){
    digitalWrite(trigPin1, LOW);  
 delay(2);  
  
 digitalWrite(trigPin1, HIGH);  
 delay(10);  
 digitalWrite(trigPin1, LOW);  
  
 dur = pulseIn(echoPin1, HIGH);  
 
 dist= dur*0.034/2;  
  
 Serial.print("Distance: ");  
 Serial.println(dist);  

  }
    
    void smart_car(){
      if(forward==1){c_forward();  barrier();}
      
       if(backward==1){c_backward();b();}
      
       if(left==1){c_left();delay(1000);left=0;Blynk.virtualWrite(V2,0);}
      
       if(right==1){c_right();delay(1000);right=0;Blynk.virtualWrite(V3,0);}
      
       if((forward==0 && backward==0 && right==0 && left==0)||(Stop==1)){c_stop();}
      }

void loop(){
  Blynk.run();
  smart_car();
  }
void c_forward(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(IN2,LOW);

  }
  void c_backward(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN3,LOW);
  }
  void c_left(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(IN2,LOW);

  
  }
  void c_right(){
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN4,LOW);
  }
  void c_stop(){
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  digitalWrite(IN2,LOW);
  }

   void barrier(){
    ultrasonic();
    
    if(distance > 30|| distance == 30)   
  {
   c_forward();

  }
  else{
    c_stop();
    delay(1000);
  }  }
  
 void b(){
    sonic();
    if(dist > 30|| dist== 30){
    c_backward();
  }
  else{
    c_stop();
    delay(1000);
  }
 }
 

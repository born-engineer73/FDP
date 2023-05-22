#include <ESP8266WiFi.h>
const int d = 10;
const int l = 20;
const int v = 10;
const int w = 10;
const int dis_err = 0.5;
const int ang_err = 10;
int trig = 2;
int echo = 3;
int m1_p1 = D1;
int m1_p2 = D2;
int m2_p1 = D3;
int m2_p2 = D4;
int st = millis();
int ct = millis();
int a = 0;
int dist_x=0;
int dist_y=0;


float gap(){
  digitalWrite(trig,HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trig,LOW);  
  float duration=pulseIn(echo,HIGH);  
  float r = duration*0.017;  
  return r;
}
void dist(){
  ct=millis();
  float r = v*(ct-st);
  st=ct;
  Serial.println(r);
}
void ang(){
  ct=millis();
  float r = w*(ct-st);
  st=ct;
  a+=r;
  Serial.println(a);
}
void turn(){
  digitalWrite(m1_p1,HIGH);
  digitalWrite(m1_p2,LOW);
  digitalWrite(m2_p1,HIGH);
  digitalWrite(m2_p2,LOW);
  delay(v*(d+l));
  dist();
  digitalWrite(m1_p1,LOW);
  digitalWrite(m2_p1,LOW);
  while(gap()>d+dis_err){
    digitalWrite(m1_p1,LOW);
    digitalWrite(m1_p2,LOW);
    digitalWrite(m2_p1,HIGH);
    digitalWrite(m2_p2,LOW);
  }
  ang();
}

void setup() {
  // put your setup code here, to run once:
  WiFi.begin("Aditya", "pppppppp");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print("..");
    delay(200);
  }
  Serial.println("NodeMcu is connected!");
  Serial.println(WiFi.localIP());
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(m1_p1,OUTPUT);
  pinMode(m1_p2,OUTPUT);
  pinMode(m2_p1,OUTPUT);
  pinMode(m2_p2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((gap()<=d+dis_err)&&(gap()>=d-dis_err)){
    digitalWrite(m1_p1,HIGH);
    digitalWrite(m1_p2,LOW);
    digitalWrite(m2_p1,HIGH);
    digitalWrite(m2_p2,LOW);
    dist();
  }
  else turn();
  if ((a<=360+ang_err)&&(a>=360-ang_err)) exit(0);
}

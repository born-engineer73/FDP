#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <WiFi.h>

//set pins as per you connections. do checkout pin reference before finalizing connections.
int enA = 2;
int in2 = 3;
int in1 = 4;
int in4 = 5;
int in3 = 6;
int enB = 7;

const int max_speed = 254;

//place your wifi details here
const char *ssid = "wifi name";
const char *pass = "wifi password";
IPAddress server(192, 168, 244, 179);

// this is hardware class
class WiFiHardware {
public:
  WiFiClient client;
  WiFiHardware(){};

  void init() {
    client.connect(server, 11411);
  }

  int read() {
    return client.read(); 
  }

  void write(uint8_t *data, int length) {
    for (int i = 0; i < length; i++)
      client.write(data[i]);
  }

  unsigned long time() {
    return millis();
  }
};


ros::NodeHandle_<WiFiHardware> nh;

void ConnectToWifi() {
  WiFi.mode(WIFI_STA);
  delay(10);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

geometry_msgs::Twist signal;

void callback(const geometry_msgs::Twist& data){
  signal = data;
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &callback);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ConnectToWifi();
  nh.initNode();
  nh.subscribe(sub);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop() {
  int x = signal.angular.x;
  int y = signal.angular.y;
  if      (x == 0 && y == 1){forward();}
  else if (x == 1 && y == 1){left();}
  else if (x == 1 && y == 0){turnLeft();}
  else if (x == 1 && y == -1){backRight();}
  else if (x == 0 && y == -1){backward();}
  else if (x == -1 && y == -1){backLeft();}
  else if (x == -1 && y == 0){turnRight();}
  else if (x == -1 && y == 1){right();}
  else {stop();}
  nh.spinOnce(); 
}

void forward(){
  // analogWrite(enA, max_speed * input.z);
  // analogWrite(enB, max_speed * input.z);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void left(){
  // analogWrite(enA, max_speed * input.z);
  // analogWrite(enB, max_speed * input.z/2);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void right(){
  // analogWrite(enA, max_speed * input.z/2);
  // analogWrite(enB, max_speed * input.z);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backward(){
  // analogWrite(enA, max_speed * input.z);
  // analogWrite(enB, max_speed * input.z);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnRight(){
  // analogWrite(enA, max_speed * input.z);
  // analogWrite(enB, max_speed * input.z);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnLeft(){
  // analogWrite(enA, max_speed * input.z);
  // analogWrite(enB, max_speed * input.z);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}


void backLeft(){
  // analogWrite(enA, max_speed * input.z/2);
  // analogWrite(enB, max_speed * input.z);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void backRight(){
  // analogWrite(enA, max_speed * input.z);
  // analogWrite(enB, max_speed * input.z/2);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stop(){
  // analogWrite(enA, max_speed * input.z);
  // analogWrite(enB, max_speed * input.z);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}


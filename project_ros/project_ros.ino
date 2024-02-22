#include <Servo.h>
#include <ros.h>
#include <std_msgs/UInt16.h>


Servo Myservo1; // Servo for the first encoder
Servo Myservo2; // Servo for the second encoder

int encoder1PinA = 2;
int encoder1PinB = 3;
int Zsignal1 = 4;
int encoder1Pos = 0;
int encoder1PinALast = LOW;
int n1 = LOW;
int time1_H;
int time1_L;
float t_period1;
float Frequency1;

int encoder2PinA = 5;
int encoder2PinB = 6;
int Zsignal2 = 7;
int encoder2Pos = 0;
int encoder2PinALast = LOW;
int n2 = LOW;
int time2_H;
int time2_L;
float t_period2;
float Frequency2;

bool switch_mode = false; // Variable to control whether the servos should be controlled by ROS or by encoders

ros::NodeHandle nh;

void control_encoder1(const std_msgs::UInt16& cmd1_msg) {
  if (switch_mode) {
    Myservo1.write(cmd1_msg.data);
  }
}

void control_encoder2(const std_msgs::UInt16& cmd2_msg) {
  if (switch_mode) {
    Myservo2.write(cmd2_msg.data);
  }
}

void switch_callback(const std_msgs::UInt16& msg) {
  switch_mode = msg.data;
}

ros::Subscriber<std_msgs::UInt16> sub1("encoder_cmd1", &control_encoder1);
ros::Subscriber<std_msgs::UInt16> sub2("encoder_cmd2", &control_encoder2);
ros::Subscriber<std_msgs::UInt16> switch_sub("mode", &switch_callback);

void setup() {
  nh.initNode();
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.subscribe(switch_sub);

  Myservo1.attach(9);
  Myservo2.attach(10);
  pinMode(encoder1PinA, INPUT_PULLUP);
  pinMode(encoder1PinB, INPUT_PULLUP);
  pinMode(Zsignal1, INPUT_PULLUP);

  pinMode(encoder2PinA, INPUT_PULLUP);
  pinMode(encoder2PinB, INPUT_PULLUP);
  pinMode(Zsignal2, INPUT_PULLUP);

  Myservo1.write(90);
  Myservo2.write(90);
}

void loop() {
  nh.spinOnce();
  if (switch_mode == '0') {
    n1 = digitalRead(encoder1PinA);
    if ((encoder1PinALast == LOW) && (n1 == HIGH)) {
      if (digitalRead(encoder1PinB) == LOW) {
        encoder1Pos--;
        if (encoder1Pos < 0) {
          encoder1Pos = 0;
        }
        Serial.print(" CW, ");
      } else {
        encoder1Pos++;
        if (encoder1Pos > 180) {
          encoder1Pos = 180;
        }
        Serial.print(" CCW, ");
      }

      // Frequency Monitor
      time1_H = pulseIn(encoder1PinA, HIGH);
      time1_L = pulseIn(encoder1PinA, LOW);
      t_period1 = time1_H + time1_L;
      t_period1 = t_period1 / 1000;
      Frequency1 = 10000 / t_period1;
      //Serial.print(" F = ");
      //Serial.print(Frequency1);
      //Serial.print(" Hz, Pos = ");
      Serial.println(encoder1Pos);
      delay(5);
    }
    encoder1PinALast = n1;

    n2 = digitalRead(encoder2PinA);
    if ((encoder2PinALast == LOW) && (n2 == HIGH)) {
      if (digitalRead(encoder2PinB) == LOW) {
        encoder2Pos--;
        if (encoder2Pos < 0) {
          encoder2Pos = 0;
        }
        Serial.print(" CW, ");
      } else {
        encoder2Pos++;
        if (encoder2Pos > 180) {
          encoder2Pos = 180;
        }
        Serial.print(" CCW, ");
      }

      // Frequency Monitor
      time2_H = pulseIn(encoder2PinA, HIGH);
      time2_L = pulseIn(encoder2PinA, LOW);
      t_period2 = time2_H + time2_L;
      t_period2 = t_period2 / 1000;
      Frequency2 = 10000 / t_period2;
      //Serial.print(" F = ");
      //Serial.print(Frequency1);
      //Serial.print(" Hz, Pos = ");
      Serial.println(encoder2Pos);
      delay(5);
    }
    encoder1PinALast = n2;

    Myservo1.write(encoder1Pos);
    Myservo2.write(encoder2Pos);
  }
  delay(10);
}

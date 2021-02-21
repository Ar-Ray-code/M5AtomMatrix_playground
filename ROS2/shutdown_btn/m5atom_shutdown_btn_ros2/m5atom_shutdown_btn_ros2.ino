#include <ros2arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
WiFiUDP udp;

#include "M5Atom.h"

String ssid;
String pass;
String agent_ip;

bool IMU6886Flag = false;

bool led_flag = 1;

//-------------------
void shutdown_icon();;

void publishInt(std_msgs::Bool* msg, void* arg);
//-------------------


class TwistSub : public ros2::Node
{
  public:
    TwistSub(): Node("m5atom_shutdownBtn")
    {
      ros2::Publisher<std_msgs::Bool>* publisher_ = this->createPublisher<std_msgs::Bool>("btn_msg");
      this->createWallFreq(5, (ros2::CallbackFunc)publishInt, nullptr, publisher_);
    }
};

void publishInt(std_msgs::Bool* msg, void* arg)
{
  (void)(arg);
  shutdown_icon();
  if (M5.Btn.wasPressed())
  {
    led_flag = 0;
    msg->data = 1;
  }
  else{
    msg->data = 0;
  }
}

void shutdown_icon()
{
  if(led_flag)
  {
    M5.dis.clear();
    M5.dis.drawpix(7, 0x00ff00);
  
    M5.dis.drawpix(11, 0x00ff00);
    M5.dis.drawpix(12, 0x00ff00);
    M5.dis.drawpix(13, 0x00ff00);

    M5.dis.drawpix(15, 0x00ff00);
    M5.dis.drawpix(16, 0x00ff00);
    M5.dis.drawpix(17, 0x00ff00);
    M5.dis.drawpix(18, 0x00ff00);
    M5.dis.drawpix(19, 0x00ff00);
    M5.update();
  }
  else
  {
    M5.dis.clear();
    M5.update();
  }
}

void setup()
{
  ssid = "----";
  pass = "----";
  agent_ip = "----";

  M5.begin(true, false, true);
  Serial.begin(115200);
  WiFi.begin(ssid.c_str(), pass.c_str());
  while (WiFi.status() != WL_CONNECTED);
  ros2::init(&udp, agent_ip.c_str(), 2018);

  delay(50);

}

void loop()
{
  static TwistSub SubNode;
  ros2::spin(&SubNode);
}

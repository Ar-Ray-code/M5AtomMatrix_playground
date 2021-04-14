#include <ros2arduino.h>
#include "M5Atom.h"

#define XRCEDDS_PORT  Serial

bool IMU6886Flag = false;
bool led_flag = 1;

//-------------------
void shutdown_icon();
void publishInt(example_interfaces::Bool* msg, void* arg);
//-------------------


class TwistSub : public ros2::Node
{
  public:
    TwistSub(): Node("m5atom_shutdownBtn")
    {
      ros2::Publisher<example_interfaces::Bool>* publisher_ = this->createPublisher<example_interfaces::Bool>("btn_msg");
      this->createWallFreq(5, (ros2::CallbackFunc)publishInt, nullptr, publisher_);
    }
};

void publishInt(example_interfaces::Bool* msg, void* arg)
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
  XRCEDDS_PORT.begin(115200);
  while (!XRCEDDS_PORT); 

  ros2::init(&XRCEDDS_PORT);
  delay(50);

}

void loop()
{
  static TwistSub SubNode;
  ros2::spin(&SubNode);
}

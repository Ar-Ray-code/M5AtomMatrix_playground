#include <Ps3Controller.h>

#include "M5Atom.h"

char mac_address[] = "00:1b:dc:08:d6:d9";
void onConnect(){
  Serial.println("Connected.");
}

void gpio_setup() {
  int pwn_hz = 50;
  int pwm_level = 8;
  pinMode(23,OUTPUT);
  pinMode(33,OUTPUT);

  ledcSetup(0,pwn_hz,pwm_level);
  ledcSetup(1,pwn_hz,pwm_level);

  ledcAttachPin(23,0);
  ledcAttachPin(33,1);
}

void move_2wheel(int spd0, int spd1){
  if(spd0 > 10){
    ledcWrite(0,30);
  }else if(spd0 < -10){
    ledcWrite(0,8);
  }else{
    ledcWrite(0,0);
  }
  
  if(spd1 > 10){
    ledcWrite(1,8);
  }else if(spd1 < -10){
    ledcWrite(1,30);
  }else{
    ledcWrite(1,0);
  }
  Serial.print(spd0);
  Serial.print(",");
  Serial.println(spd1);
}

void setup() {
  M5.begin();
  
  Ps3.attachOnConnect(onConnect);
  Ps3.begin(mac_address);
  Serial.begin(115200);
  gpio_setup();
}

void loop() {
  int spd0, spd1;
  
  if(!Ps3.isConnected())
    return;
        
  float wl = Ps3.data.analog.stick.rx;
  
  float Vx = -1*Ps3.data.analog.stick.lx;
  float Vy = Ps3.data.analog.stick.ly;

  if(abs(Vy) > 5){
    spd0 = Vy;
    spd1 = Vy;
  }
  else{
    spd0 = 0;
    spd1 = 0;
  }
  
  if(abs(Vx) > 5){
    spd0 += Vx/2;
    spd1 += -1*Vx/2;
  }else{
    spd0 += 0;
    spd1 += 0;
  }
  if(spd0 >= 125)   spd0 = 125;
  if(spd0 <= -125)  spd0 = -125;
  if(spd1 >= 125)   spd1 = 125;
  if(spd1 <= -125)   spd1 = -125;
  
  move_2wheel(spd0, spd1);
  
}

#include "esphome.h"

#define SENSOR_CNT 4

class Vaillantx6 : public PollingComponent, public UARTDevice {
 Sensor *xsensor1 {nullptr};
 Sensor *xsensor2 {nullptr};
 Sensor *xsensor3 {nullptr};
 Sensor *xsensor4 {nullptr};

 public:
  Vaillantx6(UARTComponent *parent, Sensor *sensor1, Sensor *sensor2, Sensor *sensor3, Sensor *sensor4) : UARTDevice(parent) , xsensor1(sensor1), xsensor2(sensor2), xsensor3(sensor3), xsensor4(sensor4) {}

  byte cmdGetVersion[7] = {  0x07, 0x02, 0x00, 0x00, 0x00, 0x04, 0xc4 };
  byte vorlaufSet[7]    = {  0x07, 0x00, 0x00, 0x00, 0x19, 0x00, 0xd2 };        //antwort: 1+5 bytes
  byte vorlaufIst[7]    = {  0x07, 0x00, 0x00, 0x00, 0x18, 0x00, 0xd0 };        //antwort: 1+5 bytes
  byte vorlaufSoll[7]   = {  0x07, 0x00, 0x00, 0x00, 0x39, 0x00, 0x92 };       //antwort: 1+4 bytes -> 40
  byte ruecklauf[7]     = {  0x07, 0x00, 0x00, 0x00, 0x98, 0x00, 0xc9 };       //antwort: 1+4 bytes 

  int getParm(byte *cmd, int lcmd) {
    int val;
    write_array(cmd,lcmd);
    delay(1000);
    while(available()<4){}
    if (available()>=4) {
      int len = read();
      int flag = read();
      val  = read()*16 + (read()>>4);
    } else val=0;
    // überflüssige bytes abräumen
    while(available()) {
      int b = read();
    }
    return val;
  }

  void setup() override {
    this->set_update_interval(60000);
  }

  void loop() override {
  }

  void update() override {
    int val=0;
    int b,len,flag;

    val=getParm(vorlaufSoll,sizeof(vorlaufSoll));
    if (xsensor1 != nullptr)   xsensor1->publish_state(val);

    val=getParm(vorlaufIst,sizeof(vorlaufIst));
    if (xsensor2 != nullptr)   xsensor2->publish_state(val);

    val=getParm(vorlaufSet,sizeof(vorlaufSet));
    if (xsensor3 != nullptr)   xsensor3->publish_state(val);

    val=getParm(ruecklauf,sizeof(ruecklauf));
    if (xsensor4 != nullptr)   xsensor4->publish_state(val);

  }
};

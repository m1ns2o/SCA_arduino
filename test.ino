#include <SoftwareSerial.h>
//#include <SimpleTimer.h>

#define tx 2
#define rx 3
#define key 1 // 안드에서 요청 보내는 값

SoftwareSerial BTSerial(tx, rx);
void setup() {
    BTSerial.begin(9600);
    Serial.begin(9600);
}
int delta=1000, _time=10;

void loop() {
  int inp;

//  BTSerial.write(_time); 
  if(BTSerial.available()){
    inp = BTSerial.read();
    Serial.write(inp);
    //Serial.println(inp==49); //# 바이너리값 1==49
    if(inp == 49){
     
      BTSerial.write(_time); //#사용시간
      //  BTSerial.print(_time); 
      BTSerial.write(delta); //#마우스 이동량 (움직인 거리)
      Serial.println(_time); //#사용시간
      Serial.println(delta); //#마우스 이동량 (움직인 거리)
    }
  }
  
}
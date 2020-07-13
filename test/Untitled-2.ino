#include <SoftwareSerial.h>
//#include <SimpleTimer.h>
#include <MsTimer2.h>
////#include <Timer.h>
//
//SimpleTimer timer;


#define tx 2
#define rx 3
#define key 1 // 안드에서 요청 보내는 값

#define RU A1
#define RD A2
#define LU A3
#define LD A4
#define wrist A0

#define vibrate 4
#define Interval 1000

//SimpleTimer timer;

SoftwareSerial BTSerial(tx,rx);


int delta, _time=1, tt;
int sequential = 0;
bool status = 0;

int delta_pos(int RU, int RD, int LU, int LD){
    String data = "pos_"+String(RU)+" "+String(RD)+" "+String(LU)+" "+String(LD)+"\r";
    BTSerial.print(data);
    //////////////Serial.println(data);
    delay(100);
  // return delta;  
}

int count_time(){
  sequential = ++_time;
//  tt = _time;
  ////////Serial.println(_time);
  return _time;
}

void data_send(){
    String _t = "time_"+String(_time/10)+"\r";
//    String _d = "delta_"+String(delta)+"\r";
    BTSerial.print(_t); //#사용시간
    //////Serial.println(_t);
    //  BTSerial.print(_time); 
//    BTSerial.print(_d); //#마우스 이동량 (움직인 거리)
}



void setup() {
  MsTimer2::set(Interval, count_time);
    BTSerial.begin(9600);
    Serial.begin(9600);
//  timer.setInterval(1000);
//    timer.setInterval(1000, data_send);
//    timer.run();
  pinMode(vibrate, OUTPUT);
//  timer.run();
}


void loop() {
  int _press;
  int rRU, rRD, rLU, rLD;

  _press = analogRead(wrist);
  //////Serial.println(_press);
  
  if(_press > 200){
    MsTimer2::start();
    status = 1;
    if(sequential > 30){
      digitalWrite(vibrate, HIGH);
      sequential = 0;
      //////Serial.println("vibrate_true");
    }
    if(_press > 400){
      digitalWrite(vibrate, HIGH);
      //////Serial.println("alert");
      BTSerial.print("alert");
    }
    rRU = analogRead(RU);
    rRD = analogRead(RD);
    rLU = analogRead(LU);
    rLD = analogRead(LD);
//    Serial.print("TIME:");
//    //////Serial.println(_time);
    delta_pos(rRU, rRD, rLU, rLD);
    data_send();
    delay(17);
    _time++;
    sequential++;  
    
  }
  // 사용중


  else if(status){
//    tt = count_time();
//    MsTimer2::stop();
    if(sequential>100){
      digitalWrite(vibrate, HIGH);
      sequential = 0;
      //////Serial.println("vibrate_true");
    }
    status = 0;
  }
  // 사용 종료


  
}
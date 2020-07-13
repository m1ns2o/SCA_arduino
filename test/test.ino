#include <SoftwareSerial.h>
// #include <SimpleTimer.h>
#include <MsTimer2>


#define tx 2
#define rx 3
#define key 1 // 안드에서 요청 보내는 값

#define RU A1
#define RD A2
#define LU A3
#define LD A4
#define wrist A0

#define vibrate 4
#define Interval 60000


SoftwareSerial BTSerial(tx,rx);


int delta, _time=0;
int sequential = 0;
bool status = 0;

void delta_movement(int RU, int RD, int LU, int LD){
	if(RU+RL > LU+LD){
		if((RU+LU) > (RD+RU)){

		}
		else{
			
		}
	}

	else{
		if((RU+LU) > (RD+RU)){

		}
		else{

		}
	}
	// return delta;  
}

int count_time(){
	sequential = ++_time;
	return _time;
}

void data_send(int inp){
    Serial.write(inp);
    if(inp == 49){
		BTSerial.print(_time); //#사용시간
		//  BTSerial.print(_time); 
		BTSerial.print(delta); //#마우스 이동량 (움직인 거리)
		_time = delta = 0;
    }
}



void setup() {
	MsTimer2::set(Interval, count_time);
    BTSerial.begin(9600);
    Serial.begin(9600);
	pinMode(vibrate, OUTPUT);
}


void loop() {
	int inp, press;
	if(BTSerial.available()){
		inp = BTSerial.read();
		data_send(inp);
	}
	//전송
	press = analogRead(wrist)
	if(press > 300){
		MsTimer2::start();
		status = 1;
		if(sequential > 30){
			digitalWrite(vibrate, HIGH);
			sequential = 0;
			Serial.println("vibrate_true");
		}
		if(press > 600){
			digitalWrite(vibrate, HIGH);
			Serial.println("vibrate_true");
			BTSerial.print(9)
		}
		
		delta_movement(RU, RD, LU, LD);
	}
	// 사용중


	else if(status){
		MsTimer2::stop();
		sequential = 0;
		status = 0;
	}
	// 사용 종료


	
}
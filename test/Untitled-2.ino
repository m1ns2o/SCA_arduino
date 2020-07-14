#include <SoftwareSerial.h>
#include <MsTimer2.h>

#define tx 2
#define rx 3

#define RU A1
#define RD A2
#define LU A3
#define LD A4
#define wrist A0

#define vibrate 4
#define Interval 1000



SoftwareSerial BTSerial(tx, rx);

int delta, _time = 1, tt;
int sequential = 0;
bool status = 0;

int delta_pos(int RU, int RD, int LU, int LD)
{
    String data = "pos_" + String(RU) + " " + String(RD) + " " + String(LU) + " " + String(LD) + "\r";
    BTSerial.print(data);
    delay(100);
}

int count_time()
{
    sequential = ++_time;
    return _time;
}

void data_send()
{
    String _t = "time_" + String(_time / 10) + "\r";
    BTSerial.print(_t); //#사용시간
}

void setup()
{
    MsTimer2::set(Interval, count_time);
    BTSerial.begin(9600);
    Serial.begin(9600);
    pinMode(vibrate, OUTPUT);
    digitalWrite(vibrate, HIGH);
}

void loop()
{
    int _press;
    int rRU, rRD, rLU, rLD;

    _press = analogRead(wrist);

    if (_press > 200)
    {
        MsTimer2::start();
        status = 1;
        if (sequential > 30)
        {
            digitalWrite(vibrate, LOW);
            delay(400);
            digitalWrite(vibrate, HIGH);
            sequential = 0;

        }

        if (_press > 500)
        {
            digitalWrite(vibrate, LOW);
            delay(400);
            digitalWrite(vibrate, HIGH);
            Serial.println("alert");
            BTSerial.print("alert");
        }
        rRU = analogRead(RU);
        rRD = analogRead(RD);
        rLU = analogRead(LU);
        rLD = analogRead(LD);
        delta_pos(rRU, rRD, rLU, rLD);
        data_send();
        delay(17);
        _time++;
        sequential++;
    }
    // 사용중

    else if (status)
    {
        if (sequential > 100)
        {
            digitalWrite(vibrate, HIGH);
            sequential = 0;
        }
        status = 0;
    }
    // 사용 종료
}
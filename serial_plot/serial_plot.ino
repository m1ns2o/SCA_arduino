void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("RU, RD, LU,LD");

//출처: https://it-g-house.tistory.com/entry/Arduino-아두이노로-그래프graph-그리기 [IT-G-House]
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(A1));Serial.print(",");
  Serial.print(analogRead(A2));Serial.print(",");
  Serial.print(analogRead(A3));Serial.print(",");
  Serial.println(analogRead(A4));
  delay(10);
}

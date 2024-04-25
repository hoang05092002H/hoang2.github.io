#include <ArduinoJson.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#define sensor A0
#define sensor1 A1
#define sensor2 A2
#define sensor3 A3
#define sensor4 DD7
#define sensor5 DD4
#define RX_PIN  10
#define TX_PIN 11
int pre = HIGH;
int pre1 = HIGH;
int pre2 = HIGH;
int pre3 = HIGH;
int pre4 = HIGH;
int pre5 = HIGH;
unsigned int gtcb,gtcb1,gtcb2,gtcb3,gtcb4,gtcb5;
unsigned int sl1,sl2,sl3,ct1,ct2,ct3;
int tt1,tt2,tt3;
Servo servo;
Servo servo1;
Servo servo2;
String Data;
//int pos,pos1,pos2,pos3,pos4,pos5;
SoftwareSerial mySerial(RX_PIN,TX_PIN);
LiquidCrystal_I2C lcd(0x27,20,4);
void dieu_khien()
{
  gtcb=digitalRead(sensor);
  gtcb1=digitalRead(sensor1);
  gtcb2=digitalRead(sensor2);
  gtcb3=digitalRead(sensor3);
  gtcb4=digitalRead(sensor4);
  gtcb5=digitalRead(sensor5);
  if (gtcb == LOW && pre == HIGH)
  { 
    if (sl1 >9)
  {
    pre = LOW;
    tt1=0;
    truyen_uart();
    lcd.setCursor(3,3);
    lcd.print("DAY");
  }
  else {
    //Serial.println("BAI 1 VAO");
    servo.write(90);
    delay(3000);
    servo.write(180);
    sl1=sl1+1;
    ct1=ct1-1;
    tt1=1;
    truyen_uart();
    lcd.setCursor(3,3);
    lcd.print("VAO");
    delay(3000);
    lcd.setCursor(3,3);
    lcd.print("   ");
  
  }
  }
  
  if (gtcb1 == LOW && pre1 == HIGH)
  { 
    if (sl1 == 0)
  {
    pre1 = LOW;
    tt1=0;
    truyen_uart();
    lcd.setCursor(3,3);
    lcd.print("   ");
  }
  else {
     //Serial.println("BAI 1 RA");
    servo.write(90);
    delay(3000);
    servo.write(180);
    sl1=sl1-1;
    ct1=ct1+1;
    tt1=1;
    truyen_uart();
    mySerial.println(Data);
    lcd.setCursor(3,3);
    lcd.print("RA ");
    delay(3000);
    lcd.setCursor(3,3);
    lcd.print("   ");
   
  }
  }
    if (gtcb2 == LOW && pre2 == HIGH)
  {
    if (sl2 >9)
  {
    pre2 = LOW;
    tt2=0;
    truyen_uart(); 
    lcd.setCursor(10,3);
    lcd.print("DAY");
  }
  else{ 
     servo1.write(90);
    delay(3000);
    servo1.write(180); 
    sl2=sl2+1;
    ct2=ct2-1;
    tt2=1;
    truyen_uart();
    lcd.setCursor(10,3);
    lcd.print("VAO");
    delay(3000);
    lcd.setCursor(10,3);
    lcd.print("   ");
  }
  }
  if (gtcb3 == LOW && pre3 == HIGH)
  { 
    if (sl2 == 0)
  {
    pre3=LOW;
    tt2=0;
    truyen_uart();
    lcd.setCursor(10,3);
    lcd.print("   ");
  }
  else {
     //Serial.println("BAI 2 RA");
     servo1.write(90);
    delay(3000);
    servo1.write(180);
    sl2=sl2-1;
    ct2=ct2+1;
       tt2=1;
    truyen_uart();
    lcd.setCursor(10,3);
    lcd.print("RA ");
    delay(3000);
    lcd.setCursor(10,3);
    lcd.print("   ");
  }
  }
  if (gtcb4 == LOW && pre4 == HIGH)
  { 
    if (sl3 >9)
  {
    pre4=LOW;
    tt3=0;
    truyen_uart();
    lcd.setCursor(17,3);
    lcd.print("DAY");
  }
  else {
    //Serial.println("BAI 3 VAO");
    servo2.write(90);
    delay(3000);
    servo2.write(180);
    sl3=sl3+1;
    ct3=ct3-1;
    tt3=1;
    truyen_uart();
    lcd.setCursor(17,3);
    lcd.print("VAO");
    delay(3000);
    lcd.setCursor(17,3);
    lcd.print("   ");
  }
  }
  if (gtcb5 == LOW && pre5 == HIGH)
  { 
    if (sl3 == 0 )
  {
    pre5= LOW;
    tt3=0;
    truyen_uart();
    lcd.setCursor(17,3);
    lcd.print("   ");
  }else{
    //Serial.println("BAI 3 RA");
    servo2.write(90);
    delay(3000);
    servo2.write(180);
    sl3=sl3-1;
    ct3=ct3+1;
    tt3=1;
    truyen_uart();
    lcd.setCursor(17,3);
    lcd.print("RA ");
    delay(3000);
    lcd.setCursor(17,3);
    lcd.print("   ");
  }
  }
  tt2=0;
  tt1=0;
  tt3=0;
  pre=gtcb;
  pre1=gtcb1;
  pre2=gtcb2;
  pre3=gtcb3;
  pre4=gtcb4;
  pre5=gtcb5;
}
void hien_thi()
{
  lcd.setCursor(3,1);
  lcd.print((sl1/10));
  lcd.print((sl1%10));
  lcd.setCursor(3,2);
  lcd.print ((ct1/10));
  lcd.print ((ct1%10));
  lcd.setCursor(10,1);
  lcd.print((sl2/10));
  lcd.print((sl2%10));
  lcd.setCursor(10,2);
  lcd.print ((ct2/10));
  lcd.print ((ct2%10));
  lcd.setCursor(17,1);
  lcd.print((sl3/10));
  lcd.print((sl3%10));
  lcd.setCursor(17,2);
  lcd.print ((ct3/10));
  lcd.print ((ct3%10));

}
void truyen_uart()
{
    Data = String(sl1)+";"+String(ct1)+";"+String(sl2)+";"+String(ct2)+";"+String(sl3) + ";"+String(ct3) + ";"+String(tt1)+";"+String(tt2)+";"+String(tt3); 
    mySerial.println(Data);
}

void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);
  lcd.init();
  Wire.begin();
  lcd.backlight();
  pinMode(sensor,INPUT);
  pinMode(sensor1,INPUT);
  pinMode(sensor2,INPUT);
  pinMode(sensor3,INPUT);
  pinMode(sensor4,INPUT);
  pinMode(sensor5,INPUT);
  lcd.clear();
 truyen_uart();
 servo.attach(3);
 servo1.attach(9);
 servo2.attach(6);
servo.write(180);
servo1.write(180);
servo2.write(180);
  sl1=00;
  sl2=00;
  sl3=00;
  ct1=10;
  ct2=10;
  ct3=10;
  tt2=0;
  tt1=0;
  tt3=0;
  lcd.setCursor(0, 0);
  lcd.print("--------------------");
  lcd.setCursor(0, 1);
  lcd.print(" TRAN LE NHAT HOANG ");
  lcd.setCursor(0, 2);
  lcd.print("  MSSV: 20161318    ");
  lcd.setCursor(0, 3);
  lcd.print("--------------------");
  delay(3300);
  lcd.setCursor(0, 1);
  lcd.print("    Do an mon hoc   ");
  lcd.setCursor(0, 2);
  lcd.print(" Nha xe thong minh  ");
  delay(3300);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BAI 1");
  lcd.setCursor(7,0);
  lcd.print("BAI 2");
  lcd.setCursor(14,0);
  lcd.print("BAI 3");
  lcd.setCursor(0,1);
  lcd.print("SL:");
  lcd.setCursor(0,2);
  lcd.print("CT:");
  lcd.setCursor(0,3);
  lcd.print("TT:");
  lcd.setCursor(7,1);
  lcd.print("SL:");
  lcd.setCursor(7,2);
  lcd.print("CT:");
  lcd.setCursor(7,3);
  lcd.print("TT:");
  lcd.setCursor(14,1);
  lcd.print("SL:");
  lcd.setCursor(14,2);
  lcd.print("CT:");
  lcd.setCursor(14,3);
  lcd.print("TT:");

}

void loop() {


  dieu_khien();
  hien_thi();

}

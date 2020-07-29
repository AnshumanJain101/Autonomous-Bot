
                                     #include <LiquidCrystal.h>
                                     LiquidCrystal lcd(12,13,5,4,3,2);
                                     //connect these respectively to LED's 4,6,11,12,13,14
  int angle_trav=0;
  float distance=0;
  int count=0;//to count even nodes
  int count1=0;//to count total no of true nodes
const int sensor[5]={A5,A4,A3,A2,A1};
    int rm1=8;
    int rm2=9;
    int lm1=10;
    int lm2=11;
    int magic1=25;
    int magic2=26;
    int sens_reading[5];







void setup() {
  pinMode(rm1,OUTPUT);
pinMode(lm2,OUTPUT);
pinMode(lm1,OUTPUT);
pinMode(rm2,OUTPUT);
pinMode(magic1,OUTPUT);
pinMode(magic2,OUTPUT);

                     pinMode(31,INPUT);//0
                     pinMode(32,INPUT);//1
                     pinMode(33,INPUT);//2
                     pinMode(34,INPUT);//3 and the bottom one is fourth
                     pinMode(35,INPUT);                  pinMode(36,INPUT);pinMode(37,INPUT);//dono left wale aur right wale aage


pinMode(22,INPUT);//22 wala parallele mai hoga
lcd.begin(16,2);analogWrite(6,100);

                  Serial.begin(9600);

}

void loop() {

        int aagel=digitalRead(28);
        int fl=digitalRead(4);
        int sl=digitalRead(6);
        int m=digitalRead(5);
        int sr=digitalRead(2);
        int fr=digitalRead(3);
        int aageR=digitalRead(29);
        int wheel_sensor=digitalRead(7);
        if(m==LOW)
        {
                                         digitalWrite(rm1,HIGH);
                                         digitalWrite(rm2,LOW);
                                         analogWrite(magic1,128);
                                         digitalWrite(lm1,HIGH);
                                         digitalWrite(lm2,LOW);
                                         analogWrite(magic2,128);

        }
        
        if(m==LOW && aageR==LOW&&aagel==LOW&&fl==HIGH&&fr==HIGH&&sl==HIGH&&sr==HIGH)
  {
                                         digitalWrite(rm1,HIGH);
                                         digitalWrite(rm2,LOW);
                                         analogWrite(magic1,128);
                                         digitalWrite(lm1,HIGH);
                                         digitalWrite(lm2,LOW);
                                         analogWrite(magic2,128);

    lcd.setCursor(5,0);
    lcd.print("FALSE");
    delay(1000);
  }
  lcd.clear();
  if(m==HIGH&& aageR==LOW&&aagel==LOW&&fl==HIGH&&fr==HIGH&&sl==HIGH&&sr==HIGH)
  {
                                         digitalWrite(rm1,HIGH);
                                         digitalWrite(rm2,LOW);
                                         analogWrite(magic1,128);
                                         digitalWrite(lm1,HIGH);
                                         digitalWrite(lm2,LOW);
                                         analogWrite(magic2,128);

    count1++;
    lcd.setCursor(6,0);
    lcd.print("TRUE");
    lcd.setCursor(8,1);
    lcd.print(count1);
    delay(1000);
    count++;
  
  }
                       if(wheel_sensor==HIGH&&count==1)
                       {
                         angle_trav=angle_trav+20;
                       }
                       if(count==2)
                       {
                         distance=(angle_trav*3.5*3.14/180)+3;
                       }
  
  lcd.clear();
  if(m==LOW&& aageR==LOW&&aagel==LOW&&fl==LOW&&fr==LOW&&sl==LOW&&sr==LOW)
  {
                                         digitalWrite(rm1,LOW);
                                         digitalWrite(rm2,LOW);
                                         analogWrite(magic1,0);
                                         digitalWrite(lm1,LOW);
                                         digitalWrite(lm2,LOW);
                                         analogWrite(magic2,0);

    lcd.setCursor(4,0);
    lcd.print("FINISH");
    lcd.setCursor(2,1);
    lcd.print(count1);
    lcd.setCursor(8,1);
    lcd.print(distance);
     
  }
  



  

}

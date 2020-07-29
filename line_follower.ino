  int n=5;
  int rm1=5;
  int rm2=6;
  int lm1=3;
  int lm2=4;
  int magic1=7;//right
  int magic2=2;//left
  int sens_reading[5];
  const int sensor[5]={33,35,37,39,41};
  int right=1;
  int left=0;
  int button=7;
  int motor_speed=90;
  float kp=40;
  int i;
  int sens_value[5];
  float last_line_pos=0;
  float line_pos=0;
  int ls=31;//why digital read there
  int rs=43;
  int turn_speed=120;
  void setup() {
    // put your setup code here, to run once:
  pinMode(36,INPUT);
  pinMode(38,INPUT);
  pinMode(40,INPUT);
  pinMode(42,INPUT);
  pinMode(44,INPUT);
  pinMode(34,INPUT);
  pinMode(rs,INPUT);
  pinMode(ls,INPUT);
  
  
  pinMode(rm1,OUTPUT);
  pinMode(lm2,OUTPUT);
  pinMode(lm1,OUTPUT);
  pinMode(rm2,OUTPUT);
  pinMode(magic1,OUTPUT);
  pinMode(magic2,OUTPUT);
  //pinMode(button,OUTPUT);
  Serial.begin(9600);
  
  
  
  
  
  }

void loop() {

for(i=0;i<5;i++)  
 sens_reading[i]=digitalRead(sensor[i]);
  // put your main code here, to run repeatedly:
int ls1=digitalRead(ls);
int rs1=digitalRead(rs);
if(ls1==HIGH&&rs1==HIGH&&(sens_reading[0]==LOW||sens_reading[1]==LOW||sens_reading[2]==LOW||sens_reading[3]==LOW||sens_reading[4]==LOW))
{
Serial.println("Forward");
int error=calculate_error();
float correction=pid_correction(error,kp);
pid(correction);
}
//right
if(rs1==LOW && ls1==HIGH &&sens_reading[0]==HIGH&&sens_reading[1]==HIGH&&sens_reading[2]==HIGH&&sens_reading[3]==HIGH&&sens_reading[4]==HIGH)
{motorSpeed(turn_speed,-turn_speed);
Serial.println("RIGHT");
}
if(rs1==LOW && ls1==HIGH &&sens_reading[0]==HIGH&&sens_reading[1]==HIGH&&sens_reading[2]==HIGH&&sens_reading[3]==HIGH&&sens_reading[4]==LOW)
{motorSpeed(turn_speed,-turn_speed);
Serial.println("RIGHT");
}
if(rs1==LOW && ls1==HIGH &&sens_reading[0]==HIGH&&sens_reading[1]==HIGH&&sens_reading[2]==HIGH&&sens_reading[3]==LOW&&sens_reading[4]==LOW)
{motorSpeed(turn_speed,-turn_speed);
Serial.println("RIGHT");
}
if(rs1==LOW && ls1==HIGH &&sens_reading[0]==HIGH&&sens_reading[1]==HIGH&&sens_reading[2]==LOW&&sens_reading[3]==LOW&&sens_reading[4]==LOW)
{motorSpeed(turn_speed,-turn_speed);
Serial.println("RIGHT");
}
if(rs1==LOW && ls1==HIGH &&sens_reading[0]==HIGH&&sens_reading[1]==LOW&&sens_reading[2]==LOW&&sens_reading[3]==LOW&&sens_reading[4]==LOW)
{motorSpeed(turn_speed,-turn_speed);
Serial.println("RIGHT");
}

//left
if(ls1==LOW &&rs1==HIGH&&sens_reading[0]==HIGH&&sens_reading[1]==HIGH&&sens_reading[2]==HIGH&&sens_reading[3]==HIGH&&sens_reading[4]==HIGH){
motorSpeed(-turn_speed,turn_speed);
Serial.println("");
}

if(ls1==LOW &&rs1==HIGH&&sens_reading[0]==LOW&&sens_reading[1]==HIGH&&sens_reading[2]==HIGH&&sens_reading[3]==HIGH&&sens_reading[4]==HIGH){
motorSpeed(-turn_speed,turn_speed);
}
if(ls1==LOW &&rs1==HIGH&&sens_reading[0]==LOW&&sens_reading[1]==LOW&&sens_reading[2]==HIGH&&sens_reading[3]==HIGH&&sens_reading[4]==HIGH){
motorSpeed(-turn_speed,turn_speed);
}
if(ls1==LOW &&rs1==HIGH&&sens_reading[0]==LOW&&sens_reading[1]==LOW&&sens_reading[2]==LOW&&sens_reading[3]==HIGH&&sens_reading[4]==HIGH){
motorSpeed(-turn_speed,turn_speed);
}






else if(ls1==LOW &&rs1==LOW){              
motorSpeed(-turn_speed,turn_speed);
Serial.println("ALL BLACK");
}
else if(ls1==HIGH && rs1==HIGH && sens_reading[0]==HIGH&&sens_reading[1]==HIGH && sens_reading[2]==HIGH && sens_reading[3]==HIGH&&sens_reading[4]==HIGH)
{
motorSpeed(-turn_speed,turn_speed);
Serial.println("ALL WHITE");
}


//motorSpeed(-150,-150);

}
void motorSpeed(int m1,int m2)
{
int left_motorspeed=abs(m1);
int right_motorspeed=abs(m2);

if(m1>0 && m2>0)
{
digitalWrite(rm1,HIGH);
digitalWrite(rm2,LOW);
analogWrite(magic1,right_motorspeed);
digitalWrite(lm1,HIGH);
digitalWrite(lm2,LOW);
analogWrite(magic2,left_motorspeed);
}
if(m1<0 && m2>0)
{
digitalWrite(rm1,HIGH);
digitalWrite(rm2,LOW);
analogWrite(magic1,right_motorspeed);
digitalWrite(lm1,LOW);
digitalWrite(lm2,HIGH);
analogWrite(magic2,left_motorspeed);
}
if(m1>0 && m2<0)
{
digitalWrite(rm1,LOW);
digitalWrite(rm2,HIGH);
analogWrite(magic1,right_motorspeed);
digitalWrite(lm1,HIGH);
digitalWrite(lm2,LOW);
analogWrite(magic2,left_motorspeed);
}  
if(m1<0 && m2<0)
{
digitalWrite(rm2,HIGH);
digitalWrite(rm1,LOW);
analogWrite(magic1,right_motorspeed);
digitalWrite(lm2,HIGH);
digitalWrite(lm1,LOW);
analogWrite(magic2,left_motorspeed);
}
if(m1==0 && m2>0)
{
digitalWrite(rm1,HIGH);
digitalWrite(rm2,LOW);
analogWrite(magic1,right_motorspeed);
digitalWrite(lm1,LOW);
digitalWrite(lm2,LOW);
analogWrite(magic2,0);
}
if(m1>0 && m2==0)
{
digitalWrite(rm1,LOW);
digitalWrite(rm2,LOW);
analogWrite(magic1,0);
digitalWrite(lm1,HIGH);
digitalWrite(lm2,LOW);
analogWrite(magic2,left_motorspeed);
}
}

int calculate_error(){

for(i=0;i<5;i++)  
 sens_reading[i]=digitalRead(sensor[i]);
int error=0;
if(sens_reading[0]==HIGH&&sens_reading[1]==HIGH&&sens_reading[2]==HIGH&&sens_reading[3]==HIGH&&sens_reading[4]==LOW)
error=4;
else if(sens_reading[0]==HIGH&&sens_reading[1]==HIGH&&sens_reading[2]==HIGH&&sens_reading[3]==LOW&&sens_reading[4]==LOW)
error=3; 
else if(sens_reading[0]==HIGH&&sens_reading[1]==HIGH&&sens_reading[2]==HIGH&&sens_reading[3]==LOW&&sens_reading[4]==HIGH)
error=2;
if(sens_reading[0]==HIGH&&sens_reading[1]==HIGH&&sens_reading[2]==LOW&&sens_reading[3]==LOW&&sens_reading[4]==HIGH)
error=1;
if(sens_reading[0]==HIGH&&sens_reading[1]==HIGH&&sens_reading[2]==LOW&&sens_reading[3]==HIGH&&sens_reading[4]==HIGH)
error=0;
if(sens_reading[0]==HIGH&&sens_reading[1]==LOW&&sens_reading[2]==LOW&&sens_reading[3]==HIGH&&sens_reading[4]==HIGH)
error=-1;
if(sens_reading[0]==HIGH&&sens_reading[1]==LOW&&sens_reading[2]==HIGH&&sens_reading[3]==HIGH&&sens_reading[4]==HIGH)
error=-2;
if(sens_reading[0]==LOW&&sens_reading[1]==LOW&&sens_reading[2]==HIGH&&sens_reading[3]==HIGH&&sens_reading[4]==HIGH)
error=-3;
if(sens_reading[0]==LOW&&sens_reading[1]==HIGH&&sens_reading[2]==HIGH&&sens_reading[3]==HIGH&&sens_reading[4]==HIGH)
error=-4;

return error;
}


float pid_correction(int error,float kp)
{
float proportional=kp*float(error);  
  
float correction=proportional;  
return correction;
}

float pid(float correction)
{
if(correction>0)
motorSpeed(motor_speed,motor_speed-correction);
else
motorSpeed(motor_speed+correction,motor_speed);  
}

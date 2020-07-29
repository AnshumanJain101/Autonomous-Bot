#include<NewPing.h>

#define Max_dist 45

#define tp1 30   //1-left sensor

#define ep1 32

#define tp2 38   //2-front sensor

#define ep2 40

#define tp3  36     //3-right sensor

#define ep3  34

#define LM1 3

#define LM2 4

#define RM1 5

#define RM2 6 

#define magicpin1 2    //left motor
    
#define magicpin2  7    //right motor

float rfront=0;      //initial

float rlwall=0;

float rrwall=0;

float minwall=9.0;

float maxwall=20.0;

float mfront=28.0;

NewPing sonar[3]={NewPing(tp1,ep1,Max_dist),NewPing(tp2,ep2,Max_dist),NewPing(tp3,ep3,Max_dist)}; 
int rhash=0;
int lhash=0;
int turn_speed=80;
void setup()

{
  Serial.begin(9600);     

  pinMode(LM1,OUTPUT);

  pinMode(LM2,OUTPUT);

  pinMode(RM1,OUTPUT);

  pinMode(RM2,OUTPUT);
  
  //pinMode(magicpin1,OUTPUT);
  
  //pinMode(magicpin2,OUTPUT);

  pinMode(tp1,OUTPUT);

  pinMode(ep1,INPUT);

  pinMode(tp2,OUTPUT);

  pinMode(ep2,INPUT);

  pinMode(tp3,OUTPUT);

  pinMode(ep3,INPUT);
  
}

void loop()
{
  digitalWrite(tp1,HIGH);
  digitalWrite(tp2,HIGH);
  digitalWrite(tp3,HIGH);
  
  
  rlwall=lsensor();
  Serial.print(rlwall);
  Serial.print(" :left sensor ");
  Serial.println();
  rfront=fsensor();
  Serial.print(rfront);
  Serial.print(" :front sensor ");
  Serial.println();
  rrwall=rsensor();
  Serial.print(rrwall);
  Serial.print(" :right sensor ");
  Serial.println();





  
  /*------------------Start--------------------*/
  
  if(rfront>mfront || rfront==0)                                   /*no front wall*/
  {
  
    if(rlwall!=0 && rrwall==0)
    {
      lhash=1;
      rhash=0;
      if(rlwall>minwall && rlwall<maxwall)
      {
        forward();
        Serial.print(" move forward ");
        Serial.println();
      }
      else if(rlwall<minwall)
      {
        right();
        delay(25);
        forward();
        Serial.print("take slight right and then move forward");
        Serial.println();
      }
      else if(rlwall>maxwall)
      {
        left();
        delay(25);
        forward();
        Serial.print("take slight left and then move forward");
        Serial.println();
      }
    }
    else if(rlwall==0 && rrwall!=0)
    {
      rhash=1;
      lhash=0;
      if(rrwall>minwall && rrwall<maxwall)
      {
        forward();
        Serial.print(" move forward ");
        Serial.println();
      }
      else if(rrwall<minwall)
      {
        left();
        delay(25);
        forward();
        Serial.print(" take slight left and then move forward ");
        Serial.println();
      }
      else if(rrwall>maxwall)
      {
        right();
        delay(25);
        forward();
        Serial.print(" take slight left and then move forward ");
        Serial.println();
      }
    }
    else if(rlwall!=0 && rrwall!=0)
    {
      if(rlwall<minwall)
      {
        right();
        delay(25);
        forward();
        Serial.print("take slight right and then move forward");
        Serial.println();
      }
      else if(rrwall<minwall)
      {
        left();
        delay(25);
        forward();
        Serial.print(" take slight left and then move forward ");
        Serial.println();
      }
      else 
      {
        forward();
        Serial.print(" move forward ");
        Serial.println();
      }
    }
    else if(rlwall==0 && rrwall==0)              /*blind spot*/
    {
      if(rhash==0 && lhash==1)
      {
        
        analogWrite(LM1, 90);

        analogWrite(LM2, 0);

        analogWrite(RM1, 90);

        analogWrite(RM2, 0);
        analogWrite(magicpin1,90);
        analogWrite(magicpin2,90);
        
        delay(25);
        
        analogWrite(LM1, 0);

        analogWrite(LM2, 100);

        analogWrite(RM1, 100);

        analogWrite(RM2, 0);
        analogWrite(magicpin1,100);
        analogWrite(magicpin2,100);
        
        delay(75);
        
        analogWrite(LM1, 90);

        analogWrite(LM2, 0);

        analogWrite(RM1, 90);

        analogWrite(RM2, 0);
        analogWrite(magicpin1,90);
        analogWrite(magicpin2,90);
        
        delay(50);
        Serial.print(" blind spot=left ");
        Serial.println();
      }
      else if(rhash==1 && lhash==0)
      {
        
        analogWrite(LM1, 90);

        analogWrite(LM2, 0);

        analogWrite(RM1, 90);

        analogWrite(RM2, 0);
        analogWrite(magicpin1,90);
        analogWrite(magicpin2,90);
        
        delay(25);
        
        analogWrite(LM1, 100);

        analogWrite(LM2, 0);

        analogWrite(RM1, 0);

        analogWrite(RM2, 100);
        analogWrite(magicpin1,100);
        analogWrite(magicpin2,100);
        
        delay(75);
        
        analogWrite(LM1, 90);

        analogWrite(LM2, 0);

        analogWrite(RM1, 90);

        analogWrite(RM2, 0);

        analogWrite(magicpin1,90);
        analogWrite(magicpin2,90);
        
        delay(50);
        Serial.print(" blind spot=right ");
        Serial.println();
      }
    }
  }
  else if(rfront<mfront)                              /* if front wall is present*/
  {
    delay(25);
    if(rlwall!=0 && rrwall==0)
    {
      if((rlwall>minwall && rlwall<maxwall) || (rlwall<minwall) || (rlwall>maxwall))
      {
        power_right();
        delay(220);
        Serial.print(" power_right ");
        Serial.println();
      }
    }
    else if(rlwall==0 && rrwall!=0)
    {
      if((rrwall>minwall && rrwall<maxwall) || (rrwall<minwall) || (rrwall>maxwall))
      {
        power_left();
        delay(220);
        Serial.print(" power_left ");
        Serial.println();
      }
    }
    /*else if(rlwall==0 && rrwall==0)        //in exceptional case, power_right is given priority over power_left
    {
      power_right();
      delay(220);
      Serial.print(" power_right ");
      Serial.println();
    }*/
  }
}  


/*------------motor--------------*/

void stop_hulk()               //for stopping the bot
{
    digitalWrite(LM1, 0);

    digitalWrite(LM2, 0);

    digitalWrite(RM1, 0);

    digitalWrite(RM2, 0);
  
}
void forward()                   //for forward movement
{
    analogWrite(LM1, turn_speed);

    analogWrite(LM2, 0);

    analogWrite(RM1, turn_speed);

    analogWrite(RM2, 0);
  
  analogWrite(magicpin1,80);
  
  analogWrite(magicpin2,80);
}

void backward()                //for backward movement
{
    analogWrite(LM1, 0);

    analogWrite(LM2, turn_speed);

    analogWrite(RM1, 0);

    analogWrite(RM2, turn_speed);
  
  analogWrite(magicpin1,80);
  
  analogWrite(magicpin2,80);
}

void right()                  //for turning right 
{
    analogWrite(LM1, turn_speed);

    analogWrite(LM2, 0);

    analogWrite(RM1, 0);

    analogWrite(RM2, 0);
  
  analogWrite(magicpin1,80);
  
  analogWrite(magicpin2,0);
}

void left()                  //for turning left
{
    analogWrite(LM1, 0);

    analogWrite(LM2, 0);

    analogWrite(RM1, turn_speed);

    analogWrite(RM2, 0);
  
  analogWrite(magicpin1,0);
  
  analogWrite(magicpin2,80);
}
void power_right()         //power right the bot at junction
{
 
    analogWrite(LM1, 110);

    analogWrite(LM2, 0);

    analogWrite(RM1, 0);

    analogWrite(RM2, 110); 
  
  analogWrite(magicpin1,110);
  
  analogWrite(magicpin2,110);
}
void power_left()          //power left the bot at junction
{
    analogWrite(LM1, 0);

    analogWrite(LM2, 110);

    analogWrite(RM1, 110);

    analogWrite(RM2, 0);
  
  analogWrite(magicpin1,110);
  
  analogWrite(magicpin2,110);
}

/*--------------sensor readings------------------*/

int lsensor()                         //function to read left sensor value
{
  float l = sonar[0].ping_cm();
  
  sonar[0].timer_stop();

  return l;
}

int fsensor()                     //function to read front sensor value
{
  float f = sonar[1].ping_cm();      //will return ping by converting t(in microsec.) to cm
  
  sonar[1].timer_stop();
  
  return f;
}

int rsensor()                 //function to read right sensor value
{
  float r = sonar[2].ping_cm();
  
  sonar[2].timer_stop();

  return r;
}

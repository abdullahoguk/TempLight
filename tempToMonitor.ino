#include <LiquidCrystal.h>

/*TEMPERATURE
lm35 yazılı taraf onde
SOL 5v - SAG gnd - ORTA anolog in PE_4 (5)
*/

/*LDR
1> 3V 
2>PE_2 (28) 
yada (bi bacak + 5v) (ikinci bacak + pe2 + direncin 1 bacagi) (direncin 1 bacagi + GND) 

kırmızı led 
  uzun >>>PC_5 (36) 
  kisa >>> GND 
mavi led 
  uzun >>> PC_4 (36) 
  kisa >>> GND
*/

/* LCD
1- VSS > GND + potansiyometre sag
2- VDD > 5V + potansiyometre sol
3- V0  > potansiyometre orta 
4- RS  > PA_3 (12)
5- RW  > GND
6- E   > PA_2 (11)
7- bos
8- bos
9- bos
10- bos
11- D4 > PE_5 (6)
12- D5 > PB_1 (4)
13- D6 > PB_0 (3)
14- D7 > PB_5 (2)
15- Led + > 5V
16- Led - > GND
*/

// The digital number ADCvalue is a representation of the voltage on PE4 
// voltage  ADCvalue
// 0.00V     0
// 0.75V    1024
// 1.50V    2048
// 2.25V    3072
// 3.00V    4095
// 3.75V    5119
// 4.50V    6143
// 5.00V    6825,666666667
// 5.25V    7167
//carpim celcius ((5.0*1000/6825.666666667)/10) = 0,0732529179
//carpim light ((3.0*1000/4095)/10) = 0,073260073

//TEMPERATURE
const int tempPin = 5;
int analogTemp;
int tempC;
float adcValT;
float adcValL;
const int red =  RED_LED;      
const int blue =  BLUE_LED;

//LDR
const int lightPin = 28;
int analogLight;
int light;
const int redx =  PC_5;      // the number of the LED pin
const int bluex =  PC_4;


//LCD
LiquidCrystal lcd(12, 11, 6, 4, 3, 2);


void setup()
{
   // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello");
  
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(redx, OUTPUT);
  pinMode(bluex, OUTPUT); 
   Serial.begin(9600); 
}

void loop()
{
  // put your main code here, to run repeatedly:
  analogTemp = analogRead(tempPin);
   analogLight = analogRead(lightPin);

//adcValT = 6825,666666667;
//tempC = ((5.0*1000/adcValT)/10)*tempC = *0.0732529179
//adcValL = 4095;
//light = ((3.0*1000/adcValL)/10) = 0.073260073;

tempC = analogTemp*0.0732529179;
light = analogLight*0.073260073;

 lcd.clear();

  Serial.print(tempC);
  Serial.println(" C");
  Serial.print(analogTemp);
  Serial.println(" Analog temp");
 
  lcd.print(tempC);
  lcd.print(" C ");
   
  lcd.setCursor(0,1);
  
  Serial.print(light);
  Serial.println(" amount of light");
  Serial.print(analogLight);
  Serial.println(" Analog Light");
  lcd.print(light);
  lcd.print(" amount light");
  
  if(tempC>25){
      digitalWrite(red,HIGH);
      digitalWrite(blue,LOW);
  }
    else{
      digitalWrite(blue,HIGH);
      digitalWrite(red,LOW);
  }
  
   if(light<25){
     analogWrite(bluex,255);
     digitalWrite(redx,0);
  }
   else{
      digitalWrite(bluex,0);
      digitalWrite(redx,255);
  } 
  
delay(1000);
}

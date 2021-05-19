 #include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



#define SCREEN_WIDTH 128  //OLED display width, in pixels
#define SCREEN_HEIGHT 64  //OLED display height, in pixels
//set screen width and screen height and reset pin for OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int PIR_sensor_Pin = A0; //set IR sensor to A0
int buzzerPin = 3;    //set buzzer to D3
int PIR_state = LOW;      // start no motion detected

// Battery sensor set
int greenLed = 5;     //set green LED to D5
int yellowLed = 6;    //set yellow LED to D6
int redLed = 7 ;      //set red LED to D7

int analogValue = 0;
float voltage = 0;
 

void setup(){
  Serial.begin(9600);
  
  pinMode(buzzerPin,OUTPUT);

  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed,OUTPUT);
  pinMode(redLed, OUTPUT);

  //SSD1306_SWIRCHCAPVCC = generate display voltage from 3.3V internally
  pinMode(PIR_sensor_Pin, INPUT);  //set IR sensor as input
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)){
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);              //Don't proceed, loop forever
    }
    delay(2000);          //pause for 2 seconds
    display.clearDisplay(); //clear the buffer
    display.setTextSize(5); //set the word size to 5
   
  }

  void loop(){

    int status_sensor = digitalRead(PIR_sensor_Pin); //read the IR sensor status
    digitalWrite(buzzerPin, LOW);   //set buzzer low
    if(status_sensor == HIGH){   //If the IR sensor is triggered 
      
      display.setTextColor(WHITE);  //set the word color is white
      display.setCursor(0,10);      //set the text to start at the(0,10) coordinates

      battery_life();               //call battery_life function to detect battery lifef and show it
      
      display.println("SOAP");      // print SOAP on OLED screen
      display.display();            //actually display text on the screen
      display.clearDisplay();       //clear the display
      delay(2000);                  //pause for 2 seconds
      
      digitalWrite(buzzerPin, HIGH); // beep when the timer start count down
      delay(50);
      digitalWrite(buzzerPin, LOW);
      delay(50);
      
      int i;                        //define a int number i as the count down number
      for(i=20; i>=0; i--){         // the initial number is 20 and if the number is more and equal 0 number - 1
        display.setTextColor(WHITE);  // set the text color is white
        display.setCursor(0,10);    //set the text to start at the(0,10) coordinates
        display.print(i);           //print i
        display.display();          //actually display i on the screen
        delay(1000);                // pause for 1 seconds
        if(i == 0){                 // if the timer is count down to 0 then beep twice 
          digitalWrite(buzzerPin, HIGH);
          delay(50);
          digitalWrite(buzzerPin, LOW);
          delay(200);
          digitalWrite(buzzerPin, HIGH);
          delay(50);
          digitalWrite(buzzerPin, LOW);
          delay(50);
          
          }    
          display.clearDisplay();       //clear all display  
          display.display();
          digitalWrite(redLed, LOW);
          digitalWrite(yellowLed, LOW);
          digitalWrite(greenLed, LOW);
                 
      }
     }
    }

// battery_life function detect battery life and use green, yellow and red LED to show battery life
void battery_life()
{
  analogValue = analogRead(A1);     //read the battery life
  //Serial.println(analogValue);
  voltage = 0.0088*analogValue;     //transfer the analog value to voltage
  //Serial.println(voltage);

  delay(500);
  if(voltage >= 8)                  //if the voltage is greater than 8V 
  {
    digitalWrite(greenLed, HIGH);   // green LED light
  }
  else if(voltage > 7 && voltage < 8) // if the voltage is between 7 and 8V
  {
    digitalWrite(yellowLed, HIGH);    //yellow LED light
  }
  else if(voltage <= 7)             // if the voltage is less than 7V
  {
    digitalWrite(redLed, HIGH);     // red LED light
  }

  delay(1000);
  
    
  }


 

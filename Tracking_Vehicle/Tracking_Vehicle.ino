
//code developed by Saiiavon
//follow me on twitter profile:saiiavon


#include <LiquidCrystal.h> //import LCD library
#include <SoftwareSerial.h> //import Serial library
#include <TinyGPS++.h>        //import gps library

TinyGPSPlus gps;// create gps object
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //for lcd pin interface
SoftwareSerial gpsSerial(8,9);//connect tx pin of gps to arduino digital pin 8 and connect rx pin of gps to arduino digital pin 9


//Pin Declaration
#define key 10    // Digital pin for vehicle key
#define mot A2    // analog pin for Engine motor
#define Switch 12 // Digital pin for activating system
#define alrm 11   // Digital pin for Buzzer
#define tlit 13    // Digital pin for Motion

//variable declaration
int count=0;
/*if you want to use accelemeter in
 place of tlit sensor uncomment the Comment With accelemetor 
 and connect accelemeter to pin A0 and A1*/
//const int senx=A0; // for Accelemetor
//const int seny=A1; //for Accelemetor
String lattitude,longitude;
String message; //String variable for storing incomming message
int con=0;      //for Counting 
int i=0;        //for counting
boolean ext=true; // boolean value for exit from loop
int j; //for gps
int k; //for gps


void setup() //initillize
{
  pinMode(Switch,INPUT);
  pinMode(key,INPUT);
  pinMode(tlit,INPUT);
  pinMode(alrm, OUTPUT);
  pinMode(mot,OUTPUT);
  digitalWrite(key, LOW); //Set low important
  digitalWrite(tlit, LOW);
  
  lcd.begin(16,2);
  Serial.begin(9600); // for GSM
  delay(1000);
  gpsSerial.begin(9600); // for GPS
  delay(1000);
  
  
}

void loop()  //Main loop
{
  
  while(1)
  {
   
      lcd.setCursor(0, 0);
      lcd.print("Security System ");
      lcd.setCursor(0, 1);
      lcd.print(" Activated    ");
      readingGPSdata();
      movementFunction();
      
    
  }
}
  
    
    

//---------------------------------------------------------------------------


void readingGPSdata() //function for reading GPS data and sending vehicle location 
{
  for(k=0; k<50;k++){
    for(j=0; j<60;j++){
      gps.encode(gpsSerial.read());
      lattitude = String(gps.location.lat(),6);
      longitude = String(gps.location.lng(),6);
    }
    delay(10);
  }


  Serial.print("vehicle is Found at: ");
  delay(100);
  Serial.println("http://maps.google.com/maps?q=loc:");
  Serial.print(lattitude);
  Serial.print(",");
  Serial.print(longitude);
  delay(200);
  Serial.print("  ");
  
  Serial.println("If you want to stop the vehicle ");
  Serial.println("See the next Loctation while vehicle is moving");
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
  delay(3000);
  lcd.clear();
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
  delay(50);
   
}




//============================================================

void movementFunction()  //Function :- message data for movement alert
{

  for(k=0; k<50;k++){
    for(j=0; j<60;j++){
      gps.encode(gpsSerial.read());
      lattitude = String(gps.location.lat(),6);
      longitude = String(gps.location.lng(),6);
    }
    delay(10);
  }

  delay(100);
  Serial.println("Vehicle moving Postion is detected ");
  Serial.print("current location is ");
  Serial.println("http://maps.google.com/maps?q=loc:");
  Serial.print(lattitude);
  Serial.print(",");
  Serial.print(longitude);
  Serial.println(" check the vehicle!");
  delay(200);
  Serial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
  delay(3000);
  lcd.clear();
  lcd.print("System Ready");
  delay(1000);
  lcd.clear();
  delay(500);
  digitalWrite(alrm,LOW);

}







      

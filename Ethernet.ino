/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 *
 * This example shows how to use Arduino Ethernet shield (W5100)
 * to connect your project to Blynk.
 * Feel free to apply it to any other example. It's simple!
 *
 * NOTE: Pins 10, 11, 12 and 13 are reserved for Ethernet module.
 *       DON'T use them in your sketch directly!
 *
 * WARNING: If you have an SD card, you may need to disable it
 *       by setting pin 4 to HIGH. Read more here:
 *       https://www.arduino.cc/en/Main/ArduinoEthernetShield
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

#include <Servo.h>
Servo myservo;
int turn = 0;
int controlMode = 0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "e6b40a1195594a8d867813c8c28f4bac";

#define W5100_CS  10
#define SDCARD_CS 4

//Joystick
BLYNK_WRITE(V0){
  if(controlMode == 1){
    turn = param[0].asInt();
    int throttle = param[1].asInt();
    
    int turnMapped = map(turn, 0, 255, 0, 180);
    myservo.write(turnMapped);

    /*
    Serial.print("Turn: ");
    Serial.println(turn); //bal-jobb
    Serial.print("Throttle: ");
    Serial.println(throttle);
    */
  }
    
}

//tiltSensor
BLYNK_WRITE(V1){
  if(controlMode == 0){    
    int turn_motion = param[1].asFloat();
    int turnMapped = map(turn_motion, -10, 10, 0, 180);
    myservo.write(turnMapped);
  }  
}

BLYNK_WRITE(V2){
  controlMode = param.asInt();
}


 

void setup()
{
  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card
  myservo.attach(7);

  Serial.begin(9600);
  Blynk.begin(auth);
  // You can also specify server.
  // For more options, see Boards_Ethernet/Arduino_Ethernet_Manual example
  //Blynk.begin(auth, "your_server.com", 8442);
  //Blynk.begin(auth, IPAddress(192,168,1,100), 8888);
}

void loop()
{
  Blynk.run();
  
}


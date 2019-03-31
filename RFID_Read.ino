/*
  Read RFID TAG's and send informations over serial port
  The buzzer sound when tag is read
*/

#include <SoftwareSerial.h> //Used for transmitting to the device

SoftwareSerial softSerial(2, 3); //RX, TX

#include "SparkFun_UHF_RFID_Reader.h" //Library for controlling the M6E Nano module
RFID nano; //Create instance

//-- BUZZER
#define BUZZER1 10
#define BUZZER2 9
//-- end BUZZER

void setup()
{
  Serial.begin(115200);

  while (!Serial);
    Serial.println("Initialisation...");//Attente d'initialisation du serial port

  //-- BUZZER
  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);

  digitalWrite(BUZZER2, LOW); //Pull half the buzzer to ground and drive the other half.
  //-- fin BUZZER

  if (setupNano(38400) == false) //Configure nano to run at 38400bps
  {
    Serial.println("Module failed to respond. Please check wiring.");
    while (1); //Freeze!
  }

  nano.setRegion(REGION_NORTHAMERICA); //Pas d'intérêt de changer

  nano.setReadPower(1000); //5.00 dBm. Higher values may caues USB port to brown out
  //Max Read TX Power is 27.00 dBm and may cause temperature-limit throttling

  nano.startReading(); //Begin scanning for tags
}

void loop()
{
  //delay(500);
  if (nano.check() == true) //Check to see if any new data has come in from module
  {
    byte responseType = nano.parseResponse(); //Break response into tag ID, RSSI and frequency

    /*if (responseType == RESPONSE_IS_KEEPALIVE)
    {
      Serial.println(F("Scan en cours"));
    }*/
    if (responseType == RESPONSE_IS_TAGFOUND)
    {
      //If we have a full record we can pull out the fun bits
      int rssi = nano.getTagRSSI(); //Get the RSSI for this tag read

      long freq = nano.getTagFreq(); //Get the frequency this tag was detected at

      byte tagEPCBytes = nano.getTagEPCBytes(); //Get the number of bytes of EPC from response

      //----BUZZER
      tone(BUZZER1, 2093, 150); //Son de buzzer
      delay(1000);
      //----fin BUZZER
      //--------------On envoie les données dans le port serial
      Serial.print(F(" [TAG READ] ")); //Permettra dans le fichier .py de détecter une ligne où un tag est lu
      
      Serial.print(freq);
      Serial.print(F("kHz "));

      //Reader ID
      Serial.print(F("Warehouse_Compiegne "));

      //Tag ID
      for (byte x = 0 ; x < tagEPCBytes ; x++)
      {
        if (nano.msg[31 + x] < 0x10) Serial.print(F("0")); //Pretty print
        Serial.print(nano.msg[31 + x], HEX);
      }
      Serial.print(F(" "));
      Serial.print(rssi);
      
      Serial.println();
      //--------------FIN - On envoie les données dans le port serial
    }
    /*else if (responseType == ERROR_CORRUPT_RESPONSE)
    {
      Serial.println("Erreur, veuillez-reessayez.");
    }
    else
    {
      //Unknown response
      Serial.print("Erreur inconnue.");
    }*/
  }
}

//Gracefully handles a reader that is already configured and already reading continuously
//Because Stream does not have a .begin() we have to do this outside the library
boolean setupNano(long baudRate)
{
  nano.begin(softSerial); //Tell the library to communicate over software serial port

  //Test to see if we are already connected to a module
  //This would be the case if the Arduino has been reprogrammed and the module has stayed powered
  softSerial.begin(baudRate); //For this test, assume module is already at our desired baud rate
  while (softSerial.isListening() == false); //Wait for port to open

  //About 200ms from power on the module will send its firmware version at 115200. We need to ignore this.
  while (softSerial.available()) softSerial.read();

  nano.getVersion();

  if (nano.msg[0] == ERROR_WRONG_OPCODE_RESPONSE)
  {
    //This happens if the baud rate is correct but the module is doing a ccontinuous read
    nano.stopReading();

    Serial.println(F("Module continuously reading. Asking it to stop..."));

    delay(1500);
  }
  else
  {
    //The module did not respond so assume it's just been powered on and communicating at 115200bps
    softSerial.begin(115200); //Start software serial at 115200

    nano.setBaud(baudRate); //Tell the module to go to the chosen baud rate. Ignore the response msg

    softSerial.begin(baudRate); //Start the software serial port, this time at user's chosen baud rate

    delay(250);
  }

  //Test the connection
  nano.getVersion();
  if (nano.msg[0] != ALL_GOOD) return (false); //Something is not right

  //The M6E has these settings no matter what
  nano.setTagProtocol(); //Set protocol to GEN2

  nano.setAntennaPort(); //Set TX/RX antenna ports to 1

  return (true); //We are ready to rock
}

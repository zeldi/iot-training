#include <SoftwareSerial.h>
#include "dht.h"
#define dht_apin 7 // Analog Pin sensor is connected to
 
#define DEBUG true


// Creates the object to use the Sotfware Serial library
// The TX of esp8266 must be connected to pin 2 of the Arduino
// The RX of esp8266 must be connected to pin 3 of the Arduino
SoftwareSerial esp8266(2,3); 
dht DHT;

void setup()
{
  // a small delay on arduino
  // to prevent you from sending commands before the esp8266 give the start
  delay(500);
  Serial.begin(9600);
  esp8266.begin(115200); 
  
 
  //Envia o comandos AT
  
  // reset the module
  sendData("AT+RST\r\n",2000,DEBUG);
  
  // configure as access point and station
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); 
  
  // connect to the router with the password  
  // (this configuration must be done, because your router has a different name from my and password)
  sendData("AT+CWJAP='quend2012','02304304\'\r\n",10000,DEBUG); 
  
  // Returns the IP to which it is connected and the Station IP
  sendData("AT+CIFSR\r\n",1000,DEBUG); 
  
  // Enable multiple connections
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); 
  
  // Enables the server to port 80
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); 
}
 
void loop()
{
  
  // check if esp8266 is sending a message and it is available
  if(esp8266.available()) 
  {
    
    if(esp8266.find("+IPD,"))
    {  
       DHT.read11(dht_apin);
 
      // subtract 48, because the read () method returns the ASCII values, the first decimal number starts at 48 
       int connectionId = esp8266.read()-48; 
     
     // Start the assembly of the web page
     // creating the webpage variable and storing the data in it
       String webpage = "<head><meta http-equiv=""refresh"" content=""5""></head>"; 
       webpage+="<h1>Arduino Page</h1><h3>Temperature : ";
       webpage+= String(DHT.temperature); //"23"; 
       webpage+= "</h3>";
       webpage+= "<h3> Humidity : ";
       webpage+= String(DHT.humidity); //"40";
       webpage+= "</h3>";
       
     // create a variable to send the command to
     // that will send the information to the module esp8266 
       String cipSend = "AT+CIPSEND=";
       
       
       cipSend += connectionId;
       cipSend += ",";
       cipSend +=webpage.length();
       cipSend +="\r\n";
       
     // Send the commands for the module
       sendData(cipSend,1000,DEBUG);
       sendData(webpage,1000,DEBUG);
       
     // Close the commands
       String closeCommand = "AT+CIPCLOSE="; 
       closeCommand+=connectionId;
       closeCommand+="\r\n";
       
     // Sends the closing commands
       sendData(closeCommand,2000,DEBUG);
       
       delay(5000);
    }
  }
}
 
 
 // Function that sends the commands to the esp8266
String sendData(String command, const int timeout, boolean debug)
{
    //response variable
    String response = "";
    
    // send the character reading to esp8266
    esp8266.println(command); 
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {      
        // Concatenate character per character received from module esp8266 
        char c = esp8266.read(); 
        response+=c;
      }  
    }
    
    // response debug of esp8266
    if(debug)
    {
      // Print out what esp8266 sent to the arduino
      Serial.println("Arduino : " + response);
    }
    
    return response;
}



// Function that converts float to string
long getDecimal(float val)
{
  int intPart = int(val);
  
  long decPart = 100*(val-intPart);
  
  if(decPart>0)
  return(decPart);           
  
  else if(decPart=0)
     return(00);           
}

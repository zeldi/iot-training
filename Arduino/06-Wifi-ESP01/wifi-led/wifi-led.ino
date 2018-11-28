#include <SoftwareSerial.h>
 
#define DEBUG true


// Creates the object to use the Sotfware Serial library
// The TX of esp8266 must be connected to pin 2 of the Arduino
// The RX of esp8266 must be connected to pin 3 of the Arduino
SoftwareSerial esp8266(2,3); 

void setup()
{
  // a small delay on arduino
  // to prevent you from sending commands before the esp8266 give the start
  delay(500);
  Serial.begin(9600);
  //(em alguns casos a velocidade do seu esp8266 pode estar diferente desta)
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
      // subtract 48, because the read () method returns the ASCII values, the first decimal number starts at 48 
       int connectionId = esp8266.read()-48; 
     
     // Start the assembly of the web page
     // creating the webpage variable and storing the data in it
       String webpage = "<head><meta http-equiv=""refresh"" content=""5""></head>"; 
       webpage+="<h1>Arduino Page</h1><h3>Temperature : ";
       webpage+= "23"; 
       webpage+= "</h3>";
       webpage+= "<h3> Humidity : ";
       webpage+= "40";
       webpage+= "</h3>";
       
       //cria uma variavel para enviar o comando até
       //que enviará as informações para o modulo esp8266 
       String cipSend = "AT+CIPSEND=";
       
       
       cipSend += connectionId;
       cipSend += ",";
       cipSend +=webpage.length();
       cipSend +="\r\n";
       
       //Envia os comandos para o modulo
       sendData(cipSend,1000,DEBUG);
       sendData(webpage,1000,DEBUG);
       
       //Encerra os comandos
       String closeCommand = "AT+CIPCLOSE="; 
       closeCommand+=connectionId;
       closeCommand+="\r\n";
       
       //Envia os comandos de encerramento
       sendData(closeCommand,2000,DEBUG);
       
       delay(5000);
    }
  }
}
 
 
 //Metodo que envia os comandos para o esp8266
String sendData(String command, const int timeout, boolean debug)
{
    //variavel de resposta do esp8266
    String response = "";
    
    // send a leitura dos caracteres para o esp8266
    esp8266.println(command); 
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {      
        //Concatena caracter por caractere recebido do modulo esp8266 
        char c = esp8266.read(); 
        response+=c;
      }  
    }
    
    //debug de resposta do esp8266
    if(debug)
    {
      //Imprime o que o esp8266 enviou para o arduino
      Serial.println("Arduino : " + response);
    }
    
    return response;
}



//Metodo que converte float em string
long getDecimal(float val)
{
  //converte o float para inteiro 
  int intPart = int(val);
  
  //multiplica por 100
  //precisão de 2 casas decimais
  long decPart = 100*(val-intPart);
  
  //Se o valor for maior que 0 retorna
  if(decPart>0)
  //retorna a variavel decPart 
  return(decPart);           
  
  //caso contrario retorna o valor 0
  else if(decPart=0)
     return(00);           
}

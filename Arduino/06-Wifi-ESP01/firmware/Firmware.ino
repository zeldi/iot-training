/*Simple code to create webserver in Arduino and control things within the network
 Created by Frank Donald */
void serial_check();
void WiFiCheck();
void command_input();
void clear_buffer();
void   brow_req();   
void brow_resp();
//void Search_webrequest();

char Input_buffer[550];
boolean command_flag=false;
int i,j;
boolean stringComplete=false;
boolean request_processed=false;
boolean WiFiConnect=false;
short int command_count=0;
char send_bytes[]="AT+CIPSEND= ,379\r\n";
boolean client_request=false;
boolean flag=true;
char connection_id;
short int page_input_pos;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  Serial.begin(115200);
  delay(5000);
  Serial.print("AT+RST\r\n");
  delay(200);
  while(WiFiConnect==false)                             //Wait till Connecting to WiFi hotspot
  {
    serial_check();
    WiFiCheck();                                        //WiFi check subroutine
  }
  
  while(command_flag==false)                           //Looping for commands 
  {
    command_input();
  }
  clear_buffer();                                        //Clearing the array
  while(client_request==false) //Waitingfor anyclient/browser to initiate the request
  {
    serial_check();
    brow_req();                                         //sub routine to check browser request
    brow_resp();                                        //sub routine for response from Arduino
  }
  flag=false;
}

void loop() {
  serial_check();
  page_input_pos=Search_webrequest();                  //Monitor webpage indefinitely
  activate();
}


void activate()
{
  if(flag==true)
  {
    if(Input_buffer[page_input_pos]=='O'&&Input_buffer[page_input_pos+1]=='N')
    digitalWrite(12,HIGH);
    else if(Input_buffer[page_input_pos]=='O'&&Input_buffer[page_input_pos+1]=='F')
    digitalWrite(12,LOW);
  }
}

void WiFiCheck()                                        //Check whether WiFi is connected 
{
  if(stringComplete==true&&Input_buffer[j-4]=='I')   //Check for the status WIFI GOT IP 
  {
   clear_buffer();
   WiFiConnect=true;
   delay(500);
  }
  else
  {
    clear_buffer();
    stringComplete=false;
  }
}

int Search_webrequest()                                   //repeated loop to check button inputs from Webpage
{
  if(stringComplete==true)
  {
    for(i=0;i<j-2;i++)
    {
      if(Input_buffer[i]=='G'&&Input_buffer[i+1]=='E'&&Input_buffer[i+2]=='T')
      {
        flag=true;
        return i+5;
      }
    }
  }
}

void brow_req()                                               //sub routine to monitor the browser request
{
  if(stringComplete==true&&request_processed==false)          //Checking for presence of char in input buffer and check whether the client request has already processed
   {
      if(flag==true)
      connection_id=(char)Input_buffer[0];                    
      send_bytes[11]=connection_id;                           //Adding connection ID to the CIPSEND command
      Serial.print(send_bytes);
      clear_buffer();
      delay(1000);  
      request_processed=true;                                 //Changing the flag to true indicating that Client request is processed
   }
}

void brow_resp()                                             //Sub routine to respond to client request
{
  if(request_processed==true&&stringComplete==true)         //Checking the flag on client request process
  {
    serial_check();
    if(Input_buffer[j-2]=='>')                              //Checking for the Send data signal from ESP  module
    {
      memset(Input_buffer,'\0', sizeof(Input_buffer));
      Serial.print("<!DOCTYPE html><html><body><h1>Welcome to Arduino LED control Wizard</h1><p>You can turn ON/OFF LED connected to Arduino using the buttons given below</p><p><b>TURN ON</b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"ON\"><button>ON</button></a></br></p><p><b>TURN OFF</b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"OFF\"><button>OFF</button></a></br></p></body></html>");
      delay(2000);
      serial_check();
      //while(command_response_check==false);
      clear_buffer();
      request_processed=false;
      client_request=true;
    }
    else
    {
      clear_buffer();
      request_processed=false; //If request response didnt turn out successful mark the flags so that another CIPSEND command can be passed
      flag=false;   
    }
  }
}

void command_input()                                      //Sub routine for commands to create server using ESP module
{
  serial_check();
  if(command_response_check(Input_buffer)==true) //Checking the response and Tracking the counts of command to handle in case of error response from ESP
  {command_count=command_count+1;}
  else 
  delay(1000);
  clear_buffer();
  switch(command_count)                                  //Enter commands sequentially in creating server
  {
    case 0: { Serial.print("AT\r\n");
              delay(500);
              break;
              }
    case 1: { 
              Serial.print("AT+CWMODE=3\r\n");
              delay(1000);
              break;}   
    case 2: {
              Serial.print("AT+CIPSTA=\"192.168.43.253\"\r\n");
              delay(1000);
              break; 
              }
    case 3: {
              Serial.print("AT+CIPMUX=1\r\n");
              delay(1000);
              break;
            }
    case 4: {
              Serial.print("AT+CIPSERVER=1,80\r\n");
              delay(1000);
              break;
            }
    case 5: {
             command_flag=true;
             digitalWrite(13,HIGH);
             break;  
            }
  }
}

void clear_buffer()                                             //Clearing buffer
{
  memset(Input_buffer, '\0', sizeof(Input_buffer));
  stringComplete=false;
}

boolean command_response_check(char *a)                         //Checking for OK Response from ESP
{
  if(a[j-4]=='O'&&a[j-3]=='K'&&a[j-2]=='\r'&&a[j-1]=='\n')
  return true;
  else
  { delay(1000);
    return false; }  
}

void serial_check() {                                           //Serial char available check
  i=0;
  while (Serial.available()) {
    delay(2);
    char inChar = Serial.read();
    Input_buffer[i]=(char)inChar;
    i=i+1;
    stringComplete = true;
    j=i;
   }       
}

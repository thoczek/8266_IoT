#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <EEPROM.h> //Needed to access the eeprom read write functions
//#############################################################################################
//  Declarations
//#############################################################################################
  IPAddress staticIP(192, 168, 1, 103); //ESP static ip
  IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
  IPAddress subnet(255, 255, 255, 0);  //Subnet mask
  IPAddress dns(192, 168, 1, 1);  //DNS
  String ssid ="OfcaNet" ;
  String passwd="owieczka";
ESP8266WebServer server(80);
String kolor;
int inputs[5];
int outputs[4];
float analog[1];
int analogMin,analogMax,analogOffset;
void handle_index();
void handle_set();
void handle_toggle();
void handle_state();
void handle_picstate();
void EEPROMWriteInt(int p_address, int p_value);
int EEPROMReadInt(int p_address);
//#############################################################################################
//  SETUP
//#############################################################################################
void setup() {
  //#############################################################################################
  //  Inputs
  
  pinMode(16, INPUT); 
  pinMode(14, INPUT); 
  pinMode(12, INPUT); 
  pinMode(13, INPUT); 
  pinMode(15, INPUT); 
  
  //Pullup enable
  digitalWrite(16, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(15, HIGH);
  //#############################################################################################
  //  Analog in
  
  pinMode(A0, INPUT); 
  //#############################################################################################
  //  Outputs
  
  pinMode(5, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(0, OUTPUT); 
  pinMode(2, OUTPUT); 
  //#############################################################################################
  //  Output initial state
  
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(0, HIGH);
  digitalWrite(2, HIGH);
  //#############################################################################################
  //  Read EEprom data
  EEPROM.begin(512); delay(10);
  analogMin=EEPROMReadInt(0)-32743;
  analogMax=EEPROMReadInt(2)-32743;
  analogOffset=EEPROMReadInt(4)-32743;
  EEPROM.end();
  //#############################################################################################
  //  WiFiMenager setup
  
  Serial.begin(115200);

  //WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.config(staticIP, gateway, subnet, dns);
  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwd);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  
  //WiFiManager wifiManager;
  //wifiManager.setTimeout(180);
  //if(!wifiManager.autoConnect("AutoConnectAP")) 
  //{
    //Serial.println("failed to connect and hit timeout");
    //delay(60);
    //reset and try again, or maybe put it to deep sleep
    //ESP.reset();
    //delay(5000);
  //} 
  server.on("/", handle_index);
  server.on("/set", handle_set);
  server.on("/toggle", handle_toggle);
  server.on("/state", handle_state);
  server.on("/picstate", handle_picstate);
  server.on("/adconfig", handle_adconfig);
  server.begin();
}
//#############################################################################################
// LOOP
//#############################################################################################
void loop() 
{
  inputs[0]=digitalRead(16);
  inputs[1]=digitalRead(14);
  inputs[2]=digitalRead(12);
  inputs[3]=digitalRead(13);
  inputs[4]=digitalRead(15);

  server.handleClient();

  digitalWrite(5, outputs[0]);
  digitalWrite(4, outputs[1]);
  digitalWrite(0, outputs[2]);
  digitalWrite(2, outputs[3]);
  
  if (WiFi.status() != WL_CONNECTED) 
  {
    ESP.reset();
  }
  
}
//#############################################################################################
// HANDLE_INDEX
//#############################################################################################
void handle_index() {
  analog[0]=(float)(((100*analogMax)-(100*analogMin))/1024*analogRead(A0)+100*analogMin+100*analogOffset)/100;
  String content=" \
  <!DOCTYPE HTML>\
  <html>\
  <head>\
    <title>ESP8266</title>\
    <meta http-equiv=\"Cache-Control\" content=\"no-cache, no-store, must-revalidate\" />\
    <meta http-equiv=\"Pragma\" content=\"no-cache\" /><meta http-equiv=\"Expires\" content=\"-1\" />\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">\
    <script>\
      window.onpageshow = function(event) \
      {    \
        if (event.persisted) \
        {\
          window.location.reload()     \
        }\
      };\
    </script>\
    <body>\
    <table align='center' border='0px'>\
      <tr>\
        <td valign='middle' align='center'>Analog In : </td>\
        <td valign='middle' align='center'>"+(String)analog[0]+"</td>\
        <td valign='middle' align='center'>\
          <form action='/adconfig'>\
            <input type='submit' value='Configure' /> \
          </form>\
        </td>\
      </tr>\
    </table>\
    <br /><br />\
    <table align='center' border='0px'>\
      <tr>\
        <td valign='middle' align='center'>In 1 </td>\
        <td valign='middle' align='center'>In 2 </td>\
        <td valign='middle' align='center'>In 3 </td>\
        <td valign='middle' align='center'>In 4 </td>\
        <td valign='middle' align='center'>In 5 </td>\
      </tr>\
      <tr>\
        <td valign='middle'>\
          <table width='64' align='center' border=0px>\
            <tr height='64'>\
              <td BGCOLOR='";
                if (inputs[0]==1) kolor="red";
                else kolor="green";
                content=content+kolor;
              content=content+"'> </td>\
            </tr>\
          </table>\
        </td>\
        <td valign='middle'>\
          <table width='64' align='center' border=0px>\
            <tr height='64'>\
              <td BGCOLOR='";
                if (inputs[1]==1) kolor="red";
                else kolor="green";
                content=content+kolor;
              content=content+"'> </td>\
            </tr>\
          </table>\
        </td>\
        <td valign='middle'>\
          <table width='64' align='center' border=0px>\
            <tr height='64'>\
              <td bgcolor='";
                if (inputs[2]==1) kolor="red";
                else kolor="green";
                content=content+kolor;
              content=content+"'> </td>\
            </tr>\
          </table>\
        </td>\
        <td valign='middle'>\
          <table width='64' align='center' border=0px>\
            <tr height='64'>\
              <td BGCOLOR='";
                if (inputs[3]==1) kolor="red";
                else kolor="green";
                content=content+kolor;
              content=content+"'> </td>\
              </tr>\
          </table>\
          </td>\
              <td valign='middle'>\
          <table width='64' align='center' border=0px>\
            <tr height='64'>\
              <td BGCOLOR='";
                if (inputs[4]==1) kolor="red";
                else kolor="green";
                content=content+kolor;
              content=content+"'> </td>\
            </tr>\
          </table>\
        </td>\
      </tr>\
    </table>\
    <br /><br />\
    <table align='center' border=0>\
      <tr>\
        <td valign='middle'>Out 1 </td>\
        <td valign='middle'>\
          <form action='/set'>\
            <input type='hidden' name='out1' value='1' />\
            <input type='submit' value='On' />\
          </form>\
        </td>\
        <td valign='middle'>\
          <form action='/set'>\
            <input type='hidden' name='out1' value='0' />\
            <input type='submit' value='OFF' />\
          </form>\
        </td>\
        <td valign='middle'>\
          <form action='/toggle'>\
            <input type='hidden' name='out1' value='1' />\
            <input type='submit' value='Toggle' />\
          </form>\
        </td>\
        <td valign='top'>\
          <table width='64' align='center' border=0px>\
            <tr height='64'>\
              <td bgcolor='";
                if (outputs[0]==1) kolor="red";
                else kolor="green";
                content=content+kolor;
              content=content+"'></td>\
            </tr>\
          </table>\
        </td>\
      </tr>\
      <tr>\
        <td valign='middle'>Out 2 </td>\
        <td valign='middle'>\
          <form action='/set'>\
            <input type='hidden' name='out2' value='1' />\
            <input type='submit' value='On' />\
          </form>\
        </td>\
        <td valign='middle'>\
          <form action='/set'>\
            <input type='hidden' name='out2' value='0' />\
            <input type='submit' value='OFF' />\
          </form>\
        </td>\
        <td valign='middle'>\
          <form action='/toggle'>\
            <input type='hidden' name='out2' value='1' />\
            <input type='submit' value='Toggle' />\
          </form>\
        </td>\
        <td valign='top'>\
          <table width='64' align='center' border=0px>\
            <tr height='64'>\
              <td bgcolor='";
                if (outputs[1]==1) kolor="red";
                else kolor="green";
                content=content+kolor;
              content=content+"'> </td>\
            </tr>\
          </table>\
        </td>\
      </tr>\
      <tr>\
        <td valign='middle'>Out 3 </td>\
        <td valign='middle'>\
          <form action='/set'>\
            <input type='hidden' name='out3' value='1' />\
            <input type='submit' value='On' />\
          </form>\
        </td>\
        <td valign='middle'>\
          <form action='/set'>\
            <input type='hidden' name='out3' value='0' />\
            <input type='submit' value='OFF' />\
          </form>\
        </td>\
        <td valign='middle'>\
          <form action='/toggle'>\
            <input type='hidden' name='out3' value='1' />\
            <input type='submit' value='Toggle' />\
          </form>\
        </td>\
        <td valign='top'>\
          <table width='64' align='center' border=0px>\
            <tr height='64'>\
              <td bgcolor='";
                if (outputs[2]==1) kolor="red";
                else kolor="green";
                content=content+kolor;
              content=content+"'> </td>\
            </tr>\
          </table>\
        </td>\
      </tr>\
      <tr>\
        <td valign='middle'>Out 4 </td>\
        <td valign='middle'>\
          <form action='/set'>\
            <input type='hidden' name='out4' value='1' />\
            <input type='submit' value='On' />\
          </form>\
        </td>\
        <td valign='middle'>\
          <form action='/set'>\
            <input type='hidden' name='out4' value='0' />\
            <input type='submit' value='OFF' />\
          </form>\
        </td>\
        <td valign='middle'>\
          <form action='/toggle'>\
            <input type='hidden' name='out4' value='1' />\
            <input type='submit' value='Toggle' />\
          </form>\
        </td>\
        <td valign='top'>\
          <table width='64' align='center' border=0px>\
            <tr height='64'>\
              <td bgcolor='";
                if (outputs[3]==1) kolor="red";
                else kolor="green";
                content=content+kolor;
              content=content+"'> </td>\
            </tr>\
          </table>\
        </td>\
      </tr>\
    </table>\
  </body>\
</html>\
  ";
  
  server.send(200, "text/html", content);
}
//#############################################################################################
// HANDLE_SET
//#############################################################################################
void handle_set()
{
  String content="NOK";
  
  if(server.arg("out1")!="")
  {
    outputs[0]=!server.arg("out1").toInt();
    content=(String)server.arg("out1").toInt();
  }
  if(server.arg("out2")!="")
  {
    outputs[1]=!server.arg("out2").toInt();
    content=(String)server.arg("out2").toInt();
  }
  if(server.arg("out3")!="")
  {
    outputs[2]=!server.arg("out3").toInt();
    content=(String)server.arg("out3").toInt();
  }
  if(server.arg("out4")!="")
  {
    outputs[3]=!server.arg("out4").toInt();
    content=(String)server.arg("out4").toInt();
  }

  server.send(200, "text/html", content);
}
//#############################################################################################
// HANDLE_TOGGLE
//#############################################################################################
void handle_toggle()
{
  String content="NOK";
  
  if(server.arg("out1").toInt()==1)
  {
    outputs[0]=!outputs[0];
    content=(String)!outputs[0];
  }
    if(server.arg("out2").toInt()==1)
  {
    outputs[1]=!outputs[1];
    content=(String)!outputs[1];
  }
    if(server.arg("out3").toInt()==1)
  {
    outputs[2]=!outputs[2];
    content=(String)!outputs[2];
  }
    if(server.arg("out4").toInt()==1)
  {
    outputs[3]=!outputs[3];
    content=(String)!outputs[3];
  }
  
  server.send(200, "text/html", content);
}
//#############################################################################################
// HANDLE_STATE
//#############################################################################################
void handle_state()
{
  String content;
  if(server.arg("in")=="1")
  {
    content=(String)!inputs[0];
  }
  if(server.arg("in")=="2")
  {
    content=(String)!inputs[1];
  }
  if(server.arg("in")=="3")
  {
    content=(String)!inputs[2];
  }
  if(server.arg("in")=="4")
  {
    content=(String)!inputs[3];
  }
  if(server.arg("in")=="5")
  {
    content=(String)!inputs[4];
  }
  
  if(server.arg("out")=="1")
  {
    content=(String)!outputs[0];
  }
    if(server.arg("out")=="2")
  {
    content=(String)!outputs[1];
  }
    if(server.arg("out")=="3")
  {
    content=(String)!outputs[2];
  }
    if(server.arg("out")=="4")
  {
    content=(String)!outputs[3];
  }
  if(server.arg("in")=="A")
  {
    content=(float)(((100*analogMax)-(100*analogMin))/1024*analogRead(A0)+100*analogMin+100*analogOffset)/100;
  }
  server.send(200, "text/html", content);
}
//#############################################################################################
// HANDLE_PICSTSTE
//#############################################################################################
void handle_picstate()
{
  String content,color;
  content="\
    <table width='64' align='center' border=0px>\
            <tr height='64'>\
              <td BGCOLOR='";

  if(server.arg("in")=="1")
  {
    if (inputs[0]==1) color="red";
    else color="green";
    content=content+color;
  } 
  if(server.arg("in")=="2")
  {
    if (inputs[1]==1) color="red";
    else color="green";
    content=content+color;
  } 
  if(server.arg("in")=="3")
  {
    if (inputs[2]==1) color="red";
    else color="green";
    content=content+color;
  } 
  if(server.arg("in")=="4")
  {
    if (inputs[3]==1) color="red";
    else color="green";
    content=content+color;
  } 
  if(server.arg("in")=="5")
  {
    if (inputs[4]==1) color="red";
    else color="green";
    content=content+color;
  } 
  if(server.arg("out")=="1")
  {
    if (outputs[0]==1) color="red";
    else color="green";
    content=content+color;
  }               
  if(server.arg("out")=="2")
  {
    if (outputs[1]==1) color="red";
    else color="green";
    content=content+color;
  } 
  if(server.arg("out")=="3")
  {
    if (outputs[2]==1) color="red";
    else color="green";
    content=content+color;
  }            
  if(server.arg("out")=="4")
  {
    if (outputs[3]==1) color="red";
    else color="green";
    content=content+color;
  }
  
  content=content+"'> </td>\
            </tr>\
          </table>";
  server.send(200, "text/html", content);
}
//#############################################################################################
// HANDLE_adconfig
//#############################################################################################
void handle_adconfig() {
  
  if(server.arg("min")!=""&&server.arg("max")&&server.arg("offset"))
  {
    EEPROMWriteInt(0,server.arg("min").toInt()+32743);
    EEPROMWriteInt(2,server.arg("max").toInt()+32743);
    EEPROMWriteInt(4,server.arg("offset").toInt()+32743);
    //  Read EEprom data
    analogMin=EEPROMReadInt(0)-32743;
    analogMax=EEPROMReadInt(2)-32743;
    analogOffset=EEPROMReadInt(4)-32743;
  }
  analog[0]=(float)(((100*analogMax)-(100*analogMin))/1024*analogRead(A0)+100*analogMin+100*analogOffset)/100;
  
  String content;
  content="\
    <\!DOCTYPE html>\
    <html><head>\
    <meta http-equiv=\"content-type\" content=\"text/html; charset=windows-1252\">\
    <title>ESP8266</title>\
    <meta http-equiv=\"Cache-Control\" content=\"private, max-age=0, no-cache, no-store, must-revalidate\">\
    <meta http-equiv=\"Pragma\" content=\"no-cache\">\
    <meta http-equiv=\"Expires\" content=\"no-cache\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <script>\
      window.onpageshow = function(event) {\
      if (event.persisted) {\
        window.location.reload() \
        }\
      };\
    </script>\
    </head>\
    <body>\
      <center>\
        Analog to digital converter range setup\
          <form>\
            <table style=\" border:0px; \">\
              <tbody>\
                <tr><td>Min </td><td><input type=\"text\" name=\"min\" value=\""+(String)analogMin+"\"> </td></tr>\
                <tr><td>Max </td><td><input type=\"text\" name=\"max\" value=\""+(String)analogMax+"\"> </td></tr>\
                <tr><td>Offset </td><td><input type=\"text\" name=\"offset\" value=\""+(String)analogOffset+"\"></td></tr>\
                <tr><td>Value : "+analog[0]+"</td><td>Raw data : "+analogRead(A0)+"</td></tr>\
                <tr><td></td><td><input type=\"submit\" value=\"Save\"></td></tr>\
              </tbody>\
            </table>\
          </form>\
        </center>\
      </body>\
    </html>\
  ";
  server.send(200, "text/html", content);
}
//#############################################################################################
//EEPROM WRITE - This function will write a 2 byte integer to the eeprom at the specified address and address + 1
//#############################################################################################
void EEPROMWriteInt(int p_address, int p_value)
     {
     EEPROM.begin(512); delay(10);
     byte lowByte = ((p_value >> 0) & 0xFF);
     byte highByte = ((p_value >> 8) & 0xFF);
    
     EEPROM.write(p_address, lowByte);
     EEPROM.write(p_address + 1, highByte);
     EEPROM.end();
     }
//#############################################################################################
//EEPROM READ - This function will read a 2 byte integer from the eeprom at the specified address and address + 1
//#############################################################################################

//unsigned
int EEPROMReadInt(int p_address)
     {
     EEPROM.begin(512); delay(10);
     byte lowByte = EEPROM.read(p_address);
     byte highByte = EEPROM.read(p_address + 1);
     EEPROM.end();
     return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
     }

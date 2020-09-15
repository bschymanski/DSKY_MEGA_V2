#include <Arduino.h>
#include <Wire.h>
#include <main.h>
#include <arduino-timer.h>
#include <globals.h>
#include <neopixel.h>
#include <nextion.h>
#include <button_read_int.h>
#include <inputverb.h>
#include <inputnoun.h>
#include <TimeLib.h>
#include <time.h>
#include <gps.h>
#include <SoftwareSerial.h>




/*
// Ethernet
#include <SPI.h>
#include <Ethernet.h>


byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 178, 100);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
*/

// for the toggle variables
auto timer = timer_create_default();

//#define DEBUG 1

void setup()
{
  // prepare the Pins for the keyboard and attach the interrupt
  configureCommon(); // Setup pins for interrupt
  attachInterrupt(digitalPinToInterrupt(commonPin), pressInterrupt, FALLING);

  Serial.begin(9600);
  Wire.begin();
  void time_setup();
  timer.every(1000, toggle_timer_1000);
  timer.every(500, toggle_timer_500);
  timer.every(250, toggle_timer_250);
  NeoPixelSetup();
  //testLamp();
  // nextion Display Init
  Serial1.begin(9600);
  delay(100);
  Serial1.print("baud=115200");
  Serial1.write(0xff);  //Send this three lines after each command sent to the nextion display.
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.end();
  delay(100);
  Serial1.begin(115200);
  ELtestlamp();
  printVerbNounProg();
  printRegister(1, register_num_1, false, false, false, true);
  printRegister(2, register_num_2, false, false, false, true);
  printRegister(3, register_num_3, false, false, false, true);
  
  gps_setup();
  

  /*
  #ifdef DEBUG
    Serial.println("Ethernet WebServer Example");
    // start the Ethernet connection and the server:
    Ethernet.begin(mac, ip);
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // start the server
    server.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
  #endif
  */

}

void loop()
{
  // each loop, look if the toggle_timer* need to be updated
  timer.tick();
  /*
  now we have 3 gloal Toggles:
  toggle1000
  toggle500
  toggle250
  
  blinkverb = true;
  blinknoun = true;
  blinkprog = true;
  verb_ten =3;
  verb_one =7;
  noun_ten = 0;
  noun_one = 2;
  prog_ten = 6;
  prog_one = 3;
  
  printVerbNounProg();
  long number1 = 312;
  long number2 = 9512;
  long number3 = 80302;
  //extern void printRegister(int dregister, long number, bool leadzero, bool blink, bool alarm, bool signoff);
  printRegister(1, number1, false, true, false, false);
  printRegister(2, number2, false, false, false, false);
  printRegister(3, number3, false, false, false, false);
  */
  // is a Program (major mode) running ?
  switch (progRunning)
  {
    case progNone:
      // No programm running yet
      setLamp(yellow, lampProgCond);
      // is an action running?
      switch (actionRuning)
      {
        case actionNone:
          //no action is running
          setLamp(white, lampSTBY);
          break;
        case actionLampTest:
          testLamp();
          actionRuning = actionNone;
          clearVerbfunction();
          break;
        case actionDisplayRealTimeClock:
          display_time();
          setLamp(white, lampKeyRelease);
          break;
      }
      // END is an action running
      break;
    case progDispTimeDate:
      display_time();
      setLamp(off, lampProgCond);
      delay(10);
      setLamp(off, lampSTBY);
      break;
    default:
      break;
  }
  if (progRunning != progNone)
  {
    switch (actionRuning)
      {
        case actionNone:
          //no action is running
          //setLamp(white, lampSTBY);
          break;
        case actionLampTest:
          testLamp();
          actionRuning = actionNone;
          clearVerbfunction();
          break;
        case actionDisplayRealTimeClock:
          display_time();
          setLamp(white, lampKeyRelease);
          break;
      }
  }
  // END is a Program (major mode) running ?

  // check the key, if one has been pressed:
  if (keypressed == true) // a key hase been pressed
  { 
    switch(current_key) // which key has been pressed?
    {
      case keyVerb:
        inputmode = inputVerb;
        break;
      case keyRelease:
        if (actionRuning != actionNone) 
        {
          inputmode = inputIdle;
          actionRuning = actionNone;
          verb = verbNone;
          verb_valid = false;
          verb_ten = -1;
          verb_one = -1;
          noun_ten = -1;
          noun_one = -1;
          noun = verbNone;
          noun_valid = false;
          setLamp(off, lampKeyRelease);
          delay(10);
          printRegisterOFF(1);
          delay(20);
          printRegisterOFF(2);
          delay(20);
          printRegisterOFF(3);
          delay(20);
          printVerbNounProg();
          }
        break;
      default:
        break;
    }
    // check the input mode (Verb / Noun)
    switch (inputmode)
    {
      case inputIdle:
        break;
      case inputVerb:
        //lightVerblamp(yellow);
        input_Verb();
        break;
      case inputNoun:
        input_Noun();
        break;
    }
  // END check the input mode (Verb / Noun)
  old_key = current_key;
  keypressed = false;
  }
  printVerbNounProg(); 
  // END a key hase been pressed
  
  gps_test();

  /*
  #ifdef DEBUG
  
    EthernetClient client = server.available();
    if (client) {
      Serial.println("new client");
      // an http request ends with a blank line
      boolean currentLineIsBlank = true;
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          Serial.write(c);
          // if you've gotten to the end of the line (received a newline
          // character) and the line is blank, the http request has ended,
          // so you can send a reply
          if (c == '\n' && currentLineIsBlank) {
            // send a standard http response header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");  // the connection will be closed after completion of the response
            client.println("Refresh: 5");  // refresh the page automatically every 5 sec
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            
            client.println("<head>");
            client.println("<style>");
            client.println("table, th, td {");
            client.println("  border: 1px solid black;");
            client.println("  border-collapse: collapse;");
            client.println("}");
            client.println("th, td {");
            client.println("  padding: 5px;");
            client.println("}");
            client.println("th {");
            client.println("  text-align: left;");
            client.println("}");
            client.println("td {");
            client.println("  text-align: left;");
            client.println("  table-layout:fixed;");
            client.println("  width:40px;");
            client.println("  overflow:hidden;");
            client.println("  word-wrap:break-word;");
            client.println("}");
            client.println("</style>");
            client.println("</head>");
                      
            client.print("inputmode : ");client.print(inputmode);client.print("  ");client.println("<br />");
            
            client.println("<table>");
            client.println("<tr>");
            client.print("<td>progRunning</td><td>");client.print(progRunning);client.print("</td>");
            client.print("<td>actionRuning</td><td>");client.print(actionRuning);client.print("</td>");
            client.print("<td>action_valid</td><td>");client.print(action_valid);client.print("</td>");
            client.print("<td>action_found</td><td>");client.print(action_found);client.print("</td>");
            client.println("</tr>");
            client.println("<br />");
            
            client.println("<table>");
            client.println("<tr>");
            client.print("<td>verb</td><td>");client.print(verb);client.print("</td>");
            client.print("<td>verb_ten</td><td>");client.print(verb_ten);client.print("</td>");
            client.print("<td>verb_one</td><td>");client.print(verb_one);client.print("</td>");
            client.print("<td>verb_valid</td><td>");client.print(verb_valid);client.print("</td>");
            client.print("<td>verb_error</td><td>");client.print(verb_error);client.print("</td>");
            client.print("<td>blinkverb</td><td>");client.print(blinkverb);client.print("</td>");
            client.println("</tr>");
            client.println("<br />");
            
            client.println("<table>");
            client.println("<tr>");
            client.print("<td>noun</td><td>");client.print(noun);client.print("</td>");
            client.print("<td>noun_ten</td><td>");client.print(noun_ten);client.print("</td>");
            client.print("<td>noun_one</td><td>");client.print(noun_one);client.print("</td>");
            client.print("<td>noun_valid</td><td>");client.print(noun_valid);client.print("</td>");
            client.print("<td>noun_error</td><td>");client.print(noun_error);client.print("</td>");
            client.print("<td>blinknoun</td><td>");client.print(blinknoun);client.print("</td>");
            client.println("</tr>");
            client.println("<br />");
            
            client.println("<table>");
            client.println("<tr>");
            client.print("<td>prog</td><td>");client.print(prog);client.print("</td>");
            client.print("<td>prog_ten</td><td>");client.print(prog_ten);client.print("</td>");
            client.print("<td>prog_one</td><td>");client.print(prog_one);client.print("</td>");
            client.print("<td>old1_prog</td><td>");client.print(old1_prog);client.print("</td>");
            client.print("<td>blinkprog</td><td>");client.print(blinkprog);client.print("</td>");
            client.print("<td>prog_valid</td><td>");client.print(prog_valid);client.print("</td>");
            client.print("<td>prog_found</td><td>");client.print(prog_found);client.print("</td>");
            client.println("</tr>");
            client.println("<br />");
  
            client.println("<table>");
            client.println("<tr>");
            client.print("<td>register_num_1</td><td>");client.print(register_num_1);client.print("</td>");
            client.print("<td>register_num_2</td><td>");client.print(register_num_2);client.print("</td>");
            client.print("<td>register_num_3</td><td>");client.print(register_num_1);client.print("</td>");
            client.println("</tr>");
            client.println("<br />");
            
            client.println("<table>");
            client.println("<tr>");
            client.print("<td>current_key</td><td>");client.print(current_key);client.print("</td>");
            client.print("<td>current_key_int</td><td>");client.print(current_key_int);client.print("</td>");
            client.print("<td>keypressed</td><td>");client.print(keypressed);client.print("</td>");
            client.print("<td>old_key</td><td>");client.print(old_key);client.print("</td>");
            client.println("</tr>");
            client.println("<br />");
            
            client.println("<table>");
            client.println("<tr>");
            client.print("<td>toggle1000</td><td>");client.print(toggle1000);client.print("</td>");
            client.print("<td>toggle500</td><td>");client.print(toggle500);client.print("</td>");
            client.print("<td>toggle250</td><td>");client.print(toggle250);client.print("</td>");
            client.print("<td>global_state_1000</td><td>");client.print(global_state_1000);client.print("</td>");
            client.print("<td>global_state_500</td><td>");client.print(global_state_500);client.print("</td>");
            client.print("<td>global_state_250</td><td>");client.print(global_state_250);client.print("</td>");
            client.println("</tr>");
            client.println("<br />");
            
            client.println("</html>");
            break;
          }
          if (c == '\n') {
            // you're starting a new line
            currentLineIsBlank = true;
          } else if (c != '\r') {
            // you've gotten a character on the current line
            currentLineIsBlank = false;
          }
        }
      }
      // give the web browser time to receive the data
      delay(1);
      // close the connection:
      client.stop();
      Serial.println("client disconnected");
    }
  
  #endif // END debug
  */
  
}
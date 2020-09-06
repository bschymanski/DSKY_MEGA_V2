#include <Arduino.h>
#include <nextion.h>
#include <main.h>
#include <globals.h>

void nextion_enter(int serialport)  // Nextion "Enter"
{
  if (serialport == 1)
  {
    Serial1.write(0xff);
    Serial1.write(0xff);
    Serial1.write(0xff);
  }
  else if (serialport ==2)
  {
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
  }
}
// END Nextion "Enter"

void lightVerblamp(int color) // Verb Lamp
{
  switch (color)
  {
    case blue:
      Serial1.print("verblight.pco=BLUE");
      nextion_enter(1);
      break;
    case green:
      Serial1.print("verblight.pco=GREEN");
      nextion_enter(1);
      break;
    case yellow:
      Serial1.print("verblight.pco=YELLOW");
      nextion_enter(1);
      break;
    case red:
      Serial1.print("verblight.pco=RED");
      nextion_enter(1);
      break;
    case off:
      Serial1.print("verblight.pco=BLACK");
      nextion_enter(1);
      break;
    default:
      break;
  }
}
// END Verb Lamp

void lightNounlamp(int color) // Noun Lamp
{
  switch (color)
  {
    case blue:
      Serial1.print("nounlight.pco=BLUE");
      nextion_enter(1);
      break;
    case green:
      Serial1.print("nounlight.pco=GREEN");
      nextion_enter(1);
      break;
    case yellow:
      Serial1.print("nounlight.pco=YELLOW");
      nextion_enter(1);
      break;
    case red:
      Serial1.print("nounlight.pco=RED");
      nextion_enter(1);
      break;
    case off:
      Serial1.print("nounlight.pco=BLACK");
      nextion_enter(1);
      break;
    default:
      break;
  }
}
// END Noun Lamp

void lightProglamp(int color) // Prog Lamp
{
  switch (color)
  {
    case blue:
      Serial1.print("proglight.pco=BLUE");
      nextion_enter(1);
      break;
    case green:
      Serial1.print("proglight.pco=GREEN");
      nextion_enter(1);
      break;
    case yellow:
      Serial1.print("proglight.pco=YELLOW");
      nextion_enter(1);
      break;
    case red:
      Serial1.print("proglight.pco=RED");
      nextion_enter(1);
      break;
    case off:
      Serial1.print("proglight.pco=BLACK");
      nextion_enter(1);
      break;
    default:
      break;
  }
}
// END Prog Lamp

void lightCompActy(int color) // CompActy Lamp
{
  switch (color)
  {
    case blue:
      Serial1.print("compactylight.pco=BLUE");
      nextion_enter(1);
      break;
    case green:
      Serial1.print("compactylight.pco=GREEN");
      nextion_enter(1);
      break;
    case yellow:
      Serial1.print("compactylight.pco=YELLOW");
      nextion_enter(1);
      break;
    case off:
      Serial1.print("compactylight.pco=BLACK");
      nextion_enter(1);
      break;
    default:
      break;
  }
}
// END CompActy Lamp

void ELtestlamp(void) // Test Lamps on EL Board
{
  delay(100);
  lightVerblamp(off);
  lightVerblamp(off);
  delay(100);
  lightProglamp(off);
  delay(100);
  lightNounlamp(off);
  delay(100);
  lightCompActy(off);
  delay(200);
  lightVerblamp(green);
  delay(100);
  lightVerblamp(off);
  delay(100);
  lightVerblamp(green);
  delay(100);
  lightProglamp(green);
  delay(100);
  lightNounlamp(green);
  delay(100);
  //lightCompActy(green);

}
// END Test Lamps on EL Board

void printVerbNounProg(void) // print Verb / Noun / Prog
{
  // Print the verb
  if (verb == verbNone) // we don't have a valid verb yet, maybe we have started to enter one? print verb_ten and verb_one if they are bigger than -1
  {
    if (verb_ten >=0) // Print Verb_ten
    {
      Serial1.print("V1");
      Serial1.print(".txt=\"");
      if (blinkverb == false)
      {
        Serial1.print(verb_ten);
      }
      else if (blinkverb == true)
      {
        if (toggle500 == true)
        {
          Serial1.print(verb_ten);
        }
        else
        {
          Serial1.print(" ");
        }
      }
      Serial1.print("\"");
      nextion_enter(1);
    }
    else if (verb_ten < 0)
    {
      Serial1.print("V1");
      Serial1.print(".txt=\" \"");
      nextion_enter(1);
    }
    // END Print Verb_ten
    if (verb_one >=0) // Print Verb_one
    {
      Serial1.print("V2");
      Serial1.print(".txt=\"");
      if (blinkverb == false) 
      {
        Serial1.print(verb_one);
      }
      else if (blinkverb == true)
      {
        if (toggle500 == true)
        {
          Serial1.print(verb_one);
        }
        else
        {
          Serial1.print(" ");
        }
      }
      Serial1.print("\"");
      nextion_enter(1);
    }
    else if (verb_one < 0)
    {
      Serial1.print("V2");
      Serial1.print(".txt=\" \"");
      nextion_enter(1);
    }
    // END Print Verb_one
  }
  else if (verb >= 0 && verb < 100) // Print valid verb
  {
    Serial1.print("V1");
    Serial1.print(".txt=\"");
    if (blinkverb == false)
    {
      Serial1.print(verb_ten);
    }
    else if (blinkverb == true)
    {
      if (toggle500 == true)
      {
        Serial1.print(verb_ten);
      }
      else
      {
        Serial1.print(" ");
      }
    }
    Serial1.print("\"");
    nextion_enter(1);

    Serial1.print("V2");
    Serial1.print(".txt=\"");
    if (blinkverb == false) 
    {
      Serial1.print(verb_one);
    }
    else if (blinkverb == true)
    {
      if (toggle500 == true)
      {
        Serial1.print(verb_one);
      }
      else
      {
        Serial1.print(" ");
      }
    }
    Serial1.print("\"");
    nextion_enter(1);
  } //  END Print valid verb  
  // Print the verb


  // Print the noun
  if (noun == nounNone) // we don't have a valid noun yet, maybe we have started to enter one? print noun_ten and noun_one if they are bigger than -1
  {
    if (noun_ten >=0) // Print noun_ten
    {
      Serial1.print("N1");
      Serial1.print(".txt=\"");
      if (blinknoun == false)
      {
        Serial1.print(noun_ten);
      }
      else if (blinknoun == true)
      {
        if (toggle500 == true)
        {
          Serial1.print(noun_ten);
        }
        else
        {
          Serial1.print(" ");
        }
      }
      Serial1.print("\"");
      nextion_enter(1);
    }
    else if (noun_ten < 0)
    {
      Serial1.print("N1");
      Serial1.print(".txt=\" \"");
      nextion_enter(1);
    }
    // END Print noun_ten
    if (noun_one >=0) // Print noun_one
    {
      Serial1.print("N2");
      Serial1.print(".txt=\"");
      if (blinknoun == false) 
      {
        Serial1.print(noun_one);
      }
      else if (blinknoun == true)
      {
        if (toggle500 == true)
        {
          Serial1.print(noun_one);
        }
        else
        {
          Serial1.print(" ");
        }
      }
      Serial1.print("\"");
      nextion_enter(1);
    }
    else if (noun_one < 0)
    {
      Serial1.print("N2");
      Serial1.print(".txt=\" \"");
      nextion_enter(1);
    }
    // END Print noun_one
  }
  else if (noun >= 0 && noun < 100) // Print Nalid noun
  {
    Serial1.print("N1");
    Serial1.print(".txt=\"");
    if (blinknoun == false)
    {
      Serial1.print(noun_ten);
    }
    else if (blinknoun == true)
    {
      if (toggle500 == true)
      {
        Serial1.print(noun_ten);
      }
      else
      {
        Serial1.print(" ");
      }
    }
    Serial1.print("\"");
    nextion_enter(1);

    Serial1.print("N2");
    Serial1.print(".txt=\"");
    if (blinknoun == false) 
    {
      Serial1.print(noun_one);
    }
    else if (blinknoun == true)
    {
      if (toggle500 == true)
      {
        Serial1.print(noun_one);
      }
      else
      {
        Serial1.print(" ");
      }
    }
    Serial1.print("\"");
    nextion_enter(1);
  } //  END Print valid noun  
  // Print the noun

   // Print the prog
  if (prog == progNone) // we don't have a valid prog yet, maybe we have started to enter one? print prog_ten and prog_one if they are bigger than -1
  {
    if (prog_ten >=0) // Print prog_ten
    {
      Serial1.print("P1");
      Serial1.print(".txt=\"");
      if (blinkprog == false)
      {
        Serial1.print(prog_ten);
      }
      else if (blinkprog == true)
      {
        if (toggle500 == true)
        {
          Serial1.print(prog_ten);
        }
        else
        {
          Serial1.print(" ");
        }
      }
      Serial1.print("\"");
      nextion_enter(1);
    }
    else if (prog_ten < 0)
    {
      Serial1.print("P1");
      Serial1.print(".txt=\" \"");
      nextion_enter(1);
    }
    // END Print prog_ten
    if (prog_one >=0) // Print prog_one
    {
      Serial1.print("P2");
      Serial1.print(".txt=\"");
      if (blinkprog == false) 
      {
        Serial1.print(prog_one);
      }
      else if (blinkprog == true)
      {
        if (toggle500 == true)
        {
          Serial1.print(prog_one);
        }
        else
        {
          Serial1.print(" ");
        }
      }
      Serial1.print("\"");
      nextion_enter(1);
    }
    else if (prog_one < 0)
    {
      Serial1.print("P2");
      Serial1.print(".txt=\" \"");
      nextion_enter(1);
    }
    // END Print prog_one
  }
  else if (prog >= 0 && prog < 100) // Print Nalid prog
  {
    Serial1.print("P1");
    Serial1.print(".txt=\"");
    if (blinkprog == false)
    {
      Serial1.print(prog_ten);
    }
    else if (blinkprog == true)
    {
      if (toggle500 == true)
      {
        Serial1.print(prog_ten);
      }
      else
      {
        Serial1.print(" ");
      }
    }
    Serial1.print("\"");
    nextion_enter(1);

    Serial1.print("P2");
    Serial1.print(".txt=\"");
    if (blinkprog == false) 
    {
      Serial1.print(prog_one);
    }
    else if (blinkprog == true)
    {
      if (toggle500 == true)
      {
        Serial1.print(prog_one);
      }
      else
      {
        Serial1.print(" ");
      }
    }
    Serial1.print("\"");
    nextion_enter(1);
  } //  END Print valid prog  
  // EndPrint the prog
}
// print Verb / Noun / Prog

void print_REG_NUM(int dregister, int place, int number)  // print a single number on the register (5 highest place, 1 lowest place)
{
    Serial1.print("R");
    Serial1.print(dregister);
    Serial1.print("N");
    Serial1.print(place);
    Serial1.print(".txt=\"");
    Serial1.print(number);
    Serial1.print("\"");
    nextion_enter(1);
}
void print_REG_OFF(int dregister, int place)
{
    Serial1.print("R");
    Serial1.print(dregister);
    Serial1.print("N");
    Serial1.print(place);
    Serial1.print(".txt=\" \"");
    nextion_enter(1);
}

void print_REG_PLUS(int dregister)
{
    Serial1.print("R");
    Serial1.print(dregister);
    Serial1.print("sign.txt=\"+\"");
    nextion_enter(1);
}

void print_REG_MINUS(int dregister)
{
    Serial1.print("R");
    Serial1.print(dregister);
    Serial1.print("sign.txt=\"-\"");
    nextion_enter(1);
}
void print_REG_SIGNOFF(int dregister)
{
    Serial1.print("R");
    Serial1.print(dregister);
    Serial1.print("sign.txt=\" \"");
    nextion_enter(1);
}

void printRegister(int dregister, long number, bool leadzero = true, bool blink = false, bool alarm = false, bool signoff = false)
{
    // lets look at the number
    int one = 0;
    int ten = 0;
    int hundred = 0;
    long thousand = 0;
    long tenthousand = 0;
    // first, check if the number is positive or negative and set the plus or minus sign
    if (number < 0)
    {
        if (signoff == false)
        {
          number = -number;
          if (blink == true && toggle500 == false)
          {
            print_REG_SIGNOFF(dregister);
          }
          else
          {
            print_REG_MINUS(dregister);
          }
        }
        else if (signoff == true)
        {
          number = -number;
          print_REG_SIGNOFF(dregister);
        }
    }
    else 
    {
        if (signoff == false)
        {
          if (blink == true && toggle500 == false)
          {
            print_REG_SIGNOFF(dregister);
          }
          else
          {
            print_REG_PLUS(dregister);
          }
        }
        else if (signoff == true)
        {
          print_REG_SIGNOFF(dregister);
        }
    }
    // now seperate the number
    if (number == 0)
    {
        one = int(number);
        
        if (leadzero == true)
        {
          if (blink == true && toggle500 == false)
          {
            print_REG_OFF(dregister, 5);
            print_REG_OFF(dregister, 4);
            print_REG_OFF(dregister, 3);
            print_REG_OFF(dregister, 2);
            print_REG_OFF(dregister, 1);
          }
          else
          {
            print_REG_NUM(dregister,5, tenthousand);
            print_REG_NUM(dregister,4, thousand);
            print_REG_NUM(dregister,3, hundred);
            print_REG_NUM(dregister,2, ten);
          }
        }
        else
        {
          print_REG_OFF(dregister, 5);
          print_REG_OFF(dregister, 4);
          print_REG_OFF(dregister, 3);
          print_REG_OFF(dregister, 2);
        }
        print_REG_NUM(dregister,1, one);
    }
    else if ((number > 0) && (number < 10))
    {
        one = int(number);
        if (leadzero == true)
        {
          if (blink == true && toggle500 == false)
          {
            print_REG_OFF(dregister, 5);
            print_REG_OFF(dregister, 4);
            print_REG_OFF(dregister, 3);
            print_REG_OFF(dregister, 2);
            print_REG_OFF(dregister, 1);
          }
          else
          {
            print_REG_NUM(dregister,5, tenthousand);
            print_REG_NUM(dregister,4, thousand);
            print_REG_NUM(dregister,3, hundred);
            print_REG_NUM(dregister,2, ten);
          }
        }
        else
        {
          print_REG_OFF(dregister, 5);
          print_REG_OFF(dregister, 4);
          print_REG_OFF(dregister, 3);
          print_REG_OFF(dregister, 2);
        }
        if (blink == true && toggle500 == false)
        {
          print_REG_OFF(dregister, 5);
          print_REG_OFF(dregister, 4);
          print_REG_OFF(dregister, 3);
          print_REG_OFF(dregister, 2);
          print_REG_OFF(dregister, 1);
        }
        else
        {
          if (blink == true && toggle500 == false)
          {
            print_REG_OFF(dregister, 5);
            print_REG_OFF(dregister, 4);
            print_REG_OFF(dregister, 3);
            print_REG_OFF(dregister, 2);
            print_REG_OFF(dregister, 1);
          }
          else
          {
            print_REG_NUM(dregister,1, one);
          }
        }
    }
    else if ((number >= 10) && (number < 100))
    {   
        one = number % 10;
        ten = (number - one) / 10;
        if (leadzero == true)
        {
          if (blink == true && toggle500 == false)
          {
            print_REG_OFF(dregister, 5);
            print_REG_OFF(dregister, 4);
            print_REG_OFF(dregister, 3);
            print_REG_OFF(dregister, 2);
            print_REG_OFF(dregister, 1);
          }
          else
          {
            print_REG_NUM(dregister,5, tenthousand);
            print_REG_NUM(dregister,4, thousand);
            print_REG_NUM(dregister,3, hundred);
          }
        }
        else
        {
          print_REG_OFF(dregister, 5);
          print_REG_OFF(dregister, 4);
          print_REG_OFF(dregister, 3);
        }
        if (blink == true && toggle500 == false)
        {
          print_REG_OFF(dregister, 5);
          print_REG_OFF(dregister, 4);
          print_REG_OFF(dregister, 3);
          print_REG_OFF(dregister, 2);
          print_REG_OFF(dregister, 1);
        }
        else
        {
          print_REG_NUM(dregister,2, ten);
          print_REG_NUM(dregister,1, one);
        }
    }
    else if ((number >= 100) && (number < 1000))
    {
        one = number % 10;
        ten = (number / 10) % 10;
        hundred = (number / 100) % 10;
        if (leadzero == true)
        {
          if (blink == true && toggle500 == false)
          {
            print_REG_OFF(dregister, 5);
            print_REG_OFF(dregister, 4);
            print_REG_OFF(dregister, 3);
            print_REG_OFF(dregister, 2);
            print_REG_OFF(dregister, 1);
          }
          else
          {
            print_REG_NUM(dregister,5, tenthousand);
            print_REG_NUM(dregister,4, thousand);
          }
        }
        else
        {
          print_REG_OFF(dregister, 5);
          print_REG_OFF(dregister, 4);
        }
        if (blink == true && toggle500 == false)
        {
          print_REG_OFF(dregister, 5);
          print_REG_OFF(dregister, 4);
          print_REG_OFF(dregister, 3);
          print_REG_OFF(dregister, 2);
          print_REG_OFF(dregister, 1);
        }
        else
        {
          print_REG_NUM(dregister,3, hundred);
          print_REG_NUM(dregister,2, ten);
          print_REG_NUM(dregister,1, one);
        }
    }
    else if ((number >= 1000) && (number < 10000))
    {
        one = number % 10;
        ten = (number / 10) % 10;
        hundred = (number / 100) % 10;
        thousand = (number / 1000) % 10;
        if (leadzero == true)
        {
          if (blink == true && toggle500 == false)
          {
            print_REG_OFF(dregister, 5);
            print_REG_OFF(dregister, 4);
            print_REG_OFF(dregister, 3);
            print_REG_OFF(dregister, 2);
            print_REG_OFF(dregister, 1);
          }
          else
          {
            print_REG_NUM(dregister,5, tenthousand);
          }
        }
        else
        {
          print_REG_OFF(dregister, 5);
        }
        if (blink == true && toggle500 == false)
        {
          print_REG_OFF(dregister, 5);
          print_REG_OFF(dregister, 4);
          print_REG_OFF(dregister, 3);
          print_REG_OFF(dregister, 2);
          print_REG_OFF(dregister, 1);
        }
        else
        {
          print_REG_NUM(dregister,4, thousand);
          print_REG_NUM(dregister,3, hundred);
          print_REG_NUM(dregister,2, ten);
          print_REG_NUM(dregister,1, one);
        }
    }
    else if ((number >= 10000) && (number < 100000))
    {
        one = number % 10;
        ten = (number / 10) % 10;
        hundred = (number / 100) % 10;
        thousand = (number / 1000) % 10;
        tenthousand = (number / 10000) % 10;
        if (blink == true && toggle500 == false)
        {
          print_REG_OFF(dregister, 5);
          print_REG_OFF(dregister, 4);
          print_REG_OFF(dregister, 3);
          print_REG_OFF(dregister, 2);
          print_REG_OFF(dregister, 1);
        }
        else
        {
          print_REG_NUM(dregister,5, tenthousand);
          print_REG_NUM(dregister,4, thousand);
          print_REG_NUM(dregister,3, hundred);
          print_REG_NUM(dregister,2, ten);
          print_REG_NUM(dregister,1, one);
        }
    }
    else if ((number >= 100000))
    {
        print_REG_SIGNOFF(dregister);
        print_REG_OFF(dregister, 5);
        print_REG_OFF(dregister, 4);
        print_REG_OFF(dregister, 3);
        print_REG_OFF(dregister, 2);
        print_REG_OFF(dregister, 1);
    }
    else if ((number <= -100000))
    {
        print_REG_SIGNOFF(dregister);
        print_REG_OFF(dregister, 5);
        print_REG_OFF(dregister, 4);
        print_REG_OFF(dregister, 3);
        print_REG_OFF(dregister, 2);
        print_REG_OFF(dregister, 1);
    }
    // show the number
  
}

void printRegisterOFF(int dregister)
{
  print_REG_OFF(dregister, 5);
  print_REG_OFF(dregister, 4);
  print_REG_OFF(dregister, 3);
  print_REG_OFF(dregister, 2);
  print_REG_OFF(dregister, 1);
}
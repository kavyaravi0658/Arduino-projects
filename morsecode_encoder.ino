#include <Arduino.h>

#define DOT   1
#define DASH  2

#ifndef ledpinconfig
#define ledpinconfig
#define led 13
#endif 

#ifndef alarmpinconfig
#define alarmpinconfig
#define alarm 5
#endif 

static const uint8_t morse[][7] = {
{NULL, NULL, NULL, NULL, NULL, NULL, 0  }, //NULL
{DOT,  DASH, NULL, NULL, NULL, NULL, 'A'}, //A
{DASH, DOT,  DOT,  DOT,  NULL, NULL, 'B'}, //B
{DASH, DOT,  DASH, DOT,  NULL, NULL, 'C'}, //C
{DASH, DOT,  DOT,  NULL, NULL, NULL, 'D'}, //D
{DOT,  NULL, NULL, NULL, NULL, NULL, 'E'}, //E
{DOT,  DOT,  DASH,  DOT, NULL, NULL, 'F'}, //F
{DASH, DASH, DOT,  NULL, NULL, NULL, 'G'}, //G
{DOT,  DOT,  DOT,  DOT,  NULL, NULL, 'H'}, //H
{DOT,  DOT,  NULL, NULL, NULL, NULL, 'I'}, //I
{DOT,  DASH, DASH, DASH, NULL, NULL, 'J'}, //J
{DASH, DOT,  DASH, NULL, NULL, NULL, 'K'}, //K
{DOT,  DASH, DOT,  DOT,  NULL, NULL, 'L'}, //L
{DASH, DASH, NULL, NULL, NULL, NULL, 'M'}, //M
{DASH, DOT,  NULL, NULL, NULL, NULL, 'N'}, //N
{DASH, DASH, DASH, NULL, NULL, NULL, 'O'}, //O
{DOT,  DASH, DASH, DOT,  NULL, NULL, 'P'}, //P
{DASH, DASH, DOT,  DASH, NULL, NULL, 'Q'}, //Q
{DOT,  DASH, DOT,  NULL, NULL, NULL, 'R'}, //R
{DOT,  DOT,  DOT,  NULL, NULL, NULL, 'S'}, //S
{DASH, NULL, NULL, NULL, NULL, NULL, 'T'}, //T
{DOT,  DOT,  DASH, NULL, NULL, NULL, 'U'}, //U
{DOT,  DOT,  DOT,  DASH, NULL, NULL, 'V'}, //V
{DOT,  DASH, DASH, NULL, NULL, NULL, 'W'}, //W
{DASH, DOT,  DOT,  DASH, NULL, NULL, 'X'}, //X
{DASH, DOT,  DASH, DASH, NULL, NULL, 'Y'}, //Y
{DASH, DASH, DOT,  DOT,  NULL, NULL, 'Z'}, //Z
{DASH, DASH, DASH, DASH, DASH, NULL, '0'}, //0
{DOT,  DASH, DASH, DASH, DASH, NULL, '1'}, //1
{DOT,  DOT,  DASH, DASH, DASH, NULL, '2'}, //2
{DOT,  DOT,  DOT,  DASH, DASH, NULL, '3'}, //3
{DOT,  DOT,  DOT,  DOT,  DASH, NULL, '4'}, //4
{DOT,  DOT,  DOT,  DOT,  DOT,  NULL, '5'}, //5
{DASH, DOT,  DOT,  DOT,  DOT,  NULL, '6'}, //6
{DASH, DASH, DOT,  DOT,  DOT,  NULL, '7'}, //7
{DASH, DASH, DASH, DOT,  DOT,  NULL, '8'}, //8
{DASH, DASH, DASH, DASH, DOT,  NULL, '9'}, //9
{DOT,  DASH, DOT,  DASH, DOT,  DASH, '.'}, //[.]
{DASH, DASH, DOT,  DOT,  DASH, DASH, ','}, //[,]
{DASH, DASH, DASH, DOT,  DOT,  DOT , ':'}, //[:]
{DOT,  DOT,  DASH, DASH, DOT,  DOT , '?'}, //[?]
{DOT,  DASH, DASH, DASH, DASH, DOT , '\''}, //[']
{DASH, DOT,  DOT,  DOT,  DOT,  DASH, '-'}, //[-]
{DASH, DOT,  DOT,  DASH, DOT,  NULL, '/'}, //[/]
{DASH, DOT,  DASH, DASH, DOT,  NULL, '('}, //[(]
{DASH, DOT,  DASH, DASH, DOT,  DASH, ')'}, //[)]
{DOT,  DASH, DOT,  DOT,  DASH, DOT , '\"'}, //["]
{DASH, DOT,  DOT,  DOT,  DASH, NULL, '='}, //[=]
{DOT,  DASH, DOT,  DASH,  DOT, NULL, '+'}, //[+]
{DOT,  DASH, DOT,  DOT,  DOT,  DOT , '!'}, //[!]
{DOT,  DOT,  DOT,  DASH, DOT,  DASH, '%'}, //[EOF]
{DASH, DOT,  DASH, DOT,  DASH, NULL, '$'}, //[BEGIN]
{DASH, DOT,  DOT,  DASH, NULL, NULL, 'X'}, //[x]
{DOT,  DASH, DASH, DOT,  DASH, DOT , '@'}, //[@]
};

uint8_t serialarray[50], serialcount;

void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Serial.println(F("Morse Encoder using Arduino NANO"));
  
  pinMode(alarm, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(alarm, LOW);
  digitalWrite(led, LOW);
}

void loop()
{
  if(Serial.available() > 0) serialcount = Serial.readBytesUntil('\n', serialarray, 50);

  if(serialcount)
  {
    Serial.println("--------NEW DATA FOUND-------");
    Serial.println((char*)serialarray); Serial.println(serialcount);

    for(uint8_t k = 0; k < serialcount; k++)
    {
      Serial.print((char)toupper(serialarray[k]));
      Serial.print(" :- ");

      for(uint8_t j = 1; j < 54; j++)
      {
        if(toupper(serialarray[k]) == morse[j][6])
        {
          for(uint8_t l = 0; l < 6; l++)
          {
            switch(morse[j][l])
            {
              case DOT:
              Serial.print("DOT  ");
              digitalWrite(alarm, HIGH);
              digitalWrite(led, HIGH);
              delay(300);
              digitalWrite(alarm, LOW);
              digitalWrite(led, LOW);
              delay(300);
              break;

              case DASH:
              Serial.print("DASH ");
              digitalWrite(alarm, HIGH);
              digitalWrite(led, HIGH);
              delay(600);
              digitalWrite(alarm, LOW);
              digitalWrite(led, LOW);
              delay(600);
              break;

              case NULL: default:
              Serial.print("NULL ");
              delay(200);
              break;
            }
          }
          Serial.println("");
          break;
        }
        else continue;
      }
    }
    Serial.flush();
    memset(serialarray, '\0', sizeof(serialarray));
    serialcount = 0;
  }
}

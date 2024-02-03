#include "Arduino.h"

#define CA_AH 0
#define CA_V 1
#define CA_A 2
#define CA_S 3
#define CA_D 4
#define CA_DEG 5
#define CA_RPM 6
#define CA_HW 7
#define CA_NM 8
#define CA_THI 9
#define CA_THO 10
#define CA_AUXA 11
#define CA_AUXD 12
#define CA_FLGS 13

char CA_data[14][8];
bool newData =  false;

void encodeCA(Stream &CAserial) {
  char CA_txt_outputbuffer[14][8];
  char letter; //Stores serial reading into char array
  bool new_letter = false; //Flag for new letter coming in
  int word_num = 0; //tracks which word it is on
  int letter_num = 0; //tracks which letter it is on in word

  while (1) {
    if (CAserial.available()) {
      letter = CAserial.read();
      // Serial.print(" ");
      // Serial.print(int(letter));
      new_letter = true;
    }
    if (new_letter) {
      if (letter == '\n') {
        newData = 1;
        word_num = 0;
        memcpy(CA_data, CA_txt_outputbuffer, sizeof(char)* 14 * 8); //copies from buffer into CA_data
        return;
      }
      else if (letter == '\t') {
        letter_num = 0;
        if (word_num<13) { //13 is last position in CA_txt_outputbuffer
          word_num++;
        }
      }
      else if (int(letter) == 90) {
        ; //put condition for weird 0.0 error
      }
      else {
        if (letter_num < 7) { //7 is the max length of char array [8]
          CA_txt_outputbuffer[word_num][letter_num++] = letter; //stores letter into correct array position
          CA_txt_outputbuffer[word_num][letter_num] = '\0'; //end of character
        }
      }
      new_letter = false;
    }
  }
}

void printCA() {
  if (newData) {
    int word_num = 0;
    for (int i = 0; i<14; i++) { //13 is max value [14]
      Serial.println(CA_data[i]);
    }
    Serial.println();
    newData = false;
  }
}

void setup() {
  Serial.begin(115200);
  // Serial2.begin(9600, SERIAL_8N1, 14, 13); // 14, 13 For using with USB Cable
  Serial2.begin(9600, SERIAL_8N1, 13, 14); // 13, 14 For using with Cycle Analyst
}

void loop() {
  encodeCA(Serial2);
  printCA();
  delay(100);
}
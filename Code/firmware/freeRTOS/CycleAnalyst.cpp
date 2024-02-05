#include "CycleAnalyst_task.h"

char CA_data[14][8] = {"0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0"};
char CA_txt_outputbuffer[14][8];
bool newData =  false;

void encodeCA(Stream &CAserial) {
  char CA_txt_outputbuffer[14][8] = {"0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0"};
  char letter; //Stores serial reading into char array
  bool new_letter = false; //Flag for new letter coming in
  int word_num = 0; //tracks which word it is on
  int letter_num = 0; //tracks which letter it is on in word

  while (1) {
    if (CAserial.available()) {
      letter = CAserial.read();
      // Serial.print(" ");
      // Serial.print(letter);
      new_letter = true;
    }
    else {
      vTaskDelay(50 / portTICK_PERIOD_MS); //check every 50 ms
      //Serial.println("NOTHING READ");
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

void setupCA() {
  // Serial2.begin(9600, SERIAL_8N1, 14, 13); // 14, 13 For using with USB Cable
  Serial2.begin(9600, SERIAL_8N1, 13, 14); // 13, 14 For using with Cycle Analyst
}

void loopCA(void *parameter) {
  while (1) {
    encodeCA(Serial2);
    //printCA();
    vTaskDelay(500 / portTICK_PERIOD_MS); //Check every 100 ms
  }
}
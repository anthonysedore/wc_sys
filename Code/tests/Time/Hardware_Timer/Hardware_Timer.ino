hw_timer_t * timer = NULL;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  timer = timerBegin(0, 80, true);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Seconds: ");
  
  Serial.println(timerReadSeconds(timer));
  delay(100);
  if (touchRead(13) <= 40) {
    if (timerStarted(timer)) {
      timerStop(timer);
    }
    else {
      timerStart(timer);
    }
    delay(1000);
  }
  else if (touchRead(32) <= 40) {
    timerRestart(timer);
    delay(1000);
  }
    
}

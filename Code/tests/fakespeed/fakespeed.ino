hw_timer_t * timer = NULL;
hw_timer_t * timer2 = NULL;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  timer = timerBegin(0, 80, true);
  timer2 = timerBegin(0, 80, true);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(checkSpeed());
  Serial.println(checkBatteryVoltage());
  delay(200);
}

float checkSpeed(void) {
  float speed;
  double time = timerReadSeconds(timer2);
  speed = 5*cos(time*0.2)-0.5*sin(time*0.5)+20;
  return speed; 
}

float checkBatteryVoltage(void) {
  float voltage;
  double time = timerReadSeconds(timer2);
  voltage = 84-0.05*time;
  return voltage; 
}

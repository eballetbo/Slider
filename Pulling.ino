void setupStepper() {
  pinMode(endStopA, INPUT);
  pinMode(endStopB, INPUT);
  stepper.setMaxSpeed(10000);
  stepper.setAcceleration(1000);
}

void go_to_a() {
  stepper.setSpeed(-1 * stepper_default_speed);
  while (digitalRead(endStopA))
      stepper.runSpeed();
}

void go_to_b() {
  stepper.setSpeed(stepper_default_speed);
  while (digitalRead(endStopB))
      stepper.runSpeed();
}

void pull_distance_over_time(float distance, float distance_mm_multiplier, float duration, float duration_sec_multiplier) {
  float mm = (distance * distance_mm_multiplier);
  float sec = (duration * duration_sec_multiplier);
  pull_millimeters_over_seconds(mm, sec);
}

void pull_millimeters_over_seconds(float millimeters, float seconds) {
  int endStop;
  long steps_to_move = millimetersToSteps(millimeters);
  float steps_per_second = ((float)steps_to_move / seconds);

  stepper.setCurrentPosition(0);
  stepper.moveTo(steps_to_move);
  stepper.setSpeed(steps_per_second);

  endStop = steps_to_move < 0 ? endStopA : endStopB;
 
  while (stepper.distanceToGo() != 0 && digitalRead(endStop))
      stepper.runSpeed();
}

long millimetersToSteps(float millimeters) {
  float belt_mm_per_tooth = 2;
  float pulley_teeth = 20;
  float mm_per_revolution = (belt_mm_per_tooth * pulley_teeth);
  float revolutions_needed = (millimeters / mm_per_revolution);
  float steps_per_revolution = 1600;
  float steps_needed = (revolutions_needed * steps_per_revolution);
  return (long)round(steps_needed);
}


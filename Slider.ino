#include <AccelStepper.h>
#include <MultiStepper.h>

#include <SPI.h>
#include <WiFi101.h>

int led =  LED_BUILTIN;

char ssid[] = "wifi101-network"; // created AP name

int status = WL_IDLE_STATUS;

WiFiServer server(80);

AccelStepper stepper(1, 7, 6);
const int endStopA = 4;
const int endStopB = 5;
const int stepper_default_speed = 1000;

float distance = 0;
float distance_mm_multiplier = 10;
float duration = 0;
float duration_sec_multiplier = 1;
int direction = -1;

void setup() {
  setupStepper();
  setupWiFi();
}

void loop() {
  webListenForClients();
}


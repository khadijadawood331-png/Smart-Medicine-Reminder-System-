/**
 * Smart Medicine Reminder System
 * Developed by: [Khadijah Dawood]
 * 
 * Hardware Connections:
 * - Arduino Nano Board
 * - DS1307 RTC Module: SDA -> A4, SCL -> A5
 * - I2C LCD (16x2): SDA -> A4, SCL -> A5
 * - LED Indicator: Digital Pin 12
 * - Alert Buzzer: Digital Pin 3
 * - Stop Button: Digital Pin 2 (Uses internal pull-up resistor)
 */

#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>

// Assigning hardware pins as per circuit diagram
const uint8_t LED_PIN     = 12;   // LED connected to Pin 12
const uint8_t BUZZER_PIN  = 3;    // Buzzer connected to Pin 3
const uint8_t BUTTON_PIN  = 2;    // Button connected to Pin 2

// Setting the medicine reminder alarm time (24-Hour format)
const uint8_t TARGET_HOUR   = 7;   // 7 AM
const uint8_t TARGET_MINUTE = 24;  // 24 Minutes

// Initializing the RTC and LCD objects
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Global state variables for the system
bool isAlarmActive       = false;   // Tracks if the alarm is currently ringing
bool isTriggeredForToday = false;   // Prevents the alarm from repeating within the same minute
bool showSuccessMessage  = false;   // Controls the thank-you display screen
unsigned long successMessageStartTime = 0; // Stores time to keep message on screen

// This function runs when the alarm is triggered
void triggerAlarmSequence() {
  digitalWrite(LED_PIN, HIGH);  // Turn ON the LED indicator
  
  // Creates a clean beeping sound for the buzzer without locking the system
  static unsigned long lastBeepTime = 0;
  static bool toggleTone = false;
  
  if (millis() - lastBeepTime >= 150) {
    lastBeepTime = millis();
    toggleTone = !toggleTone;
    if (toggleTone) {
      tone(BUZZER_PIN, 1000);   // Generate sound at 1kHz frequency
    } else {
      noTone(BUZZER_PIN);       // Pause sound
    }
  }

  // Show medicine alert messages on the LCD screen
  lcd.setCursor(0, 0);
  lcd.print("TAKE YOUR       ");
  lcd.setCursor(0, 1);
  lcd.print("MEDICINE NOW!   ");
}

// This function turns off everything when user presses the button
void deactivateAlarmSequence() {
  isAlarmActive = false;
  
  noTone(BUZZER_PIN);           // Stop the buzzer sound
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);   // Turn OFF the LED
  
  // Switch system state to show the success message
  showSuccessMessage = true;
  successMessageStartTime = millis();
  lcd.clear();
}

// Standard screen view: Shows the digital clock
void displayCurrentTime(DateTime now) {
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  if (now.hour() < 10) lcd.print('0');
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  if (now.minute() < 10) lcd.print('0');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  if (now.second() < 10) lcd.print('0');
  lcd.print(now.second(), DEC);
  
  lcd.setCursor(0, 1);
  lcd.print("System Active... ");
}

void setup() {
  // Configuring hardware pins as Input or Output
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Safe mode: button pin connects to GND

  // Starting up the LCD screen
  lcd.init();
  lcd.backlight();

  // Checking if RTC module is wired properly
  if (!rtc.begin()) {
    lcd.print("RTC Boot Error!");
    while (1); // Halt the system if hardware is missing
  }

  // If the RTC lost power or is fresh, sync it with the computer compile time
  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime currentTimestamp = rtc.now(); // Read current time from RTC

  // Check if current time matches the scheduled medicine time
  if (currentTimestamp.hour() == TARGET_HOUR && currentTimestamp.minute() == TARGET_MINUTE) {
    if (!isTriggeredForToday) {
      isAlarmActive = true;
      isTriggeredForToday = true;
      showSuccessMessage = false; 
    }
  }

  // Clear the daily token once the target alarm minute is over
  if (currentTimestamp.minute() != TARGET_MINUTE) {
    isTriggeredForToday = false;
  }

  // Main system state manager
  if (isAlarmActive) {
    triggerAlarmSequence();

    // Check if user has pressed the stop button (Button goes LOW when pressed)
    if (digitalRead(BUTTON_PIN) == LOW) {
      deactivateAlarmSequence();
    }
  } 
  else if (showSuccessMessage) {
    // Show confirmation screen for exactly 5 seconds (5000 milliseconds)
    lcd.setCursor(0, 0);
    lcd.print("Meds Taken!     ");
    lcd.setCursor(0, 1);
    lcd.print("Stay Healthy!   ");
    
    if (millis() - successMessageStartTime >= 5000) {
      showSuccessMessage = false;
      lcd.clear(); // Clear screen and go back to normal clock mode
    }
  } 
  else {
    displayCurrentTime(currentTimestamp);
    delay(200); // Standard screen refresh rate
  }
}

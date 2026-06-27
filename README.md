# IoT Smart Medicine Reminder System ("Medisync v1")

A multidisciplinary Mechatronics project featuring customized C++ firmware and embedded circuitry to ensure patients never miss a critical medicine dosage.

## 🛠️ Hardware Components Integrated
* **Arduino Nano v3.0** (Central Microcontroller)
* **DS1307 RTC Module** (Real-Time Clock via I2C)
* **16x2 LCD Screen with I2C Backpack** (Display Unit)
* **5V Piezo Buzzer** (Auditory Alert Indicator)
* **5mm Red LED** (Visual Notification Indicator)
* **Tactile Push Button** (Alarm Acknowledge/Reset Switch)

## 📐 Schematic & Circuit Diagram
![Circuit Layout](Smart_Medicine_Reminder_Circuit.jpg)

## 🚀 Key Firmware Logic Features
* **PID-Style Non-Blocking Beep Sequence:** Uses `millis()` for buzzer alerts instead of `delay()`, ensuring the stop button triggers instantly without any hardware lag.
* **Smart Token Anti-Repeat Mechanism:** Prevents the system from continuous loop re-triggering during the target minute once acknowledged.
* **Low-Power Safe Architecture:** Uses internal pull-up resistor setup for the reset switch to protect the microcontroller from voltage surges.
https://i.postimg.cc/L6kFnBb3/IMG-20260628-WA0002.jpg


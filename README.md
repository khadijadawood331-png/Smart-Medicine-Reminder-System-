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
![Circuit Layout](https://i.postimg.cc/L6kFnBb3/IMG-20260628-WA0002.jpg)

## 🔩 CAD Model Preview 
[![Screenshot-20260626-054912-display-0-png.png](https://i.postimg.cc/kgwCSZZY/Screenshot-20260626-054912-display-0-png.png)](https://postimg.cc/3kyz5L32)
[![Screenshot-20260626-055234-display-0-png.png](https://i.postimg.cc/gkzm0mtn/Screenshot-20260626-055234-display-0-png.png)](https://postimg.cc/c6bV9ySS)
[![Screenshot-20260626-055625-display-0-png.png](https://i.postimg.cc/Hk0w909T/Screenshot-20260626-055625-display-0-png.png)](https://postimg.cc/mPD1bHnn)
[![Screenshot-20260626-055803-display-0-png.png](https://i.postimg.cc/jdPgB749/Screenshot-20260626-055803-display-0-png.png)](https://postimg.cc/ppVJFy7Y)

## 🚀 Key Firmware Logic Features
* **PID-Style Non-Blocking Beep Sequence:** Uses `millis()` for buzzer alerts instead of `delay()`, ensuring the stop button triggers instantly without any hardware lag.
* **Smart Token Anti-Repeat Mechanism:** Prevents the system from continuous loop re-triggering during the target minute once acknowledged.
* **Low-Power Safe Architecture:** Uses internal pull-up resistor setup for the reset switch to protect the microcontroller from voltage surges.



# Arduino Ultrasonic Distance Monitor

An Arduino Uno project that measures distance with an **HC-SR04 ultrasonic sensor**, displays distance and temperature on a 16×2 I²C LCD, and uses two LEDs to indicate whether an object is within a 60 cm threshold.

The project also includes a Python script that reads the distance values sent over serial and plots them.

## Features

- HC-SR04 distance measurement
- DHT11 temperature measurement
- Temperature-adjusted speed-of-sound estimate
- 16×2 I²C LCD readout
- Red LED when measured distance is at or below 60 cm
- Green LED when measured distance is above 60 cm
- Serial output for live plotting on a computer

## Hardware

- Arduino Uno
- HC-SR04 ultrasonic sensor
- DHT11 temperature sensor
- 16×2 LCD with I²C backpack
- Red LED and green LED
- Appropriate resistors, breadboard, and jumper wires
- USB cable for programming and serial communication

## Wiring

Connections below match the pin definitions in `src/main.cpp`.

| Component | Signal | Arduino Uno |
|---|---|---|
| HC-SR04 | TRIG | D6 |
| HC-SR04 | ECHO | D7 |
| DHT11 | DATA | D8 |
| Red LED | Control | D5 |
| Green LED | Control | D4 |
| I²C LCD | SDA | A4 |
| I²C LCD | SCL | A5 |
| All modules | VCC / GND | Use the module's specified supply and a common ground |

Check the voltage and pinout of your particular sensor modules before powering them. The LCD code assumes I²C address `0x27`; some backpacks use a different address.

## How the measurement works

1. The Arduino reads the DHT11 temperature.
2. It estimates the speed of sound using (v \approx 331 + 0.6T) m/s, where (T) is temperature in °C.
3. The Arduino sends a short trigger pulse and measures the ECHO pulse duration.
4. The round-trip travel time is converted to distance:

```text
distance_cm = duration_us × speed_of_sound_m_per_s / 20000
```

5. Distance and temperature are shown on the LCD. The measured distance is also printed to the serial port at **9600 baud**.
6. The LED state is selected using the 60 cm threshold.

The temperature correction is an estimate; actual measurements depend on sensor alignment, target surface, ambient conditions, and sensor limitations.

## Build and upload

This project uses PlatformIO. Open the folder in VS Code with the PlatformIO extension, select the Arduino Uno environment, then build and upload.

The environment and libraries are configured in `platformio.ini`. The project uses the Arduino framework plus the LiquidCrystal I²C and DHT sensor libraries.

## Live plotting on a computer

Install the Python dependencies:

```bash
python -m pip install pyserial matplotlib
```

Open `ultrasonic_plot.py` and change the serial port from `COM10` to the port used by your system.

Examples:
- Windows: `COM3`, `COM10`
- Linux: often `/dev/ttyACM0` or `/dev/ttyUSB0`

Close the Arduino Serial Monitor before running the Python plotting script because only one program can usually own the serial port at a time. Then run:

```bash
python ultrasonic_plot.py
```

## Repository layout

```text
.
├── platformio.ini
├── src/
│   └── main.cpp
└── ultrasonic_plot.py
```

## Possible improvements

- Add an explicit timeout and invalid-reading handling for `pulseIn`
- Avoid clearing the LCD on every update to reduce flicker
- Smooth noisy readings and reject outliers
- Make the serial port configurable from the command line
- Add a wiring photograph and example measurement plot

This repository documents a practical embedded-systems exercise combining sensing, display control, and serial data visualization.

# Soil-7in1-sensor
The Soil 7-in-1 sensor project is an innovative IoT (Internet of Things) initiative designed to provide a comprehensive analysis of soil health for agricultural applications. Leveraging the power of real-time data acquisition, this project uses a multi-functional sensor capable of measuring seven crucial soil parameters. The Soil 7in1 Sensor is connected to the Arduino Uno via the 'RS485 to TTL' converter, and it is very tricky to make it work without niggles. The manufacturer of the soil 7in1 sensor is EmbSys, located in Chennai; refer to their documentation/datasheet for further information on the sensor. 

The repository contains 4 main files - /Arduino/Soil7in1_ArduinoUno.ino, /templates/index.html, flask_.py, app.py.
app.py has been hard-coded such that the serial communication between the computer and the Arduino Uno is taking place via COM7. This can be changed according to the use-case. 

Also, flash the Soil7in1_ArduinoUno.ino to your Arduino Uno using the Arduino IDE (The pin configuration can be understood from the code).

Make sure to run flask_.py and app.py (in this order), while the all the sensors and the Arduino Uno are plugged in.
The local-host port is defined in app.py, and can be changed accordingly.

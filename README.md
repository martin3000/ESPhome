# ESPhome

Library for reading temperature values from the X6 interface of an vaillant gas heater.
4 Sensors are create in home assistant.
For this we use an ESP8266.

Connections: 

 Heater Board from top       ESP8266

       +---------+
    6  ---       |
GND 5  ---       +--+        GND
TXD 4  ---          |        D1
RXD 3  ---          |        D0
    2  ---       +--+
    1  ---       |
       +---------+

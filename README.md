# ESPhome

Vaillant X6 sensor

Library for reading temperature values from the X6 interface of an vaillant gas heater.
4 Sensors are created in home assistant.
For this we use an ESP8266.
You need ESPhome version >=1.14

Connections: 
```
 Heater Board from top       ESP8266
    6P4C RJ connector
    
       +---------+
    6  ---       |
GND 5  ---       +--+        GND
TXD 4  ---          |        D1
RXD 3  ---          |        D0
    2  ---       +--+
    1  ---       |
       +---------+
```

For more commands, see https://old.ethersex.de/index.php/Vaillant_X6_Schnittstelle

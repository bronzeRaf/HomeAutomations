# HomeAutomations
A set of home automation project, based on Arduino and ESP8266 boards and IoT platforms.

## Really Relay

A project for controling water heaters, plugs and any kind of devices over the Internet.
This project uses the Blynk IoT platform and an NodeMCU board.

Turn on - off your devices with safety in first place.

![androidSide](https://github.com/bronzeRaf/HomeAutomations/blob/main/RealyProject/ReallyRelay/ReallyRelay/assets/android.png)

#### Services
The user is able to:
- Turn ON Heater (or applied device)
- Turn OFF Heater (or applied device)
- See live ON time
- See last session date, time and duration.

The project also provides automatically:
- Turn OFF the heater if the connection is lost
- Reconnect attemps
- Turn OFF the heater after 20mins
- Turn OFF heater if the supply is cut
- Initialize with heater OFF and sync with Android after NodeMCU reboot
- Android app can go offline
- No static IP / DynDNS is required

## Fish Feeder

A project for controling fish aquarium devices over the Internet.
This project uses an IoT platform and aArduino boards.

![feeder1](https://github.com/bronzeRaf/HomeAutomations/blob/main/FeederProject/FishFeeder/assets/1.jpg)

Go anywhere and anytime with your fish in first place.

#### Services
The user is able to:
- Feed fish
- See feeding history
- Monitor aquarium state (temperature, etc...)
- Change water
- See water changing history
- Turn ON and OFF the lights for plant growing
- Turn ON and OFF the water cooler
- Plan future action (notification, feeding, water change, lighting)

The project also provides automatically:
- Reconnect attemps if connection is lost
- Feed if the fish hadn't fed for 2 days
- Turn ON cooler if temperature is higher than 30 degrees
- Turn OFF cooler if temperature is lower than 20 degrees
- Initialize with and sync with Android after ESP8266 reboot
- Android app can go offline
- No static IP / DynDNS is required

This project is under construction
Come back soon!!!
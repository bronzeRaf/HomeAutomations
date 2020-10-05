# Really Relay

A project for controling water heaters, plugs and any kind of devices over the Internet.
This project uses the Blynk IoT platform.

Turn on - off your devices with safety in first place.

## Hardware

You will need:
- 1 NodeMCU board
- 2 ralays
- Some wires

## Software
Software is applied both in the NodeMCU and in the android smartphone.

#### Android
The Android side software is easy to develop through the [Blynk](https://docs.blynk.cc/) app. The final Android is presented in the the picture below. There are 2 screenshots, one with the Heater OFF and one with the Heater ON.

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
- Initialize with heater OFF and sync with Android after reboot

#### NodeMCU
The full source code of this side could be found the file "ReallyRelay.ino". The source code is structured in functions and it is using the Blynk api to configure callbacks and a timer.

The Pins that the app uses:
Virtual Pins
- V0 ~ Button ON - OFF
- V2 ~ Live minutes
- V3 ~ Live seconds
- V6 ~ Last session minutes
- V7 ~ Last session seconds
- V8 ~ Last session timestamp

Digital Pins
- D5 (GPIO14) ~ Relay 1 control
- D6 (GPIO12) ~ Relay 1 control

You can see the wiring schema below.

![schema](https://github.com/bronzeRaf/HomeAutomations/blob/main/RealyProject/ReallyRelay/ReallyRelay/assets/schema.png)
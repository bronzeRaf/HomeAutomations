
# Fish Feeder

*This is a lighter version of the original Fish Feeder APP.*

A project for controlling fish aquarium devices over the Internet.
This project works with Arduino, NodeMCU and EPS8266 boards.

Go anywhere and anytime with your fish in first place.

## Standard Project

#### Services

The standard version of the project could:
- Feed fish every 8 hours
- Extra feed out of the routine with a button press (with a reset to the timer)
 
#### Hardware

Electronics:
- 1x Arduino (any board)
- 1x DC motor (eg in the body of a Servo, or not...)
- 1x L293D
- 1x 6xAA battery case (or 4xAA or any input supply source 4.5-36V)
- 14x Jumpers (approximately) 

Non Electronics:
- 2x Toped Caps
- 1x Wooden/Plastic stick or straw
- 3x Screws (approximately)
- Glue (Glue gun is recommended)

#### Instructions
Electronics:
Follow the circuit on the photo below. Keep in mind that the cirtuit gets 2 power supplies, one to arduino (via USB or via power adaptor) and one into L239D in order to feed the DC motor with the correct current. 
You can power up L239D with Batteries or power adaptor in between 4.5-36V and the IC will provide the motor with the required current and voltage to make sure the supply will be enough (600mA and peaks up to 1.2A per channel).
Powering up the motor using Arduino 5V supply is bad practice and won't be enough for a reliable and long term running feeding machine. 
Puting the GNDs all together in the same connector (Arduino + Batteries/external power) is crucial for the circuit to work properly!

![circuit1](https://github.com/bronzeRaf/HomeAutomations/blob/main/FeederLightProject/FishFeederLight/assets/circuit.png)

![circuit2](https://github.com/bronzeRaf/HomeAutomations/blob/main/FeederLightProject/FishFeederLight/assets/5.jpg)

 Non Electronics:
- Open a hole on the top of the first cap so that the servo can fit inside. Then screw or yield the servo for stability.
- Open a small hole on the bottom of the cap (depended on your fishes' food size).
- Keep only the bottom of the second cap and open a similar hole like the first cap's.
- Yield the stick (or the straw) to the servo, and cut it to fit perfectly inside the cap. Then yield the other end of the stick to the bottom of the second cap.
- Cover the first cap with the top, that contains the servo that is yielded with the stick and the second's cap bottom.
- If you want, you can make another hole on the top of the cap to refill with food from there 
You can see the below photos. 

![feeder1](https://github.com/bronzeRaf/HomeAutomations/blob/main/FeederProject/FishFeeder/assets/1.jpg)

![feeder2](https://github.com/bronzeRaf/HomeAutomations/blob/main/FeederProject/FishFeeder/assets/2.jpg)

![feeder3](https://github.com/bronzeRaf/HomeAutomations/blob/main/FeederProject/FishFeeder/assets/3.jpg)

![feeder4](https://github.com/bronzeRaf/HomeAutomations/blob/main/FeederProject/FishFeeder/assets/4.jpg)

Enjoy your happy fish!! But don't forget to give them also some of your time!!

## Extended Project addons

#### Services

The extended version of the project could:
- Work over the internet
- Feed Fish (Scheduled or on demand)
- See feeding history
- Monitor aquarium state (temperature, etc...)
- Change water (Scheduled or on demand)
- See water changing history
- Turn ON and OFF the lights for plant growing (Scheduled or on demand)
- Turn ON and OFF the water cooler (Scheduled or on demand)
- Plan future action (notification, feeding, water change, lighting)

The extended project also provides automatically:
- Reconnect attempts if connection is lost
- Emergency Feed if the fish hadn't fed for 2 days
- Emergency turn ON cooler if temperature is higher than 30 degrees
- Emergency turn OFF cooler if temperature is lower than 20 degrees
- Initialize with and sync with Android after ESP8266 reboot
- Android app can go offline
- No static IP / DynDNS is required

This project is work in progress, with new releases on the way.
Come back soon!!!
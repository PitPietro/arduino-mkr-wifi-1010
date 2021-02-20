# Arduino MKR WiFi 1010

[Getting started](https://www.arduino.cc/en/Guide/MKRWiFi1010)

## Setting Up Arduino on Linux

Here are some problems I faced up during the develop of Arduino code on my Ubuntu Linux machine.

### Open the serial port

If you try to load a program that requires **Serial Port** and the IDE throws an error like the following:

```bash
processing.app.debug.RunnerException
# [...]
Caused by: processing.app.SerialException: Error touching serial port '/dev/ttyACM0'.
# [...]
Caused by: jssc.SerialPortException: Port name - /dev/ttyACM0; Method name - openPort(); Exception type - Permission denied.
```

You need to add the execution permission on the port:
```bash
sudo chmod 666 ttyACM0
```

You could also need to add yourself to the `dialout` group:
```bash
sudo usermod -a -G dialout $USER
```

Logout and then log back in for the group changes to take effect (or just `restart` the machine).

## Project Folders

To allow a better readability of the repository, below is shown all the code folder by folder:
- [bot :robot:](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/Bot-folder)
- [input](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/input-folder)
- [MKR_SD_PROTO_SHIELD](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/MKR_SD_PROTO_SHIELD-folder)
- [output](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/output-folder)

### serial-communication

#### ASCII_table

`cd serial-communication/ASCII_table`

The ASCII table was inspired by [Tutorial/ASCIITable](http://www.arduino.cc/en/Tutorial/ASCIITable) from the official website of Arduino.
The first visible ASCII element is the exclamation mark `!`, which is associated to the number 33

```c
// those declarations are equivalent
char character = 33;
char character = '!';
```

#### sizeof_test

`cd serial-communication/sizeof_test`

It simply tests the functionality of [sizeof](https://www.arduino.cc/reference/en/language/variables/utilities/sizeof/) Arduino function. 

## Libraries
### WiFiNINA
[WiFiNINA](https://www.arduino.cc/en/Reference/WiFiNINA) library allows Arduino MKR WiFi 1010 to be able to connect to a WiFi network. If you want to connect the board to a *wired network* using an Ethernet cable, you need to buy the [Arduino MKR ETH Shield](https://store.arduino.cc/arduino-mkr-eth-shield) from the official [Arduino Store](https://store.arduino.cc/).

To install **WiFiNINA** library, navigate to:
1. **Tools**
2. **Manage Libraries**
3. search for **WiFiNINA**
4. click on the **Install** button on the right bottom corner.

## Reference
- [Changing permissions on serial port](https://askubuntu.com/questions/58119/changing-permissions-on-serial-port)
- [emoji-cheat-sheet](https://github.com/ikatyang/emoji-cheat-sheet/blob/master/README.md)

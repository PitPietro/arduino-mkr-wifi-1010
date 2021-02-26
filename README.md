# Arduino MKR WiFi 1010

[Getting started](https://www.arduino.cc/en/Guide/MKRWiFi1010)

## Setting Up Arduino on Linux

Here are some problems I faced up during the develop of Arduino code on my Ubuntu Linux machine.

### Install Arduino IDE
Go to the official Arduino website, in the [software](https://www.arduino.cc/en/software) section and download the version labelled Linux 32 bits (or 64 bits, if your machine supports it).

Open a terminal window:
```bash
# ensure you are in the home directory
cd ~
# navigate to Downloads
cd Downloads
# replace 'XXX' with the correct version number
# extract the contents of the downloaded file
tar -xvf arduino-XXX-linuxarm.tar.xz
# remove the archive
rm -rfv arduino-XXX-linuxarm.tar.xz
# move the extracted folder from home/$USER/Downloads to /opt
sudo mv arduino-XXX /opt
# complete the installation
sudo /opt/arduino-XXX/install.sh
```


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
cd && sudo chmod 666 dev/ttyACM0
```

You could also need to add yourself to the `dialout` group:
```bash
sudo usermod -a -G dialout $USER
```

**Please Note**: Logout and then log back in for the group changes to take effect (or just `sudo restart` the machine).

## Project Folders
- [bot :robot:](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/Bot-folder)
- [input](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/input-folder)
- [MKR_SD_PROTO_SHIELD](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/MKR_SD_PROTO_SHIELD-folder)
- [output](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/output-folder)
- [serial-communication](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/serial-communication-folder)

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

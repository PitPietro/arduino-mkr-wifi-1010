# Arduino MKR WiFi 1010

Please, refer to the official Arduino website to [getting started](https://www.arduino.cc/en/Guide/MKRWiFi1010) with MKR WiFi 1010.

## Table of contents

- [1.0 Setting Up Arduino on Linux](#10-setting-up-arduino-on-linux)
  - [1.1 Install Arduino IDE](#11-install-arduino-ide)
  - [1.2 Open the serial port](#12-open-the-serial-port)
- [2.0 Structure](#20-structure)
- [3.0 Shields](#30-shields)
  - [3.1 MKR SD Proto Shield](#31-mkr-sd-proto-shield)
  - [3.2 MKR ETH](#32-mkr-eth)
- [4.0 Reference](#40-reference)

## 1.0 Setting Up Arduino on Linux

Here are some problems I faced up during the develop of Arduino code on my Ubuntu Linux machine.

### 1.1 Install Arduino IDE
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


### 1.2 Open the serial port

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

**Please Note**: If you accidentally stop the sketch from uploading, you just need to double click the reset button ([reference](https://forum.arduino.cc/index.php?topic=637912.0)).

## 2.0 Structure

I made a [wiki page](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki) for all the folders of the repository.

- [bot :robot:](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/Bot-folder)
- [input](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/input-folder)
- [MKR_SD_PROTO_SHIELD](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/MKR_SD_PROTO_SHIELD-folder)
- [output](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/output-folder)
- [serial-communication](https://github.com/PitPietro/arduino-mkr-wifi-1010/wiki/serial-communication-folder)



## 3.0 Shields

In this section, I'll show you the shields used in some projects.

### 3.1 MKR SD Proto Shield

![MKR SD Proto Shield](https://store-cdn.arduino.cc/uni/catalog/product/cache/1/image/500x375/f8876a31b63532bbba4e781c30024a0a/t/s/tsx00004_iso.jpg)

Thanks to the [MKR SD Proto Shield](https://store.arduino.cc/mkr-sd-proto-shield) you can add to your project an SD slot and a prototyping area.


### 3.2 MKR ETH

![Arduino MKR ETH Shield image](https://store-cdn.arduino.cc/uni/catalog/product/cache/1/image/500x375/f8876a31b63532bbba4e781c30024a0a/a/s/asx00006_iso_1_1.jpg)

If you want to connect the board to a *wired network* using an Ethernet cable, you need to buy the [Arduino MKR ETH Shield](https://store.arduino.cc/arduino-mkr-eth-shield) from the official [Arduino Store](https://store.arduino.cc/).

## 4.0 Reference
- [Changing permissions on serial port](https://askubuntu.com/questions/58119/changing-permissions-on-serial-port)
- [emoji-cheat-sheet](https://github.com/ikatyang/emoji-cheat-sheet/blob/master/README.md)

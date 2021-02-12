# Arduino MKR Wi-Fi 1010

[Getting started](https://www.arduino.cc/en/Guide/MKRWiFi1010)

## Setting Up Arduino on Linux

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

## Projects Trees

```bash
.
├── bot
│   ├── Discord
│   │   └── discord_hello_world
│   │
│   └── Telegram
│       └── UniversalTelegramBot
│           ├── echo_bot
│           │
│           ├── LED_on_off_bot
│           │
│           ├── reply_keyboard_markup
│           │
│           └── send_logo_photo_from_URL
│
├── MKR_SD_PROTO_SHIELD
│   ├── ASCII_logo_download
│   │
│   └── card_info
│
├── Network_Time_Protocol
│   └── get_time_from_NTP
│
├── Real_Time_Protocol
│   └── get_time_from_RTC
│
├── sensors
│   ├── distance
│   │   └── SR04
│   │       └── basic_SR04
│   │
│   ├── potentiometer
│   │   ├── map_value
│   │   │
│   │   └── voltage_test
│   │
│   └── temperature
│       └── TMP36
│           └── basic_thermometer
│
├── serial-communication
│   └── ASCII_table
│
└── WiFiNINA_library
    ├── check_RGB_LED
    │
    ├── connect_to_WiFi
    │
    ├── scann_network
    │
    ├── set_RBG_LED_from_potentiometers
    │
    ├── set_RBG_LED_from_Serial
    │
    └── WiFi_ping

```

## Libraries
### WiFiNINA
[WiFiNINA](https://www.arduino.cc/en/Reference/WiFiNINA) library allows Arduino MKR WiFi 1010 to be able to connect to a WiFi network. If you want to connect the board to a *wired network* using an Ethernet cable, you need to buy the [Arduino MKR ETH Shield](https://store.arduino.cc/arduino-mkr-eth-shield) from the official [Arduino Store](https://store.arduino.cc/).

To install **WiFiNINA** library, nagivate to:
1. **Tools**
2. **Manage Libraries**
3. search for **WiFiNINA**
4. click on the **Install** button on the right bottom corner.

## Reference
- [Changing permissions on serial port](https://askubuntu.com/questions/58119/changing-permissions-on-serial-port)

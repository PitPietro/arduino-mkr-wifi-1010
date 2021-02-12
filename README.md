# Arduino Wi-Fi 1010

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

Logout and then log back in for the group changes to take effect (or just **restart** the machine).

## Libraries
### WiFiNINA
[WiFiNINA](https://www.arduino.cc/en/Reference/WiFiNINA) library allows Arduino MKR WiFi 1010 to be able to connect to the network.

To install **WiFiNINA** library, nagivate to:
1. **Tools**
2. **Manage Libraries**
3. search for **WiFiNINA**
4. click on the **Install** button on the right bottom corner.

## Reference
- [Changing permissions on serial port](https://askubuntu.com/questions/58119/changing-permissions-on-serial-port)

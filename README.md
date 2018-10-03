# autonomous_driver
This is a master thesis project dealing with the investigation of autonomous driving. For that purpose, a modular, mobile and open-source development environment was built and implemented on an auonomous model vehicle. This vehicle is part of the development environment, can be used as a development tool as well as for HIL-tests of software applications for autonomous driving.

This repository provides the Autonomous Driver software that implements an autonomous driving software system. It has a graphical user interface, an autonomous driving mode and a remote control mode. In the autonomous driving mode it detects the road lane based on white road markings and stop signs with a camera. With a ultrasonic sensor it detects obstacles.

A short demo video of the autonomous driving mode can be found on <https://youtu.be/CxPvibFuxQU>.

## Hardware ##
This project was implemented with the following parts
* Raspberry Pi 3 Model B
* 16 GB microSD
* Raspberry Pi 3 case with active cooling
* Power bank with 5200 mAh, 5 V, 2.1 A
* HDMI-Monitor and/or Raspberry Pi 7" Touchscreen
* USB mouse and keyboard
* Sunfounder PCA9685 16-Channel 12-Bit PWM Driver
* HC-SR04 ultrasonic sensor
* Microsoft Lifecam HD-3000 USB webcam
* Reely 1:10 EP "Audi RS6" 4WD 2.4 GHz RtR RC model car

## Installation ##
To run this code you need the following software
* Raspbian GNU/Linux 9 (stretch)
* OpenCV 3.3.1
* Cmake
* Git
* qv4l2 (for webcam debugging only)

1. Clone this project with `git clone`:
```
git clone https://github.com/stabacariu/autonomous_driver.git
```
2. Change directory to `autonomous_driver`:
```
cd autonomous_driver
```
3. Make a build directory and change to it:
```
mkdir build
cd build
```
4. Run `cmake`:
```
cmake ../src/
```
5. Run `make` in multiple threads:
```
make -j4
```
6. Run `autonomous_driver`:
```
./autonomous_driver
```
7. Optionally you can install this program by running `make install` as admin. _Note_: This will install the `autonomous_driver` executable to `/opt/autonomous_driver` and the necessary config files to `/opt/autonomous_driver/config`. It also installs a shell script 'autonomous_driver' to `/usr/local/bin`.
```
sudo make install
```
8. After the last step you can run `autonomous_driver` by just using the command:
```
autonomous_driver
```
### Uninstallation ###
If you installed `autonomous_driver` as described in Step 7., you can uninstall the program by simply deleting the installed files and folders with:
```
sudo rm /usr/bin/local/autonomous_driver
sudo rm -r /opt/autonomous_driver
```

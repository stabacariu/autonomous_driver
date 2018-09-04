# autonomous_driver
This is a master thesis project dealing with the investigation of autonomous driving. For that purpose, a modular, mobile and open-source development environment was built and implemented on an auonomous model vehicle. This vehicle is part of the development environment, can be used as a development toll as well as for HIL-tests of software applications for autonomous driving.
This repository provides the Autonomous Driver software that implements an autonomous driving software system. It has a graphical user interface, an autonomous driving mode and a remote control mode. In the autonomous driving mode it detects the road lane based on white road markings and stop signs with a camera. With a ultrasonic sensor it detects obstacles.
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

First clone this project with 'git clone':
'''
git clone https://github.com/stabacariu/autonomous_driver.git
'''
Change directory to 'autonomous_driver':
'''
cd autonomous_driver
'''
Get latest master branch:
'''
git pull https://github.com/stabacariu/autonomous_driver.git master
'''
Make a build directory and change to it:
'''
mkdir build
cd build
'''
Run cmake:
'''
cmake ..
'''
Run make in multiple threads:
'''
make -j4
'''
Run 'autonomous_driver':
'''
./autonomous_driver
'''

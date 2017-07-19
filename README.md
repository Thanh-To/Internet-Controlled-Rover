# Internet Controlled Rover

## About
Control your 4WD robotic/rover and pan-tilt camera module through the internet by simply downloading this repository onto your Raspberry Pi and foolow the instruction down below. 

## Hardware Requirements*
*The following are the list of components used by this specific project. Equivalent components may or may not work. 
- Raspberry Pi 3
- Arduino Leonardo (Arduino Uno is preffered)
- SainSmart 4WD Drive Aluminum Mobile Robot Platform (https://www.amazon.ca/SainSmart-Aluminum-Platform-MEGA2560-Duemilanove/dp/B008Q47VKE)
- Pi Camera
- 2x2A DC Motor Shield for Arduino (https://www.dfrobot.com/product-69.html)
- USB battery bank
- 6xAA rechargable batteries and battery holder
- 

## Software Requirements
- [Node.js](https://nodejs.org/)
- [Socket.io](https://socket.io/)
- [OpenCV](http://opencv.org/)

## Assembly*
*Specific hardware assembly depends on the components you have sourced. In order for the project to work, wire the components to the according pins on the Arduino code.
[To be Updated]

## Installation
### 1. Installing Node.js
Before you install Node.js, go to https://nodejs.org/en/download/ to find the latest version, we are currently using v6.11.1
In terminal, input the followings:
```
wget https://nodejs.org/dist/v6.11.1/node-v6.11.1-linux-armv7l.tar.xz
tar -xvf node-v6.11.1-linux-armv7l.tar.xz
cd node-v6.11.1-linux-armv7l
sudo cp -R * /usr/local
```
### 2. Cloning this repository
```
cd
git clone https://github.com/ThankyTo/Internet-Controlled-Rover.git
```

### 3. Installing NPM javascript packages
```
cd Internet-Controlled-Rover
npm install express
npm install socket.io
npm install serialport
```
### 4. Installing OpenCV
follow the instructions from http://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html to install OpenCV onto your Raspberry Pi

## Set up

## Usage

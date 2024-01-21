# Homebridge Remote Switchboard

## What's this about

With this tool, you are able to build a remote switch to control light bulbs, sockets, or anything else connected to your local Homebridge installation. It is featured in this [YouTube Video](https://youtu.be/p1ukkSZFIrY).


## Prerequisites

This sketch is intended to run on ESP8266 boards. I used a D1 Mini clone. It may also run on any other Arduino board with slight modifications. And your board should have Wi-Fi access, of course. Besides the regular libraries, the project makes use of these:

* [ArduinoOTA](https://arduino-esp8266.readthedocs.io/en/latest/ota_updates/readme.html)
* [ArduinoJson](https://arduinojson.org)
* [Arduino Timer](https://github.com/contrem/arduino-timer)


## Configuration

In order to use this program, you need to set up your Wi-Fi credentials. Copy or move secrets.h.dist to secrets.h, enter your details, and compile the code.

You also have to configure your accessory IDs. These are the devices you would like to toggle on or off. There is some more explanation on that in the linked YouTube video (German language).


### License

Copyright 2024 Torsten Schmitz

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
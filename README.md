# ESP32S3 WiFi MAC address and FTM responder scanner

Authors [Emanuele Pagliari](https://github.com/Palia95)

# What is FTM

This simple sketch has been developed for the last [ESP32S3](https://esp32s3.com) SoC from Espressif, which support Fine Time Measurement (FTM) over the WiFi protocol. FTM is the measure of the time a WiFi signal takes to travel in the air from a device (“station” - STA) to a WiFi access point (AP) and it is, of course, proportional to the actual distance between them (about 3.3 nanoseconds per meter). Since the internal clocks in the two network entities are not synchronized, a one-way time measurement cannot be based on differences between timestamps at the two ends. Fortunately, the difference in timestamps when the signal travels in the reverse direction is affected in the opposite way by the clock offset. As a result, the round trip time (RTT) can be obtained without having to know the clock offsets - by simple addition and subtraction of four times: RTT = (t4-t1 + t2-t3). Therefore, knowing the round trip times to 3, 4, or more APs in known positions allows to estimate the position of the device given the positions of the APs. For more info about FTM, check [this wonderful website](http://people.csail.mit.edu/bkph/ftmrtt_intro).

# The code for Arduino ESP32S3 FTM and MAC scanner

The provided sketch is suitable only for the ESP32S3 and ESP32C2, since they are the only ESP32s that support FTM. The code is based on the Arduino and ESP-IDF frameworks. 

The output of the scan looks like this:

![ESP32S3 Arduino ESP32S3 FTM and MAC scanner output](/ESP32S3-WiFi-FTM-MAC-Scan.jpg?raw=true "Title")

Enjoy the code!
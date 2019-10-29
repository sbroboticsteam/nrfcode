# nrfcode
repo for nrf code since I keep changing it

## tips for using nrf modules
1. the addresses[] array is for a user defined address 6 characters long, make sure your transmitter and receiver code are using the same address!
2. make sure you're looking for messages of the same size when you do myRadio.read()!

### resources
1. nrf library example: http://tmrh20.github.io/RF24/GettingStarted_8ino-example.html
2. https://forum.arduino.cc/index.php?topic=421081.0

### tentative data format(not tested!!!)
// change data for message
//The data is stored in the following format:
//data[0] is the direction pad, up
//data[1] is the direction pad, down
//data[2] is the direction pad, left
//data[3] is the direction pad, right
//data[4] is the start button
//data[5] is the back button
//data[6] is the left joystick button
//data[7] is the right joystick button
//data[8] is the left button (above the left bumper)
//data[9] is the right button (above the right bumper)
//data[10] is the A button
//data[11] is the B button
//data[12] is the X button
//data[13] is the Y button
//data[14] is the left joystick x axis value (128 is center, 0 is all the way to the right, 255 is all the way to the left)
//data[15] is the left joystick y axis value (128 is center, 0 is all the way down, 255 is all the way up)
//data[16] is the right joystick x axis value (128 is center, 0 is all the way to the right, 255 is all the way to the left)
//data[17] is the right joystick y axis value (128 is center, 0 is all the way down, 255 is all the way up)
//data[18] is the left bumper analog value (0 is not pressed, 255 is pressed all the way)
//data[19] is the right bumper analog value (0 is not pressed, 255 is pressed all the way)

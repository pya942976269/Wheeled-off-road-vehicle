# Servo Shield Example.
#
# This example demonstrates the servo shield. Please follow these steps:
#
#   1. Connect a servo to any PWM output.
#   2. Connect a 3.7v battery (or 5V source) to VIN and GND.
#   3. Copy pca9685.py and servo.py to OpenMV and reset it.
#   4. Connect and run this script in the IDE.

import time
from servo import Servos
from machine import I2C, Pin
inverse_left=False  #change it to True to inverse left wheel
inverse_right=False #change it to True to inverse right wheel

i2c = I2C(sda=Pin('P5'), scl=Pin('P4'))
servo = Servos(i2c, address=0x40, freq=50, min_us=1100, max_us=1900, degrees=1000)
Left=0
Right=1
while True:


    #servo.position(0, 100)
    #time.sleep(500)
    def run(left_speed, right_speed):
        if inverse_left==True:
            left_speed=(1000-left_speed)
        if inverse_right==True:
            right_speed=(1000-right_speed)
   if    left_speed>1000
           servo.position(Left, 1000)


   elif    left_speed<0
            servo.position(Left, 0)

   else
            servo.position(Left, left_speed)

   if    right_speed>1000

                   servo.position(Right, 1000)

   elif    right_speed<0

                    servo.position(Right, 0)
   else

                    servo.position(Right, right_speed)

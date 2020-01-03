THRESHOLD =(52, 0, 127, -128, 127, -41)# Grayscale threshold for dark things...(75, 0, 127, -128, 127, -62)(71, 0, 127, -128, 54, -18)
import sensor, image, time
from pyb import LED
import car
from pid import PID
from pyb import Pin
rho_pid = PID(p=0.5, i=0.01)
theta_pid = PID(p=0.09, i=0.01)
enable='False'
exposure_us=1000
LED(1).on()
LED(2).on()
LED(3).on()
pin1=Pin('P1', Pin.IN,Pin.PULL_UP)
pin2=Pin('P2', Pin.IN,Pin.PULL_UP)
pin3=Pin('P3', Pin.IN,Pin.PULL_UP)
old_L=0
old_R=0

clock=time.clock()
sensor.reset()
#sensor.set_vflip(True)
#sensor.set_hmirror(True)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQQVGA) # 80x60 (4,800 pixels) - O(N^2) max = 2,3040,000.
sensor.set_gainceiling(2)
sensor.set_auto_exposure(False,exposure_us=2500)#baoguanglv
sensor.set_contrast(+3)
sensor.set_saturation(-1)
sensor.set_brightness(-3)


while(True):
  if pin1.value():
    clock.tick()
    img = sensor.snapshot().binary([THRESHOLD])
    #img = sensor.snapshot()
    line = img.get_regression([(-100,-100,0,0,0,0)], robust = True)
    if (line):
        rho_err = abs(line.rho())-img.width()/2
        if line.theta()>90:
            theta_err = line.theta()-180
        else:
            theta_err = line.theta()
        img.draw_line(line.line(), color = 127)
        print(rho_err,line.magnitude(),rho_err,theta_err )
        if line.magnitude()>8:
            if  -15<=theta_err<=15:
               rho_output = rho_pid.get_pid(rho_err,1)
               theta_output = theta_pid.get_pid(theta_err,1)
               output = rho_output+theta_output
               car.run(1000+(10*output), 1000-(10*output))
               old_L=1000+(10*output)
               old_R=1000-(10*output)
            elif  -15<=theta_err<=15 and pin3.value():
               rho_output = rho_pid.get_pid(rho_err,1)
               theta_output = theta_pid.get_pid(theta_err,1)
               output = rho_output+theta_output
               car.run(750+(10*output), 750-(10*output))
               old_L=750+(10*output)
               old_R=750-(10*output)

            elif    70>=theta_err>=15 or -15>=theta_err>=-70:
               rho_output = rho_pid.get_pid(rho_err,1)
               theta_output = theta_pid.get_pid(theta_err,1)
               output = rho_output+theta_output
               car.run(700+(10*output), 750-(10*output))
               old_L=700+(10*output)
               old_R=750-(10*output)
            #elif 90>theta_err>70 and -90<theta_err<-70:
              # car.run(300,700)
        else:
            car.run(400,700)
    else:
        #car.run(500,570)
        #time.sleep(600)
        if (old_L>old_R):
         car.run(old_L+17,510)
         print('海好')
        else:
         car.run(510,old_R+17)
  else:
   car.run(500,500)
  print(clock.fps())

#include <Wire.h>
#include <JY901.h>
//1为Y
//2为Z
 int y=1;
 int z=2 ;  
int ln = 13;
int flag=1;
void serialEvent() ;

void setup() 
{
  Serial.begin(9600);
  pinMode(13, INPUT); //接受遥控器的信号 
  pinMode(2, OUTPUT);//圈数
  pinMode(3, OUTPUT);//倾角减速
  pinMode(5, OUTPUT);//输出遥控器信号
}

void loop() 
{
  
  int sensorVal = digitalRead(13);
  sensorVal=1;
    //Serial.println(sensorVal);  // 将获取到的数值打印到串行调试窗口，方便调试
    if (sensorVal == 1)
    {
      digitalWrite(2,LOW);
      digitalWrite(5,HIGH);//输出遥控器信号
     digitalWrite(4,HIGH);
      int  count = 0;
  
     //print received data. Data was received in serialEvent;
     Serial.print("Time:20");Serial.print(JY901.stcTime.ucYear);Serial.print("-");Serial.print(JY901.stcTime.ucMonth);Serial.print("-");Serial.print(JY901.stcTime.ucDay);
     Serial.print(" ");Serial.print(JY901.stcTime.ucHour);Serial.print(":");Serial.print(JY901.stcTime.ucMinute);Serial.print(":");Serial.println((float)JY901.stcTime.ucSecond+(float)JY901.stcTime.usMiliSecond/1000);
               
     Serial.print("Acc:");//Serial.print((float)JY901.stcAcc.a[0]/32768*16);Serial.print(" ");Serial.print((float)JY901.stcAcc.a[1]/32768*16);Serial.print(" ");
      Serial.println((float)JY901.stcAcc.a[0]/32768*16);
  
     Serial.print("Gyro:");//Serial.print((float)JY901.stcGyro.w[0]/32768*2000);Serial.print(" ");Serial.print((float)JY901.stcGyro.w[1]/32768*2000);Serial.print(" ");
     Serial.println((float)JY901.stcGyro.w[0]/32768*2000);
  
    // Serial.print("Angle:");Serial.print((float)JY901.stcAngle.Angle[0]/32768*180);Serial.print(" ");Serial.print((float)JY901.stcAngle.Angle[1]/32768*180);Serial.print(" ");
     Serial.println((float)JY901.stcAngle.Angle[2]/32768*180);
  
     //Serial.print("Mag:");//Serial.print(JY901.stcMag.h[0]);Serial.print(" ");Serial.print(JY901.stcMag.h[1]);
     // Serial.print(" ");
      
      //Serial.println(JY901.stcMag.h[0]);
  
     // Serial.print("Pressure:");Serial.print(JY901.stcPress.lPressure);Serial.print(" ");Serial.println((float)JY901.stcPress.lAltitude/100);
  
     // Serial.print("DStatus:");Serial.print(JY901.stcDStatus.sDStatus[0]);Serial.print(" ");Serial.print(JY901.stcDStatus.sDStatus[1]);Serial.print(" ");Serial.print(JY901.stcDStatus.sDStatus[2]);Serial.print(" ");Serial.println(JY901.stcDStatus.sDStatus[3]);
  
     //Serial.print("Longitude:");Serial.print(JY901.stcLonLat.lLon/10000000);Serial.print("Deg");Serial.print((double)(JY901.stcLonLat.lLon % 10000000)/1e5);Serial.print("m Lattitude:");
    // Serial.print(JY901.stcLonLat.lLat/10000000);Serial.print("Deg");Serial.print((double)(JY901.stcLonLat.lLat % 10000000)/1e5);Serial.println("m");
  
    // Serial.print("GPSHeight:");Serial.print((float)JY901.stcGPSV.sGPSHeight/10);Serial.print("m GPSYaw:");Serial.print((float)JY901.stcGPSV.sGPSYaw/10);Serial.print("Deg GPSV:");Serial.print((float)JY901.stcGPSV.lGPSVelocity/1000);Serial.println("km/h");
  
        Serial.println("");
  //while(1)
  //{    
    if(count==0)
   {
    digitalWrite(5,LOW);
   
  }  
   if((((float)JY901.stcAngle.Angle[2]/32768*180)>0) && (((float)JY901.stcAngle.Angle[2]/32768*180)<90))
   {
    flag=1;
    
   }
   if(flag==1)
   {
    if((((float)JY901.stcAngle.Angle[2]/32768*180)>-180)&&(((float)JY901.stcAngle.Angle[2]/32768*180)<-45))
    {
      digitalWrite(2,HIGH);
     
      count++;
      flag=-1;
     
      }
   }
   
    
    if(JY901.stcAngle.Angle[y]>1 && JY901.stcAngle.Angle[y]<8)
    {
      digitalWrite(3,HIGH);
      
      
     }
    else
    {
     digitalWrite(3,LOW) ;
     }
    }
    
   }

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() 
{
  while (Serial.available()) 
  {
    JY901.CopeSerialData(Serial.read()); //Call JY901 data cope function
  }
}

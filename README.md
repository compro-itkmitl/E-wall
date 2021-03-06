![](/pic_readme/logo.jpg)

# ![](/pic_readme/1.jpg) Introduction
สวัสดีครับ วันนี้กลุ่ม E-wall หุ่นยนต์สัตว์เลี้ยง จะพาไปพบสิ่งที่สร้างรอยยิ้มให้กับพวกคุณได้ 
โดยหุ่นยนต์ของเรามีการเคลื่อนที่อัตโนมัติโดยการใช้เซ็นเซอร์ที่สามารถหลบสิ่งกีดขวางและมีฟังก์ชันอื่นๆอีกมากมายให้ได้ลองเล่นโดย Hardware ที่ใช้คือ Arduino  
ด้าน Software ใช้ภาษา C, C++ ในการเขียนโปรแกรมเป็นหลัก
ขอให้สนุกกับหุ่นยนต์ของเรากันน่ะครับ

# ![](/pic_readme/2.jpg) How to use
 
 <br>วิธีใช้
  <br>ลงแอป arduino bluetooth controller ผ่านทางplay store
  <br>เชื่อมต่อ e-wall กับมือถือ
  <br>สามารถดูสถานะของE-wallได้ในTerminal mode
  <br>สามารถเล่นกับE-wall ได้โดยพิมพ์1ในTeminal
  <br>และสามารถปิดเสียงได้โดยพิมพ์2ในTerminal
  <br>โดยตัวE-wallนั้นไม่จำเป็นต้องมีคนบังคับการเคลื่อนที่
ก็สามารถหลบสิ่งกีดขวางได้
<br>ที่จอLEDจะเป็นจอแสงอารมณ์ของe-wall
# ![](/pic_readme/4.jpg) Tools
  # อุปกรณ์ในการใช้มีดังนี้
  ![](/pic_readme/tool1.jpg)
  <br>TowerPro SG92R Mini Micro Servo x2
  <br>
  <br>
  <br>
  ![](/pic_readme/tool3.jpg)
  <br>Arduino Uno Rev3 x1
  <br>
  <br>
  <br>
  ![](/pic_readme/tool4.jpg)
  <br> Module Bluetooth HC-05 x1
  <br>
  <br>
  <br>
  ![](/pic_readme/tool5.jpg)
  <br>Ultrasonic Sensor Module (HC-SR04) x1
  <br>
  <br>
  <br>
  ![](/pic_readme/tool10.jpg)
  <br>L298N Dual H-Bridge Motor Controller x1
  <br>
  <br>
  <br>
  ![](/pic_readme/tool2.jpg)
  <br>Jumper 
  <br>
  <br>
  <br>
  ![](/pic_readme/tool6.jpg)
  <br>ฺBreadborard 400 holes x1
  <br>
  <br>
  <br>
  ![](/pic_readme/tool7.jpg)
  <br>Speaker 0.25W 8R 2.9CM ลำโพง 0.25W 8 โอห์ม ขนาด 2.9 cm x1
  <br>
  <br>
  <br>
  ![](/pic_readme/tool9.jpg)
  <br>LED Dot Matrix 8x8 Red Color Common Anode x2
  <br>
  <br>
  <br>
  ![](/pic_readme/tool8.jpg)
  <br>ถ่าน 9 V x3
  <br>
  <br>
  <br>
  ![](/pic_readme/tool11.jpg)
  <br>ตัวต้านทาน x3
  <br>
  <br>
  <br>
  ![](/pic_readme/tool12.jpg)
  <br>DF player mini mp3 player x1
  <br>
  <br>
  <br>
  ![](/pic_readme/tool13.jpg)
  <br>2wd smart car chassis 2ชั้น x1
  <br>
  <br>
  <br>
  
  
# ![](/pic_readme/5.jpg) Function
setup()//เป็นการsetupค่าต่างๆของอุปกรณ์และตัวแปร<br>
sonar()// ใช้เพื่อหาระยะทางและกำหนดทิศทางของe-wall<br>
base_go,head_go(int finalAngle)// ใช้ในการค่อยๆขยับservoส่วนฐานหรือหน้าตามที่กำหนด<br>
printDetail(uint8_t type, int value)// เป็นฟังก์ชั่นที่จะบอกสถานะของsd card<br>
happy(),sleep(),angry(),normal(),sad()//เป็นฟังก์ชั่นที่ใช้แสดงอารมณ์ต่างๆของe-wall<br>

# ![](/pic_readme/5.jpg)library
arduino.h <br>
SoftwareSerial.h <br>
DFRobotDFPlayerMini.h <br>
Servo.h,Ledcntrol.h <br>

# ![](/pic_readme/6.jpg) Team Members
|  |ชื่อ|นามสกุล|GitHub Username|รหัสนักศึกษา|
|:-:|--|------|---------------|---------|
|![https://www.facebook.com/profile.php?id=100008347569782](/pic_readme/59070171.jpg)|Saminya|Leammookda|[@it59070171](https://github.com/it59070171)|59070171|
|![https://www.facebook.com/profile.php?id=100018579390168](/pic_readme/60070114.jpg)|Apisit|Wetmaha|[@Apisit60070114](https://github.com/Apisit60070114)|60070114|
|![https://www.facebook.com/focus251](/pic_readme/60070181.jpg)|Kittichet|preedathanaphong|[@Focus565](https://github.com/Focus565)|60070181|


# ![](/pic_readme/8.jpg) Assistant Teachers
![](/pic_readme/Aj.jpg)
![](/pic_readme/itkmitl.jpg)

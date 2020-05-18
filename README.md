# SHADOW_MD_EEBEL
SHADOW Arduino Code for R2-D2 using Marcduino Control boards.  This code is used with a three Marcduino configuration.  Two are in the dome (Master and Slave) and a third is in the body (Which is setup as a Master using the Eclipse IDE.  Instructions for how to upload the Marcduino firmware are on the Curious Marc website. You will need an FTDI to USB cable, I got mine from SparkFun.com and it coasts about $18.  To get Eclipse to work, I had to install the JAVA IDE.

You will need to flash the Dome Master Marcduino and the Body Master Marcduino with the included firmware to ge the sketch to work correctly.  The Slave Marduino in the dome uses the default firmware.

Follow the basic setup and wiring from the Astromech.net SHADOW and SHADOWMD WIKI pages.  If anyone has a good suggestion on how to do a proper wiring diagram, let me know and I'll add it to this repository.  Also, I'll add any other information to this site as requested.

Pins for the body servos are as follows:

servo1:  DPL - DataPanel Door

servo2:  UtlArmU - Upper Utility Arm

servo3:  UtlArmL - Lower Utility Arm

servo4:  LBdyDr - Left BreadPan Door

servo5:  LArm - Left Arm Raise/Lower

servo6:  LArmTool - Left Arm Tool

servo7:  ToolRBdyDr - Right BreadPan Door

servo8:  RArm - Right Arm Raise/Lower

servo9:  RArmTool - Right Arm Tool

servo10: unused - Future Charge Bay Door servo
  

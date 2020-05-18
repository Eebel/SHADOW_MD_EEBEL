# SHADOW_MD_EEBEL
SHADOW Arduino Code for R2-D2 using Marcduino Control boards.  This code is used with a three Marcduino configuration.  Two are in the dome (Master and Slave) and a third is in the body (Which is setup as a Master using the Eclipse IDE.  Instructions for how to upload the Marcduino firmware are on the Curious Marc website. You will need an FTDI to USB cable, I got mine from SparkFun.com and it coasts about $18.  To get Eclipse to work, I had to install the JAVA IDE.

You will need to flash the Dome Master Marcduino and the Body Master Marcduino with the included firmware to ge the sketch to work correctly.  The Slave Marduino in the dome uses the default firmware.

Follow the basic setup and wiring from the Astromech.net SHADOW and SHADOWMD WIKI pages.  If anyone has a good suggestion on how to do a proper wiring diagram, let me know and I'll add it to this repository.  Also, I'll add any other information to this site as requested.

Pins for the body tools are as follows:
servo1   servo2   servo3   servo4   servo5   servo6   servo7   servo8   servo9   servo10
 DPL     UtlArmU  UtlArmL   LBdyDr   LArm     LArm   ToolRBdyDr RArm    RArmTool  unused

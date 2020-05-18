// =======================================================================================
//                          Initialize - Setup Function
// =======================================================================================
void setup()
{
    //Debug Serial for use with USB Debugging
    Serial.begin(115200);
    while (!Serial);
    
    if (Usb.Init() == -1)
    {
        Serial.print(F("\r\nOSC did not start"));
        while (1); //halt
    }
    
    Serial.print(F("\r\nBluetooth Library Started"));
    
    output.reserve(200); // Reserve 200 bytes for the output string

    //Setup for PS3
    PS3NavFoot->attachOnInit(onInitPS3NavFoot); // onInitPS3NavFoot is called upon a new connection
    Serial.print(F("\r\nInitFootNav"));
    PS3NavDome->attachOnInit(onInitPS3NavDome); 

    //Setup for Serial2:: Motor Controllers - Sabertooth (Feet) 
    Serial2.begin(motorControllerBaudRate);
    ST->autobaud();          // Send the autobaud command to the Sabertooth controller(s).
    ST->setTimeout(10);      //DMB:  How low can we go for safety reasons?  multiples of 100ms
    ST->setDeadband(driveDeadBandRange);
    ST->stop(); 
    SyR->autobaud();
    SyR->setTimeout(20);      //DMB:  How low can we go for safety reasons?  multiples of 100ms
    SyR->stop(); 

    //Setup for Serial1:: MarcDuino Dome Control Board
    Serial1.begin(marcDuinoBaudRate); 
    
    //Setup for Serial3:: Optional MarcDuino Control Board for Body Panels
    Serial3.begin(marcDuinoBaudRate);
    
    randomSeed(analogRead(0));  // random number seed for dome automation 

     
     //PLay MP3 Trigger sound
    //MP3Trigger trigger;//make trigger object
    // Start serial communication with the trigger (over Serial)
//    trigger.setup(&Serial3);
//    trigger.setVolume(10);//Amount of attenuation  higher=LOWER volume..ten is pretty loud 
}

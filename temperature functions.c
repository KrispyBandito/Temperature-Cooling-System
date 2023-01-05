int main(void)
{
    SYSTEM_Initialize();
    state nextState = idle;
    while (1)
    {
        switch(state)
        {
            case idle:
                nextState = recordTempHandler();
                if(Power_Button_GetValue() == 1)                    //if power button pressed then reset/turn off
                {
                    __delay_ms(5000);                               //delay to turn off LEDS
                    nextState = idleHandler();                      //send back to idle state for reset/turn off
                    while(!Power_Button_GetValue()) {}              //wait for power button to be pressed & turned on 
                }
                break;
            case recordTemp:
                nextState = setLEDsHandler();
                if(Power_Button_GetValue() == 1)
                {
                    __delay_ms(5000);
                    nextState = idleHandler();
                    while(!Power_Button_GetValue()) {}
                }
                break;
            case setLEDs:
                nextState = goFanHandler();
                if(Power_Button_GetValue() == 1)
                {
                    __delay_ms(5000);
                    nextState = idleHandler();
                    while(!Power_Button_GetValue()) {}
                }
                break;
            case goFan:
                nextState = stopFanHandler();
                if(Power_Button_GetValue() == 1)
                {
                    __delay_ms(5000);
                    nextState = idleHandler();
                    while(!Power_Button_GetValue()) {}
                }
                break;
            case stopFan:
                nextState = recordTempHandler();
                if(Power_Button_GetValue() == 1)
                {
                    __delay_ms(5000);
                    nextState = idleHandler();
                    while(!Power_Button_GetValue()) {}
                }
                break;          
        }
    }
    return 1;
}

float getTemp()
{
    int reading = Temp_Sensor_GetValue();                       //input voltage from temp sensor
    float voltage = reading * 5.0;                              //convert the voltage
    voltage /= 1024.0;
    float temperC = (voltage - 0.5) * 100;                      //temperature in Celsius 
    float temperF = (temperC * 9.0/5.0) + 32.0;                 //temperature in Fahrenheit
    return temperF;
}
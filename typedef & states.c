typedef enum
{
            idle,
            recordTemp,
            setLEDs,
            goFan,
            stopFan           
}state;

state idleHandler(void)
{
    Power_LED_SetLow();
    Green_LED_SetLow();
    Red_LED_SetLow();
    Yellow_LED_SetLow();
    FAN_SetLow();
    //button push
    return recordTemp;
}
state recordTempHandler(void)
{   
    Power_LED_SetHigh();
    Green_LED_SetLow();
    Red_LED_SetLow();
    Yellow_LED_SetLow();
    FAN_SetLow();
    __delay_ms(500);
    return setLEDs;
}

state setLEDsHandler(void)
{
    float temperature = getTemp();
    if(temperature <= 60.9)
    {
        Power_LED_SetHigh();
        Green_LED_SetHigh();
        Red_LED_SetLow();
        Yellow_LED_SetLow();
        FAN_SetLow();
    }
    else if(temperature >= 61.0 || temperature <= 70.0)
    {
        Power_LED_SetHigh();
        Green_LED_SetLow();
        Red_LED_SetLow();
        Yellow_LED_SetHigh();
        FAN_SetLow();
    }
    else
    {
        Power_LED_SetHigh();
        Green_LED_SetLow();
        Red_LED_SetHigh();
        Yellow_LED_SetLow();
        FAN_SetLow();
    }
    __delay_ms(500);
    return goFan;
}
state goFanHandler(void)
{
    Power_LED_SetHigh();
    Green_LED_SetLow();
    Red_LED_SetHigh();
    Yellow_LED_SetLow();
    FAN_SetHigh();
    __delay_ms(500);
    return stopFan;
}
state stopFanHandler(void)
{
    Power_LED_SetHigh();
    Green_LED_SetLow();
    Red_LED_SetLow();
    Yellow_LED_SetLow();
    FAN_SetLow();
    __delay_ms(500);
    return recordTemp;
}

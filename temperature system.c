#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
float voltage;
float temperature;
uint16_t reading;

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
    //FAN_SetLow();
    //button push
    return setLEDs;
}
state recordTempHandler(void)
{   
    Power_LED_SetHigh();
    Green_LED_SetLow();
    Yellow_LED_SetLow();
    Red_LED_SetLow();
    //FAN_SetLow();
    return setLEDs;
}

state setLEDsHandler(void)
{
    if(temperature < 26.055)
    {
        Power_LED_SetHigh();
        Green_LED_SetHigh();
        Yellow_LED_SetLow();
        Red_LED_SetLow();
    }
    else if(temperature >= 26.055 || temperature < 27.08)
    {
        Power_LED_SetHigh();
        Green_LED_SetLow();
        Yellow_LED_SetHigh();
        Red_LED_SetLow();
    }
    else
    {
        Power_LED_SetHigh();
        Green_LED_SetLow();
        Yellow_LED_SetLow();
        Red_LED_SetHigh();
    }
    return setLEDs;
}
state goFanHandler(void)
{
    Power_LED_SetHigh();
    Green_LED_SetLow();
    Yellow_LED_SetLow();
    Red_LED_SetHigh();
    FAN_SetHigh();
    return setLEDs;
}
state stopFanHandler(void)
{
    Power_LED_SetHigh();
    Green_LED_SetLow();
    Yellow_LED_SetLow();
    Red_LED_SetHigh();
    FAN_SetLow();
    return setLEDs;
}
void delay_ms(unsigned int);
void getTemp(void);

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    state nextState = idle;
    while (1)
    {
        switch(nextState)
        {
            case idle:
                getTemp();
                nextState = setLEDsHandler();
                delay_ms(5000);
                break;
//            case recordTemp:
//                //getTemp();
//                nextState = setLEDsHandler();
//                 delay_ms(5000);
//                break;
            case setLEDs:
                getTemp();
                if(temperature >= 27.08)
                {
                    FAN_SetHigh();
                    delay_ms(5000);
                    nextState = goFanHandler();
                }
                else
                    nextState = setLEDsHandler();
                 delay_ms(5000);
                break;
            case goFan:
                getTemp();
                if(temperature < 27.08)
                {
                    FAN_SetLow();
                    delay_ms(5000);
                    nextState = setLEDsHandler();
                }
                else
                {
                    FAN_SetHigh();
                    delay_ms(5000);
                    nextState = goFanHandler();
                }
                 delay_ms(5000);
                break;
            case stopFan:
                nextState = setLEDsHandler();
                delay_ms(5000);
                break;          
        }
    }
    return 1;
}
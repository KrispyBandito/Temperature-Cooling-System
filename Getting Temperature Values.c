void getTemp(void)
{   
        delay_ms(5000);

    Green_LED_SetLow();
    Yellow_LED_SetLow();
    Red_LED_SetLow();
    reading = ADC1_ConversionResultGet(Temp_Sensor);;           //input voltage from temp sensor
    voltage = reading * (5.0 / 1023.0);            
    //temperature = (voltage - .5) * 10.0;        
    temperature = (voltage + 1244.4) * 0.0225; 
       
}
void delay_ms(unsigned int x)
{
	unsigned int a,b;
	for(a=x;a>0;a--)
		for(b=110;b>0;b--);
}
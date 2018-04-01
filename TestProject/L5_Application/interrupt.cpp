
#include "interrupt.hpp"


int pin1;
int pin2;
SemaphoreHandle_t SwitchLock = xSemaphoreCreateBinary();

bool Enable_eint3(int pinNumber1, int pinNumber2)
{

	 if(pinNumber1 >=0 && pinNumber1 <= 13 && pinNumber2 >= 0 && pinNumber2 <= 13)
	 {
		 NVIC_EnableIRQ(EINT3_IRQn);
		 LPC_GPIO0->FIODIR &= ~(1 << pinNumber2);
		 LPC_GPIO2->FIODIR &= ~(1 << pinNumber1);
		 isr_register(EINT3_IRQn,Handle_General_Interrupt);
	     LPC_GPIOINT->IO2IntEnR |= (1 << pinNumber1);
	     LPC_GPIOINT->IO0IntEnR |= (1 << pinNumber2);
	     pin1 = pinNumber1;
	     pin2 = pinNumber2;
	     //SwitchLock = xSemaphoreCreateMutex();

		 return true;
	 }
	 else

		 return false;
}

void Handle_General_Interrupt()
{
	xSemaphoreGive(SwitchLock);
	bool status0 = LPC_GPIOINT->IO0IntStatR & (1 << pin2);
	bool status2 = LPC_GPIOINT->IO2IntStatR & (1 << pin1);

	if(xSemaphoreTake(SwitchLock,portMAX_DELAY))
	{
		delay_ms(200);
	}
	xSemaphoreGive(SwitchLock);
	if(status0)
	{
		LPC_GPIOINT->IO0IntEnR &= ~(1 << pin2);
		Switch1();
		LPC_GPIOINT->IO0IntEnR |= (1 << pin2);

	}
	else if(status2)
	{
		LPC_GPIOINT->IO2IntEnR &= ~(1 << pin1);
		Switch2();
		LPC_GPIOINT->IO2IntEnR |= (1 << pin1);


	}



}

void Switch1()
{

	{
		u0_dbg_printf("Switch on port 0 pressed\n\n");
		delay_ms(200);
	    LPC_GPIOINT->IO0IntClr = 0xFFFFFFFF;
	}


}

void Switch2()
{
	//if(xSemaphoreTake(SwitchLock,portMAX_DELAY))
	{
		u0_dbg_printf("Switch on port 2 pressed\n\n");
		delay_ms(200);
		LPC_GPIOINT->IO2IntClr = 0xFFFFFFFF;
	}

}

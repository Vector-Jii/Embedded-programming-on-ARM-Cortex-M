/*Objective : Generate the below peripheral interrupt using NVIC interrupt pending register and observer the execution
 * of IRSs when the priority is same and different \
 * 	TIM2 global interrupt   IRQ no 28
 * 	I2C1_EV event interrupt IRQ no 31 */
#include <stdint.h>
#include <stdio.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define IRQNO_TIMER2 28
#define IRQNO_I2C1_EV 31

// pointer variable to hold base address
uint32_t *pNVIC_IPRBase = (uint32_t*)0xE000E400;
uint32_t *pNVIC_ISERBase = (uint32_t*)0xE000E100;
uint32_t *pNVIC_ISPRbase = (uint32_t*)0XE000E200;

void configure_priority_for_irqs(uint8_t irq_no,uint8_t priority_value)
{
	//which IPR to use
	uint8_t iprx = irq_no/4;  //  IPR 7
	uint32_t *ipr = pNVIC_IPRBase+iprx;

	//position of bit within the selected IPR
	uint8_t pos = (irq_no%4)*8;

	//configure the priority
	*ipr &= ~(0xFF << pos);   //clear
	*ipr |= (priority_value << pos);
}

int main(void)
{
//	 1) Let's configure the interrupt priority
	configure_priority_for_irqs(IRQNO_TIMER2,0x80);

	configure_priority_for_irqs(IRQNO_I2C1_EV,0x70);

//	 2) set interrupt pending bit in NVIC
	*pNVIC_ISPRbase |= (1<< IRQNO_TIMER2); //Triggering the interrupt for TIMER2

//	 3) Enable the IRQ
	*pNVIC_ISERBase |= (1 << IRQNO_I2C1_EV);
	*pNVIC_ISERBase |= (1 << IRQNO_TIMER2);

    /* Loop forever */
	for(;;);
}

// isrs
void TIM2_IRQHandler(void)
{
	printf("TIM2_IRQHandler \n");
	*pNVIC_ISPRbase |= (1<< IRQNO_I2C1_EV);  // Triggering the interrupt for I2C1
	while(1);
}

void I2C1_EV_IRQHandler(void)
{
	printf("I2C1_EV_IRQHandler \n");
}

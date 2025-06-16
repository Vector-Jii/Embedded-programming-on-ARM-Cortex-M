#include <stdio.h>
#include <stdint.h>


/*This function executes in the thread MODE of the processor*/
generate_interrupt()
{
	uint32_t *pSTIR = (uint32_t*)0xE000EF00;
	uint32_t *pISER0 = (uint32_t*) 0xE000E100;

	//enable IRQ 3
	*pISER0 |= (1 << 3);

	//generate a interrupt for software for IRQ 3
	*pSTIR = (3 & 0x1FF);
}

/*This function executes in the thread mode of the processor*/
void main(){
	printf("In thread mode before the interrupt");

	generate_interrupt();

	printf("In thread mode after the interrupt");

	for(;;);
}

void RTC_WKUP_IRQHandler(void)
{
	printf("In handler mode \n");
}

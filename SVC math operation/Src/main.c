/*
 * Write a program to add subtract ,multiply and divide 2 operands using SVC handler
 * and return the result to thread mode and print the result .Thread mode code should
 * pass 2 operand via the stack frame
 * hint :  36 -> addition
 *         37 -> subtraction
 *         38 -> multiplication
 *         39 -> division
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include<stdint.h>
#include<stdio.h>

void SVC_Handle_c(uint32_t *pBaseStackFrame);    // function prototype

int32_t add_numbers(int32_t x , int32_t y )    // 1st arg in R0 ,2nd arg in R1 and so on
{
		int32_t res;
		__asm volatile("SVC #36");
		__asm volatile("MOV %0,R0": "=r"(res) ::);
		return res;
}


int32_t sub_numbers(int32_t x , int32_t y )
{
	    int32_t res;
		__asm volatile("SVC #37");
		__asm volatile("MOV %0,R0": "=r"(res) ::);
		return res;

}

int32_t mul_numbers(int32_t x , int32_t y )
{
	    int32_t res;
		__asm volatile("SVC #38");
		__asm volatile("MOV %0,R0": "=r"(res) ::);
		return res;

}

int32_t div_numbers(int32_t x , int32_t y )
{
	    int32_t res;
		__asm volatile("SVC #39");
		__asm volatile("MOV %0,R0": "=r"(res) ::);
		return res;

}


int main(void)
{
	int32_t res;

	res = add_numbers(40, -90);
	printf("Add result = %ld \n",res);

	 res = sub_numbers(25,150);
	printf("Sub result = %ld\n",res);

	res = mul_numbers(374,890);
	printf("mul result = %ld\n", res);

	res = div_numbers(67,-3);
	printf("div result = %ld\n",res);

    for(;;);
}


__attribute__( ( naked ) ) void SVC_Handler( void )
{
    __asm ("MRS r0,MSP");
    __asm( "B SVC_Handler_c");
}


void SVC_Handler_c(uint32_t *pBaseOfStackFrame)
{
    printf("in SVC handler\n");

    int32_t arg0, arg1, res;

    uint8_t *pReturn_addr = (uint8_t*)pBaseOfStackFrame[6];

    //2. decrement the return address by 2 to point to
    //opcode of the SVC instruction in the program memory
    pReturn_addr-=2;


    //3. extract the SVC number (LSByte of the opcode)
    uint8_t svc_number = *pReturn_addr;

    printf("Svc number is : %d\n",svc_number);

    arg0 = pBaseOfStackFrame[0];
    arg1 = pBaseOfStackFrame[1];

    switch(svc_number)
    {
    case 36:
    	res = arg0 + arg1;
    	return res;
    	break;
    case 37:
    	res = arg0 - arg1;
		return res;
		break;
    case 38:
    	res = arg0 * arg1;
		return res;
		break;
    case 39:
    	res = arg0 / arg1;
		return res;
		break;
    default:
    	printf("Invalid svc code\n");
    }

    pBaseOfStackFrame[0] = res;
}

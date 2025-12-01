#include "uart.h"

void USART1_Init(void){
//1.enable clock access to uart1
	RCC->APB2ENR |= 0x10; 
	//2.enable closk access to portA
	RCC->AHB1ENR |= 0x01;
	//3.Enable pins for alternate fucntions, pa2, pa3
	 
	GPIOA->MODER &=~0xFF0000;
	GPIOA->MODER |= 0x280000; /*Enable alt. function for PA2, PA3*/ 
	//4.Configure type of alternate function
		
	// Configure Alternate Function registers (AFR) for USART1 (AF7 for most STM32s)
	// PA9 (AFRH) and PA10 (AFRH) use AF7 (0111)
	GPIOA->AFR[1] &= ~((0xF) << ( (9-8) * 4)); // Clear bits for PA9 in AFR[1]
	GPIOA->AFR[1] |= ( (7U) << ( (9-8) * 4));  // Set PA9 to AF7

	GPIOA->AFR[1] &= ~((0xF) << ( (10-8) * 4)); // Clear bits for PA10 in AFR[1]
	GPIOA->AFR[1] |= ( (7U) << ( (10-8) * 4));  // Set PA10 to AF7

	//Configure uart

	USART1->BRR  =  0x008B;
	USART1->CR1  =  0x000C; /*Enabled tx rx, 8-bit data*/
	USART1->CR2  =  0x000;
	USART1->CR3  =  0x000;
	USART1->CR1  |=  0x2000; /*Enable uart */
}

int USART1_write(int ch){

	while(!(USART1->SR & 0x0080)){}
	USART1->DR = (ch & 0xFF);
	
  return ch;
}

int USART1_read(void){
  while(!(USART1->SR & 0x0020)){}
	return USART1->DR;
}

/* The code below is the interface to the C standard I/O library.
 * All the I/O are directed to the console.
 */
//struct __FILE { int handle; };
FILE __stdin  = {0};
FILE __stdout = {1};
FILE __stderr = {2};


int fgetc(FILE *f) {
    int c;
	
    c = USART1_read();      /* read the character from console */

    if (c == '\r') {        /* if '\r', after it is echoed, a '\n' is appended*/
        USART1_write(c);    /* echo */
        c = '\n';
    }

    USART1_write(c);        /* echo */

    return c;
}


/* Called by C library console/file output */
int fputc(int c, FILE *f) {
    return USART1_write(c);  /* write the character to console */
}


int n;
char str[80];
		
void test_setup(void){
	
	printf("please enter a number: ");
	scanf("%d", &n);
	printf("the number entered is: %d\r\n", n);
	printf("please type a character string: ");
	gets(str);
	printf("the character string entered is: ");
	puts(str);
	printf("\r\n");
	
}
#include "uart.h"


/* The code below is the interface to the C standard I/O library.
 * All the I/O are directed to the console.
 */
//struct __FILE { int handle; };
FILE __stdin  = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *f) {
    int c;

    c = USART_read();      /* read the character from console */

    if (c == '\r') {        /* if '\r', after it is echoed, a '\n' is appended*/
        USART_write(c);    /* echo */
        c = '\n';
    }

    USART_write(c);        /* echo */

    return c;
}


/* Called by C library console/file output */
int fputc(int c, FILE *f) {
    return USART_write(c);  /* write the character to console */
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

int USART_write(int ch){

	while(!(USART1->SR & 0x0080)){}
	USART1->DR = (ch & 0xFF);
	
  return ch;
}

int USART_read(void){
  while(!(USART1->SR & 0x0020)){}
	return USART1->DR;
}
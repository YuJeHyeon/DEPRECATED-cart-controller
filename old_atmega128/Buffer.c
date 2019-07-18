// S/W Environment : AVR Studio + WINAVR Compiler
// Target : M128
// Crystal: 16Mhz
//
// Made by chowk.
// Circular Buffer

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "Buffer.h"

#define UART0_BUF_SIZE 8

unsigned char rx0_buf[UART0_BUF_SIZE];
volatile signed int p_rx0_wr, p_rx0_rd;
volatile signed int rx0_data_counter;
volatile signed char buffer_full_flag;
volatile signed char buffer_empty_flag;

unsigned char get_char_uart0 (void);


void init_BUFFER()
{
	unsigned int i;

	buffer_full_flag = FALSE;
	buffer_empty_flag = TRUE;
	p_rx0_wr = 0;
	p_rx0_rd = 0;
	rx0_data_counter = 0;
	for (i=0; i<UART0_BUF_SIZE; i++) rx0_buf[i] = 0;
}

// Buffer�� ���ڸ� �߰� �Ѵ�.
// Buffer �� Full ���� �̸� Buffer Full �޼����� ��� �Ѵ�.
void putchar2buffer(unsigned char c) 
{
	// Buffer �� Full ���°� �ƴϸ� ���޵� ���ڸ� Buffer�� ���� �Ѵ�.
	if (rx0_data_counter < UART0_BUF_SIZE)
	{
		rx0_data_counter++;
		rx0_buf[p_rx0_wr] = c;
		buffer_empty_flag = FALSE;
//printf(" INT rx0: %c  UDR0: %c pt_w: %d   ct: %d\r\n",rx0_buf[p_rx0_wr],UDR0,p_rx0_wr,rx0_data_counter);


		p_rx0_wr++;
		if (p_rx0_wr >= (UART0_BUF_SIZE))p_rx0_wr = 0;
		//		SCI_OutString("Error: Uart0 buffer full");	
	}
	// Buffer �� Full ���� �̸� buffer_full_flag�� TRUE�� �ϰ� Input Buffer Full �޼����� ��� �Ѵ�.
	else {
		buffer_full_flag = TRUE;
		printf("\r\nInput Buffer Full.");
		}
}

// Buffer�� ���� ���� �ϳ��� �о� ����. 
// Buffer�� ��� �ִ� ��� Buffer Empty �޼����� ��� �ϰ�, 0�� return �Ѵ�.
unsigned char getchar_buffer(void)
{
	char c;

	// Buffer �� Empty ���°� �ƴϸ� ���� ���ڸ� Return �Ѵ�.
	if(rx0_data_counter > 0)
	{
		c = rx0_buf[p_rx0_rd];
//printf(" Get rx0: %c          pt_r: %d  ct: %d\r\n",rx0_buf[p_rx0_rd],p_rx0_rd,rx0_data_counter);
		rx0_data_counter--;
		buffer_full_flag = FALSE;
		p_rx0_rd++;
		if (p_rx0_rd >= (UART0_BUF_SIZE)) p_rx0_rd = 0;
		return c;
	}
	// Buffer�� ��� �ִ� ��� Buffer Empty �޼����� ��� �ϰ�, 0�� return �Ѵ�.
	else {
		buffer_empty_flag = TRUE;
		printf("\r\nInput Buffer Empty.");		
		return 0;
	}
}

// Backspace ���ڰ� �Է� �Ǹ� Buffer�� ����� ���� �ϳ��� ���� �Ѵ�.
void backspace2buffer(void) 
{
	// ���� Buffer�� ����� ���ڰ� �ִ� ��� ����� ���� �ϳ��� ���� �Ѵ�.
	if (rx0_data_counter > 0)
	{
		rx0_data_counter--;
		buffer_full_flag = FALSE;

		p_rx0_wr--;
		if (p_rx0_wr < 0) p_rx0_wr = UART0_BUF_SIZE - 1;
//printf("  rx0_data_counter:%d  p_rx0_wr:%d \r\n",rx0_data_counter, p_rx0_wr );
	}
	// Buffer�� ��� �ִ� ��� Buffer Empty �޼����� ��� �Ѵ�.
	else {
		buffer_empty_flag = TRUE;
		printf("\r\nInput Buffer Empty.");
		}
}

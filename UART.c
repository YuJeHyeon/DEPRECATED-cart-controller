// S/W Environment : AVR Studio + WINAVR Compiler
// Target : M128
// Crystal: 16Mhz
//
// Made by chowk.
// UART init and basic function

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Buffer.h"
#include "UART.h"

#define F_CPU 16000000               // Clock Speed
//define BAUD1 115200        // R-PI
#define BAUD0 9600            // HC-06
//#define BAUD1 9600



// #define MYUBRR1 (F_CPU/8/BAUD1-1)      // Double the USART Transmission Speed
#define MYUBRR0 (F_CPU/8/BAUD0-1)

void init_UART0(void);
unsigned char rx0_char(void);
void tx0_char(unsigned char data);
//void uart1_init(void);



// UART1 initialize
// Char size: 8 bit, Parity: Disabled

/*
void init_UART1(void)
{
   unsigned int ubrr;   

   ubrr = MYUBRR1;         // Set baud rate

   UBRR1H = (unsigned char)(ubrr>>8);
   UBRR1L = (unsigned char)ubrr;
   // Double the USART Transmission Speed
   UCSR1A = (1<<U2X1); 
   // Enable receiver and transmitter
   UCSR1B = (1<<RXEN1)|(1<<TXEN1);
   // Set frame format: 8data, 1stop bit
   UCSR1C = (0<<USBS1)|(3<<UCSZ10);
}
*/

void init_UART0(void)
{
   unsigned int ubrr;   

   ubrr = MYUBRR0;         // Set baud rate

   UBRR0H = (unsigned char)(ubrr>>8);
   UBRR0L = (unsigned char)ubrr;
   // Double the USART Transmission Speed
   UCSR0A = (1<<U2X); 
   // Enable receiver and transmitter //RXCIE: SREG�� set�ǰ� �굵 set�̸� RXcomplete interrupt�߻�, UDRn Data�� �о ��밡��
   UCSR0B = (1<<RXEN)|(1<<TXEN)|(1 << RXCIE); 
   // Set frame format: 8data, 1stop bit // USBS1: stop bit, UCSZ10: 8bit data set
   UCSR0C = (0<<USBS)|(3<<UCSZ0); //���ϸ� 9��Ʈ�� ����
}



unsigned char rx0_char(void)
{
   // Wait for data to be received
   while ( !(UCSR0A & (1<<RXC)) ); //receive 
   // Get and return received data from buffer
   return UDR0;
}


// UART1 �� �̿��� ���
void tx0_char(unsigned char data)
{
   // Wait for empty transmit buffer
   while ( !(UCSR0A & (1<<UDRE))); //transmit buffet�� ���� ǥ�� set�̸� empty
   // Put data into buffer, sends the data
   UDR0 = data;
}


/* 16������ �ٲٱ�
void SCI_OutUHex(unsigned short number){
  if(number >= 0x10) {
    SCI_OutUHex(number / 0x10);
    SCI_OutUHex(number % 0x10);
  }
  else if(number < 0xA){
    SCI_OutChar(number + '0');
  }
  else{
    SCI_OutChar((number - 0x0A) + 'A');
  }
} 
*/
/*
unsigned char rx1_char(void)
{
   // Wait for data to be received
   while ( !(UCSR1A & (1<<RXC1)) );
   // Get and return received data from buffer
   return UDR1;
}

// UART1 �� �̿��� ���
void tx1_char(unsigned char data)
{
   // Wait for empty transmit buffer
   while ( !(UCSR1A & (1<<UDRE1)));
   // Put data into buffer, sends the data
   UDR1 = data;
}
*/

//-------------------------SCI_OutChar to USART------------------------

void SCI_OutChar(char letter){ 
   tx0_char(letter);
}

//-------------------------SCI_InChar from USART------------------------

unsigned short SCI_InChar(){ 
  return (rx0_char());
}

void SCI_OutString(char *pt)
{ char letter;
  while((letter = *pt++)){
    SCI_OutChar(letter);
  }
}

 //USART1, Rx Interrupt ó�� Routine                                           

/*
ISR(USART0_RX_vect)
{
	char c;
	// �Էµ� ���ڸ� ó�� �ϴ� ���� ���ο� Interrupt�� �߻� ���� �ʵ���
	// Rx Interrupt�� Disable �Ѵ�.
	UCSR0B &= ~(1 << RXCIE0);   // Rx Complete Interrupt disable

	c = rx0_char();

	if(c=='a') Add_Speed+=25;
	
	UCSR0B |= (1 << RXCIE0); 
}*/
/*
ISR(USART0_RX_vect)
{
   char c;

   // �Էµ� ���ڸ� ó�� �ϴ� ���� ���ο� Interrupt�� �߻� ���� �ʵ���
   // Rx Interrupt�� Disable �Ѵ�.
   UCSR0B &= ~(1 << RXCIE0);   // Rx Complete Interrupt disable

   c = UDR0;
   // �Էµ� ���ڰ� CR or BS Code �� �ƴ� ���
   if(!((c == CR) | (c == BS))){
      // Buffer�� ���ڸ� ���� �Ѵ�.
      putchar2buffer(c);
      // Buffer�� ���ڸ� ���� �ϴ� ���� ������ ��� ���ڸ� ����Ϳ� ��� �Ѵ�.
      // buffer_full_flag �� TRUE �� ���� ���� Buffer �� Full �����̱� ������
      // ���ڸ� Buffer�� ���� ���� ���� ��� �̴�.
      if(buffer_full_flag == FALSE)tx0_char(c);
   }
   // ���� �Էµ� ���ڰ� BS Code�� ��� Buffer���� ���� �ϳ��� ��� �Ѵ�.
   if(c == BS){
      backspace2buffer();
      tx0_char(BS);
   }

   // ���ο� ���ڸ� ���� �� �ֵ��� Rx Interrupt�� Enable �Ѵ�.
   UCSR0B |= (1 << RXCIE0); // Rx Complete Interrupt enable

   // ���� �Էµ� ���ڰ� CR Code�� ��� Tx Interrupt�� Enable �Ѵ�.
   // CTx Interrupt�� Enable �Ǹ� Tx Interrupt ó�� Routine ����
   // Buffer�� ������ ����Ϳ� ��� �ϰ� �ȴ�.
   if(c == CR){
      UCSR0B |= (1 << TXCIE0); // Tx Complete Interrupt enable
      tx0_char(CR); tx0_char(LF);
   }
} 

// USART0, Tx Interrupt ó�� Routine
ISR(USART0_TX_vect)
{
   char c;

   // Tx Interrupt�� ó�� �ϴ� ���� ���ο� Rx Interrupt�� �߻� ���� �ʵ���
   // Rx Interrupt�� Disable �Ѵ�.
   UCSR0B &= ~(1 << RXCIE0);   // Rx Complete Interrupt disable

   // Interrupt ó���� �ϴ� ���� ���ο� Interrupt�� �߻� ���� �ʵ���
   // Tx Interrupt�� Disable �Ѵ�.
   UCSR0B &= ~(1 << TXCIE0);   // Tx Complete Interrupt disable

   // Buffer�� ���� �ϳ��� ���ڸ� ���� �´�.
   c = getchar_buffer();
   // ���� ���ڰ� �ҹ����̸� �빮�ڷ� ��ȯ �Ѵ�.
   if((c >= 'a') && (c <= 'z')) c &= 0b11011111;
   // Buffer�� ���� ���������� ���ڸ� ������ ���  
   if(c != 0){
      // ����Ϳ� ���ڸ� ��� �Ѵ�.
      tx0_char(c);
      // ���ο� ���ڸ� ��� �� �� �ֵ��� Tx Interrupt�� Ensable �Ѵ�.
      UCSR0B |= (1 << TXCIE0); // Tx Complete Interrupt enable
    }
   // ���ο� ���ڸ� ���� �� �ֵ��� Rx Interrupt�� Ensable �Ѵ�.
   else {
      tx0_char(CR); tx0_char(LF);
      UCSR0B |= (1 << RXCIE0); // Rx Complete Interrupt enable
   }
}
*/

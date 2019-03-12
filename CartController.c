/**************************************************************
TrashCarrier
Made by HHC
**************************************************************/
#  ifndef atmega128
	#define atmega128
#  endif
#define FOSC 16000000// Clock Speed

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Timer_pwm.h"
#include "UART.h"
#include "Motor.h"
#include "Buffer.h"
#include "Sensor.h"

int put_char(char c, FILE *stream)
{
	tx0_char(c);
	return 0;   
}

void init_DEVICES(void)
{
	cli();         			// Disable all interrupts
	fdevopen(put_char,0);
	init_UART0();
	init_BUFFER();
	init_MOTOR();
	init_TIMER3();	
	init_SONAR();
	init_ENCODER();
	init_PSD();
	sei();                 // Re-enable interrupts
}


int main(){

	//char buffer1[50], buffer2[50];

	//TCNT1 = 34286; //Ÿ�̸�0�� ������ 0.0025�� �����÷� ���ͷ�Ʈ�� ����� ���ؼ� 14.7456MHZ�ε� TCCRO�� ������ 256����
	//TIMSK=0x04; //Ÿ�̸�0 �����÷� ���ͷ�Ʈ�� �㰡��
	init_DEVICES();	
	MotorStop();
	MotorGoFoward();
	OCR3A = 600;
	OCR3B = 600;
	while(1)
	{ 
	//	y_SONAR();


    // SONAR BLUETOOTH DISPLAY
	/*	itoa(cnt1,buffer1,10); //char���� ��ȯ
   		itoa(cnt2,buffer2,10);

    	SCI_OutChar('L'); 
		SCI_OutChar(32);  // space bar
    	SCI_OutString(buffer1); //���ڴ���
    	SCI_OutChar(32);
    	SCI_OutChar('R');
		SCI_OutChar(32); 
    	SCI_OutString(buffer2);
   		SCI_OutChar(LF);  // ������
   		SCI_OutChar(CR);*/
		
		PID();
	//	if(flag){  //1�� ���
            //RPM_L=60*(M_L/60)/0.1;// rpm=(60*m)/(�ֱ�*���ش�)=(60*m)/(1s*1000) // ������ ���� 
            //RPM_R=60*(M_R/60)/0.1;
		//	enc_norm1 = (RPM_L - NORM_MIN)/(NORM_MAX - NORM_MIN) * RANGE_MAX;
		//	enc_norm2 = (RPM_R - NORM_MIN)/(NORM_MAX - NORM_MIN) * RANGE_MAX;
			// W1_MIN, W2_MIN: 400

      //      flag=0;
   	//	}
       // RPM_L=M_L; //rpm=(60*m)/(�ֱ�*���ش�)=(60*m)/(1s*200)	
		//RPM_R=M_R; //rpm=(60*m)/(�ֱ�*���ش�)=(60*m)/(1s*200)	                     
        



	}			 	
	return 0;
}
// USART1, Rx Interrupt ó�� Routine
/*
SIGNAL(USART0_RX_vect)
{
	 char c;
	
	// �Էµ� ���ڸ� ó�� �ϴ� ���� ���ο� Interrupt�� �߻� ���� �ʵ���
	// Rx Interrupt�� Disable �Ѵ�.
	UCSR0B &= ~(1 << RXCIE0);	// Rx Complete Interrupt disable
	
	c = command;
	command = c;
	tx0_char(c);
	//MotorCommand(c);
	
	UCSR0B |= (1 << RXCIE0);

}*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Sensor.h"
#include "Motor.h"
#include "Timer_pwm.h"

void init_MOTOR(){
	
	//MotorPort &= ~(Motor_Mask);                                                                                                                                                                                                                                                                                                                
	MotorPort_DDR |= Motor_Mask;
	MotorPort_PWMDDR = 0x18;
	asm volatile(" NOP");

}
void MotorGoFoward()//����
{	

//	MotorStop();
//	delay_1mSec(10);
//	PORTF = 0x02;
 	MotorPort |= (1<<MotorL_1)|(1<<MotorR_1);
	MotorPort &= ~((1<<MotorL_2)|(1<<MotorR_2));
	asm volatile(" NOP");
}
void MotorGoBackward()//���� 
{
//	PORTF = 0x03;
	MotorPort &= ~((1<<MotorL_1)|(1<<MotorR_1));
	MotorPort |= (1<<MotorL_2)|(1<<MotorR_2);
	asm volatile(" NOP");
}
void TurnRight()//��������
{
//	PORTF = 0x04;
	OCR3A = 700;
	OCR3B = 600;
	MotorPort |= (1<<MotorL_1)|(1<<MotorR_2);
	MotorPort &= ~((1<<MotorL_2)|(1<<MotorR_1));
}
void TurnLeft() //������
{
//	PORTF = 0x05;
	OCR3A = 700;
	OCR3B = 600;
	
	MotorPort |= (1<<MotorL_2)|(1<<MotorR_1);
	MotorPort &= ~((1<<MotorL_1)|(1<<MotorR_2));
}
void MotorStop()//����
{
//	PORTF = 0x06;
	MotorPort &= ~((1<<MotorL_2)|(1<<MotorR_1)|(1<<MotorL_1)|(1<<MotorR_2));
	asm volatile(" NOP");
}
void MotorCommand(char command)//����Ʈ�� ��ɾ�
{	
	MotorPort |= 0x00;
	if ( command == 'w') avoid_PSD();
	else if ( command == 'x') MotorGoBackward();
	else if ( command == 's')
 	{   DDRE=1;
		MotorStop();
		PORTE = 1;
	
	}
	else if ( command == 'a')  TurnLeft();
	else if ( command == 'd')  TurnRight();
	else if ( command == 'q')  Left3();
	else if ( command == 'z')  Left4();
	else if ( command == 'e')  Right3();
	else if ( command == 'c')  Right4();

}
void Motor_Sonar(unsigned int x, unsigned int y)
{
	MotorGoFoward();
	OCR3A = (x);//�ʿ��� ��ŭ ����
	OCR3B = (y);//�ʿ��� ��ŭ ����
}
void Left1(int a)//Custom ��ȸ��
{
	MotorGoFoward();
	OCR3A = 1000 - a;//�ʿ��� ��ŭ ����
	OCR3B = 1000;
}

void Left2(void)//���� ��ȸ��
{
	MotorGoFoward();
	OCR3A = 1000 - 400;
	OCR3B = 1000;
}

void Left3(void)//���� ��ȸ��
{
	MotorGoFoward();
	OCR3A = 1000 - 800;
	OCR3B = 1000;
}
void Left4(void)//���� ��ȸ��
{
	MotorGoFoward();
	OCR3A = 0;
	OCR3B = 1023;
}

void Right1(int b)//Custom ��ȸ��
{
	MotorGoFoward();
	OCR3A = 1000;
	OCR3B = 1000-b;//�ʿ��� ��ŭ ����
}


void Right2(void)//���� ��ȸ��
{
	MotorGoFoward();
	OCR3A = 1023;
	OCR3B = 900-500;
}

void Right3(void)//���� ��ȸ��
{
	MotorGoFoward();
	OCR3A = 1023;
	OCR3B = 900-800;
}
void Right4(void)//���� ��ȸ��
{
	MotorGoFoward();
	OCR3A = 1023;
	OCR3B = 0;
}

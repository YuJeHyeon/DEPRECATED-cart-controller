
/**************************** [SONAR] ******************************************
PF0,2 >> ���� ������ [Ʈ���� & ����]
PF1,3 >> ������ ������ [Ʈ���� & ����]
*****************************************************************************/

#define trig1_1 PORTF|=1  // PF0, srf04-1 Ʈ����
#define trig1_0 PORTF&=~1 // PF0, srf04-1 Ʈ����
#define echo1   (PINF&4)  // PF2, srf04-1 ����
//
#define trig2_1 PORTF|=2  // PF1, srf04-2 Ʈ����
#define trig2_0 PORTF&=~2 // PF1, srf04-2 Ʈ����
#define echo2   (PINF&8)  // PF3, srf04-2 ����
//
//����ȭ ���� ����
unsigned int n_v1, n_v2; // ����ȭ �� ��
float norm1,norm2,diff1,diff2;

//Define : ���� ��&�� �ּҰ�(W1, W2), ����ȭ Min&Max ��(Norm), ���� ������(Range) 
#define W1_MIN 400
#define W2_MIN 400
#define RANGE_MAX 60
#define NORM_MIN 3
#define NORM_MAX 180

unsigned int  cnt1,cnt2;

void get_SONAR();
void y_SONAR(void);
void init_SONAR(void);

/**************************** [PSD] ******************************************
PORTA >> ��
PORTB >> ��
*****************************************************************************/

char PSD_SIDE; 
char PSD_FRONT;
 
char FPA[7];
char FPC[7];

char drive;
unsigned int weightR;
unsigned int weightL;

void init_PSD();	
void get_PSD();
void avoid_PSD();
void drive_PSD();

/*********************************[ENCODER]***********************************
INT0 (PD0) >> ��
INT1 (PD1) >> ��
*****************************************************************************/

//���� ����ȭ�� ����
#define ENC_NORM_MIN 0
#define ENC_NORM_MAX 1023

unsigned int enc_norm1,enc_norm2, enc_diff1, enc_diff2; // ����ȭ �� ��

//�������� �����
volatile unsigned int count_L, count_R, encoder_T, flag, M_L,M_R, RPM_L, RPM_R;
volatile unsigned int encT_L, encT_R;
/*
volatile float motor_signal0;
volatile float error_funct;
volatile float old_error_funct;
volatile float old_error_funct2;
volatile float desired;
volatile float measured;
volatile float old_motor_signal;
volatile double KP;
volatile double KD;
volatile double KI;
volatile float delta_t;
volatile int limit;
volatile int pwmduty;*/

//�Լ� �����
void init_ENCODER();
//void PID(void);

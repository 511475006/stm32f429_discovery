#include <stm32f4xx.h>

#include <raw_api.h>

/******************************************************************************/
#define SYS_LED_TASK_STK_SIZE 	128
static PORT_STACK 				sys_led_task_stk[SYS_LED_TASK_STK_SIZE];
static RAW_TASK_OBJ 			sys_led_task_obj;
/******************************************************************************/

static struct
{
	GPIO_TypeDef *port;
	uint16_t pin;
}SYS_LED[] =
{
	{GPIOG, GPIO_Pin_13},
};

static void sys_len_init(void)
{
	int i;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	for(i=0; i<ARRAY_SIZE(SYS_LED); i++)
	{
		GPIO_InitStructure.GPIO_Pin = SYS_LED[i].pin;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		
		GPIO_Init(SYS_LED[i].port, &GPIO_InitStructure);
	}
}

static void sys_led_on(unsigned char n)
{
	SYS_LED[n].port->BSRRL = SYS_LED[n].pin;	//��λ
}
static void sys_led_off(unsigned char n)
{
	SYS_LED[n].port->BSRRH = SYS_LED[n].pin; //��λ
}

static void sys_led_task(void *pdat)
{
	(void)pdat;
	
	raw_printf("sys_led init...\r\t\t\t\t");
	sys_len_init();
	raw_printf("[OK]\r\n");
	
	for(;;)
	{
		sys_led_on(0);
		raw_sleep(RAW_TICKS_PER_SECOND>>1);
		sys_led_off(0);
		raw_sleep(RAW_TICKS_PER_SECOND>>1);
	}
}

void sys_led_init(RAW_U8 prio)
{
	raw_task_create(&sys_led_task_obj, 			/* ������ƿ��ַ 	*/
					(RAW_U8  *)"sys_led_task", 	/* ������ 			*/
					(void *)0,					/* ������� 		*/
					prio, 						/* ���ȼ� 			*/
					0,							/* ʱ��Ƭ 			*/
					sys_led_task_stk,			/* ����ջ�׵�ַ 	*/
					SYS_LED_TASK_STK_SIZE ,		/* ����ջ��С 		*/
					sys_led_task,				/* ������ڵ�ַ 	*/
					1);							/* �Ƿ��������� 	*/
}

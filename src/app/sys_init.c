#include <raw_api.h>

#include <bsp.h>

/******************************************************************************/
#define SYS_INIT_TASK_STK_SIZE 	128
static PORT_STACK 				sys_init_task_stk[SYS_INIT_TASK_STK_SIZE];
static RAW_TASK_OBJ 			sys_init_task_obj;
/******************************************************************************/

typedef void (*init_func_t)(RAW_U8 prio);
typedef struct init_task_t
{
	init_func_t init_task;	//�����ʼ������
	RAW_U8 prio;			//�������ȼ�
}init_task_t;

/******************************************************************************/

void debug_uart_init(unsigned char prio);
RAW_TASK_OBJ *get_shell_task_obj(void);

void sys_led_init(RAW_U8 prio);
void lua_task_init(unsigned char prio);

/******************************************************************************/

static const init_task_t sys_init_arry[]  = 
{
	{debug_uart_init, 		CONFIG_RAW_PRIO_MAX - 10},		// ���İ崮��
	{port_memory_init, 		CONFIG_RAW_PRIO_MAX     },
	{sys_led_init, 			CONFIG_RAW_PRIO_MAX - 3 },
	{lua_task_init, 		CONFIG_RAW_PRIO_MAX - 5 },
};

static int memory_test(void)
{
	unsigned int *const sdram = SDRAM_BASE_ADDR;
	unsigned int i=0;
	
	for(i=0; i<SDRAM_SIZE/sizeof(unsigned int); i++)
	{
		sdram[i] = i;
	}
	
	for(i=0; i<SDRAM_SIZE/sizeof(unsigned int); i++)
	{
		if(sdram[i] != i)
			break;
	}
	
	return (i>=SDRAM_SIZE/sizeof(unsigned int))? 0 : -1;
}

static void sys_init_task(void *pdat)
{
	(void)pdat;
	int i;
	
	raw_sys_tick_init();   //��һ����������ʱ����ϵͳtick��ʱ��
	
	// debug_uart ��ʼ��
	sys_init_arry[0].init_task( sys_init_arry[0].prio );
	
	raw_printf("\r\n-------------  raw-os  ----------------\r\n");
	
	RAW_ASSERT( 0 == memory_test() );
	
	// �����ʼ��, ��1��ʼ������debug_uart
	for(i=1; i<ARRAY_SIZE(sys_init_arry); i++)
	{
		sys_init_arry[i].init_task( sys_init_arry[i].prio );
	}

	raw_printf("\r\n---------------------------------------\r\n");
	
	raw_task_resume(get_shell_task_obj()); 		// ����shell_deamon
	
	for(;;)
	{	
		raw_task_suspend(raw_task_identify());
	}
}

void create_init_task(void)
{
	raw_task_create(&sys_init_task_obj,			/* ������ƿ��ַ 	*/
					(RAW_U8  *)"sys_init_task",	/* ������ 			*/
					(void *)0,					/* ������� 		*/
					CONFIG_RAW_PRIO_MAX - 2,	/* ���ȼ� 			*/
					0,							/* ʱ��Ƭ 			*/
					sys_init_task_stk,			/* ����ջ�׵�ַ 	*/
					SYS_INIT_TASK_STK_SIZE ,	/* ����ջ��С 		*/
					sys_init_task,				/* ������ڵ�ַ 	*/
					1);							/* �Ƿ��������� 	*/
}

#include <stm32f4xx.h>

#include <raw_api.h>


/******************************************************************************/
#define DEBUG_SHELL_TASK_STK_SIZE 	512
static  PORT_STACK 				debug_shell_task_stk[DEBUG_SHELL_TASK_STK_SIZE];
static  RAW_TASK_OBJ 			debug_shell_task_obj;
/******************************************************************************/


int debug_write(const void *buf, int len)
{
	return 0;
}



/******************************************************************************/

RAW_TASK_OBJ *get_shell_task_obj(void)
{
	return &debug_shell_task_obj;
}

static void debug_shell_task(void *pdat)
{	
	(void)pdat;
//	uart0_init(115200);
//	if(debug_fifo_init() < 0)
//	{
//		for(;;);
//	}
//	
//	cli_init();
	
	raw_task_suspend(raw_task_identify());	// �������, �ȴ�sys_init����
	for(;;)
	{
		raw_task_suspend(raw_task_identify());
//		cli_loop();
	}
}





void debug_uart_init(unsigned char prio)
{
	raw_task_create(&debug_shell_task_obj, 				/* ������ƿ��ַ 	*/
					(RAW_U8  *)"shell_daemon", 			/* ������ 			*/
					(void *)0,							/* ������� 		*/
					prio, 								/* ���ȼ� 			*/
					0,									/* ʱ��Ƭ 			*/
					debug_shell_task_stk,				/* ����ջ�׵�ַ 	*/
					DEBUG_SHELL_TASK_STK_SIZE ,			/* ����ջ��С 		*/
					debug_shell_task,					/* ������ڵ�ַ 	*/
					1);									/* �Ƿ��������� 	*/	
}

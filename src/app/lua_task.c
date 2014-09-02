#include <stdio.h>

#include <raw_api.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

/******************************************************************************/
#define LUA_TASK_STK_SIZE 		(16 *1024)
static PORT_STACK 				lua_task_stk[LUA_TASK_STK_SIZE];
static RAW_TASK_OBJ 			lua_task_obj;
/******************************************************************************/

#include "stm32f429i_discovery_lcd.h"

static void lua_task(void *pdat)
{
	(void)pdat;
	
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	
	for(;;)
	{
		LCD_Clear(0xFFFF);
		LCD_SetLayer(LCD_FOREGROUND_LAYER);
		LCD_DrawCircle(100, 100, 50);
		raw_task_suspend(raw_task_identify());
	}
}

void lua_task_init(unsigned char prio)
{
	raw_task_create(&lua_task_obj,			/* ������ƿ��ַ 	*/
					(RAW_U8  *)"lua_task",	/* ������ 			*/
					(void *)0,				/* ������� 		*/
					prio,					/* ���ȼ� 			*/
					0,						/* ʱ��Ƭ 			*/
					lua_task_stk,			/* ����ջ�׵�ַ 	*/
					LUA_TASK_STK_SIZE ,		/* ����ջ��С 		*/
					lua_task,				/* ������ڵ�ַ 	*/
					1);						/* �Ƿ��������� 	*/
}

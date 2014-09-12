#ifndef __CLI_CONFIG_H__
#define __CLI_CONFIG_H__

#define CONFIG_SYS_PROMPT 	"raw-os# "	// ϵͳ������ʾ��

#define CONFIG_SYS_CBSIZE 	(80) 	// console I/O buffer size

#define CONFIG_SYS_MAXARGS 	(5) 	//
#define CONFIG_SYS_HELP_CMD_WIDTH 	"8"

#define CLI_POOL_SIZE 	1024 		// CLI ����ش�С

#define CONFIG_AUTO_COMPLETE 	 	// �Զ���ȫ
#define CONFIG_CMDLINE_EDITING 	 	// ʹ����ʷ����
#define CONFIG_SYS_LONGHELP 	 	// ʹ�ܳ�������Ϣ
#define CONFIG_CMD_RUN

#define SIGNLE_CR_LF 		0 		// �ն˷��͵��ǵ���<CR>��<LF>��1; ���ͬʱ����<CR><LF>��0


#endif

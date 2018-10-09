#include "common.h"

int main(int argc,char *argv[])
{
	for (int i = 1; i < argc; ++i )
	{
		if ( strchr(argv[i], '.') == NULL )
			g_nPort = atoi(argv[i]);
		else
			g_Host = argv[i];
	}

	if ( g_Host == "" ) g_Host = IPADDRESS;
	if ( g_nPort <= 0 ) g_nPort = PORT;
	printf("init port is set to %d\n", g_nPort);

    // 开始监听并处理连接
    DoServer(IPADDRESS, g_nPort, g_nPort);

    return 0;
}


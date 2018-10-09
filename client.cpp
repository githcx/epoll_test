#include "common.h"
#include <unistd.h>
#include <stdio.h>

int OneClient()
{
	printf("client #%d\n", (int)getpid());
	fflush(stdout);
    DoConnect(IPADDRESS, PORT, g_conn_timeout);
    return 0;
}

int main(int argc,char *argv[])
{
	int cli_port = -1;
	for (int i = 1; i < argc; ++i)
	{
		if ( strchr(argv[i], '.') == NULL )
			cli_port = atoi(argv[i]);
		else
			g_Host = argv[i];
	}

	if ( cli_port <= 0 )
		cli_port = PORT;

	if ( g_Host == "" )
		g_Host = IPADDRESS;
	
	int nClient = PARALLEL_CLIENTS;
	if (nClient > 1)
	{
		nClient -= 5;
		for (int i = 0; i < nClient; ++i)
		{
			pid_t pid = fork();
			if ( pid < 0 ) return -1;
			if ( pid == 0 ) return OneClient();
		}
		return 0;
	}

    // 开始读取stdio，并在读取完成后完成一次echo(write-read)
    DoConnect(g_Host.c_str(), cli_port, g_conn_timeout);

    return 0;
}

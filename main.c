// a simple program which makes a listener and prints the ip address of peers who connect
#include <stdio.h>

#include "tcp.h"
#include "tcp.c"

int main(void)
{
	int ipv4_listener, client;
	char peer_address[22];
	
	ipv4_listener = make_tcp_listener(1024);
	
	while(1)
	{
		client = wait_for_connection(ipv4_listener);
		
		get_ip_address(client, peer_address);
		
		printf("peer address: %s\n", peer_address);
	}
	
	return 0;
}
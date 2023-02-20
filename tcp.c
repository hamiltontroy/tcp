#include <unistd.h> // close
#include <arpa/inet.h> // sockaddr_in and all the socket stuff
#include <string.h> // memset
#include <stdio.h> // sprintf

int make_tcp_listener(unsigned short port_number)
{
    int
        listener_fd;
    struct sockaddr_in
        listener_address;

    listener_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listener_fd == -1)
    {
        return -1;
    }
    
    memset(&listener_address, 0, sizeof(struct sockaddr_in));
    
    listener_address.sin_family = AF_INET;
    listener_address.sin_port = htons(port_number);
    listener_address.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(listener_fd, (const struct sockaddr*) &listener_address, 
        sizeof(struct sockaddr_in)) == -1)
    {
        close(listener_fd);
        return -1;
    }
    
    if(listen(listener_fd, 4096) == -1)
    {
        close(listener_fd);
        return -1;
    }
    
    return listener_fd;
}

int wait_for_connection(int listener)
{
	return accept(listener, NULL, NULL);
}

int get_ip_address(int ipv4_socket, char *destination)
{
	struct sockaddr_in address;
	socklen_t len;
	char *dot_address;
	unsigned short port_number;
	
	len = sizeof(struct sockaddr_in);
	getpeername(ipv4_socket, (struct sockaddr*)&address, &len);
	dot_address = inet_ntoa(address.sin_addr);
	port_number = ntohs(address.sin_port);
	
	sprintf(destination, "%s:%u", dot_address, port_number);
}

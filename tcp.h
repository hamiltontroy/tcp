int make_tcp_listener(unsigned short port_number);
int wait_for_connection(int listener);
int get_ip_address(int ipv4_socket, char *destination);

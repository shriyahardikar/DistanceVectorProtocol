#include <arpa/inet.h>
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include <unistd.h>
#include<stdlib.h>
#include <netdb.h>

/* Structure to store all the servers */
typedef struct Servers
{
	int id;
	char ip[20];
	int port;
}Servers;

/* Structure to store the neighbors */
typedef struct Neighbors
{
	int serv_id;
	int n_id;
	int cost;
	int hop[5];
	int total_cost;
}Neighbors;

/* Structure to store a packet and send it over the socket: */
typedef struct Packet
{
	unsigned short int num_update_fields;
	unsigned short int server_port;
	struct in_addr server_ip;
	
	struct in_addr server_ip_1;
	unsigned short int server_id_1;
	unsigned short int server_port_1;
	unsigned short int cost_1;
	
	struct in_addr server_ip_2;
	unsigned short int server_id_2;
	unsigned short int server_port_2;
	unsigned short int cost_2;
		
	struct in_addr server_ip_3;
	unsigned short int server_id_3;
	unsigned short int server_port_3;
	unsigned short int cost_3;
	
	struct in_addr server_ip_4;
	unsigned short int server_id_4;
	unsigned short int server_port_4;
	unsigned short int cost_4;
	
	struct in_addr server_ip_5;
	unsigned short int server_id_5;
	unsigned short int server_port_5;
	unsigned short int cost_5;
	
}Packet;

Servers servers[10];
Neighbors neighbors[10];

int num_serv, num_neighbors, output_port = 7000, listening_port;
int num_packets, my_id;

char my_ip[256];

void send_packet()
{
	char ip_addr[256];
	int loop, loop2;
	struct sockaddr_in sa;
	struct in_addr data;
	Packet packet;
	
	struct sockaddr_in my_address2, server_addr;
	char server[256];
	int port;
	socklen_t addr_length= sizeof(server_addr);
	int socket_fd2;
	
	/* Form all the fields of the packet and sent to all neighbors */
	
	packet.num_update_fields = 17;
	inet_pton(AF_INET, my_ip, &(sa.sin_addr));
	packet.server_ip = sa.sin_addr;
	
	data = sa.sin_addr;
	inet_ntop(AF_INET, &(data), ip_addr, 256);
	
	packet.server_ip_1 = sa.sin_addr;
	packet.server_port = (short int) listening_port;
	
	for(loop=0; loop<num_serv; loop++)
	{
		if(neighbors[0].n_id==servers[loop].id)
		{
			inet_pton(AF_INET, servers[loop].ip, &(sa.sin_addr));
			packet.server_ip_1 = sa.sin_addr;
			packet.server_id_1 = (short int) servers[loop].id;
			packet.cost_1 = (short int) neighbors[0].cost;
			packet.server_port_1 = (short int) servers[loop].port;
			
			data = sa.sin_addr;
			inet_ntop(AF_INET, &(data), ip_addr, 256);
			break;
		}
	}
	
	for(loop=0; loop<num_serv; loop++)
	{
		if(neighbors[1].n_id==servers[loop].id)
		{
			inet_pton(AF_INET, servers[loop].ip, &(sa.sin_addr));
			packet.server_ip_2 = sa.sin_addr;
			packet.server_id_2 = (short int) servers[loop].id;
			packet.cost_2 = (short int) neighbors[1].cost;
			packet.server_port_2 = (short int) servers[loop].port;
			
			data = sa.sin_addr;
			inet_ntop(AF_INET, &(data), ip_addr, 256);
			break;
		}
	}
	
	for(loop=0; loop<num_serv; loop++)
	{
		if(neighbors[2].n_id==servers[loop].id)
		{
			inet_pton(AF_INET, servers[loop].ip, &(sa.sin_addr));
			packet.server_ip_3 = sa.sin_addr;
			packet.server_id_3 = (short int) servers[loop].id;
			packet.cost_3 = (short int) neighbors[2].cost;
			packet.server_port_3 = (short int) servers[loop].port;
			
			data = sa.sin_addr;
			inet_ntop(AF_INET, &(data), ip_addr, 256);
			break;
		}
	}
	
	for(loop=0; loop<num_serv; loop++)
	{
		if(neighbors[3].n_id==servers[loop].id)
		{
			inet_pton(AF_INET, servers[loop].ip, &(sa.sin_addr));
			packet.server_ip_4 = sa.sin_addr;
			packet.server_id_4 = (short int) servers[loop].id;
			packet.cost_4 = (short int) neighbors[3].cost;
			packet.server_port_4 = (short int) servers[loop].port;
			
			data = sa.sin_addr;
			inet_ntop(AF_INET, &(data), ip_addr, 256);
			break;
		}
	}
	
	for(loop=0; loop<num_serv; loop++)
	{
		if(neighbors[4].n_id==servers[loop].id)
		{
			inet_pton(AF_INET, servers[loop].ip, &(sa.sin_addr));
			packet.server_ip_5 = sa.sin_addr;
			packet.server_id_5 = (short int) servers[loop].id;
			packet.cost_5 = (short int) neighbors[4].cost;
			packet.server_port_5 = (short int) servers[loop].port;
			
			data = sa.sin_addr;
			inet_ntop(AF_INET, &(data), ip_addr, 256);
			break;
		}
	}
	
	/* Sending the packet to all neighbors: */
	
	for(loop2=0; loop2<num_neighbors, neighbors[loop2].cost!=9999, neighbors[loop2].cost!=0; loop2++)
	{
		for(loop=0; loop<num_serv; loop++)
		{
			if(neighbors[loop2].n_id==servers[loop].id) /*get ip and port of neighbor from its id*/
			{
				port = servers[loop].port;
				strcpy(server,servers[loop].ip);
			}
		}
		printf("\nSENDING ROUTER UPDATE TO SERVER %d",neighbors[loop2].n_id);
		if( (socket_fd2=socket(AF_INET,SOCK_DGRAM,0)) <0)
		{		
			perror("Error creating a socket!");
			return;
		}
		memset((char *)&my_address2,0,sizeof(my_address2));
		my_address2.sin_family = AF_INET;
		my_address2.sin_addr.s_addr = htonl(INADDR_ANY);
		my_address2.sin_port= htons(output_port);
		
		if(bind(socket_fd2,(struct sockaddr *)&my_address2, sizeof(my_address2)) < 0)
		{
			perror("\nError Binding!");
			return;
		}
		memset((char *)&server_addr,0,sizeof(server_addr) );
		server_addr.sin_family= AF_INET;
		server_addr.sin_port = htons(port);
		if(inet_aton(server,&server_addr.sin_addr)==0 )
		{
			printf("\n inet_aton() failed!");
			exit(1);
		}
		if(sendto(socket_fd2,&packet,sizeof(struct Packet),0,(struct sockaddr *)&server_addr,addr_length)==-1)
		{
			perror("\nSending Failed!!");
			return;
		}
		close(socket_fd2);
	}
}

/* Displaying all the servers and routing table */
void display()
{
	int loop;
	printf("\nServers are: ");
	printf("\nID\tIP\t\tPort");
	for(loop=0; loop<num_serv; loop++)
	{
		printf("\n%d\t%s\t%d",servers[loop].id, servers[loop].ip, servers[loop].port);
	}
	
	printf("\nRouting table is: ");
	printf("\nServer ID\tNeighbor ID\tTotal Cost");
	for(loop=0; loop<num_neighbors; loop++)
	{
		printf("\n%d\t\t%d\t\t%d",neighbors[loop].serv_id, neighbors[loop].n_id, neighbors[loop].total_cost);
	}
}

/* Updating the routing table after receiving packet*/
void receive_packet(Packet packet)
{
	int loop, sender_id, sender_cost, new_cost;
	char sender_ip[256];
	
	num_packets++;
	
	inet_ntop(AF_INET, &(packet.server_ip), sender_ip, 256);
	for(loop=0; loop<num_serv; loop++)
	{
		if(strcmp(sender_ip,servers[loop].ip)==0)
		{
			sender_id = servers[loop].id;
			break;
		}
	}
	for(loop=0; loop<num_neighbors; loop++)
	{
		if(neighbors[loop].n_id == sender_id)
		{
			if(packet.server_id_1 == my_id)
			{
				neighbors[loop].cost = packet.cost_1;
				neighbors[loop].total_cost = packet.cost_1;
			}
			else if(packet.server_id_2 == my_id)
			{
				neighbors[loop].cost = packet.cost_2;
				neighbors[loop].total_cost = packet.cost_2;
			}
			else if(packet.server_id_3 == my_id)
			{
				neighbors[loop].cost = packet.cost_3;
				neighbors[loop].total_cost = packet.cost_3;
			}
			else if(packet.server_id_4 == my_id)
			{
				neighbors[loop].cost = packet.cost_4;
				neighbors[loop].total_cost = packet.cost_4;
			}
			else if(packet.server_id_5 == my_id)
			{
				neighbors[loop].cost = packet.cost_5;
				neighbors[loop].total_cost = packet.cost_5;
			}
			
			sender_cost = neighbors[loop].cost;
		}
	}
	if(packet.server_id_1!=my_id)
	{
		new_cost = packet.cost_1 + sender_cost;
		for(loop=0; loop<num_neighbors; loop++)
		{
			if(neighbors[loop].n_id==packet.server_id_1)
			{
				if(neighbors[loop].total_cost>new_cost)
				{
					neighbors[loop].total_cost=new_cost;
				}
			}
		}
	}
	
	else if(packet.server_id_2!=my_id)
	{
		new_cost = packet.cost_1 + sender_cost;
		for(loop=0; loop<num_neighbors; loop++)
		{
			if(neighbors[loop].n_id==packet.server_id_2)
			{
				if(neighbors[loop].total_cost>new_cost)
				{
					neighbors[loop].total_cost=new_cost;
				}
			}
		}
	}
	
	else if(packet.server_id_3!=my_id)
	{
		new_cost = packet.cost_1 + sender_cost;
		for(loop=0; loop<num_neighbors; loop++)
		{
			if(neighbors[loop].n_id==packet.server_id_3)
			{
				if(neighbors[loop].total_cost>new_cost)
				{
					neighbors[loop].total_cost=new_cost;
				}
			}
		}
	}
	
	else if(packet.server_id_4!=my_id)
	{
		new_cost = packet.cost_1 + sender_cost;
		for(loop=0; loop<num_neighbors; loop++)
		{
			if(neighbors[loop].n_id==packet.server_id_4)
			{
				if(neighbors[loop].total_cost>new_cost)
				{
					neighbors[loop].total_cost=new_cost;
				}
			}
		}
	}
	
	else if(packet.server_id_5!=my_id)
	{
		new_cost = packet.cost_1 + sender_cost;
		for(loop=0; loop<num_neighbors; loop++)
		{
			if(neighbors[loop].n_id==packet.server_id_5)
			{
				if(neighbors[loop].total_cost>new_cost)
				{
					neighbors[loop].total_cost=new_cost;
				}
			}
		}
	}
	printf("\nRECEIVED A MESSAGE FROM SERVER %d",sender_id);
}

/* Handling the commands entered by user */
void user_input(char command[256])
{
	char temp[256];
	char message[256];
	char* p;
	char* chunks[10];
	int num_chunks,loop, loop2;
	int flag=0, id1, id2;
	
	strcpy(temp,command);
	for(loop=0; loop<10; loop++)
	{
		chunks[loop] = 0;
	}
	num_chunks=0;
	chunks[num_chunks++] = temp;

	p = temp;
	while(*p)
	{
		if(*p == ' ')
		{
			*p = 0;
			chunks[num_chunks++] = p + 1;
		}
		p++;
	}
	
	/*Disable command*/
	if((strcmp(chunks[0],"-")==0) && (strcmp("disable",chunks[1])==0))
	{
		flag = 0;
		id1 = atoi(chunks[2]);
		for(loop=0; loop<num_neighbors; loop++)
		{
			if(neighbors[loop].n_id == id1 && neighbors[loop].cost!=9999 && neighbors[loop].cost!=0)
			{
				/* Infinity value to disabled router */
				neighbors[loop].cost=9999;
				neighbors[loop].total_cost=9999;
				
				printf("\nDISABLE SUCCESSFUL!");
				flag = 1;
				break;
			}
		}
		if(flag==0)
			printf("\nDISABLE FAILED! EDGE NOT FOUND");
	}
	
	/*Crash command:*/
	else if((strcmp(chunks[0],"-")==0) && (strstr(chunks[1],"crash")!=0))
	{
		for(loop=0; loop<num_neighbors, neighbors[loop].cost!=0; loop++)
		{
			/* Infinity value to all routers*/
			neighbors[loop].cost=9999;
			neighbors[loop].total_cost=9999;
		}
		printf("\nCRASH SUCCESSFUL!");
	}
		
	/*Packets command:*/
	else if((strcmp(chunks[0],"-")==0) && (strstr(chunks[1],"packets")!=0))
	{
		printf("\nPackets received are: %d",num_packets);
		printf("\nPACKETS SUCCESSFUL!");
		num_packets=0;
	}
	
	/*step command*/
	else if((strcmp(chunks[0],"-")==0) && (strstr(chunks[1],"step")!=0))
	{
		send_packet();
		printf("\nSTEP SUCCESSFUL");
	}
	
	/*Update command*/
	/* Updates own routing table only */
	else if(strcmp(chunks[0],"-")==0 && (strcmp(chunks[1],"update")==0))
	{
		flag = 0;
		if(atoi(chunks[2]) == my_id)
		{
			id1 = atoi(chunks[2]);
			id2 = atoi(chunks[3]);
		}
		else
		{
			id2 = atoi(chunks[2]);
			id1 = atoi(chunks[3]);
		}
		for(loop=0; loop<num_neighbors; loop++)
		{
			if(neighbors[loop].serv_id==id1 && neighbors[loop].n_id==id2)
			{
				if(strstr(chunks[4],"inf")!=0)
				{
					neighbors[loop].cost = 9999;
					neighbors[loop].total_cost = 9999;
				}
				else
				{
					neighbors[loop].cost = atoi(chunks[4]);
					neighbors[loop].total_cost = atoi(chunks[4]);
				}
				printf("\nUPDATE SUCCESSFUL!");
				flag = 1;
			}
		}
		if(flag==0)
		{
			printf("\nUPDATE FAILURE!");
		}
	}
	else if(strcmp(chunks[0],"-")==0 && (strstr(chunks[1],"display")!=0))
	{
		display();
		printf("\nDISPLAY SUCCESSFUL");
	}
	else
	{
		printf("\nInvalid command! Enter again:");
	}
}

int main(int argc, char **argv)
{
	int socket_fd, loop, loop2;
	struct sockaddr_in my_address, caddr;
	socklen_t addr_length = sizeof(caddr);
	int rcv_message;
	int flag=0;
	char command[256], temp[256];
	char message[256];
	int time_interval;
	Packet packet;
	
	char *line;
	size_t size = 0;
	ssize_t read;
	char* p;
	char* chunks[10];
	int num_chunks;
	FILE *file_pointer;
		
	fd_set rset, allset;
	int maxfd, selected_sock;
	struct timeval timeout;
	
	num_packets = 0;
		
	/* Asks to provide topology file */
	while(strstr(command,"- server -t")==0)
	{
		printf("\nThe server is not on! Enter the topology file: ");
		bzero(command,255);
		fgets(command,255,stdin);
	}
	strcpy(temp,command);
	for(loop=0; loop<10; loop++)
	{
		chunks[loop] = 0;
	}
	num_chunks=0;
	chunks[num_chunks++] = temp;

	/* Reads topology file command */
	p = temp;
	while(*p)
	{
		if(*p == ' ')
		{
			*p = 0;
			chunks[num_chunks++] = p + 1;
		}
		p++;
	}
	
	/* Reads topology file and fills all the tables */
	file_pointer = fopen(chunks[3],"r");
	printf("\nConnected to topology file!");
	
	time_interval = atoi(chunks[5]);
	
	read = getline(&line, &size, file_pointer);
	num_serv = atoi(line);
	
	read = getline(&line, &size, file_pointer);
	num_neighbors = atoi(line);
	
	for(loop2=0; loop2<num_serv; loop2++)
	{
		read = getline(&line, &size, file_pointer);
		strcpy(temp,line);
		
		for(loop=0; loop<10; loop++)
		{
			chunks[loop] = 0;
		}
		num_chunks=0;
		chunks[num_chunks++] = temp;

		p = temp;
		while(*p)
		{
			if(*p == ' ')
			{
				*p = 0;
				chunks[num_chunks++] = p + 1;
			}
			p++;
		}
		servers[loop2].id = atoi(chunks[0]);
		strcpy(servers[loop2].ip,chunks[1]);
		servers[loop2].port = atoi(chunks[2]);
	}
	
	for(loop2=0; loop2<num_neighbors; loop2++)
	{
		read = getline(&line, &size, file_pointer);
		strcpy(temp,line);
		for(loop=0; loop<10; loop++)
		{
			chunks[loop] = 0;
		}
		num_chunks=0;
		chunks[num_chunks++] = temp;

		p = temp;
		while(*p)
		{
			if(*p == ' ')
			{
				*p = 0;
				chunks[num_chunks++] = p + 1;
			}
			p++;
		}
		
		neighbors[loop2].serv_id = atoi(chunks[0]);
		neighbors[loop2].n_id = atoi(chunks[1]);
		neighbors[loop2].cost = atoi(chunks[2]);
		neighbors[loop2].total_cost = atoi(chunks[2]);
	}
	my_id = neighbors[0].serv_id;
	printf("\n\nGot my id: %d\n",my_id);
	
	for(loop2=0; loop2<num_serv; loop2++)
	{
		if(servers[loop2].id == my_id)
		{
			listening_port = servers[loop2].port;
			strcpy(my_ip,servers[loop2].ip);
			break;
		}
	}
	fclose(file_pointer);
	
	printf("\n\nGot listening port: %d\n",listening_port);
	
	for(loop=0; loop<num_serv; loop++)
	{
		flag=0;
		for(loop2=0; loop2<num_neighbors; loop2++)
		{
			if(servers[loop].id==neighbors[loop2].n_id)
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			neighbors[num_neighbors].serv_id = my_id;
			neighbors[num_neighbors].n_id = servers[loop].id;
			neighbors[num_neighbors].cost = 9999;
			neighbors[num_neighbors].total_cost = 9999;
			if(servers[loop].id == my_id)
			{
				neighbors[num_neighbors].cost = 0;
				neighbors[num_neighbors].total_cost = 0;
			}
			num_neighbors++;
		}
	}
	display();

	/* Creating listening socket */
	if((socket_fd = socket(AF_INET,SOCK_DGRAM,0) )<0)
	{
		perror("Socket creation failed!!");
		return 0;
	}
	
	memset((char*)&my_address,0,sizeof(my_address));
	my_address.sin_family = AF_INET;
	my_address.sin_addr.s_addr = htonl(INADDR_ANY);
	my_address.sin_port = htons(listening_port);
	
	if((bind(socket_fd, (struct sockaddr *)&my_address, sizeof(my_address)))<0)
	{
		perror("\nSocket Bind Failed!!");
		return 0;
	}
	
	maxfd = socket_fd;  
	
	FD_ZERO(&allset);
	FD_SET(socket_fd, &allset);
	FD_SET(0, &allset);
	rset = allset;
	
	/* Adding listening socket and stdin into select API */
	while(1)
	{
		timeout.tv_sec = time_interval;
		timeout.tv_usec = 0; 
		
		printf("\nCommand> ");
		/* send_packet();  */
		
		FD_ZERO(&rset);
		rset = allset;	/*To reset the select socket*/
		selected_sock = select( (maxfd +1), &rset, NULL, NULL, &timeout); 
		
		/*If select returns an error:*/
		if(selected_sock<0) 
		{
			perror("Select API Failed!!");
			exit(0);
		}  
		
		/*If command received from the user command prompt:*/
		if (FD_ISSET(0, &rset))
		{
			bzero(command,255);
			fgets(command,255,stdin);
			user_input(command);
		}
			
		/*If message received from another server:*/
		if (FD_ISSET(socket_fd, &rset))
		{    
			rcv_message = recvfrom(socket_fd,&packet,sizeof(struct Packet),0,(struct sockaddr*)&caddr, &addr_length);
			if(rcv_message>0)
			{
				receive_packet(packet);
			}
			else
				printf("\nError while receiving!");
		}
	}
}

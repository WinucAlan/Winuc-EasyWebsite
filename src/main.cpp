#include <bits/stdc++.h>
#include <winsock2.h> 
#define PORT 8888
#define  BUFFER_SIZE 4196
using namespace std;
struct sockaddr_in client_addr;
SOCKET server_socket;
int client_addr_len;
char buf[BUFFER_SIZE+100];
SOCKET client_socket;
int IsTcpDataAvailable(SOCKET s, int timeout_ms)
{
	fd_set read_fds;
	struct timeval timeout;
	// 初始化fd_set，只关注目标套接字
	FD_ZERO(&read_fds);
	FD_SET(s, &read_fds);
	// 设置超时时间
	timeout.tv_sec = timeout_ms / 1000;
	timeout.tv_usec = (timeout_ms % 1000) * 1000;
	// 调用select，只检查读状态
	int ret = select(0, &read_fds, NULL, NULL, &timeout);
	if (ret == SOCKET_ERROR)
	{
		// 出错，打印错误码
		printf("select error: %d\n", WSAGetLastError());
		return -1;
	}
	else if (ret > 0) // 返回值>0表示有套接字就绪，检查目标套接字是否在就绪集合中
		if (FD_ISSET(s, &read_fds))
			return 1; // 有数据可读
	// 超时，无数据可读
	return 0;
}

int main()
{
	WORD winsock_version = MAKEWORD(2,2);
	WSADATA wsa_data;
	if (WSAStartup(winsock_version, &wsa_data) != 0)
	{
		printf("Failed to init socket dll!\n");
		return 1;
	}
	server_socket= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == INVALID_SOCKET)
	{
		printf("Failed to create server socket!\n");
		return 2;
	}
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(server_socket, (LPSOCKADDR)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		printf("Failed to bind port!\n");
		return 3;
	}
	if (listen(server_socket, 10))
	{
		printf("Failed to listen!\n");
		return 4;
	}
	client_addr_len = sizeof(client_addr);
	printf("Wait for connecting...\n");
	while(1)
	{
		client_socket = accept(server_socket, (SOCKADDR*)&client_addr, &client_addr_len);
		printf("[info]connect to new client: IP=%s\n" , inet_ntoa(client_addr.sin_addr));
		if (client_socket == INVALID_SOCKET)
		{
			printf("Failed to accept!\n");
			continue;
		}
		string childLabel;
		if(IsTcpDataAvailable(client_socket,1000))
		{
			memset(buf,0,sizeof(buf));
			recv(client_socket,buf,BUFFER_SIZE,0);
			printf("%s\n",buf);
			int startPos=string(buf).find("GET");
			if(startPos==string::npos)
			{
				printf("ERROR:Undefined request\n");
				send(client_socket,"HTTP/1.1 404 Not Found",sizeof("HTTP/1.1 404 Not Found"),0);
				closesocket(client_socket);
				continue;
			}
			for(int i=startPos+4;i<strlen(buf)&&buf[i]!=' ';i++) childLabel+=buf[i];
			if(childLabel=="/favicon.ico")
			{
				string html;
				ifstream fin("favicon.png",ios::binary);
				char c;
				while(fin.get(c)) html+=c;
				fin.close();
				string response="HTTP/1.1 200 OK\r\nContent-Type: image/apng; charset=UTF-8\r\nContent-Length: "+to_string(html.size())+"\r\n\r\n"+html; 
				send(client_socket,response.c_str(),response.size(),0);
				closesocket(client_socket);
				continue;
			}
		}
		//加载网页列表
		string fileName;
		bool flag=0;
		ifstream lists("list.txt");
		string child,type;
		while(lists>>child>>type>>fileName)
		{
			if(child==childLabel)
			{
				flag=1;
				break;
			}
		}
		lists.close();
		if(!flag)
		{
			printf("ERROR:Undefined child:%s\n",childLabel.c_str());
			send(client_socket,"HTTP/1.1 404 Not Found",sizeof("HTTP/1.1 404 Not Found"),0);
			closesocket(client_socket);
			continue;
		}
		//加载HTML源码 
		string html;
		ifstream fin(fileName);
		char c;
		while(fin.get(c)) html+=c;
		fin.close();
		string response="HTTP/1.1 200 OK\r\nContent-Type: "+type+"; charset=UTF-8\r\nContent-Length: "+to_string(html.size())+"\r\n\r\n"+html; 
		send(client_socket,response.c_str(),response.size(),0);
		Sleep(100);
		closesocket(client_socket);
	}
	closesocket(server_socket);
	WSACleanup();
	return 0;
}

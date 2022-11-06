#include<stdio.h>
#include<sys/types.h>
//  #include <sys/socket.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>


int main(int argc,char *argv[])
{
	if (argc != 3)
	{
		printf("argv error");
		return -1;
	}

	//创建套接字
		int sockfd = socket(AF_INET,SOCK_STREAM,0);
		if (sockfd == -1)
		{
			perror("socket error\n");
			return -1;
		}

		//bind 绑定
		struct sockaddr_in sAddr;
		memset(&sAddr,0,sizeof(sAddr));
		// 协议 IP 端口号
		sAddr.sin_family = AF_INET;
		sAddr.sin_addr.s_addr= inet_network(argv[1]);
		sAddr.sin_port = htons(atoi(argv[2]));
		int r = bind( sockfd,( struct sockaddr*) &sAddr,sizeof(sAddr));
		if (r == -1)
		{
			perror("bind socket error");
			close(socket);
			return -1;
		}


		//3.listen 开启监听操作
		listen(sockfd,10);
		struct sockaddr_in cAddr;
		socklen_t addrlen=sizeof(cAddr);
		while (1)
		{
			int confd=accept(sockfd, (struct sockaddr*) &cAddr, &addrlen);
			if (confd > 0)
				printf("accept success\n");
			printf("client IP=%s ,client port%d\n", inet_ntoa(cAddr.sin_addr),
				ntohs(cAddr.sin_port));

			//进行通信
			char buf[256] = {0};
			r=read(confd,buf,256);
			if (r > 0)
			{
				printf("r=%d,message :%s", r, buf);
			}
			write(confd, "goodbye", 20);
			close(confd);
		}

		close(sockfd);


return 0;
}


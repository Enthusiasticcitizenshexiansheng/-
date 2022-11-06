#include<stdio.h>
#include<sys/types.h>
 //  #include <sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("cuowu");
		return -1;
	}




	//1����tcp
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd == -1)
	{
		perror("socket error\n");
		return -1;
	}


	//2���ӷ�����
	//  ��׼������ṹ��
	struct sockaddr_in sAddr;  //����
	//���õ�ַ�ṹ��
	memset(&sAddr, 0, sizeof(sAddr));
	sAddr.sin_family = AF_INET;  //Э����
	sAddr.sin_port = htons(stoi(argv[2]));  //�˿ں�
      //����ip
	inet_aton(argv[1], &(sAddr.sin_addr));
	
	
	// sockfd ����ָ�� 
	int r=  connect( sockfd, (struct sockaddr*)&sAddr, sizeof(sAddr));
	if (r == -1)
	{
		perror("connet error");
		close(sockfd);
		return -1;
	}
	printf("connet �ɹ�");


	//3������
		char buf[256] = {"hello server\n"};
		write(sockfd, buf, 15);

		r = recv(sockfd,buf,256,0);
		if (r > 0)
		{
			printf("%s ",buf);
		}


		//4.�ر�
		close(sockfd);
		return 0;
}
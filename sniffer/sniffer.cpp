#include "stdafx.h"
void recvIp(SOCKET s);

int main()
{
	WSADATA     wsadata;     // ������������� WinSock.
	SOCKET      s;           // ��������� �����.
	SOCKADDR_IN sa;          // ����� �����
	HOSTENT*    phe;         // ���������� � �����.
	char        name[128];   // ��� ����� (����������).
	unsigned long flag = 1;  // ���� PROMISC ���/����.

	if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsadata)))
	{
		printf("\nInvalid WSAStartup=%d\n",WSAGetLastError());
		system("pause");
		return -1;
	}

	s = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
	if (INVALID_SOCKET == s)
	{
		printf("\nInvalid Socket=%d\n", WSAGetLastError());
		WSACleanup();
		system("pause");
		return -1;
	}
	
	gethostname(name, sizeof(name));
	phe = gethostbyname(name);
	ZeroMemory(&sa, sizeof(sa));

	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = ((struct in_addr *)phe->h_addr_list[0])->s_addr;
	if (bind(s, (SOCKADDR *)&sa, sizeof(SOCKADDR)))
	{
		printf("\nInvalid Bind=%d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		system("pause");
		return -1;
	}

	//������������ ��� �����
	ioctlsocket(s, 0x98000001, &flag);

	//����������� ���� ������ IP-�������. �� ��� ���, ���� �� ����� ������ ����� ������.
	recvIp(s);

	closesocket(s);
	WSACleanup();
	system("pause");
	return 0;
}

void recvIp(SOCKET s)
{
	// ����� ��� ������ ������
	char Buffer[1024 * 64];
	int count;
	bool codeid[4] = {1, 1, 1, 1};
	while (1)
	{
		count = recv(s, Buffer, sizeof(Buffer), 0);
		if (_kbhit())
		{
			int key = _getch();
			switch (key)
			{
			case 49: 
				codeid[0] = !codeid[0];
				break;
			case 50:
				codeid[1] = !codeid[1];
				break;
			case 51:
				codeid[2] = !codeid[2];
				break;
			case 27:
				return;
				break;
			default:
				codeid[3] = !codeid[3];
				break;
			}
		}
		if (!codeid[3])
			continue;
		// ��������� IP-������
		if (count >= sizeof(IPHeader))
		{
			IPHeader* IpHdr = (IPHeader *)Buffer;
			UDPHeader* UdpHdr = (UDPHeader *)(Buffer + IpHdr->h_length * 4);
			TCPHeader* TcpHdr = (TCPHeader *)(Buffer + IpHdr->h_length * 4);
			ICMPHeader* IcmpHdr = (ICMPHeader *)(Buffer + IpHdr->h_length * 4);
			
			// ���� ��� UDP-�����, ������� UDP-����������.
			if (codeid[0] && IpHdr->proto == 17)
			{
				printIp(IpHdr);
				printUdp(UdpHdr, IpHdr);
			}

			// ���� ��� TCP-�����, ������� TCP-����������.
			if (codeid[1] && IpHdr->proto == 6)
			{
				printIp(IpHdr);
				printTcp(TcpHdr, IpHdr);
			}
			
			// ���� ��� ICMP-�����, ������� ICMP-����������.
			if (codeid[2] && IpHdr->proto == 1)
			{
				printIp(IpHdr);
				printIcmp(IcmpHdr, IpHdr);
			}
		}
	}
}
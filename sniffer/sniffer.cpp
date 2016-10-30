#include "stdafx.h"
void recvIp(SOCKET s);

int main()
{
	WSADATA     wsadata;     // Инициализация WinSock.
	SOCKET      s;           // Слушающий сокет.
	SOCKADDR_IN sa;          // Адрес хоста
	HOSTENT*    phe;         // Информация о хосте.
	char        name[128];   // Имя хоста (компьютера).
	unsigned long flag = 1;  // Флаг PROMISC Вкл/выкл.

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

	//Прослушиваем все порты
	ioctlsocket(s, 0x98000001, &flag);

	//Бесконечный цикл приема IP-пакетов. До тех пор, пока не будет нажата любая кнопка.
	recvIp(s);

	closesocket(s);
	WSACleanup();
	system("pause");
	return 0;
}

void recvIp(SOCKET s)
{
	// Буфер для приема данных
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
		// Обработка IP-пакета
		if (count >= sizeof(IPHeader))
		{
			IPHeader* IpHdr = (IPHeader *)Buffer;
			UDPHeader* UdpHdr = (UDPHeader *)(Buffer + IpHdr->h_length * 4);
			TCPHeader* TcpHdr = (TCPHeader *)(Buffer + IpHdr->h_length * 4);
			ICMPHeader* IcmpHdr = (ICMPHeader *)(Buffer + IpHdr->h_length * 4);
			
			// Если это UDP-пакет, выводим UDP-информацию.
			if (codeid[0] && IpHdr->proto == 17)
			{
				printIp(IpHdr);
				printUdp(UdpHdr, IpHdr);
			}

			// Если это TCP-пакет, выводим TCP-информацию.
			if (codeid[1] && IpHdr->proto == 6)
			{
				printIp(IpHdr);
				printTcp(TcpHdr, IpHdr);
			}
			
			// Если это ICMP-пакет, выводим ICMP-информацию.
			if (codeid[2] && IpHdr->proto == 1)
			{
				printIp(IpHdr);
				printIcmp(IcmpHdr, IpHdr);
			}
		}
	}
}
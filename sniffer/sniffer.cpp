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
	if (ioctlsocket(s, 0x98000001, &flag))
	{
		printf("\nInvalid Bind=%d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		system("pause");
		return -1;
	};

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
	int count = 0;

	// Фильтрация по типу пакета
	const int clength = 4;
	bool codeid[clength] = { 1, 1, 1, 1 };
	LPCWSTR print[clength] = { L"", L"", L"", L"" };
	LPCWSTR def[clength] = { L"UDP", L"TCP", L"ICMP", L"" };
	std::wstring title = L"";
	std::wstring space = L" ";

	while (1)
	{
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
			case 99:
				system("cls");
				break;
			case 27:
				return;
				break;
			case 32:
				codeid[3] = !codeid[3];
				break;
			default:
				break;
			}
			for (int i = 0; i < clength; i++)
			{
				if (codeid[i] == 1)
				{
					print[i] = def[i];
				}
				else
				{
					print[i] = L"";
					if (i == clength - 1)
						print[i] = L"pause";
				}
				title += print[i] + space;
			}
			SetConsoleTitleW(title.c_str());
			title = L"";
		}
		if (!codeid[3])
			continue;

		count = recv(s, Buffer, sizeof(Buffer), 0);
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
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
	if (ioctlsocket(s, 0x98000001, &flag))
	{
		printf("\nInvalid Bind=%d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		system("pause");
		return -1;
	};

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
	int count = 0;

	// ���������� �� ���� ������
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
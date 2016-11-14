#include "stdafx.h"
// ��������� ��������� IP-������
typedef struct IPHeader {
	unsigned char	h_length: 4; // ����� ���������
	unsigned char	version:  4; // ����� ������ ���������
	unsigned char   tos;         // ��� �������
	unsigned short  tlen;        // ����� ����� ������
	unsigned short  id;          // ������������� ������
	unsigned short  flags_fo;     // ����������� ����� � �������� ��������� 
	unsigned char   ttl;         // ����� ����� ������
	unsigned char   proto;       // �������� �������� ������
	unsigned short  crc;         // ����������� ����� ���������
	unsigned int    src_addr;    // IP-����� �����������
	unsigned int    dst_addr;    // IP-����� ����������
} IPHeader;
// ��������� ��������� UDP-������
typedef struct UDPHeader {
	unsigned short  src_port;  // ���� �����������
	unsigned short  dst_port;  // ���� ����������
	unsigned short  length;    // ����� ����������
	unsigned short  crc;       // ����������� ����� ���������
} UDPHeader;
// ��������� ��������� TCP-������
typedef struct TCPHeader
{
	unsigned short  src_port;  // ���� �����������
	unsigned short  dst_port;  // ���� ����������
	unsigned int    seq_n;     // ����� �������
	unsigned int    ack_n;     // ����� �������������
	unsigned char   reserve1: 4;  // ���������������
	unsigned char	offset  : 4;  // �������� ������ (����� ���������)
	unsigned char	fin : 1;   // ���������� ����������
	unsigned char   syn : 1;   // ������������� ������� ������������������
	unsigned char   rst : 1;   // ����� ����������, ������� ������
	unsigned char	psh : 1;   // �������� ������ �� ������
	unsigned char	ack : 1;   // ����� �������������
	unsigned char   urg : 1;   // ��������� ��������
	unsigned char   reserve2 : 2;  // ���������������
	unsigned short  win;       // ������ ����
	unsigned short  crc;       // ����������� ����� ���������
	unsigned short  padding;   // ���������� �� 20 ����
} TCPHeader;
// ��������� ��������� ICMP-������
typedef struct ICMPHeader
{
	unsigned char   type;		// ��� ICMP- ������
	unsigned char   code;		// ��� ICMP- ������ 
	unsigned short  crc;		// ����������� ����� 
	union {
		struct { unsigned charuc1, uc2, uc3, uc4; } s_uc;
		struct { unsigned shortus1, us2; } s_us;
		unsigned long s_ul;
	} s_icmp;                   // ������� �� ���� 
} ICMPHeader;

void printIp(IPHeader* IpHdr);
void printTcp(TCPHeader* TcpHdr, IPHeader* IpHdr);
void printUdp(UDPHeader* UdpHdr, IPHeader* IpHdr);
void printIcmp(ICMPHeader* IcmpHdr, IPHeader* IpHdr);
char *HostIp(unsigned long int in);
#include "stdafx.h"
// ��������� ��������� IP-������
typedef struct IPHeader {
	unsigned char	h_length: 4; // ����� ���������
	unsigned char	version:  4; // ����� ������ ���������
	unsigned char   tos;         // ��� �������
	unsigned short  tlen;        // ����� ����� ������
	unsigned short  id;          // ������������� ������
	unsigned short  flags_fo;    // ����������� ����� � �������� ���������
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
	unsigned char   offset;    // �������� ������ 
	unsigned char   flags;     // �����
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
	unsigned short  id;         // ������������� ������
	unsigned short  seq;        
} ICMPHeader;

void printIp(IPHeader* IpHdr);
void printTcp(TCPHeader* TcpHdr, IPHeader* IpHdr);
void printUdp(UDPHeader* UdpHdr, IPHeader* IpHdr);
void printIcmp(ICMPHeader* IcmpHdr, IPHeader* IpHdr);
char *HostIp(unsigned long int in);
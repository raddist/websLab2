#include "stdafx.h"
// Структура заголовка IP-пакета
typedef struct IPHeader {
	unsigned char	h_length: 4; // длина заголовка
	unsigned char	version:  4; // номер версии протокола
	unsigned char   tos;         // тип сервиса
	unsigned short  tlen;        // общая длина пакета
	unsigned short  id;          // идентификатор пакета
	unsigned short  flags_fo;    // управляющие флаги и смещение фрагмента
	unsigned char   ttl;         // время жизни пакета
	unsigned char   proto;       // протокол верхнего уровня
	unsigned short  crc;         // контрольная сумма заголовка
	unsigned int    src_addr;    // IP-адрес отправителя
	unsigned int    dst_addr;    // IP-адрес получателя
} IPHeader;
// Структура заголовка UDP-пакета
typedef struct UDPHeader {
	unsigned short  src_port;  // порт отправителя
	unsigned short  dst_port;  // порт получателя
	unsigned short  length;    // длина датаграммы
	unsigned short  crc;       // контрольная сумма заголовка
} UDPHeader;
// Структура заголовка TCP-пакета
typedef struct TCPHeader
{
	unsigned short  src_port;  // порт отправителя
	unsigned short  dst_port;  // порт получателя
	unsigned int    seq_n;     // номер очереди
	unsigned int    ack_n;     // номер подтверждения
	unsigned char   offset;    // смещение данных 
	unsigned char   flags;     // флаги
	unsigned short  win;       // размер окна
	unsigned short  crc;       // контрольная сумма заголовка
	unsigned short  padding;   // дополнение до 20 байт
} TCPHeader;
// Структура заголовка ICMP-пакета
typedef struct ICMPHeader
{
	unsigned char   type;		// тип ICMP- пакета
	unsigned char   code;		// код ICMP- пакета 
	unsigned short  crc;		// контрольная сумма 
	unsigned short  id;         // идентификатор пакета
	unsigned short  seq;        
} ICMPHeader;

void printIp(IPHeader* IpHdr);
void printTcp(TCPHeader* TcpHdr, IPHeader* IpHdr);
void printUdp(UDPHeader* UdpHdr, IPHeader* IpHdr);
void printIcmp(ICMPHeader* IcmpHdr, IPHeader* IpHdr);
char *HostIp(unsigned long int in);
#include "stdafx.h"
// —труктура заголовка IP-пакета
typedef struct IPHeader {
	unsigned char	h_length: 4; // длина заголовка
	unsigned char	version:  4; // номер версии протокола
	unsigned char   tos;         // тип сервиса
	unsigned short  tlen;        // обща€ длина пакета
	unsigned short  id;          // идентификатор пакета
	unsigned short  flags_fo;     // управл€ющие флаги и смещение фрагмента 
	unsigned char   ttl;         // врем€ жизни пакета
	unsigned char   proto;       // протокол верхнего уровн€
	unsigned short  crc;         // контрольна€ сумма заголовка
	unsigned int    src_addr;    // IP-адрес отправител€
	unsigned int    dst_addr;    // IP-адрес получател€
} IPHeader;
// —труктура заголовка UDP-пакета
typedef struct UDPHeader {
	unsigned short  src_port;  // порт отправител€
	unsigned short  dst_port;  // порт получател€
	unsigned short  length;    // длина датаграммы
	unsigned short  crc;       // контрольна€ сумма заголовка
} UDPHeader;
// —труктура заголовка TCP-пакета
typedef struct TCPHeader
{
	unsigned short  src_port;  // порт отправител€
	unsigned short  dst_port;  // порт получател€
	unsigned int    seq_n;     // номер очереди
	unsigned int    ack_n;     // номер подтверждени€
	unsigned char   reserve1: 4;  // зарезервировано
	unsigned char	offset  : 4;  // смещение данных (длина заголовка)
	unsigned char	fin : 1;   // завершение соединени€
	unsigned char   syn : 1;   // синхронизаци€ номеров последовательности
	unsigned char   rst : 1;   // обрыв соединени€, очистка буфера
	unsigned char	psh : 1;   // отправка данных из буфера
	unsigned char	ack : 1;   // номер подтверждени€
	unsigned char   urg : 1;   // указатель важности
	unsigned char   reserve2 : 2;  // зарезервировано
	unsigned short  win;       // размер окна
	unsigned short  crc;       // контрольна€ сумма заголовка
	unsigned short  padding;   // дополнение до 20 байт
} TCPHeader;
// —труктура заголовка ICMP-пакета
typedef struct ICMPHeader
{
	unsigned char   type;		// тип ICMP- пакета
	unsigned char   code;		// код ICMP- пакета 
	unsigned short  crc;		// контрольна€ сумма 
	union {
		struct { unsigned charuc1, uc2, uc3, uc4; } s_uc;
		struct { unsigned shortus1, us2; } s_us;
		unsigned long s_ul;
	} s_icmp;                   // зависит от типа 
} ICMPHeader;

void printIp(IPHeader* IpHdr);
void printTcp(TCPHeader* TcpHdr, IPHeader* IpHdr);
void printUdp(UDPHeader* UdpHdr, IPHeader* IpHdr);
void printIcmp(ICMPHeader* IcmpHdr, IPHeader* IpHdr);
char *HostIp(unsigned long int in);
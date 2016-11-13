#pragma once

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#define ICMP_ECHO		8
#define ICMP_ECHOREPLY	0

#pragma warning( disable : 4996 )

#define ICMP_MIN 8 // minimum 8 byte icmp packet (just header)

/* The IP header */
typedef struct iphdr {
	unsigned int h_len : 4;          // length of the header
	unsigned int version : 4;        // Version of IP
	unsigned char tos;             // Type of service
	unsigned short total_len;      // total length of the packet
	unsigned short ident;          // unique identifier
	unsigned short frag_and_flags; // flags
	unsigned char  ttl;
	unsigned char proto;           // protocol (TCP, UDP etc)
	unsigned short checksum;       // IP checksum

	unsigned int sourceIP;
	unsigned int destIP;

}IpHeader;

//
// ICMP header
//
typedef struct _ihdr {
	BYTE i_type;
	BYTE i_code; /* type sub code */
	USHORT i_cksum;
	USHORT i_id;
	USHORT i_seq;
	/* This is not the std header, but we reserve space for time */
	ULONG timestamp;
}IcmpHeader;

#define STATUS_FAILED 0xFFFF
#define DEF_PACKET_SIZE 32
#define MAX_PACKET 1024

#define xmalloc(s) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(s))
#define xfree(p)   HeapFree (GetProcessHeap(),0,(p))

void fill_icmp_data(char *, int, BYTE, BYTE);
USHORT checksum(USHORT *, int);
//void decode_resp(char *, int, struct sockaddr_in *);


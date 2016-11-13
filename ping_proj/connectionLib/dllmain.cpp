// dllmain.cpp: определяет точку входа для приложения DLL.
#include "stdafx.h"
#include "raw.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#pragma pack(4)


extern "C" __declspec(dllexport)
int sendPacket(int srcAddr, int dstAddr, int type, int code, int loops, double delay) 
{
	WSADATA wsaData;
	SOCKET sockRaw;
	struct sockaddr_in dest, from;
	struct hostent * hp;
	int bread, datasize;
	int fromlen = sizeof(from);
	int timeout = 1000;
	char *dest_ip;
	char *icmp_data;
	char *recvbuf;
	unsigned int addr = 0;
	USHORT seq_no = 0;

	int msDelay = (int)(delay * 1000);

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed: %d\n", GetLastError());
		ExitProcess(STATUS_FAILED);
	}

	sockRaw = WSASocket(AF_INET,
		SOCK_RAW,
		IPPROTO_ICMP,
		NULL, 0, 0);

	if (sockRaw == INVALID_SOCKET) {
		fprintf(stderr, "WSASocket() failed: %d\n", WSAGetLastError());
		ExitProcess(STATUS_FAILED);
	}
	bread = setsockopt(sockRaw, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout,
		sizeof(timeout));
	if (bread == SOCKET_ERROR) {
		fprintf(stderr, "failed to set recv timeout: %d\n", WSAGetLastError());
		ExitProcess(STATUS_FAILED);
	}
	timeout = 1000;
	bread = setsockopt(sockRaw, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout,
		sizeof(timeout));
	if (bread == SOCKET_ERROR) {
		fprintf(stderr, "failed to set send timeout: %d\n", WSAGetLastError());
		ExitProcess(STATUS_FAILED);
	}
	memset(&dest, 0, sizeof(dest));




	// make dst address
	addr = (unsigned int)dstAddr;;
	dest.sin_addr.s_addr = addr;
	dest.sin_family = AF_INET;
	dest_ip = inet_ntoa(dest.sin_addr);

	datasize = DEF_PACKET_SIZE;


	datasize += sizeof(IcmpHeader);

	icmp_data = (char*)malloc(MAX_PACKET);
	recvbuf = (char*)malloc(MAX_PACKET);

	if (!icmp_data) {
		fprintf(stderr, "HeapAlloc failed %d\n", GetLastError());
		ExitProcess(STATUS_FAILED);
	}


	memset(icmp_data, 0, MAX_PACKET);
	fill_icmp_data(icmp_data, datasize, (BYTE)type, (BYTE)code);

	for (int i = 0; i < loops; ++i)
	{
		int bwrote;
		
		//	prepare ICMP header
		((IcmpHeader*)icmp_data)->i_cksum = 0;
		((IcmpHeader*)icmp_data)->timestamp = GetTickCount();

		((IcmpHeader*)icmp_data)->i_seq = seq_no++;
		((IcmpHeader*)icmp_data)->i_cksum = checksum((USHORT*)icmp_data,
			datasize);

		bwrote = sendto(sockRaw, icmp_data, datasize, 0, (struct sockaddr*)&dest,
			sizeof(dest));
		if (bwrote == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAETIMEDOUT) {
				printf("timed out\n");
				continue;
			}
			fprintf(stderr, "sendto failed: %d\n", WSAGetLastError());
			ExitProcess(STATUS_FAILED);
		}
		Sleep(msDelay);
	}

	return  type;

}
/*
The response is an IP packet. We must decode the IP header to locate
the ICMP data
*/
/*void decode_resp(char *buf, int bytes, struct sockaddr_in *from) {

	IpHeader *iphdr;
	IcmpHeader *icmphdr;
	unsigned short iphdrlen;

	iphdr = (IpHeader *)buf;

	iphdrlen = iphdr->h_len * 4; // number of 32-bit words *4 = bytes

	if (bytes  < iphdrlen + ICMP_MIN) {
		printf("Too few bytes from %s\n", inet_ntoa(from->sin_addr));
	}

	icmphdr = (IcmpHeader*)(buf + iphdrlen);

	if (icmphdr->i_type != ICMP_ECHOREPLY) {
		fprintf(stderr, "non-echo type %d recvd\n", icmphdr->i_type);
		return;
	}
	if (icmphdr->i_id != (USHORT)GetCurrentProcessId()) {
		fprintf(stderr, "someone else's packet!\n");
		return;
	}
	printf("%d bytes from %s:", bytes, inet_ntoa(from->sin_addr));
	printf(" icmp_seq = %d. ", icmphdr->i_seq);
	printf(" time: %d ms ", GetTickCount() - icmphdr->timestamp);
	printf("\n");

}*/


USHORT checksum(USHORT *buffer, int size) {

	unsigned long cksum = 0;

	while (size >1) {
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}

	if (size) {
		cksum += *(UCHAR*)buffer;
	}

	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return (USHORT)(~cksum);
}
/*
Helper function to fill in various stuff in our ICMP request.
*/
void fill_icmp_data(char * icmp_data, int datasize, BYTE type, BYTE code) 
{
	IcmpHeader *icmp_hdr;
	char *datapart;

	icmp_hdr = (IcmpHeader*)icmp_data;

	icmp_hdr->i_type = type;//ICMP_ECHO;
	icmp_hdr->i_code = code;
	icmp_hdr->i_id = (USHORT)GetCurrentProcessId();
	icmp_hdr->i_cksum = 0;
	icmp_hdr->i_seq = 0;

	datapart = icmp_data + sizeof(IcmpHeader);
	//
	// Place some junk in the buffer.
	//
	memset(datapart, 'E', datasize - sizeof(IcmpHeader));
}
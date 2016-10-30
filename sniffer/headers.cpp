#include "stdafx.h"
void printIp(IPHeader* IpHdr)
{
	printf("\n\nIpHeader: version=%d h_length=%d tos=%d tlen=%d id=%d "
		"flags_fo=%d ttl=%d\nproto=%d crc=%d src_addr=%lx "
		"dst_addr=%lx\n",
		IpHdr->version,
		IpHdr->h_length,
		IpHdr->tos,
		ntohs(IpHdr->tlen),
		ntohs(IpHdr->id),
		ntohs(IpHdr->flags_fo),
		IpHdr->ttl,
		IpHdr->proto,
		ntohs(IpHdr->crc),
		HostIp(IpHdr->src_addr),
		HostIp(IpHdr->dst_addr));
}

void printTcp(TCPHeader* TcpHdr, IPHeader* IpHdr)
{
	printf("\nTCP: src_port=%d dst_port=%d seq_n=%lx "
		"ack_n=%lx offset=%d\n win=%d crc=%d "
		"padding=%d\n",
		ntohs(TcpHdr->src_port),
		ntohs(TcpHdr->dst_port),
		ntohl(TcpHdr->seq_n),
		ntohl(TcpHdr->ack_n),
		TcpHdr->offset,
		ntohs(TcpHdr->win),
		ntohs(TcpHdr->crc),
		ntohs(TcpHdr->padding));
	printf("Flags: %d\n", TcpHdr->flags);
	printf("src_addr:%s s_port:%d\n",
		HostIp(IpHdr->src_addr),
		ntohs(TcpHdr->src_port));
	printf("dst_addr:%s d_port:%d\n",
		HostIp(IpHdr->dst_addr),
		ntohs(TcpHdr->dst_port));
}

void printUdp(UDPHeader* UdpHdr, IPHeader* IpHdr)
{
	printf("\nUDP: src_port=%d dst_port=%d length=%d crc=%d\n",
		ntohs(UdpHdr->src_port), ntohs(UdpHdr->dst_port),
		ntohs(UdpHdr->length), ntohs(UdpHdr->crc));
	printf("src_addr:%s src_port:%d\n",
		HostIp(IpHdr->src_addr),
		ntohs(UdpHdr->src_port));
	printf("dst_addr:%s dst_port:%d\n",
		HostIp(IpHdr->dst_addr),
		ntohs(UdpHdr->dst_port));
}

void printIcmp(ICMPHeader* IcmpHdr, IPHeader* IpHdr)
{
	printf("\nICMP: type=%d code=%d crc=%d\n",
		IcmpHdr->type,
		IcmpHdr->code,
		ntohs(IcmpHdr->crc));
	printf("src_addr:%s\n",
		HostIp(IpHdr->src_addr));
	printf("dst_addr:%s\n",
		HostIp(IpHdr->dst_addr));
}

char *HostIp(unsigned long int in)
{
	static char szHostName[512] = "";
	struct in_addr iaddr;
	memset(&iaddr, 0, sizeof(iaddr));
	iaddr.s_addr = in;
	strcpy_s(szHostName, inet_ntoa(iaddr));
	return (szHostName);
}
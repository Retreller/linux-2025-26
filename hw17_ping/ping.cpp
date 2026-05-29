#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

uint16_t checksum(void *buf, int len) {
    uint16_t *ptr = (uint16_t *)buf;
    uint32_t sum = 0;
    while (len > 1) { sum += *ptr++; len -= 2; }
    if (len) sum += *(uint8_t *)ptr;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return ~sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <ip>\n";
        return 1;
    }

    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) { perror("socket"); return 1; }

    sockaddr_in dest;
    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &dest.sin_addr);

    icmphdr pkt;
    memset(&pkt, 0, sizeof(pkt));
    pkt.type = ICMP_ECHO;
    pkt.un.echo.id  = getpid();
    pkt.un.echo.sequence = 1;
    pkt.checksum = checksum(&pkt, sizeof(pkt));

    sendto(sock, &pkt, sizeof(pkt), 0, (sockaddr *)&dest, sizeof(dest));
    std::cout << "Sent ICMP Echo Request to " << argv[1] << "\n";

    char buf[1024];
    sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);
    int n = recvfrom(sock, buf, sizeof(buf), 0, (sockaddr *)&sender, &sender_len);
    if (n < 0) { perror("recvfrom"); return 1; }

    int ip_hdr_len = ((iphdr *)buf)->ihl * 4;
    icmphdr *reply = (icmphdr *)(buf + ip_hdr_len);

    if (reply->type == ICMP_ECHOREPLY)
        std::cout << "Received ICMP Echo Reply from " << argv[1] << "\n";
    else
        std::cout << "Received unexpected ICMP type: " << (int)reply->type << "\n";

    close(sock);
    return 0;
}

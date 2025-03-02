//
// Created by hvorostok on 02.03.2025.
//

#include "ServerTCP.h"

#ifdef _WIN32

ServerTCP::ServerTCP() {

}

ServerTCP::~ServerTCP()=default;

void ServerTCP::set_port(unsigned short port) {
    port = port;
}

unsigned short ServerTCP::get_port() {
    return port;
}

void ServerTCP::start() {
    WSAData wData;
	if (WSAStartup(MAKEWORD(2, 2), &wData) == 0)
	{
		printf("WSA Startup succes\n");
	}
	SOCKADDR_IN addr;
	int addrl = sizeof(addr);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	bind_socket(&addr);
	handle();
}

SOCKET bind_socket(SOCKADDR_IN* addr) {
    SOCKET this_s = socket(AF_INET, SOCK_STREAM, NULL);
	if (this_s == SOCKET_ERROR) {
		std::cout << "Socket not created" << endl;
	}

	if (bind(this_s, (struct sockaddr*)addr, sizeof(*addr)) != SOCKET_ERROR) {
		std::cout << "Socket succed binded" << std::endl;
	}

	if (listen(this_s, SOMAXCONN) != SOCKET_ERROR){
		printf("Start listenin at port%u\n", ntohs(addr.sin_port));
	}
    return this_s;
}

void ServerTCP::handle(SOCKET this_s) {
	while (true)
	{
		SOCKET acceptS;
		SOCKADDR_IN addr_c;
		int addrlen = sizeof(addr_c);
		if ((acceptS = accept(this_s, (struct sockaddr*)&addr_c, &addrlen)) != 0) {
			printf("send\n");
			printf("sended Client connected from 0  %u.%u.%u.%u:%u\n",
				(unsigned char)addr_c.sin_addr.S_un.S_un_b.s_b1,
				(unsigned char)addr_c.sin_addr.S_un.S_un_b.s_b2,
				(unsigned char)addr_c.sin_addr.S_un.S_un_b.s_b3,
				(unsigned char)addr_c.sin_addr.S_un.S_un_b.s_b4,
				ntohs(addr_c.sin_port));
		}
		Sleep(50);
	}
}

void ServerTCP::close() {
	closesocket(this_s);
	WSACleanup();
	cout << "Server was stoped. You can close app" << endl;
}

#else

void ServerTCP::set_port(unsigned short port) {
    port = port;
}

unsigned short ServerTCP::get_port() {
    return 0;
}

ServerTCP::ServerTCP() {

}

ServerTCP::~ServerTCP()=default;

void ServerTCP::start() {

}

void ServerTCP::close() {

}

#endif
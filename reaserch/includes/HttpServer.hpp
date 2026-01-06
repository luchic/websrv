#ifndef __HTTPSERVER_HPP
#define __HTTPSERVER_HPP

#include "IHttpServer.hpp"
#include <sys/epoll.h>

class HttpServer : IHttpServer
{
private:
	int _listenFd;
	int _epfd;

	void _setup();
	void _setNonBlocking(int fd);
	int _setupSocket();

public:
	HttpServer();
	HttpServer(const HttpServer& other);
	HttpServer operator=(const HttpServer& other);
	~HttpServer() override;

	void run() override;
};

#endif
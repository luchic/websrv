#include "HttpServer.hpp"
#include <fcntl.h>
#include <stdexcept>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string>
#define MAX_EVENTS 64

HttpServer::HttpServer() : IHttpServer()
{
	_setup();
}

HttpServer::~HttpServer()
{
	close(_listenFd);
	close(_epfd);
}

void HttpServer::_setNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1)
	{
		throw std::runtime_error("fcntl: bad flags");
	}

	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
	{
		throw std::runtime_error("fcntl error: try to setup nonblock");
	}
}

int HttpServer::_setupSocket()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		throw std::runtime_error("Error: can't create socket");
	}

	int opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0)
	{
		throw std::runtime_error("Error: can't setup socket option");
	}
	sockaddr_in adress;

	adress.sin_family = AF_INET;
	adress.sin_addr.s_addr = htonl(INADDR_ANY);
	adress.sin_port = htons(8088);

	if (bind(fd, reinterpret_cast<struct sockaddr*>(&adress), sizeof(adress)) < 0)
	{
		throw std::runtime_error("Error: can't bind socket");
	}

	if (listen(fd, SOMAXCONN) < 0)
	{
		throw std::runtime_error("Error: can't listen");
	}
	_setNonBlocking(fd);
	return fd;
}

void HttpServer::_setup()
{
	_listenFd = _setupSocket();

	_epfd = epoll_create1(0);
	if (_epfd < 0)
	{
		std::runtime_error("Error: can't create epoll opject");
	}
	
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = _listenFd;
	if (epoll_ctl(_epfd, EPOLL_CTL_ADD, _listenFd, &event) < 0)
	{
		std::runtime_error("Error: can't add fd to epoll (epoll_ctl)");
	}
}

void HttpServer::run()
{
	struct epoll_event events[MAX_EVENTS];

	while (true)
	{
		int n = epoll_wait(_epfd, events, MAX_EVENTS, -1);

		for (int i = 0; i < n; ++i)
		{
			int fd = events[i].data.fd;
			if (fd == _listenFd)
			{
				int clientFd = accept(_listenFd, nullptr, nullptr);
				_setNonBlocking(clientFd);

				struct epoll_event clientEvent;
				clientEvent.events = EPOLLIN | EPOLLHUP;
				clientEvent.data.fd = clientFd;

				epoll_ctl(_epfd, EPOLL_CTL_ADD, clientFd, &clientEvent);
			}
			else	
			{
				std::string requestBytes;
				while (true)
				{
					char buf[4096];
					ssize_t n = ::recv(fd, buf, sizeof(buf), 0);
					if (n > 0)
					{
						requestBytes.append(buf, buf + n);
					}
					else
					{
						break; // client closed
					}
				}
				std::cout << "----- RAW REQUEST (" << requestBytes.size() << " bytes) -----\n";
				std::cout.write(requestBytes.data(), static_cast<std::streamsize>(requestBytes.size()));
				std::cout << "\n----- END REQUEST -----\n";

				// Send a minimal response so the browser finishes.
				std::string body = "<!DOCTYPE html><html><head><title>Page Title</title></head><body><h1>This is a Heading</h1><p>This is a paragraph.</p></body></html>";
				std::string resp =
					"HTTP/1.1 200 OK\r\n"
					"Content-Type: text/html; charset=utf-8\r\n"
					"Content-Length: " + std::to_string(body.size()) + "\r\n"
					"Connection: close\r\n"
					"\r\n" + body;

				(void)::send(fd, resp.data(), resp.size(), 0);
	
				close(fd);
				epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, NULL);
			}
		}
	}	
}


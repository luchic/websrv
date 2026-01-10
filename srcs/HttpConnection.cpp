#include "HttpConnection.hpp"
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string>

HttpConnection::HttpConnection() :
	_fd(-1),
	_state(HttpConnection::NEW),
	_buffer("")
{
}

HttpConnection::HttpConnection(int fd) :
	_fd(fd),
	_state(HttpConnection::NEW),
	_buffer("")
{
}

HttpConnection::~HttpConnection()
{}

HttpConnection::State HttpConnection::_reciveMessage()
{
	std::string buffer;
	while (true)
	{
		char buf[4096];
		ssize_t n = ::recv(_fd, buf, sizeof(buf), 0);
		if (n > 0)
		{
			buffer.append(buf, buf + n);
			continue;
		}
		else if (n == 0)
		{
			break;
		}
		if ((errno == EAGAIN || errno == EWOULDBLOCK))
		{
			std::cout << "fd: " << _fd << " got EAGAIN or EWOULDBLOCK" << std::endl;
			_buffer += buffer;
			if (_buffer.find("\r\n\r\n") != std::string::npos)
				return HttpConnection::HANDLED;
			return HttpConnection::WAITING;
		}
		return HttpConnection::ERROR;
	}
	_buffer += buffer;
	if (_buffer.find("\r\n\r\n") != std::string::npos)
		return HttpConnection::HANDLED;
	std::cout << "fd: " << _fd << " not full message" << std::endl;
	return HttpConnection::WAITING;
}

void HttpConnection::handleRequest()
{
	_state = _reciveMessage();

	if (_state == HttpConnection::HANDLED)
	{
		std::string body = "<!DOCTYPE html><html><head><title>Page Title</title></head><body><h1>This is a Heading</h1><p>This is a paragraph.</p></body></html>";
		std::string resp =
			"HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html; charset=utf-8\r\n"
			"Content-Length: " + std::to_string(body.size()) + "\r\n"
			"Connection: close\r\n"
			"\r\n" + body;
		(void)::send(_fd, resp.data(), resp.size(), 0);
	}
	if (_state == HttpConnection::ERROR)
	{
		std::string body = "<!DOCTYPE html><html><head><title>error</title></head><body><h1>502 Gateway</h1></body></html>";
		std::string resp =
			"HTTP/1.1 502 Bad Gateway\r\n"
			"Content-Type: text/html; charset=utf-8\r\n"
			"Content-Length: " + std::to_string(body.size()) + "\r\n"
			"Connection: close\r\n"
			"\r\n" + body;
		(void)::send(_fd, resp.data(), resp.size(), 0);
	}
}

bool HttpConnection::isError()
{
	return _state == HttpConnection::ERROR;
}

bool HttpConnection::isHandled()
{
	return _state == HttpConnection::HANDLED;
}
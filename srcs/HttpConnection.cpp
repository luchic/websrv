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
	_buffer("")
{
}

HttpConnection::HttpConnection(int fd) :
	_fd(fd),
	_buffer("")
{
}

HttpConnection::~HttpConnection()
{}

bool HttpConnection::_reciveMessage()
{
	while (true)
	{
		char buf[4096];
		ssize_t n = ::recv(_fd, buf, sizeof(buf), 0);
		if (n > 0)
		{
			_buffer.append(buf, buf + n);
			continue;
		}
		else if (n == 0)
		{
			break;
		}
		if ((errno == EAGAIN || errno == EWOULDBLOCK))
		{
			_state = HttpConnection::WAITING;
			return false;
		}
		_state = HttpConnection::ERROR;
		return false;
	}
	_state = HttpConnection::HANDLED;
	return true;
}

bool HttpConnection::readIntoBuffer()
{
	auto res = _reciveMessage();
	if (!res)
		return false;
	if (_buffer.find("\r\n\r\n") == std::string::npos)
	{
		_state = HttpConnection::WAITING;
		return false;
	}
	return true;
}

bool HttpConnection::isCompleted()
{
	return HttpConnection::HANDLED == _state;
}
bool HttpConnection::isError()
{
	return HttpConnection::ERROR == _state;
} 

HttpRequest HttpConnection::getRequest() const
{
	return _reader.get()->getRequest(_buffer);
}

void HttpConnection::queueResponse(const HttpResponse& response)
{
	std::string dataResponse = _writer.get()->writeResponse(response);

}
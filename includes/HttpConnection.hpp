#ifndef __HTTPCONNECTION_H
#define __HTTPCONNECTION_H

#include "IHttpConnection.hpp"
#include <string>

class HttpConnection : public IHttpConnection
{
private:
	int _fd;
	std::string _buffer;

	typedef enum State
	{
		NEW,
		WAITING,
		HANDLED,
		ERROR
	} State;

	State _state;

	State _reciveMessage();

public:
	HttpConnection();
	HttpConnection(const HttpConnection& other);
	HttpConnection operator=(const HttpConnection& other);
	~HttpConnection() override;

	HttpConnection(int fd);

	void handleRequest() override;
	bool isHandled() override;
	bool isError() override; 
};

#endif
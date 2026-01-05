#ifndef __HTTPSERVER_HPP
#define __HTTPSERVER_HPP

#include "../interfaces/IHttpServer.hpp"

class HttpServer : IHttpServer
{
private:
	/* data */
public:
	HttpServer();
	HttpServer(const HttpServer& other);
	HttpServer operator=(const HttpServer& other);
	~HttpServer() override;
};

#endif
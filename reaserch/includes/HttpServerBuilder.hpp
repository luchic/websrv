#ifndef __HTTPSERVERBUILDER_H
#define __HTTPSERVERBUILDER_H

#include "../interfaces/IHttpServer.hpp"

class HttpServerBuilder
{
private:
	/* data */
public:
	HttpServerBuilder();
	HttpServerBuilder(const HttpServerBuilder& other);
	HttpServerBuilder& operator=(const HttpServerBuilder& other);
	~HttpServerBuilder();
};


#endif
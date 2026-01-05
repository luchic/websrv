#ifndef __HTTPAPPBUILDER_H
#define __HTTPAPPBUILDER_H

#include "../interfaces/IHttpApp.hpp"

class HttpAppBuilder
{
private:
	/* data */
public:
	HttpAppBuilder();
	HttpAppBuilder(const HttpAppBuilder& other);
	HttpAppBuilder& operator=(const HttpAppBuilder& other);
	~HttpAppBuilder();
};

#endif
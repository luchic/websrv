#ifndef __HTTPAPPBUILDER_H
#define __HTTPAPPBUILDER_H

#include "IHttpApp.hpp"
#include <string>

class HttpAppBuilder
{
private:
	/* data */
public:
	HttpAppBuilder();
	HttpAppBuilder(const HttpAppBuilder& other);
	HttpAppBuilder& operator=(const HttpAppBuilder& other);
	~HttpAppBuilder();

	HttpAppBuilder& get(std::string route);
	HttpAppBuilder& post(std::string route);
	HttpAppBuilder& qdelete(std::string route);

	IHttpApp build();
};

#endif
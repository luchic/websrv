#ifndef __IHTTPREADER_H
#define __IHTTPREADER_H

#include "HttpRequest.hpp"

class IHttpReader
{
private:
	/* data */
public:
	IHttpReader() = default;
	IHttpReader(const IHttpReader& other) = default;
	IHttpReader& operator=(const IHttpReader& other) = default;
	virtual ~IHttpReader() = default;

	virtual HttpRequest getRequest(std::string data) = 0;
};

#endif
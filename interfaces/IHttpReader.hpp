#ifndef __IHTTPREADER_H
#define __IHTTPREADER_H

#include "HttpRequest.hpp"

class IHttpReader
{
private:
	/* data */
public:
	IHttpReader();
	IHttpReader(const IHttpReader& other);
	IHttpReader& operator=(const IHttpReader& other);
	virtual ~IHttpReader();

	virtual HttpRequest getRequest(std::string data) = 0;
};

#endif
#ifndef __IHTTPWRITER_H
#define __IHTTPWRITER_H

#include "HttpResponse.hpp"

class IHttpWriter
{
private:
	/* data */
public:
	IHttpWriter();
	IHttpWriter(const IHttpWriter& other);
	IHttpWriter& operator=(const IHttpWriter& other);
	virtual ~IHttpWriter();

	virtual std::string writeResponse(const HttpResponse& response) = 0;
};

#endif
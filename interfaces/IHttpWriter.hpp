#ifndef __IHTTPWRITER_H
#define __IHTTPWRITER_H

#include "HttpResponse.hpp"

class IHttpWriter
{
private:
	/* data */
public:
	IHttpWriter() = default;
	IHttpWriter(const IHttpWriter& other) = default;
	IHttpWriter& operator=(const IHttpWriter& other) = default;
	virtual ~IHttpWriter() = default;

	virtual std::string writeResponse(const HttpResponse& response) = 0;
};

#endif
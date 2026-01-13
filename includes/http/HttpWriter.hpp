#ifndef __HTTPWRITER_H
#define __HTPPWRITER_H

#include "IHttpWriter.hpp"

class HttpWriter : public IHttpWriter
{
private:

public:
	HttpWriter();
	~HttpWriter() override;

	std::string writeResponse(const HttpResponse& response) override;
};

#endif
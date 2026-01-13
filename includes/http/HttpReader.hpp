#ifndef __HTTPREADER_H
#define __HTTPREADER_H

#include "IHttpReader.hpp"

class HttpReader : public IHttpReader
{
private:
public:
	HttpReader();
	~HttpReader() override;

	HttpRequest getRequest(std::string data) override;
};


#endif
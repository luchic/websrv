#ifndef __IHTTPREADER_H
#define __IHTTPREADER_H

class IHttpReader
{
private:
	/* data */
public:
	IHttpReader();
	IHttpReader(const IHttpReader& other);
	IHttpReader& operator=(const IHttpReader& other);
	virtual ~IHttpReader();
};

#endif
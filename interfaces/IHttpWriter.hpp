#ifndef __IHTTPWRITER_H
#define __IHTTPWRITER_H

class IHttpWriter
{
private:
	/* data */
public:
	IHttpWriter();
	IHttpWriter(const IHttpWriter& other);
	IHttpWriter& operator=(const IHttpWriter& other);
	virtual ~IHttpWriter();
};

#endif
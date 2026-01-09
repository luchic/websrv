
#ifndef __IHttpConnection_H
#define __IHttpConnection_H

class IHttpConnection
{
public:
	IHttpConnection() = default;
	IHttpConnection(const IHttpConnection& ather) = default;
	IHttpConnection& operator=(const IHttpConnection& ather) = default;
	virtual ~IHttpConnection() = default;

	virtual void handleRequest() = 0;
	virtual bool isHandled() = 0;
	virtual bool isError() = 0; 
};

#endif
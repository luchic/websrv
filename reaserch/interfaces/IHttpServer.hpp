#ifndef __IHTTPSERVER_H
#define __IHTTPSERVER_H

class IHttpServer
{
private:
	/* data */
public:
	IHttpServer();
	IHttpServer(const IHttpServer& other );
	IHttpServer &operator=(const IHttpServer& other);
	virtual ~IHttpServer() = 0;
};

#endif
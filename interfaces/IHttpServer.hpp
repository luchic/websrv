#ifndef __IHTTPSERVER_H
#define __IHTTPSERVER_H

class IHttpServer
{
private:
	/* data */
public:
    IHttpServer() = default;
    IHttpServer(const IHttpServer&) = default;
    IHttpServer& operator=(const IHttpServer&) = default;
    virtual ~IHttpServer() = default;

	virtual void run() = 0;
};

#endif
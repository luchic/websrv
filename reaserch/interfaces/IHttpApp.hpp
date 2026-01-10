#ifndef __IHTTPAPP_H
#define __IHTTPAPP_H

class IHttpApp
{
private:
	/* data */
public:
	IHttpApp() = default;
	IHttpApp(const IHttpApp& other) = default;
	IHttpApp& operator=(const IHttpApp& other) = default;
	virtual ~IHttpApp() = 0;
};

#endif
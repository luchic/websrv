#ifndef __IHTTPAPP_H
#define __IHTTPAPP_H

class IHttpApp
{
private:
	/* data */
public:
	IHttpApp();
	IHttpApp(const IHttpApp& other);
	IHttpApp operator=(const IHttpApp& other);
	virtual ~IHttpApp() = 0;
};

#endif
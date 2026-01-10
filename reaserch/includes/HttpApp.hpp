#ifndef __HTTPAPP_H
#define __HTTPAPP_H

#include "IHttpApp.hpp"

class HttpApp : IHttpApp
{
private:
	/* data */
public:
	HttpApp();
	HttpApp(const HttpApp& other);
	HttpApp& operator=(const HttpApp& other);
	~HttpApp() override;
};


#endif
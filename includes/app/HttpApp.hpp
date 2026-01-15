#ifndef __HTTPAPP_H
#define __HTTPAPP_H

#include "IHttpApp.hpp"
#include <vector>

class HttpApp : public IHttpApp
{
private:
	std::vector<std::unique_ptr<IMiddleware>> _middlewares;

public:
	HttpApp();
	HttpApp(const HttpApp& other);
	HttpApp& operator=(const HttpApp& other);
	~HttpApp() override;

	HttpResponse handle(HttpRequest& request) override;
};


#endif
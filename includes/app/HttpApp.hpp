#ifndef __HTTPAPP_H
#define __HTTPAPP_H

#include "IHttpApp.hpp"
#include <vector>

class HttpApp : public IHttpApp
{
private:
	// Do i wont to handle this in loop? Or it schould be like a rucursive algoritm??
	// Old version i need to think how i will ccontaion this middlewares
	std::vector<std::unique_ptr<IMiddleware>> _middlewares;

public:
	HttpApp();
	HttpApp(const HttpApp& other);
	HttpApp& operator=(const HttpApp& other);
	~HttpApp() override;

	HttpResponse handle(HttpRequest& request) override;
};


#endif
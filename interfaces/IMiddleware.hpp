#ifndef __IMIDDLEWARE_HPP
#define __IMIDDLEWARE_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class IMiddleware
{
public:
	IMiddleware() = default;
	IMiddleware(const IMiddleware& ather) = default;
	IMiddleware& operator=(const IMiddleware& ather) = default;
	virtual ~IMiddleware();

	virtual bool handle(const HttpRequest& request, HttpResponse& response) =0;
};

#endif
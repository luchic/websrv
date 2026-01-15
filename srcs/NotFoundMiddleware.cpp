#include "app/NotFoundMiddleware.hpp"


NotFoundMiddleware::NotFoundMiddleware(/* args */)
{
}

NotFoundMiddleware::NotFoundMiddleware(const NotFoundMiddleware& ather)
{}

NotFoundMiddleware &NotFoundMiddleware::operator=(
	const NotFoundMiddleware& ather)
{
	return *this;
}


NotFoundMiddleware::~NotFoundMiddleware()
{
}

bool NotFoundMiddleware::handle(
	const HttpRequest& request,
	HttpResponse& response)
{
	response.status = 404;
	response.statusText = "Not Found";
	response.headers["Content-Type"] = "text/html; charset=utf-8";
	response.body = "<html><body><h1>404 Not Found</h1></body></html>";
	return true;
}



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
	HttpResponse notFound;
	notFound.status = 404;
	notFound.statusText = "Not Found";
	notFound.headers["Content-Type"] = "text/html; charset=utf-8";
	notFound.body = "<html><body><h1>404 Not Found</h1></body></html>";

	response = notFound;
	return true;
}



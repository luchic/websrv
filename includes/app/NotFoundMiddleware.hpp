#ifndef __NOTFOUNDMIDDLEWARE_HPP
#define __NOTFOUNDMIDDLEWARE_HPP

#include "IMiddleware.hpp"
#include "app/BaseMiddleware.hpp"

class NotFoundMiddleware : public BaseMiddleware
{
public:
	NotFoundMiddleware();
	NotFoundMiddleware(const NotFoundMiddleware& ather);
	NotFoundMiddleware& NotFoundMiddleware::operator=(
		const NotFoundMiddleware& ather);
	~NotFoundMiddleware() override;

	bool handle(const HttpRequest& request, HttpResponse& response) override;
};



#endif
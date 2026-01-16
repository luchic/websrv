#ifndef __BASEMIDDLEWARE_HPP
#define __BASEMIDDLEWARE_HPP

#include "IMiddleware.hpp"

class BaseMiddleware : public IMiddleware
{
private:
	BaseMiddleware(const BaseMiddleware& ather);
	BaseMiddleware& BaseMiddleware::operator=(const BaseMiddleware& ather);

protected:
	std::unique_ptr<IMiddleware> _next;

public:
	BaseMiddleware();
	virtual ~BaseMiddleware() override;

	BaseMiddleware(const BaseMiddleware&& ather);
	BaseMiddleware& BaseMiddleware::operator=(const BaseMiddleware&& ather);


	void setNext(std::unique_ptr<IMiddleware> next) override
	{
		_next = std::move(next);
	}

	virtual bool handle(
		const HttpRequest& request, HttpResponse& response) override =0;
};

#endif
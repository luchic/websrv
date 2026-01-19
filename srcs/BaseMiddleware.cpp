#include "app/BaseMiddleware.hpp"

void BaseMiddleware::setNext(std::unique_ptr<IMiddleware> next)
{
	_next = std::move(next);
}
#ifndef __BASESTATICKMIDDLEWARE_HPP
#define __BASESTATICKMIDDLEWARE_HPP

#include "IMiddleware.hpp"

class BaseStaticMiddleware : public IMiddleware 
{
private:
std::string _getMimeType(const std::string& path);
std::string _readFile(const std::ifstream& file);
bool _handleFile(const HttpRequest& request, HttpResponse& response);

public:
	BaseStaticMiddleware();
	BaseStaticMiddleware(const BaseStaticMiddleware& other);
	BaseStaticMiddleware& operator=(const BaseStaticMiddleware& other);
	~BaseStaticMiddleware() override;

	bool handle(const HttpRequest& request, HttpResponse& response) override;
};

#endif
#ifndef __BASESTATICKMIDDLEWARE_HPP
#define __BASESTATICKMIDDLEWARE_HPP

#include "IMiddleware.hpp"

class StaticFilesMiddleware : public IMiddleware 
{
private:
std::string _getMimeType(const std::string& path);
std::string _readFile(const std::ifstream& file);
bool _handleFile(const HttpRequest& request, HttpResponse& response);

public:
	StaticFilesMiddleware();
	StaticFilesMiddleware(const StaticFilesMiddleware& other);
	StaticFilesMiddleware& operator=(const StaticFilesMiddleware& other);
	~StaticFilesMiddleware() override;

	bool handle(const HttpRequest& request, HttpResponse& response) override;
};

#endif
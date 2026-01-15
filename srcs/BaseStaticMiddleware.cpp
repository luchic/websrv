#include "app/BaseStaticMiddleware.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

BaseStaticMiddleware::BaseStaticMiddleware()
{
}

BaseStaticMiddleware::BaseStaticMiddleware(const BaseStaticMiddleware& other)
{
}

BaseStaticMiddleware& BaseStaticMiddleware::operator=(
	const BaseStaticMiddleware& other)
{
	return *this;
}

BaseStaticMiddleware::~BaseStaticMiddleware()
{
}

std::string BaseStaticMiddleware::_getMimeType(const std::string& path)
{
	static const std::map<std::string, std::string> mimeTypes =
	{
		{".html",  "text/html; charset=utf-8"},
		{".htm",   "text/html; charset=utf-8"},
		{".css",   "text/css; charset=utf-8"},
		{".js",    "application/javascript; charset=utf-8"},
		{".json",  "application/json"},
		{".xml",   "application/xml"},
		{".txt",   "text/plain; charset=utf-8"},
		{".png",   "image/png"},
		{".jpg",   "image/jpeg"},
		{".jpeg",  "image/jpeg"},
		{".gif",   "image/gif"},
		{".svg",   "image/svg+xml"},
		{".ico",   "image/x-icon"},
		{".pdf",   "application/pdf"},
		{".zip",   "application/zip"},
		{".woff",  "font/woff"},
		{".woff2", "font/woff2"},
		{".ttf",   "font/ttf"},
		{".mp4",   "video/mp4"},
		{".webm",  "video/webm"},
		{".mp3",   "audio/mpeg"},
		{".wav",   "audio/wav"}
	};

	size_t dotPos = path.rfind('.');
	if (dotPos == std::string::npos)
	{
		return "application/octet-stream";
	}

	std::string ext = path.substr(dotPos);

	auto it = mimeTypes.find(ext);
	if (it != mimeTypes.end())
	{
		return it->second;
	}

	return "application/octet-stream";
}

std::string BaseStaticMiddleware::_readFile(const std::ifstream& file)
{
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

bool BaseStaticMiddleware::_handleFile(const HttpRequest& request, HttpResponse& response)
{
	std::string fileName;
	std::string path = request.path;
	if (path == "/")
		fileName = "/index.html";
	
	fileName = "www" + path;
	std::ifstream file(fileName);
	if (!file.good())
		return false;

	std::string content = _readFile(file);

	response.status = 200;
	response.statusText = "OK";
	response.headers["Content-Type"] = _getMimeType(fileName);
	response.headers["Content-Length"] = std::to_string(content.size());
	response.body = content;

	return true;
}

bool BaseStaticMiddleware::handle(
	const HttpRequest& request,
	HttpResponse& response)
{

}
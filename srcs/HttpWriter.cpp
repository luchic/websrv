#include "http/HttpWriter.hpp"

HttpWriter::HttpWriter()
{
}

HttpWriter::~HttpWriter()
{
}

std::string HttpWriter::writeResponse(const HttpResponse& response)
{
	std::string body = "ok\n";
    std::string resp =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain; charset=utf-8\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" + body;
	return resp;
}


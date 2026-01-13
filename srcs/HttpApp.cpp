#include "app/HttpApp.hpp"

HttpApp::HttpApp()
{}

HttpApp::~HttpApp()
{}

HttpResponse HttpApp::handle(HttpRequest& request)
{
	return HttpResponse{};	
}

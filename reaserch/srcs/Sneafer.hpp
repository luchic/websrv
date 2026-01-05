#ifndef __SNEAFER_H
#define __SNEAFER_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>
#include <optional>
#include <string>


class HttpRequestSniffer
{
public:
  int run(uint16_t port)
  {
    int listenFd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd < 0) {
      perror("socket");
      return 1;
    }

    int yes = 1;
    ::setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    if (::bind(listenFd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
	{
      perror("bind");
      ::close(listenFd);
      return 1;
    }

    if (::listen(listenFd, 16) < 0)
	{
      perror("listen");
      ::close(listenFd);
      return 1;
    }

    std::cout << "Listening on http://127.0.0.1:" << port << "/\n";
    std::cout << "Open that URL in a browser; I'll print the raw request.\n\n";

    sockaddr_in client{};
    socklen_t clientLen = sizeof(client);
    int clientFd = ::accept(listenFd, reinterpret_cast<sockaddr*>(&client), &clientLen);
    if (clientFd < 0)
	{
      perror("accept");
      ::close(listenFd);
      return 1;
    }

    // Small timeout so we don't hang forever waiting for extra bytes
    timeval tv{};
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    ::setsockopt(clientFd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    std::string requestBytes;
    requestBytes.reserve(8192);

    // Read until end-of-headers, then read body if Content-Length exists.
    while (true)
	{
      char buf[4096];
      ssize_t n = ::recv(clientFd, buf, sizeof(buf), 0);
      if (n > 0)
	  {
        requestBytes.append(buf, buf + n);
      } 
	  else if (n == 0)
	  {
        break; // client closed
      }
	  else
	  {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
			break; // timeout
        perror("recv");
        break;
      }
    }

    std::cout << "----- RAW REQUEST (" << requestBytes.size() << " bytes) -----\n";
    std::cout.write(requestBytes.data(), static_cast<std::streamsize>(requestBytes.size()));
    std::cout << "\n----- END REQUEST -----\n";

    // Send a minimal response so the browser finishes.
    std::string body = "<!DOCTYPE html><html><head><title>Page Title</title></head><body><h1>This is a Heading</h1><p>This is a paragraph.</p></body></html>";
    std::string resp =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Content-Length: " + std::to_string(body.size()) + "\r\n"
        "Connection: close\r\n"
        "\r\n" + body;

    (void)::send(clientFd, resp.data(), resp.size(), 0);

    ::close(clientFd);
    ::close(listenFd);
    return 0;
  }
};

#endif
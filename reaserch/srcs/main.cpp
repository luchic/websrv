
#include "Sneafer.hpp"

int main(int argc, char** argv) {
  uint16_t port = 8080;
  if (argc >= 2) port = static_cast<uint16_t>(std::stoi(argv[1]));
  HttpRequestSniffer sniffer;
  return sniffer.run(port);
}
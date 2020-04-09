


#include "webi/http_client.h"

#include "cpp-httplib/httplib.h"

#include "http_converter_cpphttplib.h"

using namespace webi;


class HttpClientImpl : public HttpClient {
private:
  httplib::Client client_;
public:
  HttpClientImpl(const std::string& addr, const int port) : client_(addr.c_str(), port) {
  }

  virtual ~HttpClientImpl() {}
public:
  virtual void setTimeout(uint64_t seconds) {
      client_.set_timeout_sec(seconds);
//    client_.set_read_timeout(0, 10000);d
  }
public:
  virtual Response request(const std::string& url, const std::string& method) {
      if (method == "GET") {
          auto response = client_.Get(url.c_str());
          return convert(std::move(response));
      } else if (method == "POST") {
          auto response = client_.Post(url.c_str(), "", "text/html");
          return convert(response);
      } else if (method == "PUT") {
          auto response = client_.Put(url.c_str(),  "", "text/html");
          return convert(response);
      } else if (method == "DELETE") {
          auto response = client_.Delete(url.c_str(),  "", "text/html");
          return convert(response);
      }
  }

  virtual Response request(const std::string& url, const std::string& method, const Request& req) {
      if (method == "GET") {
          auto response = client_.Get(url.c_str());
          return convert(response);
      } else if (method == "POST") {
          auto response = client_.Post(url.c_str(), req.body.c_str(), req.contentType.c_str());
          return convert(response);
      } else if (method == "PUT") {
          auto response = client_.Put(url.c_str(), req.body.c_str(), req.contentType.c_str());
          return convert(response);
      }
  }
  
};



webi::HttpClient_ptr webi::client(const std::string& addr, const int port) {
    return webi::HttpClient_ptr(new HttpClientImpl(addr, port));
}

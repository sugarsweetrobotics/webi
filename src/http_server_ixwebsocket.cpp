#include <iostream>

#include <fstream>
#include "webi/http_server.h"

//#include "cpp-httplib/httplib.h"
#include <ixwebsocket/IXHttpServer.h>
#include <ixwebsocket/IXUserAgent.h>

#include "webi/webi.h"
#include "webi_impl.h"

using namespace webi;

/*
static webi::Request convert(const httplib::Request &req)
{
  return webi::Request(req.method, req.body, req.matches);
}


static void apply(httplib::Response &response, webi::Response &&r)
{
  response.status = r.status;
  response.version = r.version;
  
  response.set_content(r.body, r.contentType.c_str());
    //  response.body = r.body;
}
*/

class ResponseFunction {
public:
  std::function<webi::Response(webi::Request&)> func;
  std::string path;
  std::string contentType;

public:
  ResponseFunction(const std::string& path, const std::string& contentType, std::function<webi::Response(webi::Request&)> func) : path(path), contentType(contentType), func(func) {}
};

class HttpServerImpl : public HttpServer{
private:
  //httplib::Server server_;
  ix::HttpServer *server_;
  std::unique_ptr<std::thread> thread_;
  std::vector<ResponseFunction> getters_;
  std::vector<ResponseFunction> posters_;
  std::vector<ResponseFunction> putters_;
  std::string baseDir_;
public:
  HttpServerImpl();
  virtual ~HttpServerImpl();

  HttpServerImpl(HttpServerImpl&& server);

  void baseDirectory(const std::string& path) override;
  
  void response(const std::string& path, const std::string& method, const std::string& contentType, std::function<webi::Response(const webi::Request&)> callback) override;

  void runForever(const int32_t port=8080) override;
    
  void runBackground(const int32_t port=8080) override;

  bool waitBackground(const double timeout_sec=-1) override;

  void terminateBackground() override;
};


HttpServerImpl::HttpServerImpl() : baseDir_(".") {
}

HttpServerImpl::HttpServerImpl(HttpServerImpl&& server) {
}

HttpServerImpl::~HttpServerImpl() {

}

void HttpServerImpl::baseDirectory(const std::string& path) {
  //server_.set_base_dir(path.c_str());
  baseDir_ = path;
}

void HttpServerImpl::response(const std::string& path, const std::string& method, const std::string& contentType, std::function<webi::Response(const webi::Request&)> callback) {
  if (method == "GET") {
    getters_.emplace_back(ResponseFunction(path, contentType, callback));
  } else if (method == "PUT") {
    putters_.emplace_back(ResponseFunction(path, contentType, callback));
  } else if (method == "POST") {
    posters_.emplace_back(ResponseFunction(path, contentType, callback));
  }
}



static std::pair<bool, std::vector<uint8_t>> load(const std::string& path)
{
    std::vector<uint8_t> memblock;

    std::ifstream file(path);
    if (!file.is_open()) return std::make_pair(false, memblock);

    file.seekg(0, file.end);
    std::streamoff size = file.tellg();
    file.seekg(0, file.beg);

    memblock.resize((size_t) size);
    file.read((char*) &memblock.front(), static_cast<std::streamsize>(size));

    return std::make_pair(true, memblock);
}

static std::pair<bool, std::string> readAsString(const std::string& path)
{
    auto res = load(path);
    auto vec = res.second;
    return std::make_pair(res.first, std::string(vec.begin(), vec.end()));
}

static auto defaultOnConnectionCallback = [](ix::HttpRequestPtr request,
                   std::shared_ptr<ix::ConnectionState> /*connectionState*/) -> ix::HttpResponsePtr {
                std::string uri(request->uri);
                if (uri.empty() || uri == "/")
                {
                    uri = "/index.html";
                }

                ix::WebSocketHttpHeaders headers;
                headers["Server"] = ix::userAgent();

                std::string path("." + uri);
                auto res = readAsString(path);
                bool found = res.first;
                if (!found)
                {
                    return std::make_shared<ix::HttpResponse>(
                        404, "Not Found", ix::HttpErrorCode::Ok, ix::WebSocketHttpHeaders(), std::string());
                }

                std::string content = res.second;

                // Log request
                std::stringstream ss;
                ss << request->method << " " << request->headers["User-Agent"] << " "
                   << request->uri << " " << content.size();
                //logInfo(ss.str());

                // FIXME: check extensions to set the content type
                // headers["Content-Type"] = "application/octet-stream";
                headers["Accept-Ranges"] = "none";

                for (auto&& it : request->headers)
                {
                    headers[it.first] = it.second;
                }

                return std::make_shared<ix::HttpResponse>(
                    200, "OK", ix::HttpErrorCode::Ok, headers, content);
            };



void HttpServerImpl::runForever(const int32_t port /*=8080*/) {
  std::cout << "HttpServerImpl (IXWebSocket) runForever(" << port << ")" << std::endl;
  auto hostname = "0.0.0.0";
  server_ = new ix::HttpServer(port, hostname);

  server_->setOnConnectionCallback(
    [this](ix::HttpRequestPtr request,
           std::shared_ptr<ix::ConnectionState> /*connectionState*/) -> ix::HttpResponsePtr
    {
        // Build a string for the response
        std::stringstream ss;
        ss << request->method
           << " "
           << request->uri;

        std::string content = ss.str();

        return std::make_shared<ix::HttpResponse>(200, "OK",
                                              ix::HttpErrorCode::Ok,
                                              ix::WebSocketHttpHeaders(),
                                              content);
});

  auto [result, msg] = server_->listen();

  if (!result) {
    std::cerr << msg << std::endl;
    return;
  }

  server_->start();
  server_->wait();
}

void HttpServerImpl::runBackground(const int32_t port /*=8080*/) {
  std::string address = "localhost";
  const double timeout = 10.0;
  auto _port = port;
  thread_ = std::unique_ptr<std::thread>(new std::thread([port, this] {
							   this->runForever(port);
							 }));
}

bool HttpServerImpl::waitBackground(const double timeout_sec) {
  thread_->join();
  return true;
}

void HttpServerImpl::terminateBackground() {
  server_->stop();  
}

HttpServer_ptr WebiImpl::createHttpServerImpl() {
  std::cout << "WebiImpl::createHttpServerImpl(IXWebSocket)" << std::endl;
  auto svc = std::make_shared<HttpServerImpl>();

  std::cout << "exit2" << std::endl;
  return std::move(svc);
}


webi::HttpServer_ptr webi::server() {
  return webi::HttpServer_ptr(new HttpServerImpl());
}

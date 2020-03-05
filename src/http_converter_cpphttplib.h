

namespace webi {

inline webi::Request convert(const httplib::Request &req)
{
  return webi::Request(req.method, req.body, req.headers.find("Content-Type")->second, req.matches);
}

inline void apply(httplib::Response &response, webi::Response &&r)
{
  response.status = r.status;
  response.version = r.version;
  response.set_content(r.body, r.contentType.c_str());
}

inline webi::Response convert(std::shared_ptr<httplib::Response> response)
{
    return webi::Response(response->status, response->body, response->headers.find("Content-Type")->second);
}

}
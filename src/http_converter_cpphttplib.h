

namespace webi {

 template<typename T, typename K, typename V>
  std::vector<T> map(std::multimap<K, V>& map, std::function<T(const K&,V&)> func) {
    std::vector<T> ret;
    for(auto& [k, v] : map) {
      ret.emplace_back(func(k, v));
    }
    return ret;
  }

inline webi::Request convert(const httplib::Request &req)
{
  std::vector<webi::Header> ret;
  for(const auto& [k, v] : req.headers) {
    ret.push_back(Header(k, v));
  }
  
  return webi::Request(req.method, req.body, ret, req.matches);
}

inline void apply(httplib::Response &response, webi::Response &&r)
{
  response.status = r.status;
  response.version = r.version;
  response.set_content(r.body, r.contentType.c_str());
}

inline webi::Response convert(std::shared_ptr<httplib::Response> response)
{
  if (response) {
    //return webi::Response(response->status, response->body, (ret));
    return webi::Response(response->status, response->body, response->headers.find("Content-Type")->second);
  }
  return webi::Response(404, "", "text/html");
}

}
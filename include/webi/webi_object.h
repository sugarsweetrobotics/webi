#pragma once



namespace webi {

  struct WebiMessage {
    std::string target;
    std::string type;
    std::string id;
    std::string eventType;
    std::string body;
    std::string value;

    WebiMessage(const std::string& target, 
		const std::string& type,
		const std::string& id,
		const std::string& eventType,
		const std::string& body,
		const std::string& value)
    : target(target), type(type), id(id), eventType(eventType), body(body), value(value) {}
  };

  class Document;

  class IWebi {
  public:
    virtual ~IWebi() {}
    
  public:
    virtual Server_ptr createServer() = 0;
    virtual void parseEventListener(html::Tag& tag) = 0;
  };
  
  class Webi : IWebi {
  private:
    IWebi* impl_;
  public:
    Webi();
    virtual ~Webi();

    virtual Server_ptr createServer() { return impl_->createServer(); }


  public:
    virtual void parseEventListener(html::Tag& tag) { impl_->parseEventListener(tag); }

  };

  
};

#include <sstream>

#include "webi/server.h"
#include "webi/webi.h"

using namespace webi;

struct ElementCommand {
	const std::string id;
	const std::string dir;
	const std::string cmd;
	const std::string arg;
};

static std::string convert(ElementCommand&& cmd) {
	std::stringstream ss;
	ss << "{\"type\":\"" << "element"
		<< "\",\"id\":\"" << cmd.id
		<< "\",\"dir\":\"" << cmd.dir
		<< "\",\"cmd\":\"" << cmd.cmd
		<< "\",\"arg\":\"" << cmd.arg
		<< "\"}";
	return ss.str();
}


class ServerImpl : public webi::Server {
private:

	friend class Webi;

	HttpServer_ptr http_server_;
	WebSocketServer_ptr websock_server_;
public:
	ServerImpl(HttpServer_ptr http_server, WebSocketServer_ptr websock_server)
		: http_server_(http_server), websock_server_(websock_server) {}

	virtual ~ServerImpl() {}

	virtual void baseDirectory(const std::string& path) override {
		http_server_->baseDirectory(path);
	}

	virtual void response(const std::string& path, const std::string& method, const std::string& contentType, const std::string& content) override {
		http_server_->response(path, method, contentType, content);
	}

	virtual void response(const std::string& path, const std::string& method, const std::string& contentType, std::function<webi::Response(const webi::Request&)> callback) override {
		http_server_->response(path, method, contentType, callback);
	}

	virtual void get(const std::string& path, const Tag& tag) override {
		http_server_->get(path, tag);
	}

	/**
	 * Run ServerImpl on Current Thread. This function blocks until signal is raised..
	 */
	virtual void runForever(const int32_t port = 8080, const int32_t websock_port = 8081) override {
		websock_server_->runBackground();
		http_server_->runForever(port);
	}

	/**
	 * Run ServerImpl on Background Thread.
	 * @see waitBackground
	 * @see terminateBackground
	 */
	virtual void runBackground(const int32_t port = 8080, const int32_t websock_port = 8081) override {
		http_server_->runBackground(port);
		websock_server_->runBackground(websock_port);
	}

	/**
	 *
	 * @param timeout_sec Timeout Interval. Forever if negative.
	 * @return ServerImpl is ended if true. Timeout if false.
	 */
	virtual bool waitBackground(const double timeout_sec = -1) override {
		return http_server_->waitBackground(timeout_sec);
	}

	virtual void terminateBackground() override  {
		return http_server_->terminateBackground();
	}

	virtual webi::Document createDocument() override {
		return Document(this);
	}

	virtual void elementCommandById(const std::string& id,
		const std::string& direction,
		const std::string& command,
		const std::string& arg) override {
		websock_server_->send(convert({ id, direction, command, arg }));
	}

};

Server_ptr Webi::createServer() {
	return std::make_shared<ServerImpl>(createHttpServer(), createWebSocketServer());
}

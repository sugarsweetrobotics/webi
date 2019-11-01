#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <memory>

#include "webi/webi_common.h"

#include "html.h"
#include "response.h"
#include "http_server.h"
#include "websocket_server.h"

namespace webi {

	class Document;

	class ElementResponse;
	
	struct WebiMessage;

	class WEBI_API Server {
	private:
		Webi_ptr webi_ptr_;

		void setWebi(Webi_ptr ptr) {
			webi_ptr_ = ptr;
		}

		Webi_ptr getWebi() { return webi_ptr_; }

		friend class Webi;
	public:
		Server() {}

		virtual ~Server() {}

		virtual void baseDirectory(const std::string& path) = 0;

		virtual void response(const std::string& path, const std::string& method, const std::string& contentType, const std::string& content) = 0;

		virtual void response(const std::string& path, const std::string& method, const std::string& contentType, std::function<webi::Response(const webi::Request&)> callback) = 0;

		virtual void get(const std::string& path, Tag& tag) = 0;

		/**
		 * Run Server on Current Thread. This function blocks until signal is raised..
		 */
		virtual void runForever(const int32_t port = 8080, const int32_t websock_port = 8081) = 0;

		/**
		 * Run Server on Background Thread.
		 * @see waitBackground
		 * @see terminateBackground
		 */
		virtual void runBackground(const int32_t port = 8080, const int32_t websock_port = 8081) = 0;

		/**
		 *
		 * @param timeout_sec Timeout Interval. Forever if negative.
		 * @return Server is ended if true. Timeout if false.
		 */
		virtual bool waitBackground(const double timeout_sec = -1) = 0;
		virtual void terminateBackground() = 0;

		virtual webi::Document createDocument() = 0;

		virtual void elementCommandById(const std::string& id,
			const std::string& direction,
			const std::string& command,
			const std::string& arg) = 0;

		virtual void bookResponse(std::function<bool(const WebiMessage&)> filter, std::function<void(const WebiMessage&)> callback) = 0;

		virtual bool parseBookedResponse(const WebiMessage& msg) = 0;

		virtual void elementResponseById(const std::string& id, std::function<void(const ElementResponse& response)> callback) = 0;

	};

	using Server_ptr = std::shared_ptr<Server>;
};

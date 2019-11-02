#pragma once


namespace webi {
namespace js {

	class Expression {
	public:

	};

	class Object {
	private:
		std::string name_;
	public:
		Object(const std::string& name) : name_(name) {}

		auto name() const { return name_; }

        auto expression() const { return name_ + ";"; }
        
	public:

		auto concatArguments(const Object& obj) {
			return obj.name_;
		}

		template<typename...R>
		auto concatArguments(const Object& obj, R...r) {
			return obj.name_ + "," + concatArguments(r...);
		}

		template<typename...R>
		auto call(const std::string& name, R...r) {
			return Object(name_ + "." + name + "(" + concatArguments(r...) + ")");
		}
	};

	inline auto text(const std::string& txt) { return Object("\"" + txt + "\""); }

	class Element : public js::Object {
	public:
		Element(const std::string& name) : js::Object(name) {}

	public:
		auto addEventListener(const std::string& evt, const Object& func) {
			return this->call("addEventListener", js::text(evt), func);
		}
	};


	class Document : public js::Object {

	public:
		Document() : js::Object("document") {}
	public:
		auto getElementById(const std::string& id) { return Element(this->call("getElementById", js::text(id)).name()); }
	};

	class Webi : public js::Object {
	public:
		Webi() : js::Object("webi") {}

	public:
		auto on_action_event(const std::string& elementType, const std::string& inputType, const std::string& eventType, const std::string& targetId) {
			return this->call("on_action_event", js::text(elementType), js::text(inputType), js::text(eventType), js::text(targetId));
		}
	};

	inline Webi webi() { return Webi(); }

	class LambdaFunction : public Object {
	private:

	public:
		LambdaFunction(const std::string& arg0) : Object(arg0) {}

		LambdaFunction(const Object& arg0) : Object(arg0.name()) {}

	public:
		auto define(const Object& definition) {
			return Object("("+name()+")=>{" + definition.name() + "}");
		}
	};

	inline auto lambda(const std::string& arg) {
		return LambdaFunction(arg);
	}
}

}


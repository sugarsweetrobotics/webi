#pragma once

#include <sstream>

namespace webi::js {

	class Expression {
	protected:
		std::string exp_;
	public:
		Expression(const std::string& e) : exp_(e) {}
		Expression(const Expression& e) : exp_(e.exp_) {}
		Expression(Expression&& e) : exp_(std::move(e.exp_)) {}

	public:
		std::string expression() const { return exp_ + ";"; }
	};

	using ExpressionSet = std::vector<Expression>;

	inline std::string expression(const ExpressionSet& ee) {
		std::stringstream ss;
		for (auto e : ee) {
			ss << e.expression();
		}
		return ss.str();
	}

	class Object;

	inline Object text(const std::string& txt);

	class Object : public Expression {
	private:
	public:
		Object(const std::string& name) : Expression(name) {}

		auto name() const { return exp_; }

        auto expression() const { return exp_ + ";"; }

		auto member(const std::string& name) {
			return Object(exp_ + "." + name);
		}
        
		auto assign(const std::string& v) const {
			return Expression(exp_ + "=" + v);
		}

		auto assign(const Object& o) {
			return Expression(exp_ + "=" + o.name());
		}
	public:

		auto concatArguments(const Object& obj) {
			return obj.exp_;
		}

		template<typename...R>
		auto concatArguments(const Object& obj, R...r) {
			return obj.exp_ + "," + concatArguments(r...);
		}

		template<typename...R>
		auto call(const std::string& name, R...r) {
			return Object(exp_ + "." + name + "(" + concatArguments(r...) + ")");
		}

		auto addEventListener(const std::string& evt, const Object& func) {
			return this->call("addEventListener", js::text(evt), func);
		}
	};

	inline Object text(const std::string& txt) { return Object("\"" + txt + "\""); }

	class Element : public js::Object {
	public:
		Element(const std::string& name) : js::Object(name) {}

	public:
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

		auto define(const ExpressionSet& ee) {
			return Object("(" + name() + ")=>{" + js::expression(ee) + "}");
		}
	};

	inline auto lambda(const std::string& arg) {
		return LambdaFunction(arg);
	}

	inline auto var(const std::string& name) {
		return Object("var " + name);
	}

	inline auto let(const std::string& name) {
		return Object("let " + name);
	}

	inline auto new_(const std::string& name) {
		return Object("new " + name);
	}

	inline auto console_log(const std::string& name) {
		return Expression("console.log(\"" + name + "\")");
	}

	class Conditional : public Object {

	public:
		Conditional(const std::string& name) : Object(name) {}


	public:
		auto does(const ExpressionSet& es) {
			return Object("{" + js::expression(es) + "}");
		}
	};

	inline auto if_ (const Object& obj) {
		return Object("if(" + obj.name() + ")");
	}
}


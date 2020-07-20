#include "xchain/xchain.h"

// The base class of the contract
// The contract needs to implement the method specified in the base class
// The parameters are provided by the context in xchain::Contract
class BsnBaseBasic {
public:
	/*
	* func: initialization
	* @param: None; it can be customized if needed;
	*/
	virtual void initialize() = 0;
	/*
	* func: insert data
	* @param: base_key: unique key
	* @param: base_value: content
	*/
	virtual void insert() = 0;
	/*
	* func: update data
	* @param: base_key: unique key
	* @param: base_value: content
	*/
	virtual void update() = 0;
	/*
	* func: delete data
	* @param: base_key: unique key
	*/
	virtual void remove() = 0;
	/*
	* func: query data
	* @param: base_key: unique key
	*/
	virtual void select() = 0;
};

struct BsnBase :public BsnBaseBasic, public xchain::Contract {
public:
	void initialize(){
		xchain::Context* ctx = this->context();

		ctx->ok("initialize success");
	}
	void insert(){
		xchain::Context* ctx = this->context();
		const std::string& key = ctx->arg("base_key");
		const std::string& value = ctx->arg("base_value");

		if (key.empty()) {
			ctx->error("missing base_key");
			return;
		}
		if (value.empty()) {
			ctx->error("missing base_value");
			return;
		}

		std::string old_value;
		if (ctx->get_object(key, &old_value)){
			ctx->error("key already exists");
		}
		else
		{
			ctx->put_object(key, value);
			ctx->ok("insert success");
		}
	}
	void update(){
		xchain::Context* ctx = this->context();
		const std::string& key = ctx->arg("base_key");
		const std::string& value = ctx->arg("base_value");
		if (key.empty())
		{
			ctx->error("missing base_key");
			return;
		}
		if (value.empty()) {
			ctx->error("missing base_value");
			return;
		}
		std::string old_value;
		if (ctx->get_object(key, &old_value)){
			ctx->put_object(key, value);
			ctx->ok("update success");
		}
		else
		{
			ctx->error("key not found");
		}
	}
	void remove(){
		xchain::Context* ctx = this->context();
		const std::string& key = ctx->arg("base_key");
		if (key.empty())
		{
			ctx->error("missing base_key");
			return;
		}
		std::string value;
		if (ctx->get_object(key, &value)){
			ctx->delete_object(key);
			ctx->ok("remove success");
		}
		else
		{
			ctx->error("key not found");
		}
	}
	void select(){
		xchain::Context* ctx = this->context();
		const std::string& key = ctx->arg("base_key");
		if (key.empty())
		{
			ctx->error("missing base_key");
			return;
		}
		std::string value;
		if (ctx->get_object(key, &value)){
			ctx->ok(value);
		}
		else {
			ctx->error("key not found");
		}
	}
};

DEFINE_METHOD(BsnBase, initialize) {
	self.initialize();
}

DEFINE_METHOD(BsnBase, insert_data) {
	self.insert();
}

DEFINE_METHOD(BsnBase, update_data){
	self.update();
}

DEFINE_METHOD(BsnBase, remove_data){
	self.remove();
}

DEFINE_METHOD(BsnBase, select_data){
	self.select();
}

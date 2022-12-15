#include <iostream>
#include <string>

class Notify {
public:
	//发送
	virtual void send(std::string& msg) = 0;
	bool bEnabled(){
		return this != nullptr;
	}
};

class BaseDecorator : public Notify {
public:
	BaseDecorator(Notify* wrappee){
		this->_wrappee = wrappee;
	}

	void send(std::string& msg) override {
		_wrappee->send(msg);
	}
protected:
	Notify* _wrappee;
};

class MailNotify : public BaseDecorator {
public:
	MailNotify(Notify* wrappee) : BaseDecorator(wrappee) {
		this->_wrappee = wrappee;
	}
	void send(std::string& msg) override {
		std::cout << "mail send --->" << msg << std::endl;
		if(this->_wrappee->bEnabled()){
			this->_wrappee->send(msg);
		}
	}
};

class WechatNotify : public Notify{
public:
	void send(std::string& msg) override {
		std::cout << "wechat send --->" << msg << std::endl;
	}
};

class DingdingNotify : public Notify{
public:
	void send(std::string& msg) override {
		std::cout << "dingding sen --->" << msg << std::endl;
	}
};

int main() {
	std::cout << "wrapper/decorator" << std::endl;
	//Notify notify;
	//notify.send("this is a notify msg.");
	
	std::string msg = "hello i am wrapper patterner";

	//MailNotify mailNotify;
	//mailNotify.send(msg);

	//WechatNotify wechatNotify;
	//wechatNotify.send(msg);

	//DingdingNotify dingdingNotify;
	//dingdingNotify.send(msg);

	WechatNotify wechatNotify;
	MailNotify mailNotify(&wechatNotify);
	mailNotify.send(msg);

	Notify* notify = new WechatNotify();
	MailNotify mailNotify2(notify);
	mailNotify2.send(msg);

	delete notify;
	notify = NULL;

	return EXIT_SUCCESS;
}

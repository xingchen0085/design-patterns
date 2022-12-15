[TOC]

# 设计模式

软件设计模式是面向对象环境中反复出现的问题的通用解决方案，它不能直接转换源码为设计，而是解决这些问题的通用模版。我们将各模式的目的分为创建型（抽象实例化对象）、结构型（类和对象如何组织成更大的结构）、行为行（对象之间的责任分配）三大类。

## 创建型

工厂方法，父类中提供一个方法供子类实例化对象

抽象工厂，创建一系列相关对象，无需制定具体类

生成器，如何创建复合对象，分步骤创建复杂对象，不同的对象的通过不同的步骤生成

原型，复制已有对象，无需代码依赖他们所属的类

单例，保证一个类只有一个实例，并提供访问该实例的全局方法

### 工厂方法

“当你在编写代码的过程中， 如果无法预知对象确切类别及其依赖关系时， 可使用工厂方法。”

“ 如果你希望用户能扩展你软件库或框架的内部组件， 可使用工厂方法。”

“如果你希望复用现有对象来节省系统资源， 而不是每次都重新创建对象， 可使用工厂方法。”

> 摘录来自
> 深入设计模式
> 亚历山大 · 什韦茨
> https://itunes.apple.com/WebObjects/MZStore.woa/wa/viewBook?id=0。

```cpp
#include <iostream>

class Product{
public:
    virtual void doStuff() = 0;
};

class ConcreteProductA : public Product {
public:
    void doStuff() override {
        std::cout << "I am ConcreteProductA.doStuff()" << std::endl;
    }
};

class ConcreteProductB : public Product {
public:
    void doStuff() override {
        std::cout << "I am ConcreteProductB.doStuff()" << std::endl;
    }
};

class ProductFactory{
public:
    virtual Product* createProduct() = 0;
};

class ProductFactoryA : public ProductFactory {
public:
    Product* createProduct(){
        return new ConcreteProductA();
    }
};

class ProductFactoryB : public ProductFactory {
public:
    Product* createProduct(){
        return new ConcreteProductB();
    }
};

class Button{
public:
    virtual bool render() = 0;
};
class WindowButton : public Button {
public:
    bool render() override {
        std::cout << "Windows Button render ok." << std::endl;
    }
};
class HtmlButton : public Button {
public:
    bool render() override {
        std::cout << "<button>Html Button</button>" << std::endl;
    }
};
class Dialog {
public:
    virtual Button* createButton() = 0;
};
class WindowDialog : public Dialog {
public:
    Button* createButton() override{
        return new WindowButton();
    }
};
class HtmlDialog : public Dialog {
public:
    Button* createButton() override{
        return new HtmlButton();
    }
};

int main(){
    std::cout<< "factory method." <<std::endl;

    ProductFactory* factory = new ProductFactoryA();
    Product* productA = factory->createProduct();
    productA->doStuff();

    ProductFactory* factory2 = new ProductFactoryB();
    Product* productB = factory2->createProduct();
    productB->doStuff();

    delete productB;
    delete productA;
    delete factory2;
    delete factory;

    Dialog* dialog = new HtmlDialog();
    Button* htmlButton = dialog->createButton();
    htmlButton->render();

    Dialog* dialog2 = new WindowDialog();
    Button* windowButton = dialog2->createButton();
    windowButton->render();

    delete windowButton;
    delete dialog2;
    delete htmlButton;
    delete dialog;
    return EXIT_SUCCESS;
}
```

### 抽象工厂

“如果代码需要与多个不同系列的相关产品交互， 但是由于无法提前获取相关信息， 或者出于对未来扩展性的考虑， 你不希望代码基于产品的具体类进行构建， 在这种情况下， 你可以使用抽象工厂”

```cpp
#include <iostream>

class Button {
public:
    virtual std::string render() = 0;
};

class WindowButton : public Button {
public:
    std::string render() override {
        return "<button type = 'WIN'>Windows Button</button>";
    }
};

class MacButton : public Button {
public:
    std::string render() override {
        return "<button type = 'MACOS'> Macos Button </button>";
    }
};

class CheckBox {
public:
    virtual void onClick() = 0;
};

class WindowCheckBox : public CheckBox {
public:
    void onClick() override{
        std::cout<< "WindowCheckBox.onClick()" <<std::endl;
    }
};

class MacCheckBox : public CheckBox {
public:
    void onClick() override{
        std::cout<< "MacCheckBox.onClick()" <<std::endl;
    }
};

class GUIFactory {
public:
    virtual Button* createButton() = 0;
    virtual CheckBox* createCheckBox() = 0;
};

class ConcreteWindowGUIFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new WindowButton();
    }
    CheckBox* createCheckBox() override {
        return new WindowCheckBox();
    }
};

class ConcreteMaxGUIFactory : public GUIFactory {
public:
    Button* createButton() override {
        return new MacButton();
    }
    CheckBox* createCheckBox() override {
        return new MacCheckBox();
    }
};


int main(){
    std::cout<< "factory abstract" <<std::endl;
    
    GUIFactory* factory1 = new ConcreteWindowGUIFactory();
    Button* winBtn = factory1->createButton();
    std::cout<< winBtn->render() <<std::endl;
    CheckBox* winCb = factory1->createCheckBox();
    winCb->onClick();

    GUIFactory* factory2 = new ConcreteMaxGUIFactory();
    Button* macBtn = factory2->createButton();
    std::cout<< macBtn->render() <<std::endl;
    CheckBox* macCb = factory2->createCheckBox();
    macCb->onClick();

    delete macCb;
    delete macBtn;
    delete factory2;
    delete winCb;
    delete winBtn;
    delete factory1;

    return EXIT_SUCCESS;
}
```



```cpp
#include <iostream>

enum ShapeType {
    CIRCLE, RECTANGE
};

enum ColorType {
    RED, GREEN, BLUE
};

class Color {
public:
    virtual ~Color(){}
    virtual void fill() = 0;
};

class RedColor : public Color {
public: 
    virtual void fill() override {
        std::cout<< "fill Red." <<std::endl;
    }
};

class GreenColor : public Color {
public: 
    virtual void fill() override {
        std::cout<< "fill Green." <<std::endl;
    }
};

class BlueColor : public Color {
public: 
    virtual void fill() override {
        std::cout<< "file Blue." <<std::endl;
    }
};

class Shape {
public:
    virtual ~Shape(){
        if(this->color){
            std::cout<< "Color pointer free." <<std::endl;
            delete this->color;
        }
    }
    virtual void draw() = 0;
    void setColor(Color* color) {
        this->color = color;
    }
protected:
    Color* color;
};

class Circle : public Shape {
public:
    virtual void draw() override {
        std::cout<< "Cilcle." <<std::endl;
        this->color->fill();
    }
};

class Rectange : public Shape {
public:
    virtual void draw() override {
        std::cout<< "Rectange." <<std::endl;
        this->color->fill();
    }
};

class AbsFactory {
public:
    virtual ~AbsFactory(){};
    virtual Shape* createShape(ShapeType shapeType) = 0;
    virtual Color* createColor(ColorType colorType) = 0;
};

class ShapeFactory : public AbsFactory {
public:
    Shape* createShape(ShapeType type) override {
        if(type == ShapeType::CIRCLE){
            return new Circle();
        } else if(type == ShapeType::RECTANGE){
            return new Rectange();
        } else {
            std::cerr<< "Unsuported this Shape." <<std::endl;
            return nullptr;
        }
    }
    Color* createColor(ColorType colorType) override {
        return nullptr;
    }
};

class ColorFactory : public AbsFactory {
public:
    Shape* createShape(ShapeType type) override {
        return nullptr;
    }
    Color* createColor(ColorType type) override {
        if(type == ColorType::RED){
            return new RedColor();
        } else if(type == ColorType::GREEN){
            return new GreenColor();
        } else if(type == ColorType::BLUE){
            return new BlueColor();
        } else {
            std::cerr<< "Unsuported this color." <<std::endl;
            return nullptr;
        }
    }
};

class FactoryProducer {
public:
    AbsFactory* getFactory(std::string type){
        if("SHAPE" == type){
            return new ShapeFactory();
        } else if("COLOR" == type){
            return new ColorFactory();
        } else {
            return nullptr;
        }
    }
};

int main(){
   
    FactoryProducer factoryProducer;
    AbsFactory* shapeFactory = factoryProducer.getFactory("SHAPE");
    AbsFactory* colorFatctory = factoryProducer.getFactory("COLOR");

    Shape* cicle = shapeFactory->createShape(ShapeType::CIRCLE);
    cicle->setColor(colorFatctory->createColor(ColorType::RED));
    cicle->draw();

    Shape* rectange = shapeFactory->createShape(ShapeType::RECTANGE);
    rectange->setColor(colorFatctory->createColor(ColorType::BLUE));
    rectange->draw();

    delete rectange;
    delete cicle;
    delete colorFatctory;
    delete shapeFactory;

    return EXIT_SUCCESS;
}
```

### 建造模式

“使用生成器模式可避免 “重叠构造函数 （tele­scop­ing con­struc­tor）” 的出现。”

“当你希望使用代码创建不同形式的产品 （例如石头或木头房屋） 时， 可使用生成器模式”

“使用生成器构造组合树或其他复杂对象“

```cpp
#include <iostream>

class Car {
public:
    class CarBuilder;
    void setEngine(std::string engine) {
        this->_engine = engine;
    }
    void setSeats(int seats){
        this->_seats = seats;
    }
    void setGps(int gps){
        this->_gps = gps;
    }
    void run(){
        std::cout<< "Engine: " << _engine <<std::endl;
        std::cout<< "Seats: " << _seats <<std::endl;
        std::cout<< "GPS: " << _gps <<std::endl;
        std::cout<< this <<" the car is running" <<std::endl;
    }
private:
    //引擎
    std::string _engine;
    //座位
    int _seats;
    //GPS
    int _gps;
};

class Car::CarBuilder {
public:
    CarBuilder(){
        this->_car = new Car();
    }
    ~CarBuilder(){
        if(_car){
            delete _car;
        }
    }
    CarBuilder* reset(){
        if(_car){
            delete _car;
        }
        _car = new Car();
        return this;
    }
    CarBuilder* setEngine(std::string engine) {
        _car->setEngine(engine);
        return this;
    }
    CarBuilder* setSeatx(int seats) {
        _car->setSeats(seats);
        return this;
    }
    CarBuilder* setGps(int gps){
        _car->setGps(gps);
        return this;
    }
    Car* build(){
        return _car;
    }
private:
    Car* _car;
};

int main(){
    std::cout<< "builder." <<std::endl;
    
    Car::CarBuilder carBuilder;
    Car* car1 = carBuilder.setEngine("火山引擎")
                            ->setSeatx(5)
                            ->setGps(10)
                            ->build();
    car1->run();
    Car* car2 = carBuilder.reset()
                            ->setEngine("阿里引擎")
                            ->setSeatx(3)
                            ->setGps(20)
                            ->build();

    car2->run();

    Car* car3 = carBuilder.reset()->setEngine("abc")->build();
    car3->run();

    return EXIT_SUCCESS;
}
```

### 原型模式

“如果你需要复制一些对象， 同时又希望代码独立于这些对象所属的具体类， 可以使用原型模式。”

“如果子类的区别仅在于其对象的初始化方式， 那么你可以使用该模式来减少子类的数量。 别人创建这些子类的目的可能是为了创建特定类型的对象。”

```cpp
#include <iostream>
#include <vector>

template<typename T>
class IPrototype {
    virtual IPrototype<T>* clone() = 0;
};

class Child {
public:
    void print() {
        std::cout << "Child-->" << this <<std::endl;
    }
};

class Container : public IPrototype<Container> {
public:
    ~Container() {
        children.clear();
    }
    Container(std::string name){
        this->name = name;
    }
    std::string getName(){
        return name;
    }
    void addChild(const Child& child){
        children.push_back(child);
    }
    std::vector<Child> getChildren(){
        return children;
    }
    Container* clone() override {
        Container* prototype = new Container(name);
        prototype->children = this->children;
        return prototype;
    }
private:
    std::string name;
    std::vector<Child> children;
};

int main(){
    std::cout<< "prototype..." <<std::endl;

    Container container(" i am a container.");
    Child c1;
    Child c2;
    container.addChild(c1);
    container.addChild(c2);
    std::vector<Child> children = container.getChildren();
    std::cout << &container << container.getName() << std::endl;
    for(auto& item : children){
        item.print();
    }

    Container* prototype = container.clone();
    std::cout << prototype << prototype->getName() << std::endl;
    std::vector<Child> prototypeChildren = prototype->getChildren();
    for(auto& item : prototypeChildren){
        item.print();
    }
    if(prototype){
        delete prototype;
    }
    return EXIT_SUCCESS;
}
```

### 单例模式

“如果程序中的某个类对于所有客户端只有一个可用的实例， 可以使用单例模式。”

“如果你需要更加严格地控制全局变量， 可以使用单例模式。”

“抽象工厂、 生成器和原型都可以用单例来实现。”

```cpp
#include <iostream>
#include <thread>
#include <mutex>

class Singleton {
protected:
    static Singleton* instance;
    static std::mutex _lock;
public:
    static Singleton* getInstance() {
        //加锁 
        //std::lock_guard<std::mutex> lock(_lock); 如果注释下面一句，将会出现线程安全问题
        std::lock_guard<std::mutex> lock(_lock);
        if(!instance){
            instance = new Singleton();
        }
        return instance;
    }
    static int getCount() {
        return count++;
    }
    void doSomething() {
        std::cout << this << "--->doSomething()" <<std::endl;
    }
private:
    static int count;
    Singleton(){};//!!!!!!!!!!!!!important 必须要有实现或者添加 {}
    Singleton(Singleton& other) = delete;
    void operator=(const Singleton& other) = delete;
};

int Singleton::count = 0;
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::_lock;

Singleton* current;

void getInstance(){
    for(int i = 0; i < 10000; i++){
        Singleton* newInstance = Singleton::getInstance();
        if(current && current != newInstance){
            std::cout<< "\ndiff--->" << current << newInstance <<std::endl;
            throw "diff";
        }
        current = newInstance;
        current->doSomething();
        int count = Singleton::getCount();
        std::cout<< count <<std::endl;
    }
}

int main(){
    std::cout<< "singleton" <<std::endl;

    for(int i = 0; i < 6; i++){
        std::thread t(&getInstance);
        t.join();
    }

    delete current;

    return EXIT_SUCCESS;
}
```

## 结构型

### 适配器模式

“当你希望使用某个类， 但是其接口与其他代码不兼容时， 可以使用适配器类。”

“如果您需要复用这样一些类， 他们处于同一个继承体系， 并且他们又有了额外的一些共同的方法， 但是这些共同的方法不是所有在这一继承体系中的子类所具有的共性。”

```cpp
#include <iostream>
#include <string>
#include <exception>
#include <math.h>

/** 
 * 圆钉
 */
class RoundPeg {
public:
    RoundPeg(float r){
        this->radius = r;
    }
    float getRadius(){
        return radius;
    }
private:
    float radius;
};

/**
 * 圆孔
 */
class RoundHole {
public:
    RoundHole(float r){
        this->radius  = r;
    }
    void fit(RoundPeg& peg){
        if(radius < peg.getRadius()){
            std::string what("can not fit: ");
            std::cerr<< what + std::to_string(peg.getRadius()) + "--->" + std::to_string(radius) <<std::endl;
            return;
        }
        std::cout<< "fit success!" <<std::endl;
    }
private:
    /** 半径 */
    float radius;
};

/**
 * 方钉 
 */ 
class SquarePeg : public RoundPeg {
public:
    SquarePeg(float w, float h) : RoundPeg(sqrt(pow(w, 2) + pow(h, 2)) * 0.5f){ //对角线 * 0.5f 就是半径
        this->width = w;
        this->height = h;
    }
private:
    float width, height;
};

int main(){
    std::cout<< "adapter" <<std::endl;

    RoundPeg peg(0.8f);
    RoundHole hole(0.81f);
    hole.fit(peg);

    float width = 1.0f;
    float height = 1.3f;
    float r = sqrt(pow(width, 2) + pow(height, 2)) * 0.5f;
    std::cout<< "对角线的一半: half an djx---> " << r <<std::endl;
    SquarePeg sPeg(width, height);
    RoundHole hole2(0.81f);
    hole2.fit(sPeg);

    return EXIT_SUCCESS;
}
```

### 桥接模式

“如果你想要拆分或重组一个具有多重功能的庞杂类 （例如能与多个数据库服务器进行交互的类）， 可以使用桥接模式。”

“如果你希望在几个独立维度上扩展一个类， 可使用该模式。”

“如果你需要在运行时切换不同实现方法， 可使用桥接模式。”

```cpp
#include <iostream>

/**
* 设备 
 */
class Device{
public:
    void setVolume(float volume) {
        this->_volume = volume;
    }
    float getVolume() const {
        return _volume;
    }
    void setChannel(int channel) {
        this->_channel = channel;
    }
    int getChannel() const{
        return _channel;
    }
    void print(){
        std::cout<< this << " volume: " << _volume << " channel: " << _channel <<std::endl;
    }
private:
    float _volume = 10.0f;
    int _channel = 1;
};

/**
 * 遥控 
 */
class RemoteControl {
public:
    void setDevice(Device* device){
        this->_device = device;
    }
    void addVolume(){
        this->_device->setVolume(_device->getVolume() + 12.0f);
    }
    void subVolume(){
        this->_device->setVolume(_device->getVolume() - 12.0f);
    }
    void addChannel(){
        this->_device->setChannel(_device->getChannel() + 1);
    }
    void subChannel(){
        this->_device->setChannel(_device->getChannel() - 1);
    }
private:
    Device* _device;
};


int main(){

    std::cout<< "bridge.." <<std::endl;

    Device tv;
    tv.print();
    RemoteControl tvRc;
    //控制tv
    tvRc.setDevice(&tv);
    tvRc.addChannel();
    tvRc.addChannel();
    tvRc.addVolume();
    tvRc.addVolume();
    tvRc.subVolume();
    tv.print();

    Device radio;
    radio.print();
    //控制第二个设备
    tvRc.setDevice(&radio);
    tvRc.addVolume();
    tvRc.addChannel();
    radio.print();

    return EXIT_SUCCESS;
}
```

### 组合模式

“如果你需要实现树状对象结构， 可以使用组合模式”

“如果你希望客户端代码以相同方式处理简单和复杂元素， 可以使用该模式。”

```cpp
#include <iostream>
#include <list>

class IComponent {
public:
    virtual void onInit() = 0;
    virtual void onUpdate() = 0;
};

class RootCmponent : public IComponent {
public:
    virtual ~RootCmponent(){
        for(auto& item : componentList){
            if(item == this){
                continue;
            }
            delete item;
        }
        std::list<IComponent*> swap;
        componentList.swap(swap);
        componentList.clear();
    }
    void add(IComponent* component){
        componentList.push_back(component);
    }

    void remove(IComponent* component){
        componentList.remove(component);
    }

    virtual void onInit() {
        for(auto& item : componentList){
            if(item == this){
                continue;
            }
            item->onInit();
        }
    }

    virtual void onUpdate(){
        for(auto& item : componentList){
            if(item == this){
                continue;
            }
            item->onUpdate();
        }
    }
private:
    std::list<IComponent*> componentList;
};

class MeshComponent : public IComponent {
public:
    virtual void onInit() override {
        std::cout<< this << "-->MeshComponent.onInit()" <<std::endl;
    }
    virtual void onUpdate() override {
        std::cout<< this << "-->MeshComponent.onUpdate()" <<std::endl;
    }
};

class TransformComponent : public IComponent {
public:
    virtual void onInit() override {
        std::cout<< this << "-->TransformComponent.onInit()" <<std::endl;
    }
    virtual void onUpdate() override {
        std::cout<< this << "-->TransformComponent.onUpdate()" <<std::endl;
    }
};

class Actor{
public:
    Actor(){
        _rootComponent = new RootCmponent();
    }
    ~Actor(){
        if(_rootComponent){
            delete _rootComponent;
        }
    }
    void addComponent(IComponent* component){
        _rootComponent->add(component);
    }
    void removeComponent(IComponent* component){
        _rootComponent->remove(component);
        delete component;
    }
    virtual void onInit(){
        _rootComponent->onInit();
    }
    virtual void onUpdate(){
        _rootComponent->onUpdate();
    }
private:
    RootCmponent* _rootComponent;
};

int main(){
    std::cout<< "composite." <<std::endl;

    IComponent* meshCpt = new MeshComponent();
    IComponent*  transformCpt = new TransformComponent();
    Actor actor;
    actor.addComponent(meshCpt);
    actor.addComponent(transformCpt);
    actor.onInit();

    for(int i = 0; i < 100; i++){
        if(i == 97){
            //actor.removeComponent(meshCpt);
            actor.removeComponent(transformCpt);
        }
        std::cout<< "No." << i << ":" <<std::endl;
        actor.onUpdate();
    }

    return EXIT_SUCCESS;
}
```

### 装饰者模式

“如果你希望在无需修改代码的情况下即可使用对象， 且希望在运行时为对象新增额外的行为， 可以使用装饰模式。”

“如果用继承来扩展对象行为的方案难以实现或者根本不可行， 你可以使用该模式。”

发消息例子：

```cpp
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
```

文件处理例子

```cpp
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <regex>

class FileWriteUtil {
public:
	void write(std::string& fileName, std::string& data){
		//执行写入
		std::ofstream osm(fileName, std::ios::out);
		if(!osm){
			throw "Write file fail..";
		}
        
        osm << data;

		osm.flush();
		osm.close();
	}
};

class FileWriteWrapper {
public:
    virtual void write(std::string& fileName, std::string& data) = 0;
};

//加密
class FileEncryWrapper {
public:
    FileEncryWrapper(FileWriteUtil* fileUtil){
        this->_fileUtil = fileUtil;
    }
    void write(std::string& fileName, std::string& data){
        //加密
        std::cout << _fileUtil << "执行加密" << std::endl;
        reverse(data.begin(), data.end());
    }
    FileWriteUtil* getFileWriteUtil() const{
        return _fileUtil;
    }
private:
    FileWriteUtil* _fileUtil;
};


//压缩
class FileCompressWrapper : public FileWriteWrapper {
public:
    //先加密-后压缩
    FileCompressWrapper(FileEncryWrapper* encryWrapper) {
        this->_encryWrapper = encryWrapper;
    }
    void write(std::string& fileName, std::string& data) {
        this->_encryWrapper->write(fileName, data);
        std::cout << "执行压缩"  << std::endl;
        data = std::regex_replace(data, std::regex("\\s+"), "");
        this->_encryWrapper->getFileWriteUtil()->write(fileName, data);
     }

private:
    FileEncryWrapper* _encryWrapper;
};

int main(){

	std::cout << "wrapper2"  << std::endl;

    std::string fileName = "hello.abc";
    std::string data = "  \n\n  line 1\nline2\nthis is wrapper pattern demo.   \n      ";
    
	FileWriteUtil fileUtil;
	fileUtil.write(fileName, data);
	
    FileEncryWrapper* encryWrapper = new FileEncryWrapper(&fileUtil);
    FileCompressWrapper* compressWrapper = new FileCompressWrapper(encryWrapper);    
    compressWrapper->write(fileName, data);

    delete encryWrapper;
    delete compressWrapper;    

	return EXIT_SUCCESS;
}
```


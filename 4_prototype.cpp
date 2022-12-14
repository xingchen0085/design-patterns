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
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
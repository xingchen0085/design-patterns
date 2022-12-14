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

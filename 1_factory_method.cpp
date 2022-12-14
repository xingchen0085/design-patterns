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
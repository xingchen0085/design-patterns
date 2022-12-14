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

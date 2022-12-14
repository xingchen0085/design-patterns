#include <iostream>

enum ShapeType {
    CIRCLE, RECTANGLE
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

class Rectangle : public Shape {
public:
    virtual void draw() override {
        std::cout<< "Rectangle." <<std::endl;
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
        } else if(type == ShapeType::RECTANGLE){
            return new Rectangle();
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

    Shape* rectangle = shapeFactory->createShape(ShapeType::RECTANGLE);
    rectangle->setColor(colorFatctory->createColor(ColorType::BLUE));
    rectangle->draw();

    delete rectangle;
    delete cicle;
    delete colorFatctory;
    delete shapeFactory;

    return EXIT_SUCCESS;
}
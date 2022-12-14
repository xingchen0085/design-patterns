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
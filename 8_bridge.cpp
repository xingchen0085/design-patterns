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
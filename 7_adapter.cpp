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
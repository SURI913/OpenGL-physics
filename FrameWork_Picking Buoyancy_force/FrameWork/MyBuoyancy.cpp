#include "MyBuoyancy.h"
#include <iostream>


//물체의 부피
MyBuoyancy::MyBuoyancy(double maxDepth, double volume, double waterHeight, double liquidDensity)
{
    this->maxDepth = maxDepth;
    this->volume = volume;
    this->waterHeight = waterHeight;
    this->liquidDensity = liquidDensity;
}

void MyBuoyancy::updateForce(Particle* particle, double duration)
{
    Vector3 force;

    Vector3 pos;
    particle->getPosition(&pos); //위치

    if (pos.y-3.0 - maxDepth > waterHeight) { //물 밖에 있을때
        force = Vector3::GRAVITY;    //중력
    }
    else if (pos.y-3.0 + maxDepth < waterHeight) {  //완전히 잠겼을 때
        //vp
        force = Vector3(0, (volume * liquidDensity), 0);
    }
    else {
        double d = (pos.y-3.0 - waterHeight - 3.0f) / (3.0f * 2);   //그 외 상태 
        force = Vector3(0, (volume * liquidDensity) * d, 0);
    }
    particle->addForce(force);
}
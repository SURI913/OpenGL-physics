#pragma once
#include "pfgen.h"
using namespace cyclone;
class MyAnchoredSpring : public ParticleForceGenerator
{
protected:
    Vector3 anchor; /** 스프링의 고정 위치. */
    double springConstant; /** 스프링 상수. */
    double restLength; /** rest길이. */
public:
    MyAnchoredSpring();
    MyAnchoredSpring(Vector3 anchor, double springConstant, double restLength);
    Vector3 getAnchor() const { return anchor; } //엥커 위치 반환 함수
    void init(Vector3 anchor, double springConstant, double restLength);  //값 설정 함수
    void updateForce(Particle* particle, real duration);
};
#pragma once

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "core.h" 
#include "particle.h" 
#include "MyParticleBuoyancy.h"
using namespace cyclone;

class Mover {
public:
	Mover();	//p초기위치
	~Mover() { };

	float size;
	float damping;
	float m_mass;

	MyBuoyancy*  m_buoyancy;

	Vector3 m_position;
	Vector3 m_oldPosition;
	Vector3 m_velocity;
	Vector3 m_acc;
	Particle* m_particle;


	void update(float duration);
	void stop();
	void draw(int shadow);
	void checkEdges();
	//draw somthing

};
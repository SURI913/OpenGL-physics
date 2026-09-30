#pragma once

#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "core.h" 
#include "particle.h" 
#include "Myspring.h"
using namespace cyclone;

class Mover {
public:
	Mover(Vector3& p);	//p초기위치
	~Mover() { };

	float size;

	Myspring*  m_spring;
	ParticleGravity* m_gravity;
	ParticleDrag* m_drag;
	ParticleForceRegistry* m_forces;

	Vector3 m_position;
	Vector3 m_oldPosition;
	Vector3 m_velocity;
	Vector3 m_acc;
	Particle* m_particle;


	void update(float duration);
	void stop();
	void draw(int shadow);
	void checkEdges();
	void setConnection(Mover* a);	//a 연결되는 상대방 mover
	//draw somthing

};
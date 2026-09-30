#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "core.h" 
#include "particle.h" 
using namespace cyclone;

class Mover {
public:
	Mover();
	~Mover() { };
	
	float size;
	float damping;
	float m_mass;
	Vector3 m_position;
	Vector3 m_velocity;
	Vector3 m_acc;
	//Particle* m_particle;

	void update(float duration);
	void stop();
	
	void draw(int shadow);

	void checkEdges();
	//draw somthing
};
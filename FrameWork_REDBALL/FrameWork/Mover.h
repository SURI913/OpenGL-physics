#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "core.h" 

class Mover {
public:
	Mover() { };
	~Mover() { };
	
	cyclone::Vector3 m_position;

	void update(float duration);
	void stop();
	
	void draw(int shadow);

	//draw somthing
};
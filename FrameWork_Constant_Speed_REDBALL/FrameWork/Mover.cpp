#include "Mover.h"
#include "MyGlWindow.h"

using namespace cyclone;


Mover :: Mover() {
	m_position.x = 0;
	m_position.y = 3;
	m_position.z = 0;
};

void Mover:: update(float duration) {
	damping = 0.999;
	m_mass = 1.0;

	Vector3 velocity(5, 0, 0);
	m_position += velocity * duration;//위치업데이트

	if (m_position.x > 100) m_position.x = 0;
}
void Mover:: stop() {

}
void Mover:: draw(int shadow) {

	float size = 2.0;
	if (shadow)
	{
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glColor3f(0.1f, 0.1f, 0.1f); //그림자 색상
		glutSolidSphere(size, 30, 30); //만드는것
	}
	else
	{
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glColor3f(1.0f, 0.0f, 0.0f); // 오브젝트 색상
		glutSolidSphere(size, 30, 30); //만드는것
	}
	
}
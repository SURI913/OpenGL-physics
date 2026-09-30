#include "Mover.h"
#include "MyGlWindow.h"

using namespace cyclone;

void Mover:: checkEdges() {
	float MAX_xVal = 100.0f - size;
	
	if (m_position.y < size && m_position.x > MAX_xVal) { //완전히 멈출때
		m_position = Vector3(MAX_xVal, size, m_position.z);
		m_velocity = Vector3(m_velocity.x * -1.0f, m_velocity.y * -1.0f, m_velocity.z);
	}
	else if (m_position.y <= size) {	//바닥에 닿았다면  튀어오르게
		m_position = Vector3(m_position.x, size, m_position.z);
		m_velocity = Vector3(m_velocity.x, m_velocity.y * -1.0f, m_velocity.z); //속도, 방향 변경
	}
	else if (m_position.x >= MAX_xVal)	//벽에 닿았다면 튀어오르게
	{
		m_position = Vector3(MAX_xVal, m_position.y, m_position.z);
		m_velocity = Vector3(m_velocity.x * -1.0f, m_velocity.y, m_velocity.z);
	}
}

Mover :: Mover() {

	size = 2.0f; //공 크기

	m_position = Vector3(5, 20, 0);
	m_velocity = Vector3(0, 0, 0);
	m_acc = Vector3(0, -9.8, 0);
	m_mass = 1.0f;
	damping = 0.999f;

};

void Mover:: update(float duration) {
	Vector3 F(0, 0, 0);	//f =0
	Vector3 a = m_acc;	//a' = a
	a = a + F * (1 / m_mass);	
	m_velocity = m_velocity + a * duration;
	m_velocity = m_velocity * pow(damping, duration);
	m_position = m_position + m_velocity * duration;
	
	checkEdges();
}
void Mover:: stop() {

}
void Mover:: draw(int shadow) {
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
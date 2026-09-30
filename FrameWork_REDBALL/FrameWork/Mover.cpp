#include "Mover.h"
#include "MyGlWindow.h"

void Mover:: update(float duration) {
	
}
void Mover:: stop() {

}
void Mover:: draw(int shadow) {
	float size = 2.0;
	if (shadow)
	{
		glTranslatef(0, 3, 0);
		glColor3f(0.1f, 0.1f, 0.1f); //그림자 색상
		glutSolidSphere(size, 30, 30); //만드는것
	}
	else
	{
		glTranslatef(0, 3, 0);
		glColor3f(1.0f, 0.0f, 0.0f); // 오브젝트 색상
		glutSolidSphere(size, 30, 30); //만드는것
	}
	
}
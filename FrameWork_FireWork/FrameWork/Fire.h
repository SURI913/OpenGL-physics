#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "core.h"
#include "particle.h"
#include <deque>
#include <vector>
#include "FireworksRule.h"

using namespace std;

class Fire {
public:
	Fire(int type, int creatCount);	//type을 가진 fire생성 (0 = Init Fire, 1 = Child Fire)
	~Fire();

	
	float m_size;	//그리기 위한 Fire의 크기
	int m_type;		//Fire의 타입 (set in 생성자)
	cyclone::real m_age;	//Fire의 현재
	cyclone::Particle* m_particle;
	FireWorksRule* m_rule;	//어떤 룰에 적용 받나
	cyclone::Vector3 m_color;	//Fire의 색상
	deque<cyclone::Vector3> m_history;	//위치 history저장

	bool update(float duration);
	void stop();
	void draw(int shadow);
	void drawHistory();
	void setRule(FireWorksRule* r);	//트정 률을 설정
	void putHistory();	//현재 위치를 m_histroy에 저장
};

#include "Fire.h"
#include <vector>

using namespace std;
class Fireworks {
public:
	Fireworks();
	~Fireworks();

	vector<Fire*> fireworks;	//Fire=저장
	int FireCountInit;	//FireInit 생성 갯수만큼 룰 변경
	int FireCountChild;	//FireChild 생성 갯수만큼 룰 변경

	void update(float duration);	//Fire의 생성/ 소멸/업데이트
	void creat();	//init Fire생성
	void creat(Fire* parent);	//Child Fire 생성
	void draw(int shadow);	//그리기
	int getSize();
	FireWorksRule m_rule[2];	//룰
};
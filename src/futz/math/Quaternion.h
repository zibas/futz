#ifndef QUATERNION_H_
#define QUATERNION_H_

class Quaternion {
public:
	float x, y, z, w;
	Quaternion();
	void SetAxis(double, float, float, float);
	void SetFromEuler(float, float, float);
	void Reset();
	void Print();
	bool IsNAN();
	Quaternion operator *(Quaternion q);
	virtual ~Quaternion();
};

#endif

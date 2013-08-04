#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "../math/Vector3.h"
#include "../math/Matrix4.h"
#include "../math/Quaternion.h"

class Transform {
	private:
	public:
		void RecalculateMatrix();
		void* node;

		Vector3 position;
		Vector3 euler;

		double scale;

		Matrix4 matrix;
		Quaternion rotation;

		Transform();
		void SetOrbit(Vector3, double, Quaternion);
		void SetPosition(double, double, double);
		void SetRotation(double, double, double);
		void SetScale(double);
		void AddRelativeTranslation(double, double, double);
		void LookAt(Vector3);
		~Transform();
		void Print();
};

#endif

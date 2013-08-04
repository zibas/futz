
#ifndef ASTEROIDS_H_
#define ASTEROIDS_H_

#include <stdlib.h>
#include <time.h>
#include "core/Node.h"
#include "models/Model.h"
#include "math/Matrix4.h"
class Asteroids {
	public:
		Model* model;
		Node* asteroids[100];
		Vector3* rotations[100];

		int count;

		void Start();
		virtual ~Asteroids();
		void Update();	
};

#endif

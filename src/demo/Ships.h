
#ifndef SHIPS_H_
#define SHIPS_H_

#include <stdlib.h>
#include <time.h>
#include "core/Node.h"
#include "models/Model.h"
#include "math/Matrix4.h"

class Ships {
	public:
		Model* model;
		Node* ships[25];
		double rotations[25];
		Vector3 centers[25];
		double radii[25];

		int count;

		void Start();
		virtual ~Ships();
		void Update();	
};

#endif

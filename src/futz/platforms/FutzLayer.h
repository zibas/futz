/*
 * FutzLayer.h
 *
 *  Created on: Nov 3, 2010
 *      Author: ziba
 */

#ifndef FUTZLAYER_H_
#define FUTZLAYER_H_
#include "SystemLayerBase.h"


class FutzLayer: public SystemLayerBase {
	
public:
	FutzLayer();
	void Initialize(int argc, char** argv);
	virtual ~FutzLayer();
};

#endif /* FUTZLAYER_H_ */

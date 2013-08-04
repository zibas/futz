
#ifndef FUTZIOS_H_
#define FUTZIOS_H_
#include "SystemLayerBase.h"


class FutzIOS: public SystemLayerBase {
	
public:
	FutzIOS();
	void Initialize(int argc, char** argv);
	virtual ~FutzIOS(){};
	
	string ResolveFilename(string);
	void PostUIInit();
};

#endif /* FUTZIOS_H_ */
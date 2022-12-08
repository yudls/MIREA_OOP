#ifndef COBJECT_H
#define COBJECT_H

#include "cbase.h"
	
class Cobject: public CBase {
public:
	Cobject(CBase* parent, std::string name);
};

#endif // COBJECT_H
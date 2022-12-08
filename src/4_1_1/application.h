#ifndef APPLICATION_H
#define APPLICATION_H

#include "cbase.h"

class Application: public CBase {
	CBase* tempParent;
	CBase* tempChild;
public:
	Application(CBase* parent, std::string name="Application");
	void buildTree();
	int execute();
};

#endif // APPLICATION_H
#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>

#include "cobject.h"
#include "cbase.h"
#include "two.h"
#include "three.h"
#include "four.h"
#include "five.h"
#include "six.h"

class Application: public CBase {
public:
	Application(CBase* parent, std::string name="Application");
	void buildTree();
	int execute();
};

#endif // APPLICATION_H
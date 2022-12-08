#include "application.h"
#include "cobject.h"
#include <iostream>

Application::Application(CBase* parent, std::string name): CBase(parent, name){}

void Application::buildTree() {
	std::string parentName, childName;
	std::cin >> parentName;
	setName(parentName);
	tempParent = this;
	do {
	std::cin >> parentName >> childName;
	if(parentName == childName) return;
	if(parentName != tempParent -> getName()) {
		if(parentName == tempChild -> getName())
			tempParent = tempChild;
		else continue;
	}
	tempChild = new Cobject(tempParent, childName);
	}
	while(true);
}

int Application::execute(){
	std::cout << getName();
	printNames();
	return 0;
}
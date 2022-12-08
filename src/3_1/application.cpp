#include "application.h"

Application::Application(CBase* parent, std::string name): CBase(parent, name){}

void Application::buildTree() {
	std::string parentName, childName;
	int classNum;
	std::cin >> parentName;
	this->setName(parentName);
	while(true) {
		std::cin >> parentName;
		if (parentName == "endtree") return;
		std::cin >> childName >> classNum;
		switch(classNum) {
			case 2:
				new Two(this->findByName(parentName), childName);
				break;
			case 3:
				new Three(this->findByName(parentName), childName);
				break;
			case 4:
				new Four(this->findByName(parentName), childName);
				break;
			case 5:
				new Five(this->findByName(parentName), childName);
				break;
			case 6:
				new Six(this->findByName(parentName), childName);
				break;
			default:
				break;
		}
	}
}

int Application::execute() {
	std::cout << "Object tree" << '\n';
	this->printTree();
	while(!std::cin.eof()) {
		std::string name;
		int readiness;
		std::cin >> name >> readiness;
		this->findByName(name)->setReadiness(readiness);
	}
	std::cout << '\n' << "The tree of objects and their readiness" << '\n';
	this-> printTreeWithReadiness();
	return 0;
}

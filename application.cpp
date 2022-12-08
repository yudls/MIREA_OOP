#include "application.h"
	
Application::Application(CBase* parent, std::string name): CBase(parent, name){}
	
void Application::buildTree() {
	std::string parentPath, childName;
	CBase* tmp;
	int classNum;
	std::cin >> parentPath;
	this->setName(parentPath);
	while(true) {
		std::cin >> parentPath;
		if (parentPath == "endtree") return;
		std::cin >> childName >> classNum;
		tmp = this->findByPath(parentPath);
		if(!tmp) {
			std::cout << "Object tree" << '\n';
			this->printTree();
			std::cout << "\nThe head object " << parentPath << " is not found";
			exit(1);
		}
		switch(classNum) {
			case 2:
				new Two(tmp, childName);
				break;
			case 3:
				new Three(tmp, childName);
				break;
			case 4:
				new Four(tmp, childName);
				break;
			case 5:
				new Five(tmp, childName);
				break;
			case 6:
				new Six(tmp, childName);
				break;
			default:
				break;
		}
	}
}

int Application::execute() {
	std::cout << "Object tree" << '\n';
	this->printTree();
	std::string command, path;
	CBase* setted = this;
	std::cin >> command;
	if(command != "END")
		std::cout << '\n';
	while(command != "END") {
		if(command == "SET") {
			std::cin >> path;
			if(setted->findByPath(path)) {
				setted = setted->findByPath(path);
				std::cout << "Object is set: "<<setted->getName();
			}
			else {
				std::cout<<"Object is not found: "<< setted->getName()<<" "<<path;
			}
		}
		if(command == "FIND") {
			std::cin >> path;
			if(setted->findByPath(path))
				std::cout << path << "     Object name: " << setted->findByPath(path)->getName();
			else std::cout << path << "     Object is not found";
		}
		std::cin >> command;
		if(command!="END") std::cout << '\n';
	}
	return 0;
}

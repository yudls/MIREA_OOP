#include "cbase.h"
#include <iostream>

CBase::CBase(CBase* parent, std::string name): parent(parent), name(name), readiness(0) {
	if(parent != nullptr )
		this->parent->children.push_back(this);
}

void CBase::setName(std::string name) {
	this->name = name;
}

std::string CBase::getName() {
	return this->name;
}

void CBase::setReadiness(int readiness) {
	if(readiness == 0) {
		this->readiness = readiness;
		for(CBase* child : children)
			child->setReadiness(readiness);
	}
	else {
		CBase* root = this;
		while (root->parent != nullptr) {
			if (root->parent->readiness == 0) {
				this->readiness = 0;
				return;
			}
			root = root-> parent;
		}
		this->readiness = readiness;
	}
}

CBase* CBase::findByName(std::string name) {
	if (this->name == name) return this;
	CBase* root = this;
	while(root->parent != nullptr) {
		if(root->parent->name == name) return root->parent;
		root = root->parent;
	}
	return root->getChild(name);
}

CBase* CBase::findByPath(std::string path) {
	if(path == "") return nullptr;
	
	int state = 0; // состояние чтения пути
	/*
	state == 0 - считывается первый символ
	state == 1 - первый символ '/' - корневой объект
	state == 2 - первый символ '.' - текущий объект
	state == 3 - первый символ не '/', и не '.'
	state == 4 - если первые два символа "//" - поиск объекта по уникальному имени от корневого
	state == 5 - если первый символ '/', а следующий не '/' - абсолютная координата от корневого объекта
	state == 6 - если встретилось '/' после имени объекта - относительная координата от текущего
	*/
	for(size_t i=0; i<path.size(); ++i) {
		char ch = path[i];
		switch(state) {
			case 0: {
				if(ch == '/') state = 1;
				else if(ch == '.') state = 2;
				else state = 3;
				break;
			}
			case 1: {
				if(ch == '/') state = 4;
				else state = 5;
				break;
			}
			case 2: {
				return nullptr;
			}
			case 3: {
				if(ch == '/') state = 6;
				break;
			}
			case 4: {
				return findByName(path.substr(2));
			}
			case 5: {
				return getRoot()->findByPath(path.substr(1));
			}
			case 6: {
				CBase* tmp = this->childExists(path.substr(0, i-1));
				if(tmp) {
					return tmp->findByPath(path.substr(i));
				}
				return nullptr;
			}
		}
	}
	
	if(state == 1)
		return getRoot();
	if(state == 2)
		return this;
	if(state == 3)
		return childExists(path);
	return nullptr;
}

CBase* CBase::childExists(std::string name) {
	for(size_t i=0; i<children.size(); ++i) {
		if(children[i]->name == name){
			return children[i];
		}
	}
	return nullptr;
}

CBase* CBase::getChild(std::string name) {
	for(CBase* child : children)
		if(child->name == name) return child;
	for(CBase* child : children) {
		if((child->children).size() > 0) {
			CBase* tempObj = child->getChild(name);
			if (tempObj != nullptr)
				return tempObj;
		}
	}
	return nullptr;
}

CBase* CBase::getRoot() {
	CBase* root = this;
	while (root->parent != nullptr)
		root = root->parent;
	return root;
}


void CBase::setParent(CBase* newParent) {
	CBase* oldParent = this->parent;
	if (oldParent == nullptr || newParent == nullptr) return;
	std::vector<CBase*> oldPatherChildren = oldParent->children;
	for (size_t i=0; i < oldPatherChildren.size(); ++i)
		if(oldPatherChildren[i] == this) {
			oldPatherChildren.erase(oldPatherChildren.begin()+i);
			break;
		}
	this->parent = newParent;
	parent->children.push_back(this);
}

void CBase::printTree(int level, bool readiness) {
	if (parent == nullptr) {
		std::cout << name;
		std::cout << (readiness ? ((bool)(this->readiness) ? " is ready" : " is not ready") : "");
	}
	for (CBase* child : children) {
		std::cout << '\n' << std::string(4*level, ' ') << child->name;
		std::cout << (readiness ? ((bool)child->readiness ? " is ready" : " is not ready") : "");
		child->printTree(level +1, readiness);
	}
}

void CBase::printTreeWithReadiness() {
	this->printTree(1, true);
}

CBase::~CBase() {
	for(size_t i=0; i < children.size(); ++i)
		delete children[i];
}
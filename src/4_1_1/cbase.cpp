#include "cbase.h"
#include <iostream>

CBase::CBase(CBase* parent, std::string name) {
	this->parent = parent;
	this->name = name;
	if(parent != nullptr)
		this->parent->children.push_back(this);
}

void CBase::setName(std::string name) {
	this->name = name;
}

std::string CBase::getName() {
	return this->name;
}

void CBase::setState(int state) {
	this->state = state;
}

int CBase::getState() {
	return this->state;
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

void CBase::printNames() {
	if(children.empty()) return;
	std::cout << "\n" << name;
	childrenIterator = children.begin();
	while(childrenIterator != children.end()) {
	std::cout << "  " << (*(*childrenIterator)).getName();
	childrenIterator++;
	}
	childrenIterator--;
	(*childrenIterator)->printNames();
}

CBase::~CBase() {
	for(size_t i=0; i < children.size(); ++i)
		delete children[i];
}
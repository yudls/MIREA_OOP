#include "cbase.h"
#include <iostream>

CBase::CBase(CBase* parent, std::string name): parent(parent), name(name), readiness(0) {
	if(parent != nullptr)
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

CBase* CBase::findByName(std::string name, CBase* currentRoot) {
	CBase* root;
	if(currentRoot == nullptr)
		if(this->parent != nullptr)
			root = this->getRoot();
		else
			root = this;
	else
		root = currentRoot;
	if(root->name == name) return root;
	for(CBase* child : root->children)
		if(child->name == name) return child;
	for(CBase* child : root->children) {
		if((child->children).size() > 0) {
			root = child;
			CBase* tempRoot = child->findByName(name, child);
			if (tempRoot != nullptr)
				return tempRoot;
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
		std::cout << readiness ? ((bool)child->readiness ? " is ready" : " is not ready") : "";
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
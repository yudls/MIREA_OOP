#ifndef CBASE_H
#define CBASE_H

#include <string>
#include <vector>

class CBase {
private:
	CBase* getRoot();
	std::string name;
	CBase* parent;
	int readiness;
	std::vector<CBase*> children;
public:
	CBase(CBase* parent, std::string name="Base");
	void setName(std::string name);
	std::string getName();
	void setReadiness(int readiness);
	void setParent(CBase* parent);
	CBase* getParent();
	CBase* findByName(std::string name, CBase* currentRoot=nullptr);
	void printTree(int level=1, bool readiness=false);
	void printTreeWithReadiness();
	~CBase();
};

#endif // CBASE_H
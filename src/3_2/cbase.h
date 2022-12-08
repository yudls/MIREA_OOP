#ifndef CBASE_H
#define CBASE_H

#include <string>
#include <vector>

class CBase {
private:
	CBase* parent;
	std::string name;
	int readiness;
	std::vector<CBase*> children;
	CBase* getRoot();
public:
	CBase(CBase* parent, std::string name="Base");
	void setName(std::string name);
	std::string getName();
	void setReadiness(int readiness);
	void setParent(CBase* parent);
	CBase* getParent();
	CBase* getChild(std::string name);
	CBase* findByName(std::string name);
	CBase* childExists(std::string name);
	CBase* findByPath(std::string path);
	void printTree(int level=1, bool readiness=false);
	void printTreeWithReadiness();
	~CBase();
};

#endif // CBASE_H
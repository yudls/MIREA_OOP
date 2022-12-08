#ifndef CBASE_H
#define CBASE_H

#include <string>
#include <vector>

class CBase {
private:
	std::string name;
	CBase* parent;
	int state;
	std::vector<CBase*> children;
	std::vector <CBase*>::iterator childrenIterator;
public:
	CBase(CBase* parent, std::string name="Base");
	void setName(std::string name);
	std::string getName();
	void setState(int state);
	int getState();
	void setParent(CBase* parent);
	CBase* getParent();
	void printNames();
	~CBase();
};

#endif // CBASE_H
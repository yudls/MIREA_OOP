#include "application.h"

	
int main() {
	
	Application root(nullptr);
	root.buildTree();
	return root.execute();
}

#ifndef POLYNODE_H_
#define POLYNODE_H_

class PolyNode {

public:
	// Attributes
	int deg;
	int coeff;
	PolyNode* next;

	// Constructor
	PolyNode(int d, int c, PolyNode* n) {
		deg = d;
		coeff = c;
		next = n;
	}
};

#endif /* POLYNODE_H_ */

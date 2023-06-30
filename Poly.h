#ifndef POLY_H_
#define POLY_H_

#include "PolyNode.h"
#include <vector>
#include <string>
#include <map>


class Poly {

private:
	PolyNode* head = NULL;

public:
	// Constructors & Destructors
	Poly();
	Poly(const std::string& poly);
	Poly(const std::vector<int>& deg, const std::vector<double>& coeff);
	~Poly();

	// Methods
	std::map<int, int> parsePoly(const std::string& poly);
	void addMono(int i, double c);
	void addPoly(const Poly& p);
	void multiplyMono(int i, double c);
	void multiplyPoly(const Poly& p);
	void duplicate(Poly& outputPoly);
	int getDegree();
	int getTermsNo();
	double evaluate(double x);
	std::string toString();

	// used for testing
	PolyNode* getHead() {
		return head;
	};
};

#endif /* POLY_H_ */

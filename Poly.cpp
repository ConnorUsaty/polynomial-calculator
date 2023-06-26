#include "Poly.h"

using namespace std;


Poly::Poly()
{
	// Creates dummy header
	head = new PolyNode(-1,0,NULL);
}


Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)
{
	int length = deg.size();

	// Dummy header
	head = new PolyNode(-1,0,NULL);

	// Pointer to iterate through
	PolyNode* p = head;

	// Iterate through both lists creating all nodes
	for (int i = 0; i < length; i++) {
		p->next = new PolyNode(deg[i],coeff[i],NULL);
		p = p->next;
	}
}


Poly::~Poly()
// Destructor
{
	// Pointer to iterate through
	PolyNode* p = head->next;

	// Delete all nodes except dummy header
	while (p != NULL) {
		PolyNode* t = p;
		p = p->next;
		delete t;
	}

	// Delete ptr
	delete p;
}


void Poly::addMono(int i, double c)
// O(n) at max it loops through LL once
// O(1) uses a constant amount of memory
// Memory use is not dependent on size of input
{
	if (c == 0) {
		return;
	}

	PolyNode* current = head->next;
	PolyNode* prev = head;

	while (current != NULL) {

		// If matching deg found add coeffs together
		if (current->deg == i) {
			current->coeff += c;

			// Delete term is it ends up with a coeff of 0
			if(current->coeff == 0) {
				prev->next = current->next;
				delete current;
			}

			return;
		}

		// If current deg is lower then this input term add it before
		else if (current->deg < i) {
			prev->next = new PolyNode(i,c,current);
			return;
		}

		else if (current->deg > i) {
			prev = prev->next;
			current = current->next;
		}
	}

	prev->next = new PolyNode(i,c,NULL);
}


void Poly::addPoly(const Poly& p)
// O(n^2) time; Loops through LL once
// O(1) space; Not dependent on size of input
{
	// Pointer to iterate through
	PolyNode* current = p.head->next;

	// Add each term of p to THIS poly
	while (current != NULL) { //O(n)
		addMono(current->deg, current->coeff); // 1 to n summation = O(n^2)
		current = current->next;
	}
}


void Poly::multiplyMono(int i, double c)
// O(n) time; Loops through LL once
// O(1) space; Memory use not dependent on input size
{
	if (c == 0) {
		head->next = NULL;
		return;
	}

	PolyNode* p = head->next;

	// Multiplies each term by the input term
	while (p != NULL) {
		p->deg += i;
		p->coeff *= c;
		p = p->next;
	}
}


void Poly::multiplyPoly(const Poly& p)
// O(n^2 * m^2) or O(n^4) time complexity
// O(n*m) or O(n^2) space for resultPoly where n is terms in THIS and m is terms of p
{
    if (p.head->next == NULL || head->next == NULL) {
        head->next = NULL;
        return;
    }

    Poly resultPoly;
    PolyNode* p1 = head->next;
    PolyNode* p2 = p.head->next;

    // Iterate through all terms of THIS poly
    while (p1 != NULL) { // O(n)

    	// Reset p pointer to start of LL and iterate through
        p2 = p.head->next;
        while (p2 != NULL) { // O(n)

        	// Add product of these two terms to the result
        	// Creates new PolyNode for each term and adds to resultPoly
            resultPoly.addMono(p1->deg + p2->deg, p1->coeff * p2->coeff); // 1 to n^2 summation = O(n^4)
            p2 = p2->next;
        }

        p1 = p1->next;
    }

    // Delete the original Poly
    PolyNode* oldhead = head->next;
	while (oldhead != NULL) {
		PolyNode* t = oldhead;
		oldhead = oldhead->next;
		delete t;
	}
	delete oldhead;

	// Copy result onto THIS poly
    resultPoly.duplicate(*this);
}


void Poly::duplicate(Poly& outputPoly)
// O(n) time; Loops through LL once
// O(n) space; Creates new LL with n PolyNodes
{
	outputPoly.head = new PolyNode(-1,0,NULL);

	PolyNode* p = head->next;
	PolyNode* pCopy = outputPoly.head;

	// Copies each term from THIS poly into the outputPoly
	while (p != NULL) {
		pCopy->next = new PolyNode(p->deg,p->coeff,NULL);
		pCopy = pCopy->next;
		p = p->next;
	}
}


int Poly::getDegree()
// O(1) time; Not dependent on input size
// O(1) space; Not dependent on input size
{
	// Checks if there is a node besides dummy header
	if (head->next != NULL) {
		return head->next->deg;
	}

	// No terms
	return -1;
}


int Poly::getTermsNo()
// O(n) time; Loops through LL once
// O(1) space; Memory use not dependent on input size
{
	int count = 0;

	PolyNode* p = head->next;

	while (p != NULL) {
		count++;
		p = p->next;
	}

	return count;
}


double Poly::evaluate(double x)
// Evaluates the polynomial for a certain x value
{
	PolyNode* current = head->next;

	// Will hold the evaluation of the polynomial as it is summed
	double total = 0.0;
	// Will hold the evaluation of the X component of the current term
	double term_eval = 0.0;

	// Loop while current node is not null
	for (int i = 0; current != NULL; i++) {
		if (current->deg > 0) {
			term_eval = x;

			// Will only enter if degree >= 2
			for (int exp = 2; exp <= current->deg; exp++) {
				term_eval *= x;
			}
			total += term_eval * current->coeff;
		}

		else {
			total += current->coeff;
		}

		current = current->next;
	}

	return total;
}


std::string Poly::toString()
// Converts LL to string
{
	string output;

	PolyNode* p = head->next;

	output += "degree=";
	output += to_string(getDegree());
	output += ";";

	while (p != NULL) {
		output += " a(";
		output += to_string(p->deg);
		output += ")=";
		output += to_string(p->coeff);
		output += ";";
	}

	return output;
}

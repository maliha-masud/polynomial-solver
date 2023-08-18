# Polynomial Solver
## C++ program to add and multiply two polynomials, and evaluate a polynomial.

Project Description:
A math solver to solve large polynomials, which are a collection of terms where each term has a variable exponent and a coefficient.
* Assumed that exponent is a non-negative integer, coefficient can be any real number.
* Example P(n) = 5n^2 + 19n - 13 is a polynomial with three terms:
	5n^2, 19n and -13.
	First term has coefficient 5 and exponent 2
	Second term has coefficient 19 and exponent 1
	Third term has coefficient -13 and exponent 0
* Addition and multiplication are binary operations where both operands are polynomials that add or multiply two polynomials and a resultant polynomial is generated
* Evaluate is a binary operator that takes a real value for n and evaluates P(n).
	For example P(2) = 5(4) + 19(2) -13 = 45.

Code Description:
* Linked lists used to implement polynomials
* Two classes: Term and Polynomial
	Term is nested class of polynomial
	Members: Exponent, coefficient, pointer to (next) term
	Polynomial members: pointer to (first) term, size (store no. of terms in polynomial)
* Implemented member functions of class Polynomial
	Input(): Input number of terms and enter coeffiecient and exponent of each term. Check validity and store polynomial in simplest form and in decreasing order of exponent
		Example: Entered:- 5n + 9n^2 - 12n + 7n^5, Stored:- 7n^5 + 9n^2 - 12n.
	Output():
		* A term with coefficient c and exponent x must be displayed as cn^x
		* If a term is not the first term, then the sign of the coefficient (+/-) must be displayed
		* If the exponent of a term is 0 then do not output the variable ‘n’
	Add(): Overloaded '+' operator for this operation. Take polynomial as parameter, add with caller object and return resultant.
		Done in O(n+m) time (n and m are number of terms in polynomials)
	Multiply(): Overloaded '*' operator for this operation. Take polynomial as parameter, multiply with caller object and resturn resultant.
		Done in O(n*m) time (n and m are number of terms in polynomials)
	Evaluate(): Overloaded '.' operator for this operation. Evaluate the value of the polynomial using an input real number.
* Implemented default constructor, copy constructor, destructor, overloaded '=' operator (implements deep copy)
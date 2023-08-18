#include <iostream>
#include <cmath> //to use power function in Evaluate
using namespace std;

class Polynomial {
public:
    //-----------------------------------------------------------------------------
    //------------ Class Term implemented as nested class of Polynomial -----------
    class Term {
    private:
        //members of class Term
        int Exponent;       //non-negative int
        double Coefficient; //any real number
        Term* Next;         //pointer to term: stores address of next term

    public:
        //Default Constructor
        Term() {
            Exponent = 0;
            Coefficient = 0.0;
            Next = NULL;
        }

        //getters for private data members
        int getExponent() { return Exponent; }
        double getCoefficient() { return Coefficient; }
        Term* getNext() { return Next; }

        //setters for private data members
        void setExponent(int Exp) { Exponent = Exp; }
        void setCoefficient(double coeff) { Coefficient = coeff; }
        void setNext(Term* next) { Next = next; }
    };
    //--------------------- End Of Class Term Definition --------------------
    //-----------------------------------------------------------------------
private:
    //data members of class Polynomial
    Term* first;    //pointer to first term: has address of first term
    int Size;       //stores total number of terms in polynomial

public: //member functions of class Polynomial
    //-------------------
    //Default Constructor
    Polynomial() {
        first = NULL;
        Size = 0;
    }
    //-------------------
    //Copy Constructor
    Polynomial(Polynomial& Copy)
    {
        first = Copy.first;
        Size = Copy.Size;
    }
    //-------------------
    //Destructor
    ~Polynomial() {
        /*Term* temp = new Term;
        Term* ptr = first;
        while (ptr != NULL)
        {
            temp = ptr;
            ptr = ptr->getNext();
            delete ptr;
        }*/
    }
    //--------------------------------------
    //Overloaded Assignment Operator: Implements Deep Copy
    Polynomial& operator=(const Polynomial& obj) {
        this->Size = obj.Size;
        Term* objPtr = obj.first;

        if (objPtr == NULL); //nothing to copy
        else
        {
            for (int i = 0; i < obj.Size; i++) //traverse through obj to be copied
            {
                InsertAtEnd(objPtr); //add to calling polynomial
                objPtr = objPtr->getNext();
            }
        }

        //Output();

        return *this;
    }

    //getters for private data members
    Term* getFirst() { return first; }
    int getSize() { return Size; }

    //setters for private data members
    void setFirst(Term* head) { first = head; }
    void setSize(int size) { Size = size; }

    //helper function for Input, Add and Multiply
    void InsertAtEnd(Term* temp) {
        //insert the Term into Polynomial
        if (first == NULL) //if first Term being inserted
        {
            first = temp;
        }
        else //if Polynomial already has Terms in it, add to end
        {
            Term* ptr = first;
            //traverse through polynomial
            while (ptr->getNext() != NULL)
            {
                ptr = ptr->getNext();
            }
            //ptr now points to last Term
            ptr->setNext(temp);
        }
    }

    //helper function for input, add and multiply
    void Simplify() {
        //------------------------------------------------
        //place terms in decreasing order of exponent-----
        //using logic of bubble sort
        bool Swap = false;
        Term* p1;
        Term* p2;
        int tempExp; double tempCoeff;    //store numbers termporarily

        //traverse through Polynomial
        for (p1 = first; p1->getNext() != NULL; p1 = p1->getNext())
        {
            Swap = false;
            for (p2 = first; p2->getNext() != NULL; p2 = p2->getNext())
            {
                if (p2->getNext()->getExponent() > p2->getExponent()) //if next exponent is greater than previous
                {   //swap the two elements
                    tempCoeff = p2->getNext()->getCoefficient();
                    tempExp = p2->getNext()->getExponent();
                    p2->getNext()->setCoefficient(p2->getCoefficient());
                    p2->getNext()->setExponent(p2->getExponent());
                    p2->setCoefficient(tempCoeff);
                    p2->setExponent(tempExp);
                    Swap = true;
                }
            }
            if (Swap == false) //no more elements need to be swapped
            {
                break;
            }
        }
        //end sort----------------------------------------
        //------------------------------------------------

        //------------------------------------------------
        //check for consecutive same exponent in sorted Polynomial. If so, simplify
        Term* ptr = first->getNext();
        Term* pre = first;

        while (ptr != NULL) //traverse through Polynomial
        {
            if (ptr->getExponent() != pre->getExponent())
            {   //not same exponents. Increment the pointers
                pre = ptr;
                ptr = ptr->getNext();
            }
            else { //consecutive exponents are same
                pre->setCoefficient(pre->getCoefficient() + ptr->getCoefficient()); //simply
                pre->setNext(ptr->getNext()); //connect pre to next unique exponent
                delete ptr;                   //delete repeting exponent, as it has been simplified
                ptr = pre->getNext();         //to continue traversing
            }
        }
        //---------------------------------------------------

        //----------------------
        //update Size-----------
        //as Polynomial now exists as simplest form in memory
        Size = 0;
        Term* t = first;
        while (t != NULL)
        {
            Size++;
            t = t->getNext();
        }
        //end update Size-------
        //----------------------
    }

    //-----------------------------------------------------------------------
    //---------------------------- Main Functions ---------------------------
    //-----------------------------------------------------------------------
    ////--------------------------------------------------------------------
    //--------------------- FUNCTION FOR INPUT() -------------------------
    void Input() {
        int noOfTerms = 0;
        //take number of terms as input
        do {
            cout << "Please input the number of terms in your polynomial: ";
            cin >> noOfTerms;
        } while (noOfTerms <= 0); //input validation: number of terms should be > 0

        int tempExp; double tempCoeff;    //store numbers termporarily

        //take coefficient and exponent of each term
        for (int i = 0; i < noOfTerms; i++) {
            Term* temp = new Term; //stores current term temporarily
            cout << "Coefficient of Term " << i + 1 << ": ";
            cin >> tempCoeff;
            temp->setCoefficient(tempCoeff);

            do
            {
                cout << "Exponent of Term " << i + 1 << ": ";
                cin >> tempExp;
            } while (tempExp < 0); //input validation: exponent must be nonnegative
            temp->setExponent(tempExp);
            temp->setNext(NULL);

            //insert the Term into Polynomial
            InsertAtEnd(temp);
        }
        //call helper function that simplifies large polynomials--
        //--into polynomials with just one term for a unique exponent
        Simplify();
    }
    //--------------------- END OF INPUT FUNCTION ------------------------
    //--------------------------------------------------------------------

    //--------------------------------------------------------------------
    //--------------------- FUNCTION FOR OUTPUT() ------------------------
    void Output() {
        if (first == NULL) //No terms yet
        {
            cout << "Polynomial has not been created. Please add some terms first" << endl;
            return;
        }
        //else: if Polynomial exists
        Term* ptr = first;
        for (int i = 0; i < Size; i++)
        {
            if (ptr == first) { //don't need to output +/- sign for first term
                if (ptr->getCoefficient() == 0);    //do not output anything
                else if (ptr->getCoefficient() == 1) //do not need to output coefficient
                {
                    cout << 'n';
                    if (ptr->getExponent() != 1) //do not need to output exponent of n
                        cout << '^' << ptr->getExponent();
                }
                else
                {
                    cout << ptr->getCoefficient() << 'n';
                    if (ptr->getExponent() != 1) //do not need to output exponent of n
                        cout << '^' << ptr->getExponent();
                }
            }
            else if (ptr->getExponent() == 0) { //do not output n or exponent
                //output sign +/- according to value of coefficient
                if (ptr->getCoefficient() == 0);    //do not output anything
                else if (ptr->getCoefficient() > 0)
                    cout << " + ";
                else
                    cout << ' ';
                //'-' will output itself

                cout << ptr->getCoefficient();
            }
            else if (ptr->getExponent() == 1) { //do not need to output exponent of n
               //output sign +/- according to value of coefficient
                if (ptr->getCoefficient() == 0);    //do not output anything
                else if (ptr->getCoefficient() > 0)
                    cout << " + ";
                else
                    cout << ' ';
                //'-' will output itself

                if (ptr->getCoefficient() == 0);    //do not output anything
                else if (ptr->getCoefficient() == 1) //do not need to output coefficient
                    cout << "n";
                else
                    cout << ptr->getCoefficient() << "n";
            }
            else { //if term is not first term
                //output sign +/- according to value of coefficient
                if (ptr->getCoefficient() == 0);    //do not output anything
                if (ptr->getCoefficient() > 0)
                    cout << " + ";
                else
                    cout << ' ';
                //'-' will output itself

                if (ptr->getCoefficient() == 0);    //do not output anything
                else if (ptr->getCoefficient() == 1) //do not need to output coefficient
                    cout << "n^" << ptr->getExponent();
                else
                    cout << ptr->getCoefficient() << "n^" << ptr->getExponent(); //output as cn^x
            }
            ptr = ptr->getNext(); //output next term in next iteration
        }
        cout << endl;
    }
    //--------------------- END OF OUTPUT FUNCTION -----------------------
    //--------------------------------------------------------------------

    //--------------------------------------------------------------------
    //---------------------- FUNCTION FOR ADD() --------------------------

    //overload '+' for this operation
    Polynomial& operator+(const Polynomial& obj) {  //takes polynomial parameter, adds and returns result
        Polynomial resultant;

        //pointers to access calling & passed polynomials
        Term* calling = first;
        Term* passed = obj.first;

        resultant.Size = this->Size + obj.Size; //first make a larger polynomial that will store values

        //copy values of calling polynomial
        for (int i = 0; i < Size; i++) //takes time O(m), where m = size of calling object
        {
            Term* temp = new Term;
            temp->setCoefficient(calling->getCoefficient());
            temp->setExponent(calling->getExponent());
            temp->setNext(NULL);

            resultant.InsertAtEnd(temp);
            calling = calling->getNext();
        }
        //now copy values of passed polynomial
        for (int i = Size; i < resultant.Size; i++) //takes time O(n), where n = passed object size
        {
            Term* temp = new Term;
            temp->setCoefficient(passed->getCoefficient());
            temp->setExponent(passed->getExponent());
            temp->setNext(NULL);

            resultant.InsertAtEnd(temp);
            passed = passed->getNext();
        }
        //can call helper function that simplifies large polynomials--
        //--into polynomials with just one term for a unique exponent
        resultant.Simplify();
        resultant.Output();

        return resultant;
    }
    //---------------------- END OF ADD FUNCTION -------------------------
    //--------------------------------------------------------------------

    //--------------------------------------------------------------------
    //-------------------- FUNCTION FOR MULTIPLY() -----------------------

    //overload '*' for this operation
    Polynomial& operator*(const Polynomial& obj) {  //takes polynomial parameter, mulitplies and returns result
        Polynomial resultant;

        //pointers to access calling & passed polynomials
        Term* larger = first;
        Term* smaller = obj.first;

        //keep record of which polynomial has larger size. Used later in loops
        int largerSize; int smallerSize;

        if (this->Size > obj.Size)
        {
            largerSize = this->Size;
            smallerSize = obj.Size;
            larger = first;
        }
        else
        {
            largerSize = obj.Size;
            smallerSize = this->Size;
            larger = obj.first;
        }
        //end of assigning values to keep record of size

        resultant.Size = this->Size * obj.Size; //first make a larger polynomial that will store values

        for (int i = 0; i < largerSize; i++) {
            //"smaller" ptr points to start of smaller polynomial at start of new iteration
            if (this->Size > obj.Size)
            {
                smaller = obj.first;
            }
            else
            {
                smaller = first;
            }
            for (int j = 0; j < smallerSize; j++) { //Outer loop: O(n), inner loop: O(m). Total = O(n*m)
                //multiply current term of large poly with each term of smaller poly
                //and store in resultant
                Term* temp = new Term;
                temp->setCoefficient(larger->getCoefficient() * smaller->getCoefficient());
                temp->setExponent(larger->getExponent() + smaller->getExponent());
                temp->setNext(NULL);

                if (resultant.first == NULL) {
                    resultant.first = temp;
                }
                else {
                    resultant.InsertAtEnd(temp);
                }
                smaller = smaller->getNext(); //go to next term of small polynomial
            }
            larger = larger->getNext(); //go to next term of large polynomial
        }

        //--call helper function that simplifies large polynomials--
        resultant.Simplify();
        resultant.Output();

        return resultant;
    }
    //-------------------- END OF MULTIPLY FUNCTION ----------------------
    //--------------------------------------------------------------------

    ////------------------------------------------------------------------
    //-------------------- FUNCTION FOR EVALUATE() -----------------------

    double Evaluate(double n) { //take real value of n
        double result = 0;
        Term* ptr = first;
        for (int i = 0; i < Size; i++)
        {
            //display to user 
            if (ptr->getNext() != NULL)
                cout << ptr->getCoefficient() << '(' << pow(n, ptr->getExponent()) << ") + ";
            else //last term reached
                cout << ptr->getCoefficient() << '(' << pow(n, ptr->getExponent()) << ") = ";
            //end display

            //add (c * n ^ exp) into result
            result = result + (ptr->getCoefficient() * pow(n, ptr->getExponent()));
            ptr = ptr->getNext();
        }
        return result;
    }
    //-------------------- END OF EVALUATE FUNCTION ----------------------
    //--------------------------------------------------------------------
};
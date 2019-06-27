#ifndef MY_CLASS_H // Will only be true the once!
#define MY_CLASS_H

/*
AC_Circuit_Classes.h

Header file for AC Circuit Project

The file defines all of the classes used in the project, and explains them in comments
The functions for these classes are defined in AC_Circuit_Fucntions.cpp


*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <complex>
#include <memory>
#include <algorithm>

//define the value of PI
#define Pi 3.1415926535897;

const double BadFunction(-1);

using namespace std;

/*
general component class, abstract base class
it defines the interface as well as some values that all componnents inherit
all components have an impedance and have the frequency which is same throughout
There are then also static numbers to count the number of components
All functions are virtual, and defined for each derived class (some are the same definition for every derived class)
This allows a circuit to be defined as a container of base class pointers
*/
class component
{
protected:
	complex<double> Impedance;  //complex double for impedance, commonly represented by the letter Z
	double Frequency;  //double for frequency, commponly represented by letter f
	static int NumberOfComponents;
	static int NumberOfResistors;
	static int NumberOfCapacitors;
	static int NumberOfInductors;
	static int NumberOfDesignedComponents;
	static int NumberOfNestedCircuits;
public:
	virtual ~component() {}; //component destructor, fully defined here
	virtual void SetFrequency(double freq) = 0; //changes frequency, same for all derived classes (sfadc)
	virtual double GetFrequency() = 0; //returns the frequency, sfadc
	virtual complex<double> GetImpedance() = 0; //returns impedance in complex form, sfadc
	virtual double GetMagnitudeOfImpedance() = 0; //returns magnitude of impedance, sfadc
	virtual double GetPhaseDifference() = 0; //returns argument of impedance, which is equal to the phase difference, sfadc
	virtual int TotalNumber() = 0; //returns the total number of components, from the static number that counts up for each new component (except nested circuits)
	virtual int GetNumber() = 0; //gives number of the type of derived class
	virtual string NumberString() = 0; //this is used to present the different numbers for the components, explained in depth when defined for resistor, sfadc
	virtual string GetType() = 0; //gives strength describing the type of derived class
	virtual vector<vector<shared_ptr<component>>> GetCircuit() = 0; //this is only used for nested circuits, returns the component list of the nested circuit as to help in recursion in operator<<
};


/*
resistor class, derived from component
adds a double for resistance and calculates the impedance from that: Z = R+0*i where R is resistance
*/
class resistor : public component
{
protected:
	double Resistance;  //double for resistance, represented by R
public:
	resistor(double resistance, double frequency); //constructor sets R and f, and calculates Z from Z=R+0*i
	~resistor() {}; //destructor, defined here
	void SetFrequency(double freq);
	double GetFrequency();
	complex<double> GetImpedance();
	double GetMagnitudeOfImpedance();
	double GetPhaseDifference();
	int TotalNumber();
	int GetNumber(); //returns number of resistors
	string GetType(); //returns string "Resistor"
	string NumberString();
	vector<vector<shared_ptr<component>>> GetCircuit();
};



/*
capacitor class, derived from component
adds a double for capacitance, C, and calculates the impedance from that: Z = 1/iwC  where w=2*pi*f
*/
class capacitor : public component
{
protected:
	double Capacitance;
public:
	capacitor(double capacitance, double frequency); //constructor sets C and f
	~capacitor() {}; //destructor, defined here
	void SetFrequency(double freq);
	double GetFrequency();
	complex<double> GetImpedance();
	double GetMagnitudeOfImpedance();
	double GetPhaseDifference();
	int TotalNumber();
	int GetNumber(); //returns number of capacitors
	string GetType(); //returns string "Capacitor"
	string NumberString();
	vector<vector<shared_ptr<component>>> GetCircuit();
};


/*
inductor class, derived from component
adds a double for inductance, L, and calculates the impedance from that: Z = iwL  where w=2*pi*f
*/
class inductor : public component
{
protected:
	double Inductance;
public:
	inductor(double inductance, double frequency); //constructor sets L and f, and calculates Z
	~inductor() {}; //destructor, defined here
	void SetFrequency(double freq);
	double GetFrequency();
	complex<double> GetImpedance();
	double GetMagnitudeOfImpedance();
	double GetPhaseDifference();
	int TotalNumber();
	int GetNumber(); //returns number of inductors
	string GetType(); //returns string "Inductor"
	string NumberString();
	vector<vector<shared_ptr<component>>> GetCircuit();
};


/*
designed component class, derived from component
this is a generic component, with impedance chosen by the user, with no limits
*/
class designedComponent : public component
{
public:
	designedComponent(double real, double imaginary, double frequency); //constructor sets the real component of Z and imaginary component of Z, and frequency f
	~designedComponent() {}; //destructor, defined here
	void SetFrequency(double freq);
	double GetFrequency();
	complex<double> GetImpedance();
	double GetMagnitudeOfImpedance();
	double GetPhaseDifference();
	int TotalNumber();
	int GetNumber(); //returns number of user-designed components
	string GetType(); //returns string "User-designed component"
	string NumberString();
	vector<vector<shared_ptr<component>>> GetCircuit();
};


/*
circuit class
the data of this is a double for the frequency, and a vector<vector> oh shared-ptr to components
each <vector<shared...> is a branch of components in series
they are shared pointers so the component can be defined once, and then moved to a circuit or many
therefore vector<vector...> allows us to add as many branches of components in parallel as needed
once these are defined the total impedance can be calculated and stored

total impedance:
	components in series: Z(total) = Z1 + Z2 + Z3 + ...
	components in parallel: 1/Z(total) = 1/Z1 + 1/Z2 + ...
So the program calculates impedance of each branch, and adds the inverse of that branch impedance to a total of 1/Z(counting)
This eventually gives the impedance at the end
This is all done in CalculateImpedance()
*/
class circuit
{
protected:
	vector<vector<shared_ptr<component>>> ComponentList;
	complex<double> Impedance;
	double Frequency;
public:
	circuit(); //default constructor creates an empty vector and frequency and impedance of 0
	circuit(double frequency); //sets f, vector is empty and impedance is 0
	circuit(vector<shared_ptr<component>> complist); //creates a circuit of one branch (everything in series), sets frequency from the component list and calculates impedance
	circuit(vector<vector<shared_ptr<component>>> complist); //creates a circuit of many branches from full vector<vector...>, sets frequency from this and calculates impedance
	circuit(circuit &Original); //copy constructor
	circuit(circuit &&Original); //move contrusctor
	circuit & operator=(circuit &Original); //copy assignment operator
	~circuit(); //destructor is defined in functions.cpp, clears memory from shared-ptrs by .reset() and then clears vector
	double GetFrequency(); //returns frequency
	complex<double> GetImpedance(); //returns complex impedance
	double GetMagnitudeOfImpedance(); //returns magnitude of impedance
	double GetPhaseDifference(); //returns argument of impedance
	void AddComponent(shared_ptr<component> comp, int branch = 0); //adds a component to the end of a branch, if unspecified the first branch
	void CalculateImpedance(); //calculates the impedance, as described above
	vector<vector<shared_ptr<component>>> GetComponentList(); //returns the list of shared pointers to components
	friend ifstream& operator>> (ifstream& instream, circuit& Circuit); //friend function to overload the operator>> for use with files, so file can set all details of circuit
	friend void ConvertStringToComponent(string Input, circuit &Circuit, int branch); //friend function that is used only in operator>>, takes string from getline, and adds the corresponding component from the code
	friend void ConvertStringToFrequency(string Input, circuit &Circuit); //friend function only used in >>, takes string from getline, and sets frequency from code
	friend ostream & operator<< (ostream &outstream, circuit &Circuit); //operator used to print out the details of the circuit
	friend istream & operator>>(istream &instream, circuit &Circuit); //operator used to set details of circuit from display
	friend string GetCircuitComponentNumbersAsAString(circuit Circuit); //this returns NumberString() from very first component in vec<vec..>
};

/*
nest circuit class, derived from component
this is a component, and so can be added to a circuit
but it includes a circuit, and then component is set from the impedance and frequency of that circuit
note that, whilst it does tick up number of nested circuits by one, it does not add to total components, as those have already been set
*/
class nestedCircuit : public component
{
protected:
	circuit CircuitNest;
public:
	nestedCircuit(circuit InputCircuit); //constructor, takes a circuit as the argument
	~nestedCircuit() {}; //destructor
	void SetFrequency(double freq);
	double GetFrequency();
	complex<double> GetImpedance();
	double GetMagnitudeOfImpedance();
	double GetPhaseDifference();
	int TotalNumber();
	int GetNumber(); //returns number of nested circuits
	string GetType(); //returns string "Nested circuit"
	string NumberString();
	vector<vector<shared_ptr<component>>> GetCircuit(); //returns the ComponentList of the circuit, that can be used to set a new circuit, in printing out the nested circuit
};


//declaration of non-member (non-friend) functions
ostream & operator<< (ostream &outstream, shared_ptr<component> comp);  //ostream operator<< for putting a component into an ostream
template <class T> bool StringToNumber(string Input, T& Number); //template function attempts to convert a string to something of class T (intended for int or double)
template <class T> T GetNumberFromCinStream(istream &instream); //takes input from istream and tries to convert this to something of class T, attempt done in StringToNumber
void ClearWhitespace(ifstream& infile); //clears spaces and newlines from instream until there is something else
void ClearJustSpaces(ifstream& infile); //clears spaces from instream until there is something else
void DecideAndRunInput(circuit &Circuit); //asks user for the way to input and then does it (file or display)
void DecideAndRunOutput(circuit &Circuit); //asks user for way to out put then does it (file or display or both)
void ExplanationOfProgram(); //prints out the details of the program for the user

#endif






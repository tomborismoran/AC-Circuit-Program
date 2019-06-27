/*
AC_Circuit_Functions.cpp

Source file for AC Circuit Project that defines all the functions for the classes in header file AC_Circuit_Classes.h

The file defines all of the classes used in the project, and explains them in comments
The explanations of what these functions do is mostly in the header file


*/

#include "AC_Circuit_Classes.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <complex>
#include <memory>
#include <algorithm>
#include <sstream>

//define the value of PI
#define Pi 3.1415926535897;

using namespace std;


//sets static values at 0 before any components are added
int component::NumberOfResistors(0);
int component::NumberOfCapacitors(0);
int component::NumberOfInductors(0);
int component::NumberOfComponents(0);
int component::NumberOfDesignedComponents(0);
int component::NumberOfNestedCircuits(0);

/*
	Now define the functions
*/


// define functions for resistor class
resistor::resistor(double resistance, double frequency)
{
	Resistance = resistance;
	Frequency = frequency;
	Impedance = complex<double>(Resistance, 0);
	NumberOfResistors++;
	NumberOfComponents++;
}

void resistor::SetFrequency(double freq)
{
	Frequency = freq;
}

double resistor::GetFrequency()
{
	return Frequency;
}

complex<double> resistor::GetImpedance()
{
	return Impedance;
}

double resistor::GetMagnitudeOfImpedance()
{
	double Magnitude = abs(Impedance);
	return Magnitude;
}

double resistor::GetPhaseDifference()
{
	double Magnitude = arg(Impedance);
	return Magnitude;
}

int resistor::TotalNumber()
{
	return NumberOfComponents;
}

int resistor::GetNumber()
{
	return NumberOfResistors;
}

string resistor::GetType()
{
	string Type = "Resistor";
	return Type;
}

string resistor::NumberString()
{
	/*
	This formats a string so that it can be printed out, by 'ostream >> NumberString()', giving the numbers as such:

	"Number of Total Components: int
		Number of Resistors: int
		Number of Capacitors: int
		Number of Inductors: int
		Number of Designed Components: int
		Number of Nested Circuits: int"
	*/


	string Output = "Number of Total Components: ";
	Output.append(to_string(NumberOfComponents));
	Output.append("\n		Number of Resistors: ");
	Output.append(to_string(NumberOfResistors));
	Output.append("\n		Number of Capacitors: ");
	Output.append(to_string(NumberOfCapacitors));
	Output.append("\n		Number of Inductors: ");
	Output.append(to_string(NumberOfInductors));
	Output.append("\n		Number of Designed Components: ");
	Output.append(to_string(NumberOfDesignedComponents));
	Output.append("\n		Number of Nested Circuits: ");
	Output.append(to_string(NumberOfNestedCircuits));
	return Output;
}

vector<vector<shared_ptr<component>>> resistor::GetCircuit()
{
	throw BadFunction;
	return {};
}



// define functions for capacitor class
capacitor::capacitor(double capacitance, double frequency)
{
	Capacitance = capacitance;
	Frequency = frequency;
	// Z = 1/iwC
	double w = 2 * Pi;
	double ImaginaryComponentOfImpedance = -1 / (w * Frequency * Capacitance);
	Impedance = complex<double>(0, ImaginaryComponentOfImpedance);
	NumberOfCapacitors++;
	NumberOfComponents++;
}

void capacitor::SetFrequency(double freq)
{
	Frequency = freq;
}

double capacitor::GetFrequency()
{
	return Frequency;
}

complex<double> capacitor::GetImpedance()
{
	return Impedance;
}

double capacitor::GetMagnitudeOfImpedance()
{
	double Magnitude = abs(Impedance);
	return Magnitude;
}

double capacitor::GetPhaseDifference()
{
	double Magnitude = arg(Impedance);
	return Magnitude;
}

int capacitor::TotalNumber()
{
	return NumberOfComponents;
}

int capacitor::GetNumber()
{
	return NumberOfCapacitors;
}

string capacitor::GetType()
{
	string Type = "Capacitor";
	return Type;
}

vector<vector<shared_ptr<component>>> capacitor::GetCircuit()
{
	throw BadFunction;
	return {};
}

string capacitor::NumberString()
{
	string Output = "Number of Total Components: ";
	Output.append(to_string(NumberOfComponents));
	Output.append("\n		Number of Resistors: ");
	Output.append(to_string(NumberOfResistors));
	Output.append("\n		Number of Capacitors: ");
	Output.append(to_string(NumberOfCapacitors));
	Output.append("\n		Number of Inductors: ");
	Output.append(to_string(NumberOfInductors));
	Output.append("\n		Number of Designed Components: ");
	Output.append(to_string(NumberOfDesignedComponents));
	Output.append("\n		Number of Nested Circuits: ");
	Output.append(to_string(NumberOfNestedCircuits));
	return Output;
}


// define functions for inductor class

inductor::inductor(double inductance, double frequency)
{
	Inductance = inductance;
	Frequency = frequency;
	// Z = iwL
	double ImaginaryComponentOfImpedance = 2 * Frequency * Inductance * Pi;
	Impedance = complex<double>(0, ImaginaryComponentOfImpedance);
	NumberOfInductors++;
	NumberOfComponents++;
}

void inductor::SetFrequency(double freq)
{
	Frequency = freq;
}

double inductor::GetFrequency()
{
	return Frequency;
}

complex<double> inductor::GetImpedance()
{
	return Impedance;
}

double inductor::GetMagnitudeOfImpedance()
{
	double Magnitude = abs(Impedance);
	return Magnitude;
}

double inductor::GetPhaseDifference()
{
	double Magnitude = arg(Impedance);
	return Magnitude;
}

int inductor::TotalNumber()
{
	return NumberOfComponents;
}

int inductor::GetNumber()
{
	return NumberOfInductors;
}

string inductor::GetType()
{
	string Type = "Inductor";
	return Type;
}

vector<vector<shared_ptr<component>>> inductor::GetCircuit()
{
	throw BadFunction;
	return {};
}

string inductor::NumberString()
{
	string Output = "Number of Total Components: ";
	Output.append(to_string(NumberOfComponents));
	Output.append("\n		Number of Resistors: ");
	Output.append(to_string(NumberOfResistors));
	Output.append("\n		Number of Capacitors: ");
	Output.append(to_string(NumberOfCapacitors));
	Output.append("\n		Number of Inductors: ");
	Output.append(to_string(NumberOfInductors));
	Output.append("\n		Number of Designed Components: ");
	Output.append(to_string(NumberOfDesignedComponents));
	Output.append("\n		Number of Nested Circuits: ");
	Output.append(to_string(NumberOfNestedCircuits));
	return Output;
}


// define functions for designed component class

designedComponent::designedComponent(double real, double imaginary, double frequency)
{
	Frequency = frequency;
	Impedance = complex<double>(real, imaginary);
	NumberOfDesignedComponents++;
	NumberOfComponents++;
}

void designedComponent::SetFrequency(double freq)
{
	Frequency = freq;
}

double designedComponent::GetFrequency()
{
	return Frequency;
}

complex<double> designedComponent::GetImpedance()
{
	return Impedance;
}

double designedComponent::GetMagnitudeOfImpedance()
{
	double Magnitude = abs(Impedance);
	return Magnitude;
}

double designedComponent::GetPhaseDifference()
{
	double Magnitude = arg(Impedance);
	return Magnitude;
}

int designedComponent::TotalNumber()
{
	return NumberOfComponents;
}

int designedComponent::GetNumber()
{
	return NumberOfDesignedComponents;
}

string designedComponent::GetType()
{
	string Type = "User-designed component";
	return Type;
}

vector<vector<shared_ptr<component>>> designedComponent::GetCircuit()
{
	throw BadFunction;
	return {};
}

string designedComponent::NumberString()
{
	string Output = "Number of Total Components: ";
	Output.append(to_string(NumberOfComponents));
	Output.append("\n		Number of Resistors: ");
	Output.append(to_string(NumberOfResistors));
	Output.append("\n		Number of Capacitors: ");
	Output.append(to_string(NumberOfCapacitors));
	Output.append("\n		Number of Inductors: ");
	Output.append(to_string(NumberOfInductors));
	Output.append("\n		Number of Designed Components: ");
	Output.append(to_string(NumberOfDesignedComponents));
	Output.append("\n		Number of Nested Circuits: ");
	Output.append(to_string(NumberOfNestedCircuits));
	return Output;
}


// define functions for nested circuit class

nestedCircuit::nestedCircuit(circuit InputCircuit)
{
	CircuitNest = InputCircuit;
	Frequency = InputCircuit.GetFrequency();
	Impedance =InputCircuit.GetImpedance();
	NumberOfNestedCircuits++;
}

void nestedCircuit::SetFrequency(double freq)
{
	Frequency = freq;
}

double nestedCircuit::GetFrequency()
{
	return Frequency;
}

complex<double> nestedCircuit::GetImpedance()
{
	return Impedance;
}

double nestedCircuit::GetMagnitudeOfImpedance()
{
	double Magnitude = abs(Impedance);
	return Magnitude;
}

double nestedCircuit::GetPhaseDifference()
{
	double Magnitude = arg(Impedance);
	return Magnitude;
}

int nestedCircuit::TotalNumber()
{
	return NumberOfComponents;
}

int nestedCircuit::GetNumber()
{
	return NumberOfNestedCircuits;
}

string nestedCircuit::GetType()
{
	string Type = "Nested circuit";
	return Type;
}

vector<vector<shared_ptr<component>>> nestedCircuit::GetCircuit()
{
	return CircuitNest.GetComponentList();
}

string nestedCircuit::NumberString()
{
	string Output = "Number of Total Components: ";
	Output.append(to_string(NumberOfComponents));
	Output.append("\n		Number of Resistors: ");
	Output.append(to_string(NumberOfResistors));
	Output.append("\n		Number of Capacitors: ");
	Output.append(to_string(NumberOfCapacitors));
	Output.append("\n		Number of Inductors: ");
	Output.append(to_string(NumberOfInductors));
	Output.append("\n		Number of Designed Components: ");
	Output.append(to_string(NumberOfDesignedComponents));
	Output.append("\n		Number of Nested Circuits: ");
	Output.append(to_string(NumberOfNestedCircuits));
	return Output;
}



//Here are other functions thsat are required for processing

//ostream operator<< for putting a component into an ostream
ostream & operator<< (ostream &outstream, shared_ptr<component> comp)
{
	outstream << comp->GetType() << endl;
	outstream << "		" << "Impedance: " << comp->GetImpedance() << endl;
	outstream << "		" << "Magnitude of impedance: " << comp->GetMagnitudeOfImpedance() << endl;
	outstream << "		" << "Phase difference: " << comp->GetPhaseDifference() << endl;
	return outstream;
}

//template function attempts to convert a string to something of class T (intended for int or double)
//it used try throw and catch to attempt this
//if it works Number is changed as it is passed by reference
//a bool return also declares if it worked ( 1 if worked, 0 if thrown )
template <class T> bool StringToNumber(string Input, T& Number)
{
	const int NumberFlag(-1);
	bool Valid = 0;
	try
	{
		stringstream InputStream(Input);
		if ((InputStream >> Number).fail())
		{
			throw NumberFlag;
		}
		InputStream >> Number;
		Valid = 1;
	}
	catch (const int Error)
	{ 
		if (Error == NumberFlag)
		{
			cout << "Invalid conversion. ";
		}
	}
	return Valid;
}

//takes input from istream and tries to convert this to something of class T
//the attempt is done within StringToNumber
template <class T> T GetNumberFromCinStream(istream &instream)
{
	string DataLine;
	bool NumberCheck = 0;
	T Number;
	while (NumberCheck == 0)
	{
		cout << "Must be a " << typeid(Number).name() << ": ";
		instream >> DataLine;
		instream.ignore(numeric_limits<streamsize>::max(), '\n');
		NumberCheck = StringToNumber<T>(DataLine, Number);
	}
	return Number;
}

//clears spaces and newlines from instream until there is something else
void ClearWhitespace(ifstream& infile)
{
	while ((infile.peek() == ' ') || (infile.peek() == '\n'))
	{
		infile.ignore(1);
	}
}

//clears spaces from instream until there is something else
void ClearJustSpaces(ifstream& infile)
{
	while (infile.peek() == ' ')
	{
		infile.ignore(1);
	}
}


//defines functions for circuit class

void circuit::CalculateImpedance()
{
	complex<double> OneOverImpedance = 0;
	for (size_t i = 0; i < ComponentList.size(); i++)
	{
		complex<double> BranchImpedance = 0;
		for (auto VectorIterator = ComponentList[i].begin(); VectorIterator < ComponentList[i].end(); ++VectorIterator)
		{
			BranchImpedance += (*VectorIterator)->GetImpedance();
		}
		OneOverImpedance += (1.0 / BranchImpedance);
	}
	Impedance = (1.0 / OneOverImpedance);
}

circuit::circuit()
{
	ComponentList = {};
	Impedance = 0;
	Frequency = 0;
}

circuit::circuit(double frequency)
{
	ComponentList = {};
	Impedance = 0;
	Frequency = frequency;
}

circuit::circuit(vector<shared_ptr<component>> complist)
{
	bool FrequencyIsSame = 1;
	for (auto VectorIterator = complist.begin(); VectorIterator < complist.end(); ++VectorIterator)
	{
		if (complist[0]->GetFrequency() != (*VectorIterator)->GetFrequency())
		{
			FrequencyIsSame = 0;
		}
	}

	if (FrequencyIsSame)
	{
		ComponentList.push_back(complist);
		Frequency = complist[0]->GetFrequency();
		complex<double> imped = 0;
		for (auto VectorIterator = ComponentList[0].begin(); VectorIterator < ComponentList[0].end(); ++VectorIterator)
		{
			imped += (*VectorIterator)->GetImpedance();
		}
		Impedance = imped;
	}
	else
	{
		cout << "Component list did not have same frequencies. Invalid. Empty circuit has been made" << endl;
		ComponentList = {};
		Impedance = 0;
		Frequency = 0;
	}
}

circuit::circuit(vector<vector<shared_ptr<component>>> complist)
{
	bool FrequencyIsSame = 1;
	for (auto DoubleVectorIterator = complist.begin(); DoubleVectorIterator < complist.end(); ++DoubleVectorIterator)
	{
		for (auto VectorIterator = (*DoubleVectorIterator).begin(); VectorIterator < (*DoubleVectorIterator).end(); ++VectorIterator)
		{
			if ((*DoubleVectorIterator)[0]->GetFrequency() != (*VectorIterator)->GetFrequency())
			{
				FrequencyIsSame = 0;
			}
		}
	}

	if (FrequencyIsSame)
	{
		ComponentList = complist;
		Frequency = complist[0][0]->GetFrequency();
		CalculateImpedance();
	}
	else
	{
		cout << "Component list did not have same frequencies. Invalid. Empty circuit has been made" << endl;
		ComponentList = {};
		Impedance = 0;
		Frequency = 0;
	}
}

circuit::circuit(circuit &Original)
{
	Frequency = Original.Frequency;
	ComponentList.resize(Original.ComponentList.size());
	for (size_t i = 0; i < ComponentList.size(); i++)
	{
		for (auto VectorIterator = Original.ComponentList[i].begin(); VectorIterator < Original.ComponentList[i].end(); ++VectorIterator)
		{
			shared_ptr<component> Pointer(*VectorIterator);
			ComponentList[i].push_back(Pointer);
		}
	}
	CalculateImpedance();
}

circuit::circuit(circuit &&Original)
{
	ComponentList = Original.ComponentList;
	Impedance = Original.Impedance;
	Frequency = Original.Frequency;
	Original.Impedance = 0;
	Original.Frequency = 0;
	for (size_t i = 0; i < Original.ComponentList.size(); i++)
	{
		for (auto VectorIterator = Original.ComponentList[i].begin(); VectorIterator < Original.ComponentList[i].end(); ++VectorIterator)
			(*VectorIterator).reset();
	}
	Original.ComponentList.clear();
}

circuit & circuit::operator=(circuit &Original)
{
	if (&Original == this) return *this;

	for (size_t i = 0; i < ComponentList.size(); i++)
	{
		for (auto VectorIterator = ComponentList[i].begin(); VectorIterator < ComponentList[i].end(); ++VectorIterator)
			(*VectorIterator).reset();
	}
	ComponentList.clear();
	Frequency = 0;
	Impedance = 0;

	ComponentList.resize(Original.ComponentList.size());
	for (size_t i = 0; i < ComponentList.size(); i++)
	{
		for (auto VectorIterator = Original.ComponentList[i].begin(); VectorIterator < Original.ComponentList[i].end(); ++VectorIterator)
		{
			shared_ptr<component> Pointer(*VectorIterator);
			ComponentList[i].push_back(Pointer);
		}
	}
	Impedance = Original.Impedance;
	Frequency = Original.Frequency;
}

double circuit::GetFrequency()
{
	return Frequency;
}

complex<double> circuit::GetImpedance()
{
	return Impedance;
}

double circuit::GetMagnitudeOfImpedance()
{
	double Magnitude = abs(Impedance);
	return Magnitude;
}

double circuit::GetPhaseDifference()
{
	double Magnitude = arg(Impedance);
	return Magnitude;
}

void circuit::AddComponent(shared_ptr<component> comp, int branch)
{
	ComponentList[branch].push_back(comp);
	CalculateImpedance();
}

circuit::~circuit()
{
	for (size_t i = 0; i < ComponentList.size(); i++)
	{
		for (auto VectorIterator = ComponentList[i].begin(); VectorIterator < ComponentList[i].end(); ++VectorIterator)
			(*VectorIterator).reset();
	}

	ComponentList.clear();
}

vector<vector<shared_ptr<component>>> circuit::GetComponentList()
{
	return ComponentList;
}

ifstream& operator>> (ifstream& infile, circuit& Circuit)
{
	string FirstLine;
	getline(infile, FirstLine, '\n');
	ConvertStringToFrequency(FirstLine, Circuit);
	ClearWhitespace(infile);
	int branch = 0;
	while (infile.peek() != EOF)
	{
		Circuit.ComponentList.resize(branch + 1);
		string Line;
		getline(infile, Line, ';');
		ConvertStringToComponent(Line, Circuit, branch);
		ClearJustSpaces(infile);
		if (infile.peek() == '\n')
		{
			infile.ignore(1);
			branch++;
		}
		ClearWhitespace(infile);
		if (infile.peek() != EOF)
		{
			Circuit.ComponentList.resize(branch + 1);
		}
	}
	Circuit.CalculateImpedance();
	return infile;
}

void ConvertStringToComponent(string Input, circuit &Circuit, int branch)
{
	if ( (Input.find_first_of(",") == Input.find_last_of(",")) && (Input.find_first_of(",") != string::npos) )
	{
		string ComponentName;
		char ComponentIndex;
		ComponentName = Input.substr(0, Input.find_first_of(","));
		if ((ComponentName == "R") || (ComponentName == "Resistor"))
		{
			ComponentIndex = 'R';
		}
		else if ((ComponentName == "C") || (ComponentName == "Capacitor"))
		{
			ComponentIndex = 'C';
		}
		else if ((ComponentName == "L") || (ComponentName == "Inductor"))
		{
			ComponentIndex = 'L';
		}
		else
		{
			cout << "Could not find valid component type. Component not added to circuit" << endl;
			ComponentIndex = '0';
		}

		double ComponentValue = 0;
		string ComponentData = Input.substr(Input.find_first_of(",") + 1);
		bool ConversionWorked = StringToNumber<double>(ComponentData, ComponentValue);
		if ((ComponentValue > 0) && ConversionWorked)
		{
			if (ComponentIndex == 'R')
			{
				shared_ptr<component> Pointer(new resistor(ComponentValue, Circuit.Frequency));
				Circuit.ComponentList[branch].push_back(Pointer);
			}
			else if (ComponentIndex == 'C')
			{
				shared_ptr<component> Pointer(new capacitor(ComponentValue, Circuit.Frequency));
				Circuit.ComponentList[branch].push_back(Pointer);
			}
			else if (ComponentIndex == 'L')
			{
				shared_ptr<component> Pointer(new inductor(ComponentValue, Circuit.Frequency));
				Circuit.ComponentList[branch].push_back(Pointer);
			}
		}
		else
		{
			cout << "Could not find valid component value. Must be a positive double. Component not added" << endl;
		}
	}
	else if (Input.find_first_of(",") == string::npos)
	{
		string NestName;
		NestName = Input.substr(0, Input.find_first_of(";"));
		if (NestName == "N")
		{
			circuit Nest(Circuit.Frequency);
			ifstream NestFile("NestedCircuitInput.txt");
			if (NestFile.is_open())
				NestFile >> Nest;
			NestFile.close();
			shared_ptr<component> Pointer(new nestedCircuit(Nest));
			Circuit.ComponentList[branch].push_back(Pointer);
		}
	}
	else if ((Input.find_first_of(",", Input.find_first_of(",")+1) == Input.find_last_of(",")) && (Input.find_first_of(",", Input.find_first_of(",") + 1) != string::npos))
	{
		string DesignedComponentName;
		DesignedComponentName = Input.substr(0, Input.find_first_of(","));
		if (DesignedComponentName == "U")
		{
			double RealValue = 0;
			string RealData = Input.substr(Input.find_first_of(",") + 1);

			double ImagValue = 0;
			string ImagData = Input.substr(Input.find_first_of(",", Input.find_first_of(",") + 1) + 1);

			bool DataIsValid = (StringToNumber<double>(RealData, RealValue)) * (StringToNumber<double>(ImagData, ImagValue));

			if (DataIsValid)
			{
				shared_ptr<component> Pointer(new designedComponent(RealValue, ImagValue, Circuit.Frequency));
				Circuit.ComponentList[branch].push_back(Pointer);
			}
		}
	}
	else
	{
		cout << "Invalid format. Component not added" << endl;
	}

}

void ConvertStringToFrequency(string Input, circuit &Circuit)
{
	if ((Input.find_first_of(":") == Input.find_last_of(":")) && (Input.rfind("Frequency:") != string::npos))
	{
		double frequency = 0;
		string FrequencyData = Input.substr(Input.find_first_of(":") + 1, Input.find_first_of(";"));
		bool FoundFrequency = StringToNumber<double>(FrequencyData, frequency);
		if (!FoundFrequency)
		{
			cout << "Frequency could not be set, set to 0" << endl;
		}
		if ((Circuit.Frequency != 0) && (Circuit.Frequency != frequency))
		{
			cout << "Frequency of nested circuit does not match, frequency of larger circuit kept" << endl;
		}
		else
		{
			Circuit.Frequency = frequency;
		}
	}
	else
	{
		cout << "Invalid format. Frequency not set" << endl;
	}

}

ostream & operator<< (ostream &outstream, circuit &Circuit)
{
	vector<shared_ptr<component>> ListOfNestedCircuits;
	for (size_t i = 0; i < Circuit.ComponentList.size(); i++)
	{
		outstream << "Branch " << i + 1 << ":" << endl;
		int componentCount = 0;
		for_each(Circuit.ComponentList[i].begin(), Circuit.ComponentList[i].end(), [&componentCount, &outstream, &ListOfNestedCircuits] (shared_ptr<component> comp)
		{
			outstream << "	" << "Component " << componentCount + 1 << ": ";
			outstream << comp;
			if (comp->GetType() == "Nested circuit")
				ListOfNestedCircuits.push_back(comp);
			componentCount++;
		});
	}
	
	if (!ListOfNestedCircuits.empty())
	{
		outstream << endl << "Nested circuits:" << endl << endl;
		int nestCount = 0;
		for_each(ListOfNestedCircuits.begin(), ListOfNestedCircuits.end(), [&nestCount, &outstream] (shared_ptr<component> nest)
		{
			outstream << "Nested circuit " << nestCount + 1 << ": " << endl;
			circuit NestOutput(nest->GetCircuit());
			outstream << NestOutput;
		});
		outstream << endl << "End of nested circuits" << endl << endl;
	}

	outstream << "Circuit data:" << endl;
	outstream << "Frequency: " << Circuit.Frequency << "Hz" << endl;
	outstream << "Total impedance: " << Circuit.Impedance << endl;
	outstream << "Magnitude of impedance: " << abs(Circuit.Impedance) << endl;
	outstream << "Phase difference: " << arg(Circuit.Impedance) << endl;
	return outstream;
}

istream & operator>>(istream &instream, circuit &Circuit)
{
	if (Circuit.Frequency == 0)
	{
		cout << "Enter the frequency. ";
		Circuit.Frequency = GetNumberFromCinStream<double>(instream);
	}
	bool Continue = 1;
	int branch = 0;
	while (Continue)
	{
		Circuit.ComponentList.resize(branch + 1);
		cout << "Add a component (c) or a new branch (b) or end (e): ";
		string Line;
		instream >> Line;
		instream.ignore(numeric_limits<streamsize>::max(), '\n');
		while ((Line != "c") && (Line != "b") && (Line != "e"))
		{
			cout << "Enter c/b/e: ";
			instream >> Line;
			instream.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (Line == "c")
		{
			cout << "Add a resistor (R) or a capacitor (C) or an inductor (L) or a user-desgined component (U) or a nested circuit (N): ";
			string NextLine;
			instream >> NextLine;
			instream.ignore(numeric_limits<streamsize>::max(), '\n');
			while ((NextLine != "R") && (NextLine != "V") && (NextLine != "L") && (NextLine != "U") && (NextLine != "N"))
			{
				cout << "Enter R/C/L/N: ";
				instream >> NextLine;
				instream.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if ((NextLine == "R") || (NextLine == "C") || (NextLine == "L"))
			{
				if (NextLine == "R")
				{
					cout << "Enter the resistance. ";
				}
				else if (NextLine == "C")
				{
					cout << "Enter the capacitance. ";
				}
				else if (NextLine == "L")
				{
					cout << "Enter the inductance. ";
				}
				double Data = GetNumberFromCinStream<double>(instream);
				if (NextLine == "R")
				{
					shared_ptr<component> Pointer(new resistor(Data, Circuit.Frequency));
					Circuit.ComponentList[branch].push_back(Pointer);
				}
				else if (NextLine == "C")
				{
					shared_ptr<component> Pointer(new capacitor(Data, Circuit.Frequency));
					Circuit.ComponentList[branch].push_back(Pointer);
				}
				else if (NextLine == "L")
				{
					shared_ptr<component> Pointer(new inductor(Data, Circuit.Frequency));
					Circuit.ComponentList[branch].push_back(Pointer);
				}
			}
			else if (NextLine == "U")
			{
				cout << "Enter the real component of the impedance. ";
				double RealData = GetNumberFromCinStream<double>(instream);
				cout << "Enter the imaginary component of the impedance. ";
				double ImagData = GetNumberFromCinStream<double>(instream);
				shared_ptr<component> Pointer(new designedComponent(RealData, ImagData, Circuit.Frequency));
				Circuit.ComponentList[branch].push_back(Pointer);
			}
			else if (NextLine == "N")
			{
				cout << "Give the details of the nested circuit now:" << endl;
				circuit Nest(Circuit.Frequency);
				instream >> Nest;
				shared_ptr<component> Pointer(new nestedCircuit(Nest));
				Circuit.ComponentList[branch].push_back(Pointer);
				cout << "Having created the nested circuit, back to options for the previous circuit" << endl << endl;
			}
		}
		else if (Line == "b")
		{
			if (Circuit.ComponentList[branch].empty())
			{
				cout << "Current branch is empty, so a new one will not be added." << endl;
			}
			else
			{
				branch++;
				Circuit.ComponentList.resize(branch + 1);
			}
		}
		else if (Line == "e")
		{
			Continue = 0;
		}
	}

	Circuit.CalculateImpedance();

	cout << "Circuit made" << endl << endl;

	return instream;

}

string GetCircuitComponentNumbersAsAString(circuit Circuit)
{
	string Output = Circuit.ComponentList[0][0]->NumberString();
	return Output;
}


//functions for use in main()
void DecideAndRunInput(circuit &Circuit)
{
	cout << "A circuit can be added from the file 'CircuitInput.txt' or from the display" << endl;
	cout << "Take the input from file (f) or (d): ";
	string Line;
	cin >> Line;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while ((Line != "f") && (Line != "d"))
	{
		cout << "Enter f/d: ";
		cin >> Line;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	if (Line == "f")
	{
		ifstream InputFile("CircuitInput.txt");
		if (InputFile.is_open())
			InputFile >> Circuit;
		InputFile.close();
	}

	if (Line == "d")
	{
		cin >> Circuit;
	}
}

void DecideAndRunOutput(circuit &Circuit)
{
	string Line;
	cout << "Sent output to file (f) or display (d) or both (b): ";
	cin >> Line;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while ((Line != "f") && (Line != "d") && (Line != "b"))
	{
		cout << "Enter f/d/b: ";
		cin >> Line;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	if (Line == "f")
	{
		ofstream OutputFile("CircuitOutput.txt");
		if (OutputFile.is_open())
		{
			OutputFile << Circuit;
			OutputFile << endl << GetCircuitComponentNumbersAsAString(Circuit) << endl;
		}
		OutputFile.close();
	}

	if (Line == "d")
	{
		cout << Circuit;
		cout << endl << GetCircuitComponentNumbersAsAString(Circuit) << endl;
	}

	if (Line == "b")
	{
		ofstream OutputFile("CircuitOutput.txt");
		if (OutputFile.is_open())
		{
			OutputFile << Circuit;
			OutputFile << endl << GetCircuitComponentNumbersAsAString(Circuit) << endl;
		}
		OutputFile.close();
		cout << Circuit;
		cout << endl << GetCircuitComponentNumbersAsAString(Circuit) << endl;
	}
}

void ExplanationOfProgram()
{
	cout << "This program is used to create a circuit and then print out the details of that circuit" << endl;
	cout << "This circuit can contain resistors, capacitors, inductors, user-desgined components and nested circuits" << endl;
	cout << "These components can be placed in any order on any number of branches in a parallel circuit" << endl;
	cout << "The circuit can be input using the file 'CircuitInput.txt' or from the keyboard input (display)" << endl;
	cout << "The file input follows a rigid format:" << endl;
	cout << "	The first then is 'Frequency: ' followed by a double" << endl;
	cout << "	The next lines each correspond to a branch of the parallel circuit" << endl;
	cout << "	Components should be declared using a component code, followed by required details, then a semi-colon" << endl;
	cout << "		Resistors are given by 'R, ' followed by as double that is the resistancev (R, x;)" << endl;
	cout << "		Capacitors are given by 'C, ' followed by as double that is the capacitance (C, x;)" << endl;
	cout << "		Inductors are given by 'L, ' followed by as double that is the inductance (L, x;)" << endl;
	cout << "		User-designed components are given by 'U, ' followed by two doubles for the impedance separated by a comma (U, x, y;)" << endl;
	cout << "		Nested circuits are given by 'N' (N;), and then call up the nested circuit from file 'NestedCircuitInput.txt'" << endl;
	cout << "			(Only one nested circuit can be added by file, but this one can be repeated)" << endl;
	cout << "The keyboard input gives prompts to give the appropriate inputs:" << endl;
	cout << "	Branches and components can be added" << endl;
	cout << "	Component addition requires inputting the componnent code when prompted, and all values will be asked for afteerwards" << endl;
	cout << "	When a nested circuit is added, it will start a new instance of the keyboard input, and the nested circuit is added" << endl;
	cout << "	When the nested circuit creation is ended the larger circuit can continue to be added to" << endl;
	cout << "	With this method, there is no limit to the number of nested circuits" << endl;
	cout << "The details of the circuit created can be outputted to the file 'CircuitOutput.txt' or the display or both" << endl;
	cout << "________________________________________________________________________________________________________________________" << endl;
	cout << endl << endl;



}
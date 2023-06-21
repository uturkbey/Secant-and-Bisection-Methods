#include <iostream>
#include <cmath>

using namespace std;

//This class called Polynomial represents a one dimensional and of variable degree polynomial function.
class Polynomial
{
	public:
		//instance variables
		int degree; //to hold degree of polynýmial
		double * coeffs; //to hold coefficients of polynomial
		
		//constructor
		Polynomial(int, double *);
		
		//instance methods
		double valueAt(double); //this function evaluates the polynomial at the given point as parameter
		
};

Polynomial::Polynomial(int d, double * cs)
{
	degree = d;
	coeffs = cs;
}

double Polynomial::valueAt(double point)
{
	double value = 0;
	
	for (int i = 0; i <= degree; i++)//traverse throug each 
	{
		double product = 1;
		for (int j = 0; j < degree - i; j++)
		{
			product = product * point;
		}
		value = value + coeffs[i] * product;
	} 
	return value;
}

//this static function checks the sign of given number in parameter
//returns 1 if 0 or positive, -1 if negative
int sign (double number)
{
	if (number >= 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

//This main function implements Bisection, Secant and a hybrid(of those two methods) methods 
//to find zero of the given polynomial within given interval and tolerance as command line arguments
int main(int argc, char * argv[]) //Paramters needed in order to give necessary command line arguments to the main function
{
	//1)variables
	double * coeffs; //double pointer to hold dynamically allocated array of coefficients of polynomial given in command line arguments
	double tolerance; //to hold tolerance given in command line arguments
	double x0; //first initial guess
	double x1; //second initial gues	(x1 > x0)
	int numOfIteration; //to hold num of iterations in each method
	
	  
	//2)assigning command line inputs to variables accordingly  
	tolerance = atof(argv[argc - 1]); //last command line input is the tolerance
	x0 = atof(argv[argc - 3]); //third from the last command line input is the smaller initial guess
	x1 = atof(argv[argc - 2]); //second from last command line input is the larger initial guess
	coeffs = new double [argc - 4]; //total number of command line arguments mines 4 is the number of coefficients
	for (int i = 1; i < argc - 3; i++)
	{
		coeffs[i - 1] = atof(argv[i]); 
	}
	
	//3)initializing a polynomial object out of given command line inputs
	Polynomial pol(argc - 5, coeffs);
	
	//4)BISECTION METHOD(Retrieved from M. Heath, Scientific Computation 2. Edition, p. 224, algorithm 5.1) 
	numOfIteration = 0; //reset number of iterations
	double a = x0; //set left end of interval to x0
	double b = x1; //set right end of interval to x1
	double m; //middle point to be used in algorithm
	
	while ( (b - a) > tolerance) //execute bisection algorithm
	{
		m = a + (b - a) / 2; //compute midpoint
		if(sign(pol.valueAt(a)) == sign(pol.valueAt(m))) //signs of midpoint and a is same
		{
			a = m; //use right interval
		}
		else //signs of midpoint and a are opposite
		{
			b = m; //use left interval
		}	
		numOfIteration = numOfIteration + 1; //increment number of iterations by one
	} //end loop when interval is smaller than tolerance

	cout << "For the Bisection Method: " << numOfIteration << " number of iterations and " << m << " is the root.\n\n"; //print the root and the number of iterations to console
	
	
	//5)SECANT METHOD(Retrieved from M. Heath, Scientific Computation 2. Edition, p. 232, algorithm 5.3)
	numOfIteration = 0; //reset number of iterations
	a = x0; //set left end of interval to x0 -> X(k-1)
	b = x1; //set right end of interval to x1 -> X(k)
	double c; //-> X(k+1)
	
	do { //execute secant algorithm
		c = b - (pol.valueAt(b) * (b - a)) / (pol.valueAt(b) - pol.valueAt(a)); //find X(k+1)
		a = b; //update X(k-1)
		b = c; //update X(k)
		numOfIteration = numOfIteration + 1; //increment number of iterations by one 
	} while (abs(b - a) > tolerance); //continue if |X(k+1) - X(k)| > tolerance
	
	cout << "For the Secant Method: " << numOfIteration << " number of iterations and " << c << " is the root.\n\n"; //print the root and the number of iterations to console
	
	//6)HYBRID METHOD(Combination of parts 4 and 5)
	numOfIteration = 0; //reset number of iterations
	a = x0; //set left end of interval to x0
	b = x1; //set right end of interval to x1
	
	while ( (b - a) > tolerance && numOfIteration < 2) //iterate bisection algorithm for at most 2 times
	{
		m = a + (b - a) / 2; //compute midpoint
		if(sign(pol.valueAt(a)) == sign(pol.valueAt(m))) //signs of midpoint and a is same
		{
			a = m; //use right interval
		}
		else //signs of midpoint and a are opposite
		{
			b = m; //use left interval
		}	
		numOfIteration = numOfIteration + 1; //increment number of iterations by one
	} //end loop when interval is smaller than tolerance
	
	do { //execute secant algorithm after 2 iterations of bisection algorithm
		c = b - (pol.valueAt(b) * (b - a)) / (pol.valueAt(b) - pol.valueAt(a)); //find X(k+1)
		a = b; //update X(k-1)
		b = c; //update X(k)
		numOfIteration = numOfIteration + 1; //increment number of iterations by one 
	} while (abs(b - a) > tolerance); //continue if |X(k+1) - X(k)| > tolerance
	
	cout << "For the Hybrid Method: " << numOfIteration << " number of iterations and " << c << " is the root.\n\n"; //print the root and the number of iterations to console
	
	
	return 0;
}

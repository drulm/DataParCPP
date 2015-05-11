// ----------------------------------------------------------------------------------
//		TEST PROGRAM FOR PARALLEL CLASSES
// ----------------------------------------------------------------------------------
#include "par.h"
#include <iostream>
#include <iomanip>
using namespace std;

const int SZ=10000;

/// <summary>
/// Mains this instance.
/// </summary>
/// <returns></returns>
int main()
{
	par<double> term(SZ),x(SZ);

	self_address(x);

	cout << 
		 reduce_sum(4.0/(1.0+(x*2.0))*pow(-1.0,x))
		 << endl;

	par<char *> ch(5);
	ch = "hello";
	cout<<endl<<ch<<endl;

	return 0;
}


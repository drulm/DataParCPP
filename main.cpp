// ----------------------------------------------------------------------------------
//		TEST PROGRAM FOR PARALLEL CLASSES
// ----------------------------------------------------------------------------------

#include "par.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Size of the data-parallel array
const int DataParallelArraySize = 10000;

/// <summary>
/// Mains this instance.
/// </summary>
/// <returns></returns>
int main()
{
	// Create a data parallel array of size DataParallelArraySize
	par<double> x(DataParallelArraySize);

	// Assign data-parallel variable it's self address: 1,2,3, ..., DataParallelArraySize
	self_address(x);

	// Compute and output PI, in one line of data-parallel code based on PI definition
	// Note: this is not a fast method.
	cout <<  reduce_sum(4.0/(1.0+(x*2.0))*pow(-1.0,x)) << endl;

	return 0;
}


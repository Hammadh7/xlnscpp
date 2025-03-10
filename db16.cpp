#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#define xlns16_ideal
#include "xlns16.cpp"

using namespace std;

//called by sblptest.py
int main(int argc, char ** argv)
{
	int zi;
	xlns16 one,z,res;
	one =fp2xlns16(-1.0);
	if (argc < 2)
	{
		cout << "db16 <int>; computes Gaussian Log for 16-bit LNS\n";
		return 1;
	}

	zi = atoi(argv[1]);
	z = ((xlns16) ((zi & 0x7fff)^0x4000));
	res = xlns16_add( z , one );
	cout << ((xlns16_signed)(0x4000^res)) <<"\n";
	return 0;
}	

#include "mystruct.h"
#include <iostream>

using namespace std;

int main() {
	blifElaborate myblif;
	myblif.blifElaborateRead();
	myblif.blif2Verilog();
	return 0;
}

// deal with conflict
#include "mystruct.h"
#include <iostream>

using namespace std;

int main() {
	BilfElaborate myBilf;
	myBilf.BilfElaborateRead();
	myBilf.Bilf2Verilog();
	return 0;
}

// deal with conflict
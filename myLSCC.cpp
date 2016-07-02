#include <iostream>
#include "localSearch.h"

using namespace std;

int main(int argc, char* argv[])
{
	char filename[1024];
	sscanf(argv[1], "%s", filename);

	int seed;
	sscanf(argv[2], "%d", &seed);
	srand(seed);

	int time_limit;
	sscanf(argv[3], "%d", &time_limit);

	StochasticLocalSearch mySLS(filename, time_limit);
	//mySLS.show_state();


	mySLS.clique_sls();

	mySLS.show_results();

	return 0;
}

#include "GeneticAlgorithm.hpp"

#include <Rcpp.h>
#include <string>
#include <sstream>

using namespace std;
using namespace Rcpp;
using namespace SIMSEMI;

// [[Rcpp::export]]
List TestMain(const int& n, const int& m)
{
	int arrInt[n];
	for (int i = 0 ; i < n ; i++ ) {
		arrInt[i] = static_cast<int>(R::runif(1,4));
	}

	size_t nJobCnt = sizeof(arrInt)/sizeof(*arrInt);
	int nMachine = m;

	CGeneticAlgorithm ga;
	ga.execOptimalSolutionGeneration(Vec_INT(arrInt, arrInt+nJobCnt), nMachine);
	JobContainer jobs = ga.getOptimalSolution();
	ostringstream oss;
	oss << jobs;
	return List::create(oss.str(), ga.getEvaluatedVals());
}

#include "GeneticAlgorithm.hpp"

#include <Rcpp.h>
#include <string>
#include <sstream>

using namespace std;
using namespace Rcpp;
using namespace SIMSEMI;

// [[Rcpp::export]]
std::string TestMain()
{
	int arrInt[] = { 3, 2, 1, 1, 2, 3, 3, 3, 3, 2, 2, 2, 1, 2, 3 };
	size_t nJobCnt = sizeof(arrInt)/sizeof(*arrInt);
	int nMachine = 10;

	CGeneticAlgorithm ga;
	ga.execOptimalSolutionGeneration(Vec_INT(arrInt, arrInt+nJobCnt), nMachine);


	JobContainer jobs = ga.getOptimalSolution();
	sort(jobs.begin(), jobs.end());
	ostringstream oss;
	oss << jobs;

	return oss.str();
}

#include "HeuristicAlgorithm.hpp"
#include "GeneticAlgorithm.hpp"

#include <Rcpp.h>
#include <string>
#include <sstream>

using namespace std;
using namespace Rcpp;
using namespace SIMSEMI;

// [[Rcpp::export]]
List TestGeneric(const int& lot, const int& machine, int population = 5000, int loop = 500, double crossover = 1., double mutation = 0.2)
{
	ostringstream oss;
	CGeneticAlgorithm ga(population, loop, crossover, mutation);

	try {
		OperationContainer Operations;
		for (int i = 1 ; i <= lot ; i++ ) {
			int step = static_cast<int>(R::runif(1,4));
			for ( int j = 1 ; j <= step ; j++ ) {
				OperationType op(i, j);
				op.dblProcTime = static_cast<int>(R::runif(20,100));
				Operations.push_back(op);
			}
		}

		cout << Operations << endl;
		ga.ExecOptimalSolutionGeneration(Operations, lot, machine);
		OperationContainer lots = ga.GetOptimalSolution();
		oss << lots;
    } catch(std::exception &ex) {
		forward_exception_to_r(ex);
    } catch(...) {
		::Rf_error("c++ exception (unknown reason)");
    }
	return List::create(oss.str(), ga.GetEvaluatedVals());
}


// [[Rcpp::export]]
List TestHeuristic(const int& lot, const int& machine, int population = 5000, int loop = 500)
{
	ostringstream oss;
	CHeuristicAlgorithm ha(population, loop);

	try {
		OperationContainer Operations;
		for (int i = 1 ; i <= lot ; i++ ) {
			int step = static_cast<int>(R::runif(1,4));
			for ( int j = 1 ; j <= step ; j++ ) {
				OperationType op(i, j);
				op.dblProcTime = static_cast<int>(R::runif(20,100));
				Operations.push_back(op);
			}
		}

		cout << Operations << endl;
		ha.ExecOptimalSolutionGeneration(Operations, lot, machine);
		OperationContainer lots = ha.GetOptimalSolution();
		oss << lots;
    } catch(std::exception &ex) {
		forward_exception_to_r(ex);
    } catch(...) {
		::Rf_error("c++ exception (unknown reason)");
    }
	return List::create(oss.str(), ha.GetEvaluatedVals());
}


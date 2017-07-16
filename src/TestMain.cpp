#include "HeuristicAlgorithm.hpp"
#include "GeneticAlgorithm.hpp"

#include <Rcpp.h>
#include <string>
#include <sstream>

using namespace std;
using namespace Rcpp;
using namespace SIMSEMI;

// [[Rcpp::export]]
List TestGenetic(const int& lot = 3, const int& machine = 3, int population = 5000, int loop = 500, double crossover = 1., double mutation = 0.2)
{
	ostringstream oss;
	CGeneticAlgorithm ga(population, loop, crossover, mutation);

	try {
		const int nLotCnt = 5;
		const int nStepMax = 3;
		const int nMachine = 5;
		int arrStep[nLotCnt] = { 3, 3, 3, 3, 3};
		int arrPrcTime[nLotCnt][nStepMax] = {
			{30, 14, 45}
			,{15, 25, 30}
			,{25, 10, 10}
			,{16, 22, 51}
			,{27, 5, 35}
		};
		int nOperationCnt = sizeof(arrStep) / sizeof(*arrStep);
		int nStepCnt = 0;


		OperationContainer Operations;
				// sum steps of all jobs
		for (int i = 0; i < nOperationCnt; nStepCnt += arrStep[i], i++);

		for (int j = 0; j < nOperationCnt; j++) {
			for (int s = 0; s < arrStep[j]; s++) {
				Operations.push_back(OperationType(j, s, -1, arrPrcTime[j][s]));
			}
		}
		/*
		for (int i = 1 ; i <= lot ; i++ ) {
			int step = static_cast<int>(R::runif(0,3));
			for ( int j = 1 ; j <= step ; j++ ) {
				OperationType op(i, j);
				op.dblProcTime = static_cast<int>(R::runif(20,100));
				Operations.push_back(op);
			}
		}
		 */

		cout << Operations << endl;
		ga.ExecOptimalSolutionGeneration(Operations, nLotCnt, nMachine); // lot, machine
		OperationContainer lots = ga.GetOptimalSolution();
		oss << lots;
    } catch(std::exception &ex) {
		forward_exception_to_r(ex);
    } catch(...) {
		::Rf_error("c++ exception (unknown reason)");
    }

	EvaluationValContainer eval = ga.GetEvaluatedVals();
	Vec_DBL vals;
	for (size_t i=0;i<eval.size();i++) {
		vals.push_back(eval[i].dblMakespan);
	}

	return List::create(oss.str(), vals);
}


// [[Rcpp::export]]
List TestHeuristic(const int& lot, const int& machine, int population = 5000, int loop = 500)
{
	ostringstream oss;
	CHeuristicAlgorithm ha(population, loop);

	try {
		OperationContainer Operations;
		for (int i = 0 ; i < lot ; i++ ) {
			int step = static_cast<int>(R::runif(0,3));
			for ( int j = 0 ; j < step+1 ; j++ ) {
				Operations.push_back(OperationType(i, j, -1, static_cast<int>(R::runif(20,100))));
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

	EvaluationValContainer eval = ha.GetEvaluatedVals();
	Vec_DBL vals;
	for (size_t i=0;i<eval.size();i++) {
		vals.push_back(eval[i].dblMakespan);
	}

	return List::create(oss.str(), vals);
}


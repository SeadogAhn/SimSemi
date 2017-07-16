#include "HeuristicAlgorithm.hpp"

#include <Rcpp.h>

using namespace std;
using namespace Rcpp;
using namespace SIMSEMI;

SIMSEMI::CHeuristicAlgorithm::CHeuristicAlgorithm(int population, int loop)
{
	Init(population, loop);
}

SIMSEMI::CHeuristicAlgorithm::~CHeuristicAlgorithm()
{
}

void SIMSEMI::CHeuristicAlgorithm::Init(int population, int loop)
{
	OperationOrderContainer().swap(Population_);
	OperationContainer().swap(GlobalBestSolution_);
	// default values
	nPopulationSize_ = population;
	nGenerationLoopLimit_ = loop;
}

void SIMSEMI::CHeuristicAlgorithm::ExecOptimalSolutionGeneration(const OperationContainer& Operations, int nLotCnt, int nMachineCnt)
{
	try {
		FeasibleSolutionGenerator_.SetOperation(Operations, nLotCnt, nMachineCnt);
		GlobalBestSolution_ = FeasibleSolutionGenerator_.GetRandomFeasibleSolution();
		EvaluationOfSolutionType gbs = FeasibleSolutionGenerator_.EvaluateOperProc(GlobalBestSolution_);
		EvaluationOfSolutionType lbs;
		for (int i = 0 ; i < nGenerationLoopLimit_ ; i++) {
			SetPopulation();
			Selection();
			lbs = FeasibleSolutionGenerator_.EvaluateOperProc(LocalBestSolution_);
			//minimize makespan
			if (gbs > lbs) {
				gbs = lbs;
				GlobalBestSolution_ = LocalBestSolution_;
				cout << "Global Best Solution's evaluated value(Makespan, Max workload, Total workload:"
					<< gbs.dblMakespan << ',' << gbs.dblMaxWorkload << ',' << gbs.dblTotalWorkload << endl;
				cout << GlobalBestSolution_ << endl;
			}
			EvaluatedVals_.push_back(gbs);
		}

		FeasibleSolutionGenerator_.MakeGanttTableData(GlobalBestSolution_);
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}
	catch (...) {
		cerr << __func__ << ":Unknown error has been caugth." << endl;
		throw domain_error("Unknown error");
	}
}

void SIMSEMI::CHeuristicAlgorithm::SetPopulation()
{
	try {
		Population_ = FeasibleSolutionGenerator_.GetRandomFeasibleSolutions(nPopulationSize_);
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}
	catch (...) {
		cerr << __func__ << ":Unknown error has been caugth." << endl;
		throw domain_error("Unknown error");
	}
}

void SIMSEMI::CHeuristicAlgorithm::Selection()
{
	try {
		EvaluationOfSolutionType lbs;
		size_t nPosLocalBest;
		for (int i = 0 ; i < nPopulationSize_ ; i++ ) {
			if (lbs < FeasibleSolutionGenerator_.EvaluateOperProc(Population_[i])) {
				nPosLocalBest = i;
			}
		}

		LocalBestSolution_ = Population_[nPosLocalBest];
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}
	catch (...) {
		cerr << __func__ << ":Unknown error has been caugth." << endl;
		throw domain_error("Unknown error");
	}
}

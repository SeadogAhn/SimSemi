#include "GeneticAlgorithm.hpp"

#include <Rcpp.h>

using namespace std;
using namespace Rcpp;
using namespace SIMSEMI;


SIMSEMI::CGeneticAlgorithm::CGeneticAlgorithm(int population, int loop, double Crossover, double Mutation)
{
	Init(population, loop, Crossover, Mutation);
}

SIMSEMI::CGeneticAlgorithm::~CGeneticAlgorithm()
{
}

void SIMSEMI::CGeneticAlgorithm::Init(int population, int loop, double Crossover, double Mutation)
{
	OperationOrderContainer().swap(Population_);
	OperationContainer().swap(GlobalBestSolution_);
	// default values
	nPopulationSize_ = population;
	nGenerationLoopLimit_ = loop;
	dblCrossoverRate_ = Crossover;
	dblMutationRate_ = Mutation;
}

void SIMSEMI::CGeneticAlgorithm::ExecOptimalSolutionGeneration(const OperationContainer& Operations, int nLotCnt, int nMachineCnt)
{
	try {
		FeasibleSolutionGenerator_.SetOperation(Operations, nLotCnt, nMachineCnt);
		// first time to initialize the poputlation and the global best solution.
		SetPopulation();
		GlobalBestSolution_ = GetBestSolutionInPopulation(Population_);
		double gbs = FeasibleSolutionGenerator_.EvaluateOperProc(GlobalBestSolution_);
		double lbs = numeric_limits<double>::max();

		for (int i = 0 ; i < nGenerationLoopLimit_ ; i++) {
			Selection();
			Crossover();
			Mutation();
			lbs = FeasibleSolutionGenerator_.EvaluateOperProc(Offspring_);
			//minimize makespan
			if (gbs > lbs) {
				gbs = lbs;
				GlobalBestSolution_ = Offspring_;
				//EvaluatedVals_.push_back(lbs);
				cout << "Global Best Solution's evaluated value:" << lbs << endl;
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

void SIMSEMI::CGeneticAlgorithm::SetPopulation()
{
	try {
		Population_ = FeasibleSolutionGenerator_.GetRandomFeasibleSolutions(nPopulationSize_, Population_);
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

const SIMSEMI::OperationContainer SIMSEMI::CGeneticAlgorithm::GetBestSolutionInPopulation(const OperationOrderContainer& population)
{
	size_t nPosLocalBest = 0;

	try {
		double lbs = 0.;
		for (size_t i = 0 ; i < population.size() ; i++ ) {
			if (lbs < FeasibleSolutionGenerator_.EvaluateOperProc(population[i])) {
				nPosLocalBest = i;
			}
		}
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}
	catch (...) {
		cerr << __func__ << ":Unknown error has been caugth." << endl;
		throw domain_error("Unknown error");
	}
	return population[nPosLocalBest];
}

void SIMSEMI::CGeneticAlgorithm::Selection()
{
	try {
		while (1) {
			Parent1_ = GlobalBestSolution_;
			Parent2_ = GetBestSolutionInPopulation(FeasibleSolutionGenerator_.GetRandomFeasibleSolutions(nPopulationSize_));
			if (Parent1_ != Parent2_) {
				break;
			}
		}
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

void SIMSEMI::CGeneticAlgorithm::Crossover()
{
	try {
		size_t cp = 0;
		double r = R::runif(0,1);
		if (r < dblCrossoverRate_) {
			while (1) {
				// clear offspring
				OperationContainer().swap(Offspring_);
				cp = static_cast<int>(R::runif(0,Parent1_.size()));
				/*
						   cp
						|  |   |
					p1 1093457682
					p2 2193468750
					o  1093246875
				*/

				Offspring_.insert(Offspring_.begin(), Parent1_.begin(), Parent1_.begin()+cp);
				for (size_t i = 0 ; i < Parent2_.size() ; i++) {
					if ( find(Offspring_.begin(), Offspring_.end(), Parent2_[i]) == Offspring_.end() ) {
						Offspring_.push_back(Parent2_[i]);
					}
				}

				if (FeasibleSolutionGenerator_.CheckPolicy(Offspring_)) break;
			}
		}
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

void SIMSEMI::CGeneticAlgorithm::Mutation()
{
	try {
		double r = R::runif(0,1);
		if (r < dblMutationRate_) {
			size_t cp1 = static_cast<int>(R::runif(0,Offspring_.size()));
			size_t cp2 = static_cast<int>(R::runif(0,Offspring_.size()));
			swap(Offspring_[cp1].nMachine, Offspring_[cp2].nMachine);
		}
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

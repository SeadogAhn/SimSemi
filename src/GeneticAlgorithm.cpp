#include "GeneticAlgorithm.hpp"

#include <Rcpp.h>

using namespace std;
using namespace Rcpp;
using namespace SIMSEMI;

SIMSEMI::CGeneticAlgorithm::CGeneticAlgorithm(int population, int loop, double crossover, double mutation)
{
	init(population, loop, crossover, mutation);
}

SIMSEMI::CGeneticAlgorithm::~CGeneticAlgorithm()
{
}

void SIMSEMI::CGeneticAlgorithm::init(int population, int loop, double crossover, double mutation)
{
	JobsContainer().swap(Population_);
	JobContainer().swap(GlobalBestSolution_);
	// default values
	nPopulationSize_ = population;
	nGenerationLoopLimit_ = loop;
	dblCrossoverRate_ = crossover;
	dblMutationRate_ = mutation;
}

void SIMSEMI::CGeneticAlgorithm::execOptimalSolutionGeneration(const std::vector<int>& StepInfo, int nMachineCnt)
{
	cout << __FUNCTION__ << ":START" << endl;

	FeasibleSolutionGenerator_.setOperation(StepInfo, nMachineCnt);
	//setPopulation();
	double gbs = numeric_limits<double>::max();
	double ofs = numeric_limits<double>::max();
	for (int i = 0 ; i < nGenerationLoopLimit_ ; i++) {
		selection();
		crossover();
		mutation();
		ofs = FeasibleSolutionGenerator_.evaluateJobs(Offspring_);
		//minimize makespan
		if (gbs > ofs) {
			gbs = ofs;
			GlobalBestSolution_ = Offspring_;
			//EvaluatedVals_.push_back(ofs);
			FeasibleSolutionGenerator_.makeGanttTableData(GlobalBestSolution_);
			//cout << "Global Best Solution's evaluated value:" << ofs << endl;
			//cout << GlobalBestSolution_ << endl;
		}
		EvaluatedVals_.push_back(gbs);
	}
	cout << __FUNCTION__ << ":END" << endl;
}

void SIMSEMI::CGeneticAlgorithm::setPopulation()
{
	Population_ = FeasibleSolutionGenerator_.getRandomFeasibleSolutions(nPopulationSize_, Population_);
}

void SIMSEMI::CGeneticAlgorithm::selection()
{
	while (1) {
		// Population_[static_cast<int>(R::runif(0,nPopulationSize_))];
		Parent1_ = FeasibleSolutionGenerator_.getRandomFeasibleSolution();
		Parent2_ = FeasibleSolutionGenerator_.getRandomFeasibleSolution();
		if (Parent1_ != Parent2_) {
			break;
		}
	}
	//cout << "P1:" << Parent1_ << endl;
	//cout << "P2:" << Parent2_ << endl;
}

void SIMSEMI::CGeneticAlgorithm::crossover()
{
	size_t cp = 0;
	double r = R::runif(0,1);
	if (r < dblCrossoverRate_) {
		while (1) {
			// clear offspring
			JobContainer().swap(Offspring_);
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

			if (FeasibleSolutionGenerator_.checkPolicy(Offspring_)) break;
		}
	}
}

void SIMSEMI::CGeneticAlgorithm::mutation()
{
	double r = R::runif(0,1);
	if (r < dblMutationRate_) {
		size_t cp1 = static_cast<int>(R::runif(0,Offspring_.size()));
		size_t cp2 = static_cast<int>(R::runif(0,Offspring_.size()));
		swap(Offspring_[cp1].machine, Offspring_[cp2].machine);
	}
}

void SIMSEMI::CGeneticAlgorithm::decode()
{

}

void SIMSEMI::CGeneticAlgorithm::encode()
{

}

void SIMSEMI::CGeneticAlgorithm::statistics()
{

}


#include "FeasibleSolutionGenerator.hpp"

#include <algorithm>

using namespace std;
using namespace SIMSEMI;

SIMSEMI::CFeasibleSolutionGenerator::CFeasibleSolutionGenerator()
{
	nJobCnt_ = 0;
	nStepCnt_ = 0;
	nMachineCnt_ = 0;
}

SIMSEMI::CFeasibleSolutionGenerator::~CFeasibleSolutionGenerator()
{
}

void SIMSEMI::CFeasibleSolutionGenerator::setOperation(const std::vector<int>& StepInfo, int nMachineCnt)
{
	nJobCnt_ = StepInfo.size();
	nMachineCnt_ = nMachineCnt;
	// sum steps of all jobs
	for (int i = 0 ; i < nJobCnt_ ; nStepCnt_+=StepInfo[i], i++);

	for (int j = 0; j < nJobCnt_; j++) {
		for (int s = 0; s < StepInfo[j]; s++) {
			Jobs_.push_back(OperationType(j, s));
		}
	}
}

const JobContainer SIMSEMI::CFeasibleSolutionGenerator::getRandomFeasibleSolution()
{
	JobContainer Jobs;

	initMachine(Jobs);
	return Jobs;
}

const std::vector<JobContainer> SIMSEMI::CFeasibleSolutionGenerator::getRandomFeasibleSolutions(int n)
{
	std::vector<JobContainer> tempContainer;
	while (tempContainer.size() < n) {
		JobContainer tempJobs = getRandomFeasibleSolution();
		if (find(tempContainer.begin(), tempContainer.end(), tempJobs) != tempContainer.end()) {
			tempContainer.push_back(tempJobs);
		}
	}
	return tempContainer;
}

const JobContainer SIMSEMI::CFeasibleSolutionGenerator::getNeighborhoodJobs(const JobContainer& Jobs)
{
	JobContainer tempJobs = Jobs;
	permutate(tempJobs);
	return tempJobs;
}

void SIMSEMI::CFeasibleSolutionGenerator::permutate(JobContainer& Jobs)
{
	while (1) {
		next_permutation(Jobs.begin(), Jobs.end());
		if (checkPolicy(Jobs)) {
			break;
		}
	}
}

bool SIMSEMI::CFeasibleSolutionGenerator::checkPolicy(const JobContainer& Jobs)
{
	for (size_t p1 = 0; p1 < Jobs.size() - 1; p1++) {
		for (size_t p2 = p1 + 1; p2 < Jobs.size(); p2++) {
			if ((Jobs[p1].job == Jobs[p2].job) && Jobs[p1].step > Jobs[p2].step) {
				return false;
			}
		}
	}
	return true;
}

void SIMSEMI::CFeasibleSolutionGenerator::initMachine(JobContainer& Jobs)
{
	if (Jobs.empty())
		return;

	int64_t nRndMax = (uint64_t)(pow((double)(nMachineCnt_), (double)(nStepCnt_)));
	CIntRandom rnd(0, nRndMax);

	int64_t n = rnd.execNumberGenerate();

	// create vectmachine and initialize elements
	vector<int> vecMachine(Jobs.size());

	for (int i = vecMachine.size() - 1 ; i >= 0; i--) {
		if (n <= 0) break;
		vecMachine[i] = n % nMachineCnt_;
		n = (n - vecMachine[i]) / nMachineCnt_;
	}

	for (size_t i = 0; i < Jobs.size(); i++) {
		Jobs[i].machine = vecMachine[i];
	}
}

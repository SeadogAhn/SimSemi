#include "FeasibleSolutionGenerator.hpp"

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>

#include <Rcpp.h>

using namespace std;
using namespace Rcpp;
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
	JobsQueue_.resize(nJobCnt_);

	// sum steps of all jobs
	for (int i = 0 ; i < nJobCnt_ ; nStepCnt_+=StepInfo[i], i++);

	for (int j = 0; j < nJobCnt_; j++) {
		for (int s = 0; s < StepInfo[j]; s++) {
			Jobs_.push_back(OperationType(j, s));
			JobsQueue_[j].push(s);
		}
	}

	cout << "JOBS:" << Jobs_ << endl;
}

const JobContainer SIMSEMI::CFeasibleSolutionGenerator::getRandomFeasibleSolution()
{
	JobContainer Jobs;
	JobQueueType JobsQueue(JobsQueue_);

	while (1) {
		if (Jobs.size() == Jobs_.size()) {
			break;
		}
		int r = static_cast<int>(R::runif(0,JobsQueue.size()));
		if (JobsQueue[r].empty()) {
			continue;
		}
		else {
			Jobs.push_back(OperationType(r, JobsQueue[r].front()));
			JobsQueue[r].pop();
		}
	}
	initMachine(Jobs);
	return Jobs;
}

const JobsContainer SIMSEMI::CFeasibleSolutionGenerator::getRandomFeasibleSolutions(size_t n, const JobsContainer& solutions)
{
	JobsContainer tempContainer;
	while (tempContainer.size() < n) {
		JobContainer tempJobs = getRandomFeasibleSolution();
		if (!solutions.empty() && find(solutions.begin(), solutions.end(), tempJobs) != solutions.end()) {
			continue;
		}
		if (find(tempContainer.begin(), tempContainer.end(), tempJobs) != tempContainer.end()) {
			continue;
		}
		tempContainer.push_back(tempJobs);
	}
	return tempContainer;
}

const JobContainer SIMSEMI::CFeasibleSolutionGenerator::getNeighborhoodJobs(const JobContainer& Jobs)
{
	JobContainer tempJobs = Jobs;
	permutate(tempJobs);
	return tempJobs;
}

void SIMSEMI::CFeasibleSolutionGenerator::generateMachineJobOrder( const JobContainer& Jobs )
{
	MachineJobOrderType().swap(MachineJobOrders_);
	MachineJobOrders_.resize(nMachineCnt_);

	// wait time when product is changed
	const int nWaitTimeForChangingProduct = 5;
	// operation loop
	for ( size_t nPosJob = 0 ; nPosJob < Jobs.size() ; nPosJob++ ) {
		OperationTimeType ot;
		ot.Operation = Jobs[nPosJob];
		// if first step
		if ( Jobs[nPosJob].step == 0 ) {
			// if there is no another job in a Machine
			if ( MachineJobOrders_[Jobs[nPosJob].machine].empty() ) {
				ot.dblStartTime = 0.;
				ot.dblEndTime = Jobs[nPosJob].prctime;
			}
			else {
				ot.dblStartTime = MachineJobOrders_[Jobs[nPosJob].machine].back().dblEndTime + nWaitTimeForChangingProduct;
				ot.dblEndTime = ot.dblStartTime + Jobs[nPosJob].prctime;
			}
		}
		// operation is not first step
		else {
			// find the same job's end time of the pre step
			double preStepEndTime = 0.;
			for ( size_t nPosMachine = 0 ; nPosMachine < MachineJobOrders_.size() ; nPosMachine++ ) {
				for ( size_t nPosJobOrder = 0 ; nPosJobOrder < MachineJobOrders_[nPosMachine].size() ; nPosJobOrder++ ) {
					if ( Jobs[nPosJob].job == MachineJobOrders_[nPosMachine][nPosJobOrder].Operation.job
              			&& Jobs[nPosJob].step - 1 == MachineJobOrders_[nPosMachine][nPosJobOrder].Operation.step ) {
						preStepEndTime = MachineJobOrders_[nPosMachine][nPosJobOrder].dblEndTime + nWaitTimeForChangingProduct;
					}
				}
			}
			// if there is no another job in a Machine
			if ( MachineJobOrders_[Jobs[nPosJob].machine].empty() ) {
				ot.dblStartTime = preStepEndTime;
				ot.dblEndTime = ot.dblStartTime + Jobs[nPosJob].prctime;
			}
			else {
				if ( preStepEndTime > MachineJobOrders_[Jobs[nPosJob].machine].back().dblEndTime ) {
					ot.dblStartTime = preStepEndTime;
					ot.dblEndTime = ot.dblStartTime + Jobs[nPosJob].prctime;
				}
				else {
					ot.dblStartTime = MachineJobOrders_[Jobs[nPosJob].machine].back().dblEndTime + nWaitTimeForChangingProduct;
					ot.dblEndTime = ot.dblStartTime + Jobs[nPosJob].prctime;
				}
			}
		}
		MachineJobOrders_[Jobs[nPosJob].machine].push_back(ot);
	}
}

double SIMSEMI::CFeasibleSolutionGenerator::evaluateJobs(const JobContainer& Jobs)
{
	double val = 0.;

	generateMachineJobOrder( Jobs );

	for ( size_t nPosMachine = 0 ; nPosMachine < MachineJobOrders_.size() ; nPosMachine++ ) {
		for ( size_t nPosJobOrder = 0 ; nPosJobOrder < MachineJobOrders_[nPosMachine].size() ; nPosJobOrder++ ) {
			val = max(MachineJobOrders_[nPosMachine][nPosJobOrder].dblEndTime, val);
		}
	}

	return val;
}

void SIMSEMI::CFeasibleSolutionGenerator::makeGanttTableData(const JobContainer& Jobs)
{
	static int nIdx = 0;
	ostringstream oss;
	oss << "D:\\temp\\GanData" << nIdx++ << ".txt";
	ofstream ofs(oss.str().c_str());

	generateMachineJobOrder( Jobs );

	ofs << "group|content|start|end" << endl;
	for ( size_t nPosMachine = 0 ; nPosMachine < MachineJobOrders_.size() ; nPosMachine++ ) {
		for ( size_t nPosJobOrder = 0 ; nPosJobOrder < MachineJobOrders_[nPosMachine].size() ; nPosJobOrder++ ) {
			ofs << nPosMachine
       			<< '|' << "O(" << MachineJobOrders_[nPosMachine][nPosJobOrder].Operation.job << ',' << MachineJobOrders_[nPosMachine][nPosJobOrder].Operation.step << ')'
       			<< '|' << MachineJobOrders_[nPosMachine][nPosJobOrder].dblStartTime
       			<< '|' << MachineJobOrders_[nPosMachine][nPosJobOrder].dblEndTime
          		<< endl;
		}
	}
	ofs.close();
}

void SIMSEMI::CFeasibleSolutionGenerator::permutate(JobContainer& Jobs)
{
	while (1) {
		next_permutation(Jobs.begin(), Jobs.end());
		if (checkPolicy(Jobs)) break;
	}
}

void SIMSEMI::CFeasibleSolutionGenerator::initMachine(JobContainer& Jobs)
{
	if (Jobs.empty())
		return;

	for (size_t i = 0 ; i < Jobs.size() ; i++) {
		Jobs[i].machine =  static_cast<int>(R::runif(0,nMachineCnt_));
	}
}

bool SIMSEMI::CFeasibleSolutionGenerator::checkPolicy(const JobContainer& Jobs)
{
	if (Jobs.empty() || Jobs.size() < 2) return true;

	for (size_t p1 = 0; p1 < Jobs.size() - 1; p1++) {
		for (size_t p2 = p1 + 1; p2 < Jobs.size(); p2++) {
			// p1, p2 job and machine are same but p1 step is greater than p2
			if ((Jobs[p1].job == Jobs[p2].job) && Jobs[p1].step > Jobs[p2].step && Jobs[p1].machine == Jobs[p2].machine) {
				return false;
			}
		}
	}
	return true;
}

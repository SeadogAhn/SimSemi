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
	nLotCnt_ = 0;
	nMachineCnt_ = 0;
}

SIMSEMI::CFeasibleSolutionGenerator::~CFeasibleSolutionGenerator()
{
}

void SIMSEMI::CFeasibleSolutionGenerator::SetOperation(const OperationContainer& Operations, int nLotCnt, int nMachineCnt)
{
	try {
		if (Operations.empty()) {
			return;
		}
		Operations_ = Operations;
		nLotCnt_ = nLotCnt;
		nMachineCnt_ = nMachineCnt;
		OperQueue_.resize(nLotCnt_);
		for (size_t i = 0 ; i < Operations_.size(); i++ ) {
			OperQueue_[Operations_[i].nLot].push_back(Operations_[i]);
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

const OperationContainer SIMSEMI::CFeasibleSolutionGenerator::GetRandomFeasibleSolution()
{
	OperationContainer Operations;

	try {
		OperationQueue OperQueue(OperQueue_);

		while (1) {
			if (Operations.size() == Operations_.size()) {
				break;
			}
			int r = static_cast<int>(R::runif(0,OperQueue.size()));

			Operations.push_back(OperQueue[r].front());
			OperQueue[r].pop_front();

			if (OperQueue[r].empty()) {
				OperationQueue::iterator itor = OperQueue.begin()+r;
				OperQueue.erase(itor);
			}
		}
		InitMachine(Operations);
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}
	catch (...) {
		cerr << __func__ << ":Unknown error has been caugth." << endl;
		throw domain_error("Unknown error");
	}

	return Operations;
}

const OperationOrderContainer SIMSEMI::CFeasibleSolutionGenerator::GetRandomFeasibleSolutions(size_t n, const OperationOrderContainer& Solutions)
{
	OperationOrderContainer tempOrderContainer;

	try {
		while (tempOrderContainer.size() <= n) {
			OperationContainer tempOperations = GetRandomFeasibleSolution();
			/*	it doesn't compare with the Solution and tempOperations
				some solutions are duplicated if small solution space.

			if (!Solutions.empty() && find(Solutions.begin(), Solutions.end(), tempOperations) != Solutions.end()) {
				continue;
			}
			if (find(tempOrderContainer.begin(), tempOrderContainer.end(), tempOperations) != tempOrderContainer.end()) {
				continue;
			}
			*/
			tempOrderContainer.push_back(tempOperations);
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

	return tempOrderContainer;
}

const OperationContainer SIMSEMI::CFeasibleSolutionGenerator::GetNeighborhoodOperProc(const OperationContainer& Operations)
{
	OperationContainer tempOperations = Operations;

	try {
		Permutate(tempOperations);
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}
	catch (...) {
		cerr << __func__ << ":Unknown error has been caugth." << endl;
		throw domain_error("Unknown error");
	}

	return tempOperations;
}

void SIMSEMI::CFeasibleSolutionGenerator::OrderOperationMachine( const OperationContainer& Operations )
{
	try {
		OperationOrderContainer().swap(OperationsOrder_);
		OperationsOrder_.resize(nMachineCnt_);

		// wait time when product is changed
		const int nWaitTimeForChangingProduct = 5;
		// operation loop
		for ( size_t nPosJob = 0 ; nPosJob < Operations.size() ; nPosJob++ ) {
			OperationType ot;
			ot = Operations[nPosJob];
			// if first step
			if ( Operations[nPosJob].nStep == 0 ) {
				// if there is no another lot in a Machine
				if ( OperationsOrder_[Operations[nPosJob].nMachine].empty() ) {
					ot.dblStartTime = 0.;
					ot.dblEndTime = Operations[nPosJob].dblProcTime;
				}
				else {
					ot.dblStartTime = OperationsOrder_[Operations[nPosJob].nMachine].back().dblEndTime + nWaitTimeForChangingProduct;
					ot.dblEndTime = ot.dblStartTime + Operations[nPosJob].dblProcTime;
				}
			}
			// operation is not first step
			else {
				// find the same lot's end time of the pre step
				double preStepEndTime = 0.;
				for ( size_t nPosMachine = 0 ; nPosMachine < OperationsOrder_.size() ; nPosMachine++ ) {
					for ( size_t nPosJobOrder = 0 ; nPosJobOrder < OperationsOrder_[nPosMachine].size() ; nPosJobOrder++ ) {
						if ( Operations[nPosJob].nLot == OperationsOrder_[nPosMachine][nPosJobOrder].nLot
							&& Operations[nPosJob].nStep - 1 == OperationsOrder_[nPosMachine][nPosJobOrder].nStep ) {
							preStepEndTime = OperationsOrder_[nPosMachine][nPosJobOrder].dblEndTime + nWaitTimeForChangingProduct;
						}
					}
				}
				// if there is no another lot in a Machine
				if ( OperationsOrder_[Operations[nPosJob].nMachine].empty() ) {
					ot.dblStartTime = preStepEndTime;
					ot.dblEndTime = ot.dblStartTime + Operations[nPosJob].dblProcTime;
				}
				else {
					if ( preStepEndTime > OperationsOrder_[Operations[nPosJob].nMachine].back().dblEndTime ) {
						ot.dblStartTime = preStepEndTime;
						ot.dblEndTime = ot.dblStartTime + Operations[nPosJob].dblProcTime;
					}
					else {
						ot.dblStartTime = OperationsOrder_[Operations[nPosJob].nMachine].back().dblEndTime + nWaitTimeForChangingProduct;
						ot.dblEndTime = ot.dblStartTime + Operations[nPosJob].dblProcTime;
					}
				}
			}
			OperationsOrder_[Operations[nPosJob].nMachine].push_back(ot);
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

double SIMSEMI::CFeasibleSolutionGenerator::EvaluateOperProc(const OperationContainer& Operations)
{
	double val = 0.;

	try {
		OrderOperationMachine(Operations);

		for ( size_t nPosMachine = 0 ; nPosMachine < OperationsOrder_.size() ; nPosMachine++ ) {
			for ( size_t nPosJobOrder = 0 ; nPosJobOrder < OperationsOrder_[nPosMachine].size() ; nPosJobOrder++ ) {
				val = max(OperationsOrder_[nPosMachine][nPosJobOrder].dblEndTime, val);
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

	return val;
}

void SIMSEMI::CFeasibleSolutionGenerator::MakeGanttTableData(const OperationContainer& Operations, std::string strFileName)
{
	try {
		static int nIdx = 0;
		ostringstream oss;
		oss << strFileName << nIdx++ << ".txt";
		ofstream ofs(oss.str().c_str());

		OrderOperationMachine( Operations );

		ofs << "group|content|start|end" << endl;
		for (size_t nPosMachine = 0 ; nPosMachine < OperationsOrder_.size() ; nPosMachine++) {
			for (size_t nPosJobOrder = 0 ; nPosJobOrder < OperationsOrder_[nPosMachine].size() ; nPosJobOrder++) {
				ofs << nPosMachine
					<< '|' << "O(" << OperationsOrder_[nPosMachine][nPosJobOrder].nLot << ',' << OperationsOrder_[nPosMachine][nPosJobOrder].nStep << ')'
					<< '|' << OperationsOrder_[nPosMachine][nPosJobOrder].dblStartTime
					<< '|' << OperationsOrder_[nPosMachine][nPosJobOrder].dblEndTime
					<< endl;
			}
		}
		ofs.close();
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

void SIMSEMI::CFeasibleSolutionGenerator::Permutate(OperationContainer& Operations)
{
	try {
		while (1) {
			next_permutation(Operations.begin(), Operations.end());
			if (CheckPolicy(Operations)) break;
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

void SIMSEMI::CFeasibleSolutionGenerator::InitMachine(OperationContainer& Operations)
{
	try {
		if (Operations.empty())
			return;

		for (size_t i = 0 ; i < Operations.size() ; i++) {
			Operations[i].nMachine =  static_cast<int>(R::runif(0,(nMachineCnt_)));
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

bool SIMSEMI::CFeasibleSolutionGenerator::CheckPolicy(const OperationContainer& Operations)
{
	try {
		if (Operations.size() < 2) return true;

		for (size_t p1 = 0; p1 < Operations.size() - 1; p1++) {
			for (size_t p2 = p1 + 1; p2 < Operations.size(); p2++) {
				// p1, p2 lot and machine are same but p1 step is greater than p2
				if ((Operations[p1].nLot == Operations[p2].nLot) && Operations[p1].nStep > Operations[p2].nStep && Operations[p1].nMachine == Operations[p2].nMachine) {
					return false;
				}
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
	return true;
}

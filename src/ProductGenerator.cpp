#include "ProductGenerator.hpp"
#include "Utility.hpp"

#include <fstream>
#include <string>
#include <stdexcept>

#include <Rcpp.h>

using namespace std;
using namespace Rcpp;

SIMSEMI::CProductGenerator::CProductGenerator()
{
}

SIMSEMI::CProductGenerator::~CProductGenerator()
{
}

void SIMSEMI::CProductGenerator::InitProductMasterPlan(const std::string& strFileName)
{
	try {
		enum enumLabelPos{ ePARTID, QUANTITY, eLABELSIZE };
		ifstream ifs(strFileName.c_str());
		string strTemp;
		/*	read header
			0      1
			PARTID,QUANTITY
			0,2000
		*/
		getline(ifs,strTemp);

		Vec_STR vecTemp;
		int nPart = 0, nQuantity = 0;

		// read master plan and make products
		while (getline(ifs,strTemp)) {
			if (ifs.eof() || strTemp.empty()) break;
			fnStringSpliter(vecTemp, strTemp);
			if (vecTemp.size() < eLABELSIZE) throw domain_error(strFileName+" is wrong foramt.");

			nPart = atoi(vecTemp[ePARTID].c_str());
			nQuantity = atoi(vecTemp[QUANTITY].c_str());

			Products_.insert(make_pair(nPart, MakeLots(nQuantity)));
		}

		ifs.close();
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}
}

void SIMSEMI::CProductGenerator::AddNewDemand(int nPart, int nQuantity)
{
	try {
		LotContainer tempLots = MakeLots(nQuantity);
		if (Products_.find(nPart) != Products_.end()) {
			Products_[nPart].insert(Products_[nPart].end(), tempLots.begin(), tempLots.end());
		}
		else {
			Products_.insert(make_pair(nPart, tempLots));
		}
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}
}

SIMSEMI::CProductGenerator::LotContainer SIMSEMI::CProductGenerator::MakeLots(int nQuantity)
{
	static int nLot = 1;
	LotContainer Lots;
	int nWaferCnt = 0;

	try {
		while (nQuantity > 0) {
			nWaferCnt = 25; // need to generate random number;
			CLot Lot(nLot, nWaferCnt);
			Lots.push_back(Lot);
			nQuantity -= nWaferCnt;
			nLot++;
		}
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}

	return Lots;
}

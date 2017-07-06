#include "ProductSpecification.hpp"
#include "Utility.hpp"

#include <fstream>
#include <stdexcept>

using namespace std;

SIMSEMI::CProductSpecification::CProductSpecification()
{
}

SIMSEMI::CProductSpecification::~CProductSpecification()
{
}

void SIMSEMI::CProductSpecification::InitProductSpecification(const std::string& strFileName)
{
	try {
		enum enumLabelPos{ ePARTID, eSTEPCNT, eSTEP1, eSTEP2, eSTEP3, eYLD_MEAN, eYLD_STDDEV, ePRICE, eLABELSIZE };
		ifstream ifs(strFileName.c_str());
		string strTemp;
		/*	read header
			0      1       2     3     4     5        6          7
			PARTID,STEPCNT,STEP1,STEP2,STEP3,YLD_MEAN,YLD_STDDEV,PRICE
			1,3,25,25,25,75,5,100
		*/
		getline(ifs,strTemp);

		Vec_STR vecTemp;
		while (getline(ifs,strTemp)) {
			if (ifs.eof() || strTemp.empty()) break;
			fnStringSpliter(vecTemp, strTemp);
			if (vecTemp.size() < eLABELSIZE) throw domain_error(strFileName+" is wrong foramt.");

			ProductAttributeType pa;
			pa.nPart = atoi(vecTemp[ePARTID].c_str());
			pa.nStepCnt = atoi(vecTemp[eSTEPCNT].c_str());
			for (size_t i = eSTEP1; i < eSTEP1+pa.nStepCnt ; i++) {
				pa.ProcTimes.push_back(atof(vecTemp[i].c_str()));
			}
			pa.dblProdYieldMean = atof(vecTemp[eYLD_MEAN].c_str());
			pa.dblProdYieldStdDev = atof(vecTemp[eYLD_STDDEV].c_str());
			pa.dblPrice = atof(vecTemp[ePRICE].c_str());

			AddProductAttribute(pa);
		}

		ifs.close();
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}
}

void SIMSEMI::CProductSpecification::AddProductAttribute(const ProductAttributeType& pa)
{
	try {
		RemoveProductAttribute(pa.nPart);
		ProductAttributes_.insert(make_pair(pa.nPart, pa));
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}
}

void SIMSEMI::CProductSpecification::RemoveProductAttribute(const int& nPart)
{
	try {
		ProductAttributeContainer::iterator itor = ProductAttributes_.find(nPart);
		if (itor != ProductAttributes_.end()) {
			ProductAttributes_.erase(itor);
		}
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}
}

const SIMSEMI::ProductAttributeType* SIMSEMI::CProductSpecification::GetProductAttribute(int nPart)
{
	try {
		ProductAttributeContainer::const_iterator citor = ProductAttributes_.find(nPart);
		if (citor != ProductAttributes_.end()) {
			return &ProductAttributes_[nPart];
		}
		else {
			return NULL;
		}
	}
	catch (std::exception& error) {
		cerr << __func__ << ':' << error.what() << endl;
		throw error;
	}
}

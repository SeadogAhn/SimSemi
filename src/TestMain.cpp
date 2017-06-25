#include "GeneticAlgorithm.hpp"

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
const std::vector<double> TestMain()
{
	std::vector<double> vec;
	for (int i = 0 ; i < 10 ; i++ ) {
		vec.push_back(i);
	}

	return vec;
}


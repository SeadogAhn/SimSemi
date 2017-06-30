// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// TestMain
List TestMain(const int& n, const int& m, int population, int loop, double crossover, double mutation);
RcppExport SEXP SimSemi_TestMain(SEXP nSEXP, SEXP mSEXP, SEXP populationSEXP, SEXP loopSEXP, SEXP crossoverSEXP, SEXP mutationSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const int& >::type n(nSEXP);
    Rcpp::traits::input_parameter< const int& >::type m(mSEXP);
    Rcpp::traits::input_parameter< int >::type population(populationSEXP);
    Rcpp::traits::input_parameter< int >::type loop(loopSEXP);
    Rcpp::traits::input_parameter< double >::type crossover(crossoverSEXP);
    Rcpp::traits::input_parameter< double >::type mutation(mutationSEXP);
    rcpp_result_gen = Rcpp::wrap(TestMain(n, m, population, loop, crossover, mutation));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"SimSemi_TestMain", (DL_FUNC) &SimSemi_TestMain, 6},
    {NULL, NULL, 0}
};

RcppExport void R_init_SimSemi(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}

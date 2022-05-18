#include <Rcpp.h>
#include <cmath>
#include <iostream>
using namespace Rcpp;

// This function calculates the ratio of confidence
int ratio(IntegerVector& vec, const int& n){
    float pmax1 = 0;
    float pmax2 = 0;

    for (int i = 0; i < n; ++i){
        float prob_i = float(vec(i)/10000.);
        if (prob_i > pmax1) {
            pmax2 = pmax1;
            pmax1 = prob_i;
        } else if (prob_i > pmax2) {
            pmax2 = prob_i;
        }
    }
    float ratio = 0;
    if (pmax1 > 0) {
        ratio = pmax2 / pmax1;
    }
    int i_ratio = (int)(10000 * ratio);
    return i_ratio;
}
// [[Rcpp::export]]
IntegerVector ratio_probs(const IntegerMatrix& mtx, const int& n) {

    int nrows = mtx.nrow();
    int ncols = mtx.ncol();

    IntegerVector vec(ncols);
    IntegerVector unc(nrows);

    for (int i = 0; i < nrows; i++) {
        IntegerVector vec = mtx(i, _);
        unc(i) = ratio(vec, n);
    }
    return unc;
}


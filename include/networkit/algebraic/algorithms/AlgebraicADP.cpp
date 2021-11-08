//
// Created by valentin on 07.11.21.
//

#include "AlgebraicADP.h"

#include <networkit/io/KONECTGraphReader.hpp>
#include <iostream>

namespace NetworKit {

    AlgebraicADP::AlgebraicADP(const std::string &path) {
        Graph graph = KONECTGraphReader().read(path);
        count nonZeros = graph.isDirected() ? graph.numberOfEdges() : graph.numberOfEdges() * 2;
        std::vector<Triplet> triplets(nonZeros);
        index idx = 0;
        graph.forEdges([&](node i, node j, double val) {
            triplets[idx++] = {i, j, val};
            if (!graph.isDirected() && i != j)
                triplets[idx++] = {j, i, val};
        });

        this->a =  DenseMatrix(graph.upperNodeIdBound(), triplets);
    }


    void AlgebraicADP::run() {
        DenseMatrix d = recursive_calculation(a);
        for(int i = 0; i < d.numberOfRows(); ++i){
            for(int j = 0; j < d.numberOfColumns(); ++j) {
                std::cout<<d(i,j)<<" ";
            }
        }
    }

    DenseMatrix AlgebraicADP::recursive_calculation(DenseMatrix a) {
        if(a.numberOfRows() * a.numberOfColumns() == a.nnz())
        {
            return a*a-a;
        }
        DenseMatrix z = a*a;
        DenseMatrix a_prime = compute_a_prime(a, z);
        DenseMatrix d_prime = recursive_calculation(a_prime);
        DenseMatrix s = a*d_prime;
        DenseMatrix d = DenseMatrix(d_prime.numberOfRows(), d_prime.numberOfColumns());
        for(int i = 0; i < d.numberOfRows(); ++i){
            for(int j = 0; j < d.numberOfColumns(); ++j) {
                if(s(i,j) > d_prime(i,j)*z(i,i)) {
                    d.setValue(i,j,2*d_prime(i,j));
                }
                else{
                    d.setValue(i,j,2*d_prime(i,j)-1);
                }
            }
        }
        return d;
    }

    DenseMatrix AlgebraicADP::compute_a_prime(DenseMatrix a, DenseMatrix z) {
        DenseMatrix a_prime = a + z;
        a_prime.apply([](double a){return a > 0;});
        return a_prime;
    }
}
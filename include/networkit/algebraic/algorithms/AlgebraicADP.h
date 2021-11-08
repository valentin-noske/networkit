//
// Created by valentin on 07.11.21.
//

#ifndef NETWORKIT_ALGEBRAICADP_H
#define NETWORKIT_ALGEBRAICADP_H

#include <networkit/base/Algorithm.hpp>
#include <networkit/graph/Graph.hpp>
#include <networkit/algebraic/DenseMatrix.hpp>

namespace NetworKit {

    class AlgebraicADP: public Algorithm {
    public:
        AlgebraicADP(const std::string &path);

        ~AlgebraicADP() = default;

        void run();

    private:
        DenseMatrix a;

        DenseMatrix recursive_calculation(DenseMatrix a);

        DenseMatrix compute_a_prime(DenseMatrix a, DenseMatrix z);
    };


}
#endif // NETWORKIT_ALGEBRAICADP_H



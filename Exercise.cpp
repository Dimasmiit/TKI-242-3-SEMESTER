#include "Exercise.h"

namespace miit::algebra
{

    Exercise::Exercise(Matrix<int> mat) : matrix(std::move(mat))
    {
    }

    const Matrix<int>& Exercise::get_matrix() const
    {
        return matrix;
    }

}
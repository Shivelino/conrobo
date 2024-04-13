/*********************************************************************
 * @file    matrix-eigen.h    
 * @brief   
 * @details  
 * @author  Shivelino
 * @date    2024.4.12
 * @version 
 * @par Copyright(c): Concloud Software Corporation
 * @par todo:
 * @par history: 
 *********************************************************************/
#pragma once
#include <eigen3/Dense>

namespace conrobo {
namespace details {

template <typename _ScalarTy, int _Rows, int _Cols>
class MatrixImpl_Eigen {
public:
    using Base = Eigen::Matrix<_ScalarTy, _Rows, _Cols>;
    using ValueType = _ScalarTy;

private:
    Base* _base;

public:
    explicit MatrixImpl_Eigen() {
        _base = new Base();
        _base->setZero();
    }

    ~MatrixImpl_Eigen() { delete _base; }

public:
    inline MatrixImpl_Eigen& operator+=(const MatrixImpl_Eigen& rhs) {
        (*_base) = (*_base) + *(rhs._base);
        return *this;
    }

    inline MatrixImpl_Eigen& operator-=(const MatrixImpl_Eigen& rhs) {
        (*_base) = (*_base) - *(rhs._base);
        return *this;
    }

    inline MatrixImpl_Eigen& operator*=(const MatrixImpl_Eigen& rhs) {
        (*_base) = (*_base) * *(rhs._base);
        return *this;
    }

public:
    inline void set_element(size_t i, size_t j, ValueType value) { (*_base)(i, j) = value; }

    inline ValueType element(size_t i, size_t j) { return _base->coeff(i, j); }

    inline ValueType determinant() { return _base->determinant(); }

    inline void guass_simply() {
        int rows = _Rows;
        int cols = _Cols;
        Base& A = *_base;

        for (int i = 0; i < rows - 1; ++i) {
            for (int j = i + 1; j < rows; ++j) {
                double factor = A(j, i) / A(i, i);
                for (int k = i; k < cols; ++k) {
                    A(j, k) -= factor * A(i, k);
                }
            }
        }
    }
};

}  // namespace details
}  // namespace conrobo

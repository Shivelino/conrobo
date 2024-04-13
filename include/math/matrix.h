/*********************************************************************
 * @file    matrix.h    
 * @brief   
 * @details  
 * @author  Shivelino
 * @date    2024.4.11
 * @version 
 * @par Copyright(c): Concloud Software Corporation
 * @par todo:
 * @par history: 
 *********************************************************************/
#pragma once
#include <concepts>
#include <iostream>
#include <type_traits>

#include "details/matrix-eigen.h"

namespace conrobo {  // todo: use a diff namespace to include Conlinear as a 3rdparty

enum class MatrixBackend {
    Eigen,
};

//template <typename _Ty, typename _Vty, int _Rows, int _Cols>
//concept Matrix2Dim_Concept = requires(_Ty obj) {
//    { obj.set_element(std::declval<size_t>(), std::declval<size_t>(), std::declval<_Vty>()) } -> std::same_as<void>;
//    { obj.element(std::declval<size_t>(), std::declval<size_t>()) } -> std::same_as<_Vty>;
//};

// =====================================================================================================================

namespace details {

template <MatrixBackend Backend, typename ScalarTy, int Rows, int Cols>
struct MatrixImplSelector {};

template <typename ScalarTy, int Rows, int Cols>
struct MatrixImplSelector<MatrixBackend::Eigen, ScalarTy, Rows, Cols> {
    using Type = MatrixImpl_Eigen<ScalarTy, Rows, Cols>;
};

template <MatrixBackend Backend, typename ScalarTy, int Rows, int Cols>
using MatrixImpl = typename MatrixImplSelector<Backend, ScalarTy, Rows, Cols>::Type;

}  // namespace details

// =====================================================================================================================

template <MatrixBackend Backend, typename ScalarTy, int Rows, int Cols>
class Matrix {
    static_assert(Rows > 0, "Rows <= 0");
    static_assert(Cols > 0, "Cols <= 0");

public:
    using ImplType = details::MatrixImpl<Backend, ScalarTy, Rows, Cols>;
    using ValueType = ImplType::ValueType;

private:
    ImplType* impl = nullptr;

public:
    inline explicit Matrix() { impl = new ImplType(); }

    inline ~Matrix() { delete impl; }

public:
    template <MatrixBackend RhsBackend, typename RhsScalarTy, int RhsRows, int RhsCols>
    inline Matrix& operator+=(const Matrix<RhsBackend, RhsScalarTy, RhsRows, RhsCols>& rhs) {
        static_assert(Backend == RhsBackend, "Not same Matrix Backend. Now do not support different backend");
        static_assert(std::is_same_v<ScalarTy, RhsScalarTy>, "Now do not support Inner ScalarType Cast");
        static_assert(Rows == RhsRows, "Not same Matrix Rows");
        static_assert(Cols == RhsCols, "Not same Matrix Cols");
        (*impl) += *(rhs.impl);
        return *this;
    }

    template <MatrixBackend RhsBackend, typename RhsScalarTy, int RhsRows, int RhsCols>
    inline Matrix& operator-=(const Matrix<RhsBackend, RhsScalarTy, RhsRows, RhsCols>& rhs) {
        static_assert(Backend == RhsBackend, "Not same Matrix Backend. Now do not support different backend");
        static_assert(std::is_same_v<ScalarTy, RhsScalarTy>, "Now do not support Inner ScalarType Cast");
        static_assert(Rows == RhsRows, "Not same Matrix Rows");
        static_assert(Cols == RhsCols, "Not same Matrix Cols");
        (*impl) -= *(rhs.impl);
        return *this;
    }

    template <MatrixBackend RhsBackend, typename RhsScalarTy, int RhsRows, int RhsCols>
    inline Matrix& operator*=(const Matrix<RhsBackend, RhsScalarTy, RhsRows, RhsCols>& rhs) {
        static_assert(Backend == RhsBackend, "Not same Matrix Backend. Now do not support different backend");
        static_assert(std::is_same_v<ScalarTy, RhsScalarTy>, "Now do not support Inner ScalarType Cast");
        static_assert(Cols == RhsRows, "Could not multiply for left.cols != right.rows");
        (*impl) *= *(rhs.impl);
        return *this;
    }

public:
    inline void set_element(size_t i, size_t j, ValueType value) { impl->set_element(i, j, value); }

    inline ValueType element(size_t i, size_t j) { return impl->element(i, j); }

    inline ValueType determinant() {
        static_assert(Rows == Cols, "Matrix with det only when Rows == Cols");
        return impl->determinant();
    }

    inline void guass_simply() { impl->guass_simply(); }

public:
    inline void debug_print() {
        size_t rows = Rows;
        size_t cols = Cols;
        std::cout << "==========Mat Begin==========\n";
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < Cols; j++) {
                std::cout << element(i, j) << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "========== Mat End ==========\n" << std::endl;
    }
};

// =====================================================================================================================

template <typename ScalarTy, int Rows, int Cols>
using MatrixEigen = Matrix<MatrixBackend::Eigen, ScalarTy, Rows, Cols>;

}  // namespace conrobo

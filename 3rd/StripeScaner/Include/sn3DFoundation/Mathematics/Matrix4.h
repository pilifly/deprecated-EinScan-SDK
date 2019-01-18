// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef MATRIX4_H
#define MATRIX4_H

// Matrix operations are applied on the left.  For example, given a matrix M
// and a vector V, matrix-times-vector is M*V.  That is, V is treated as a
// column vector.  Some graphics APIs use V*M where V is treated as a row
// vector.  In this context the "M" matrix is really a transpose of the M as
// represented in Wild Magic.  Similarly, to apply two matrix operations M0
// and M1, in that order, you compute M1*M0 so that the transform of a vector
// is (M1*M0)*V = M1*(M0*V).  Some graphics APIs use M0*M1, but again these
// matrices are the transpose of those as represented in Wild Magic.  You
// must therefore be careful about how you interface the transformation code
// with graphics APIS.
//
// For memory organization it might seem natural to chose Real[N][N] for the
// matrix storage, but this can be a problem on a platform/console that
// chooses to store the data in column-major rather than row-major format.
// To avoid potential portability problems, the matrix is stored as Real[N*N]
// and organized in row-major order.  That is, the entry of the matrix in row
// r (0 <= r < N) and column c (0 <= c < N) is stored at index i = c+N*r
// (0 <= i < N*N).

#include "sn3DFoundationLIB.h"
#include "Plane3.h"
#include "Vector4.h"

namespace sn3DFoundation
{

template <class Real>
class Matrix4
{
public:
    // If bZero is true, create the zero matrix.  Otherwise, create the
    // identity matrix.
    Matrix4 (bool bZero = true);

    // copy constructor
    Matrix4 (const Matrix4& rkM);

    // input Mrc is in row r, column c.
    Matrix4 (Real fM00, Real fM01, Real fM02, Real fM03,
             Real fM10, Real fM11, Real fM12, Real fM13,
             Real fM20, Real fM21, Real fM22, Real fM23,
             Real fM30, Real fM31, Real fM32, Real fM33);

    // Create a matrix from an array of numbers.  The input array is
    // interpreted based on the Boolean input as
    //   true:  entry[0..15]={m00,m01,m02,m03,m10,m11,m12,m13,m20,m21,m22,
    //                        m23,m30,m31,m32,m33} [row major]
    //   false: entry[0..15]={m00,m10,m20,m30,m01,m11,m21,m31,m02,m12,m22,
    //                        m32,m03,m13,m23,m33} [col major]
    Matrix4 (const Real afEntry[16], bool bRowMajor);

    void MakeZero ();
    void MakeIdentity ();

    // member access
    inline operator const Real* () const;
    inline operator Real* ();
    inline const Real* operator[] (int iRow) const;
    inline Real* operator[] (int iRow);
    inline Real operator() (int iRow, int iCol) const;
    inline Real& operator() (int iRow, int iCol);
    void SetRow (int iRow, const Vector4<Real>& rkV);
    Vector4<Real> GetRow (int iRow) const;
    void SetColumn (int iCol, const Vector4<Real>& rkV);
    Vector4<Real> GetColumn (int iCol) const;
    void GetColumnMajor (Real* afCMajor) const;

    // assignment
    inline Matrix4& operator= (const Matrix4& rkM);

    // comparison
    bool operator== (const Matrix4& rkM) const;
    bool operator!= (const Matrix4& rkM) const;
    bool operator<  (const Matrix4& rkM) const;
    bool operator<= (const Matrix4& rkM) const;
    bool operator>  (const Matrix4& rkM) const;
    bool operator>= (const Matrix4& rkM) const;

    // arithmetic operations
    inline Matrix4 operator+ (const Matrix4& rkM) const;
    inline Matrix4 operator- (const Matrix4& rkM) const;
    inline Matrix4 operator* (const Matrix4& rkM) const;
    inline Matrix4 operator* (Real fScalar) const;
    inline Matrix4 operator/ (Real fScalar) const;
    inline Matrix4 operator- () const;

    // arithmetic updates
    inline Matrix4& operator+= (const Matrix4& rkM);
    inline Matrix4& operator-= (const Matrix4& rkM);
    inline Matrix4& operator*= (Real fScalar);
    inline Matrix4& operator/= (Real fScalar);

    // matrix times vector
    inline Vector4<Real> operator* (const Vector4<Real>& rkV) const;  // M * v

    // other operations
    Matrix4 Transpose () const;  // M^T
    Matrix4 TransposeTimes (const Matrix4& rkM) const;  // this^T * M
    Matrix4 TimesTranspose (const Matrix4& rkM) const;  // this * M^T
    Matrix4 Inverse () const;
    Matrix4 Adjoint () const;
    Real Determinant () const;
    Real QForm (const Vector4<Real>& rkU,
        const Vector4<Real>& rkV) const;  // u^T*M*v

    // projection matrices onto a specified plane
    void MakeObliqueProjection (const Vector3<Real>& rkNormal,
        const Vector3<Real>& rkPoint, const Vector3<Real>& rkDirection);
    void MakePerspectiveProjection (const Vector3<Real>& rkNormal,
        const Vector3<Real>& rkPoint, const Vector3<Real>& rkEye);

    // reflection matrix through a specified plane
    void MakeReflection (const Vector3<Real>& rkNormal,
        const Vector3<Real>& rkPoint);

    // special matrices
    SN3D_FOUNDATION_ITEM static const Matrix4 ZERO;
    SN3D_FOUNDATION_ITEM static const Matrix4 IDENTITY;

private:
    // support for comparisons
    int CompareArrays (const Matrix4& rkM) const;

    Real m_afEntry[16];
};

// c * M
template <class Real>
inline Matrix4<Real> operator* (Real fScalar, const Matrix4<Real>& rkM);

// v^T * M
template <class Real>
inline Vector4<Real> operator* (const Vector4<Real>& rkV,
    const Matrix4<Real>& rkM);

#include "Matrix4.inl"

typedef Matrix4<float> Matrix4f;
typedef Matrix4<double> Matrix4d;

}

#endif

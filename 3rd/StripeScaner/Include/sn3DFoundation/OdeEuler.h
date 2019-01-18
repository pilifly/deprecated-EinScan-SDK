// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef ODEEULER_H
#define ODEEULER_H

#include "sn3DFoundationLIB.h"
#include "OdeSolver.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM OdeEuler : public OdeSolver<Real>
{
public:
    OdeEuler (int iDim, Real fStep,
        typename OdeSolver<Real>::Function oFunction, void* pvData = 0);

    virtual ~OdeEuler ();

    virtual void Update (Real fTIn, Real* afXIn, Real& rfTOut,
        Real* afXOut);

    virtual void SetStepSize (Real fStep);

protected:
    using OdeSolver<Real>::m_iDim;
    using OdeSolver<Real>::m_fStep;
    using OdeSolver<Real>::m_pvData;
    using OdeSolver<Real>::m_afFValue;
};

typedef OdeEuler<float> OdeEulerf;
typedef OdeEuler<double> OdeEulerd;

}

#endif

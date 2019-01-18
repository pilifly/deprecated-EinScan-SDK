// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef DISTLINE3CIRCLE3_H
#define DISTLINE3CIRCLE3_H

#include "sn3DFoundationLIB.h"
#include "Distance.h"
#include "Line3.h"
#include "Circle3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM DistLine3Circle3
    : public Distance<Real,Vector3<Real> >
{
public:
    DistLine3Circle3 (const Line3<Real>& rkLine,
        const Circle3<Real>& rkCircle);

    // object access
    const Line3<Real>& GetLine () const;
    const Circle3<Real>& GetCircle () const;

    // Static distance queries.  Compute the distance from the point P to the
    // circle.  When P is on the normal line C+t*N where C is the circle
    // center and N is the normal to the plane containing the circle, then
    // all circle points are equidistant from P.  In this case the returned
    // point is (infinity,infinity,infinity).
    virtual Real Get ();
    virtual Real GetSquared ();

    // function calculations for dynamic distance queries
    virtual Real Get (Real fT, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);
    virtual Real GetSquared (Real fT, const Vector3<Real>& rkVelocity0,
        const Vector3<Real>& rkVelocity1);

private:
    using Distance<Real,Vector3<Real> >::m_kClosestPoint0;
    using Distance<Real,Vector3<Real> >::m_kClosestPoint1;

    const Line3<Real>* m_pkLine;
    const Circle3<Real>* m_pkCircle;
};

typedef DistLine3Circle3<float> DistLine3Circle3f;
typedef DistLine3Circle3<double> DistLine3Circle3d;

}

#endif

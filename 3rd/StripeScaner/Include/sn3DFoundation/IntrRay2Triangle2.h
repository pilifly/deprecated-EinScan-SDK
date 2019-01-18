// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRRAY2TRIANGLE2_H
#define INTRRAY2TRIANGLE2_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Ray2.h"
#include "Triangle2.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrRay2Triangle2
    : public Intersector<Real,Vector2<Real> >
{
public:
    IntrRay2Triangle2 (const Ray2<Real>& rkRay,
        const Triangle2<Real>& rkTriangle);

    // Object access.
    const Ray2<Real>& GetRay () const;
    const Triangle2<Real>& GetTriangle () const;

    // Static intersection query.
    virtual bool Test ();
    virtual bool Find ();

    // The intersection set.  If the ray and triangle do not intersect,
    // GetQuantity() returns 0, in which case the intersection type is
    // IT_EMPTY.  If the ray and triangle intersect in a single point,
    // GetQuantity() returns 1, in which case the intersection type is
    // IT_POINT and GetPoint() returns the intersection point.  If the ray
    // and triangle intersect in a segment, GetQuantity() returns 2, in which
    // case the intersection type is IT_SEGMENT and GetPoint() returns the
    // segment endpoints.
    int GetQuantity () const;
    const Vector2<Real>& GetPoint (int i) const;

private:
    using Intersector<Real,Vector2<Real> >::IT_EMPTY;
    using Intersector<Real,Vector2<Real> >::IT_POINT;
    using Intersector<Real,Vector2<Real> >::IT_SEGMENT;
    using Intersector<Real,Vector2<Real> >::m_iIntersectionType;

    // The objects to intersect.
    const Ray2<Real>* m_pkRay;
    const Triangle2<Real>* m_pkTriangle;

    // Information about the intersection set.
    int m_iQuantity;
    Vector2<Real> m_akPoint[2];
};

typedef IntrRay2Triangle2<float> IntrRay2Triangle2f;
typedef IntrRay2Triangle2<double> IntrRay2Triangle2d;

}

#endif

// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef INTRPLANE3BOX3_H
#define INTRPLANE3BOX3_H

#include "sn3DFoundationLIB.h"
#include "Intersector.h"
#include "Plane3.h"
#include "Box3.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM IntrPlane3Box3
    : public Intersector<Real,Vector3<Real> >
{
public:
    IntrPlane3Box3 (const Plane3<Real>& rkPlane,
        const Box3<Real>& rkBox);

    // object access
    const Plane3<Real>& GetPlane () const;
    const Box3<Real>& GetBox () const;

    // static intersection query
    virtual bool Test ();

    // Culling support.  The view frustum is assumed to be on the positive
    // side of the plane.  The box is culled if it is on the negative side
    // of the plane.
    bool BoxIsCulled () const;

protected:
    // the objects to intersect
    const Plane3<Real>* m_pkPlane;
    const Box3<Real>* m_pkBox;
};

typedef IntrPlane3Box3<float> IntrPlane3Box3f;
typedef IntrPlane3Box3<double> IntrPlane3Box3d;

}

#endif

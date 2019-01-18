// Geometric Tools, LLC
// Copyright (c) 1998-2010
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
//
// File Version: 4.10.0 (2009/11/18)

#ifndef GRIDGRAPH2_H
#define GRIDGRAPH2_H

#include "sn3DFoundationLIB.h"
#include "sn3DMath.h"

namespace sn3DFoundation
{

template <class Real>
class SN3D_FOUNDATION_ITEM GridGraph2
{
public:
    // The 2D grid is chosen to be 8-connected.  Each vertex (x,y) has 8
    // neighbors: (x-1,y-1), (x,y-1), (x+1,y-1), (x-1,y), (x+1,y),
    // (x-1,y+1), (x,y+1), (x+1,y+1).  The graph is undirected.
    GridGraph2 (int iXSize, int iYSize);
    virtual ~GridGraph2 ();

    // Access to the graph sizes.
    int GetXSize () const;
    int GetYSize () const;
    int GetVertexQuantity () const;

    // Basic access to the edge weights of the graph.
    void SetWeight (int iX, int iY, int iDX, int iDY, Real fWeight);
    Real GetWeight (int iX, int iY, int iDX, int iDY) const;

    // Compute the minimum-weight path from (x0,y0) to (x1,y1).
    void ComputeMinimumWeightPath (int iX0, int iY0, int iX1, int iY1);

    // The path is stored internally.  Access it using these functions.  If
    // the input index i is out of range, the returned values are -1.
    int GetPathQuantity () const;
    void GetPathPoint (int i, int& riX, int& riY) const;

    // A callback that is executed during relaxation step.
    typedef void (*RelaxationCallbackFunction)();
    RelaxationCallbackFunction RelaxationCallback;

    int GetNumProcessed () const;

protected:
    class Vertex
    {
    public:
        Vertex ()
        {
            for (int i = 0; i < 8; i++)
            {
                m_afWeight[i] = Math<Real>::MAX_REAL;
            }
            Estimate = Math<Real>::MAX_REAL;
            Predecessor = -1;
        }

        void SetWeight (int iDX, int iDY, Real fWeight)
        {
            m_afWeight[GridGraph2<Real>::ms_aaiIndex[iDY+1][iDX+1]] = fWeight;
        }

        Real GetWeight (int iDX, int iDY) const
        {
            return m_afWeight[GridGraph2<Real>::ms_aaiIndex[iDY+1][iDX+1]];
        }

        // support for minimum-weight paths
        Real Estimate;
        int Predecessor;

    private:
        // Weights for the eight neighbors.
        //   weight[0] for (x-1,y-1)
        //   weight[1] for (x  ,y-1)
        //   weight[2] for (x+1,y-1)
        //   weight[3] for (x-1,y  )
        //   weight[4] for (x+1,y  )
        //   weight[5] for (x-1,y+1)
        //   weight[6] for (x  ,y+1)
        //   weight[7] for (x+1,y+1)
        Real m_afWeight[8];
    };

    // The 2-dimensional grid is stored as a 1-dimensional array.
    int GetIndex (int iX, int iY) const { return iX + m_iXSize*iY; }
    int GetX (int iIndex) const { return iIndex % m_iXSize; }
    int GetY (int iIndex) const { return iIndex / m_iXSize; }

    int m_iXSize, m_iYSize, m_iVertexQuantity;
    Vertex* m_akVertex;

    int m_iPathQuantity;
    int* m_aiPath;
    int* m_aiPending;
    int m_iNumProcessed;

    friend class Vertex;
    static const int ms_aaiIndex[3][3];  // index[dy][dx]
};

typedef GridGraph2<float> GridGraph2f;
typedef GridGraph2<double> GridGraph2d;

}

#endif

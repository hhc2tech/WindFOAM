/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Description

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline label primitiveMesh::nPoints() const
{
    return nPoints_;
}


inline label primitiveMesh::nEdges() const
{
    if (nEdges_ < 0)
    {
        nEdges_ = edges().size();
    }

    return nEdges_;
}


inline label primitiveMesh::nInternalFaces() const
{
    return nInternalFaces_;
}


inline label primitiveMesh::nFaces() const
{
    return nFaces_;
}


inline label primitiveMesh::nCells() const
{
    return nCells_;
}


inline bool primitiveMesh::isInternalFace(const label faceIndex) const
{
    return faceIndex < nInternalFaces();
}


inline bool primitiveMesh::hasCellShapes() const
{
    return cellShapesPtr_;
}


inline bool primitiveMesh::hasEdges() const
{
    return edgesPtr_;
}


inline bool primitiveMesh::hasCellCells() const
{
    return ccPtr_;
}


inline bool primitiveMesh::hasEdgeCells() const
{
    return ecPtr_;
}


inline bool primitiveMesh::hasPointCells() const
{
    return pcPtr_;
}


inline bool primitiveMesh::hasCells() const
{
    return cfPtr_;
}


inline bool primitiveMesh::hasEdgeFaces() const
{
    return efPtr_;
}


inline bool primitiveMesh::hasPointFaces() const
{
    return pfPtr_;
}


inline bool primitiveMesh::hasCellEdges() const
{
    return cePtr_;
}


inline bool primitiveMesh::hasFaceEdges() const
{
    return fePtr_;
}


inline bool primitiveMesh::hasPointEdges() const
{
    return pePtr_;
}


inline bool primitiveMesh::hasPointPoints() const
{
    return ppPtr_;
}


inline bool primitiveMesh::hasCellPoints() const
{
    return cpPtr_;
}


inline bool primitiveMesh::hasCellCentres() const
{
    return cellCentresPtr_;
}


inline bool primitiveMesh::hasFaceCentres() const
{
    return faceCentresPtr_;
}


inline bool primitiveMesh::hasCellVolumes() const
{
    return cellVolumesPtr_;
}


inline bool primitiveMesh::hasFaceAreas() const
{
    return faceAreasPtr_;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //

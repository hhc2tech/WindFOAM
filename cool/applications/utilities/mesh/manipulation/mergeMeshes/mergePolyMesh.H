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

Class
    Foam::mergePolyMesh

Description
    Add a given mesh to the original mesh to create a single new mesh

SourceFiles
    mergePolyMesh.C

\*---------------------------------------------------------------------------*/

#ifndef mergePolyMesh_H
#define mergePolyMesh_H

#include "polyMesh.H"
#include "directTopoChange.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes

/*---------------------------------------------------------------------------*\
                           Class mergePolyMesh Declaration
\*---------------------------------------------------------------------------*/

class mergePolyMesh
:
    public polyMesh
{
    // Private data

        //- Topological change to accumulated all mesh changes
        directTopoChange meshMod_;

        //- Patch types
        DynamicList<word> patchTypes_;

        //- Patch names
        DynamicList<word> patchNames_;

        //- Point zone names
        DynamicList<word> pointZoneNames_;

        //- Face zone names
        DynamicList<word> faceZoneNames_;

        //- Cell zone names
        DynamicList<word> cellZoneNames_;

        //- Point zones
        DynamicList<label>  pointZones_;

        //- Face zones
        DynamicList<label>  faceZones_;

        //- Face zone Flips
        DynamicList<bool>  faceZoneFlips_;

        //- Cell zones
        DynamicList<label> cellZones_;

    // Private Member Functions

        //- Disallow default bitwise copy construct
        mergePolyMesh(const mergePolyMesh&);

        //- Disallow default bitwise assignment
        void operator=(const mergePolyMesh&);


        //- Return patch index given a name and type
        label patchIndex(const polyPatch&);

        //- Return zone index given a list of active zones and a name
        label zoneIndex(DynamicList<word>&, const word&);


public:

    //- Runtime type information
    TypeName("mergePolyMesh");


    // Constructors

        //- Construct from IOobject
        mergePolyMesh(const IOobject& io);


    // Destructor

        virtual ~mergePolyMesh()
        {}


    // Member Functions

        //- Add a mesh
        void addMesh(const polyMesh& m);

        //- Merge meshes
        void merge();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

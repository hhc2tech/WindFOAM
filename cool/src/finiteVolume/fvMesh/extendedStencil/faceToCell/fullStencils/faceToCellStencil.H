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
    Foam::faceToCellStencil

Description
    baseclass for extended cell centred addressing. Contains per cell a
    list of neighbouring faces in global addressing.

SourceFiles
    faceToCellStencil.C

\*---------------------------------------------------------------------------*/

#ifndef faceToCellStencil_H
#define faceToCellStencil_H

#include "globalIndex.H"
#include "boolList.H"
#include "HashSet.H"
#include "indirectPrimitivePatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class polyMesh;

/*---------------------------------------------------------------------------*\
                           Class faceToCellStencil Declaration
\*---------------------------------------------------------------------------*/

class faceToCellStencil
:
    public labelListList
{
    // Private data

        const polyMesh& mesh_;

        //- Global numbering for faces
        const globalIndex globalNumbering_;


    // Private Member Functions

//HJ        //- Disallow default bitwise copy construct
//HJ        faceToCellStencil(const faceToCellStencil&);
//HJ
//HJ        //- Disallow default bitwise assignment
//HJ        void operator=(const faceToCellStencil&);

public:

    // Constructors

        //- Construct from mesh
        explicit faceToCellStencil(const polyMesh&);


    // Member Functions

        const polyMesh& mesh() const
        {
            return mesh_;
        }

        //- Global numbering for faces
        const globalIndex& globalNumbering() const
        {
            return globalNumbering_;
        }

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

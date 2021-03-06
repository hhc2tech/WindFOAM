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
    Foam::extendedCentredFaceToCellStencil

Description

SourceFiles
    extendedCentredFaceToCellStencil.C

\*---------------------------------------------------------------------------*/

#ifndef extendedCentredFaceToCellStencil_H
#define extendedCentredFaceToCellStencil_H

#include "extendedFaceToCellStencil.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

class faceToCellStencil;

/*---------------------------------------------------------------------------*\
                           Class extendedCentredFaceToCellStencil Declaration
\*---------------------------------------------------------------------------*/

class extendedCentredFaceToCellStencil
:
    public extendedFaceToCellStencil
{
    // Private data

        //- Swap map for getting neigbouring data
        autoPtr<mapDistribute> mapPtr_;

        //- Per face the stencil.
        labelListList stencil_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        extendedCentredFaceToCellStencil
        (
            const extendedCentredFaceToCellStencil&
        );

        //- Disallow default bitwise assignment
        void operator=(const extendedCentredFaceToCellStencil&);


public:

    // Constructors

        //- Construct from uncompacted face stencil
        explicit extendedCentredFaceToCellStencil(const faceToCellStencil&);


    // Member Functions

        //- Return reference to the parallel distribution map
        const mapDistribute& map() const
        {
            return mapPtr_();
        }

        //- Return reference to the stencil
        const labelListList& stencil() const
        {
            return stencil_;
        }

        //- After removing elements from the stencil adapt the schedule (map).
        void compact();

        //- Use map to get the data into stencil order
        template<class T>
        void collectData
        (
            const GeometricField<T, fvsPatchField, surfaceMesh>& fld,
            List<List<T> >& stencilFld
        ) const
        {
            extendedFaceToCellStencil::collectData
            (
                map(),
                stencil(),
                fld,
                stencilFld
            );
        }

        //- Sum surface field contributions to create cell values
        template<class Type>
        tmp<GeometricField<Type, fvPatchField, volMesh> > weightedSum
        (
            const GeometricField<Type, fvsPatchField, surfaceMesh>& fld,
            const List<List<scalar> >& stencilWeights
        ) const
        {
            return extendedFaceToCellStencil::weightedSum
            (
                map(),
                stencil(),
                fld,
                stencilWeights
            );
        }

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

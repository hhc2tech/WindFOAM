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
    Foam::meshToMesh

Description
    mesh to mesh interpolation class.

SourceFiles
    meshToMesh.C
    calculateMeshToMeshAddressing.C
    calculateMeshToMeshWeights.C
    meshToMeshInterpolate.C

\*---------------------------------------------------------------------------*/

#ifndef meshtoMesh_H
#define meshtoMesh_H

#include "fvMesh.H"
#include "HashTable.H"
#include "fvPatchMapper.H"
#include "scalarList.H"
#include "className.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

template<class Type>
class octree;

class octreeDataCell;

/*---------------------------------------------------------------------------*\
                           Class meshToMesh Declaration
\*---------------------------------------------------------------------------*/

class meshToMesh
{
    // Private data

        // mesh references

        const fvMesh& fromMesh_;
        const fvMesh& toMesh_;

        //- fromMesh patch labels
        HashTable<label> fromMeshPatches_;

        //- toMesh patch labels
        HashTable<label> toMeshPatches_;

        //- Patch map
        HashTable<word> patchMap_;

        //- toMesh patch labels which cut the from-mesh
        HashTable<label> cuttingPatches_;

        //- Cell addressing
        labelList cellAddressing_;

        //- Boundary addressing
        labelListList boundaryAddressing_;

        //- Inverse-distance interpolation weights
        mutable scalarListList* inverseDistanceWeightsPtr_;


    // Private Member Functions

        void calcAddressing();

        void cellAddresses
        (
            labelList& cells,
            const pointField& points,
            const fvMesh& fromMesh,
            const List<bool>& boundaryCell,
            const octree<octreeDataCell>& oc
        ) const;

        void calculateInverseDistanceWeights() const;

        const scalarListList& inverseDistanceWeights() const;


    // Private static data members

        //- Direct hit tolerance
        static const scalar directHitTol;


public:

    // Declare name of the class and its debug switch
    ClassName("meshToMesh");


    //- Enumeration specifying required accuracy
    enum order
    {
        MAP,
        INTERPOLATE,
        CELL_POINT_INTERPOLATE
    };


    // Constructors

        //- Construct from the two meshes, the patch name map for the patches
        //  to be interpolated and the names of the toMesh-patches which
        //  cut the fromMesh
        meshToMesh
        (
            const fvMesh& fromMesh,
            const fvMesh& toMesh,
            const HashTable<word>& patchMap,
            const wordList& cuttingPatchNames
        );

        //- Construct from the two meshes assuming there is an exact mapping
        //  between the patches
        meshToMesh
        (
            const fvMesh& fromMesh,
            const fvMesh& toMesh
        );


    // Destructor

        ~meshToMesh();


    //- Patch-field interpolation class
    class patchFieldInterpolator
    :
        public fvPatchFieldMapper
    {
        const labelList& directAddressing_;

    public:

        // Constructors

            //- Construct given addressing
            patchFieldInterpolator(const labelList& addr)
            :
                directAddressing_(addr)
            {}


        // Destructor

            virtual ~patchFieldInterpolator()
            {}


        // Member Functions

            virtual label size() const
            {
                return directAddressing_.size();
            }

            virtual label sizeBeforeMapping() const
            {
                return directAddressing_.size();
            }

            virtual bool direct() const
            {
                return true;
            }

            const labelList& directAddressing() const
            {
                return directAddressing_;
            }
    };


    // Member Functions

        // Access

            const fvMesh& fromMesh() const
            {
                return fromMesh_;
            }
 
            const fvMesh& toMesh() const
            {
                return toMesh_;
            }

            //- From toMesh cells to fromMesh cells
            const labelList& cellAddressing() const
            {
                return cellAddressing_;
            }

        // Interpolation

            //- Map field
            template<class Type>
            void mapField
            (
                Field<Type>&,
                const Field<Type>&,
                const labelList& adr
            ) const;

            //- Interpolate field using inverse-distance weights
            template<class Type>
            void interpolateField
            (
                Field<Type>&,
                const GeometricField<Type, fvPatchField, volMesh>&,
                const labelList& adr,
                const scalarListList& weights
            ) const;

            //- Interpolate field using cell-point interpolation
            template<class Type>
            void interpolateField
            (
                Field<Type>&,
                const GeometricField<Type, fvPatchField, volMesh>&,
                const labelList& adr,
                const vectorField& centres
            ) const;


            //- Interpolate internal volume field
            template<class Type>
            void interpolateInternalField
            (
                Field<Type>&,
                const GeometricField<Type, fvPatchField, volMesh>&,
                order=INTERPOLATE
            ) const;

            template<class Type>
            void interpolateInternalField
            (
                Field<Type>&,
                const tmp<GeometricField<Type, fvPatchField, volMesh> >&,
                order=INTERPOLATE
            ) const;


            //- Interpolate volume field
            template<class Type>
            void interpolate
            (
                GeometricField<Type, fvPatchField, volMesh>&,
                const GeometricField<Type, fvPatchField, volMesh>&,
                order=INTERPOLATE
            ) const;

            template<class Type>
            void interpolate
            (
                GeometricField<Type, fvPatchField, volMesh>&,
                const tmp<GeometricField<Type, fvPatchField, volMesh> >&,
                order=INTERPOLATE
            ) const;


            //- Interpolate volume field
            template<class Type>
            tmp<GeometricField<Type, fvPatchField, volMesh> > interpolate
            (
                const GeometricField<Type, fvPatchField, volMesh>&,
                order=INTERPOLATE
            ) const;

            template<class Type>
            tmp<GeometricField<Type, fvPatchField, volMesh> > interpolate
            (
                const tmp<GeometricField<Type, fvPatchField, volMesh> >&,
                order=INTERPOLATE
            ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "meshToMeshInterpolate.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

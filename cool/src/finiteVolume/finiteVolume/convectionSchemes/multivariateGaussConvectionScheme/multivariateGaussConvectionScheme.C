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

#include "multivariateGaussConvectionScheme.H"
#include "gaussConvectionScheme.H"
#include "fvMatrices.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace fv
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
multivariateGaussConvectionScheme<Type>::interpolate
(
    const surfaceScalarField& faceFlux,
    const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
    return gaussConvectionScheme<Type>
    (
        this->mesh(),
        faceFlux,
        tinterpScheme_()(vf)
    ).interpolate(faceFlux, vf);
}


template<class Type>
tmp<GeometricField<Type, fvsPatchField, surfaceMesh> >
multivariateGaussConvectionScheme<Type>::flux
(
    const surfaceScalarField& faceFlux,
    const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
    return gaussConvectionScheme<Type>
    (
        this->mesh(),
        faceFlux,
        tinterpScheme_()(vf)
    ).flux(faceFlux, vf);
}


template<class Type>
tmp<fvMatrix<Type> >
multivariateGaussConvectionScheme<Type>::fvmDiv
(
    const surfaceScalarField& faceFlux,
    GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
    return gaussConvectionScheme<Type>
    (
        this->mesh(),
        faceFlux,
        tinterpScheme_()(vf)
    ).fvmDiv(faceFlux, vf);
}


template<class Type>
tmp<GeometricField<Type, fvPatchField, volMesh> >
multivariateGaussConvectionScheme<Type>::fvcDiv
(
    const surfaceScalarField& faceFlux,
    const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
    return gaussConvectionScheme<Type>
    (
        this->mesh(),
        faceFlux,
        tinterpScheme_()(vf)
    ).fvcDiv(faceFlux, vf);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace fv

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //

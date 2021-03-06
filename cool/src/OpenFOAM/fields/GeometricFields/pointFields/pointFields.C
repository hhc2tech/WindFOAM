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

\*---------------------------------------------------------------------------*/

#include "polyMesh.H"
#include "pointFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

defineTemplateTypeNameAndDebug(pointScalarField::DimensionedInternalField, 0);
defineTemplateTypeNameAndDebug(pointVectorField::DimensionedInternalField, 0);
defineTemplateTypeNameAndDebug(pointSphericalTensorField::DimensionedInternalField, 0);
defineTemplateTypeNameAndDebug(pointSymmTensorField::DimensionedInternalField, 0);
defineTemplateTypeNameAndDebug(pointTensorField::DimensionedInternalField, 0);

defineTemplateTypeNameAndDebug(pointScalarField, 0);
defineTemplateTypeNameAndDebug(pointVectorField, 0);
defineTemplateTypeNameAndDebug(pointSphericalTensorField, 0);
defineTemplateTypeNameAndDebug(pointSymmTensorField, 0);
defineTemplateTypeNameAndDebug(pointTensorField, 0);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

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
    Uniform motion diffusivity.

\*---------------------------------------------------------------------------*/

#include "uniformDiff.H"
#include "addToRunTimeSelectionTable.H"
#include "elementFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(uniformDiff, 0);
    addToRunTimeSelectionTable(motionDiff, uniformDiff, dictionary);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
Foam::uniformDiff::uniformDiff(const tetDecompositionMotionSolver& mSolver)
:
    motionDiff(mSolver),
    motionGamma_
    (
        IOobject
        (
            "motionGamma",
            tetMesh().time().timeName(),
            tetMesh()(),
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        tetMesh(),
        dimensionedScalar("1.0", dimless, 1.0)
    )
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::uniformDiff::~uniformDiff()
{}


// ************************************************************************* //

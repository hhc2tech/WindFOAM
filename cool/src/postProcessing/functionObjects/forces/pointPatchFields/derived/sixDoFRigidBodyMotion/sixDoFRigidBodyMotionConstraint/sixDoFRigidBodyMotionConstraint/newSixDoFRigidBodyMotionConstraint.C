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

#include "sixDoFRigidBodyMotionConstraint.H"

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::sixDoFRigidBodyMotionConstraint>
Foam::sixDoFRigidBodyMotionConstraint::New(const dictionary& sDoFRBMCDict)
{
    word sixDoFRigidBodyMotionConstraintTypeName =
        sDoFRBMCDict.lookup("sixDoFRigidBodyMotionConstraint");

    // Info<< "Selecting sixDoFRigidBodyMotionConstraint function "
    //     << sixDoFRigidBodyMotionConstraintTypeName << endl;

    dictionaryConstructorTable::iterator cstrIter =
    dictionaryConstructorTablePtr_->find
    (
        sixDoFRigidBodyMotionConstraintTypeName
    );

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorIn
        (
            "sixDoFRigidBodyMotionConstraint::New"
            "("
                "const dictionary& sDoFRBMCDict"
            ")"
        )   << "Unknown sixDoFRigidBodyMotionConstraint type "
            << sixDoFRigidBodyMotionConstraintTypeName << endl << endl
            << "Valid  sixDoFRigidBodyMotionConstraints are : " << endl
            << dictionaryConstructorTablePtr_->toc()
            << exit(FatalError);
    }

    return autoPtr<sixDoFRigidBodyMotionConstraint>(cstrIter()(sDoFRBMCDict));
}


// ************************************************************************* //

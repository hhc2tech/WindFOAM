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

#include "XiGModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

Foam::autoPtr<Foam::XiGModel> Foam::XiGModel::New
(
    const dictionary& XiGProperties,
    const hhuCombustionThermo& thermo,
    const compressible::RASModel& turbulence,
    const volScalarField& Su
)
{
    word XiGModelTypeName = XiGProperties.lookup("XiGModel");

    Info<< "Selecting flame-wrinkling model " << XiGModelTypeName << endl;

    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(XiGModelTypeName);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorIn
        (
            "XiGModel::New"
            "("
            "    const hhuCombustionThermo& thermo,"
            "    const compressible::RASModel& turbulence,"
            "    const volScalarField& Su"
            ")"
        )   << "Unknown XiGModel type "
            << XiGModelTypeName << endl << endl
            << "Valid  XiGModels are : " << endl
            << dictionaryConstructorTablePtr_->toc()
            << exit(FatalError);
    }

    return autoPtr<XiGModel>
        (cstrIter()(XiGProperties, thermo, turbulence, Su));
}


// ************************************************************************* //

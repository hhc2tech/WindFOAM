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

#include "faceToPoint.H"
#include "polyMesh.H"
#include "faceSet.H"

#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{

defineTypeNameAndDebug(faceToPoint, 0);

addToRunTimeSelectionTable(topoSetSource, faceToPoint, word);

addToRunTimeSelectionTable(topoSetSource, faceToPoint, istream);

}


Foam::topoSetSource::addToUsageTable Foam::faceToPoint::usage_
(
    faceToPoint::typeName,
    "\n    Usage: faceToPoint <faceSet> all\n\n"
    "    Select all points of faces in the faceSet\n\n"
);

template<>
const char* Foam::NamedEnum<Foam::faceToPoint::faceAction, 1>::names[] =
{
    "all"
};

const Foam::NamedEnum<Foam::faceToPoint::faceAction, 1>
    Foam::faceToPoint::faceActionNames_;


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::faceToPoint::combine(topoSet& set, const bool add) const
{
    // Load the set
    faceSet loadedSet(mesh_, setName_);

    // Add all points from faces in loadedSet
    for
    (
        faceSet::const_iterator iter = loadedSet.begin();
        iter != loadedSet.end();
        ++iter
    )
    {
        const face& f = mesh_.faces()[iter.key()];

        forAll(f, fp)
        {
            addOrDelete(set, f[fp], add);
        }
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
Foam::faceToPoint::faceToPoint
(
    const polyMesh& mesh,
    const word& setName,
    const faceAction option
)
:
    topoSetSource(mesh),
    setName_(setName),
    option_(option)
{}


// Construct from dictionary
Foam::faceToPoint::faceToPoint
(
    const polyMesh& mesh,
    const dictionary& dict
)
:
    topoSetSource(mesh),
    setName_(dict.lookup("set")),
    option_(faceActionNames_.read(dict.lookup("option")))
{}


// Construct from Istream
Foam::faceToPoint::faceToPoint
(
    const polyMesh& mesh,
    Istream& is
)
:
    topoSetSource(mesh),
    setName_(checkIs(is)),
    option_(faceActionNames_.read(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::faceToPoint::~faceToPoint()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::faceToPoint::applyToSet
(
    const topoSetSource::setAction action,
    topoSet& set
) const
{
    if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
    {
        Info<< "    Adding points from face in faceSet " << setName_
            << " ..." << endl;

        combine(set, true);
    }
    else if (action == topoSetSource::DELETE)
    {
        Info<< "    Removing points from face in faceSet " << setName_
            << " ..." << endl;

        combine(set, false);
    }
}


// ************************************************************************* //

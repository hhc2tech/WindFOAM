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
    Foam::surfZoneIOList

Description
    IOobject for a surfZoneList

SourceFiles
    surfZoneIOList.C

\*---------------------------------------------------------------------------*/

#ifndef surfZoneIOList_H
#define surfZoneIOList_H

#include "surfZoneList.H"
#include "regIOobject.H"
#include "faceList.H"
#include "className.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of classes

/*---------------------------------------------------------------------------*\
                      Class surfZoneIOList Declaration
\*---------------------------------------------------------------------------*/

class surfZoneIOList
:
    public surfZoneList,
    public regIOobject
{
    // Private Member Functions

        //- Disallow default bitwise copy construct
        surfZoneIOList(const surfZoneIOList&);

        //- Disallow default bitwise assignment
        void operator=(const surfZoneIOList&);


public:

    //- Runtime type information
    TypeName("surfZoneList");


    // Constructors

        //- Construct from IOobject
        explicit surfZoneIOList(const IOobject&);

        //- Construct from IOobject and surfZoneList
        surfZoneIOList(const IOobject&, const surfZoneList&);

        //- Construct from IOobject and surfZoneList
        surfZoneIOList(const IOobject&, const Xfer<surfZoneList>&);


    // Destructor

        ~surfZoneIOList();


    // Member Functions

        //- writeData member function required by regIOobject
        bool writeData(Ostream&) const;


    // IOstream Operators

        friend Ostream& operator<<(Ostream&, const surfZoneIOList&);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

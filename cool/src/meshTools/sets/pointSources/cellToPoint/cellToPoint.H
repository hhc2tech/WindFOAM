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
    Foam::cellToPoint

Description
    A topoSetSource to select points based on usage in cells.

SourceFiles
    cellToPoint.C

\*---------------------------------------------------------------------------*/

#ifndef cellToPoint_H
#define cellToPoint_H

#include "topoSetSource.H"
#include "NamedEnum.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                        Class cellToPoint Declaration
\*---------------------------------------------------------------------------*/

class cellToPoint
:
    public topoSetSource
{

public:
        //- Enumeration defining the valid options
        enum cellAction
        {
            ALL
        };

private:

        //- Add usage string
        static addToUsageTable usage_;

        static const NamedEnum<cellAction, 1> cellActionNames_;

        //- Name of set to use
        word setName_;

        //- Option
        cellAction option_;


    // Private Member Functions

        //- Depending on face to cell option add to or delete from cellSet.
        void combine(topoSet& set, const bool add) const;


public:

    //- Runtime type information
    TypeName("cellToPoint");

    // Constructors

        //- Construct from components
        cellToPoint
        (
            const polyMesh& mesh,
            const word& setName,
            const cellAction option
        );

        //- Construct from dictionary
        cellToPoint
        (
            const polyMesh& mesh,
            const dictionary& dict
        );

        //- Construct from Istream
        cellToPoint
        (
            const polyMesh& mesh,
            Istream&
        );


    // Destructor

        virtual ~cellToPoint();


    // Member Functions

        virtual void applyToSet
        (
            const topoSetSource::setAction action,
            topoSet&
        ) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

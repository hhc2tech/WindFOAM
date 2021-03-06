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
    Foam::OSstream

Description
    Generic output stream.

SourceFiles
    OSstreamI.H
    OSstream.C
    chkStream.C

\*---------------------------------------------------------------------------*/

#ifndef OSstream_H
#define OSstream_H

#include "Ostream.H"
#include "fileName.H"
#include <iostream>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                          Class OSstream Declaration
\*---------------------------------------------------------------------------*/

class OSstream
:
    public Ostream
{
    // Private data

        fileName name_;
        ostream& os_;


    // Private Member Functions

        //- Disallow default bitwise assignment
        void operator=(const OSstream&);


protected:

        //- Return the stream reference
        ostream& stream()
        {
            return os_;
        }

        //- Return the const stream reference
        const ostream& stream() const
        {
            return os_;
        }


public:

    // Constructors

        //- Set stream status
        OSstream
        (
            ostream& os,
            const string& name,
            streamFormat format=ASCII,
            versionNumber version=currentVersion,
            compressionType compression=UNCOMPRESSED
        );


    // Member functions

        // Enquiry

            //- Return the name of the stream
            //  Useful for Fstream to return the filename
            virtual const fileName& name() const
            {
                return name_;
            }

            //- Return non-const access to the name of the stream
            //  Useful to alter the stream name
            virtual fileName& name()
            {
                return name_;
            }

            //- Return flags of output stream
            virtual ios_base::fmtflags flags() const;


        // Write functions

            //- Write next token to stream
            virtual Ostream& write(const token&);

            //- Write character
            virtual Ostream& write(const char);

            //- Write character string
            virtual Ostream& write(const char*);

            //- Write word
            virtual Ostream& write(const word&);

            //- Write string
            //  In the rare case that the string contains a final trailing
            //  backslash, it will be dropped to the appearance of an escaped
            //  double-quote.
            virtual Ostream& write(const string&);

            //- Write std::string surrounded by quotes.
            //  Optional write without quotes.
            virtual Ostream& writeQuoted
            (
                const std::string&,
                const bool quoted=true
            );

            //- Write label
            virtual Ostream& write(const label);

            //- Write floatScalar
            virtual Ostream& write(const floatScalar);

            //- Write doubleScalar
            virtual Ostream& write(const doubleScalar);

            //- Write binary block
            virtual Ostream& write(const char*, std::streamsize);

            //- Add indentation characters
            virtual void indent();


        // Stream state functions

            //- Set flags of output stream
            virtual ios_base::fmtflags flags(const ios_base::fmtflags flags);

            //- Flush stream
            virtual void flush();

            //- Add newline and flush stream
            virtual void endl();

            //- Get width of output field
            virtual int width() const;

            //- Set width of output field (and return old width)
            virtual int width(const int);

            //- Get precision of output field
            virtual int precision() const;

            //- Set precision of output field (and return old precision)
            virtual int precision(const int);


        // Print

            //- Print description of IOstream to Ostream
            virtual void print(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "OSstreamI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

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

#include "error.H"
#include "sigSegv.H"
#include "JobInfo.H"
#include "IOstreams.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

struct sigaction Foam::sigSegv::oldAction_;

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::sigSegv::sigSegvHandler(int)
{
    // Reset old handling
    if (sigaction(SIGSEGV, &oldAction_, NULL) < 0)
    {
        FatalErrorIn
        (
            "Foam::sigSegv::sigSegvHandler()"
        )   << "Cannot reset SIGSEGV trapping"
            << abort(FatalError);    
    }

    // Update jobInfo file
    jobInfo.signalEnd();

    error::printStack(Perr);

    // Throw signal (to old handler)
    raise(SIGSEGV);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::sigSegv::sigSegv()
{
    oldAction_.sa_handler = NULL;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::sigSegv::~sigSegv()
{
    // Reset old handling
    if (sigaction(SIGSEGV, &oldAction_, NULL) < 0)
    {
        FatalErrorIn
        (
            "Foam::sigSegv::~sigSegv()"
        )   << "Cannot reset SIGSEGV trapping"
            << abort(FatalError);    
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::sigSegv::set(const bool verbose)
{
    if (oldAction_.sa_handler)
    {
        FatalErrorIn
        (
            "Foam::sigSegv::set()"
        )   << "Cannot call sigSegv::set() more than once"
            << abort(FatalError);
    }

    struct sigaction newAction;
    newAction.sa_handler = sigSegvHandler;
    newAction.sa_flags = SA_NODEFER;
    sigemptyset(&newAction.sa_mask);
    if (sigaction(SIGSEGV, &newAction, &oldAction_) < 0)
    {
        FatalErrorIn
        (
            "Foam::sigSegv::set()"
        )   << "Cannot set SIGSEGV trapping"
            << abort(FatalError);    
    }
}


// ************************************************************************* //

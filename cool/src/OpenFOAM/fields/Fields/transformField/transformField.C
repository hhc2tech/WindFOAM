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

#include "transformField.H"
#include "FieldM.H"
#include "diagTensor.H"

// * * * * * * * * * * * * * * * global functions  * * * * * * * * * * * * * //

void Foam::transform
(
    vectorField& rtf,
    const quaternion& q,
    const vectorField& tf
)
{
    tensor t = q.R();
    TFOR_ALL_F_OP_FUNC_S_F(vector, rtf, =, transform, tensor, t, vector, tf)
}


Foam::tmp<Foam::vectorField> Foam::transform
(
    const quaternion& q,
    const vectorField& tf
)
{
    tmp<vectorField > tranf(new vectorField(tf.size()));
    transform(tranf(), q, tf);
    return tranf;
}


Foam::tmp<Foam::vectorField> Foam::transform
(
    const quaternion& q,
    const tmp<vectorField>& ttf
)
{
    tmp<vectorField > tranf = reuseTmp<vector, vector>::New(ttf);
    transform(tranf(), q, ttf());
    reuseTmp<vector, vector>::clear(ttf);
    return tranf;
}


void Foam::transform
(
    vectorField& rtf,
    const septernion& tr,
    const vectorField& tf
)
{
    vector T = tr.t();

    // Check if any rotation
    if (mag(tr.r().R() - I) > SMALL)
    {
        transform(rtf, tr.r(), tf);

        if (mag(T) > VSMALL)
        {
            rtf += T;
        }
    }
    else
    {
        if (mag(T) > VSMALL)
        {
            TFOR_ALL_F_OP_S_OP_F(vector, rtf, =, vector, T, +, vector, tf);
        }
        else
        {
            rtf = tf;
        }
    }
}


Foam::tmp<Foam::vectorField> Foam::transform
(
    const septernion& tr,
    const vectorField& tf
)
{
    tmp<vectorField > tranf(new vectorField(tf.size()));
    transform(tranf(), tr, tf);
    return tranf;
}


Foam::tmp<Foam::vectorField> Foam::transform
(
    const septernion& tr,
    const tmp<vectorField>& ttf
)
{
    tmp<vectorField > tranf = reuseTmp<vector, vector>::New(ttf);
    transform(tranf(), tr, ttf());
    reuseTmp<vector, vector>::clear(ttf);
    return tranf;
}


// ************************************************************************* //

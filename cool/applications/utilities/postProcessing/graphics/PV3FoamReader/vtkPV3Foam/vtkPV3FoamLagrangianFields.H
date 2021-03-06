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

InClass
    vtkPV3Foam

\*---------------------------------------------------------------------------*/

#ifndef vtkPV3FoamLagrangianFields_H
#define vtkPV3FoamLagrangianFields_H

#include "Cloud.H"

#include "vtkOpenFOAMTupleRemap.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void Foam::vtkPV3Foam::convertLagrangianFields
(
    const IOobjectList& objects,
    vtkMultiBlockDataSet* output,
    const label datasetNo
)
{
    const partInfo& selector = partInfoLagrangian_;

    forAllConstIter(IOobjectList, objects, iter)
    {
        // restrict to this IOField<Type>
        if (iter()->headerClassName() == IOField<Type>::typeName)
        {
            IOField<Type> tf(*iter());
            convertLagrangianField(tf, output, selector, datasetNo);
        }
    }
}


template<class Type>
void Foam::vtkPV3Foam::convertLagrangianField
(
    const IOField<Type>& tf,
    vtkMultiBlockDataSet* output,
    const partInfo& selector,
    const label datasetNo
)
{
    const label nComp = pTraits<Type>::nComponents;

    vtkFloatArray *pointData = vtkFloatArray::New();
    pointData->SetNumberOfTuples( tf.size() );
    pointData->SetNumberOfComponents( nComp );
    pointData->Allocate( nComp*tf.size() );
    pointData->SetName( tf.name().c_str() );

    if (debug)
    {
        Info<< "convert LagrangianField: "
            << tf.name()
            << " size = " << tf.size()
            << " nComp=" << nComp
            << " nTuples = " << tf.size() <<  endl;
    }

    float vec[nComp];
    forAll(tf, i)
    {
        const Type& t = tf[i];
        for (direction d=0; d<nComp; d++)
        {
            vec[d] = component(t, d);
        }
        vtkOpenFOAMTupleRemap<Type>(vec);

        pointData->InsertTuple(i, vec);
    }


    vtkPolyData::SafeDownCast
    (
        GetDataSetFromBlock(output, selector, datasetNo)
    )   ->GetPointData()
        ->AddArray(pointData);

    pointData->Delete();
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

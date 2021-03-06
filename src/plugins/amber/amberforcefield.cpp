/******************************************************************************
**
** Copyright (C) 2009-2011 Kyle Lutz <kyle.r.lutz@gmail.com>
** All rights reserved.
**
** This file is a part of the chemkit project. For more information
** see <http://www.chemkit.org>.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in the
**     documentation and/or other materials provided with the distribution.
**   * Neither the name of the chemkit project nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/

// Implementation of the AMBER force field using the parm99 parameters. The
// AMBER parameters can be downloaded from: <http://ambermd.org/dbase.html>.

#include "amberforcefield.h"

#include "amberatomtyper.h"
#include "amberparameters.h"
#include "ambercalculation.h"

#include <chemkit/atom.h>
#include <chemkit/ring.h>
#include <chemkit/foreach.h>
#include <chemkit/molecule.h>
#include <chemkit/forcefieldinteractions.h>

// --- Construction and Destruction ---------------------------------------- //
AmberForceField::AmberForceField()
    : chemkit::ForceField("amber")
{
    m_parameters = new AmberParameters;

    setFlags(chemkit::ForceField::AnalyticalGradient);
}

AmberForceField::~AmberForceField()
{
    delete m_parameters;
}

// --- Setup --------------------------------------------------------------- //
bool AmberForceField::setup()
{
    const chemkit::Molecule *molecule = this->molecule();
    if(!molecule){
        return false;
    }

    // assign atom types
    AmberAtomTyper typer;
    typer.setMolecule(molecule);

    // add atoms
    foreach(const chemkit::Atom *atom, molecule->atoms()){
        chemkit::ForceFieldAtom *forceFieldAtom = new chemkit::ForceFieldAtom(this, atom);
        forceFieldAtom->setType(typer.typeString(atom));
        addAtom(forceFieldAtom);
    }

    chemkit::ForceFieldInteractions interactions(molecule, this);

    // add bond calculations
    std::pair<const chemkit::ForceFieldAtom *, const chemkit::ForceFieldAtom *> bondedPair;
    foreach(bondedPair, interactions.bondedPairs()){
        addCalculation(new AmberBondCalculation(bondedPair.first,
                                                bondedPair.second));
    }

    // add angle calculations
    std::vector<const chemkit::ForceFieldAtom *> angleGroup;
    foreach(angleGroup, interactions.angleGroups()){
        addCalculation(new AmberAngleCalculation(angleGroup[0],
                                                 angleGroup[1],
                                                 angleGroup[2]));
    }

    // add torsion calculations
    std::vector<const chemkit::ForceFieldAtom *> torsionGroup;
    foreach(torsionGroup, interactions.torsionGroups()){
        addCalculation(new AmberTorsionCalculation(torsionGroup[0],
                                                   torsionGroup[1],
                                                   torsionGroup[2],
                                                   torsionGroup[3]));
    }

    // add nonbonded calculations
    std::pair<const chemkit::ForceFieldAtom *, const chemkit::ForceFieldAtom *> nonbondedPair;
    foreach(nonbondedPair, interactions.nonbondedPairs()){
        addCalculation(new AmberNonbondedCalculation(nonbondedPair.first,
                                                     nonbondedPair.second));
    }

    bool ok = true;

    foreach(chemkit::ForceFieldCalculation *calculation, calculations()){
        bool setup = static_cast<AmberCalculation *>(calculation)->setup(m_parameters);

        if(!setup){
            ok = false;
        }

        setCalculationSetup(calculation, setup);
    }

    return ok;
}

const AmberParameters* AmberForceField::parameters() const
{
    return m_parameters;
}

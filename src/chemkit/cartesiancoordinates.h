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

#ifndef CHEMKIT_CARTESIANCOORDINATES_H
#define CHEMKIT_CARTESIANCOORDINATES_H

#include "chemkit.h"

#include <vector>

#include <Eigen/Core>

#include "matrix.h"
#include "point3.h"
#include "vector3.h"

namespace chemkit {

class Atom;
class Molecule;
class Conformer;

class CHEMKIT_EXPORT CartesianCoordinates
{
public:
    // construction and destruction
    CartesianCoordinates();
    CartesianCoordinates(int size);
    CartesianCoordinates(const Molecule *molecule);
    CartesianCoordinates(const Conformer *conformer);
    CartesianCoordinates(const std::vector<Atom *> &atoms);
    CartesianCoordinates(const std::vector<Point3> &points);
    CartesianCoordinates(const CartesianCoordinates &coordinates);
    ~CartesianCoordinates();

    // properties
    void setSize(int size);
    int size() const;
    bool isEmpty() const;
    Matrix toMatrix() const;

    // coordinates
    void setPosition(int index, const Point3 &position);
    void setPosition(int index, Real x, Real y, Real z);
    Point3 position(int index) const;
    void setValue(int row, int column, Real value);
    Real value(int row, int column) const;
    void append(const Point3 &position);
    void append(Real x, Real y, Real z);
    void insert(int index, const Point3 &position);
    void insert(int index, Real x, Real y, Real z);
    void remove(int index);

    // geometry
    Real distance(int i, int j) const;
    Real angle(int i, int j, int k) const;
    Real angleRadians(int i, int j, int k) const;
    Real torsionAngle(int i, int j, int k, int l) const;
    Real torsionAngleRadians(int i, int j, int k, int l) const;
    Real wilsonAngle(int i, int j, int k, int l) const;
    Real wilsonAngleRadians(int i, int j, int k, int l) const;
    Point3 center() const;
    Point3 weightedCenter(const std::vector<Real> &weights) const;
    void moveBy(const Vector3 &vector);
    void moveBy(Real x, Real y, Real z);
    Matrix distanceMatrix() const;

    // math
    CartesianCoordinates add(const CartesianCoordinates &coordinates) const;
    CartesianCoordinates subtract(const CartesianCoordinates &coordinates) const;
    Eigen::Matrix<Real, 3, 3> multiply(const CartesianCoordinates *coordinates) const;

    // operators
    CartesianCoordinates operator+(const CartesianCoordinates &coordinates) const;
    CartesianCoordinates operator-(const CartesianCoordinates &coordinates) const;
    CartesianCoordinates& operator=(const CartesianCoordinates &coordinates);

private:
    Matrix m_matrix;
};

} // end chemkit namespace

#endif // CHEMKIT_CARTESIANCOORDINATES_H
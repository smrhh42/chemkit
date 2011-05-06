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

#include "trajectoryfileformat.h"

#include "pluginmanager.h"

namespace chemkit {

// === TrajectoryFileFormatPrivate ========================================= //
class TrajectoryFileFormatPrivate
{
    public:
        std::string name;
        std::string errorString;
};

// === TrajectoryFormatFile ================================================ //
/// \class TrajectoryFileFormat trajectoryfileformat.h chemkit/trajectoryfileformat.h
/// \ingroup chemkit
/// \brief The TrajectoryFileFormat class represents a trajectory
///        file format.

// --- Construction and Destruction ---------------------------------------- //
TrajectoryFileFormat::TrajectoryFileFormat(const std::string &name)
    : d(new TrajectoryFileFormatPrivate)
{
    d->name = name;
}

/// Destroys the trajectory file format object.
TrajectoryFileFormat::~TrajectoryFileFormat()
{
    delete d;
}

// --- Properties ---------------------------------------------------------- //
/// Returns the name of the trajectory file format.
std::string TrajectoryFileFormat::name() const
{
    return d->name;
}

// --- Input and Output ---------------------------------------------------- //
/// Reads a trajectory file from \p iodev into \p file.
bool TrajectoryFileFormat::read(QIODevice *iodev, TrajectoryFile *file)
{
    CHEMKIT_UNUSED(iodev);
    CHEMKIT_UNUSED(file);

    setErrorString(QString("'%1' reading not supported.").arg(name().c_str()).toStdString());
    return false;
}

/// Writes a trajectory file from \p file to \p iodev.
bool TrajectoryFileFormat::write(const TrajectoryFile *file, QIODevice *iodev)
{
    CHEMKIT_UNUSED(file);
    CHEMKIT_UNUSED(iodev);

    setErrorString(QString("'%1' writing not supported.").arg(name().c_str()).toStdString());
    return false;
}

// --- Error Handling ------------------------------------------------------ //
/// Sets a string describing the last error that occurred.
void TrajectoryFileFormat::setErrorString(const std::string &errorString)
{
    d->errorString = errorString;
}

/// Returns a string describing the last error that occurred.
std::string TrajectoryFileFormat::errorString() const
{
    return d->errorString;
}

// --- Static Methods ------------------------------------------------------ //
/// Creates a new trajectory file format from \p name. Returns \c 0
/// if \p name is invalid or not supported.
TrajectoryFileFormat* TrajectoryFileFormat::create(const std::string &name)
{
    return PluginManager::instance()->createPluginClass<TrajectoryFileFormat>(name);
}

/// Returns a list of the names of all supported trajectory file
/// formats.
std::vector<std::string> TrajectoryFileFormat::formats()
{
    return PluginManager::instance()->pluginClassNames<TrajectoryFileFormat>();
}

} // end chemkit namespace

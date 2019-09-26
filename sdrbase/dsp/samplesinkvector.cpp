///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 Edouard Griffiths, F4EXB                                   //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
// (at your option) any later version.                                           //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#include "samplesinkvector.h"

SampleSinkVector::SampleSinkVector(QObject* parent) :
    QObject(parent),
    m_dataSize(0)
{}

SampleSinkVector::SampleSinkVector(const SampleSinkVector& other) :
    m_sampleVector(other.m_sampleVector),
    m_dataSize(other.m_dataSize)
{}

SampleSinkVector::~SampleSinkVector()
{}

void SampleSinkVector::write(const SampleVector::const_iterator& begin, const SampleVector::const_iterator& end, bool signal)
{
    if (end - begin > m_sampleVector.size()) {
        m_sampleVector.resize(end - begin);
    }

    std::copy(begin, end, m_sampleVector.begin());
    m_dataSize = end - begin;
    // m_begin = begin;
    // m_end = end;
    if (signal) {
        emit dataReady();
    }
}

void SampleSinkVector::append(const SampleVector::const_iterator& begin, const SampleVector::const_iterator& end, bool signal)
{
    if ((end - begin) + m_dataSize > m_sampleVector.size()) {
        m_sampleVector.resize((end - begin) + m_dataSize);
    }

    std::copy(begin, end, m_sampleVector.begin() + m_dataSize);
    m_dataSize += (end - begin);
    if (signal) {
        emit dataReady();
    }
}

void SampleSinkVector::read(SampleVector::iterator& begin, SampleVector::iterator& end)
{
    begin = m_sampleVector.begin();
    end = m_sampleVector.begin() + m_dataSize;
    // begin = m_begin;
    // end = m_end;
}
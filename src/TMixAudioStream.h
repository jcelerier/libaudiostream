/*

Copyright (C) Grame 2002-2012

This library is free software; you can redistribute it and modify it under
the terms of the GNU Library General Public License as published by the
Free Software Foundation version 2 of the License, or any later version.

This library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
for more details.

You should have received a copy of the GNU Library General Public License
along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
research@grame.fr

*/

#ifndef __TMixAudioStream__
#define __TMixAudioStream__

#include "TBinaryAudioStream.h"
#include "UTools.h"

//-----------------------
// Class TMixAudioStream
//-----------------------
/*!
\brief A TMixAudioStream mix two streams.
*/

class TMixAudioStream : public TBinaryAudioStream
{

    public:

        TMixAudioStream(TAudioStreamPtr s1, TAudioStreamPtr s2): TBinaryAudioStream(s1, s2, NULL)
        {}
        virtual ~TMixAudioStream()
        {}

        long Read(TAudioBuffer<float>* buffer, long framesNum, long framePos, long channels);

        void Reset();
        TAudioStreamPtr CutBegin(long frames);
        long Length()
        {
            return UTools::Max(fStream1->Length(), fStream2->Length());
        }
        long Channels()
        {
            return UTools::Max(fStream1->Channels(), fStream2->Channels());
        }
        TAudioStreamPtr Copy()
        {
            return new TMixAudioStream(fStream1->Copy(), fStream2->Copy());
        }
};

typedef TMixAudioStream * TMixAudioStreamPtr;

#endif

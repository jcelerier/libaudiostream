/*

Copyright (C) Grame 2002-2013

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

#ifndef __TNullAudioStream__
#define __TNullAudioStream__

#include "TAudioStream.h"
#include "UAudioTools.h"
#include "UTools.h"

//------------------------
// Class TNullAudioStream
//------------------------
/*!
\brief  A TNullAudioStream generates "silence".
*/

class TNullAudioStream : public TAudioStream
{

    private:

        long fFramesNum;
        long fCurFrame;

    public:

        TNullAudioStream(long lengthFrame): fFramesNum(lengthFrame), fCurFrame(0)
        {}
        virtual ~TNullAudioStream()
        {}

        long Read(FLOAT_BUFFER buffer, long framesNum, long framePos, long channels)
        {
            framesNum = UTools::Min(framesNum, fFramesNum - fCurFrame);
            fCurFrame += framesNum;
            return framesNum;
        }

        TAudioStreamPtr CutBegin(long frames)
        {
            return new TNullAudioStream(UTools::Max(0,fFramesNum - frames));
        }
        long Length()
        {
            return fFramesNum;
        }
        void Reset()
        {
            fCurFrame = 0;
        }
        TAudioStreamPtr Copy()
        {
            return new TNullAudioStream(fFramesNum);
        }
};

typedef TNullAudioStream * TNullAudioStreamPtr;

#endif

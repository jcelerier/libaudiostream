/*
Copyright � Grame 2002

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
grame@rd.grame.fr

*/

#ifndef __TVolAudioEffect__
#define __TVolAudioEffect__

#include "TAudioEffectInterface.h"

//-----------------------
// Class TVolAudioEffect
//-----------------------
/*!
\brief Volume effect.
*/

class TVolAudioEffect : public TAudioEffectInterface
{

    private:

        float fGain;

    public:

        TVolAudioEffect(float gain): TAudioEffectInterface(), fGain(gain)
        {}
        virtual ~TVolAudioEffect()
        {}

        void Process(float* buffer, long framesNum, long channels)
        {
            for (int i = 0; i < framesNum; i++) {
                for (int j = 0; j < channels; j++) {
                    buffer[i*channels + j] = (buffer[i * channels + j] * fGain);
                }
            }
        }

        TAudioEffectInterface* Copy()
        {
            return new TVolAudioEffect(fGain);
        }
        void Reset()
        {}
        long Channels()
        {
            return 2;
        }
};

typedef TVolAudioEffect * TVolAudioEffectPtr;

#endif

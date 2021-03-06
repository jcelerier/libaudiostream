/*

Copyright � Grame 2006-2007

This library is free software; you can redistribute it and modify it under
the terms of the GNU Library General Public License as published by the
Free Software Foundation version 2 of the License, or any later version.

This library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
for more details.

You should have received a copy of the GNU Library General Public License
along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
research@grame.fr

*/

#include <iostream>
#include "LibAudioStream++.h"
using namespace std;

class FilePlayer {

	private:
	
		enum { kIn = 2, kOut = 2, kChans = 8, kSRate = 44100, kAudioBuff = 512, kFileBuff = 65536 * 4 };
		AudioPlayerPtr fPlayer;

	public:
	
		FilePlayer()	
		{ 
			fPlayer = OpenAudioPlayer(kIn, kOut, kChans, kSRate, kAudioBuff, kFileBuff, kFileBuff, kPortAudioRenderer, 1);
			if (!fPlayer) {
				printf("cannot start player with PortAudio API, now quit...\n");
				return;
			}
			StartAudioPlayer(fPlayer);
		}

		virtual ~FilePlayer()	
		{
			StopChannel(fPlayer, 1);
    		StopAudioPlayer(fPlayer);
    		CloseAudioPlayer(fPlayer);
		}
		
		void Play(char *file, long beginFrame, long endFrame) 
		{
			AudioStream stream = MakeStereoSound(MakeRegionSound(file, beginFrame, endFrame));
			if (!stream) {
				printf("cannot open filename = %s, now quit...\n", file);
				return;
			}
			LoadChannel(fPlayer, stream, 1, 1.0f, 1.0f, 0.0f);
			StartChannel(fPlayer, 1);
		} 
		
		long Status() 
		{
			ChannelInfo info;
			GetInfoChannel(fPlayer, 1, &info);
			return info.fStatus;
		} 

};

int main(int argc, char *argv[]) 
{
	if (argc != 4) {
		cerr << "usage: fileplay 'file' 'start' 'end'\n" << endl;
		return 1;
	} else {
		FilePlayer player;
		int start = atoi(argv[2]);
		int end = atoi(argv[3]);
		cout << "playing file " << argv[1] << " from " << start << " to " << end << endl;	
		player.Play(argv[1], start * 44100, end * 44100);
		while (player.Status());
		cout << "done" << endl;	
	}
	return 0;
}

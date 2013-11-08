
#include <stdio.h>
#include "LibAudioStreamMC++.h"

#define LLVM_EFFECT1 "/Documents/faust-sf/examples/freeverb.dsp"
#define LLVM_EFFECT2 "/Documents/faust-sf/examples/zita_rev1.dsp"
#define LLVM_EFFECT3 "/Documents/faust-sf/examples/freeverb4.dsp"

#define CHANNELS 4

#define FILENAME1 "/Users/letz/Music/Sounds/levot.wav"
#define FILENAME2 "/Users/letz/Music/Sounds/tango.wav"
#define FILENAME3 "/Users/letz/son1.wav"
#define FILENAME4 "/Users/letz/Music/Sounds/levot-mono.aiff"

// Global context
static long gSampleRate = 0;
static long gBufferSize = 0;
static AudioRendererPtr gAudioRenderer = 0;
static AudioPlayerPtr gAudioPlayer = 0;

static long tmpInChan = 4;
static long tmpOutChan = 4;
static long tmpBufferSize = 512;
static long tmpSampleRate = 44100;
  
static AudioEffect faust_effect1 = MakeFaustAudioEffect(LLVM_EFFECT1, "", "");
static AudioEffect faust_effect2 = MakeFaustAudioEffect(LLVM_EFFECT2, "", "");
static AudioEffect faust_effect3 = MakeFaustAudioEffect("process = _@10000,_@10000,_@10000,_@10000;", "", "");
static AudioEffect faust_effect4 = MakeFaustAudioEffect(LLVM_EFFECT3, "", "");
static AudioEffect faust_effect5 = MakeFaustAudioEffect("process = _*vslider(\"Volume\", 1, 0, 1, 0.1);", "", "");
    
static void printControls(AudioEffect faust_effect)
{
    printf("Faust effect: param num %ld\n", GetControlCountEffect(faust_effect));
    for (int i = 0; i < GetControlCountEffect(faust_effect); i++) {
        float min, max, init;
        char label[32];
        GetControlParamEffect(faust_effect, i, label, &min, &max, &init); 
        printf("Faust effect: param label = %s min = %f max = %f init = %f value = %f\n", label, min, max, init, GetControlValueEffect(faust_effect, i));
    }
}

static void test1()
{
    AudioStream stream1 = MakeRegionSound(FILENAME1, 5 * tmpSampleRate, tmpSampleRate * 15);
    AddSound(gAudioPlayer, stream1);

    AudioStream stream2 = MakeRegionSound(FILENAME2, 0, tmpSampleRate * 25);
    AddSound(gAudioPlayer, stream2);
}

static void test2()
{
    AudioStream stream1 = MakeRegionSound(FILENAME1, 5 * tmpSampleRate, tmpSampleRate * 15);
    AudioStream stream2 = MakeRegionSound(FILENAME2, 0, tmpSampleRate * 25);
    AudioStream stream3 = MakeParSound(stream1, stream2);
    AddSound(gAudioPlayer, stream3);
}

static void test3()
{
    AudioStream stream1 = MakeRegionSound(FILENAME4, 5 * tmpSampleRate, tmpSampleRate * 15);
    AudioStream stream2 = MakeRegionSound(FILENAME4, 7 * tmpSampleRate, tmpSampleRate * 15);
    
    AudioStream stream3 = MakeRegionSound(FILENAME2, 0, tmpSampleRate * 25);
    AudioStream stream4 = MakeParSound(stream1, MakeParSound(stream2, stream3));
    AddSound(gAudioPlayer, stream4);
}

static void test4()
{
    AudioStream stream1 = MakeEffectSound(MakeRegionSound(FILENAME1, 5 * tmpSampleRate, tmpSampleRate * 50), faust_effect1, 100, 100);
    AddSound(gAudioPlayer, stream1);
    
    AudioStream stream2 = MakeEffectSound(MakeRegionSound(FILENAME2, 5 * tmpSampleRate, tmpSampleRate * 50), faust_effect2, 100, 100);
    AddSound(gAudioPlayer, stream2);
}

static void test5()
{
    AudioStream stream1 = MakeEffectSound(MakeRegionSound(FILENAME1, 5 * tmpSampleRate, tmpSampleRate * 50), faust_effect1, 100, 100);
    AudioStream stream2 = MakeEffectSound(MakeRegionSound(FILENAME2, 5 * tmpSampleRate, tmpSampleRate * 50), faust_effect2, 100, 100);
    AudioStream stream3 = MakeParSound(stream1, stream2);
    AddSound(gAudioPlayer, stream3);
}

static void test6()
{
    AudioStream stream1 = MakeEffectSound(MakeSharedInputSound(), faust_effect4, 100, 100); 
    AddSound(gAudioPlayer, stream1);
}

static void test7()
{
    AudioStream stream1 = MakeSeqSound(MakeCutSound(MakeSharedInputSound(), 0, 10*tmpSampleRate),
                            MakeLoopSound(MakeCutSound(MakeEffectSound(MakeSharedInputSound(), faust_effect4, 100, 100), 0*tmpSampleRate, 10*tmpSampleRate), 4), 0);
     
    AddSound(gAudioPlayer, stream1);
}

double pitch_shift = 1.0;
double time_strech = 0.5;

static void test8()
{
    AudioStream stream2 = MakeRegionSound(FILENAME2, 0, tmpSampleRate * 25);
    AddSound(gAudioPlayer, MakePitchSchiftTimeStretchSound(stream2, &pitch_shift, &time_strech));
}

static void test9()
{
    AudioStream stream1 = MakeRegionSound(FILENAME1, 0, tmpSampleRate * 25);
    AudioStream stream2 = MakeRegionSound(FILENAME2, 0, tmpSampleRate * 25);
    AudioStream stream3 = MakeParSound(stream1, stream2);
    AddSound(gAudioPlayer, MakePitchSchiftTimeStretchSound(stream3, &pitch_shift, &time_strech));
}

static void test10()
{
    //AudioStream stream1 = MakeEffectSound(MakeSharedInputSound(), faust_effect5, 100, 100);
    //AudioStream stream1 = MakeEffectSound(MakeSharedInputSound(), faust_effect1, 100, 100); 
    AudioStream stream1 = MakeEffectSound(MakeSharedInputSound(), faust_effect4, 100, 100); 
    
    printf("Error %s\n", GetLastLibError()); 
    AddSound(gAudioPlayer, stream1);
}

static void test11()
{
    //AudioStream stream1 = MakeEffectSound(MakeSharedInputSound(), faust_effect5, 100, 100);
    //AudioStream stream1 = MakeEffectSound(MakeSharedInputSound(), faust_effect1, 100, 100); 
    
    std::vector <int> selection;
    selection.push_back(0);
    
    AudioStream stream1 = MakeSelectSound(MakeEffectSound(MakeSharedInputSound(), faust_effect4, 100, 100), selection); 
    
    printf("Error %s\n", GetLastLibError()); 
    //AddSound(gAudioPlayer, stream1);
}

int main(int argc, char* argv[])
{
    gAudioPlayer = OpenAudioPlayer(tmpInChan, tmpOutChan, CHANNELS, tmpSampleRate, tmpBufferSize, 65536 * 4, tmpSampleRate * 60 * 10, kJackRenderer, 1);
    if (!gAudioPlayer) {
        printf("Cannot OpenAudioPlayer\n");
        return 0;
    } 

    SetControlValueEffect(faust_effect1, 0, 0.99);
    SetControlValueEffect(faust_effect1, 1, 0.99);
    SetControlValueEffect(faust_effect1, 2, 0.99);
    
    printControls(faust_effect1);
    printControls(faust_effect2);
    
    //test();
    /*
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    */
    //test8();
    //test9();
    
    //test10();
    test11();
       
    StartAudioPlayer(gAudioPlayer);
    
    SetControlValueEffect(faust_effect1, 0, 0.9);
    SetControlValueEffect(faust_effect1, 1, 0.9);
    SetControlValueEffect(faust_effect1, 2, 0.9);
    
    SetControlValueEffect(faust_effect2, 9, 0.9);
    SetControlValueEffect(faust_effect2, 10, 0.9);
    
    SetControlValueEffect(faust_effect4, 0, 0.9);
    SetControlValueEffect(faust_effect4, 1, 0.9);
    SetControlValueEffect(faust_effect4, 2, 0.9);
    
    SetControlValueEffect(faust_effect5, 0, 0.9);
     
    char c;
    printf("Type 'q' to quit\n");

    while ((c = getchar()) && c != 'q') {
        switch (c) {
        
            case 'p':
                AddSound(gAudioPlayer, MakeEffectSound(MakeRegionSound(FILENAME1, 5 * tmpSampleRate, tmpSampleRate * 13), MakeFaustAudioEffect(LLVM_EFFECT1, "", ""), 100, 100));
                break;
                
             case 'o':
                AddSound(gAudioPlayer, MakeEffectSound(MakeRegionSound(FILENAME2, 5 * tmpSampleRate, tmpSampleRate * 13), MakeFaustAudioEffect(LLVM_EFFECT1, "", ""), 100, 100));
                break;
        
        }
        sleep(0.01);
    }
    
}
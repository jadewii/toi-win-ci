//
//     ,ad888ba,                              88
//    d8"'    "8b
//   d8            88,dba,,adba,   ,aPP8A.A8  88     The Cmajor Toolkit
//   Y8,           88    88    88  88     88  88
//    Y8a.   .a8P  88    88    88  88,   ,88  88     (C)2024 Cmajor Software Ltd
//     '"Y888Y"'   88    88    88  '"8bbP"Y8  88     https://cmajor.dev
//                                           ,88
//                                        888P"
//
//  The Cmajor project is subject to commercial or open-source licensing.
//  You may use it under the terms of the GPLv3 (see www.gnu.org/licenses), or
//  visit https://cmajor.dev to learn about our commercial licence options.
//
//  CMAJOR IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
//  EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
//  DISCLAIMED.

// Auto-generated Cmajor code for patch 'JWVCS'

#include <JuceHeader.h>
#include "cmajor/helpers/cmaj_JUCEPlugin.h"
#include "choc/javascript/choc_javascript_QuickJS.h"



#include <cstdint>
#include <cmath>
#include <string>
#include <cstring>
#include <array>
#include <stdexcept>

//==============================================================================
/// Auto-generated C++ class for the 'JWVCS' processor
///

#if ! (defined (__cplusplus) && (__cplusplus >= 201703L))
 #error "This code requires that your compiler is set to use C++17 or later!"
#endif

namespace performer
{
    struct JWVCS
    {
        JWVCS() = default;
        ~JWVCS() = default;

        static constexpr std::string_view name = "JWVCS";

        //==============================================================================
        using EndpointHandle = uint32_t;

        enum class EndpointType
        {
            stream,
            event,
            value
        };

        struct EndpointInfo
        {
            uint32_t handle;
            const char* name;
            EndpointType endpointType;
        };

        //==============================================================================
        static constexpr uint32_t numInputEndpoints  = 189;
        static constexpr uint32_t numOutputEndpoints = 2;

        static constexpr uint32_t maxFramesPerBlock  = 512;
        static constexpr uint32_t eventBufferSize    = 32;
        static constexpr uint32_t maxOutputEventSize = 8;
        static constexpr double   latency            = 0.000000;

        enum class EndpointHandles
        {
            midiIn    = 1  ,
            o1Freq    = 2  ,
            o1Range   = 3  ,
            o1Sine    = 4  ,
            o1Saw     = 5  ,
            o2Freq    = 6  ,
            o2Range   = 7  ,
            o2Shape   = 8  ,
            o2Pw      = 9  ,
            o2Level   = 10 ,
            o3Freq    = 11 ,
            o3Range   = 12 ,
            o3Shape   = 13 ,
            o3Pw      = 14 ,
            o3Level   = 15 ,
            drift     = 16 ,
            noise     = 17 ,
            cutoff    = 18 ,
            reso      = 19 ,
            fKeyTrack = 20 ,
            trapA     = 21 ,
            trapOn    = 22 ,
            trapD     = 23 ,
            trapOff   = 24 ,
            reverb    = 25 ,
            mx00      = 26 ,
            mx01      = 27 ,
            mx02      = 28 ,
            mx03      = 29 ,
            mx04      = 30 ,
            mx05      = 31 ,
            mx06      = 32 ,
            mx07      = 33 ,
            mx08      = 34 ,
            mx09      = 35 ,
            mx0A      = 36 ,
            mx0B      = 37 ,
            mx0C      = 38 ,
            mx0D      = 39 ,
            mx0E      = 40 ,
            mx0F      = 41 ,
            mx10      = 42 ,
            mx11      = 43 ,
            mx12      = 44 ,
            mx13      = 45 ,
            mx14      = 46 ,
            mx15      = 47 ,
            mx16      = 48 ,
            mx17      = 49 ,
            mx18      = 50 ,
            mx19      = 51 ,
            mx1A      = 52 ,
            mx1B      = 53 ,
            mx1C      = 54 ,
            mx1D      = 55 ,
            mx1E      = 56 ,
            mx1F      = 57 ,
            mx20      = 58 ,
            mx21      = 59 ,
            mx22      = 60 ,
            mx23      = 61 ,
            mx24      = 62 ,
            mx25      = 63 ,
            mx26      = 64 ,
            mx27      = 65 ,
            mx28      = 66 ,
            mx29      = 67 ,
            mx2A      = 68 ,
            mx2B      = 69 ,
            mx2C      = 70 ,
            mx2D      = 71 ,
            mx2E      = 72 ,
            mx2F      = 73 ,
            mx30      = 74 ,
            mx31      = 75 ,
            mx32      = 76 ,
            mx33      = 77 ,
            mx34      = 78 ,
            mx35      = 79 ,
            mx36      = 80 ,
            mx37      = 81 ,
            mx38      = 82 ,
            mx39      = 83 ,
            mx3A      = 84 ,
            mx3B      = 85 ,
            mx3C      = 86 ,
            mx3D      = 87 ,
            mx3E      = 88 ,
            mx3F      = 89 ,
            mx40      = 90 ,
            mx41      = 91 ,
            mx42      = 92 ,
            mx43      = 93 ,
            mx44      = 94 ,
            mx45      = 95 ,
            mx46      = 96 ,
            mx47      = 97 ,
            mx48      = 98 ,
            mx49      = 99 ,
            mx4A      = 100,
            mx4B      = 101,
            mx4C      = 102,
            mx4D      = 103,
            mx4E      = 104,
            mx4F      = 105,
            mx50      = 106,
            mx51      = 107,
            mx52      = 108,
            mx53      = 109,
            mx54      = 110,
            mx55      = 111,
            mx56      = 112,
            mx57      = 113,
            mx58      = 114,
            mx59      = 115,
            mx5A      = 116,
            mx5B      = 117,
            mx5C      = 118,
            mx5D      = 119,
            mx5E      = 120,
            mx5F      = 121,
            mx60      = 122,
            mx61      = 123,
            mx62      = 124,
            mx63      = 125,
            mx64      = 126,
            mx65      = 127,
            mx66      = 128,
            mx67      = 129,
            mx68      = 130,
            mx69      = 131,
            mx6A      = 132,
            mx6B      = 133,
            mx6C      = 134,
            mx6D      = 135,
            mx6E      = 136,
            mx6F      = 137,
            mx70      = 138,
            mx71      = 139,
            mx72      = 140,
            mx73      = 141,
            mx74      = 142,
            mx75      = 143,
            mx76      = 144,
            mx77      = 145,
            mx78      = 146,
            mx79      = 147,
            mx7A      = 148,
            mx7B      = 149,
            mx7C      = 150,
            mx7D      = 151,
            mx7E      = 152,
            mx7F      = 153,
            mx80      = 154,
            mx81      = 155,
            mx82      = 156,
            mx83      = 157,
            mx84      = 158,
            mx85      = 159,
            mx86      = 160,
            mx87      = 161,
            mx88      = 162,
            mx89      = 163,
            mx8A      = 164,
            mx8B      = 165,
            mx8C      = 166,
            mx8D      = 167,
            mx8E      = 168,
            mx8F      = 169,
            mx90      = 170,
            mx91      = 171,
            mx92      = 172,
            mx93      = 173,
            mx94      = 174,
            mx95      = 175,
            mx96      = 176,
            mx97      = 177,
            mx98      = 178,
            mx99      = 179,
            mx9A      = 180,
            mx9B      = 181,
            mx9C      = 182,
            mx9D      = 183,
            mx9E      = 184,
            mx9F      = 185,
            joyX      = 186,
            joyY      = 187,
            volume    = 188,
            tune      = 189,
            audioOut  = 190,
            noteOut   = 191
        };

        static constexpr uint32_t getEndpointHandleForName (std::string_view endpointName)
        {
            if (endpointName == "midiIn")     return static_cast<uint32_t> (EndpointHandles::midiIn);
            if (endpointName == "o1Freq")     return static_cast<uint32_t> (EndpointHandles::o1Freq);
            if (endpointName == "o1Range")    return static_cast<uint32_t> (EndpointHandles::o1Range);
            if (endpointName == "o1Sine")     return static_cast<uint32_t> (EndpointHandles::o1Sine);
            if (endpointName == "o1Saw")      return static_cast<uint32_t> (EndpointHandles::o1Saw);
            if (endpointName == "o2Freq")     return static_cast<uint32_t> (EndpointHandles::o2Freq);
            if (endpointName == "o2Range")    return static_cast<uint32_t> (EndpointHandles::o2Range);
            if (endpointName == "o2Shape")    return static_cast<uint32_t> (EndpointHandles::o2Shape);
            if (endpointName == "o2Pw")       return static_cast<uint32_t> (EndpointHandles::o2Pw);
            if (endpointName == "o2Level")    return static_cast<uint32_t> (EndpointHandles::o2Level);
            if (endpointName == "o3Freq")     return static_cast<uint32_t> (EndpointHandles::o3Freq);
            if (endpointName == "o3Range")    return static_cast<uint32_t> (EndpointHandles::o3Range);
            if (endpointName == "o3Shape")    return static_cast<uint32_t> (EndpointHandles::o3Shape);
            if (endpointName == "o3Pw")       return static_cast<uint32_t> (EndpointHandles::o3Pw);
            if (endpointName == "o3Level")    return static_cast<uint32_t> (EndpointHandles::o3Level);
            if (endpointName == "drift")      return static_cast<uint32_t> (EndpointHandles::drift);
            if (endpointName == "noise")      return static_cast<uint32_t> (EndpointHandles::noise);
            if (endpointName == "cutoff")     return static_cast<uint32_t> (EndpointHandles::cutoff);
            if (endpointName == "reso")       return static_cast<uint32_t> (EndpointHandles::reso);
            if (endpointName == "fKeyTrack")  return static_cast<uint32_t> (EndpointHandles::fKeyTrack);
            if (endpointName == "trapA")      return static_cast<uint32_t> (EndpointHandles::trapA);
            if (endpointName == "trapOn")     return static_cast<uint32_t> (EndpointHandles::trapOn);
            if (endpointName == "trapD")      return static_cast<uint32_t> (EndpointHandles::trapD);
            if (endpointName == "trapOff")    return static_cast<uint32_t> (EndpointHandles::trapOff);
            if (endpointName == "reverb")     return static_cast<uint32_t> (EndpointHandles::reverb);
            if (endpointName == "mx00")       return static_cast<uint32_t> (EndpointHandles::mx00);
            if (endpointName == "mx01")       return static_cast<uint32_t> (EndpointHandles::mx01);
            if (endpointName == "mx02")       return static_cast<uint32_t> (EndpointHandles::mx02);
            if (endpointName == "mx03")       return static_cast<uint32_t> (EndpointHandles::mx03);
            if (endpointName == "mx04")       return static_cast<uint32_t> (EndpointHandles::mx04);
            if (endpointName == "mx05")       return static_cast<uint32_t> (EndpointHandles::mx05);
            if (endpointName == "mx06")       return static_cast<uint32_t> (EndpointHandles::mx06);
            if (endpointName == "mx07")       return static_cast<uint32_t> (EndpointHandles::mx07);
            if (endpointName == "mx08")       return static_cast<uint32_t> (EndpointHandles::mx08);
            if (endpointName == "mx09")       return static_cast<uint32_t> (EndpointHandles::mx09);
            if (endpointName == "mx0A")       return static_cast<uint32_t> (EndpointHandles::mx0A);
            if (endpointName == "mx0B")       return static_cast<uint32_t> (EndpointHandles::mx0B);
            if (endpointName == "mx0C")       return static_cast<uint32_t> (EndpointHandles::mx0C);
            if (endpointName == "mx0D")       return static_cast<uint32_t> (EndpointHandles::mx0D);
            if (endpointName == "mx0E")       return static_cast<uint32_t> (EndpointHandles::mx0E);
            if (endpointName == "mx0F")       return static_cast<uint32_t> (EndpointHandles::mx0F);
            if (endpointName == "mx10")       return static_cast<uint32_t> (EndpointHandles::mx10);
            if (endpointName == "mx11")       return static_cast<uint32_t> (EndpointHandles::mx11);
            if (endpointName == "mx12")       return static_cast<uint32_t> (EndpointHandles::mx12);
            if (endpointName == "mx13")       return static_cast<uint32_t> (EndpointHandles::mx13);
            if (endpointName == "mx14")       return static_cast<uint32_t> (EndpointHandles::mx14);
            if (endpointName == "mx15")       return static_cast<uint32_t> (EndpointHandles::mx15);
            if (endpointName == "mx16")       return static_cast<uint32_t> (EndpointHandles::mx16);
            if (endpointName == "mx17")       return static_cast<uint32_t> (EndpointHandles::mx17);
            if (endpointName == "mx18")       return static_cast<uint32_t> (EndpointHandles::mx18);
            if (endpointName == "mx19")       return static_cast<uint32_t> (EndpointHandles::mx19);
            if (endpointName == "mx1A")       return static_cast<uint32_t> (EndpointHandles::mx1A);
            if (endpointName == "mx1B")       return static_cast<uint32_t> (EndpointHandles::mx1B);
            if (endpointName == "mx1C")       return static_cast<uint32_t> (EndpointHandles::mx1C);
            if (endpointName == "mx1D")       return static_cast<uint32_t> (EndpointHandles::mx1D);
            if (endpointName == "mx1E")       return static_cast<uint32_t> (EndpointHandles::mx1E);
            if (endpointName == "mx1F")       return static_cast<uint32_t> (EndpointHandles::mx1F);
            if (endpointName == "mx20")       return static_cast<uint32_t> (EndpointHandles::mx20);
            if (endpointName == "mx21")       return static_cast<uint32_t> (EndpointHandles::mx21);
            if (endpointName == "mx22")       return static_cast<uint32_t> (EndpointHandles::mx22);
            if (endpointName == "mx23")       return static_cast<uint32_t> (EndpointHandles::mx23);
            if (endpointName == "mx24")       return static_cast<uint32_t> (EndpointHandles::mx24);
            if (endpointName == "mx25")       return static_cast<uint32_t> (EndpointHandles::mx25);
            if (endpointName == "mx26")       return static_cast<uint32_t> (EndpointHandles::mx26);
            if (endpointName == "mx27")       return static_cast<uint32_t> (EndpointHandles::mx27);
            if (endpointName == "mx28")       return static_cast<uint32_t> (EndpointHandles::mx28);
            if (endpointName == "mx29")       return static_cast<uint32_t> (EndpointHandles::mx29);
            if (endpointName == "mx2A")       return static_cast<uint32_t> (EndpointHandles::mx2A);
            if (endpointName == "mx2B")       return static_cast<uint32_t> (EndpointHandles::mx2B);
            if (endpointName == "mx2C")       return static_cast<uint32_t> (EndpointHandles::mx2C);
            if (endpointName == "mx2D")       return static_cast<uint32_t> (EndpointHandles::mx2D);
            if (endpointName == "mx2E")       return static_cast<uint32_t> (EndpointHandles::mx2E);
            if (endpointName == "mx2F")       return static_cast<uint32_t> (EndpointHandles::mx2F);
            if (endpointName == "mx30")       return static_cast<uint32_t> (EndpointHandles::mx30);
            if (endpointName == "mx31")       return static_cast<uint32_t> (EndpointHandles::mx31);
            if (endpointName == "mx32")       return static_cast<uint32_t> (EndpointHandles::mx32);
            if (endpointName == "mx33")       return static_cast<uint32_t> (EndpointHandles::mx33);
            if (endpointName == "mx34")       return static_cast<uint32_t> (EndpointHandles::mx34);
            if (endpointName == "mx35")       return static_cast<uint32_t> (EndpointHandles::mx35);
            if (endpointName == "mx36")       return static_cast<uint32_t> (EndpointHandles::mx36);
            if (endpointName == "mx37")       return static_cast<uint32_t> (EndpointHandles::mx37);
            if (endpointName == "mx38")       return static_cast<uint32_t> (EndpointHandles::mx38);
            if (endpointName == "mx39")       return static_cast<uint32_t> (EndpointHandles::mx39);
            if (endpointName == "mx3A")       return static_cast<uint32_t> (EndpointHandles::mx3A);
            if (endpointName == "mx3B")       return static_cast<uint32_t> (EndpointHandles::mx3B);
            if (endpointName == "mx3C")       return static_cast<uint32_t> (EndpointHandles::mx3C);
            if (endpointName == "mx3D")       return static_cast<uint32_t> (EndpointHandles::mx3D);
            if (endpointName == "mx3E")       return static_cast<uint32_t> (EndpointHandles::mx3E);
            if (endpointName == "mx3F")       return static_cast<uint32_t> (EndpointHandles::mx3F);
            if (endpointName == "mx40")       return static_cast<uint32_t> (EndpointHandles::mx40);
            if (endpointName == "mx41")       return static_cast<uint32_t> (EndpointHandles::mx41);
            if (endpointName == "mx42")       return static_cast<uint32_t> (EndpointHandles::mx42);
            if (endpointName == "mx43")       return static_cast<uint32_t> (EndpointHandles::mx43);
            if (endpointName == "mx44")       return static_cast<uint32_t> (EndpointHandles::mx44);
            if (endpointName == "mx45")       return static_cast<uint32_t> (EndpointHandles::mx45);
            if (endpointName == "mx46")       return static_cast<uint32_t> (EndpointHandles::mx46);
            if (endpointName == "mx47")       return static_cast<uint32_t> (EndpointHandles::mx47);
            if (endpointName == "mx48")       return static_cast<uint32_t> (EndpointHandles::mx48);
            if (endpointName == "mx49")       return static_cast<uint32_t> (EndpointHandles::mx49);
            if (endpointName == "mx4A")       return static_cast<uint32_t> (EndpointHandles::mx4A);
            if (endpointName == "mx4B")       return static_cast<uint32_t> (EndpointHandles::mx4B);
            if (endpointName == "mx4C")       return static_cast<uint32_t> (EndpointHandles::mx4C);
            if (endpointName == "mx4D")       return static_cast<uint32_t> (EndpointHandles::mx4D);
            if (endpointName == "mx4E")       return static_cast<uint32_t> (EndpointHandles::mx4E);
            if (endpointName == "mx4F")       return static_cast<uint32_t> (EndpointHandles::mx4F);
            if (endpointName == "mx50")       return static_cast<uint32_t> (EndpointHandles::mx50);
            if (endpointName == "mx51")       return static_cast<uint32_t> (EndpointHandles::mx51);
            if (endpointName == "mx52")       return static_cast<uint32_t> (EndpointHandles::mx52);
            if (endpointName == "mx53")       return static_cast<uint32_t> (EndpointHandles::mx53);
            if (endpointName == "mx54")       return static_cast<uint32_t> (EndpointHandles::mx54);
            if (endpointName == "mx55")       return static_cast<uint32_t> (EndpointHandles::mx55);
            if (endpointName == "mx56")       return static_cast<uint32_t> (EndpointHandles::mx56);
            if (endpointName == "mx57")       return static_cast<uint32_t> (EndpointHandles::mx57);
            if (endpointName == "mx58")       return static_cast<uint32_t> (EndpointHandles::mx58);
            if (endpointName == "mx59")       return static_cast<uint32_t> (EndpointHandles::mx59);
            if (endpointName == "mx5A")       return static_cast<uint32_t> (EndpointHandles::mx5A);
            if (endpointName == "mx5B")       return static_cast<uint32_t> (EndpointHandles::mx5B);
            if (endpointName == "mx5C")       return static_cast<uint32_t> (EndpointHandles::mx5C);
            if (endpointName == "mx5D")       return static_cast<uint32_t> (EndpointHandles::mx5D);
            if (endpointName == "mx5E")       return static_cast<uint32_t> (EndpointHandles::mx5E);
            if (endpointName == "mx5F")       return static_cast<uint32_t> (EndpointHandles::mx5F);
            if (endpointName == "mx60")       return static_cast<uint32_t> (EndpointHandles::mx60);
            if (endpointName == "mx61")       return static_cast<uint32_t> (EndpointHandles::mx61);
            if (endpointName == "mx62")       return static_cast<uint32_t> (EndpointHandles::mx62);
            if (endpointName == "mx63")       return static_cast<uint32_t> (EndpointHandles::mx63);
            if (endpointName == "mx64")       return static_cast<uint32_t> (EndpointHandles::mx64);
            if (endpointName == "mx65")       return static_cast<uint32_t> (EndpointHandles::mx65);
            if (endpointName == "mx66")       return static_cast<uint32_t> (EndpointHandles::mx66);
            if (endpointName == "mx67")       return static_cast<uint32_t> (EndpointHandles::mx67);
            if (endpointName == "mx68")       return static_cast<uint32_t> (EndpointHandles::mx68);
            if (endpointName == "mx69")       return static_cast<uint32_t> (EndpointHandles::mx69);
            if (endpointName == "mx6A")       return static_cast<uint32_t> (EndpointHandles::mx6A);
            if (endpointName == "mx6B")       return static_cast<uint32_t> (EndpointHandles::mx6B);
            if (endpointName == "mx6C")       return static_cast<uint32_t> (EndpointHandles::mx6C);
            if (endpointName == "mx6D")       return static_cast<uint32_t> (EndpointHandles::mx6D);
            if (endpointName == "mx6E")       return static_cast<uint32_t> (EndpointHandles::mx6E);
            if (endpointName == "mx6F")       return static_cast<uint32_t> (EndpointHandles::mx6F);
            if (endpointName == "mx70")       return static_cast<uint32_t> (EndpointHandles::mx70);
            if (endpointName == "mx71")       return static_cast<uint32_t> (EndpointHandles::mx71);
            if (endpointName == "mx72")       return static_cast<uint32_t> (EndpointHandles::mx72);
            if (endpointName == "mx73")       return static_cast<uint32_t> (EndpointHandles::mx73);
            if (endpointName == "mx74")       return static_cast<uint32_t> (EndpointHandles::mx74);
            if (endpointName == "mx75")       return static_cast<uint32_t> (EndpointHandles::mx75);
            if (endpointName == "mx76")       return static_cast<uint32_t> (EndpointHandles::mx76);
            if (endpointName == "mx77")       return static_cast<uint32_t> (EndpointHandles::mx77);
            if (endpointName == "mx78")       return static_cast<uint32_t> (EndpointHandles::mx78);
            if (endpointName == "mx79")       return static_cast<uint32_t> (EndpointHandles::mx79);
            if (endpointName == "mx7A")       return static_cast<uint32_t> (EndpointHandles::mx7A);
            if (endpointName == "mx7B")       return static_cast<uint32_t> (EndpointHandles::mx7B);
            if (endpointName == "mx7C")       return static_cast<uint32_t> (EndpointHandles::mx7C);
            if (endpointName == "mx7D")       return static_cast<uint32_t> (EndpointHandles::mx7D);
            if (endpointName == "mx7E")       return static_cast<uint32_t> (EndpointHandles::mx7E);
            if (endpointName == "mx7F")       return static_cast<uint32_t> (EndpointHandles::mx7F);
            if (endpointName == "mx80")       return static_cast<uint32_t> (EndpointHandles::mx80);
            if (endpointName == "mx81")       return static_cast<uint32_t> (EndpointHandles::mx81);
            if (endpointName == "mx82")       return static_cast<uint32_t> (EndpointHandles::mx82);
            if (endpointName == "mx83")       return static_cast<uint32_t> (EndpointHandles::mx83);
            if (endpointName == "mx84")       return static_cast<uint32_t> (EndpointHandles::mx84);
            if (endpointName == "mx85")       return static_cast<uint32_t> (EndpointHandles::mx85);
            if (endpointName == "mx86")       return static_cast<uint32_t> (EndpointHandles::mx86);
            if (endpointName == "mx87")       return static_cast<uint32_t> (EndpointHandles::mx87);
            if (endpointName == "mx88")       return static_cast<uint32_t> (EndpointHandles::mx88);
            if (endpointName == "mx89")       return static_cast<uint32_t> (EndpointHandles::mx89);
            if (endpointName == "mx8A")       return static_cast<uint32_t> (EndpointHandles::mx8A);
            if (endpointName == "mx8B")       return static_cast<uint32_t> (EndpointHandles::mx8B);
            if (endpointName == "mx8C")       return static_cast<uint32_t> (EndpointHandles::mx8C);
            if (endpointName == "mx8D")       return static_cast<uint32_t> (EndpointHandles::mx8D);
            if (endpointName == "mx8E")       return static_cast<uint32_t> (EndpointHandles::mx8E);
            if (endpointName == "mx8F")       return static_cast<uint32_t> (EndpointHandles::mx8F);
            if (endpointName == "mx90")       return static_cast<uint32_t> (EndpointHandles::mx90);
            if (endpointName == "mx91")       return static_cast<uint32_t> (EndpointHandles::mx91);
            if (endpointName == "mx92")       return static_cast<uint32_t> (EndpointHandles::mx92);
            if (endpointName == "mx93")       return static_cast<uint32_t> (EndpointHandles::mx93);
            if (endpointName == "mx94")       return static_cast<uint32_t> (EndpointHandles::mx94);
            if (endpointName == "mx95")       return static_cast<uint32_t> (EndpointHandles::mx95);
            if (endpointName == "mx96")       return static_cast<uint32_t> (EndpointHandles::mx96);
            if (endpointName == "mx97")       return static_cast<uint32_t> (EndpointHandles::mx97);
            if (endpointName == "mx98")       return static_cast<uint32_t> (EndpointHandles::mx98);
            if (endpointName == "mx99")       return static_cast<uint32_t> (EndpointHandles::mx99);
            if (endpointName == "mx9A")       return static_cast<uint32_t> (EndpointHandles::mx9A);
            if (endpointName == "mx9B")       return static_cast<uint32_t> (EndpointHandles::mx9B);
            if (endpointName == "mx9C")       return static_cast<uint32_t> (EndpointHandles::mx9C);
            if (endpointName == "mx9D")       return static_cast<uint32_t> (EndpointHandles::mx9D);
            if (endpointName == "mx9E")       return static_cast<uint32_t> (EndpointHandles::mx9E);
            if (endpointName == "mx9F")       return static_cast<uint32_t> (EndpointHandles::mx9F);
            if (endpointName == "joyX")       return static_cast<uint32_t> (EndpointHandles::joyX);
            if (endpointName == "joyY")       return static_cast<uint32_t> (EndpointHandles::joyY);
            if (endpointName == "volume")     return static_cast<uint32_t> (EndpointHandles::volume);
            if (endpointName == "tune")       return static_cast<uint32_t> (EndpointHandles::tune);
            if (endpointName == "audioOut")   return static_cast<uint32_t> (EndpointHandles::audioOut);
            if (endpointName == "noteOut")    return static_cast<uint32_t> (EndpointHandles::noteOut);
            return 0;
        }

        static constexpr EndpointInfo inputEndpoints[] =
        {
            { 1,    "midiIn",     EndpointType::event },
            { 2,    "o1Freq",     EndpointType::event },
            { 3,    "o1Range",    EndpointType::event },
            { 4,    "o1Sine",     EndpointType::event },
            { 5,    "o1Saw",      EndpointType::event },
            { 6,    "o2Freq",     EndpointType::event },
            { 7,    "o2Range",    EndpointType::event },
            { 8,    "o2Shape",    EndpointType::event },
            { 9,    "o2Pw",       EndpointType::event },
            { 10,   "o2Level",    EndpointType::event },
            { 11,   "o3Freq",     EndpointType::event },
            { 12,   "o3Range",    EndpointType::event },
            { 13,   "o3Shape",    EndpointType::event },
            { 14,   "o3Pw",       EndpointType::event },
            { 15,   "o3Level",    EndpointType::event },
            { 16,   "drift",      EndpointType::event },
            { 17,   "noise",      EndpointType::event },
            { 18,   "cutoff",     EndpointType::event },
            { 19,   "reso",       EndpointType::event },
            { 20,   "fKeyTrack",  EndpointType::event },
            { 21,   "trapA",      EndpointType::event },
            { 22,   "trapOn",     EndpointType::event },
            { 23,   "trapD",      EndpointType::event },
            { 24,   "trapOff",    EndpointType::event },
            { 25,   "reverb",     EndpointType::event },
            { 26,   "mx00",       EndpointType::event },
            { 27,   "mx01",       EndpointType::event },
            { 28,   "mx02",       EndpointType::event },
            { 29,   "mx03",       EndpointType::event },
            { 30,   "mx04",       EndpointType::event },
            { 31,   "mx05",       EndpointType::event },
            { 32,   "mx06",       EndpointType::event },
            { 33,   "mx07",       EndpointType::event },
            { 34,   "mx08",       EndpointType::event },
            { 35,   "mx09",       EndpointType::event },
            { 36,   "mx0A",       EndpointType::event },
            { 37,   "mx0B",       EndpointType::event },
            { 38,   "mx0C",       EndpointType::event },
            { 39,   "mx0D",       EndpointType::event },
            { 40,   "mx0E",       EndpointType::event },
            { 41,   "mx0F",       EndpointType::event },
            { 42,   "mx10",       EndpointType::event },
            { 43,   "mx11",       EndpointType::event },
            { 44,   "mx12",       EndpointType::event },
            { 45,   "mx13",       EndpointType::event },
            { 46,   "mx14",       EndpointType::event },
            { 47,   "mx15",       EndpointType::event },
            { 48,   "mx16",       EndpointType::event },
            { 49,   "mx17",       EndpointType::event },
            { 50,   "mx18",       EndpointType::event },
            { 51,   "mx19",       EndpointType::event },
            { 52,   "mx1A",       EndpointType::event },
            { 53,   "mx1B",       EndpointType::event },
            { 54,   "mx1C",       EndpointType::event },
            { 55,   "mx1D",       EndpointType::event },
            { 56,   "mx1E",       EndpointType::event },
            { 57,   "mx1F",       EndpointType::event },
            { 58,   "mx20",       EndpointType::event },
            { 59,   "mx21",       EndpointType::event },
            { 60,   "mx22",       EndpointType::event },
            { 61,   "mx23",       EndpointType::event },
            { 62,   "mx24",       EndpointType::event },
            { 63,   "mx25",       EndpointType::event },
            { 64,   "mx26",       EndpointType::event },
            { 65,   "mx27",       EndpointType::event },
            { 66,   "mx28",       EndpointType::event },
            { 67,   "mx29",       EndpointType::event },
            { 68,   "mx2A",       EndpointType::event },
            { 69,   "mx2B",       EndpointType::event },
            { 70,   "mx2C",       EndpointType::event },
            { 71,   "mx2D",       EndpointType::event },
            { 72,   "mx2E",       EndpointType::event },
            { 73,   "mx2F",       EndpointType::event },
            { 74,   "mx30",       EndpointType::event },
            { 75,   "mx31",       EndpointType::event },
            { 76,   "mx32",       EndpointType::event },
            { 77,   "mx33",       EndpointType::event },
            { 78,   "mx34",       EndpointType::event },
            { 79,   "mx35",       EndpointType::event },
            { 80,   "mx36",       EndpointType::event },
            { 81,   "mx37",       EndpointType::event },
            { 82,   "mx38",       EndpointType::event },
            { 83,   "mx39",       EndpointType::event },
            { 84,   "mx3A",       EndpointType::event },
            { 85,   "mx3B",       EndpointType::event },
            { 86,   "mx3C",       EndpointType::event },
            { 87,   "mx3D",       EndpointType::event },
            { 88,   "mx3E",       EndpointType::event },
            { 89,   "mx3F",       EndpointType::event },
            { 90,   "mx40",       EndpointType::event },
            { 91,   "mx41",       EndpointType::event },
            { 92,   "mx42",       EndpointType::event },
            { 93,   "mx43",       EndpointType::event },
            { 94,   "mx44",       EndpointType::event },
            { 95,   "mx45",       EndpointType::event },
            { 96,   "mx46",       EndpointType::event },
            { 97,   "mx47",       EndpointType::event },
            { 98,   "mx48",       EndpointType::event },
            { 99,   "mx49",       EndpointType::event },
            { 100,  "mx4A",       EndpointType::event },
            { 101,  "mx4B",       EndpointType::event },
            { 102,  "mx4C",       EndpointType::event },
            { 103,  "mx4D",       EndpointType::event },
            { 104,  "mx4E",       EndpointType::event },
            { 105,  "mx4F",       EndpointType::event },
            { 106,  "mx50",       EndpointType::event },
            { 107,  "mx51",       EndpointType::event },
            { 108,  "mx52",       EndpointType::event },
            { 109,  "mx53",       EndpointType::event },
            { 110,  "mx54",       EndpointType::event },
            { 111,  "mx55",       EndpointType::event },
            { 112,  "mx56",       EndpointType::event },
            { 113,  "mx57",       EndpointType::event },
            { 114,  "mx58",       EndpointType::event },
            { 115,  "mx59",       EndpointType::event },
            { 116,  "mx5A",       EndpointType::event },
            { 117,  "mx5B",       EndpointType::event },
            { 118,  "mx5C",       EndpointType::event },
            { 119,  "mx5D",       EndpointType::event },
            { 120,  "mx5E",       EndpointType::event },
            { 121,  "mx5F",       EndpointType::event },
            { 122,  "mx60",       EndpointType::event },
            { 123,  "mx61",       EndpointType::event },
            { 124,  "mx62",       EndpointType::event },
            { 125,  "mx63",       EndpointType::event },
            { 126,  "mx64",       EndpointType::event },
            { 127,  "mx65",       EndpointType::event },
            { 128,  "mx66",       EndpointType::event },
            { 129,  "mx67",       EndpointType::event },
            { 130,  "mx68",       EndpointType::event },
            { 131,  "mx69",       EndpointType::event },
            { 132,  "mx6A",       EndpointType::event },
            { 133,  "mx6B",       EndpointType::event },
            { 134,  "mx6C",       EndpointType::event },
            { 135,  "mx6D",       EndpointType::event },
            { 136,  "mx6E",       EndpointType::event },
            { 137,  "mx6F",       EndpointType::event },
            { 138,  "mx70",       EndpointType::event },
            { 139,  "mx71",       EndpointType::event },
            { 140,  "mx72",       EndpointType::event },
            { 141,  "mx73",       EndpointType::event },
            { 142,  "mx74",       EndpointType::event },
            { 143,  "mx75",       EndpointType::event },
            { 144,  "mx76",       EndpointType::event },
            { 145,  "mx77",       EndpointType::event },
            { 146,  "mx78",       EndpointType::event },
            { 147,  "mx79",       EndpointType::event },
            { 148,  "mx7A",       EndpointType::event },
            { 149,  "mx7B",       EndpointType::event },
            { 150,  "mx7C",       EndpointType::event },
            { 151,  "mx7D",       EndpointType::event },
            { 152,  "mx7E",       EndpointType::event },
            { 153,  "mx7F",       EndpointType::event },
            { 154,  "mx80",       EndpointType::event },
            { 155,  "mx81",       EndpointType::event },
            { 156,  "mx82",       EndpointType::event },
            { 157,  "mx83",       EndpointType::event },
            { 158,  "mx84",       EndpointType::event },
            { 159,  "mx85",       EndpointType::event },
            { 160,  "mx86",       EndpointType::event },
            { 161,  "mx87",       EndpointType::event },
            { 162,  "mx88",       EndpointType::event },
            { 163,  "mx89",       EndpointType::event },
            { 164,  "mx8A",       EndpointType::event },
            { 165,  "mx8B",       EndpointType::event },
            { 166,  "mx8C",       EndpointType::event },
            { 167,  "mx8D",       EndpointType::event },
            { 168,  "mx8E",       EndpointType::event },
            { 169,  "mx8F",       EndpointType::event },
            { 170,  "mx90",       EndpointType::event },
            { 171,  "mx91",       EndpointType::event },
            { 172,  "mx92",       EndpointType::event },
            { 173,  "mx93",       EndpointType::event },
            { 174,  "mx94",       EndpointType::event },
            { 175,  "mx95",       EndpointType::event },
            { 176,  "mx96",       EndpointType::event },
            { 177,  "mx97",       EndpointType::event },
            { 178,  "mx98",       EndpointType::event },
            { 179,  "mx99",       EndpointType::event },
            { 180,  "mx9A",       EndpointType::event },
            { 181,  "mx9B",       EndpointType::event },
            { 182,  "mx9C",       EndpointType::event },
            { 183,  "mx9D",       EndpointType::event },
            { 184,  "mx9E",       EndpointType::event },
            { 185,  "mx9F",       EndpointType::event },
            { 186,  "joyX",       EndpointType::event },
            { 187,  "joyY",       EndpointType::event },
            { 188,  "volume",     EndpointType::event },
            { 189,  "tune",       EndpointType::event }
        };

        static constexpr EndpointInfo outputEndpoints[] =
        {
            { 190,  "audioOut",  EndpointType::stream },
            { 191,  "noteOut",   EndpointType::event  }
        };

        //==============================================================================
        static constexpr uint32_t numAudioInputChannels  = 0;
        static constexpr uint32_t numAudioOutputChannels = 2;

        static constexpr std::array outputAudioStreams
        {
            outputEndpoints[0]
        };

        static constexpr std::array outputEvents
        {
            outputEndpoints[1]
        };

        static constexpr std::array<EndpointInfo, 0> outputMIDIEvents {};

        static constexpr std::array<EndpointInfo, 0> inputAudioStreams {};

        static constexpr std::array inputEvents
        {
            inputEndpoints[0],
            inputEndpoints[1],
            inputEndpoints[2],
            inputEndpoints[3],
            inputEndpoints[4],
            inputEndpoints[5],
            inputEndpoints[6],
            inputEndpoints[7],
            inputEndpoints[8],
            inputEndpoints[9],
            inputEndpoints[10],
            inputEndpoints[11],
            inputEndpoints[12],
            inputEndpoints[13],
            inputEndpoints[14],
            inputEndpoints[15],
            inputEndpoints[16],
            inputEndpoints[17],
            inputEndpoints[18],
            inputEndpoints[19],
            inputEndpoints[20],
            inputEndpoints[21],
            inputEndpoints[22],
            inputEndpoints[23],
            inputEndpoints[24],
            inputEndpoints[25],
            inputEndpoints[26],
            inputEndpoints[27],
            inputEndpoints[28],
            inputEndpoints[29],
            inputEndpoints[30],
            inputEndpoints[31],
            inputEndpoints[32],
            inputEndpoints[33],
            inputEndpoints[34],
            inputEndpoints[35],
            inputEndpoints[36],
            inputEndpoints[37],
            inputEndpoints[38],
            inputEndpoints[39],
            inputEndpoints[40],
            inputEndpoints[41],
            inputEndpoints[42],
            inputEndpoints[43],
            inputEndpoints[44],
            inputEndpoints[45],
            inputEndpoints[46],
            inputEndpoints[47],
            inputEndpoints[48],
            inputEndpoints[49],
            inputEndpoints[50],
            inputEndpoints[51],
            inputEndpoints[52],
            inputEndpoints[53],
            inputEndpoints[54],
            inputEndpoints[55],
            inputEndpoints[56],
            inputEndpoints[57],
            inputEndpoints[58],
            inputEndpoints[59],
            inputEndpoints[60],
            inputEndpoints[61],
            inputEndpoints[62],
            inputEndpoints[63],
            inputEndpoints[64],
            inputEndpoints[65],
            inputEndpoints[66],
            inputEndpoints[67],
            inputEndpoints[68],
            inputEndpoints[69],
            inputEndpoints[70],
            inputEndpoints[71],
            inputEndpoints[72],
            inputEndpoints[73],
            inputEndpoints[74],
            inputEndpoints[75],
            inputEndpoints[76],
            inputEndpoints[77],
            inputEndpoints[78],
            inputEndpoints[79],
            inputEndpoints[80],
            inputEndpoints[81],
            inputEndpoints[82],
            inputEndpoints[83],
            inputEndpoints[84],
            inputEndpoints[85],
            inputEndpoints[86],
            inputEndpoints[87],
            inputEndpoints[88],
            inputEndpoints[89],
            inputEndpoints[90],
            inputEndpoints[91],
            inputEndpoints[92],
            inputEndpoints[93],
            inputEndpoints[94],
            inputEndpoints[95],
            inputEndpoints[96],
            inputEndpoints[97],
            inputEndpoints[98],
            inputEndpoints[99],
            inputEndpoints[100],
            inputEndpoints[101],
            inputEndpoints[102],
            inputEndpoints[103],
            inputEndpoints[104],
            inputEndpoints[105],
            inputEndpoints[106],
            inputEndpoints[107],
            inputEndpoints[108],
            inputEndpoints[109],
            inputEndpoints[110],
            inputEndpoints[111],
            inputEndpoints[112],
            inputEndpoints[113],
            inputEndpoints[114],
            inputEndpoints[115],
            inputEndpoints[116],
            inputEndpoints[117],
            inputEndpoints[118],
            inputEndpoints[119],
            inputEndpoints[120],
            inputEndpoints[121],
            inputEndpoints[122],
            inputEndpoints[123],
            inputEndpoints[124],
            inputEndpoints[125],
            inputEndpoints[126],
            inputEndpoints[127],
            inputEndpoints[128],
            inputEndpoints[129],
            inputEndpoints[130],
            inputEndpoints[131],
            inputEndpoints[132],
            inputEndpoints[133],
            inputEndpoints[134],
            inputEndpoints[135],
            inputEndpoints[136],
            inputEndpoints[137],
            inputEndpoints[138],
            inputEndpoints[139],
            inputEndpoints[140],
            inputEndpoints[141],
            inputEndpoints[142],
            inputEndpoints[143],
            inputEndpoints[144],
            inputEndpoints[145],
            inputEndpoints[146],
            inputEndpoints[147],
            inputEndpoints[148],
            inputEndpoints[149],
            inputEndpoints[150],
            inputEndpoints[151],
            inputEndpoints[152],
            inputEndpoints[153],
            inputEndpoints[154],
            inputEndpoints[155],
            inputEndpoints[156],
            inputEndpoints[157],
            inputEndpoints[158],
            inputEndpoints[159],
            inputEndpoints[160],
            inputEndpoints[161],
            inputEndpoints[162],
            inputEndpoints[163],
            inputEndpoints[164],
            inputEndpoints[165],
            inputEndpoints[166],
            inputEndpoints[167],
            inputEndpoints[168],
            inputEndpoints[169],
            inputEndpoints[170],
            inputEndpoints[171],
            inputEndpoints[172],
            inputEndpoints[173],
            inputEndpoints[174],
            inputEndpoints[175],
            inputEndpoints[176],
            inputEndpoints[177],
            inputEndpoints[178],
            inputEndpoints[179],
            inputEndpoints[180],
            inputEndpoints[181],
            inputEndpoints[182],
            inputEndpoints[183],
            inputEndpoints[184],
            inputEndpoints[185],
            inputEndpoints[186],
            inputEndpoints[187],
            inputEndpoints[188]
        };

        static constexpr std::array inputMIDIEvents
        {
            inputEndpoints[0]
        };

        static constexpr std::array inputParameters
        {
            inputEndpoints[1],
            inputEndpoints[2],
            inputEndpoints[3],
            inputEndpoints[4],
            inputEndpoints[5],
            inputEndpoints[6],
            inputEndpoints[7],
            inputEndpoints[8],
            inputEndpoints[9],
            inputEndpoints[10],
            inputEndpoints[11],
            inputEndpoints[12],
            inputEndpoints[13],
            inputEndpoints[14],
            inputEndpoints[15],
            inputEndpoints[16],
            inputEndpoints[17],
            inputEndpoints[18],
            inputEndpoints[19],
            inputEndpoints[20],
            inputEndpoints[21],
            inputEndpoints[22],
            inputEndpoints[23],
            inputEndpoints[24],
            inputEndpoints[25],
            inputEndpoints[26],
            inputEndpoints[27],
            inputEndpoints[28],
            inputEndpoints[29],
            inputEndpoints[30],
            inputEndpoints[31],
            inputEndpoints[32],
            inputEndpoints[33],
            inputEndpoints[34],
            inputEndpoints[35],
            inputEndpoints[36],
            inputEndpoints[37],
            inputEndpoints[38],
            inputEndpoints[39],
            inputEndpoints[40],
            inputEndpoints[41],
            inputEndpoints[42],
            inputEndpoints[43],
            inputEndpoints[44],
            inputEndpoints[45],
            inputEndpoints[46],
            inputEndpoints[47],
            inputEndpoints[48],
            inputEndpoints[49],
            inputEndpoints[50],
            inputEndpoints[51],
            inputEndpoints[52],
            inputEndpoints[53],
            inputEndpoints[54],
            inputEndpoints[55],
            inputEndpoints[56],
            inputEndpoints[57],
            inputEndpoints[58],
            inputEndpoints[59],
            inputEndpoints[60],
            inputEndpoints[61],
            inputEndpoints[62],
            inputEndpoints[63],
            inputEndpoints[64],
            inputEndpoints[65],
            inputEndpoints[66],
            inputEndpoints[67],
            inputEndpoints[68],
            inputEndpoints[69],
            inputEndpoints[70],
            inputEndpoints[71],
            inputEndpoints[72],
            inputEndpoints[73],
            inputEndpoints[74],
            inputEndpoints[75],
            inputEndpoints[76],
            inputEndpoints[77],
            inputEndpoints[78],
            inputEndpoints[79],
            inputEndpoints[80],
            inputEndpoints[81],
            inputEndpoints[82],
            inputEndpoints[83],
            inputEndpoints[84],
            inputEndpoints[85],
            inputEndpoints[86],
            inputEndpoints[87],
            inputEndpoints[88],
            inputEndpoints[89],
            inputEndpoints[90],
            inputEndpoints[91],
            inputEndpoints[92],
            inputEndpoints[93],
            inputEndpoints[94],
            inputEndpoints[95],
            inputEndpoints[96],
            inputEndpoints[97],
            inputEndpoints[98],
            inputEndpoints[99],
            inputEndpoints[100],
            inputEndpoints[101],
            inputEndpoints[102],
            inputEndpoints[103],
            inputEndpoints[104],
            inputEndpoints[105],
            inputEndpoints[106],
            inputEndpoints[107],
            inputEndpoints[108],
            inputEndpoints[109],
            inputEndpoints[110],
            inputEndpoints[111],
            inputEndpoints[112],
            inputEndpoints[113],
            inputEndpoints[114],
            inputEndpoints[115],
            inputEndpoints[116],
            inputEndpoints[117],
            inputEndpoints[118],
            inputEndpoints[119],
            inputEndpoints[120],
            inputEndpoints[121],
            inputEndpoints[122],
            inputEndpoints[123],
            inputEndpoints[124],
            inputEndpoints[125],
            inputEndpoints[126],
            inputEndpoints[127],
            inputEndpoints[128],
            inputEndpoints[129],
            inputEndpoints[130],
            inputEndpoints[131],
            inputEndpoints[132],
            inputEndpoints[133],
            inputEndpoints[134],
            inputEndpoints[135],
            inputEndpoints[136],
            inputEndpoints[137],
            inputEndpoints[138],
            inputEndpoints[139],
            inputEndpoints[140],
            inputEndpoints[141],
            inputEndpoints[142],
            inputEndpoints[143],
            inputEndpoints[144],
            inputEndpoints[145],
            inputEndpoints[146],
            inputEndpoints[147],
            inputEndpoints[148],
            inputEndpoints[149],
            inputEndpoints[150],
            inputEndpoints[151],
            inputEndpoints[152],
            inputEndpoints[153],
            inputEndpoints[154],
            inputEndpoints[155],
            inputEndpoints[156],
            inputEndpoints[157],
            inputEndpoints[158],
            inputEndpoints[159],
            inputEndpoints[160],
            inputEndpoints[161],
            inputEndpoints[162],
            inputEndpoints[163],
            inputEndpoints[164],
            inputEndpoints[165],
            inputEndpoints[166],
            inputEndpoints[167],
            inputEndpoints[168],
            inputEndpoints[169],
            inputEndpoints[170],
            inputEndpoints[171],
            inputEndpoints[172],
            inputEndpoints[173],
            inputEndpoints[174],
            inputEndpoints[175],
            inputEndpoints[176],
            inputEndpoints[177],
            inputEndpoints[178],
            inputEndpoints[179],
            inputEndpoints[180],
            inputEndpoints[181],
            inputEndpoints[182],
            inputEndpoints[183],
            inputEndpoints[184],
            inputEndpoints[185],
            inputEndpoints[186],
            inputEndpoints[187],
            inputEndpoints[188]
        };

        static constexpr const char programDetailsJSON[] = {
                123,10,32,32,34,109,97,105,110,80,114,111,99,101,115,115,111,114,34,58,32,34,74,87,86,67,83,34,44,10,32,32,34,105,110,112,117,116,115,34,58,32,91,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,
                111,105,110,116,73,68,34,58,32,34,109,105,100,105,73,110,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,
                100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,111,98,106,101,99,116,34,44,10,32,32,32,32,32,32,32,32,34,99,108,97,115,115,34,58,32,34,77,101,
                115,115,97,103,101,34,44,10,32,32,32,32,32,32,32,32,34,109,101,109,98,101,114,115,34,58,32,123,10,32,32,32,32,32,32,32,32,32,32,34,109,101,115,115,97,103,101,34,58,32,123,10,32,32,32,32,32,32,32,
                32,32,32,32,32,34,116,121,112,101,34,58,32,34,105,110,116,51,50,34,10,32,32,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,
                110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,73,68,73,32,105,110,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,
                111,115,101,34,58,32,34,109,105,100,105,32,105,110,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,111,49,70,114,101,113,34,
                44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,
                32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,
                32,34,110,97,109,101,34,58,32,34,79,83,67,49,32,70,114,101,113,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,
                32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,52,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,
                32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,111,49,82,97,110,103,101,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,
                121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,
                50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,79,83,67,49,32,82,97,110,103,
                101,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,53,10,
                32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,
                110,100,112,111,105,110,116,73,68,34,58,32,34,111,49,83,105,110,101,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,
                32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,
                110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,79,83,67,49,32,83,105,110,101,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,
                46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,51,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,
                111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,111,49,83,97,119,34,
                44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,
                32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,
                32,34,110,97,109,101,34,58,32,34,79,83,67,49,32,83,97,119,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,
                32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,55,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,
                125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,111,50,70,114,101,113,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,
                101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,
                10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,79,83,67,50,32,70,114,101,113,34,44,
                10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,52,50,10,32,32,
                32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,73,68,34,58,32,34,111,50,82,97,110,103,101,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,
                32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,
                111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,79,83,67,50,32,82,97,110,103,101,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,
                44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,53,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,
                115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,111,50,83,104,97,112,101,
                34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,
                32,32,34,110,97,109,101,34,58,32,34,79,83,67,50,32,83,104,97,112,101,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,
                10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,54,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,
                32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,111,50,80,119,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,
                112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,
                34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,79,83,67,50,32,80,87,34,44,10,32,
                32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,52,53,10,32,32,32,32,
                32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,
                111,105,110,116,73,68,34,58,32,34,111,50,76,101,118,101,108,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,
                34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,
                111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,79,83,67,50,32,76,101,118,101,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,
                48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,54,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,
                111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,111,51,70,114,101,
                113,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,79,83,67,51,32,70,114,101,113,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,
                44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,51,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,
                10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,111,51,82,97,110,103,101,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,
                110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,
                97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,79,83,67,51,32,82,
                97,110,103,101,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,
                48,46,49,56,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,
                32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,111,51,83,104,97,112,101,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,
                34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,
                32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,79,83,67,51,32,83,104,97,112,101,34,44,10,32,32,32,32,32,32,32,32,34,109,
                105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,
                32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,
                34,111,51,80,119,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,
                123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,
                32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,79,83,67,51,32,80,87,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,
                49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,53,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,
                34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,111,51,76,101,118,101,108,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,
                105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,
                111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,79,83,67,51,32,
                76,101,118,101,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,
                32,48,46,52,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,
                32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,100,114,105,102,116,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,
                44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,
                32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,68,114,105,102,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,
                48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,50,56,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,
                114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,110,111,105,
                115,101,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,
                32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,
                32,32,32,32,32,34,110,97,109,101,34,58,32,34,78,111,105,115,101,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,
                32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,51,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,
                32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,99,117,116,111,102,102,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,
                121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,
                50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,67,117,116,111,102,102,34,44,
                10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,53,56,10,32,32,
                32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,73,68,34,58,32,34,114,101,115,111,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,
                97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,
                97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,82,101,115,111,110,97,110,99,101,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,
                32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,52,50,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,
                101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,102,75,101,121,84,114,97,99,
                107,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,75,101,121,32,84,114,97,99,107,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,
                44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,52,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,
                10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,116,114,97,112,65,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,
                84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,
                51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,84,114,97,112,32,65,116,116,
                97,99,107,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,
                48,54,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,
                32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,116,114,97,112,79,110,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,
                32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,
                32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,84,114,97,112,32,79,110,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,
                48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,51,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,
                112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,116,114,97,112,
                68,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,
                32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,
                32,32,32,34,110,97,109,101,34,58,32,34,84,114,97,112,32,68,101,99,97,121,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,
                44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,52,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,
                10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,116,114,97,112,79,102,102,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,
                110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,
                97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,84,114,97,112,32,79,
                102,102,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,49,10,
                32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,
                110,100,112,111,105,110,116,73,68,34,58,32,34,114,101,118,101,114,98,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,
                32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,
                110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,82,101,118,101,114,98,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,
                10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,51,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,
                101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,48,48,34,44,10,32,
                32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,
                34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,
                97,109,101,34,58,32,34,77,32,79,49,62,79,49,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,
                32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,
                44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,48,49,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,
                34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,
                32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,49,62,79,50,99,118,34,44,10,32,32,32,32,
                32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,
                10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,
                116,73,68,34,58,32,34,109,120,48,50,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,
                112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,
                34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,49,62,79,51,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,
                34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,
                97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,48,51,34,44,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,
                34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,
                32,79,49,62,82,105,110,103,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,
                116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,
                32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,48,52,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,
                34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,
                32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,49,62,70,105,108,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,
                110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,49,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                48,53,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,49,62,70,105,108,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,
                32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,
                114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,48,54,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,
                116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,
                116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,49,62,82,101,
                118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,
                32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,
                110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,48,55,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,
                34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,
                111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,49,62,79,117,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,
                32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,
                34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,48,56,34,44,10,32,32,32,
                32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,
                121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,
                101,34,58,32,34,77,32,79,49,62,111,50,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,
                32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,
                32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,48,57,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,
                118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,
                125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,49,62,111,51,80,87,77,34,44,10,32,32,32,32,32,
                32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,
                32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,
                73,68,34,58,32,34,109,120,48,65,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,
                101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,
                58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,49,62,82,101,115,111,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,
                32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,
                114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,48,66,34,44,10,32,32,32,32,32,32,34,101,110,
                100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,
                32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,
                77,32,79,49,62,67,117,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,
                105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,
                10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,48,67,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,
                34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,
                32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,49,62,82,101,118,83,110,100,34,44,10,32,32,32,32,32,32,32,32,34,
                109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,
                32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,
                32,34,109,120,48,68,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,
                32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,
                10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,49,62,79,117,116,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,
                97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,
                101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,48,69,34,44,10,32,32,32,32,32,32,34,101,110,100,112,
                111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,
                108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,49,
                62,78,122,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,
                58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,
                32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,48,70,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,
                10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,
                32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,49,62,79,117,116,66,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,
                34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                49,48,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,50,62,79,49,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,
                10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,
                32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,49,49,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,
                112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,
                34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,50,62,79,50,99,118,34,
                44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,
                32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,73,68,34,58,32,34,109,120,49,50,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,
                97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,
                97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,50,62,79,51,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,
                32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,
                58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,49,51,34,44,10,32,32,32,32,
                32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,
                121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,
                101,34,58,32,34,77,32,79,50,62,82,105,110,103,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,
                32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,
                32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,49,52,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,
                118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,
                125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,50,62,70,105,108,116,34,44,10,32,32,32,32,32,32,
                32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,55,10,32,32,32,32,32,32,125,44,10,32,
                32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,
                68,34,58,32,34,109,120,49,53,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,
                34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,
                32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,50,62,70,105,108,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,
                34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,
                97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,49,54,34,44,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,
                34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,
                32,79,50,62,82,101,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,
                34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,
                32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,49,55,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,
                44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,
                32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,50,62,79,117,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,
                34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                49,56,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,50,62,111,50,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,
                44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,
                10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,49,57,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,
                121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,
                50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,50,62,111,51,80,87,
                77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,
                32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,
                110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,49,65,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,
                34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,
                111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,50,62,82,101,115,111,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,
                48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,
                111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,49,66,34,44,
                10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,
                32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,
                34,110,97,109,101,34,58,32,34,77,32,79,50,62,67,117,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,
                32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,
                32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,49,67,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,
                34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,
                32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,50,62,82,101,118,83,110,100,34,
                44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,
                32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,73,68,34,58,32,34,109,120,49,68,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,
                97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,
                97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,50,62,79,117,116,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,
                10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,
                101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,49,69,34,44,10,32,
                32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,
                34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,
                97,109,101,34,58,32,34,77,32,79,50,62,78,122,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,
                32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,
                44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,49,70,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,
                34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,
                32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,50,62,79,117,116,66,34,44,10,32,32,32,32,
                32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,
                10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,
                116,73,68,34,58,32,34,109,120,50,48,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,
                112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,
                34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,79,49,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,
                34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,
                97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,50,49,34,44,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,
                34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,
                32,79,51,62,79,50,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,
                34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,
                32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,50,50,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,
                44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,
                32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,79,51,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,
                34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                50,51,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,82,105,110,103,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,
                44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,
                10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,50,52,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,
                121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,
                50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,70,105,108,116,
                34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,
                32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,
                100,112,111,105,110,116,73,68,34,58,32,34,109,120,50,53,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,
                100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,
                116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,70,105,108,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,
                44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,
                115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,50,54,34,44,10,
                32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,
                32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,
                110,97,109,101,34,58,32,34,77,32,79,51,62,82,101,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,
                32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,
                44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,50,55,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,
                34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,
                32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,79,117,116,34,44,10,32,32,32,32,32,
                32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,
                32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,
                73,68,34,58,32,34,109,120,50,56,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,
                101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,
                58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,111,50,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,
                34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,
                97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,50,57,34,44,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,
                34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,
                32,79,51,62,111,51,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,
                116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,
                32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,50,65,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,
                34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,
                32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,82,101,115,111,67,86,34,44,10,32,32,32,32,32,32,32,32,34,
                109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,
                32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,
                32,34,109,120,50,66,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,
                32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,
                10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,67,117,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,
                120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,
                116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,50,67,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,
                105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,
                111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,
                82,101,118,83,110,100,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,
                58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,
                32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,50,68,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,
                10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,
                32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,79,117,116,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,
                105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,
                32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,
                34,109,120,50,69,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,
                123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,
                32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,78,122,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,
                34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,
                101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,50,70,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,
                110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,
                97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,79,51,62,79,
                117,116,66,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,
                46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,
                32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,51,48,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,
                32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,
                97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,79,49,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,
                48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,
                112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,51,49,
                34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,
                32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,79,50,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,
                32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,
                32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,51,50,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,
                34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,
                32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,79,51,99,118,34,44,10,32,
                32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,
                32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,
                105,110,116,73,68,34,58,32,34,109,120,51,51,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,
                97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,
                105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,82,105,110,103,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,
                32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,
                32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,51,52,34,44,10,32,32,32,32,32,
                32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,
                112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,
                34,58,32,34,77,32,78,122,62,70,105,108,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,
                34,105,110,105,116,34,58,32,48,46,50,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,
                32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,51,53,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,
                118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,
                125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,70,105,108,116,67,86,34,44,10,32,32,32,
                32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,
                44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,
                116,73,68,34,58,32,34,109,120,51,54,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,
                112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,
                34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,82,101,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,
                109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,
                109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,51,55,34,44,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,
                34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,
                32,78,122,62,79,117,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,
                34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,
                32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,51,56,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,
                44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,
                32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,111,50,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,
                110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,
                34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,
                109,120,51,57,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,
                10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,
                32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,111,51,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,
                58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,
                101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,51,65,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,
                110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,
                97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,82,
                101,115,111,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,
                32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,
                32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,51,66,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,
                32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,
                32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,67,117,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,
                34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                51,67,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,82,101,118,83,110,100,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,
                32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,
                114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,51,68,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,
                116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,
                116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,79,117,
                116,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,
                48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,
                32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,51,69,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,
                32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,
                34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,78,122,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,
                58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                51,70,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,78,122,62,79,117,116,66,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,
                44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,
                10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,52,48,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,
                121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,
                50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,79,49,
                99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,
                10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,
                101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,52,49,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,
                32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,
                110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,79,50,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,
                48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,
                112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,52,50,
                34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,
                32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,79,51,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,
                44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,
                10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,52,51,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,
                121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,
                50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,82,105,
                110,103,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,
                48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,
                34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,52,52,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,
                32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,
                110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,70,105,108,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,
                58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                52,53,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,70,105,108,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,
                34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,
                101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,52,54,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,
                110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,
                97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,
                62,82,101,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,
                48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,
                32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,52,55,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,
                32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,
                34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,79,117,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,
                34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                52,56,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,111,50,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,
                58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,
                101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,52,57,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,
                110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,
                97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,
                62,111,51,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,
                32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,
                32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,52,65,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,
                32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,
                32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,82,101,115,111,67,86,34,44,10,32,32,32,32,32,32,32,32,34,
                109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,
                32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,
                32,34,109,120,52,66,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,
                32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,
                10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,67,117,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,
                34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,
                97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,52,67,34,44,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,
                34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,
                32,82,105,110,103,62,82,101,118,83,110,100,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,
                34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,
                32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,52,68,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,
                118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,
                125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,79,117,116,76,118,108,34,44,10,
                32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,
                32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,
                111,105,110,116,73,68,34,58,32,34,109,120,52,69,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,
                116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,
                116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,78,122,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,
                44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,
                115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,52,70,34,44,10,
                32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,
                32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,
                110,97,109,101,34,58,32,34,77,32,82,105,110,103,62,79,117,116,66,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,
                32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,
                32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,48,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,
                34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,
                32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,79,49,99,118,34,
                44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,
                32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,73,68,34,58,32,34,109,120,53,49,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,
                97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,
                97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,79,50,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,
                10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,
                101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,50,34,44,10,32,
                32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,
                34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,
                97,109,101,34,58,32,34,77,32,70,105,108,116,62,79,51,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,
                32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,
                32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,51,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,
                34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,
                32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,82,105,110,103,34,
                44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,
                32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,73,68,34,58,32,34,109,120,53,52,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,
                97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,
                97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,70,105,108,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,
                44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,
                115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,53,34,44,10,
                32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,
                32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,
                110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,70,105,108,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,
                44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,
                10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,54,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,
                121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,
                50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,82,101,
                118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,52,10,
                32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,
                110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,55,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,
                34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,
                111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,79,117,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,
                48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,49,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,
                101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,56,34,44,10,32,
                32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,
                34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,
                97,109,101,34,58,32,34,77,32,70,105,108,116,62,111,50,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,
                32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,
                32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,57,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,
                34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,
                32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,111,51,80,87,77,
                34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,
                32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,
                100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,65,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,
                100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,
                116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,82,101,115,111,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,
                48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,
                112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,66,
                34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,
                32,32,34,110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,67,117,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,
                49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,
                34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,67,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,
                84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,
                51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,82,
                101,118,83,110,100,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,
                32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,
                32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,68,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,
                32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,
                32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,79,117,116,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,
                109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,
                32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,
                32,34,109,120,53,69,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,
                32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,
                10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,70,105,108,116,62,78,122,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,
                34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,
                97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,53,70,34,44,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,
                34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,
                32,70,105,108,116,62,79,117,116,66,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,
                110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,
                123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,48,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,
                116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,
                32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,79,49,99,118,34,44,10,32,32,32,32,32,32,32,32,34,
                109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,
                32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,
                32,34,109,120,54,49,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,
                32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,
                10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,79,50,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,
                120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,
                116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,50,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,
                105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,
                111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,
                62,79,51,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,
                48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,
                32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,51,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,
                32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,
                34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,82,105,110,103,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,
                34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                54,52,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,70,105,108,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,
                49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,
                34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,53,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,
                84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,
                51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,70,105,
                108,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,
                48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,
                32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,54,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,
                32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,
                34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,82,101,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,
                32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,
                114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,
                55,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,
                32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,
                32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,79,117,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,
                10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,53,53,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,
                10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,56,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,
                121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,
                50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,111,50,80,
                87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,
                10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,
                101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,57,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,
                32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,
                110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,111,51,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,
                48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,
                112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,65,
                34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,
                32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,82,101,115,111,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,
                49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,
                34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,66,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,
                84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,
                51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,67,117,
                116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,
                48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,
                34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,67,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,
                32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,
                110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,82,101,118,83,110,100,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,
                34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                54,68,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,79,117,116,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,
                34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,
                101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,69,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,
                110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,
                97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,
                78,122,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,
                32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,
                32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,54,70,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,
                32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,
                32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,82,101,118,62,79,117,116,66,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,
                34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                55,48,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,79,49,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,
                32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,
                114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,55,49,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,
                116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,
                116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,
                79,50,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,
                46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,
                32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,55,50,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,
                32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,
                97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,79,51,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,
                58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                55,51,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,82,105,110,103,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,
                32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,
                114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,55,52,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,
                116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,
                116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,
                70,105,108,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,
                48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,
                32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,55,53,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,
                32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,
                34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,70,105,108,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,
                105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,53,53,10,32,32,32,32,32,32,125,44,10,32,32,32,32,
                32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,
                32,34,109,120,55,54,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,
                32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,
                10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,82,101,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,
                97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,
                101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,55,55,34,44,10,32,32,32,32,32,32,34,101,110,100,112,
                111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,
                108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,
                97,112,62,79,117,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,
                58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,
                32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,55,56,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,
                10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,
                32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,111,50,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,
                105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,
                32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,
                34,109,120,55,57,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,
                123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,
                32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,111,51,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,
                97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,
                101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,55,65,34,44,10,32,32,32,32,32,32,34,101,110,100,112,
                111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,
                108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,
                97,112,62,82,101,115,111,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,
                105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,
                10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,55,66,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,
                34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,
                32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,67,117,116,67,86,34,44,10,32,32,32,32,32,32,32,32,
                34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,
                32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,
                58,32,34,109,120,55,67,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,
                58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,
                123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,82,101,118,83,110,100,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,
                32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,
                97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,55,68,34,44,10,32,32,32,32,32,32,34,101,
                110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,
                58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,
                34,77,32,84,114,97,112,62,79,117,116,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,
                32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,
                10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,55,69,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,
                101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,
                32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,78,122,76,118,108,34,44,10,32,
                32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,
                32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,
                105,110,116,73,68,34,58,32,34,109,120,55,70,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,
                97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,
                105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,84,114,97,112,62,79,117,116,66,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,
                32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,
                34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,56,48,34,44,10,32,32,32,
                32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,
                121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,
                101,34,58,32,34,77,32,74,111,121,88,62,79,49,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,
                32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,
                44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,56,49,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,
                34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,
                32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,88,62,79,50,99,118,34,44,10,32,32,
                32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,
                125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,
                110,116,73,68,34,58,32,34,109,120,56,50,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,
                121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,
                110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,88,62,79,51,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,
                32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,
                34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,56,51,34,44,10,32,32,32,32,32,32,
                34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,
                101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,
                58,32,34,77,32,74,111,121,88,62,82,105,110,103,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,
                32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,
                32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,56,52,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,
                118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,
                125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,88,62,70,105,108,116,34,44,10,32,32,32,
                32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,
                44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,
                116,73,68,34,58,32,34,109,120,56,53,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,
                112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,
                34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,88,62,70,105,108,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,
                32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,
                32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,56,54,34,44,10,32,32,32,32,32,
                32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,
                112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,
                34,58,32,34,77,32,74,111,121,88,62,82,101,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,
                32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,
                32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,56,55,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,
                118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,
                125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,88,62,79,117,116,34,44,10,32,32,32,32,
                32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,
                10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,
                116,73,68,34,58,32,34,109,120,56,56,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,
                112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,
                34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,88,62,111,50,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,
                32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,
                112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,56,57,34,44,10,32,32,32,32,32,32,34,
                101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,
                34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,
                32,34,77,32,74,111,121,88,62,111,51,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,
                32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,
                32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,56,65,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,
                118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,
                125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,88,62,82,101,115,111,67,86,34,44,10,32,
                32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,
                32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,
                105,110,116,73,68,34,58,32,34,109,120,56,66,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,
                97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,
                105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,88,62,67,117,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,
                32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,
                34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,56,67,34,44,10,32,32,32,
                32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,
                121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,
                101,34,58,32,34,77,32,74,111,121,88,62,82,101,118,83,110,100,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,
                32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,
                32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,56,68,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,
                34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,
                32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,88,62,79,117,116,76,118,
                108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,
                32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,
                110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,56,69,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,
                34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,
                111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,88,62,78,122,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,
                48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,
                112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,56,70,
                34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,
                32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,88,62,79,117,116,66,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,
                44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,
                10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,57,48,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,
                121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,
                50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,62,79,49,
                99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,
                10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,
                101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,57,49,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,
                32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,
                110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,62,79,50,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,
                48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,
                112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,57,50,
                34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,
                32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,62,79,51,99,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,
                44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,
                10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,57,51,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,
                121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,
                50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,62,82,105,
                110,103,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,
                48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,
                34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,57,52,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,
                32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,
                110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,62,70,105,108,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,
                58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                57,53,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,62,70,105,108,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,
                34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,
                101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,57,54,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,
                110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,
                97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,
                62,82,101,118,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,
                48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,
                32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,57,55,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,
                32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,
                34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,62,79,117,116,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,
                58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,
                117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,
                57,56,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,
                32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,
                32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,62,111,50,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,
                58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,
                101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,57,57,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,
                110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,
                97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,
                62,111,51,80,87,77,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,
                32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,
                32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,57,65,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,
                32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,
                32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,62,82,101,115,111,67,86,34,44,10,32,32,32,32,32,32,32,32,34,
                109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,
                32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,
                32,34,109,120,57,66,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,
                32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,
                10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,62,67,117,116,67,86,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,
                109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,
                109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,57,67,34,44,10,32,32,32,32,32,32,34,101,110,100,
                112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,
                34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,
                32,74,111,121,89,62,82,101,118,83,110,100,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,
                34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,
                32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,57,68,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,
                118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,
                125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,62,79,117,116,76,118,108,34,44,10,32,
                32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,
                32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,
                105,110,116,73,68,34,58,32,34,109,120,57,69,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,
                97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,
                105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,32,74,111,121,89,62,78,122,76,118,108,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,
                32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,
                34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,109,120,57,70,34,44,10,32,32,32,
                32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,
                121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,
                101,34,58,32,34,77,32,74,111,121,89,62,79,117,116,66,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,
                32,32,32,34,105,110,105,116,34,58,32,48,46,48,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,
                44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,106,111,121,88,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,
                32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,
                32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,74,111,121,115,116,105,99,107,32,88,34,44,10,32,
                32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,53,10,32,32,32,32,32,
                32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,
                105,110,116,73,68,34,58,32,34,106,111,121,89,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,
                97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,
                105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,74,111,121,115,116,105,99,107,32,89,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,
                32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,53,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,
                58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,118,111,108,117,109,101,34,44,10,
                32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,
                32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,
                110,97,109,101,34,58,32,34,86,111,108,117,109,101,34,44,10,32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,
                32,32,34,105,110,105,116,34,58,32,48,46,56,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,44,
                10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,116,117,110,101,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,
                34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,
                32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,77,97,115,116,101,114,32,84,117,110,101,34,44,10,
                32,32,32,32,32,32,32,32,34,109,105,110,34,58,32,48,46,48,44,10,32,32,32,32,32,32,32,32,34,109,97,120,34,58,32,49,44,10,32,32,32,32,32,32,32,32,34,105,110,105,116,34,58,32,48,46,53,10,32,32,32,32,
                32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,112,97,114,97,109,101,116,101,114,34,10,32,32,32,32,125,10,32,32,93,44,10,32,32,34,111,117,116,112,117,116,115,34,58,
                32,91,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,73,68,34,58,32,34,97,117,100,105,111,79,117,116,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,
                121,112,101,34,58,32,34,115,116,114,101,97,109,34,44,10,32,32,32,32,32,32,34,100,97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,118,101,99,116,111,
                114,34,44,10,32,32,32,32,32,32,32,32,34,101,108,101,109,101,110,116,34,58,32,123,10,32,32,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,102,108,111,97,116,51,50,34,10,32,32,32,32,32,32,
                32,32,125,44,10,32,32,32,32,32,32,32,32,34,115,105,122,101,34,58,32,50,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,
                32,32,34,110,97,109,101,34,58,32,34,65,117,100,105,111,32,111,117,116,34,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,112,117,114,112,111,115,101,34,58,32,34,97,117,100,105,111,32,111,117,
                116,34,44,10,32,32,32,32,32,32,34,110,117,109,65,117,100,105,111,67,104,97,110,110,101,108,115,34,58,32,50,10,32,32,32,32,125,44,10,32,32,32,32,123,10,32,32,32,32,32,32,34,101,110,100,112,111,105,
                110,116,73,68,34,58,32,34,110,111,116,101,79,117,116,34,44,10,32,32,32,32,32,32,34,101,110,100,112,111,105,110,116,84,121,112,101,34,58,32,34,101,118,101,110,116,34,44,10,32,32,32,32,32,32,34,100,
                97,116,97,84,121,112,101,34,58,32,123,10,32,32,32,32,32,32,32,32,34,116,121,112,101,34,58,32,34,111,98,106,101,99,116,34,44,10,32,32,32,32,32,32,32,32,34,99,108,97,115,115,34,58,32,34,78,111,116,
                101,69,118,101,110,116,34,44,10,32,32,32,32,32,32,32,32,34,109,101,109,98,101,114,115,34,58,32,123,10,32,32,32,32,32,32,32,32,32,32,34,112,105,116,99,104,34,58,32,123,10,32,32,32,32,32,32,32,32,
                32,32,32,32,34,116,121,112,101,34,58,32,34,105,110,116,51,50,34,10,32,32,32,32,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,32,32,32,32,34,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,32,32,
                32,32,34,116,121,112,101,34,58,32,34,105,110,116,51,50,34,10,32,32,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,32,32,125,10,32,32,32,32,32,32,125,44,10,32,32,32,32,32,32,34,97,110,110,111,116,
                97,116,105,111,110,34,58,32,123,10,32,32,32,32,32,32,32,32,34,110,97,109,101,34,58,32,34,78,111,116,101,32,111,117,116,34,10,32,32,32,32,32,32,125,10,32,32,32,32,125,10,32,32,93,10,125, 0 };

        //==============================================================================
        struct intrinsics;

        using SizeType = int32_t;
        using IndexType = int32_t;
        using StringHandle = uint32_t;

        struct Null
        {
            template <typename AnyType> operator AnyType() const    { return {}; }
            Null operator[] (IndexType) const                       { return {}; }
        };

        //==============================================================================
        template <typename ElementType, SizeType numElements>
        struct Array
        {
            Array() = default;
            Array (Null) {}
            Array (const Array&) = default;

            template <typename ElementOrList>
            Array (const ElementOrList& value) noexcept
            {
                if constexpr (std::is_convertible<ElementOrList, ElementType>::value)
                {
                    for (IndexType i = 0; i < numElements; ++i)
                        this->elements[i] = static_cast<ElementType> (value);
                }
                else
                {
                    for (IndexType i = 0; i < numElements; ++i)
                        this->elements[i] = static_cast<ElementType> (value[i]);
                }
            }

            template <typename... Others>
            Array (ElementType e0, ElementType e1, Others... others) noexcept
            {
                this->elements[0] = static_cast<ElementType> (e0);
                this->elements[1] = static_cast<ElementType> (e1);

                if constexpr (numElements > 2)
                {
                    const ElementType initialisers[] = { static_cast<ElementType> (others)... };

                    for (size_t i = 0; i < sizeof...(others); ++i)
                        this->elements[i + 2] = initialisers[i];
                }
            }

            Array (const ElementType* rawArray, size_t) noexcept
            {
                for (IndexType i = 0; i < numElements; ++i)
                    this->elements[i] = rawArray[i];
            }

            Array& operator= (const Array&) noexcept = default;
            Array& operator= (Null) noexcept                 { this->clear(); return *this; }

            template <typename ElementOrList>
            Array& operator= (const ElementOrList& value) noexcept
            {
                if constexpr (std::is_convertible<ElementOrList, ElementType>::value)
                {
                    for (IndexType i = 0; i < numElements; ++i)
                        this->elements[i] = static_cast<ElementType> (value);
                }
                else
                {
                    for (IndexType i = 0; i < numElements; ++i)
                        this->elements[i] = static_cast<ElementType> (value[i]);
                }
            }

            static constexpr SizeType size()                                    { return numElements; }

            const ElementType& operator[] (IndexType index) const noexcept      { return this->elements[index]; }
            ElementType& operator[] (IndexType index) noexcept                  { return this->elements[index]; }

            void clear() noexcept
            {
                for (auto& element : elements)
                    element = ElementType();
            }

            void clear (SizeType numElementsToClear) noexcept
            {
                for (SizeType i = 0; i < numElementsToClear; ++i)
                    elements[i] = ElementType();
            }

            ElementType elements[numElements] = {};
        };

        //==============================================================================
        template <typename ElementType, SizeType numElements>
        struct Vector  : public Array<ElementType, numElements>
        {
            Vector() = default;
            Vector (Null) {}

            template <typename ElementOrList>
            Vector (const ElementOrList& value) noexcept  : Array<ElementType, numElements> (value) {}

            template <typename... Others>
            Vector (ElementType e0, ElementType e1, Others... others) noexcept  : Array<ElementType, numElements> (e0, e1, others...) {}

            Vector (const ElementType* rawArray, size_t) noexcept  : Array<ElementType, numElements> (rawArray, size_t()) {}

            template <typename ElementOrList>
            Vector& operator= (const ElementOrList& value) noexcept { return Array<ElementType, numElements>::operator= (value); }

            Vector& operator= (Null) noexcept { this->clear(); return *this; }

            operator ElementType() const noexcept
            {
                static_assert (numElements == 1);
                return this->elements[0];
            }

            constexpr auto operator!() const noexcept     { return performUnaryOp ([] (ElementType n) { return ! n; }); }
            constexpr auto operator~() const noexcept     { return performUnaryOp ([] (ElementType n) { return ~n; }); }
            constexpr auto operator-() const noexcept     { return performUnaryOp ([] (ElementType n) { return -n; }); }

            constexpr auto operator+ (const Vector& rhs) const noexcept   { return performBinaryOp (rhs, [] (ElementType a, ElementType b) { return a + b; }); }
            constexpr auto operator- (const Vector& rhs) const noexcept   { return performBinaryOp (rhs, [] (ElementType a, ElementType b) { return a - b; }); }
            constexpr auto operator* (const Vector& rhs) const noexcept   { return performBinaryOp (rhs, [] (ElementType a, ElementType b) { return a * b; }); }
            constexpr auto operator/ (const Vector& rhs) const noexcept   { return performBinaryOp (rhs, [] (ElementType a, ElementType b) { return a / b; }); }
            constexpr auto operator% (const Vector& rhs) const noexcept   { return performBinaryOp (rhs, [] (ElementType a, ElementType b) { return intrinsics::modulo (a, b); }); }
            constexpr auto operator& (const Vector& rhs) const noexcept   { return performBinaryOp (rhs, [] (ElementType a, ElementType b) { return a & b; }); }
            constexpr auto operator| (const Vector& rhs) const noexcept   { return performBinaryOp (rhs, [] (ElementType a, ElementType b) { return a | b; }); }
            constexpr auto operator<< (const Vector& rhs) const noexcept   { return performBinaryOp (rhs, [] (ElementType a, ElementType b) { return a << b; }); }
            constexpr auto operator>> (const Vector& rhs) const noexcept   { return performBinaryOp (rhs, [] (ElementType a, ElementType b) { return a >> b; }); }

            constexpr auto operator== (const Vector& rhs) const noexcept  { return performComparison (rhs, [] (ElementType a, ElementType b) { return a == b; }); }
            constexpr auto operator!= (const Vector& rhs) const noexcept  { return performComparison (rhs, [] (ElementType a, ElementType b) { return a != b; }); }
            constexpr auto operator<  (const Vector& rhs) const noexcept  { return performComparison (rhs, [] (ElementType a, ElementType b) { return a < b; }); }
            constexpr auto operator<= (const Vector& rhs) const noexcept  { return performComparison (rhs, [] (ElementType a, ElementType b) { return a <= b; }); }
            constexpr auto operator>  (const Vector& rhs) const noexcept  { return performComparison (rhs, [] (ElementType a, ElementType b) { return a > b; }); }
            constexpr auto operator>= (const Vector& rhs) const noexcept  { return performComparison (rhs, [] (ElementType a, ElementType b) { return a >= b; }); }

            template <typename Functor>
            constexpr Vector performUnaryOp (Functor&& f) const noexcept
            {
                Vector result;

                for (IndexType i = 0; i < numElements; ++i)
                    result.elements[i] = f (this->elements[i]);

                return result;
            }

            template <typename Functor>
            constexpr Vector performBinaryOp (const Vector& rhs, Functor&& f) const noexcept
            {
                Vector result;

                for (IndexType i = 0; i < numElements; ++i)
                    result.elements[i] = f (this->elements[i], rhs.elements[i]);

                return result;
            }

            template <typename Functor>
            constexpr Vector<bool, numElements> performComparison (const Vector& rhs, Functor&& f) const noexcept
            {
                Vector<bool, numElements> result;

                for (IndexType i = 0; i < numElements; ++i)
                    result.elements[i] = f (this->elements[i], rhs.elements[i]);

                return result;
            }
        };

        //==============================================================================
        template <typename ElementType>
        struct Slice
        {
            Slice() = default;
            Slice (Null) {}
            Slice (ElementType* e, SizeType size) : elements (e), numElements (size) {}
            Slice (const Slice&) = default;
            Slice& operator= (const Slice&) = default;
            template <typename ArrayType> Slice (const ArrayType& a) : elements (const_cast<ArrayType&> (a).elements), numElements (a.size()) {}
            template <typename ArrayType> Slice (const ArrayType& a, SizeType offset, SizeType size) : elements (const_cast<ArrayType&> (a).elements + offset), numElements (size) {}

            constexpr SizeType size() const                                     { return numElements; }
            ElementType operator[] (IndexType index) const noexcept             { return numElements == 0 ? ElementType() : elements[index]; }
            ElementType& operator[] (IndexType index) noexcept                  { return numElements == 0 ? emptyValue : elements[index]; }

            Slice slice (IndexType start, IndexType end) noexcept
            {
                if (numElements == 0) return {};
                if (start >= numElements) return {};

                return { elements + start, std::min (static_cast<SizeType> (end - start), numElements - start) };
            }

            const Slice slice (IndexType start, IndexType end) const noexcept
            {
                if (numElements == 0) return {};
                if (start >= numElements) return {};

                return { elements + start, std::min (static_cast<SizeType> (end - start), numElements - start) };
            }

            ElementType* elements = nullptr;
            SizeType numElements = 0;

            static inline ElementType emptyValue {};
        };

        //==============================================================================
        #if __clang__
         #pragma clang diagnostic push
         #pragma clang diagnostic ignored "-Wunused-variable"
         #pragma clang diagnostic ignored "-Wunused-parameter"
         #pragma clang diagnostic ignored "-Wunused-label"
         #pragma clang diagnostic ignored "-Wtautological-compare"

         #if __clang_major__ >= 14
          #pragma clang diagnostic ignored "-Wunused-but-set-variable"
         #endif

         #if __clang_major__ >= 17
          #pragma clang diagnostic ignored "-Wnan-infinity-disabled"
         #endif

        #elif __GNUC__
         #pragma GCC diagnostic push
         #pragma GCC diagnostic ignored "-Wunused-variable"
         #pragma GCC diagnostic ignored "-Wunused-parameter"
         #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
         #pragma GCC diagnostic ignored "-Wunused-label"
        #else
         #pragma warning (push, 0)
         #pragma warning (disable: 4702)
         #pragma warning (disable: 4706)
        #endif

        //==============================================================================
        struct plugincorp_Params
        {
            float o1Freq = {};
            float o1Range = {};
            float o1Sine = {};
            float o1Saw = {};
            float o2Freq = {};
            float o2Range = {};
            float o2Shape = {};
            float o2Pw = {};
            float o2Level = {};
            float o3Freq = {};
            float o3Range = {};
            float o3Shape = {};
            float o3Pw = {};
            float o3Level = {};
            float drift = {};
            float noise = {};
            float cutoff = {};
            float reso = {};
            float fKeyTrack = {};
            float trapA = {};
            float trapOn = {};
            float trapD = {};
            float trapOff = {};
            float reverb = {};
            Array<float, 160> mx;
            float joyX = {};
            float joyY = {};
            float volume = {};
            float tune = {};
        };

        struct _VCSVoice_1_State
        {
            plugincorp_Params params;
            bool active = {};
            float freq = {};
            float vel = {};
            float ph1 = {};
            float ph2 = {};
            float ph3 = {};
            float dr1 = {};
            float dr2 = {};
            float dr3 = {};
            float drT1 = {};
            float drT2 = {};
            float drT3 = {};
            int32_t rngc = {};
            float lp1 = {};
            float lp2 = {};
            float lp3 = {};
            float lp4 = {};
            float lp4out = {};
            Array<float, 2048> sbuf;
            int32_t sw = {};
            float sap1 = {};
            float sap2 = {};
            float sdamp = {};
            float dcx = {};
            float dcy = {};
            int32_t trapStage = {};
            float trap = {};
            float trapOffT = {};
            float filtPrev = {};
            float revPrev = {};
            Array<float, 10> src;
            int32_t _instanceIndex = {};
            float sr = {};
            float invSr = {};
            float ny = {};
            int32_t _resumeIndex = {};
        };

        struct std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_VoiceState
        {
            bool isActive = {};
            bool isReleasing = {};
            int32_t channel = {};
            int32_t age = {};
            float pitch = {};
        };

        struct std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State
        {
            Array<std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_VoiceState, 1> voiceState;
            int32_t nextActiveTime = {};
            int32_t nextInactiveTime = {};
            bool mpeMasterSustainActive = {};
            int64_t perChannelSustainActive = {};
        };

        struct _ParamsProcessor_1_State
        {
            plugincorp_Params params;
            bool seeded = {};
        };

        struct std_midi_MPEConverter_1_State
        {
        };

        struct _JWVCS_State
        {
            int32_t _sessionID = {};
            double _frequency = {};
            Array<_VCSVoice_1_State, 1> voices;
            std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State voiceAllocator;
            _ParamsProcessor_1_State paramsProcessor;
            std_midi_MPEConverter_1_State mpe;
            std_midi_MPEConverter_1_State noteTap;
        };

        struct plugincorp_NoteEvent
        {
            int32_t pitch = {};
            int32_t on = {};
        };

        struct JWVCS_eventValue_noteOut
        {
            int32_t frame = {};
            int32_t type = {};
            plugincorp_NoteEvent value_0;
        };

        struct JWVCS_State
        {
            int32_t _currentFrame = {};
            _JWVCS_State _state;
            int32_t noteOut_eventCount = {};
            Array<JWVCS_eventValue_noteOut, 32> noteOut;
        };

        struct std_midi_Message
        {
            int32_t message = {};
        };

        struct std_notes_NoteOn
        {
            int32_t channel = {};
            float pitch = {};
            float velocity = {};
        };

        struct std_notes_NoteOff
        {
            int32_t channel = {};
            float pitch = {};
            float velocity = {};
        };

        struct std_notes_PitchBend
        {
            int32_t channel = {};
            float bendSemitones = {};
        };

        struct std_notes_Pressure
        {
            int32_t channel = {};
            float pressure = {};
        };

        struct std_notes_Slide
        {
            int32_t channel = {};
            float slide = {};
        };

        struct std_notes_Control
        {
            int32_t channel = {};
            int32_t control = {};
            float value = {};
        };

        struct JWVCS_IO
        {
            Array<Vector<float, 2>, 512> audioOut;
        };

        struct _JWVCS_IO
        {
            Vector<float, 2> audioOut;
        };

        struct _VCSVoice_1_IO
        {
            Vector<float, 2> voiceOut;
        };

        struct std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO
        {
        };

        using std_notes_T = float;
        using std_intrinsics_T = float;
        using std_intrinsics_T_0 = float;
        using std_intrinsics_T_1 = float;
        using std_intrinsics_T_2 = float;
        using std_intrinsics_T_3 = float;
        using std_intrinsics_T_4 = float;
        using std_intrinsics_T_5 = float;
        using std_intrinsics_T_6 = float;
        using std_intrinsics_T_7 = float;
        using std_intrinsics_T_8 = float;
        using std_intrinsics_T_9 = float;

        //==============================================================================
        double getMaxFrequency() const
        {
            return 192000.0;
        }

        void initialise (int32_t sessionID, double frequency)
        {
            if (frequency > getMaxFrequency()) throw std::runtime_error ("frequency out of range");
            initSessionID = sessionID;
            initFrequency = frequency;
            reset();
        }

        void reset()
        {
            std::memset (reinterpret_cast<char*> (&cmajState), 0, sizeof (cmajState));
            int32_t processorID = 0;
            _initialise (cmajState, processorID, initSessionID, initFrequency);
        }

        void advance (int32_t frames)
        {
            cmajIO.audioOut.clear (static_cast<SizeType> (frames));
            _advance (cmajState, cmajIO, frames);
        }

        void copyOutputValue (EndpointHandle endpointHandle, void* dest)
        {
            (void) endpointHandle; (void) dest;

            throw std::runtime_error ("Unknown value endpointHandle:" + std::to_string (endpointHandle));
        }

        void copyOutputFrames (EndpointHandle endpointHandle, void* dest, uint32_t numFramesToCopy)
        {
            if (endpointHandle == 190) { std::memcpy (reinterpret_cast<char*> (dest), std::addressof (cmajIO.audioOut), 8 * numFramesToCopy); std::memset (reinterpret_cast<char*> (std::addressof (cmajIO.audioOut)), 0, 8 * numFramesToCopy); return; }
            throw std::runtime_error ("Unknown stream endpointHandle:" + std::to_string (endpointHandle));
        }

        uint32_t getNumOutputEvents (EndpointHandle endpointHandle)
        {
            if (endpointHandle == 191) return (uint32_t) cmajState.noteOut_eventCount;
            throw std::runtime_error ("Unknown event endpointHandle:" + std::to_string (endpointHandle));
            return {};
        }

        void resetOutputEventCount (EndpointHandle endpointHandle)
        {
            if (endpointHandle == 191) { cmajState.noteOut_eventCount = 0; return; }
        }

        uint32_t getOutputEventType (EndpointHandle endpointHandle, uint32_t index)
        {
            if (endpointHandle == 191) return (uint32_t) cmajState.noteOut[(IndexType) index].type;
            throw std::runtime_error ("Unknown event endpointHandle:" + std::to_string (endpointHandle));
            return {};
        }

        static uint32_t getOutputEventDataSize (EndpointHandle endpointHandle, uint32_t typeIndex)
        {
            (void) endpointHandle; (void) typeIndex;

            if (endpointHandle == 191 && typeIndex == 0) return 8;
            throw std::runtime_error ("Unknown event endpointHandle:" + std::to_string (endpointHandle));
            return 0;
        }

        uint32_t readOutputEvent (EndpointHandle endpointHandle, uint32_t index, unsigned char* dest)
        {
            if (endpointHandle == 191)
            {
                auto& event = cmajState.noteOut[(IndexType) index];
                if (event.type == 0)
                {
                    memcpy (dest, std::addressof (event.value_0.pitch), 4);
                    dest += 4;
                    memcpy (dest, std::addressof (event.value_0.on), 4);
                    dest += 4;
                    return (uint32_t) event.frame;
                }
            }

            throw std::runtime_error ("Unknown event endpointHandle:" + std::to_string (endpointHandle));
            return {};
        }

        void addEvent_midiIn (const std_midi_Message& event)
        {
            _sendEvent_midiIn (cmajState, event);
        }

        void addEvent_o1Freq (float event)
        {
            _sendEvent_o1Freq (cmajState, event);
        }

        void addEvent_o1Range (float event)
        {
            _sendEvent_o1Range (cmajState, event);
        }

        void addEvent_o1Sine (float event)
        {
            _sendEvent_o1Sine (cmajState, event);
        }

        void addEvent_o1Saw (float event)
        {
            _sendEvent_o1Saw (cmajState, event);
        }

        void addEvent_o2Freq (float event)
        {
            _sendEvent_o2Freq (cmajState, event);
        }

        void addEvent_o2Range (float event)
        {
            _sendEvent_o2Range (cmajState, event);
        }

        void addEvent_o2Shape (float event)
        {
            _sendEvent_o2Shape (cmajState, event);
        }

        void addEvent_o2Pw (float event)
        {
            _sendEvent_o2Pw (cmajState, event);
        }

        void addEvent_o2Level (float event)
        {
            _sendEvent_o2Level (cmajState, event);
        }

        void addEvent_o3Freq (float event)
        {
            _sendEvent_o3Freq (cmajState, event);
        }

        void addEvent_o3Range (float event)
        {
            _sendEvent_o3Range (cmajState, event);
        }

        void addEvent_o3Shape (float event)
        {
            _sendEvent_o3Shape (cmajState, event);
        }

        void addEvent_o3Pw (float event)
        {
            _sendEvent_o3Pw (cmajState, event);
        }

        void addEvent_o3Level (float event)
        {
            _sendEvent_o3Level (cmajState, event);
        }

        void addEvent_drift (float event)
        {
            _sendEvent_drift (cmajState, event);
        }

        void addEvent_noise (float event)
        {
            _sendEvent_noise (cmajState, event);
        }

        void addEvent_cutoff (float event)
        {
            _sendEvent_cutoff (cmajState, event);
        }

        void addEvent_reso (float event)
        {
            _sendEvent_reso (cmajState, event);
        }

        void addEvent_fKeyTrack (float event)
        {
            _sendEvent_fKeyTrack (cmajState, event);
        }

        void addEvent_trapA (float event)
        {
            _sendEvent_trapA (cmajState, event);
        }

        void addEvent_trapOn (float event)
        {
            _sendEvent_trapOn (cmajState, event);
        }

        void addEvent_trapD (float event)
        {
            _sendEvent_trapD (cmajState, event);
        }

        void addEvent_trapOff (float event)
        {
            _sendEvent_trapOff (cmajState, event);
        }

        void addEvent_reverb (float event)
        {
            _sendEvent_reverb (cmajState, event);
        }

        void addEvent_mx00 (float event)
        {
            _sendEvent_mx00 (cmajState, event);
        }

        void addEvent_mx01 (float event)
        {
            _sendEvent_mx01 (cmajState, event);
        }

        void addEvent_mx02 (float event)
        {
            _sendEvent_mx02 (cmajState, event);
        }

        void addEvent_mx03 (float event)
        {
            _sendEvent_mx03 (cmajState, event);
        }

        void addEvent_mx04 (float event)
        {
            _sendEvent_mx04 (cmajState, event);
        }

        void addEvent_mx05 (float event)
        {
            _sendEvent_mx05 (cmajState, event);
        }

        void addEvent_mx06 (float event)
        {
            _sendEvent_mx06 (cmajState, event);
        }

        void addEvent_mx07 (float event)
        {
            _sendEvent_mx07 (cmajState, event);
        }

        void addEvent_mx08 (float event)
        {
            _sendEvent_mx08 (cmajState, event);
        }

        void addEvent_mx09 (float event)
        {
            _sendEvent_mx09 (cmajState, event);
        }

        void addEvent_mx0A (float event)
        {
            _sendEvent_mx0A (cmajState, event);
        }

        void addEvent_mx0B (float event)
        {
            _sendEvent_mx0B (cmajState, event);
        }

        void addEvent_mx0C (float event)
        {
            _sendEvent_mx0C (cmajState, event);
        }

        void addEvent_mx0D (float event)
        {
            _sendEvent_mx0D (cmajState, event);
        }

        void addEvent_mx0E (float event)
        {
            _sendEvent_mx0E (cmajState, event);
        }

        void addEvent_mx0F (float event)
        {
            _sendEvent_mx0F (cmajState, event);
        }

        void addEvent_mx10 (float event)
        {
            _sendEvent_mx10 (cmajState, event);
        }

        void addEvent_mx11 (float event)
        {
            _sendEvent_mx11 (cmajState, event);
        }

        void addEvent_mx12 (float event)
        {
            _sendEvent_mx12 (cmajState, event);
        }

        void addEvent_mx13 (float event)
        {
            _sendEvent_mx13 (cmajState, event);
        }

        void addEvent_mx14 (float event)
        {
            _sendEvent_mx14 (cmajState, event);
        }

        void addEvent_mx15 (float event)
        {
            _sendEvent_mx15 (cmajState, event);
        }

        void addEvent_mx16 (float event)
        {
            _sendEvent_mx16 (cmajState, event);
        }

        void addEvent_mx17 (float event)
        {
            _sendEvent_mx17 (cmajState, event);
        }

        void addEvent_mx18 (float event)
        {
            _sendEvent_mx18 (cmajState, event);
        }

        void addEvent_mx19 (float event)
        {
            _sendEvent_mx19 (cmajState, event);
        }

        void addEvent_mx1A (float event)
        {
            _sendEvent_mx1A (cmajState, event);
        }

        void addEvent_mx1B (float event)
        {
            _sendEvent_mx1B (cmajState, event);
        }

        void addEvent_mx1C (float event)
        {
            _sendEvent_mx1C (cmajState, event);
        }

        void addEvent_mx1D (float event)
        {
            _sendEvent_mx1D (cmajState, event);
        }

        void addEvent_mx1E (float event)
        {
            _sendEvent_mx1E (cmajState, event);
        }

        void addEvent_mx1F (float event)
        {
            _sendEvent_mx1F (cmajState, event);
        }

        void addEvent_mx20 (float event)
        {
            _sendEvent_mx20 (cmajState, event);
        }

        void addEvent_mx21 (float event)
        {
            _sendEvent_mx21 (cmajState, event);
        }

        void addEvent_mx22 (float event)
        {
            _sendEvent_mx22 (cmajState, event);
        }

        void addEvent_mx23 (float event)
        {
            _sendEvent_mx23 (cmajState, event);
        }

        void addEvent_mx24 (float event)
        {
            _sendEvent_mx24 (cmajState, event);
        }

        void addEvent_mx25 (float event)
        {
            _sendEvent_mx25 (cmajState, event);
        }

        void addEvent_mx26 (float event)
        {
            _sendEvent_mx26 (cmajState, event);
        }

        void addEvent_mx27 (float event)
        {
            _sendEvent_mx27 (cmajState, event);
        }

        void addEvent_mx28 (float event)
        {
            _sendEvent_mx28 (cmajState, event);
        }

        void addEvent_mx29 (float event)
        {
            _sendEvent_mx29 (cmajState, event);
        }

        void addEvent_mx2A (float event)
        {
            _sendEvent_mx2A (cmajState, event);
        }

        void addEvent_mx2B (float event)
        {
            _sendEvent_mx2B (cmajState, event);
        }

        void addEvent_mx2C (float event)
        {
            _sendEvent_mx2C (cmajState, event);
        }

        void addEvent_mx2D (float event)
        {
            _sendEvent_mx2D (cmajState, event);
        }

        void addEvent_mx2E (float event)
        {
            _sendEvent_mx2E (cmajState, event);
        }

        void addEvent_mx2F (float event)
        {
            _sendEvent_mx2F (cmajState, event);
        }

        void addEvent_mx30 (float event)
        {
            _sendEvent_mx30 (cmajState, event);
        }

        void addEvent_mx31 (float event)
        {
            _sendEvent_mx31 (cmajState, event);
        }

        void addEvent_mx32 (float event)
        {
            _sendEvent_mx32 (cmajState, event);
        }

        void addEvent_mx33 (float event)
        {
            _sendEvent_mx33 (cmajState, event);
        }

        void addEvent_mx34 (float event)
        {
            _sendEvent_mx34 (cmajState, event);
        }

        void addEvent_mx35 (float event)
        {
            _sendEvent_mx35 (cmajState, event);
        }

        void addEvent_mx36 (float event)
        {
            _sendEvent_mx36 (cmajState, event);
        }

        void addEvent_mx37 (float event)
        {
            _sendEvent_mx37 (cmajState, event);
        }

        void addEvent_mx38 (float event)
        {
            _sendEvent_mx38 (cmajState, event);
        }

        void addEvent_mx39 (float event)
        {
            _sendEvent_mx39 (cmajState, event);
        }

        void addEvent_mx3A (float event)
        {
            _sendEvent_mx3A (cmajState, event);
        }

        void addEvent_mx3B (float event)
        {
            _sendEvent_mx3B (cmajState, event);
        }

        void addEvent_mx3C (float event)
        {
            _sendEvent_mx3C (cmajState, event);
        }

        void addEvent_mx3D (float event)
        {
            _sendEvent_mx3D (cmajState, event);
        }

        void addEvent_mx3E (float event)
        {
            _sendEvent_mx3E (cmajState, event);
        }

        void addEvent_mx3F (float event)
        {
            _sendEvent_mx3F (cmajState, event);
        }

        void addEvent_mx40 (float event)
        {
            _sendEvent_mx40 (cmajState, event);
        }

        void addEvent_mx41 (float event)
        {
            _sendEvent_mx41 (cmajState, event);
        }

        void addEvent_mx42 (float event)
        {
            _sendEvent_mx42 (cmajState, event);
        }

        void addEvent_mx43 (float event)
        {
            _sendEvent_mx43 (cmajState, event);
        }

        void addEvent_mx44 (float event)
        {
            _sendEvent_mx44 (cmajState, event);
        }

        void addEvent_mx45 (float event)
        {
            _sendEvent_mx45 (cmajState, event);
        }

        void addEvent_mx46 (float event)
        {
            _sendEvent_mx46 (cmajState, event);
        }

        void addEvent_mx47 (float event)
        {
            _sendEvent_mx47 (cmajState, event);
        }

        void addEvent_mx48 (float event)
        {
            _sendEvent_mx48 (cmajState, event);
        }

        void addEvent_mx49 (float event)
        {
            _sendEvent_mx49 (cmajState, event);
        }

        void addEvent_mx4A (float event)
        {
            _sendEvent_mx4A (cmajState, event);
        }

        void addEvent_mx4B (float event)
        {
            _sendEvent_mx4B (cmajState, event);
        }

        void addEvent_mx4C (float event)
        {
            _sendEvent_mx4C (cmajState, event);
        }

        void addEvent_mx4D (float event)
        {
            _sendEvent_mx4D (cmajState, event);
        }

        void addEvent_mx4E (float event)
        {
            _sendEvent_mx4E (cmajState, event);
        }

        void addEvent_mx4F (float event)
        {
            _sendEvent_mx4F (cmajState, event);
        }

        void addEvent_mx50 (float event)
        {
            _sendEvent_mx50 (cmajState, event);
        }

        void addEvent_mx51 (float event)
        {
            _sendEvent_mx51 (cmajState, event);
        }

        void addEvent_mx52 (float event)
        {
            _sendEvent_mx52 (cmajState, event);
        }

        void addEvent_mx53 (float event)
        {
            _sendEvent_mx53 (cmajState, event);
        }

        void addEvent_mx54 (float event)
        {
            _sendEvent_mx54 (cmajState, event);
        }

        void addEvent_mx55 (float event)
        {
            _sendEvent_mx55 (cmajState, event);
        }

        void addEvent_mx56 (float event)
        {
            _sendEvent_mx56 (cmajState, event);
        }

        void addEvent_mx57 (float event)
        {
            _sendEvent_mx57 (cmajState, event);
        }

        void addEvent_mx58 (float event)
        {
            _sendEvent_mx58 (cmajState, event);
        }

        void addEvent_mx59 (float event)
        {
            _sendEvent_mx59 (cmajState, event);
        }

        void addEvent_mx5A (float event)
        {
            _sendEvent_mx5A (cmajState, event);
        }

        void addEvent_mx5B (float event)
        {
            _sendEvent_mx5B (cmajState, event);
        }

        void addEvent_mx5C (float event)
        {
            _sendEvent_mx5C (cmajState, event);
        }

        void addEvent_mx5D (float event)
        {
            _sendEvent_mx5D (cmajState, event);
        }

        void addEvent_mx5E (float event)
        {
            _sendEvent_mx5E (cmajState, event);
        }

        void addEvent_mx5F (float event)
        {
            _sendEvent_mx5F (cmajState, event);
        }

        void addEvent_mx60 (float event)
        {
            _sendEvent_mx60 (cmajState, event);
        }

        void addEvent_mx61 (float event)
        {
            _sendEvent_mx61 (cmajState, event);
        }

        void addEvent_mx62 (float event)
        {
            _sendEvent_mx62 (cmajState, event);
        }

        void addEvent_mx63 (float event)
        {
            _sendEvent_mx63 (cmajState, event);
        }

        void addEvent_mx64 (float event)
        {
            _sendEvent_mx64 (cmajState, event);
        }

        void addEvent_mx65 (float event)
        {
            _sendEvent_mx65 (cmajState, event);
        }

        void addEvent_mx66 (float event)
        {
            _sendEvent_mx66 (cmajState, event);
        }

        void addEvent_mx67 (float event)
        {
            _sendEvent_mx67 (cmajState, event);
        }

        void addEvent_mx68 (float event)
        {
            _sendEvent_mx68 (cmajState, event);
        }

        void addEvent_mx69 (float event)
        {
            _sendEvent_mx69 (cmajState, event);
        }

        void addEvent_mx6A (float event)
        {
            _sendEvent_mx6A (cmajState, event);
        }

        void addEvent_mx6B (float event)
        {
            _sendEvent_mx6B (cmajState, event);
        }

        void addEvent_mx6C (float event)
        {
            _sendEvent_mx6C (cmajState, event);
        }

        void addEvent_mx6D (float event)
        {
            _sendEvent_mx6D (cmajState, event);
        }

        void addEvent_mx6E (float event)
        {
            _sendEvent_mx6E (cmajState, event);
        }

        void addEvent_mx6F (float event)
        {
            _sendEvent_mx6F (cmajState, event);
        }

        void addEvent_mx70 (float event)
        {
            _sendEvent_mx70 (cmajState, event);
        }

        void addEvent_mx71 (float event)
        {
            _sendEvent_mx71 (cmajState, event);
        }

        void addEvent_mx72 (float event)
        {
            _sendEvent_mx72 (cmajState, event);
        }

        void addEvent_mx73 (float event)
        {
            _sendEvent_mx73 (cmajState, event);
        }

        void addEvent_mx74 (float event)
        {
            _sendEvent_mx74 (cmajState, event);
        }

        void addEvent_mx75 (float event)
        {
            _sendEvent_mx75 (cmajState, event);
        }

        void addEvent_mx76 (float event)
        {
            _sendEvent_mx76 (cmajState, event);
        }

        void addEvent_mx77 (float event)
        {
            _sendEvent_mx77 (cmajState, event);
        }

        void addEvent_mx78 (float event)
        {
            _sendEvent_mx78 (cmajState, event);
        }

        void addEvent_mx79 (float event)
        {
            _sendEvent_mx79 (cmajState, event);
        }

        void addEvent_mx7A (float event)
        {
            _sendEvent_mx7A (cmajState, event);
        }

        void addEvent_mx7B (float event)
        {
            _sendEvent_mx7B (cmajState, event);
        }

        void addEvent_mx7C (float event)
        {
            _sendEvent_mx7C (cmajState, event);
        }

        void addEvent_mx7D (float event)
        {
            _sendEvent_mx7D (cmajState, event);
        }

        void addEvent_mx7E (float event)
        {
            _sendEvent_mx7E (cmajState, event);
        }

        void addEvent_mx7F (float event)
        {
            _sendEvent_mx7F (cmajState, event);
        }

        void addEvent_mx80 (float event)
        {
            _sendEvent_mx80 (cmajState, event);
        }

        void addEvent_mx81 (float event)
        {
            _sendEvent_mx81 (cmajState, event);
        }

        void addEvent_mx82 (float event)
        {
            _sendEvent_mx82 (cmajState, event);
        }

        void addEvent_mx83 (float event)
        {
            _sendEvent_mx83 (cmajState, event);
        }

        void addEvent_mx84 (float event)
        {
            _sendEvent_mx84 (cmajState, event);
        }

        void addEvent_mx85 (float event)
        {
            _sendEvent_mx85 (cmajState, event);
        }

        void addEvent_mx86 (float event)
        {
            _sendEvent_mx86 (cmajState, event);
        }

        void addEvent_mx87 (float event)
        {
            _sendEvent_mx87 (cmajState, event);
        }

        void addEvent_mx88 (float event)
        {
            _sendEvent_mx88 (cmajState, event);
        }

        void addEvent_mx89 (float event)
        {
            _sendEvent_mx89 (cmajState, event);
        }

        void addEvent_mx8A (float event)
        {
            _sendEvent_mx8A (cmajState, event);
        }

        void addEvent_mx8B (float event)
        {
            _sendEvent_mx8B (cmajState, event);
        }

        void addEvent_mx8C (float event)
        {
            _sendEvent_mx8C (cmajState, event);
        }

        void addEvent_mx8D (float event)
        {
            _sendEvent_mx8D (cmajState, event);
        }

        void addEvent_mx8E (float event)
        {
            _sendEvent_mx8E (cmajState, event);
        }

        void addEvent_mx8F (float event)
        {
            _sendEvent_mx8F (cmajState, event);
        }

        void addEvent_mx90 (float event)
        {
            _sendEvent_mx90 (cmajState, event);
        }

        void addEvent_mx91 (float event)
        {
            _sendEvent_mx91 (cmajState, event);
        }

        void addEvent_mx92 (float event)
        {
            _sendEvent_mx92 (cmajState, event);
        }

        void addEvent_mx93 (float event)
        {
            _sendEvent_mx93 (cmajState, event);
        }

        void addEvent_mx94 (float event)
        {
            _sendEvent_mx94 (cmajState, event);
        }

        void addEvent_mx95 (float event)
        {
            _sendEvent_mx95 (cmajState, event);
        }

        void addEvent_mx96 (float event)
        {
            _sendEvent_mx96 (cmajState, event);
        }

        void addEvent_mx97 (float event)
        {
            _sendEvent_mx97 (cmajState, event);
        }

        void addEvent_mx98 (float event)
        {
            _sendEvent_mx98 (cmajState, event);
        }

        void addEvent_mx99 (float event)
        {
            _sendEvent_mx99 (cmajState, event);
        }

        void addEvent_mx9A (float event)
        {
            _sendEvent_mx9A (cmajState, event);
        }

        void addEvent_mx9B (float event)
        {
            _sendEvent_mx9B (cmajState, event);
        }

        void addEvent_mx9C (float event)
        {
            _sendEvent_mx9C (cmajState, event);
        }

        void addEvent_mx9D (float event)
        {
            _sendEvent_mx9D (cmajState, event);
        }

        void addEvent_mx9E (float event)
        {
            _sendEvent_mx9E (cmajState, event);
        }

        void addEvent_mx9F (float event)
        {
            _sendEvent_mx9F (cmajState, event);
        }

        void addEvent_joyX (float event)
        {
            _sendEvent_joyX (cmajState, event);
        }

        void addEvent_joyY (float event)
        {
            _sendEvent_joyY (cmajState, event);
        }

        void addEvent_volume (float event)
        {
            _sendEvent_volume (cmajState, event);
        }

        void addEvent_tune (float event)
        {
            _sendEvent_tune (cmajState, event);
        }

        void addEvent (EndpointHandle endpointHandle, uint32_t typeIndex, const unsigned char* eventData)
        {
            (void) endpointHandle; (void) typeIndex; (void) eventData;

            if (endpointHandle == 1)
            {
                std_midi_Message value;
                memcpy (&value.message, eventData, 4);
                eventData += 4;
                return addEvent_midiIn (value);
            }

            if (endpointHandle == 2)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o1Freq (value);
            }

            if (endpointHandle == 3)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o1Range (value);
            }

            if (endpointHandle == 4)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o1Sine (value);
            }

            if (endpointHandle == 5)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o1Saw (value);
            }

            if (endpointHandle == 6)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o2Freq (value);
            }

            if (endpointHandle == 7)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o2Range (value);
            }

            if (endpointHandle == 8)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o2Shape (value);
            }

            if (endpointHandle == 9)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o2Pw (value);
            }

            if (endpointHandle == 10)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o2Level (value);
            }

            if (endpointHandle == 11)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o3Freq (value);
            }

            if (endpointHandle == 12)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o3Range (value);
            }

            if (endpointHandle == 13)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o3Shape (value);
            }

            if (endpointHandle == 14)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o3Pw (value);
            }

            if (endpointHandle == 15)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o3Level (value);
            }

            if (endpointHandle == 16)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_drift (value);
            }

            if (endpointHandle == 17)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_noise (value);
            }

            if (endpointHandle == 18)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_cutoff (value);
            }

            if (endpointHandle == 19)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_reso (value);
            }

            if (endpointHandle == 20)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_fKeyTrack (value);
            }

            if (endpointHandle == 21)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_trapA (value);
            }

            if (endpointHandle == 22)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_trapOn (value);
            }

            if (endpointHandle == 23)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_trapD (value);
            }

            if (endpointHandle == 24)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_trapOff (value);
            }

            if (endpointHandle == 25)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_reverb (value);
            }

            if (endpointHandle == 26)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx00 (value);
            }

            if (endpointHandle == 27)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx01 (value);
            }

            if (endpointHandle == 28)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx02 (value);
            }

            if (endpointHandle == 29)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx03 (value);
            }

            if (endpointHandle == 30)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx04 (value);
            }

            if (endpointHandle == 31)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx05 (value);
            }

            if (endpointHandle == 32)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx06 (value);
            }

            if (endpointHandle == 33)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx07 (value);
            }

            if (endpointHandle == 34)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx08 (value);
            }

            if (endpointHandle == 35)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx09 (value);
            }

            if (endpointHandle == 36)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx0A (value);
            }

            if (endpointHandle == 37)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx0B (value);
            }

            if (endpointHandle == 38)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx0C (value);
            }

            if (endpointHandle == 39)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx0D (value);
            }

            if (endpointHandle == 40)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx0E (value);
            }

            if (endpointHandle == 41)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx0F (value);
            }

            if (endpointHandle == 42)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx10 (value);
            }

            if (endpointHandle == 43)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx11 (value);
            }

            if (endpointHandle == 44)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx12 (value);
            }

            if (endpointHandle == 45)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx13 (value);
            }

            if (endpointHandle == 46)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx14 (value);
            }

            if (endpointHandle == 47)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx15 (value);
            }

            if (endpointHandle == 48)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx16 (value);
            }

            if (endpointHandle == 49)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx17 (value);
            }

            if (endpointHandle == 50)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx18 (value);
            }

            if (endpointHandle == 51)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx19 (value);
            }

            if (endpointHandle == 52)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx1A (value);
            }

            if (endpointHandle == 53)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx1B (value);
            }

            if (endpointHandle == 54)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx1C (value);
            }

            if (endpointHandle == 55)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx1D (value);
            }

            if (endpointHandle == 56)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx1E (value);
            }

            if (endpointHandle == 57)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx1F (value);
            }

            if (endpointHandle == 58)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx20 (value);
            }

            if (endpointHandle == 59)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx21 (value);
            }

            if (endpointHandle == 60)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx22 (value);
            }

            if (endpointHandle == 61)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx23 (value);
            }

            if (endpointHandle == 62)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx24 (value);
            }

            if (endpointHandle == 63)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx25 (value);
            }

            if (endpointHandle == 64)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx26 (value);
            }

            if (endpointHandle == 65)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx27 (value);
            }

            if (endpointHandle == 66)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx28 (value);
            }

            if (endpointHandle == 67)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx29 (value);
            }

            if (endpointHandle == 68)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx2A (value);
            }

            if (endpointHandle == 69)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx2B (value);
            }

            if (endpointHandle == 70)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx2C (value);
            }

            if (endpointHandle == 71)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx2D (value);
            }

            if (endpointHandle == 72)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx2E (value);
            }

            if (endpointHandle == 73)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx2F (value);
            }

            if (endpointHandle == 74)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx30 (value);
            }

            if (endpointHandle == 75)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx31 (value);
            }

            if (endpointHandle == 76)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx32 (value);
            }

            if (endpointHandle == 77)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx33 (value);
            }

            if (endpointHandle == 78)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx34 (value);
            }

            if (endpointHandle == 79)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx35 (value);
            }

            if (endpointHandle == 80)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx36 (value);
            }

            if (endpointHandle == 81)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx37 (value);
            }

            if (endpointHandle == 82)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx38 (value);
            }

            if (endpointHandle == 83)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx39 (value);
            }

            if (endpointHandle == 84)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx3A (value);
            }

            if (endpointHandle == 85)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx3B (value);
            }

            if (endpointHandle == 86)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx3C (value);
            }

            if (endpointHandle == 87)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx3D (value);
            }

            if (endpointHandle == 88)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx3E (value);
            }

            if (endpointHandle == 89)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx3F (value);
            }

            if (endpointHandle == 90)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx40 (value);
            }

            if (endpointHandle == 91)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx41 (value);
            }

            if (endpointHandle == 92)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx42 (value);
            }

            if (endpointHandle == 93)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx43 (value);
            }

            if (endpointHandle == 94)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx44 (value);
            }

            if (endpointHandle == 95)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx45 (value);
            }

            if (endpointHandle == 96)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx46 (value);
            }

            if (endpointHandle == 97)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx47 (value);
            }

            if (endpointHandle == 98)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx48 (value);
            }

            if (endpointHandle == 99)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx49 (value);
            }

            if (endpointHandle == 100)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx4A (value);
            }

            if (endpointHandle == 101)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx4B (value);
            }

            if (endpointHandle == 102)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx4C (value);
            }

            if (endpointHandle == 103)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx4D (value);
            }

            if (endpointHandle == 104)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx4E (value);
            }

            if (endpointHandle == 105)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx4F (value);
            }

            if (endpointHandle == 106)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx50 (value);
            }

            if (endpointHandle == 107)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx51 (value);
            }

            if (endpointHandle == 108)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx52 (value);
            }

            if (endpointHandle == 109)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx53 (value);
            }

            if (endpointHandle == 110)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx54 (value);
            }

            if (endpointHandle == 111)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx55 (value);
            }

            if (endpointHandle == 112)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx56 (value);
            }

            if (endpointHandle == 113)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx57 (value);
            }

            if (endpointHandle == 114)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx58 (value);
            }

            if (endpointHandle == 115)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx59 (value);
            }

            if (endpointHandle == 116)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx5A (value);
            }

            if (endpointHandle == 117)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx5B (value);
            }

            if (endpointHandle == 118)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx5C (value);
            }

            if (endpointHandle == 119)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx5D (value);
            }

            if (endpointHandle == 120)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx5E (value);
            }

            if (endpointHandle == 121)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx5F (value);
            }

            if (endpointHandle == 122)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx60 (value);
            }

            if (endpointHandle == 123)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx61 (value);
            }

            if (endpointHandle == 124)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx62 (value);
            }

            if (endpointHandle == 125)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx63 (value);
            }

            if (endpointHandle == 126)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx64 (value);
            }

            if (endpointHandle == 127)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx65 (value);
            }

            if (endpointHandle == 128)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx66 (value);
            }

            if (endpointHandle == 129)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx67 (value);
            }

            if (endpointHandle == 130)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx68 (value);
            }

            if (endpointHandle == 131)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx69 (value);
            }

            if (endpointHandle == 132)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx6A (value);
            }

            if (endpointHandle == 133)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx6B (value);
            }

            if (endpointHandle == 134)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx6C (value);
            }

            if (endpointHandle == 135)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx6D (value);
            }

            if (endpointHandle == 136)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx6E (value);
            }

            if (endpointHandle == 137)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx6F (value);
            }

            if (endpointHandle == 138)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx70 (value);
            }

            if (endpointHandle == 139)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx71 (value);
            }

            if (endpointHandle == 140)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx72 (value);
            }

            if (endpointHandle == 141)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx73 (value);
            }

            if (endpointHandle == 142)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx74 (value);
            }

            if (endpointHandle == 143)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx75 (value);
            }

            if (endpointHandle == 144)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx76 (value);
            }

            if (endpointHandle == 145)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx77 (value);
            }

            if (endpointHandle == 146)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx78 (value);
            }

            if (endpointHandle == 147)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx79 (value);
            }

            if (endpointHandle == 148)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx7A (value);
            }

            if (endpointHandle == 149)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx7B (value);
            }

            if (endpointHandle == 150)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx7C (value);
            }

            if (endpointHandle == 151)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx7D (value);
            }

            if (endpointHandle == 152)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx7E (value);
            }

            if (endpointHandle == 153)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx7F (value);
            }

            if (endpointHandle == 154)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx80 (value);
            }

            if (endpointHandle == 155)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx81 (value);
            }

            if (endpointHandle == 156)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx82 (value);
            }

            if (endpointHandle == 157)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx83 (value);
            }

            if (endpointHandle == 158)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx84 (value);
            }

            if (endpointHandle == 159)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx85 (value);
            }

            if (endpointHandle == 160)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx86 (value);
            }

            if (endpointHandle == 161)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx87 (value);
            }

            if (endpointHandle == 162)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx88 (value);
            }

            if (endpointHandle == 163)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx89 (value);
            }

            if (endpointHandle == 164)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx8A (value);
            }

            if (endpointHandle == 165)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx8B (value);
            }

            if (endpointHandle == 166)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx8C (value);
            }

            if (endpointHandle == 167)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx8D (value);
            }

            if (endpointHandle == 168)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx8E (value);
            }

            if (endpointHandle == 169)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx8F (value);
            }

            if (endpointHandle == 170)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx90 (value);
            }

            if (endpointHandle == 171)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx91 (value);
            }

            if (endpointHandle == 172)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx92 (value);
            }

            if (endpointHandle == 173)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx93 (value);
            }

            if (endpointHandle == 174)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx94 (value);
            }

            if (endpointHandle == 175)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx95 (value);
            }

            if (endpointHandle == 176)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx96 (value);
            }

            if (endpointHandle == 177)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx97 (value);
            }

            if (endpointHandle == 178)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx98 (value);
            }

            if (endpointHandle == 179)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx99 (value);
            }

            if (endpointHandle == 180)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx9A (value);
            }

            if (endpointHandle == 181)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx9B (value);
            }

            if (endpointHandle == 182)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx9C (value);
            }

            if (endpointHandle == 183)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx9D (value);
            }

            if (endpointHandle == 184)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx9E (value);
            }

            if (endpointHandle == 185)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_mx9F (value);
            }

            if (endpointHandle == 186)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_joyX (value);
            }

            if (endpointHandle == 187)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_joyY (value);
            }

            if (endpointHandle == 188)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_volume (value);
            }

            if (endpointHandle == 189)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_tune (value);
            }
        }

        void setValue (EndpointHandle endpointHandle, const void* value, int32_t frames)
        {
            (void) endpointHandle; (void) value; (void) frames;
        }

        void setInputFrames (EndpointHandle endpointHandle, const void* frameData, uint32_t numFrames, uint32_t numTrailingFramesToClear)
        {
            (void) endpointHandle; (void) frameData; (void) numFrames; (void) numTrailingFramesToClear;
        }

        //==============================================================================
        // Rendering state values
        int32_t initSessionID;
        double initFrequency;
        JWVCS_State cmajState = {};
        JWVCS_IO cmajIO = {};

        //==============================================================================
        void _sendEvent_midiIn (JWVCS_State& _state, std_midi_Message value) noexcept
        {
            _JWVCS__midiIn (_state._state, value);
        }

        void _JWVCS__midiIn (_JWVCS_State& _state, std_midi_Message value) noexcept
        {
            std__midi__MPEConverter__parseMIDI (_state.mpe, value);
        }

        void std__midi__MPEConverter__parseMIDI (std_midi_MPEConverter_1_State& _state, std_midi_Message message) noexcept
        {
            std_notes_NoteOn  _temp;
            std_notes_NoteOn  _temp_0;
            std_notes_NoteOff  _temp_1;
            std_notes_NoteOff  _temp_2;
            std_notes_PitchBend  _temp_3;
            std_notes_PitchBend  _temp_4;
            std_notes_Pressure  _temp_5;
            std_notes_Pressure  _temp_6;
            std_notes_Slide  _temp_7;
            std_notes_Slide  _temp_8;
            std_notes_Control  _temp_9;
            std_notes_Control  _temp_10;

            if (std__midi__isNoteOn (message))
            {
                _temp.channel = std__midi__getChannel0to15 (message);
                _temp.pitch = std__midi__getPitch (message);
                _temp.velocity = std__midi__getFloatVelocity (message);
                _temp_0 = _temp;
                std__midi__MPEConverter___writeEvent_eventOut (_state, _temp_0);
            }
            else
            {
                if (std__midi__isNoteOff (message))
                {
                    _temp_1.channel = std__midi__getChannel0to15 (message);
                    _temp_1.pitch = std__midi__getPitch (message);
                    _temp_1.velocity = std__midi__getFloatVelocity (message);
                    _temp_2 = _temp_1;
                    std__midi__MPEConverter___writeEvent_eventOut_0 (_state, _temp_2);
                }
                else
                {
                    if (std__midi__isPitchWheel (message))
                    {
                        _temp_3.channel = std__midi__getChannel0to15 (message);
                        _temp_3.bendSemitones = (0.005859375f * static_cast<float> (std__midi__get14BitValue (message) - int32_t {8192}));
                        _temp_4 = _temp_3;
                        std__midi__MPEConverter___writeEvent_eventOut_1 (_state, _temp_4);
                    }
                    else
                    {
                        if (std__midi__isChannelPressure (message))
                        {
                            _temp_5.channel = std__midi__getChannel0to15 (message);
                            _temp_5.pressure = std__midi__getFloatChannelPressureValue (message);
                            _temp_6 = _temp_5;
                            std__midi__MPEConverter___writeEvent_eventOut_2 (_state, _temp_6);
                        }
                        else
                        {
                            if (std__midi__isController (message))
                            {
                                if (std__midi__getControllerNumber (message) == g_slideController)
                                {
                                    _temp_7.channel = std__midi__getChannel0to15 (message);
                                    _temp_7.slide = std__midi__getFloatControllerValue (message);
                                    _temp_8 = _temp_7;
                                    std__midi__MPEConverter___writeEvent_eventOut_3 (_state, _temp_8);
                                }
                                else
                                {
                                    _temp_9.channel = std__midi__getChannel0to15 (message);
                                    _temp_9.control = std__midi__getControllerNumber (message);
                                    _temp_9.value = std__midi__getFloatControllerValue (message);
                                    _temp_10 = _temp_9;
                                    std__midi__MPEConverter___writeEvent_eventOut_4 (_state, _temp_10);
                                }
                            }
                        }
                    }
                }
            }
        }

        bool std__midi__isNoteOn (const std_midi_Message& this_) noexcept
        {
            return ((this_.message & int32_t {0xf00000}) == int32_t {0x900000}) ? ((this_.message & int32_t {255}) != int32_t {0}) : false;
        }

        void std__midi__MPEConverter___writeEvent_eventOut (std_midi_MPEConverter_1_State& _state, const std_notes_NoteOn& value) noexcept
        {
            _JWVCS___forwardEvent (state_upcast_struct_JWVCS_State_struc_FEfOBc(_state), value);
            _JWVCS___forwardEvent_5 (state_upcast_struct_JWVCS_State_struc_FEfOBc(_state), value);
        }

        void _JWVCS___forwardEvent (_JWVCS_State& _state, std_notes_NoteOn value) noexcept
        {
            NoteTap__eventsIn (_state.noteTap, value);
        }

        void NoteTap__eventsIn (std_midi_MPEConverter_1_State& _state, std_notes_NoteOn e) noexcept
        {
            plugincorp_NoteEvent  n;

            n = plugincorp_NoteEvent {};
            n.pitch = static_cast<int32_t> (e.pitch);
            n.on = int32_t {1};
            NoteTap___writeEvent_noteOut (_state, n);
        }

        void NoteTap___writeEvent_noteOut (std_midi_MPEConverter_1_State& _state, const plugincorp_NoteEvent& value) noexcept
        {
            _JWVCS___forwardEvent_3 (state_upcast_struct_JWVCS_State_struc_N1feHc(_state), value);
        }

        void _JWVCS___forwardEvent_3 (_JWVCS_State& _state, plugincorp_NoteEvent value) noexcept
        {
            _JWVCS___writeEvent_noteOut (_state, value);
        }

        void _JWVCS___writeEvent_noteOut (_JWVCS_State& _state, const plugincorp_NoteEvent& value) noexcept
        {
            JWVCS___writeEvent_noteOut (state_upcast_struct_JWVCS_State_struct_meOY3b(_state), value);
        }

        void JWVCS___writeEvent_noteOut (JWVCS_State& _state, const plugincorp_NoteEvent& value) noexcept
        {
            JWVCS___writeEvent_noteOut_0 (_state, value);
        }

        void JWVCS___writeEvent_noteOut_0 (JWVCS_State& _state, const plugincorp_NoteEvent& value) noexcept
        {
            if (_state.noteOut_eventCount < int32_t {32})
            {
                _state.noteOut[_state.noteOut_eventCount].frame = _state._currentFrame;
                _state.noteOut[_state.noteOut_eventCount].type = int32_t {0};
                _state.noteOut[_state.noteOut_eventCount].value_0 = value;
            }
            ++_state.noteOut_eventCount;
        }

        void _JWVCS___forwardEvent_5 (_JWVCS_State& _state, std_notes_NoteOn value) noexcept
        {
            std__voices__VoiceAllocator__eventIn (_state.voiceAllocator, value);
        }

        void std__voices__VoiceAllocator__eventIn (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, std_notes_NoteOn noteOn) noexcept
        {
            int32_t  oldest;
            std_notes_NoteOff  _temp;
            std_notes_NoteOff  _temp_0;

            oldest = std__voices__VoiceAllocator__findOldestIndex();
            if (_state.voiceState[oldest].isActive)
            {
                _temp.channel = _state.voiceState[oldest].channel;
                _temp.pitch = _state.voiceState[oldest].pitch;
                _temp.velocity = 0.0f;
                _temp_0 = _temp;
                std__voices__VoiceAllocator___writeEvent_voiceEventOut (_state, oldest, _temp_0);
            }
            std__voices__VoiceAllocator__start (_state, _state.voiceState[oldest], noteOn.channel, noteOn.pitch);
            std__voices__VoiceAllocator___writeEvent_voiceEventOut_0 (_state, oldest, noteOn);
        }

        int32_t std__voices__VoiceAllocator__findOldestIndex() noexcept
        {
            {
                return int32_t {0};
            }
        }

        void std__voices__VoiceAllocator___writeEvent_voiceEventOut (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, int32_t index, const std_notes_NoteOff& value) noexcept
        {
            _JWVCS___forwardEvent_12 (state_upcast_struct_JWVCS_State_struc_p00AYc(_state), index, value);
        }

        void _JWVCS___forwardEvent_12 (_JWVCS_State& _state, int32_t index, std_notes_NoteOff value) noexcept
        {
            VCSVoice__eventsIn (_state.voices[index], value);
        }

        void VCSVoice__eventsIn (_VCSVoice_1_State& _state, std_notes_NoteOff e) noexcept
        {
            if ((_state.trapStage == int32_t {1}) ? true : (_state.trapStage == int32_t {0}))
            {
                _state.trapStage = int32_t {2};
            }
        }

        void std__voices__VoiceAllocator__start (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_VoiceState& this_, int32_t channel, float pitch) noexcept
        {
            this_.isActive = true;
            this_.isReleasing = false;
            this_.channel = channel;
            this_.pitch = pitch;
            ++_state.nextActiveTime;
            this_.age = _state.nextActiveTime;
        }

        void std__voices__VoiceAllocator___writeEvent_voiceEventOut_0 (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, int32_t index, const std_notes_NoteOn& value) noexcept
        {
            _JWVCS___forwardEvent_11 (state_upcast_struct_JWVCS_State_struc_p00AYc(_state), index, value);
        }

        void _JWVCS___forwardEvent_11 (_JWVCS_State& _state, int32_t index, std_notes_NoteOn value) noexcept
        {
            VCSVoice__eventsIn_0 (_state.voices[index], value);
        }

        void VCSVoice__eventsIn_0 (_VCSVoice_1_State& _state, std_notes_NoteOn e) noexcept
        {
            _state.freq = std__notes__noteToFrequency (e.pitch);
            _state.vel = e.velocity;
            _state.active = true;
            _state.trapStage = int32_t {0};
            _state.trap = 0.0f;
            _state.trapOffT = 0.0f;
        }

        float std__notes__noteToFrequency (float midiNoteNumber) noexcept
        {
            return 440.0f * intrinsics::pow (2.0f, 0.083333336f * (midiNoteNumber - static_cast<float> (int32_t {69})));
        }

        float std__intrinsics__pow (float a, float b) noexcept
        {
            {
                return 0.0f;
            }
        }

        int32_t std__midi__getChannel0to15 (const std_midi_Message& this_) noexcept
        {
            return (this_.message >> int32_t {16}) & int32_t {15};
        }

        float std__midi__getPitch (const std_midi_Message& this_) noexcept
        {
            return static_cast<float> (std__midi__getNoteNumber (this_));
        }

        int32_t std__midi__getNoteNumber (const std_midi_Message& this_) noexcept
        {
            return (this_.message >> int32_t {8}) & int32_t {127};
        }

        float std__midi__getFloatVelocity (const std_midi_Message& this_) noexcept
        {
            return static_cast<float> (this_.message & int32_t {127}) * 0.007874016f;
        }

        bool std__midi__isNoteOff (const std_midi_Message& this_) noexcept
        {
            return ((this_.message & int32_t {0xf00000}) == int32_t {0x800000}) ? true : ((this_.message & int32_t {0xf000ff}) == int32_t {0x900000});
        }

        void std__midi__MPEConverter___writeEvent_eventOut_0 (std_midi_MPEConverter_1_State& _state, const std_notes_NoteOff& value) noexcept
        {
            _JWVCS___forwardEvent_2 (state_upcast_struct_JWVCS_State_struc_FEfOBc(_state), value);
            _JWVCS___forwardEvent_6 (state_upcast_struct_JWVCS_State_struc_FEfOBc(_state), value);
        }

        void _JWVCS___forwardEvent_2 (_JWVCS_State& _state, std_notes_NoteOff value) noexcept
        {
            NoteTap__eventsIn_0 (_state.noteTap, value);
        }

        void NoteTap__eventsIn_0 (std_midi_MPEConverter_1_State& _state, std_notes_NoteOff e) noexcept
        {
            plugincorp_NoteEvent  n;

            n = plugincorp_NoteEvent {};
            n.pitch = static_cast<int32_t> (e.pitch);
            n.on = int32_t {0};
            NoteTap___writeEvent_noteOut (_state, n);
        }

        void _JWVCS___forwardEvent_6 (_JWVCS_State& _state, std_notes_NoteOff value) noexcept
        {
            std__voices__VoiceAllocator__eventIn_0 (_state.voiceAllocator, value);
        }

        void std__voices__VoiceAllocator__eventIn_0 (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, std_notes_NoteOff noteOff) noexcept
        {
            int32_t  i;

            {
                i = {};
                for (;;)
                {
                    if (i >= int32_t {1})
                    {
                        break;
                    }
                    if ((_state.voiceState[i].channel == noteOff.channel) ? (_state.voiceState[i].pitch == noteOff.pitch) : false)
                    {
                        if (std__voices__VoiceAllocator__isSustainActive (_state, noteOff.channel))
                        {
                            _state.voiceState[i].isReleasing = true;
                        }
                        else
                        {
                            std__voices__VoiceAllocator___writeEvent_voiceEventOut (_state, std__intrinsics___wrap_1 (i), noteOff);
                            std__voices__VoiceAllocator__free (_state, _state.voiceState[i]);
                        }
                    }
                    {
                        ++i;
                    }
                }
            }
        }

        bool std__voices__VoiceAllocator__isSustainActive (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, int32_t channel) noexcept
        {
            return _state.mpeMasterSustainActive ? true : ((_state.perChannelSustainActive & (int64_t {1L} << static_cast<int64_t> (channel))) != static_cast<int64_t> (int32_t {0}));
        }

        int32_t std__intrinsics___wrap_1 (int32_t n) noexcept
        {
            return n & int32_t {0};
        }

        void std__voices__VoiceAllocator__free (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_VoiceState& this_) noexcept
        {
            this_.isActive = false;
            ++_state.nextInactiveTime;
            this_.age = _state.nextInactiveTime;
        }

        bool std__midi__isPitchWheel (const std_midi_Message& this_) noexcept
        {
            return (this_.message & int32_t {0xf00000}) == int32_t {0xe00000};
        }

        void std__midi__MPEConverter___writeEvent_eventOut_1 (std_midi_MPEConverter_1_State& _state, const std_notes_PitchBend& value) noexcept
        {
            _JWVCS___forwardEvent_7 (state_upcast_struct_JWVCS_State_struc_FEfOBc(_state), value);
        }

        void _JWVCS___forwardEvent_7 (_JWVCS_State& _state, std_notes_PitchBend value) noexcept
        {
            std__voices__VoiceAllocator__eventIn_1 (_state.voiceAllocator, value);
        }

        void std__voices__VoiceAllocator__eventIn_1 (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, std_notes_PitchBend bend) noexcept
        {
            int32_t  i;

            {
                i = {};
                for (;;)
                {
                    if (i >= int32_t {1})
                    {
                        break;
                    }
                    if (_state.voiceState[i].channel == bend.channel)
                    {
                        std__voices__VoiceAllocator___writeEvent_voiceEventOut_1 (_state, std__intrinsics___wrap_1 (i), bend);
                    }
                    {
                        ++i;
                    }
                }
            }
        }

        void std__voices__VoiceAllocator___writeEvent_voiceEventOut_1 (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, int32_t index, const std_notes_PitchBend& value) noexcept
        {
        }

        int32_t std__midi__get14BitValue (const std_midi_Message& this_) noexcept
        {
            return ((this_.message >> int32_t {8}) & int32_t {127}) | ((this_.message & int32_t {127}) << int32_t {7});
        }

        bool std__midi__isChannelPressure (const std_midi_Message& this_) noexcept
        {
            return (this_.message & int32_t {0xf00000}) == int32_t {0xd00000};
        }

        void std__midi__MPEConverter___writeEvent_eventOut_2 (std_midi_MPEConverter_1_State& _state, const std_notes_Pressure& value) noexcept
        {
            _JWVCS___forwardEvent_9 (state_upcast_struct_JWVCS_State_struc_FEfOBc(_state), value);
        }

        void _JWVCS___forwardEvent_9 (_JWVCS_State& _state, std_notes_Pressure value) noexcept
        {
            std__voices__VoiceAllocator__eventIn_2 (_state.voiceAllocator, value);
        }

        void std__voices__VoiceAllocator__eventIn_2 (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, std_notes_Pressure pressure) noexcept
        {
            int32_t  i;

            {
                i = {};
                for (;;)
                {
                    if (i >= int32_t {1})
                    {
                        break;
                    }
                    if (_state.voiceState[i].channel == pressure.channel)
                    {
                        std__voices__VoiceAllocator___writeEvent_voiceEventOut_2 (_state, std__intrinsics___wrap_1 (i), pressure);
                    }
                    {
                        ++i;
                    }
                }
            }
        }

        void std__voices__VoiceAllocator___writeEvent_voiceEventOut_2 (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, int32_t index, const std_notes_Pressure& value) noexcept
        {
        }

        float std__midi__getFloatChannelPressureValue (const std_midi_Message& this_) noexcept
        {
            return static_cast<float> ((this_.message >> int32_t {8}) & int32_t {127}) * 0.007874016f;
        }

        bool std__midi__isController (const std_midi_Message& this_) noexcept
        {
            return (this_.message & int32_t {0xf00000}) == int32_t {0xb00000};
        }

        int32_t std__midi__getControllerNumber (const std_midi_Message& this_) noexcept
        {
            return (this_.message >> int32_t {8}) & int32_t {127};
        }

        void std__midi__MPEConverter___writeEvent_eventOut_3 (std_midi_MPEConverter_1_State& _state, const std_notes_Slide& value) noexcept
        {
            _JWVCS___forwardEvent_8 (state_upcast_struct_JWVCS_State_struc_FEfOBc(_state), value);
        }

        void _JWVCS___forwardEvent_8 (_JWVCS_State& _state, std_notes_Slide value) noexcept
        {
            std__voices__VoiceAllocator__eventIn_3 (_state.voiceAllocator, value);
        }

        void std__voices__VoiceAllocator__eventIn_3 (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, std_notes_Slide slide) noexcept
        {
            int32_t  i;

            {
                i = {};
                for (;;)
                {
                    if (i >= int32_t {1})
                    {
                        break;
                    }
                    if (_state.voiceState[i].channel == slide.channel)
                    {
                        std__voices__VoiceAllocator___writeEvent_voiceEventOut_3 (_state, std__intrinsics___wrap_1 (i), slide);
                    }
                    {
                        ++i;
                    }
                }
            }
        }

        void std__voices__VoiceAllocator___writeEvent_voiceEventOut_3 (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, int32_t index, const std_notes_Slide& value) noexcept
        {
        }

        float std__midi__getFloatControllerValue (const std_midi_Message& this_) noexcept
        {
            return static_cast<float> (this_.message & int32_t {127}) * 0.007874016f;
        }

        void std__midi__MPEConverter___writeEvent_eventOut_4 (std_midi_MPEConverter_1_State& _state, const std_notes_Control& value) noexcept
        {
            _JWVCS___forwardEvent_10 (state_upcast_struct_JWVCS_State_struc_FEfOBc(_state), value);
        }

        void _JWVCS___forwardEvent_10 (_JWVCS_State& _state, std_notes_Control value) noexcept
        {
            std__voices__VoiceAllocator__eventIn_4 (_state.voiceAllocator, value);
        }

        void std__voices__VoiceAllocator__eventIn_4 (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, std_notes_Control control) noexcept
        {
            bool  isMPEMasterChannel;
            bool  sustainActive;
            int32_t  i;
            std_notes_NoteOff  _temp;
            std_notes_NoteOff  _temp_0;
            int32_t  i_0;

            if (control.control == int32_t {64})
            {
                isMPEMasterChannel = control.channel == g_MPEMasterChannel;
                sustainActive = control.value >= 0.5f;
                std__voices__VoiceAllocator__setChannelSustain (_state, control.channel, sustainActive);
                if (isMPEMasterChannel)
                {
                    _state.mpeMasterSustainActive = sustainActive;
                }
                if (! sustainActive)
                {
                    {
                        i = {};
                        for (;;)
                        {
                            if (i >= int32_t {1})
                            {
                                break;
                            }
                            if (((isMPEMasterChannel ? true : (_state.voiceState[i].channel == control.channel)) ? _state.voiceState[i].isActive : false) ? _state.voiceState[i].isReleasing : false)
                            {
                                _temp.channel = _state.voiceState[i].channel;
                                _temp.pitch = _state.voiceState[i].pitch;
                                _temp.velocity = 0.0f;
                                _temp_0 = _temp;
                                std__voices__VoiceAllocator___writeEvent_voiceEventOut (_state, std__intrinsics___wrap_1 (i), _temp_0);
                                std__voices__VoiceAllocator__free (_state, _state.voiceState[i]);
                            }
                            {
                                ++i;
                            }
                        }
                    }
                }
            }
            else
            {
                {
                    i_0 = {};
                    for (;;)
                    {
                        if (i_0 >= int32_t {1})
                        {
                            break;
                        }
                        if (_state.voiceState[i_0].channel == control.channel)
                        {
                            std__voices__VoiceAllocator___writeEvent_voiceEventOut_4 (_state, std__intrinsics___wrap_1 (i_0), control);
                        }
                        {
                            ++i_0;
                        }
                    }
                }
            }
        }

        void std__voices__VoiceAllocator__setChannelSustain (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, int32_t channel, bool active) noexcept
        {
            if (active)
            {
                _state.perChannelSustainActive = (_state.perChannelSustainActive | (int64_t {1L} << static_cast<int64_t> (channel)));
            }
            else
            {
                _state.perChannelSustainActive = (_state.perChannelSustainActive & (~ (int64_t {1L} << static_cast<int64_t> (channel))));
            }
        }

        void std__voices__VoiceAllocator___writeEvent_voiceEventOut_4 (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, int32_t index, const std_notes_Control& value) noexcept
        {
        }

        void _sendEvent_o1Freq (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o1Freq (_state._state, value);
        }

        void _JWVCS__o1Freq (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o1Freq (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o1Freq (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o1Freq = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void ParamsProcessor__seed (_ParamsProcessor_1_State& _state) noexcept
        {
            _state.params.o1Freq = 0.4f;
            _state.params.o1Range = 0.5f;
            _state.params.o1Sine = 0.3f;
            _state.params.o1Saw = 0.7f;
            _state.params.o2Freq = 0.42f;
            _state.params.o2Range = 0.5f;
            _state.params.o2Shape = 0.6f;
            _state.params.o2Pw = 0.45f;
            _state.params.o2Level = 0.6f;
            _state.params.o3Freq = 0.3f;
            _state.params.o3Range = 0.18f;
            _state.params.o3Shape = 0.0f;
            _state.params.o3Pw = 0.5f;
            _state.params.o3Level = 0.4f;
            _state.params.drift = 0.28f;
            _state.params.noise = 0.3f;
            _state.params.cutoff = 0.58f;
            _state.params.reso = 0.42f;
            _state.params.fKeyTrack = 0.4f;
            _state.params.trapA = 0.06f;
            _state.params.trapOn = 0.3f;
            _state.params.trapD = 0.4f;
            _state.params.trapOff = 1.0f;
            _state.params.reverb = 0.3f;
            _state.params.mx[int32_t {4}] = 1.0f;
            _state.params.mx[int32_t {20}] = 0.7f;
            _state.params.mx[int32_t {52}] = 0.2f;
            _state.params.mx[int32_t {86}] = 0.18f;
            _state.params.mx[int32_t {87}] = 1.0f;
            _state.params.mx[int32_t {103}] = 0.28f;
            _state.params.mx[int32_t {117}] = 0.55f;
            _state.params.joyX = 0.5f;
            _state.params.joyY = 0.5f;
            _state.params.volume = 0.8f;
            _state.params.tune = 0.5f;
            _state.seeded = true;
        }

        void ParamsProcessor___writeEvent_paramsOut (_ParamsProcessor_1_State& _state, const plugincorp_Params& value) noexcept
        {
            _JWVCS___forwardEvent_4 (state_upcast_struct_JWVCS_State_struc_djBVBe(_state), value);
        }

        void _JWVCS___forwardEvent_4 (_JWVCS_State& _state, plugincorp_Params value) noexcept
        {
            VCSVoice__paramsIn (_state.voices[int32_t {0}], value);
        }

        void VCSVoice__paramsIn (_VCSVoice_1_State& _state, plugincorp_Params p) noexcept
        {
            _state.params = p;
        }

        void _sendEvent_o1Range (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o1Range (_state._state, value);
        }

        void _JWVCS__o1Range (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o1Range (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o1Range (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o1Range = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o1Sine (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o1Sine (_state._state, value);
        }

        void _JWVCS__o1Sine (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o1Sine (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o1Sine (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o1Sine = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o1Saw (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o1Saw (_state._state, value);
        }

        void _JWVCS__o1Saw (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o1Saw (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o1Saw (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o1Saw = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o2Freq (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o2Freq (_state._state, value);
        }

        void _JWVCS__o2Freq (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o2Freq (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o2Freq (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o2Freq = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o2Range (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o2Range (_state._state, value);
        }

        void _JWVCS__o2Range (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o2Range (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o2Range (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o2Range = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o2Shape (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o2Shape (_state._state, value);
        }

        void _JWVCS__o2Shape (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o2Shape (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o2Shape (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o2Shape = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o2Pw (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o2Pw (_state._state, value);
        }

        void _JWVCS__o2Pw (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o2Pw (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o2Pw (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o2Pw = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o2Level (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o2Level (_state._state, value);
        }

        void _JWVCS__o2Level (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o2Level (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o2Level (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o2Level = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o3Freq (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o3Freq (_state._state, value);
        }

        void _JWVCS__o3Freq (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o3Freq (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o3Freq (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o3Freq = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o3Range (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o3Range (_state._state, value);
        }

        void _JWVCS__o3Range (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o3Range (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o3Range (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o3Range = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o3Shape (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o3Shape (_state._state, value);
        }

        void _JWVCS__o3Shape (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o3Shape (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o3Shape (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o3Shape = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o3Pw (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o3Pw (_state._state, value);
        }

        void _JWVCS__o3Pw (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o3Pw (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o3Pw (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o3Pw = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o3Level (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__o3Level (_state._state, value);
        }

        void _JWVCS__o3Level (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__o3Level (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o3Level (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.o3Level = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_drift (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__drift (_state._state, value);
        }

        void _JWVCS__drift (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__drift (_state.paramsProcessor, value);
        }

        void ParamsProcessor__drift (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.drift = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_noise (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__noise (_state._state, value);
        }

        void _JWVCS__noise (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__noise (_state.paramsProcessor, value);
        }

        void ParamsProcessor__noise (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.noise = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_cutoff (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__cutoff (_state._state, value);
        }

        void _JWVCS__cutoff (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__cutoff (_state.paramsProcessor, value);
        }

        void ParamsProcessor__cutoff (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.cutoff = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_reso (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__reso (_state._state, value);
        }

        void _JWVCS__reso (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__reso (_state.paramsProcessor, value);
        }

        void ParamsProcessor__reso (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.reso = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_fKeyTrack (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__fKeyTrack (_state._state, value);
        }

        void _JWVCS__fKeyTrack (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__fKeyTrack (_state.paramsProcessor, value);
        }

        void ParamsProcessor__fKeyTrack (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.fKeyTrack = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_trapA (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__trapA (_state._state, value);
        }

        void _JWVCS__trapA (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__trapA (_state.paramsProcessor, value);
        }

        void ParamsProcessor__trapA (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.trapA = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_trapOn (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__trapOn (_state._state, value);
        }

        void _JWVCS__trapOn (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__trapOn (_state.paramsProcessor, value);
        }

        void ParamsProcessor__trapOn (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.trapOn = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_trapD (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__trapD (_state._state, value);
        }

        void _JWVCS__trapD (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__trapD (_state.paramsProcessor, value);
        }

        void ParamsProcessor__trapD (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.trapD = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_trapOff (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__trapOff (_state._state, value);
        }

        void _JWVCS__trapOff (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__trapOff (_state.paramsProcessor, value);
        }

        void ParamsProcessor__trapOff (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.trapOff = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_reverb (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__reverb (_state._state, value);
        }

        void _JWVCS__reverb (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__reverb (_state.paramsProcessor, value);
        }

        void ParamsProcessor__reverb (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.reverb = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_mx00 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx00 (_state._state, value);
        }

        void _JWVCS__mx00 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx00 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx00 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {0}, v);
        }

        void ParamsProcessor__setMx (_ParamsProcessor_1_State& _state, int32_t idx, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.mx[std__intrinsics___wrap_160 (idx)] = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        int32_t std__intrinsics___wrap_160 (int32_t n) noexcept
        {
            int32_t  x;

            x = intrinsics::modulo (n, int32_t {160});
            return (x < int32_t {0}) ? (x + int32_t {160}) : x;
        }

        void _sendEvent_mx01 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx01 (_state._state, value);
        }

        void _JWVCS__mx01 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx01 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx01 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {1}, v);
        }

        void _sendEvent_mx02 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx02 (_state._state, value);
        }

        void _JWVCS__mx02 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx02 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx02 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {2}, v);
        }

        void _sendEvent_mx03 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx03 (_state._state, value);
        }

        void _JWVCS__mx03 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx03 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx03 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {3}, v);
        }

        void _sendEvent_mx04 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx04 (_state._state, value);
        }

        void _JWVCS__mx04 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx04 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx04 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {4}, v);
        }

        void _sendEvent_mx05 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx05 (_state._state, value);
        }

        void _JWVCS__mx05 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx05 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx05 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {5}, v);
        }

        void _sendEvent_mx06 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx06 (_state._state, value);
        }

        void _JWVCS__mx06 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx06 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx06 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {6}, v);
        }

        void _sendEvent_mx07 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx07 (_state._state, value);
        }

        void _JWVCS__mx07 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx07 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx07 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {7}, v);
        }

        void _sendEvent_mx08 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx08 (_state._state, value);
        }

        void _JWVCS__mx08 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx08 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx08 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {8}, v);
        }

        void _sendEvent_mx09 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx09 (_state._state, value);
        }

        void _JWVCS__mx09 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx09 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx09 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {9}, v);
        }

        void _sendEvent_mx0A (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx0A (_state._state, value);
        }

        void _JWVCS__mx0A (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx0A (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx0A (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {10}, v);
        }

        void _sendEvent_mx0B (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx0B (_state._state, value);
        }

        void _JWVCS__mx0B (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx0B (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx0B (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {11}, v);
        }

        void _sendEvent_mx0C (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx0C (_state._state, value);
        }

        void _JWVCS__mx0C (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx0C (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx0C (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {12}, v);
        }

        void _sendEvent_mx0D (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx0D (_state._state, value);
        }

        void _JWVCS__mx0D (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx0D (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx0D (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {13}, v);
        }

        void _sendEvent_mx0E (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx0E (_state._state, value);
        }

        void _JWVCS__mx0E (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx0E (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx0E (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {14}, v);
        }

        void _sendEvent_mx0F (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx0F (_state._state, value);
        }

        void _JWVCS__mx0F (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx0F (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx0F (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {15}, v);
        }

        void _sendEvent_mx10 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx10 (_state._state, value);
        }

        void _JWVCS__mx10 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx10 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx10 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {16}, v);
        }

        void _sendEvent_mx11 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx11 (_state._state, value);
        }

        void _JWVCS__mx11 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx11 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx11 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {17}, v);
        }

        void _sendEvent_mx12 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx12 (_state._state, value);
        }

        void _JWVCS__mx12 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx12 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx12 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {18}, v);
        }

        void _sendEvent_mx13 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx13 (_state._state, value);
        }

        void _JWVCS__mx13 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx13 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx13 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {19}, v);
        }

        void _sendEvent_mx14 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx14 (_state._state, value);
        }

        void _JWVCS__mx14 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx14 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx14 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {20}, v);
        }

        void _sendEvent_mx15 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx15 (_state._state, value);
        }

        void _JWVCS__mx15 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx15 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx15 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {21}, v);
        }

        void _sendEvent_mx16 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx16 (_state._state, value);
        }

        void _JWVCS__mx16 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx16 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx16 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {22}, v);
        }

        void _sendEvent_mx17 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx17 (_state._state, value);
        }

        void _JWVCS__mx17 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx17 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx17 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {23}, v);
        }

        void _sendEvent_mx18 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx18 (_state._state, value);
        }

        void _JWVCS__mx18 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx18 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx18 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {24}, v);
        }

        void _sendEvent_mx19 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx19 (_state._state, value);
        }

        void _JWVCS__mx19 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx19 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx19 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {25}, v);
        }

        void _sendEvent_mx1A (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx1A (_state._state, value);
        }

        void _JWVCS__mx1A (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx1A (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx1A (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {26}, v);
        }

        void _sendEvent_mx1B (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx1B (_state._state, value);
        }

        void _JWVCS__mx1B (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx1B (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx1B (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {27}, v);
        }

        void _sendEvent_mx1C (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx1C (_state._state, value);
        }

        void _JWVCS__mx1C (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx1C (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx1C (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {28}, v);
        }

        void _sendEvent_mx1D (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx1D (_state._state, value);
        }

        void _JWVCS__mx1D (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx1D (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx1D (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {29}, v);
        }

        void _sendEvent_mx1E (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx1E (_state._state, value);
        }

        void _JWVCS__mx1E (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx1E (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx1E (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {30}, v);
        }

        void _sendEvent_mx1F (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx1F (_state._state, value);
        }

        void _JWVCS__mx1F (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx1F (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx1F (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {31}, v);
        }

        void _sendEvent_mx20 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx20 (_state._state, value);
        }

        void _JWVCS__mx20 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx20 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx20 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {32}, v);
        }

        void _sendEvent_mx21 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx21 (_state._state, value);
        }

        void _JWVCS__mx21 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx21 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx21 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {33}, v);
        }

        void _sendEvent_mx22 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx22 (_state._state, value);
        }

        void _JWVCS__mx22 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx22 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx22 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {34}, v);
        }

        void _sendEvent_mx23 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx23 (_state._state, value);
        }

        void _JWVCS__mx23 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx23 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx23 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {35}, v);
        }

        void _sendEvent_mx24 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx24 (_state._state, value);
        }

        void _JWVCS__mx24 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx24 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx24 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {36}, v);
        }

        void _sendEvent_mx25 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx25 (_state._state, value);
        }

        void _JWVCS__mx25 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx25 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx25 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {37}, v);
        }

        void _sendEvent_mx26 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx26 (_state._state, value);
        }

        void _JWVCS__mx26 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx26 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx26 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {38}, v);
        }

        void _sendEvent_mx27 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx27 (_state._state, value);
        }

        void _JWVCS__mx27 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx27 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx27 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {39}, v);
        }

        void _sendEvent_mx28 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx28 (_state._state, value);
        }

        void _JWVCS__mx28 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx28 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx28 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {40}, v);
        }

        void _sendEvent_mx29 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx29 (_state._state, value);
        }

        void _JWVCS__mx29 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx29 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx29 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {41}, v);
        }

        void _sendEvent_mx2A (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx2A (_state._state, value);
        }

        void _JWVCS__mx2A (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx2A (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx2A (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {42}, v);
        }

        void _sendEvent_mx2B (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx2B (_state._state, value);
        }

        void _JWVCS__mx2B (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx2B (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx2B (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {43}, v);
        }

        void _sendEvent_mx2C (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx2C (_state._state, value);
        }

        void _JWVCS__mx2C (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx2C (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx2C (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {44}, v);
        }

        void _sendEvent_mx2D (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx2D (_state._state, value);
        }

        void _JWVCS__mx2D (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx2D (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx2D (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {45}, v);
        }

        void _sendEvent_mx2E (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx2E (_state._state, value);
        }

        void _JWVCS__mx2E (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx2E (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx2E (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {46}, v);
        }

        void _sendEvent_mx2F (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx2F (_state._state, value);
        }

        void _JWVCS__mx2F (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx2F (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx2F (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {47}, v);
        }

        void _sendEvent_mx30 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx30 (_state._state, value);
        }

        void _JWVCS__mx30 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx30 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx30 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {48}, v);
        }

        void _sendEvent_mx31 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx31 (_state._state, value);
        }

        void _JWVCS__mx31 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx31 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx31 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {49}, v);
        }

        void _sendEvent_mx32 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx32 (_state._state, value);
        }

        void _JWVCS__mx32 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx32 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx32 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {50}, v);
        }

        void _sendEvent_mx33 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx33 (_state._state, value);
        }

        void _JWVCS__mx33 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx33 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx33 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {51}, v);
        }

        void _sendEvent_mx34 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx34 (_state._state, value);
        }

        void _JWVCS__mx34 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx34 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx34 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {52}, v);
        }

        void _sendEvent_mx35 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx35 (_state._state, value);
        }

        void _JWVCS__mx35 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx35 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx35 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {53}, v);
        }

        void _sendEvent_mx36 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx36 (_state._state, value);
        }

        void _JWVCS__mx36 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx36 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx36 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {54}, v);
        }

        void _sendEvent_mx37 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx37 (_state._state, value);
        }

        void _JWVCS__mx37 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx37 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx37 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {55}, v);
        }

        void _sendEvent_mx38 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx38 (_state._state, value);
        }

        void _JWVCS__mx38 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx38 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx38 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {56}, v);
        }

        void _sendEvent_mx39 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx39 (_state._state, value);
        }

        void _JWVCS__mx39 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx39 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx39 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {57}, v);
        }

        void _sendEvent_mx3A (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx3A (_state._state, value);
        }

        void _JWVCS__mx3A (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx3A (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx3A (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {58}, v);
        }

        void _sendEvent_mx3B (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx3B (_state._state, value);
        }

        void _JWVCS__mx3B (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx3B (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx3B (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {59}, v);
        }

        void _sendEvent_mx3C (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx3C (_state._state, value);
        }

        void _JWVCS__mx3C (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx3C (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx3C (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {60}, v);
        }

        void _sendEvent_mx3D (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx3D (_state._state, value);
        }

        void _JWVCS__mx3D (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx3D (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx3D (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {61}, v);
        }

        void _sendEvent_mx3E (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx3E (_state._state, value);
        }

        void _JWVCS__mx3E (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx3E (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx3E (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {62}, v);
        }

        void _sendEvent_mx3F (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx3F (_state._state, value);
        }

        void _JWVCS__mx3F (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx3F (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx3F (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {63}, v);
        }

        void _sendEvent_mx40 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx40 (_state._state, value);
        }

        void _JWVCS__mx40 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx40 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx40 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {64}, v);
        }

        void _sendEvent_mx41 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx41 (_state._state, value);
        }

        void _JWVCS__mx41 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx41 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx41 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {65}, v);
        }

        void _sendEvent_mx42 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx42 (_state._state, value);
        }

        void _JWVCS__mx42 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx42 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx42 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {66}, v);
        }

        void _sendEvent_mx43 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx43 (_state._state, value);
        }

        void _JWVCS__mx43 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx43 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx43 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {67}, v);
        }

        void _sendEvent_mx44 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx44 (_state._state, value);
        }

        void _JWVCS__mx44 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx44 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx44 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {68}, v);
        }

        void _sendEvent_mx45 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx45 (_state._state, value);
        }

        void _JWVCS__mx45 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx45 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx45 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {69}, v);
        }

        void _sendEvent_mx46 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx46 (_state._state, value);
        }

        void _JWVCS__mx46 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx46 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx46 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {70}, v);
        }

        void _sendEvent_mx47 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx47 (_state._state, value);
        }

        void _JWVCS__mx47 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx47 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx47 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {71}, v);
        }

        void _sendEvent_mx48 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx48 (_state._state, value);
        }

        void _JWVCS__mx48 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx48 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx48 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {72}, v);
        }

        void _sendEvent_mx49 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx49 (_state._state, value);
        }

        void _JWVCS__mx49 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx49 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx49 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {73}, v);
        }

        void _sendEvent_mx4A (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx4A (_state._state, value);
        }

        void _JWVCS__mx4A (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx4A (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx4A (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {74}, v);
        }

        void _sendEvent_mx4B (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx4B (_state._state, value);
        }

        void _JWVCS__mx4B (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx4B (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx4B (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {75}, v);
        }

        void _sendEvent_mx4C (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx4C (_state._state, value);
        }

        void _JWVCS__mx4C (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx4C (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx4C (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {76}, v);
        }

        void _sendEvent_mx4D (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx4D (_state._state, value);
        }

        void _JWVCS__mx4D (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx4D (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx4D (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {77}, v);
        }

        void _sendEvent_mx4E (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx4E (_state._state, value);
        }

        void _JWVCS__mx4E (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx4E (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx4E (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {78}, v);
        }

        void _sendEvent_mx4F (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx4F (_state._state, value);
        }

        void _JWVCS__mx4F (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx4F (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx4F (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {79}, v);
        }

        void _sendEvent_mx50 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx50 (_state._state, value);
        }

        void _JWVCS__mx50 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx50 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx50 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {80}, v);
        }

        void _sendEvent_mx51 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx51 (_state._state, value);
        }

        void _JWVCS__mx51 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx51 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx51 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {81}, v);
        }

        void _sendEvent_mx52 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx52 (_state._state, value);
        }

        void _JWVCS__mx52 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx52 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx52 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {82}, v);
        }

        void _sendEvent_mx53 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx53 (_state._state, value);
        }

        void _JWVCS__mx53 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx53 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx53 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {83}, v);
        }

        void _sendEvent_mx54 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx54 (_state._state, value);
        }

        void _JWVCS__mx54 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx54 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx54 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {84}, v);
        }

        void _sendEvent_mx55 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx55 (_state._state, value);
        }

        void _JWVCS__mx55 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx55 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx55 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {85}, v);
        }

        void _sendEvent_mx56 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx56 (_state._state, value);
        }

        void _JWVCS__mx56 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx56 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx56 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {86}, v);
        }

        void _sendEvent_mx57 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx57 (_state._state, value);
        }

        void _JWVCS__mx57 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx57 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx57 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {87}, v);
        }

        void _sendEvent_mx58 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx58 (_state._state, value);
        }

        void _JWVCS__mx58 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx58 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx58 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {88}, v);
        }

        void _sendEvent_mx59 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx59 (_state._state, value);
        }

        void _JWVCS__mx59 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx59 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx59 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {89}, v);
        }

        void _sendEvent_mx5A (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx5A (_state._state, value);
        }

        void _JWVCS__mx5A (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx5A (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx5A (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {90}, v);
        }

        void _sendEvent_mx5B (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx5B (_state._state, value);
        }

        void _JWVCS__mx5B (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx5B (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx5B (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {91}, v);
        }

        void _sendEvent_mx5C (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx5C (_state._state, value);
        }

        void _JWVCS__mx5C (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx5C (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx5C (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {92}, v);
        }

        void _sendEvent_mx5D (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx5D (_state._state, value);
        }

        void _JWVCS__mx5D (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx5D (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx5D (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {93}, v);
        }

        void _sendEvent_mx5E (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx5E (_state._state, value);
        }

        void _JWVCS__mx5E (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx5E (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx5E (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {94}, v);
        }

        void _sendEvent_mx5F (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx5F (_state._state, value);
        }

        void _JWVCS__mx5F (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx5F (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx5F (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {95}, v);
        }

        void _sendEvent_mx60 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx60 (_state._state, value);
        }

        void _JWVCS__mx60 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx60 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx60 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {96}, v);
        }

        void _sendEvent_mx61 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx61 (_state._state, value);
        }

        void _JWVCS__mx61 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx61 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx61 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {97}, v);
        }

        void _sendEvent_mx62 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx62 (_state._state, value);
        }

        void _JWVCS__mx62 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx62 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx62 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {98}, v);
        }

        void _sendEvent_mx63 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx63 (_state._state, value);
        }

        void _JWVCS__mx63 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx63 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx63 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {99}, v);
        }

        void _sendEvent_mx64 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx64 (_state._state, value);
        }

        void _JWVCS__mx64 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx64 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx64 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {100}, v);
        }

        void _sendEvent_mx65 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx65 (_state._state, value);
        }

        void _JWVCS__mx65 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx65 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx65 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {101}, v);
        }

        void _sendEvent_mx66 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx66 (_state._state, value);
        }

        void _JWVCS__mx66 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx66 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx66 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {102}, v);
        }

        void _sendEvent_mx67 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx67 (_state._state, value);
        }

        void _JWVCS__mx67 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx67 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx67 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {103}, v);
        }

        void _sendEvent_mx68 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx68 (_state._state, value);
        }

        void _JWVCS__mx68 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx68 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx68 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {104}, v);
        }

        void _sendEvent_mx69 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx69 (_state._state, value);
        }

        void _JWVCS__mx69 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx69 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx69 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {105}, v);
        }

        void _sendEvent_mx6A (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx6A (_state._state, value);
        }

        void _JWVCS__mx6A (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx6A (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx6A (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {106}, v);
        }

        void _sendEvent_mx6B (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx6B (_state._state, value);
        }

        void _JWVCS__mx6B (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx6B (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx6B (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {107}, v);
        }

        void _sendEvent_mx6C (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx6C (_state._state, value);
        }

        void _JWVCS__mx6C (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx6C (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx6C (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {108}, v);
        }

        void _sendEvent_mx6D (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx6D (_state._state, value);
        }

        void _JWVCS__mx6D (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx6D (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx6D (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {109}, v);
        }

        void _sendEvent_mx6E (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx6E (_state._state, value);
        }

        void _JWVCS__mx6E (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx6E (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx6E (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {110}, v);
        }

        void _sendEvent_mx6F (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx6F (_state._state, value);
        }

        void _JWVCS__mx6F (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx6F (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx6F (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {111}, v);
        }

        void _sendEvent_mx70 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx70 (_state._state, value);
        }

        void _JWVCS__mx70 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx70 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx70 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {112}, v);
        }

        void _sendEvent_mx71 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx71 (_state._state, value);
        }

        void _JWVCS__mx71 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx71 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx71 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {113}, v);
        }

        void _sendEvent_mx72 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx72 (_state._state, value);
        }

        void _JWVCS__mx72 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx72 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx72 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {114}, v);
        }

        void _sendEvent_mx73 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx73 (_state._state, value);
        }

        void _JWVCS__mx73 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx73 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx73 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {115}, v);
        }

        void _sendEvent_mx74 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx74 (_state._state, value);
        }

        void _JWVCS__mx74 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx74 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx74 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {116}, v);
        }

        void _sendEvent_mx75 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx75 (_state._state, value);
        }

        void _JWVCS__mx75 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx75 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx75 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {117}, v);
        }

        void _sendEvent_mx76 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx76 (_state._state, value);
        }

        void _JWVCS__mx76 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx76 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx76 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {118}, v);
        }

        void _sendEvent_mx77 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx77 (_state._state, value);
        }

        void _JWVCS__mx77 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx77 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx77 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {119}, v);
        }

        void _sendEvent_mx78 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx78 (_state._state, value);
        }

        void _JWVCS__mx78 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx78 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx78 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {120}, v);
        }

        void _sendEvent_mx79 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx79 (_state._state, value);
        }

        void _JWVCS__mx79 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx79 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx79 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {121}, v);
        }

        void _sendEvent_mx7A (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx7A (_state._state, value);
        }

        void _JWVCS__mx7A (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx7A (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx7A (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {122}, v);
        }

        void _sendEvent_mx7B (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx7B (_state._state, value);
        }

        void _JWVCS__mx7B (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx7B (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx7B (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {123}, v);
        }

        void _sendEvent_mx7C (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx7C (_state._state, value);
        }

        void _JWVCS__mx7C (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx7C (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx7C (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {124}, v);
        }

        void _sendEvent_mx7D (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx7D (_state._state, value);
        }

        void _JWVCS__mx7D (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx7D (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx7D (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {125}, v);
        }

        void _sendEvent_mx7E (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx7E (_state._state, value);
        }

        void _JWVCS__mx7E (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx7E (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx7E (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {126}, v);
        }

        void _sendEvent_mx7F (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx7F (_state._state, value);
        }

        void _JWVCS__mx7F (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx7F (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx7F (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {127}, v);
        }

        void _sendEvent_mx80 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx80 (_state._state, value);
        }

        void _JWVCS__mx80 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx80 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx80 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {128}, v);
        }

        void _sendEvent_mx81 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx81 (_state._state, value);
        }

        void _JWVCS__mx81 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx81 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx81 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {129}, v);
        }

        void _sendEvent_mx82 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx82 (_state._state, value);
        }

        void _JWVCS__mx82 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx82 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx82 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {130}, v);
        }

        void _sendEvent_mx83 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx83 (_state._state, value);
        }

        void _JWVCS__mx83 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx83 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx83 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {131}, v);
        }

        void _sendEvent_mx84 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx84 (_state._state, value);
        }

        void _JWVCS__mx84 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx84 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx84 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {132}, v);
        }

        void _sendEvent_mx85 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx85 (_state._state, value);
        }

        void _JWVCS__mx85 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx85 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx85 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {133}, v);
        }

        void _sendEvent_mx86 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx86 (_state._state, value);
        }

        void _JWVCS__mx86 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx86 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx86 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {134}, v);
        }

        void _sendEvent_mx87 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx87 (_state._state, value);
        }

        void _JWVCS__mx87 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx87 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx87 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {135}, v);
        }

        void _sendEvent_mx88 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx88 (_state._state, value);
        }

        void _JWVCS__mx88 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx88 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx88 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {136}, v);
        }

        void _sendEvent_mx89 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx89 (_state._state, value);
        }

        void _JWVCS__mx89 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx89 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx89 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {137}, v);
        }

        void _sendEvent_mx8A (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx8A (_state._state, value);
        }

        void _JWVCS__mx8A (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx8A (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx8A (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {138}, v);
        }

        void _sendEvent_mx8B (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx8B (_state._state, value);
        }

        void _JWVCS__mx8B (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx8B (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx8B (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {139}, v);
        }

        void _sendEvent_mx8C (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx8C (_state._state, value);
        }

        void _JWVCS__mx8C (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx8C (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx8C (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {140}, v);
        }

        void _sendEvent_mx8D (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx8D (_state._state, value);
        }

        void _JWVCS__mx8D (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx8D (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx8D (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {141}, v);
        }

        void _sendEvent_mx8E (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx8E (_state._state, value);
        }

        void _JWVCS__mx8E (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx8E (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx8E (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {142}, v);
        }

        void _sendEvent_mx8F (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx8F (_state._state, value);
        }

        void _JWVCS__mx8F (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx8F (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx8F (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {143}, v);
        }

        void _sendEvent_mx90 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx90 (_state._state, value);
        }

        void _JWVCS__mx90 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx90 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx90 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {144}, v);
        }

        void _sendEvent_mx91 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx91 (_state._state, value);
        }

        void _JWVCS__mx91 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx91 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx91 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {145}, v);
        }

        void _sendEvent_mx92 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx92 (_state._state, value);
        }

        void _JWVCS__mx92 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx92 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx92 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {146}, v);
        }

        void _sendEvent_mx93 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx93 (_state._state, value);
        }

        void _JWVCS__mx93 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx93 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx93 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {147}, v);
        }

        void _sendEvent_mx94 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx94 (_state._state, value);
        }

        void _JWVCS__mx94 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx94 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx94 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {148}, v);
        }

        void _sendEvent_mx95 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx95 (_state._state, value);
        }

        void _JWVCS__mx95 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx95 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx95 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {149}, v);
        }

        void _sendEvent_mx96 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx96 (_state._state, value);
        }

        void _JWVCS__mx96 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx96 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx96 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {150}, v);
        }

        void _sendEvent_mx97 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx97 (_state._state, value);
        }

        void _JWVCS__mx97 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx97 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx97 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {151}, v);
        }

        void _sendEvent_mx98 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx98 (_state._state, value);
        }

        void _JWVCS__mx98 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx98 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx98 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {152}, v);
        }

        void _sendEvent_mx99 (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx99 (_state._state, value);
        }

        void _JWVCS__mx99 (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx99 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx99 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {153}, v);
        }

        void _sendEvent_mx9A (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx9A (_state._state, value);
        }

        void _JWVCS__mx9A (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx9A (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx9A (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {154}, v);
        }

        void _sendEvent_mx9B (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx9B (_state._state, value);
        }

        void _JWVCS__mx9B (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx9B (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx9B (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {155}, v);
        }

        void _sendEvent_mx9C (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx9C (_state._state, value);
        }

        void _JWVCS__mx9C (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx9C (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx9C (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {156}, v);
        }

        void _sendEvent_mx9D (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx9D (_state._state, value);
        }

        void _JWVCS__mx9D (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx9D (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx9D (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {157}, v);
        }

        void _sendEvent_mx9E (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx9E (_state._state, value);
        }

        void _JWVCS__mx9E (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx9E (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx9E (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {158}, v);
        }

        void _sendEvent_mx9F (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__mx9F (_state._state, value);
        }

        void _JWVCS__mx9F (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__mx9F (_state.paramsProcessor, value);
        }

        void ParamsProcessor__mx9F (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            ParamsProcessor__setMx (_state, int32_t {159}, v);
        }

        void _sendEvent_joyX (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__joyX (_state._state, value);
        }

        void _JWVCS__joyX (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__joyX (_state.paramsProcessor, value);
        }

        void ParamsProcessor__joyX (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.joyX = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_joyY (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__joyY (_state._state, value);
        }

        void _JWVCS__joyY (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__joyY (_state.paramsProcessor, value);
        }

        void ParamsProcessor__joyY (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.joyY = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_volume (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__volume (_state._state, value);
        }

        void _JWVCS__volume (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__volume (_state.paramsProcessor, value);
        }

        void ParamsProcessor__volume (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.volume = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_tune (JWVCS_State& _state, float value) noexcept
        {
            _JWVCS__tune (_state._state, value);
        }

        void _JWVCS__tune (_JWVCS_State& _state, float value) noexcept
        {
            ParamsProcessor__tune (_state.paramsProcessor, value);
        }

        void ParamsProcessor__tune (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            if (! _state.seeded)
            {
                ParamsProcessor__seed (_state);
            }
            _state.params.tune = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _initialise (JWVCS_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
        {
            _JWVCS___initialise (_state._state, processorID, sessionID, frequency);
        }

        void _JWVCS___initialise (_JWVCS_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
        {
            g__sessionID = sessionID;
            g__frequency = frequency;
            _state.voices[int32_t {0}]._instanceIndex = int32_t {0};
            VCSVoice___initialise (_state.voices[int32_t {0}], processorID, sessionID, frequency);
            std__voices__VoiceAllocator___initialise (_state.voiceAllocator, processorID, sessionID, frequency);
            ParamsProcessor___initialise (_state.paramsProcessor, processorID, sessionID, frequency);
            _initialise_0 (_state.mpe, processorID, sessionID, frequency);
            _initialise_1 (_state.noteTap, processorID, sessionID, frequency);
        }

        void VCSVoice___initialise (_VCSVoice_1_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
        {
            g__sessionID = sessionID;
            g__frequency = frequency;
            _state.rngc = int32_t {11};
            _state.freq = 110.0f;
            _state.vel = 0.0f;
            _state.active = false;
            _state.trapStage = int32_t {-1};
            _state.trap = 0.0f;
            _state.trapOffT = 0.0f;
            _state.drT1 = 0.0f;
            _state.drT2 = 0.0f;
            _state.drT3 = 0.0f;
            _state.dr1 = 0.0f;
            _state.dr2 = 0.0f;
            _state.dr3 = 0.0f;
            _state.ph1 = 0.0f;
            _state.ph2 = 0.0f;
            _state.ph3 = 0.0f;
            _state.dcx = 0.0f;
            _state.dcy = 0.0f;
            _state.lp4out = 0.0f;
            _state.lp1 = 0.0f;
            _state.lp2 = 0.0f;
            _state.lp3 = 0.0f;
            _state.lp4 = 0.0f;
            _state.filtPrev = 0.0f;
            _state.sap1 = 0.0f;
            _state.sap2 = 0.0f;
            _state.sdamp = 0.0f;
            _state.revPrev = 0.0f;
        }

        void std__voices__VoiceAllocator___initialise (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
        {
            g__sessionID = sessionID;
            g__frequency = frequency;
            _state.nextActiveTime = int32_t {0x70000000};
            _state.nextInactiveTime = int32_t {1};
        }

        void ParamsProcessor___initialise (_ParamsProcessor_1_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
        {
            g__sessionID = sessionID;
            g__frequency = frequency;
            _state.seeded = false;
        }

        void _initialise_0 (std_midi_MPEConverter_1_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
        {
        }

        void _initialise_1 (std_midi_MPEConverter_1_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
        {
        }

        void _advance (JWVCS_State& _state, JWVCS_IO& _io, int32_t _frames) noexcept
        {
            _JWVCS_IO  ioCopy;

            for (;;)
            {
                if (_state._currentFrame == _frames)
                {
                    break;
                }
                ioCopy = _JWVCS_IO {};
                main (_state._state, ioCopy);
                _io.audioOut[_state._currentFrame] = ioCopy.audioOut;
                ++_state._currentFrame;
            }
            _state._currentFrame = int32_t {0};
        }

        void main (_JWVCS_State& _state, _JWVCS_IO& _io) noexcept
        {
            Array<_VCSVoice_1_IO, 1>  voices_io;
            std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO  voiceAllocator_io;
            std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO  paramsProcessor_io;
            std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO  mpe_io;
            std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO  noteTap_io;
            Array<Vector<float, 2>, 1>  _temp;
            Vector<float, 2>  _temp_0;

            voices_io = Array<_VCSVoice_1_IO, 1> {};
            voiceAllocator_io = std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO {};
            paramsProcessor_io = std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO {};
            mpe_io = std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO {};
            noteTap_io = std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO {};
            {
            }
            main_0 (_state.paramsProcessor, paramsProcessor_io);
            {
            }
            main_1 (_state.mpe, mpe_io);
            {
            }
            main_2 (_state.voiceAllocator, voiceAllocator_io);
            {
            }
            VCSVoice__main (_state.voices[int32_t {0}], voices_io[int32_t {0}]);
            {
            }
            main_3 (_state.noteTap, noteTap_io);
            {
                _temp_0 = voices_io[int32_t {0}].voiceOut;
                _temp[int32_t {0}] = _temp_0;
                _io.audioOut = (_io.audioOut + _temp[int32_t {0}]);
            }
        }

        void main_0 (_ParamsProcessor_1_State& _state, std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO& _io) noexcept
        {
        }

        void main_1 (std_midi_MPEConverter_1_State& _state, std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO& _io) noexcept
        {
        }

        void main_2 (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& _state, std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO& _io) noexcept
        {
        }

        void VCSVoice__main (_VCSVoice_1_State& _state, _VCSVoice_1_IO& _io) noexcept
        {
            float  outL;
            float  outR;
            float  masterTune;
            float  baseF;
            float  driftAmt;
            float  aR;
            float  dR;
            float  onT;
            float  offT;
            float  trapCV;
            float  joyXcv;
            float  joyYcv;
            float  cvK;
            float  o1CV;
            float  o2CV;
            float  o3CV;
            float  filtCV;
            float  f1;
            float  f2;
            float  f3base;
            float  f3;
            float  inc1;
            float  inc2;
            float  inc3;
            float  o1;
            float  o2;
            float  o3;
            float  nz;
            float  ringP;
            float  ringQ;
            int32_t  r;
            float  g3;
            float  ringOut;
            float  filtIn;
            float  yb;
            float  kbd;
            float  fcOct;
            float  fc;
            float  fcSafe;
            float  g;
            float  G;
            float  k;
            float  fbc;
            float  fbk;
            float  inSat;
            float  y1;
            float  y2;
            float  y3;
            float  y4;
            float  knee;
            float  filtOut;
            float  revIn;
            float  x;
            float  g1;
            float  n1;
            float  o_ap1;
            float  g2;
            float  n2;
            float  o_ap2;
            float  dly;
            float  dly2;
            float  mix;
            float  revOut;
            float  sig;
            float  amp;
            float  o;
            Vector<float, 2>  _temp;

            switch (_state._resumeIndex)
            {
                case 1: goto _branch0_0;
                default: break;
            }

            _state.sr = static_cast<float> (1.0 * g__frequency);
            _state.invSr = (1.0f / _state.sr);
            _state.ny = (_state.sr * 0.45f);
            _branch0_0:
            {
                for (;;)
                {
                    outL = 0.0f;
                    outR = 0.0f;
                    if (_state.active)
                    {
                        masterTune = intrinsics::pow (2.0f, (_state.params.tune - 0.5f) * 0.16f);
                        baseF = _state.freq * masterTune;
                        driftAmt = (_state.params.drift * _state.params.drift) * 0.04f;
                        _state.drT1 = (_state.drT1 + (0.13f * _state.invSr));
                        if (_state.drT1 >= 1.0f)
                        {
                            _state.drT1 = (_state.drT1 - 1.0f);
                        }
                        _state.drT2 = (_state.drT2 + (0.071f * _state.invSr));
                        if (_state.drT2 >= 1.0f)
                        {
                            _state.drT2 = (_state.drT2 - 1.0f);
                        }
                        _state.drT3 = (_state.drT3 + (0.091f * _state.invSr));
                        if (_state.drT3 >= 1.0f)
                        {
                            _state.drT3 = (_state.drT3 - 1.0f);
                        }
                        _state.dr1 = (_state.dr1 + (((intrinsics::sin (_state.drT1 * 6.2831855f) + (0.4f * VCSVoice__rnd (_state))) - _state.dr1) * 0.0008f));
                        _state.dr2 = (_state.dr2 + (((intrinsics::sin (_state.drT2 * 6.2831855f) + (0.4f * VCSVoice__rnd (_state))) - _state.dr2) * 0.0008f));
                        _state.dr3 = (_state.dr3 + (((intrinsics::sin (_state.drT3 * 6.2831855f) + (0.4f * VCSVoice__rnd (_state))) - _state.dr3) * 0.0008f));
                        aR = 1.0f / (intrinsics::max (0.0008f, 0.001f + ((_state.params.trapA * _state.params.trapA) * 4.0f)) * _state.sr);
                        dR = 1.0f / (intrinsics::max (0.0008f, 0.005f + ((_state.params.trapD * _state.params.trapD) * 8.0f)) * _state.sr);
                        onT = 0.005f + ((_state.params.trapOn * _state.params.trapOn) * 4.0f);
                        offT = 0.005f + ((_state.params.trapOff * _state.params.trapOff) * 4.0f);
                        if (_state.trapStage == int32_t {0})
                        {
                            _state.trap = (_state.trap + aR);
                            if (_state.trap >= 1.0f)
                            {
                                _state.trap = 1.0f;
                                _state.trapStage = int32_t {1};
                                _state.trapOffT = 0.0f;
                            }
                        }
                        else
                        {
                            if (_state.trapStage == int32_t {1})
                            {
                                _state.trapOffT = (_state.trapOffT + _state.invSr);
                                if (_state.trapOffT >= onT)
                                {
                                    _state.trapStage = int32_t {2};
                                }
                            }
                            else
                            {
                                if (_state.trapStage == int32_t {2})
                                {
                                    _state.trap = (_state.trap - dR);
                                    if (_state.trap <= 0.0f)
                                    {
                                        _state.trap = 0.0f;
                                        _state.trapStage = int32_t {3};
                                        _state.trapOffT = 0.0f;
                                    }
                                }
                                else
                                {
                                    if (_state.trapStage == int32_t {3})
                                    {
                                        _state.trapOffT = (_state.trapOffT + _state.invSr);
                                        if ((_state.params.trapOff < 0.05f) ? (_state.trapOffT >= offT) : false)
                                        {
                                            _state.trapStage = int32_t {0};
                                        }
                                        else
                                        {
                                            if ((_state.params.trapOff >= 0.05f) ? (_state.trapOffT >= 0.05f) : false)
                                            {
                                                _state.active = false;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        trapCV = _state.trap;
                        joyXcv = (_state.params.joyX - 0.5f) * 2.0f;
                        joyYcv = (_state.params.joyY - 0.5f) * 2.0f;
                        _state.src[int32_t {7}] = trapCV;
                        _state.src[int32_t {8}] = joyXcv;
                        _state.src[int32_t {9}] = joyYcv;
                        cvK = 3.0f;
                        o1CV = intrinsics::tanh (VCSVoice__destBus (_state, int32_t {0})) * cvK;
                        o2CV = intrinsics::tanh (VCSVoice__destBus (_state, int32_t {1})) * cvK;
                        o3CV = intrinsics::tanh (VCSVoice__destBus (_state, int32_t {2})) * cvK;
                        filtCV = intrinsics::tanh (VCSVoice__destBus (_state, int32_t {5})) * 6.0f;
                        f1 = intrinsics::clamp (VCSVoice__oscHz (_state.params.o1Freq, _state.params.o1Range, baseF, o1CV) * (1.0f + (_state.dr1 * driftAmt)), 0.02f, _state.ny);
                        f2 = intrinsics::clamp (VCSVoice__oscHz (_state.params.o2Freq, _state.params.o2Range, baseF, o2CV) * (1.0f + (_state.dr2 * driftAmt)), 0.02f, _state.ny);
                        f3base = VCSVoice__oscHz (_state.params.o3Freq, _state.params.o3Range, baseF, o3CV) * (1.0f + (_state.dr3 * driftAmt));
                        f3 = intrinsics::clamp (f3base, 0.02f, _state.ny);
                        inc1 = f1 * _state.invSr;
                        inc2 = f2 * _state.invSr;
                        inc3 = f3 * _state.invSr;
                        _state.ph1 = (_state.ph1 + inc1);
                        if (_state.ph1 >= 1.0f)
                        {
                            _state.ph1 = (_state.ph1 - 1.0f);
                        }
                        _state.ph2 = (_state.ph2 + inc2);
                        if (_state.ph2 >= 1.0f)
                        {
                            _state.ph2 = (_state.ph2 - 1.0f);
                        }
                        _state.ph3 = (_state.ph3 + inc3);
                        if (_state.ph3 >= 1.0f)
                        {
                            _state.ph3 = (_state.ph3 - 1.0f);
                        }
                        o1 = VCSVoice__osc1Out (_state.ph1, inc1, _state.params.o1Sine, _state.params.o1Saw);
                        o2 = VCSVoice__morphOsc (_state.ph2, inc2, _state.params.o2Shape, intrinsics::clamp (_state.params.o2Pw + (intrinsics::tanh (VCSVoice__destBus (_state, int32_t {8})) * 0.45f), 0.03f, 0.97f)) * _state.params.o2Level;
                        o3 = VCSVoice__morphOsc (_state.ph3, inc3, _state.params.o3Shape, intrinsics::clamp (_state.params.o3Pw + (intrinsics::tanh (VCSVoice__destBus (_state, int32_t {9})) * 0.45f), 0.03f, 0.97f)) * _state.params.o3Level;
                        nz = VCSVoice__rnd (_state) * intrinsics::clamp (_state.params.noise + (intrinsics::tanh (VCSVoice__destBus (_state, int32_t {14})) * 0.5f), 0.0f, 1.0f);
                        ringP = 0.0f;
                        ringQ = 0.0f;
                        {
                            r = {};
                            for (;;)
                            {
                                if (r >= int32_t {10})
                                {
                                    break;
                                }
                                g3 = _state.src[r] * _state.params.mx[std__intrinsics___wrap_160 ((r * int32_t {16}) + int32_t {3})];
                                if ((r & int32_t {1}) == int32_t {0})
                                {
                                    ringP = (ringP + g3);
                                }
                                else
                                {
                                    ringQ = (ringQ + g3);
                                }
                                {
                                    ++r;
                                }
                            }
                        }
                        if (ringQ == 0.0f)
                        {
                            ringQ = ringP;
                        }
                        if (ringP == 0.0f)
                        {
                            ringP = ringQ;
                        }
                        ringOut = intrinsics::tanh ((ringP * ringQ) * 2.0f);
                        _state.src[int32_t {0}] = o1;
                        _state.src[int32_t {1}] = o2;
                        _state.src[int32_t {2}] = o3;
                        _state.src[int32_t {3}] = nz;
                        _state.src[int32_t {4}] = ringOut;
                        filtIn = VCSVoice__destBus (_state, int32_t {4});
                        filtIn = intrinsics::tanh (filtIn * 0.8f);
                        yb = (filtIn - _state.dcx) + (0.9985f * _state.dcy);
                        _state.dcx = filtIn;
                        _state.dcy = yb;
                        filtIn = yb;
                        kbd = _state.params.fKeyTrack * VCSVoice__log2f (intrinsics::max (baseF, 1.0f) / 261.63f);
                        fcOct = (((_state.params.cutoff * 9.0f) + kbd) + filtCV) + (VCSVoice__destBus (_state, int32_t {11}) * 3.0f);
                        fc = intrinsics::clamp (30.0f * intrinsics::pow (2.0f, fcOct), 20.0f, _state.ny);
                        fcSafe = intrinsics::clamp (fc, 20.0f, _state.sr * 0.45f);
                        g = intrinsics::tan ((3.1415927f * fcSafe) * _state.invSr);
                        G = g / (1.0f + g);
                        k = ((_state.params.reso * _state.params.reso) * 4.3f) + (intrinsics::max (0.0f, VCSVoice__destBus (_state, int32_t {10})) * 3.0f);
                        fbc = intrinsics::clamp (_state.lp4out, -1.3f, 1.3f);
                        fbk = fbc - (((fbc * fbc) * fbc) * 0.18f);
                        inSat = intrinsics::tanh ((filtIn - (k * fbk)) * 0.9f);
                        y1 = (G * (inSat - _state.lp1)) + _state.lp1;
                        _state.lp1 = ((2.0f * y1) - _state.lp1);
                        y2 = (G * (y1 - _state.lp2)) + _state.lp2;
                        _state.lp2 = ((2.0f * y2) - _state.lp2);
                        y3 = (G * (y2 - _state.lp3)) + _state.lp3;
                        _state.lp3 = ((2.0f * y3) - _state.lp3);
                        y4 = (G * (y3 - _state.lp4)) + _state.lp4;
                        _state.lp4 = ((2.0f * y4) - _state.lp4);
                        _state.lp4out = y4;
                        knee = 0.55f;
                        filtOut = intrinsics::tanh ((y2 * 0.45f) + (y3 * knee));
                        _state.filtPrev = filtOut;
                        _state.src[int32_t {5}] = filtOut;
                        revIn = VCSVoice__destBus (_state, int32_t {6}) + VCSVoice__destBus (_state, int32_t {12});
                        revIn = intrinsics::tanh (revIn * 0.8f);
                        x = revIn;
                        g1 = 0.6f;
                        n1 = x + (_state.sap1 * g1);
                        o_ap1 = ((- x) * g1) + _state.sap1;
                        _state.sap1 = n1;
                        x = o_ap1;
                        g2 = 0.55f;
                        n2 = x + (_state.sap2 * g2);
                        o_ap2 = ((- x) * g2) + _state.sap2;
                        _state.sap2 = n2;
                        x = o_ap2;
                        dly = _state.sbuf[_state.sw];
                        dly2 = _state.sbuf[std__intrinsics___wrap_2048 (_state.sw + int32_t {731})];
                        mix = (dly + dly2) * 0.5f;
                        _state.sdamp = ((mix * 0.4f) + (_state.sdamp * 0.6f));
                        _state.sbuf[_state.sw] = (x + (_state.sdamp * 0.4f));
                        std__intrinsics___wrapped_post_inc_2048 (_state.sw);
                        revOut = intrinsics::tanh (mix);
                        _state.revPrev = revOut;
                        _state.src[int32_t {6}] = revOut;
                        sig = intrinsics::tanh (VCSVoice__destBus (_state, int32_t {7}) + VCSVoice__destBus (_state, int32_t {15}));
                        sig = (sig + (((_state.src[int32_t {6}] * _state.params.mx[int32_t {103}]) * _state.params.reverb) * 0.5f));
                        amp = (((sig * trapCV) * (0.4f + (0.6f * _state.vel))) * (0.35f + (_state.params.volume * 1.1f))) * (1.0f + intrinsics::tanh (VCSVoice__destBus (_state, int32_t {13})));
                        o = intrinsics::tanh (amp * 1.2f);
                        outL = o;
                        outR = o;
                        if ((((outL != outL) ? true : (outL > 2.0f)) ? true : (outL < -2.0f)) ? true : (o != o))
                        {
                            outL = 0.0f;
                            outR = 0.0f;
                            _state.lp1 = 0.0f;
                            _state.lp2 = 0.0f;
                            _state.lp3 = 0.0f;
                            _state.lp4 = 0.0f;
                            _state.lp4out = 0.0f;
                            _state.sap1 = 0.0f;
                            _state.sap2 = 0.0f;
                            _state.sdamp = 0.0f;
                            _state.dcx = 0.0f;
                            _state.dcy = 0.0f;
                            _state.filtPrev = 0.0f;
                            _state.revPrev = 0.0f;
                            _state.src[int32_t {0}] = 0.0f;
                            _state.src[int32_t {1}] = 0.0f;
                            _state.src[int32_t {2}] = 0.0f;
                            _state.src[int32_t {3}] = 0.0f;
                            _state.src[int32_t {4}] = 0.0f;
                            _state.src[int32_t {5}] = 0.0f;
                            _state.src[int32_t {6}] = 0.0f;
                        }
                    }
                    _temp[int32_t {0}] = outL;
                    _temp[int32_t {1}] = outR;
                    _io.voiceOut = (_io.voiceOut + _temp);
                    _state._resumeIndex = int32_t {1};
                    return;
                }
            }
        }

        float std__intrinsics__sin (float n) noexcept
        {
            {
                return 0.0f;
            }
        }

        float VCSVoice__rnd (_VCSVoice_1_State& _state) noexcept
        {
            _state.rngc = (((_state.rngc * int32_t {0x41c64e6d}) + int32_t {12345}) & int32_t {0x7fffffff});
            return (static_cast<float> (_state.rngc) / 1073741800.0f) - 1.0f;
        }

        float std__intrinsics__max (float v1, float v2) noexcept
        {
            {
                return (v1 > v2) ? v1 : v2;
            }
        }

        float std__intrinsics__tanh (float n) noexcept
        {
            float  e;

            e = intrinsics::exp (intrinsics::min (n, 20.0f) * static_cast<float> (int32_t {2}));
            return (e - static_cast<float> (int32_t {1})) / (e + static_cast<float> (int32_t {1}));
        }

        float std__intrinsics__exp (float n) noexcept
        {
            {
                return 0.0f;
            }
        }

        float std__intrinsics__min (float v1, float v2) noexcept
        {
            {
                return (v1 < v2) ? v1 : v2;
            }
        }

        float VCSVoice__destBus (_VCSVoice_1_State& _state, int32_t c) noexcept
        {
            float  acc;
            int32_t  r;

            acc = 0.0f;
            {
                r = {};
                for (;;)
                {
                    if (r >= int32_t {10})
                    {
                        break;
                    }
                    acc = (acc + (_state.src[r] * _state.params.mx[std__intrinsics___wrap_160 ((r * int32_t {16}) + c)]));
                    {
                        ++r;
                    }
                }
            }
            return acc;
        }

        float std__intrinsics__clamp (float value, float minimum, float maximum) noexcept
        {
            return (value > maximum) ? maximum : ((value < minimum) ? minimum : value);
        }

        float VCSVoice__oscHz (float knob, float range, float baseF, float cv) noexcept
        {
            int32_t  rng;
            float  centre;
            float  oct;

            rng = static_cast<int32_t> (intrinsics::floor ((range * 2.0f) + 0.5f));
            centre = baseF;
            if (rng == int32_t {0})
            {
                centre = (baseF * 0.05f);
            }
            else
            {
                if (rng == int32_t {2})
                {
                    centre = (baseF * 4.0f);
                }
            }
            oct = ((knob - 0.5f) * 6.0f) + cv;
            return centre * intrinsics::pow (2.0f, oct);
        }

        float std__intrinsics__floor (float n) noexcept
        {
            float  rounded;

            {
                rounded = static_cast<float> (static_cast<int64_t> (n));
                if (rounded == n)
                {
                    return n;
                }
                if (n >= static_cast<float> (int32_t {0}))
                {
                    return rounded;
                }
                return rounded - static_cast<float> (int32_t {1});
            }
        }

        float VCSVoice__osc1Out (float p, float inc, float sineLvl, float sawLvl) noexcept
        {
            float  sine;
            float  saw;

            sine = intrinsics::sin (6.2831855f * p) + (0.08f * intrinsics::sin ((6.2831855f * p) * 2.0f));
            saw = ((2.0f * p) - 1.0f) - toi__dsp__polyBlep (p, inc);
            return (sine * sineLvl) + (saw * sawLvl);
        }

        float toi__dsp__polyBlep (float t, float dt) noexcept
        {
            float  x;
            float  x_0;

            if (dt <= 0.0f)
            {
                return 0.0f;
            }
            if (t < dt)
            {
                x = t / dt;
                return ((x + x) - (x * x)) - 1.0f;
            }
            else
            {
                if (t > (1.0f - dt))
                {
                    x_0 = (t - 1.0f) / dt;
                    return ((x_0 * x_0) + (x_0 + x_0)) + 1.0f;
                }
            }
            return 0.0f;
        }

        float VCSVoice__morphOsc (float p, float inc, float shape, float pw) noexcept
        {
            float  p2;
            float  saw;
            float  saw2;
            float  pulse;
            float  tri;
            float  dirtyTri;

            p2 = p + intrinsics::clamp (pw, 0.05f, 0.95f);
            if (p2 >= 1.0f)
            {
                p2 = (p2 - 1.0f);
            }
            saw = ((2.0f * p) - 1.0f) - toi__dsp__polyBlep (p, inc);
            saw2 = ((2.0f * p2) - 1.0f) - toi__dsp__polyBlep (p2, inc);
            pulse = saw - saw2;
            tri = (p < 0.5f) ? ((4.0f * p) - 1.0f) : (3.0f - (4.0f * p));
            dirtyTri = tri + (0.12f * intrinsics::sin ((6.2831855f * p) * 2.0f));
            return (dirtyTri * (1.0f - shape)) + (pulse * shape);
        }

        float VCSVoice__log2f (float x) noexcept
        {
            return intrinsics::log (intrinsics::max (x, 1e-9f)) * 1.442695f;
        }

        float std__intrinsics__log (float n) noexcept
        {
            {
                return 0.0f;
            }
        }

        float std__intrinsics__tan (float n) noexcept
        {
            {
                return intrinsics::sin (n) / intrinsics::cos (n);
            }
        }

        float std__intrinsics__cos (float n) noexcept
        {
            {
                return 0.0f;
            }
        }

        int32_t std__intrinsics___wrap_2048 (int32_t n) noexcept
        {
            return n & int32_t {2047};
        }

        int32_t std__intrinsics___wrapped_post_inc_2048 (int32_t& n) noexcept
        {
            int32_t  result;

            result = n;
            n = std__intrinsics___wrap_2048 (n + int32_t {1});
            return result;
        }

        void main_3 (std_midi_MPEConverter_1_State& _state, std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_IO& _io) noexcept
        {
        }

        //==============================================================================
        const char* getStringForHandle (uint32_t handle, size_t& stringLength)
        {
            (void) handle; (void) stringLength;
            return "";
        }

        //==============================================================================
        #define OFFSETOF(type, member)   ((size_t)((char *)&(*(type *)nullptr).member))
        static _JWVCS_State& state_upcast_struct_JWVCS_State_struc_djBVBe (_ParamsProcessor_1_State& child) { return *reinterpret_cast<_JWVCS_State*> (reinterpret_cast<char*> (std::addressof (child)) - (OFFSETOF (_JWVCS_State, paramsProcessor))); }
        static _JWVCS_State& state_upcast_struct_JWVCS_State_struc_p00AYc (std_voices_std_voices_VoiceAllocator_specialised_Sitcze_1_State& child) { return *reinterpret_cast<_JWVCS_State*> (reinterpret_cast<char*> (std::addressof (child)) - (OFFSETOF (_JWVCS_State, voiceAllocator))); }
        static JWVCS_State& state_upcast_struct_JWVCS_State_struct_meOY3b (_JWVCS_State& child) { return *reinterpret_cast<JWVCS_State*> (reinterpret_cast<char*> (std::addressof (child)) - (OFFSETOF (JWVCS_State, _state))); }
        static _JWVCS_State& state_upcast_struct_JWVCS_State_struc_N1feHc (std_midi_MPEConverter_1_State& child) { return *reinterpret_cast<_JWVCS_State*> (reinterpret_cast<char*> (std::addressof (child)) - (OFFSETOF (_JWVCS_State, noteTap))); }
        static _JWVCS_State& state_upcast_struct_JWVCS_State_struc_FEfOBc (std_midi_MPEConverter_1_State& child) { return *reinterpret_cast<_JWVCS_State*> (reinterpret_cast<char*> (std::addressof (child)) - (OFFSETOF (_JWVCS_State, mpe))); }

        //==============================================================================
        static constexpr int32_t g_slideController { int32_t {74} };
        static constexpr int32_t g_MPEMasterChannel { int32_t {0} };
        int32_t g__sessionID {};
        double g__frequency {};

        //==============================================================================
        struct intrinsics
        {
            template <typename T> static T modulo (T a, T b)
            {
                if constexpr (std::is_floating_point<T>::value)
                    return std::fmod (a, b);
                else
                    return a % b;
            }

            template <typename T> static T addModulo2Pi (T a, T b)
            {
                constexpr auto twoPi = static_cast<T> (3.141592653589793238 * 2);
                auto n = a + b;
                return n >= twoPi ? std::remainder (n, twoPi) : n;
            }

            template <typename T> static T abs           (T a)              { return std::abs (a); }
            template <typename T> static T min           (T a, T b)         { return std::min (a, b); }
            template <typename T> static T max           (T a, T b)         { return std::max (a, b); }
            template <typename T> static T clamp         (T a, T b, T c)    { return a < b ? b : (a > c ? c : a); }
            template <typename T> static T wrap          (T a, T b)         { if (b == 0) return 0; auto n = modulo (a, b); if (n < 0) n += b; return n; }
            template <typename T> static T fmod          (T a, T b)         { return b != 0 ? std::fmod (a, b) : 0; }
            template <typename T> static T remainder     (T a, T b)         { return b != 0 ? std::remainder (a, b) : 0; }
            template <typename T> static T floor         (T a)              { return std::floor (a); }
            template <typename T> static T ceil          (T a)              { return std::ceil (a); }
            template <typename T> static T rint          (T a)              { return std::rint (a); }
            template <typename T> static T sqrt          (T a)              { return std::sqrt (a); }
            template <typename T> static T pow           (T a, T b)         { return std::pow (a, b); }
            template <typename T> static T exp           (T a)              { return std::exp (a); }
            template <typename T> static T log           (T a)              { return std::log (a); }
            template <typename T> static T log10         (T a)              { return std::log10 (a); }
            template <typename T> static T sin           (T a)              { return std::sin (a); }
            template <typename T> static T cos           (T a)              { return std::cos (a); }
            template <typename T> static T tan           (T a)              { return std::tan (a); }
            template <typename T> static T sinh          (T a)              { return std::sinh (a); }
            template <typename T> static T cosh          (T a)              { return std::cosh (a); }
            template <typename T> static T tanh          (T a)              { return std::tanh (a); }
            template <typename T> static T asinh         (T a)              { return std::asinh (a); }
            template <typename T> static T acosh         (T a)              { return std::acosh (a); }
            template <typename T> static T atanh         (T a)              { return std::atanh (a); }
            template <typename T> static T asin          (T a)              { return std::asin (a); }
            template <typename T> static T acos          (T a)              { return std::acos (a); }
            template <typename T> static T atan          (T a)              { return std::atan (a); }
            template <typename T> static T atan2         (T a, T b)         { return std::atan2 (a, b); }
            template <typename T> static T isnan         (T a)              { return std::isnan (a) ? 1 : 0; }
            template <typename T> static T isinf         (T a)              { return std::isinf (a) ? 1 : 0; }
            template <typename T> static T select        (bool c, T a, T b) { return c ? a : b; }

            static int32_t reinterpretFloatToInt (float   a)                { int32_t i; memcpy (std::addressof(i), std::addressof(a), sizeof(i)); return i; }
            static int64_t reinterpretFloatToInt (double  a)                { int64_t i; memcpy (std::addressof(i), std::addressof(a), sizeof(i)); return i; }
            static float   reinterpretIntToFloat (int32_t a)                { float   f; memcpy (std::addressof(f), std::addressof(a), sizeof(f)); return f; }
            static double  reinterpretIntToFloat (int64_t a)                { double  f; memcpy (std::addressof(f), std::addressof(a), sizeof(f)); return f; }

            static int32_t rightShiftUnsigned (int32_t a, int32_t b)        { return static_cast<int32_t> (static_cast<uint32_t> (a) >> b); }
            static int64_t rightShiftUnsigned (int64_t a, int64_t b)        { return static_cast<int64_t> (static_cast<uint64_t> (a) >> b); }

            struct VectorOps
            {
                template <typename Vec> static Vec abs     (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::abs (x); }); }
                template <typename Vec> static Vec min     (Vec a, Vec b)     { return a.performBinaryOp (b, [] (auto x, auto y) { return intrinsics::min (x, y); }); }
                template <typename Vec> static Vec max     (Vec a, Vec b)     { return a.performBinaryOp (b, [] (auto x, auto y) { return intrinsics::max (x, y); }); }
                template <typename Vec> static Vec sqrt    (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::sqrt (x); }); }
                template <typename Vec> static Vec log     (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::log (x); }); }
                template <typename Vec> static Vec log10   (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::log10 (x); }); }
                template <typename Vec> static Vec sin     (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::sin (x); }); }
                template <typename Vec> static Vec cos     (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::cos (x); }); }
                template <typename Vec> static Vec tan     (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::tan (x); }); }
                template <typename Vec> static Vec sinh    (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::sinh (x); }); }
                template <typename Vec> static Vec cosh    (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::cosh (x); }); }
                template <typename Vec> static Vec tanh    (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::tanh (x); }); }
                template <typename Vec> static Vec asinh   (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::asinh (x); }); }
                template <typename Vec> static Vec acosh   (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::acosh (x); }); }
                template <typename Vec> static Vec atanh   (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::atanh (x); }); }
                template <typename Vec> static Vec asin    (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::asin (x); }); }
                template <typename Vec> static Vec acos    (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::acos (x); }); }
                template <typename Vec> static Vec atan    (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::atan (x); }); }
                template <typename Vec> static Vec atan2   (Vec a, Vec b)     { return a.performBinaryOp (b, [] (auto x, auto y) { return intrinsics::atan2 (x, y); }); }
                template <typename Vec> static Vec pow     (Vec a, Vec b)     { return a.performBinaryOp (b, [] (auto x, auto y) { return intrinsics::pow (x, y); }); }
                template <typename Vec> static Vec exp     (Vec a)            { return a.performUnaryOp ([] (auto x) { return intrinsics::exp (x); }); }

                template <typename Vec> static Vec rightShiftUnsigned (Vec a, Vec b) { return a.performBinaryOp (b, [] (auto x, auto y) { return intrinsics::rightShiftUnsigned (x, y); }); }
            };
        };

        static constexpr float  _inf32  =  std::numeric_limits<float>::infinity();
        static constexpr double _inf64  =  std::numeric_limits<double>::infinity();
        static constexpr float  _ninf32 = -std::numeric_limits<float>::infinity();
        static constexpr double _ninf64 = -std::numeric_limits<double>::infinity();
        static constexpr float  _nan32  =  std::numeric_limits<float>::quiet_NaN();
        static constexpr double _nan64  =  std::numeric_limits<double>::quiet_NaN();

        //==============================================================================
        #if __clang__
         #pragma clang diagnostic pop
        #elif __GNUC__
         #pragma GCC diagnostic pop
        #else
         #pragma warning (pop)
        #endif
    };
} // namespace performer



struct JWVCS
{
    using PerformerClass = performer::JWVCS;
    static constexpr auto filename = "VCS.cmajorpatch";

    struct File { std::string_view name, content; };

    static constexpr const char* cmaj_api_cmajpatchconnection_js =
        "//\n"
        "//     ,ad888ba,                              88\n"
        "//    d8\"'    \"8b\n"
        "//   d8            88,dba,,adba,   ,aPP8A.A8  88\n"
        "//   Y8,           88    88    88  88     88  88\n"
        "//    Y8a.   .a8P  88    88    88  88,   ,88  88     (C)2024 Cmajor Software Ltd\n"
        "//     '\"Y888Y\"'   88    88    88  '\"8bbP\"Y8  88     https://cmajor.dev\n"
        "//                                           ,88\n"
        "//                                        888P\"\n"
        "//\n"
        "//  This file may be used under the terms of the ISC license:\n"
        "//\n"
        "//  Permission to use, copy, modify, and/or distribute this software for any purpose with or\n"
        "//  without fee is hereby granted, provided that the above copyright notice and this permission\n"
        "//  notice appear in all copies. THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL\n"
        "//  WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY\n"
        "//  AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR\n"
        "//  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,\n"
        "//  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n"
        "//  CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\n"
        "\n"
        "import { EventListenerList } from \"./cmaj-event-listener-list.js\"\n"
        "import * as midi from \"./cmaj-midi-helpers.js\"\n"
        "import PianoKeyboard from \"./cmaj-piano-keyboard.js\"\n"
        "import GenericPatchView from \"./cmaj-generic-patch-view.js\"\n"
        "import * as ParameterControls from \"./cmaj-parameter-controls.js\"\n"
        "\n"
        "//==============================================================================\n"
        "/** This class implements the API and much of the logic for communicating with\n"
        " *  an instance of a patch that is running.\n"
        " */\n"
        "export class PatchConnection  extends EventListenerList\n"
        "{\n"
        "    constructor()\n"
        "    {\n"
        "        super();\n"
        "    }\n"
        "\n"
        "    /** Returns the current Cmajor version */\n"
        "    async getCmajorVersion()\n"
        "    {\n"
        "        const version = await import (\"/cmaj_api/cmaj-version.js\");\n"
        "        return version.getCmajorVersion();\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    // Status-handling methods:\n"
        "\n"
        "    /** Calling this will trigger an asynchronous callback to any status listeners with the\n"
        "     *  patch's current state. Use addStatusListener() to attach a listener to receive it.\n"
        "     */\n"
        "    requestStatusUpdate()                             { this.sendMessageToServer ({ type: \"req_status\" }); }\n"
        "\n"
        "    /** Attaches a listener function that will be called whenever the patch's status changes.\n"
        "     *  The function will be called with a parameter object containing many properties describing the status,\n"
        "     *  including whether the patch is loaded, any errors, endpoint descriptions, its manifest, etc.\n"
        "     */\n"
        "    addStatusListener (listener)                      { this.addEventListener    (\"status\", listener); }\n"
        "\n"
        "    /** Removes a listener that was previously added with addStatusListener()\n"
        "     */\n"
        "    removeStatusListener (listener)                   { this.removeEventListener (\"status\", listener); }\n"
        "\n"
        "    /** Causes the patch to be reset to its \"just loaded\" state. */\n"
        "    resetToInitialState()                             { this.sendMessageToServer ({ type: \"req_reset\" }); }\n"
        "\n"
        "    //==============================================================================\n"
        "    // Methods for sending data to input endpoints:\n"
        "\n"
        "    /** Sends a value to one of the patch's input endpoints.\n"
        "     *\n"
        "     *  This can be used to send a value to either an 'event' or 'value' type input endpoint.\n"
        "     *  If the endpoint is a 'value' type, then the rampFrames parameter can optionally be used to specify\n"
        "     *  the number of frames over which the current value should ramp to the new target one.\n"
        "     *  The value parameter will be coerced to the type that is expected by the endpoint. So for\n"
        "     *  examples, numbers will be converted to float or integer types, javascript objects and arrays\n"
        "     *  will be converted into more complex types in as good a fashion is possible.\n"
        "     */\n"
        "    sendEventOrValue (endpointID, value, rampFrames, timeoutMillisecs)  { this.sendMessageToServer ({ type: \"send_value\", id: endpointID, value, rampFrames, timeout: timeoutMillisecs }); }\n"
        "\n"
        "    /** Sends a short MIDI message value to a MIDI endpoint.\n"
        "     *  The value must be a number encoded with `(byte0 << 16) | (byte1 << 8) | byte2`.\n"
        "     */\n"
        "    sendMIDIInputEvent (endpointID, shortMIDICode)    { this.sendEventOrValue (endpointID, { message: shortMIDICode }); }\n"
        "\n"
        "    /** Tells the patch that a series of changes that constitute a gesture is about to take place\n"
        "     *  for the given endpoint. Remember to call sendParameterGestureEnd() after they're done!\n"
        "     */\n"
        "    sendParameterGestureStart (endpointID)            { this.sendMessageToServer ({ type: \"send_gesture_start\", id: endpointID }); }\n"
        "\n"
        "    /** Tells the patch that a gesture started by sendParameterGestureStart() has finished.\n"
        "     */\n"
        "    sendParameterGestureEnd (endpointID)              { this.sendMessageToServer ({ type: \"send_gesture_end\", id: endpointID }); }\n"
        "\n"
        "    //==============================================================================\n"
        "    // Stored state control methods:\n"
        "\n"
        "    /** Requests a callback to any stored-state value listeners with the current value of a given key-value pair.\n"
        "     *  To attach a listener to receive these events, use addStoredStateValueListener().\n"
        "     *  @param {string} key\n"
        "     */\n"
        "    requestStoredStateValue (key)                     { this.sendMessageToServer ({ type: \"req_state_value\", key: key }); }\n"
        "\n"
        "    /** Modifies a key-value pair in the patch's stored state.\n"
        "     *  @param {string} key\n"
        "     *  @param {Object | null | undefined} newValue\n"
        "     */\n"
        "    sendStoredStateValue (key, newValue)              { this.sendMessageToServer ({ type: \"send_state_value\", key: key, value: newValue }); }\n"
        "\n"
        "    /** Removes all stored state values in the patch.\n"
        "     */\n"
        "    clearAllStoredStateValues()                       { this.sendMessageToServer ({ type: \"clear_all_state_values\" }); }\n"
        "\n"
        "    /** Attaches a listener function that will be called when any key-value pair in the stored state is changed.\n"
        "     *  The listener function will receive a message parameter with properties 'key' and 'value'.\n"
        "     */\n"
        "    addStoredStateValueListener (listener)            { this.addEventListener    (\"state_key_value\", listener); }\n"
        "\n"
        "    /** Removes a listener that was previously added with addStoredStateValueListener().\n"
        "     */\n"
        "    removeStoredStateValueListener (listener)         { this.removeEventListener (\"state_key_value\", listener); }\n"
        "\n"
        "    /** Applies a complete stored state to the patch.\n"
        "     *  To get the current complete state, use requestFullStoredState().\n"
        "     */\n"
        "    sendFullStoredState (fullState)                   { this.sendMessageToServer ({ type: \"send_full_state\", value: fullState }); }\n"
        "\n"
        "    /** Asynchronously requests the full stored state of the patch.\n"
        "     *  The listener function that is supplied will be called asynchronously with the state as its argument.\n"
        "     */\n"
        "    requestFullStoredState (callback)\n"
        "    {\n"
        "        const replyType = \"fullstate_response_\" + (Math.floor (Math.random() * 100000000)).toString();\n"
        "        this.addSingleUseListener (replyType, callback);\n"
        "        this.sendMessageToServer ({ type: \"req_full_state\", replyType: replyType });\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    // Listener methods:\n"
        "\n"
        "    /** Attaches a listener function that will receive updates with the events or audio data\n"
        "     *  that is being sent or received by an endpoint.\n"
        "     *\n"
        "     *  If the endpoint is an event or value, the callback will be given an argument which is\n"
        "     *  the new value.\n"
        "     *\n"
        "     *  If the endpoint has the right shape to be treated as \"audio\" then the callback will receive\n"
        "     *  a stream of updates of the min/max range of chunks of data that is flowing through it.\n"
        "     *  There will be one callback per chunk of data, and the size of chunks is specified by\n"
        "     *  the optional granularity parameter.\n"
        "     *\n"
        "     *  @param {string} endpointID\n"
        "     *  @param {number} granularity - if defined, this specifies the number of frames per callback\n"
        "     *  @param {boolean} sendFullAudioData - if false, the listener will receive an argument object containing\n"
        "     *     two properties 'min' and 'max', which are each an array of values, one element per audio\n"
        "     *     channel. This allows you to find the highest and lowest samples in that chunk for each channel.\n"
        "     *     If sendFullAudioData is true, the listener's argument will have a property 'data' which is an\n"
        "     *     array containing one array per channel of raw audio samples data.\n"
        "     */\n"
        "    addEndpointListener (endpointID, listener, granularity, sendFullAudioData)\n"
        "    {\n"
        "        const listenerID = \"event_\" + endpointID + \"_\" + (Math.floor (Math.random() * 100000000)).toString();\n"
        "        listener[\"cmaj_endpointListenerID_\" + endpointID] = listenerID;\n"
        "        this.addEventListener (listenerID, listener);\n"
        "        this.sendMessageToServer ({ type: \"add_endpoint_listener\", endpoint: endpointID, replyType: listenerID,\n"
        "                                    granularity: granularity, fullAudioData: sendFullAudioData });\n"
        "    }\n"
        "\n"
        "    /** Removes a listener that was previously added with addEndpointListener()\n"
        "     *  @param {string} endpointID\n"
        "    */\n"
        "    removeEndpointListener (endpointID, listener)\n"
        "    {\n"
        "        const listenerID = listener[\"cmaj_endpointListenerID_\" + endpointID];\n"
        "        listener[\"cmaj_endpointListenerID_\" + endpointID] = undefined;\n"
        "        this.removeEventListener (listenerID, listener);\n"
        "        this.sendMessageToServer ({ type: \"remove_endpoint_listener\", endpoint: endpointID, replyType: listenerID });\n"
        "    }\n"
        "\n"
        "    /** This will trigger an asynchronous callback to any parameter listeners that are\n"
        "     *  attached, providing them with its up-to-date current value for the given endpoint.\n"
        "     *  Use addAllParameterListener() to attach a listener to receive the result.\n"
        "     *  @param {string} endpointID\n"
        "     */\n"
        "    requestParameterValue (endpointID)                  { this.sendMessageToServer ({ type: \"req_param_value\", id: endpointID }); }\n"
        "\n"
        "    /** Attaches a listener function which will be called whenever the value of a specific parameter changes.\n"
        "     *  The listener function will be called with an argument which is the new value.\n"
        "     *  @param {string} endpointID\n"
        "     */\n"
        "    addParameterListener (endpointID, listener)         { this.addEventListener (\"param_value_\" + endpointID.toString(), listener); }\n"
        "\n"
        "    /** Removes a listener that was previously added with addParameterListener()\n"
        "     *  @param {string} endpointID\n"
        "    */\n"
        "    removeParameterListener (endpointID, listener)      { this.removeEventListener (\"param_value_\" + endpointID.toString(), listener); }\n"
        "\n"
        "    /** Attaches a listener function which will be called whenever the value of any parameter changes in the patch.\n"
        "     *  The listener function will be called with an argument object with the fields 'endpointID' and 'value'.\n"
        "     */\n"
        "    addAllParameterListener (listener)                  { this.addEventListener (\"param_value\", listener); }\n"
        "\n"
        "    /** Removes a listener that was previously added with addAllParameterListener()\n"
        "     */\n"
        "    removeAllParameterListener (listener)               { this.removeEventListener (\"param_value\", listener); }\n"
        "\n"
        "    /** This takes a relative path to an asset within the patch bundle, and converts it to a\n"
        "     *  path relative to the root of the browser that is showing the view.\n"
        "     *\n"
        "     *  You need to use this in your view code to translate your asset URLs to a form that\n"
        "     *  can be safely used in your view's HTML DOM (e.g. in its CSS). This is needed because the\n"
        "     *  host's HTTP server (which is delivering your view pages) may have a different '/' root\n"
        "     *  than the root of your patch (e.g. if a single server is serving multiple patch GUIs).\n"
        "     *\n"
        "     *  @param {string} path\n"
        "     */\n"
        "    getResourceAddress (path)                           { return path; }\n"
        "\n"
        "    //==============================================================================\n"
        "    /**\n"
        "     *  This property contains various utility classes and functions from the Cmajor API,\n"
        "     *  for use in your GUI or worker code.\n"
        "     */\n"
        "    utilities = {\n"
        "        /** MIDI utility functions from cmaj-midi-helpers.js */\n"
        "        midi,\n"
        "        /** On-screen keyboard class from cmaj-piano-keyboard.js */\n"
        "        PianoKeyboard,\n"
        "        /** Basic parameter control GUI elements, from cmaj-parameter-controls.js */\n"
        "        ParameterControls,\n"
        "        /** The default view GUI, from cmaj-generic-patch-view.js */\n"
        "        GenericPatchView\n"
        "    };\n"
        "\n"
        "    //==============================================================================\n"
        "    // Private methods follow this point..\n"
        "\n"
        "    /** @private */\n"
        "    deliverMessageFromServer (msg)\n"
        "    {\n"
        "        if (msg.type === \"status\")\n"
        "            this.manifest = msg.message?.manifest;\n"
        "\n"
        "        if (msg.type == \"param_value\")\n"
        "            this.dispatchEvent (\"param_value_\" + msg.message.endpointID, msg.message.value);\n"
        "\n"
        "        this.dispatchEvent (msg.type, msg.message);\n"
        "    }\n"
        "}\n";
    static constexpr const char* VCS_cmajorpatch =
        "{\n"
        "  \"CmajorVersion\": 1,\n"
        "  \"ID\": \"com.plugincorp.jwvcs\",\n"
        "  \"version\": \"0.1\",\n"
        "  \"name\": \"JW-VCS\",\n"
        "  \"description\": \"TOI JW-VCS - British pin-matrix modular-in-a-box with diode-ladder filter and spring reverb by plugin corp\",\n"
        "  \"category\": \"instrument\",\n"
        "  \"manufacturer\": \"TOI\",\n"
        "  \"isInstrument\": true,\n"
        "  \"manufacturerCode\": \"Plgc\",\n"
        "  \"pluginCode\": \"Jvcs\",\n"
        "  \"source\": [\n"
        "    \"../_dsp/toi_dsp.cmajor\",\n"
        "    \"VCS.cmajor\"\n"
        "  ]\n"
        "}";
    static constexpr const char* cmaj_api_assets_cmajorlogo_svg =
        "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"150 140 1620 670\">\n"
        "  <g>\n"
        "    <path\n"
        "      d=\"M944.511,462.372V587.049H896.558V469.165c0-27.572-13.189-44.757-35.966-44.757-23.577,0-39.958,19.183-39.958,46.755V587.049H773.078V469.165c0-27.572-13.185-44.757-35.962-44.757-22.378,0-39.162,19.581-39.162,46.755V587.049H650.4v-201.4h47.551v28.77c8.39-19.581,28.771-32.766,54.346-32.766,27.572,0,46.353,11.589,56.343,35.166,11.589-23.577,33.57-35.166,65.934-35.166C918.937,381.652,944.511,412.42,944.511,462.372Zm193.422-76.724h47.953v201.4h-47.953V557.876c-6.794,19.581-31.167,33.567-64.335,33.567q-42.558,0-71.928-29.969c-19.183-20.381-28.771-45.155-28.771-75.128s9.588-54.743,28.771-74.726c19.581-20.377,43.556-30.366,71.928-30.366,33.168,0,57.541,13.985,64.335,33.566Zm3.6,100.7c0-17.579-5.993-32.368-17.981-43.953-11.589-11.59-26.374-17.583-43.559-17.583s-31.167,5.993-42.756,17.583c-11.187,11.585-16.783,26.374-16.783,43.953s5.6,32.369,16.783,43.958c11.589,11.589,25.575,17.583,42.756,17.583s31.97-5.994,43.559-17.583C1135.537,518.715,1141.53,503.929,1141.53,486.346Zm84.135,113.49c0,21.177-7.594,29.571-25.575,29.571-2.8,0-7.192-.4-13.185-.8v42.357c4.393.8,11.187,1.2,19.979,1.2,44.355,0,66.734-22.776,66.734-67.932V385.648h-47.953Zm23.978-294.108c-15.987,0-28.774,12.385-28.774,28.372s12.787,28.369,28.774,28.369a28.371,28.371,0,0,0,0-56.741Zm239.674,104.694c21.177,20.381,31.966,45.956,31.966,75.924s-10.789,55.547-31.966,75.928-47.154,30.769-77.926,30.769-56.741-10.392-77.922-30.769-31.966-45.955-31.966-75.928,10.789-55.543,31.966-75.924,47.154-30.768,77.922-30.768S1468.136,390.041,1489.317,410.422Zm-15.585,75.924c0-17.981-5.994-32.766-17.985-44.753-11.988-12.39-26.773-18.383-44.356-18.383-17.981,0-32.766,5.993-44.754,18.383-11.589,11.987-17.583,26.772-17.583,44.753s5.994,32.77,17.583,45.156c11.988,11.987,26.773,17.985,44.754,17.985q26.374,0,44.356-17.985C1467.738,519.116,1473.732,504.331,1473.732,486.346Zm184.122-104.694c-28.373,0-50.349,12.787-59.941,33.964V385.648h-47.551v201.4h47.551v-105.9c0-33.169,21.177-53.948,54.345-53.948a102.566,102.566,0,0,1,19.979,2V382.85A74.364,74.364,0,0,0,1657.854,381.652ZM58"
        "0.777,569.25l33.909,30.087c-40.644,47.027-92.892,70.829-156.173,70.829-58.637,0-108.567-19.737-149.788-59.8C268.082,570.31,247.763,519.8,247.763,460s20.319-109.726,60.962-149.786c41.221-40.059,91.151-60.38,149.788-60.38,62.119,0,113.789,22.643,154.432,68.507l-33.864,30.134c-16.261-19.069-35.272-32.933-56.978-41.783V486.346H496.536V621.1Q546.954,610.231,580.777,569.25Zm-237.74,9.1A150.247,150.247,0,0,0,396.5,614.04V486.346H370.929V319.387a159.623,159.623,0,0,0-27.892,22.829Q297.187,389.16,297.186,460C297.186,507.229,312.47,547.06,343.037,578.354Zm115.476,46.66a187.178,187.178,0,0,0,27.28-1.94V486.346H474.548V295.666c-5.236-.426-10.567-.677-16.035-.677a177.387,177.387,0,0,0-40.029,4.4V486.346H407.239v131.4A175.161,175.161,0,0,0,458.513,625.014Z\"\n"
        "      fill=\"#fff\" />\n"
        "  </g>\n"
        "</svg>\n";
    static constexpr const char* cmaj_api_cmajaudioworklethelper_js =
        "//\n"
        "//     ,ad888ba,                              88\n"
        "//    d8\"'    \"8b\n"
        "//   d8            88,dba,,adba,   ,aPP8A.A8  88\n"
        "//   Y8,           88    88    88  88     88  88\n"
        "//    Y8a.   .a8P  88    88    88  88,   ,88  88     (C)2024 Cmajor Software Ltd\n"
        "//     '\"Y888Y\"'   88    88    88  '\"8bbP\"Y8  88     https://cmajor.dev\n"
        "//                                           ,88\n"
        "//                                        888P\"\n"
        "//\n"
        "//  This file may be used under the terms of the ISC license:\n"
        "//\n"
        "//  Permission to use, copy, modify, and/or distribute this software for any purpose with or\n"
        "//  without fee is hereby granted, provided that the above copyright notice and this permission\n"
        "//  notice appear in all copies. THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL\n"
        "//  WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY\n"
        "//  AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR\n"
        "//  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,\n"
        "//  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n"
        "//  CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\n"
        "\n"
        "import { PatchConnection } from \"./cmaj-patch-connection.js\"\n"
        "\n"
        "//==============================================================================\n"
        "// N.B. code will be serialised to a string, so all `registerWorkletProcessor`s\n"
        "// dependencies must be self contained and not capture things in the outer scope\n"
        "async function serialiseWorkletProcessorFactoryToDataURI (CmajorClass, workletName, hostDescription)\n"
        "{\n"
        "    const serialisedInvocation = `(${registerWorkletProcessor.toString()}) (\"${workletName}\", ${CmajorClass.toString()}, \"${hostDescription}\");`\n"
        "\n"
        "    let reader = new FileReader();\n"
        "    reader.readAsDataURL (new Blob ([serialisedInvocation], { type: \"text/javascript\" }));\n"
        "\n"
        "    return await new Promise (res => { reader.onloadend = () => res (reader.result); });\n"
        "}\n"
        "\n"
        "function registerWorkletProcessor (workletName, CmajorClass, hostDescription)\n"
        "{\n"
        "    function makeConsumeOutputEvents ({ wrapper, eventOutputs, dispatchOutputEvent })\n"
        "    {\n"
        "        const outputEventHandlers = eventOutputs.map (({ endpointID }) =>\n"
        "        {\n"
        "            const readCount = wrapper[`getOutputEventCount_${endpointID}`]?.bind (wrapper);\n"
        "            const reset = wrapper[`resetOutputEventCount_${endpointID}`]?.bind (wrapper);\n"
        "            const readEventAtIndex = wrapper[`getOutputEvent_${endpointID}`]?.bind (wrapper);\n"
        "\n"
        "            return () =>\n"
        "            {\n"
        "                const count = readCount();\n"
        "\n"
        "                for (let i = 0; i < count; ++i)\n"
        "                    dispatchOutputEvent (endpointID, readEventAtIndex (i));\n"
        "\n"
        "                reset();\n"
        "            };\n"
        "        });\n"
        "\n"
        "        return () => outputEventHandlers.forEach ((consume) => consume() );\n"
        "    }\n"
        "\n"
        "    function setInitialParameterValues (parametersMap)\n"
        "    {\n"
        "        for (const { initialise } of Object.values (parametersMap))\n"
        "            initialise();\n"
        "    }\n"
        "\n"
        "    function makeEndpointMap (wrapper, endpoints, initialValueOverrides)\n"
        "    {\n"
        "        const toKey = ({ endpointType, endpointID }) =>\n"
        "        {\n"
        "            switch (endpointType)\n"
        "            {\n"
        "                case \"event\": return `sendInputEvent_${endpointID}`;\n"
        "                case \"value\": return `setInputValue_${endpointID}`;\n"
        "            }\n"
        "\n"
        "            throw \"Unhandled endpoint type\";\n"
        "        };\n"
        "\n"
        "        const lookup = {};\n"
        "\n"
        "        for (const { endpointID, endpointType, annotation, purpose } of endpoints)\n"
        "        {\n"
        "            const key = toKey ({ endpointType, endpointID });\n"
        "            const wrapperUpdate = wrapper[key]?.bind (wrapper);\n"
        "\n"
        "            const snapAndConstrainValue = (value) =>\n"
        "            {\n"
        "                if (annotation.step != null)\n"
        "                    value = Math.round (value / annotation.step) * annotation.step;\n"
        "\n"
        "                if (annotation.min != null && annotation.max != null)\n"
        "                    value = Math.min (Math.max (value, annotation.min), annotation.max);\n"
        "\n"
        "                return value;\n"
        "            };\n"
        "\n"
        "            const update = (value, rampFrames) =>\n"
        "            {\n"
        "                // N.B. value clamping and rampFrames from annotations not currently applied\n"
        "                const entry = lookup[endpointID];\n"
        "                entry.cachedValue = value;\n"
        "                wrapperUpdate (value, rampFrames);\n"
        "            };\n"
        "\n"
        "            if (update)\n"
        "            {\n"
        "                const initialValue = initialValueOverrides[endpointID] ?\? annotation?.init;\n"
        "\n"
        "                lookup[endpointID] = {\n"
        "                    snapAndConstrainValue,\n"
        "                    update,\n"
        "                    initialise: initialValue != null ? () => update (initialValue) : () => {},\n"
        "                    purpose,\n"
        "                    cachedValue: undefined,\n"
        "                };\n"
        "            }\n"
        "        }\n"
        "\n"
        "        return lookup;\n"
        "    }\n"
        "\n"
        "    function makeStreamEndpointHandler ({ wrapper, toEndpoints, wrapperMethodNamePrefix })\n"
        "    {\n"
        "        const endpoints = toEndpoints (wrapper);\n"
        "        if (endpoints.length === 0)\n"
        "            return () => {};\n"
        "\n"
        "        let handlers = [];\n"
        "        let targetChannels = [];\n"
        "        let channelCount = 0;\n"
        "\n"
        "        for (const endpoint of endpoints)\n"
        "        {\n"
        "            const handleFrames = wrapper[`${wrapperMethodNamePrefix}_${endpoint.endpointID}`]?.bind (wrapper);\n"
        "\n"
        "            if (! handleFrames)\n"
        "                return () => {};\n"
        "\n"
        "            handlers.push (handleFrames);\n"
        "            targetChannels.push (channelCount);\n"
        "            channelCount += endpoint.numAudioChannels;\n"
        "        }\n"
        "\n"
        "        return (channels, blockSize) =>\n"
        "        {\n"
        "            for (let i = 0; i < handlers.length; i++)\n"
        "                handlers[i] (channels, blockSize, targetChannels[i]);\n"
        "        }\n"
        "    }\n"
        "\n"
        "    function makeInputStreamEndpointHandler (wrapper)\n"
        "    {\n"
        "        return makeStreamEndpointHandler ({\n"
        "            wrapper,\n"
        "            toEndpoints: wrapper => wrapper.getInputEndpoints().filter (({ purpose }) => purpose === \"audio in\"),\n"
        "            wrapperMethodNamePrefix: \"setInputStreamFrames\",\n"
        "        });\n"
        "    }\n"
        "\n"
        "    function makeOutputStreamEndpointHandler (wrapper)\n"
        "    {\n"
        "        return makeStreamEndpointHandler ({\n"
        "            wrapper,\n"
        "            toEndpoints: wrapper => wrapper.getOutputEndpoints().filter (({ purpose }) => purpose === \"audio out\"),\n"
        "            wrapperMethodNamePrefix: \"getOutputFrames\",\n"
        "        });\n"
        "    }\n"
        "\n"
        "    class WorkletProcessor extends AudioWorkletProcessor\n"
        "    {\n"
        "        static get parameterDescriptors()\n"
        "        {\n"
        "            return [];\n"
        "        }\n"
        "\n"
        "        constructor ({ processorOptions, ...options })\n"
        "        {\n"
        "            super (options);\n"
        "\n"
        "            this.processImpl = undefined;\n"
        "            this.consumeOutputEvents = undefined;\n"
        "\n"
        "            const { sessionID = Date.now() & 0x7fffffff, initialValueOverrides = {} } = processorOptions;\n"
        "\n"
        "            const wrapper = new CmajorClass();\n"
        "\n"
        "            wrapper.initialise (sessionID, sampleRate)\n"
        "                .then (() => this.initialisePatch (wrapper, initialValueOverrides))\n"
        "                .catch (error => { throw new Error (error)});\n"
        "        }\n"
        "\n"
        "        process (inputs, outputs)\n"
        "        {\n"
        "            const input = inputs[0];\n"
        "            const output = outputs[0];\n"
        "\n"
        "            this.processImpl?.(input, output);\n"
        "            this.consumeOutputEvents?.();\n"
        "\n"
        "            return true;\n"
        "        }\n"
        "\n"
        "        sendPatchMessage (payload)\n"
        "        {\n"
        "            this.port.postMessage ({ type: \"patch\", payload });\n"
        "        }\n"
        "\n"
        "        sendParameterValueChanged (endpointID, value)\n"
        "        {\n"
        "            this.sendPatchMessage ({\n"
        "                type: \"param_value\",\n"
        "                message: { endpointID, value }\n"
        "            });\n"
        "        }\n"
        "\n"
        "        initialisePatch (wrapper, initialValueOverrides)\n"
        "        {\n"
        "            try\n"
        "            {\n"
        "                const inputParameters = wrapper.getInputEndpoints().filter (({ purpose }) => purpose === \"parameter\");\n"
        "                const parametersMap = makeEndpointMap (wrapper, inputParameters, initialValueOverrides);\n"
        "\n"
        "                setInitialParameterValues (parametersMap);\n"
        "\n"
        "                const toParameterValuesWithKey = (endpointKey, parametersMap) =>\n"
        "                {\n"
        "                    const toValue = ([endpoint, { cachedValue }]) => ({ [endpointKey]: endpoint, value: cachedValue });\n"
        "                    return Object.entries (parametersMap).map (toValue);\n"
        "                };\n"
        "\n"
        "                const initialValues = toParameterValuesWithKey (\"endpointID\", parametersMap);\n"
        "                const initialState = wrapper.getState();\n"
        "\n"
        "                const resetState = () =>\n"
        "                {\n"
        "                    wrapper.restoreState (initialState);\n"
        "\n"
        "                    // N.B. update cache used for `req_param_value` messages (we don't currently read from the wasm heap)\n"
        "                    setInitialParameterValues (parametersMap);\n"
        "                };\n"
        "\n"
        "                const isNonAudioOrParameterEndpoint = ({ purpose }) => ! [\"audio in\", \"parameter\"].includes (purpose);\n"
        "                const otherInputs = wrapper.getInputEndpoints().filter (isNonAudioOrParameterEndpoint);\n"
        "                const otherInputEndpointsMap = makeEndpointMap (wrapper, otherInputs, initialValueOverrides);\n"
        "\n"
        "                const isEvent = ({ endpointType }) => endpointType === \"event\";\n"
        "                const eventInputs = wrapper.getInputEndpoints().filter (isEvent);\n"
        "                const eventOutputs = wrapper.getOutputEndpoints().filter (isEvent);\n"
        "\n"
        "                const makeEndpointListenerMap = (eventEndpoints) =>\n"
        "                {\n"
        "                    const listeners = {};\n"
        "\n"
        "                    for (const { endpointID } of eventEndpoints)\n"
        "                        listeners[endpointID] = [];\n"
        "\n"
        "                    return listeners;\n"
        "                };\n"
        "\n"
        "                const inputEventListeners = makeEndpointListenerMap (eventInputs);\n"
        "                const outputEventListeners = makeEndpointListenerMap (eventOutputs);\n"
        "\n"
        "                this.consumeOutputEvents = makeConsumeOutputEvents ({\n"
        "                    eventOutputs,\n"
        "                    wrapper,\n"
        "                    dispatchOutputEvent: (endpointID, event) =>\n"
        "                    {\n"
        "                        for (const { replyType } of outputEventListeners[endpointID] ?\? [])\n"
        "                        {\n"
        "                            this.sendPatchMessage ({\n"
        "                                type: replyType,\n"
        "                                message: event.event, // N.B. chucking away frame and typeIndex info for now\n"
        "                            });\n"
        "                        }\n"
        "                    },\n"
        "                });\n"
        "\n"
        "                const blockSize = 128;\n"
        "                const prepareInputFrames = makeInputStreamEndpointHandler (wrapper);\n"
        "                const processOutputFrames = makeOutputStreamEndpointHandler (wrapper);\n"
        "\n"
        "                this.processImpl = (input, output) =>\n"
        "                {\n"
        "                    prepareInputFrames (input, blockSize);\n"
        "                    wrapper.advance (blockSize);\n"
        "                    processOutputFrames (output, blockSize);\n"
        "                };\n"
        "\n"
        "                // N.B. the message port makes things straightforward, but it allocates (when sending + receiving).\n"
        "                // so, we aren't doing ourselves any favours. we probably ought to marshal raw bytes over to the gui in\n"
        "                // a pre-allocated lock-free message queue (using `SharedArrayBuffer` + `Atomic`s) and transform the raw\n"
        "                // messages there.\n"
        "                this.port.addEventListener (\"message\", e =>\n"
        "                {\n"
        "                    if (e.data.type !== \"patch\")\n"
        "                        return;\n"
        "\n"
        "                    const msg = e.data.payload;\n"
        "\n"
        "                    switch (msg.type)\n"
        "                    {\n"
        "                        case \"req_status\":\n"
        "                        {\n"
        "                            this.sendPatchMessage ({\n"
        "                                type: \"status\",\n"
        "                                message: {\n"
        "                                    details: {\n"
        "                                        inputs: wrapper.getInputEndpoints(),\n"
        "                                        outputs: wrapper.getOutputEndpoints(),\n"
        "                                    },\n"
        "                                    sampleRate,\n"
        "                                    host: hostDescription ? hostDescription : \"WebAudio\"\n"
        "                                },\n"
        "                            });\n"
        "                            break;\n"
        "                        }\n"
        "\n"
        "                        case \"req_reset\":\n"
        "                        {\n"
        "                            resetState();\n"
        "                            initialValues.forEach (v => this.sendParameterValueChanged (v.endpointID, v.value));\n"
        "                            break;\n"
        "                        }\n"
        "\n"
        "                        case \"req_param_value\":\n"
        "                        {\n"
        "                            // N.B. keep a local cache here so that we can send the values back when requested.\n"
        "                            // we could instead have accessors into the wasm heap.\n"
        "                            const endpointID = msg.id;\n"
        "                            const parameter = parametersMap[endpointID];\n"
        "                            if (! parameter)\n"
        "                                return;\n"
        "\n"
        "                            const value = parameter.cachedValue;\n"
        "                            this.sendParameterValueChanged (endpointID, value);\n"
        "                            break;\n"
        "                        }\n"
        "\n"
        "                        case \"send_value\":\n"
        "                        {\n"
        "                            const endpointID = msg.id;\n"
        "                            const parameter = parametersMap[endpointID];\n"
        "\n"
        "                            if (parameter)\n"
        "                            {\n"
        "                                const newValue = parameter.snapAndConstrainValue (msg.value);\n"
        "                                parameter.update (newValue, msg.rampFrames);\n"
        "\n"
        "                                this.sendParameterValueChanged (endpointID, newValue);\n"
        "                                return;\n"
        "                            }\n"
        "\n"
        "                            const inputEndpoint = otherInputEndpointsMap[endpointID];\n"
        "\n"
        "                            if (inputEndpoint)\n"
        "                            {\n"
        "                                inputEndpoint.update (msg.value);\n"
        "\n"
        "                                for (const { replyType } of inputEventListeners[endpointID] ?\? [])\n"
        "                                {\n"
        "                                    this.sendPatchMessage ({\n"
        "                                        type: replyType,\n"
        "                                        message: inputEndpoint.cachedValue,\n"
        "                                    });\n"
        "                                }\n"
        "                            }\n"
        "                            break;\n"
        "                        }\n"
        "\n"
        "                        case \"send_gesture_start\": break;\n"
        "                        case \"send_gesture_end\": break;\n"
        "\n"
        "                        case \"req_full_state\":\n"
        "                            this.sendPatchMessage ({\n"
        "                                type: msg?.replyType,\n"
        "                                message: {\n"
        "                                    parameters: toParameterValuesWithKey (\"name\", parametersMap),\n"
        "                                },\n"
        "                            });\n"
        "                            break;\n"
        "\n"
        "                        case \"send_full_state\":\n"
        "                        {\n"
        "                            const { parameters = [] } = e.data.payload?.value || [];\n"
        "\n"
        "                            for (const [endpointID, parameter] of Object.entries (parametersMap))\n"
        "                            {\n"
        "                                const namedNextValue = parameters.find (({ name }) => name === endpointID);\n"
        "\n"
        "                                if (namedNextValue)\n"
        "                                    parameter.update (namedNextValue.value);\n"
        "                                else\n"
        "                                    parameter.initialise();\n"
        "\n"
        "                                this.sendParameterValueChanged (endpointID, parameter.cachedValue);\n"
        "                            }\n"
        "                            break;\n"
        "                        }\n"
        "\n"
        "                        case \"add_endpoint_listener\":\n"
        "                        {\n"
        "                            const insertIfValidEndpoint = (lookup, msg) =>\n"
        "                            {\n"
        "                                const endpointID = msg?.endpoint;\n"
        "                                const listeners = lookup[endpointID]\n"
        "\n"
        "                                if (! listeners)\n"
        "                                    return false;\n"
        "\n"
        "                                return listeners.push ({ replyType: msg?.replyType }) > 0;\n"
        "                            };\n"
        "\n"
        "                            if (! insertIfValidEndpoint (inputEventListeners, msg))\n"
        "                                insertIfValidEndpoint (outputEventListeners, msg)\n"
        "\n"
        "                            break;\n"
        "                        }\n"
        "\n"
        "                        case \"remove_endpoint_listener\":\n"
        "                        {\n"
        "                            const removeIfValidReplyType = (lookup, msg) =>\n"
        "                            {\n"
        "                                const endpointID = msg?.endpoint;\n"
        "                                const listeners = lookup[endpointID];\n"
        "\n"
        "                                if (! listeners)\n"
        "                                    return false;\n"
        "\n"
        "                                const index = listeners.indexOf (msg?.replyType);\n"
        "\n"
        "                                if (index === -1)\n"
        "                                    return false;\n"
        "\n"
        "                                return listeners.splice (index, 1).length === 1;\n"
        "                            };\n"
        "\n"
        "                            if (! removeIfValidReplyType (inputEventListeners, msg))\n"
        "                                removeIfValidReplyType (outputEventListeners, msg)\n"
        "\n"
        "                            break;\n"
        "                        }\n"
        "\n"
        "                        default:\n"
        "                            break;\n"
        "                    }\n"
        "                });\n"
        "\n"
        "                this.port.postMessage ({ type: \"initialised\" });\n"
        "                this.port.start();\n"
        "            }\n"
        "            catch (e)\n"
        "            {\n"
        "                this.port.postMessage (e.toString());\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "\n"
        "    registerProcessor (workletName, WorkletProcessor);\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "async function connectToAudioIn (audioContext, node)\n"
        "{\n"
        "    try\n"
        "    {\n"
        "        const input = await navigator.mediaDevices.getUserMedia ({\n"
        "            audio: {\n"
        "                echoCancellation: false,\n"
        "                noiseSuppression: false,\n"
        "                autoGainControl:  false,\n"
        "        }});\n"
        "\n"
        "        if (! input)\n"
        "            throw new Error();\n"
        "\n"
        "        const source = audioContext.createMediaStreamSource (input);\n"
        "\n"
        "        if (! source)\n"
        "            throw new Error();\n"
        "\n"
        "        source.connect (node);\n"
        "    }\n"
        "    catch (e)\n"
        "    {\n"
        "        console.warn (`Could not open audio input`);\n"
        "    }\n"
        "}\n"
        "\n"
        "async function connectToMIDI (connection, midiEndpointID)\n"
        "{\n"
        "    try\n"
        "    {\n"
        "        if (! navigator.requestMIDIAccess)\n"
        "            throw new Error (\"Web MIDI API not supported.\");\n"
        "\n"
        "        const midiAccess = await navigator.requestMIDIAccess ({ sysex: true, software: true });\n"
        "\n"
        "        for (const input of midiAccess.inputs.values())\n"
        "        {\n"
        "            input.onmidimessage = ({ data }) =>\n"
        "                connection.sendMIDIInputEvent (midiEndpointID, data[2] | (data[1] << 8) | (data[0] << 16));\n"
        "        }\n"
        "    }\n"
        "    catch (e)\n"
        "    {\n"
        "        console.warn (`Could not open MIDI devices: ${e}`);\n"
        "    }\n"
        "}\n"
        "\n"
        "\n"
        "//==============================================================================\n"
        "/**  This class provides a PatchConnection that controls a Cmajor audio worklet\n"
        " *   node.\n"
        " */\n"
        "export class AudioWorkletPatchConnection extends PatchConnection\n"
        "{\n"
        "    constructor (manifest)\n"
        "    {\n"
        "        super();\n"
        "\n"
        "        this.manifest = manifest;\n"
        "        this.cachedState = {};\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    /**  Initialises this connection to load and control the given Cmajor class.\n"
        "     *\n"
        "     *   @param {Object} parameters - the parameters to use\n"
        "     *   @param {Object} parameters.CmajorClass - the generated Cmajor class\n"
        "     *   @param {AudioContext} parameters.audioContext - a web audio AudioContext object\n"
        "     *   @param {string} parameters.workletName - the name to give the new worklet that is created\n"
        "     *   @param {string} parameters.hostDescription - a description of the host that is using the patch\n"
        "     *   @param {number} [parameters.sessionID] - an integer to use for the session ID, or undefined to use a default\n"
        "     *   @param {Object} [parameters.initialValueOverrides] - optional initial values for parameter endpoints\n"
        "     *   @param {string} [parameters.rootResourcePath] - optionally, a root to use when resolving resource paths\n"
        "     */\n"
        "    async initialise ({ CmajorClass,\n"
        "                        audioContext,\n"
        "                        workletName,\n"
        "                        hostDescription,\n"
        "                        sessionID,\n"
        "                        initialValueOverrides,\n"
        "                        rootResourcePath })\n"
        "    {\n"
        "        this.audioContext = audioContext;\n"
        "\n"
        "        if (rootResourcePath)\n"
        "        {\n"
        "            this.rootResourcePath = rootResourcePath.toString();\n"
        "\n"
        "            if (! this.rootResourcePath.endsWith (\"/\"))\n"
        "                this.rootResourcePath += \"/\";\n"
        "        }\n"
        "        else\n"
        "        {\n"
        "            const getBaseUrl = (relativeURL) =>\n"
        "            {\n"
        "                const baseURL = relativeURL.href.substring(0, relativeURL.href.lastIndexOf('/'));\n"
        "                return baseURL;\n"
        "            };\n"
        "\n"
        "            this.rootResourcePath = getBaseUrl(new URL('.', import.meta.url));\n"
        "\n"
        "            if (! this.rootResourcePath.endsWith (\"/\"))\n"
        "                this.rootResourcePath += \"/../\";\n"
        "        }\n"
        "\n"
        "        const dataURI = await serialiseWorkletProcessorFactoryToDataURI (CmajorClass, workletName, hostDescription);\n"
        "        await audioContext.audioWorklet.addModule (dataURI);\n"
        "\n"
        "        this.inputEndpoints = CmajorClass.prototype.getInputEndpoints();\n"
        "        this.outputEndpoints = CmajorClass.prototype.getOutputEndpoints();\n"
        "\n"
        "        const audioInputEndpoints  = this.inputEndpoints.filter (({ purpose }) => purpose === \"audio in\");\n"
        "        const audioOutputEndpoints = this.outputEndpoints.filter (({ purpose }) => purpose === \"audio out\");\n"
        "\n"
        "        let inputChannelCount = 0;\n"
        "        let outputChannelCount = 0;\n"
        "\n"
        "        audioInputEndpoints.forEach  ((endpoint) => { inputChannelCount = inputChannelCount + endpoint.numAudioChannels; });\n"
        "        audioOutputEndpoints.forEach ((endpoint) => { outputChannelCount = outputChannelCount + endpoint.numAudioChannels; });\n"
        "\n"
        "        const hasInput = inputChannelCount > 0;\n"
        "        const hasOutput = outputChannelCount > 0;\n"
        "\n"
        "        const node = new AudioWorkletNode (audioContext, workletName, {\n"
        "            numberOfInputs: +hasInput,\n"
        "            numberOfOutputs: +hasOutput,\n"
        "            channelCountMode: \"explicit\",\n"
        "            channelCount: hasInput ? inputChannelCount : undefined,\n"
        "            outputChannelCount: hasOutput ? [outputChannelCount] : [],\n"
        "\n"
        "            processorOptions:\n"
        "            {\n"
        "                sessionID,\n"
        "                initialValueOverrides\n"
        "            }\n"
        "        });\n"
        "\n"
        "        const waitUntilWorkletInitialised = async () =>\n"
        "        {\n"
        "            return new Promise ((resolve) =>\n"
        "            {\n"
        "                const filterForInitialised = (e) =>\n"
        "                {\n"
        "                    if (e.data.type === \"initialised\")\n"
        "                    {\n"
        "                        node.port.removeEventListener (\"message\", filterForInitialised);\n"
        "                        resolve();\n"
        "                    }\n"
        "                };\n"
        "\n"
        "                node.port.addEventListener (\"message\", filterForInitialised);\n"
        "            });\n"
        "        };\n"
        "\n"
        "        node.port.start();\n"
        "\n"
        "        await waitUntilWorkletInitialised();\n"
        "\n"
        "        this.audioNode = node;\n"
        "\n"
        "        node.port.addEventListener (\"message\", e =>\n"
        "        {\n"
        "            if (e.data.type === \"patch\")\n"
        "            {\n"
        "                const msg = e.data.payload;\n"
        "\n"
        "                if (msg?.type === \"status\")\n"
        "                    msg.message = { manifest: this.manifest, ...msg.message };\n"
        "\n"
        "                this.deliverMessageFromServer (msg)\n"
        "            }\n"
        "        });\n"
        "\n"
        "        await this.startPatchWorker();\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    /**  Attempts to connect this connection to the default audio and MIDI channels.\n"
        "     *   This must only be called once initialise() has completed successfully.\n"
        "     *\n"
        "     *   @param {AudioContext} audioContext - a web audio AudioContext object\n"
        "     */\n"
        "    async connectDefaultAudioAndMIDI (audioContext)\n"
        "    {\n"
        "        if (! this.audioNode)\n"
        "            throw new Error (\"AudioWorkletPatchConnection.initialise() must have been successfully completed before calling connectDefaultAudioAndMIDI()\");\n"
        "\n"
        "        const getInputWithPurpose = (purpose) =>\n"
        "        {\n"
        "            for (const i of this.inputEndpoints)\n"
        "                if (i.purpose === purpose)\n"
        "                    return i.endpointID;\n"
        "        }\n"
        "\n"
        "        const midiEndpointID = getInputWithPurpose (\"midi in\");\n"
        "\n"
        "        if (midiEndpointID)\n"
        "            connectToMIDI (this, midiEndpointID);\n"
        "\n"
        "        if (getInputWithPurpose (\"audio in\"))\n"
        "            connectToAudioIn (audioContext, this.audioNode);\n"
        "\n"
        "        this.audioNode.connect (audioContext.destination);\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    sendMessageToServer (msg)\n"
        "    {\n"
        "        this.audioNode.port.postMessage ({ type: \"patch\", payload: msg });\n"
        "    }\n"
        "\n"
        "    requestStoredStateValue (key)\n"
        "    {\n"
        "        this.dispatchEvent (\"state_key_value\", { key, value: this.cachedState[key] });\n"
        "    }\n"
        "\n"
        "    sendStoredStateValue (key, newValue)\n"
        "    {\n"
        "        const changed = this.cachedState[key] != newValue;\n"
        "\n"
        "        if (changed)\n"
        "        {\n"
        "            const shouldRemove = newValue == null;\n"
        "            if (shouldRemove)\n"
        "            {\n"
        "                delete this.cachedState[key];\n"
        "                return;\n"
        "            }\n"
        "\n"
        "            this.cachedState[key] = newValue;\n"
        "            // N.B. notifying the client only when updating matches behaviour of the patch player\n"
        "            this.dispatchEvent (\"state_key_value\", { key, value: newValue });\n"
        "        }\n"
        "    }\n"
        "\n"
        "    sendFullStoredState (fullState)\n"
        "    {\n"
        "        const currentStateCleared = (() =>\n"
        "        {\n"
        "            const out = {};\n"
        "            Object.keys (this.cachedState).forEach (k => out[k] = undefined);\n"
        "            return out;\n"
        "        })();\n"
        "\n"
        "        const incomingStateValues = fullState.values ?\? {};\n"
        "        const nextStateValues = { ...currentStateCleared, ...incomingStateValues };\n"
        "\n"
        "        Object.entries (nextStateValues).forEach (([key, value]) => this.sendStoredStateValue (key, value));\n"
        "\n"
        "        // N.B. worklet will handle the `parameters` part\n"
        "        super.sendFullStoredState (fullState);\n"
        "    }\n"
        "\n"
        "    requestFullStoredState (callback)\n"
        "    {\n"
        "        // N.B. the worklet only handles the `parameters` part, so we patch the key-value state in here\n"
        "        super.requestFullStoredState (msg => callback ({ values: { ...this.cachedState }, ...msg }));\n"
        "    }\n"
        "\n"
        "    getResourceAddress (path)\n"
        "    {\n"
        "        return this.rootResourcePath + path;\n"
        "    }\n"
        "\n"
        "    async readResource (path)\n"
        "    {\n"
        "        return fetch (path);\n"
        "    }\n"
        "\n"
        "    async readResourceAsAudioData (path)\n"
        "    {\n"
        "        const response = await this.readResource (path);\n"
        "        const buffer = await this.audioContext.decodeAudioData (await response.arrayBuffer());\n"
        "\n"
        "        let frames = [];\n"
        "\n"
        "        for (let i = 0; i < buffer.length; ++i)\n"
        "            frames.push ([]);\n"
        "\n"
        "        for (let chan = 0; chan < buffer.numberOfChannels; ++chan)\n"
        "        {\n"
        "            const src = buffer.getChannelData (chan);\n"
        "\n"
        "            for (let i = 0; i < buffer.length; ++i)\n"
        "                frames[i].push (src[i]);\n"
        "        }\n"
        "\n"
        "        return { frames, sampleRate: buffer.sampleRate };\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    /** @private */\n"
        "    async startPatchWorker()\n"
        "    {\n"
        "        if (this.manifest.worker?.length > 0)\n"
        "        {\n"
        "            const module = await import (this.getResourceAddress (this.manifest.worker));\n"
        "            module.default (this);\n"
        "        }\n"
        "    }\n"
        "}\n";
    static constexpr const char* cmaj_api_cmajeventlistenerlist_js =
        "//\n"
        "//     ,ad888ba,                              88\n"
        "//    d8\"'    \"8b\n"
        "//   d8            88,dba,,adba,   ,aPP8A.A8  88\n"
        "//   Y8,           88    88    88  88     88  88\n"
        "//    Y8a.   .a8P  88    88    88  88,   ,88  88     (C)2024 Cmajor Software Ltd\n"
        "//     '\"Y888Y\"'   88    88    88  '\"8bbP\"Y8  88     https://cmajor.dev\n"
        "//                                           ,88\n"
        "//                                        888P\"\n"
        "//\n"
        "//  This file may be used under the terms of the ISC license:\n"
        "//\n"
        "//  Permission to use, copy, modify, and/or distribute this software for any purpose with or\n"
        "//  without fee is hereby granted, provided that the above copyright notice and this permission\n"
        "//  notice appear in all copies. THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL\n"
        "//  WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY\n"
        "//  AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR\n"
        "//  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,\n"
        "//  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n"
        "//  CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\n"
        "\n"
        "\n"
        "/** This event listener management class allows listeners to be attached and\n"
        " *  removed from named event types.\n"
        " */\n"
        "export class EventListenerList\n"
        "{\n"
        "    constructor()\n"
        "    {\n"
        "        this.listenersPerType = {};\n"
        "    }\n"
        "\n"
        "    /** Adds a listener for a specifc event type.\n"
        "     *  If the listener is already registered, this will simply add it again.\n"
        "     *  Each call to addEventListener() must be paired with a removeventListener()\n"
        "     *  call to remove it.\n"
        "     *\n"
        "     *  @param {string} type\n"
        "     */\n"
        "    addEventListener (type, listener)\n"
        "    {\n"
        "        if (type && listener)\n"
        "        {\n"
        "            const list = this.listenersPerType[type];\n"
        "\n"
        "            if (list)\n"
        "                list.push (listener);\n"
        "            else\n"
        "                this.listenersPerType[type] = [listener];\n"
        "        }\n"
        "    }\n"
        "\n"
        "    /** Removes a listener that was previously added for the given event type.\n"
        "     *  @param {string} type\n"
        "     */\n"
        "    removeEventListener (type, listener)\n"
        "    {\n"
        "        if (type && listener)\n"
        "        {\n"
        "            const list = this.listenersPerType[type];\n"
        "\n"
        "            if (list)\n"
        "            {\n"
        "                const i = list.indexOf (listener);\n"
        "\n"
        "                if (i >= 0)\n"
        "                    list.splice (i, 1);\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "\n"
        "    /** Attaches a callback function that will be automatically unregistered\n"
        "     *  the first time it is invoked.\n"
        "     *\n"
        "     *  @param {string} type\n"
        "     */\n"
        "    addSingleUseListener (type, listener)\n"
        "    {\n"
        "        const l = message =>\n"
        "        {\n"
        "            this.removeEventListener (type, l);\n"
        "            listener?.(message);\n"
        "        };\n"
        "\n"
        "        this.addEventListener (type, l);\n"
        "    }\n"
        "\n"
        "    /** Synchronously dispatches an event object to all listeners\n"
        "     *  that are registered for the given type.\n"
        "     *\n"
        "     *  @param {string} type\n"
        "     */\n"
        "    dispatchEvent (type, event)\n"
        "    {\n"
        "        const list = this.listenersPerType[type];\n"
        "\n"
        "        if (list)\n"
        "            for (const listener of list)\n"
        "                listener?.(event);\n"
        "    }\n"
        "\n"
        "    /** Returns the number of listeners that are currently registered\n"
        "     *  for the given type of event.\n"
        "     *\n"
        "     *  @param {string} type\n"
        "     */\n"
        "    getNumListenersForType (type)\n"
        "    {\n"
        "        const list = this.listenersPerType[type];\n"
        "        return list ? list.length : 0;\n"
        "    }\n"
        "}\n";
    static constexpr const char* cmaj_api_cmajgenericpatchview_js =
        "//\n"
        "//     ,ad888ba,                              88\n"
        "//    d8\"'    \"8b\n"
        "//   d8            88,dba,,adba,   ,aPP8A.A8  88\n"
        "//   Y8,           88    88    88  88     88  88\n"
        "//    Y8a.   .a8P  88    88    88  88,   ,88  88     (C)2024 Cmajor Software Ltd\n"
        "//     '\"Y888Y\"'   88    88    88  '\"8bbP\"Y8  88     https://cmajor.dev\n"
        "//                                           ,88\n"
        "//                                        888P\"\n"
        "//\n"
        "//  This file may be used under the terms of the ISC license:\n"
        "//\n"
        "//  Permission to use, copy, modify, and/or distribute this software for any purpose with or\n"
        "//  without fee is hereby granted, provided that the above copyright notice and this permission\n"
        "//  notice appear in all copies. THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL\n"
        "//  WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY\n"
        "//  AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR\n"
        "//  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,\n"
        "//  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n"
        "//  CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\n"
        "\n"
        "import * as Controls from \"./cmaj-parameter-controls.js\"\n"
        "\n"
        "//==============================================================================\n"
        "/** A simple, generic view which can control any type of patch */\n"
        "class GenericPatchView extends HTMLElement\n"
        "{\n"
        "    /** Creates a view for a patch.\n"
        "     *  @param {PatchConnection} patchConnection - the connection to the target patch\n"
        "     */\n"
        "    constructor (patchConnection)\n"
        "    {\n"
        "        super();\n"
        "\n"
        "        this.patchConnection = patchConnection;\n"
        "\n"
        "        this.statusListener = status =>\n"
        "        {\n"
        "            this.status = status;\n"
        "            this.createControlElements();\n"
        "        };\n"
        "\n"
        "        this.attachShadow ({ mode: \"open\" });\n"
        "        this.shadowRoot.innerHTML = this.getHTML();\n"
        "\n"
        "        this.titleElement      = this.shadowRoot.querySelector (\"cmaj-generic-patch-title\");\n"
        "        this.parametersElement = this.shadowRoot.querySelector (\"cmaj-generic-patch-parameters\");\n"
        "    }\n"
        "\n"
        "    /** This is picked up by some of our wrapper code to know whether it makes\n"
        "     *  sense to put a title bar/logo above the GUI.\n"
        "     */\n"
        "    hasOwnTitleBar()\n"
        "    {\n"
        "        return true;\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    /** @private */\n"
        "    connectedCallback()\n"
        "    {\n"
        "        this.patchConnection.addStatusListener (this.statusListener);\n"
        "        this.patchConnection.requestStatusUpdate();\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    disconnectedCallback()\n"
        "    {\n"
        "        this.patchConnection.removeStatusListener (this.statusListener);\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    createControlElements()\n"
        "    {\n"
        "        this.parametersElement.innerHTML = \"\";\n"
        "        this.titleElement.innerText = this.status?.manifest?.name ?\? \"Cmajor\";\n"
        "\n"
        "        if (this.status?.details?.inputs)\n"
        "        {\n"
        "            for (const endpointInfo of this.status.details.inputs)\n"
        "            {\n"
        "                if (! endpointInfo.annotation?.hidden)\n"
        "                {\n"
        "                    const control = Controls.createLabelledControl (this.patchConnection, endpointInfo);\n"
        "\n"
        "                    if (control)\n"
        "                        this.parametersElement.appendChild (control);\n"
        "                }\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    getHTML()\n"
        "    {\n"
        "        const baseUrl = import.meta.url;\n"
        "\n"
        "        return `\n"
        "            <style>\n"
        "            * {\n"
        "                box-sizing: border-box;\n"
        "                user-select: none;\n"
        "                -webkit-user-select: none;\n"
        "                -moz-user-select: none;\n"
        "                -ms-user-select: none;\n"
        "                font-family: Avenir, 'Avenir Next LT Pro', Montserrat, Corbel, 'URW Gothic', source-sans-pro, sans-serif;\n"
        "                font-size: 0.9rem;\n"
        "            }\n"
        "\n"
        "            :host {\n"
        "                --header-height: 2.5rem;\n"
        "                --foreground: #ffffff;\n"
        "                --background: #1a1a1a;\n"
        "\n"
        "                display: block;\n"
        "                height: 100%;\n"
        "                background-color: var(--background);\n"
        "            }\n"
        "\n"
        "            cmaj-generic-patch-main {\n"
        "                background: var(--background);\n"
        "                height: 100%;\n"
        "            }\n"
        "\n"
        "            cmaj-generic-patch-header {\n"
        "                width: 100%;\n"
        "                height: var(--header-height);\n"
        "                border-bottom: 0.1rem solid var(--foreground);\n"
        "                display: flex;\n"
        "                justify-content: space-between;\n"
        "                align-items: center;\n"
        "            }\n"
        "\n"
        "            cmaj-generic-patch-title {\n"
        "                color: var(--foreground);\n"
        "                text-overflow: ellipsis;\n"
        "                white-space: nowrap;\n"
        "                overflow: hidden;\n"
        "                cursor: default;\n"
        "                font-size: 140%;\n"
        "                font-weight: bold;\n"
        "            }\n"
        "\n"
        "            cmaj-generic-patch-logo {\n"
        "                flex: 1;\n"
        "                height: 80%;\n"
        "                margin-left: 0.3rem;\n"
        "                margin-right: 0.3rem;\n"
        "                background-color: var(--foreground);\n"
        "                mask: url(${baseUrl}/../assets/cmajor-logo.svg);\n"
        "                mask-repeat: no-repeat;\n"
        "                -webkit-mask: url(${baseUrl}/../assets/cmajor-logo.svg);\n"
        "                -webkit-mask-repeat: no-repeat;\n"
        "                min-width: 6.25rem;\n"
        "            }\n"
        "\n"
        "            cmaj-generic-patch-padding {\n"
        "                flex: 1;\n"
        "            }\n"
        "\n"
        "            cmaj-generic-patch-parameters {\n"
        "                display: flex;\n"
        "                flex-flow: row wrap;\n"
        "                justify-content: center;\n"
        "                height: calc(100% - var(--header-height));\n"
        "                overflow: auto;\n"
        "                padding: 1rem;\n"
        "                text-align: center;\n"
        "            }\n"
        "\n"
        "            ${Controls.getAllCSS()}\n"
        "\n"
        "            </style>\n"
        "\n"
        "            <cmaj-generic-patch-main>\n"
        "              <cmaj-generic-patch-header>\n"
        "                <cmaj-generic-patch-logo></cmaj-generic-patch-logo>\n"
        "                <cmaj-generic-patch-title></cmaj-generic-patch-title>\n"
        "                <cmaj-generic-patch-padding></cmaj-generic-patch-padding>\n"
        "              </cmaj-generic-patch-header>\n"
        "              <cmaj-generic-patch-parameters></cmaj-generic-patch-parameters>\n"
        "            </cmaj-generic-patch-main>`;\n"
        "    }\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "/** Creates a generic view element which can be used to control any patch.\n"
        " *  @param {PatchConnection} patchConnection - the connection to the target patch\n"
        " */\n"
        "export default function createPatchView (patchConnection)\n"
        "{\n"
        "    const genericPatchViewName = \"cmaj-generic-patch-view\";\n"
        "\n"
        "    if (! window.customElements.get (genericPatchViewName))\n"
        "        window.customElements.define (genericPatchViewName, GenericPatchView);\n"
        "\n"
        "    return new (window.customElements.get (genericPatchViewName)) (patchConnection);\n"
        "}\n";
    static constexpr const char* cmaj_api_cmajmidihelpers_js =
        "//\n"
        "//     ,ad888ba,                              88\n"
        "//    d8\"'    \"8b\n"
        "//   d8            88,dba,,adba,   ,aPP8A.A8  88\n"
        "//   Y8,           88    88    88  88     88  88\n"
        "//    Y8a.   .a8P  88    88    88  88,   ,88  88     (C)2024 Cmajor Software Ltd\n"
        "//     '\"Y888Y\"'   88    88    88  '\"8bbP\"Y8  88     https://cmajor.dev\n"
        "//                                           ,88\n"
        "//                                        888P\"\n"
        "//\n"
        "//  This file may be used under the terms of the ISC license:\n"
        "//\n"
        "//  Permission to use, copy, modify, and/or distribute this software for any purpose with or\n"
        "//  without fee is hereby granted, provided that the above copyright notice and this permission\n"
        "//  notice appear in all copies. THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL\n"
        "//  WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY\n"
        "//  AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR\n"
        "//  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,\n"
        "//  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n"
        "//  CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\n"
        "\n"
        "\n"
        "export function getByte0 (message)     { return (message >> 16) & 0xff; }\n"
        "export function getByte1 (message)     { return (message >> 8) & 0xff; }\n"
        "export function getByte2 (message)     { return message & 0xff; }\n"
        "\n"
        "function isVoiceMessage (message, type)     { return ((message >> 16) & 0xf0) == type; }\n"
        "function get14BitValue (message)            { return getByte1 (message) | (getByte2 (message) << 7); }\n"
        "\n"
        "export function getChannel0to15 (message)   { return getByte0 (message) & 0x0f; }\n"
        "export function getChannel1to16 (message)   { return getChannel0to15 (message) + 1; }\n"
        "\n"
        "export function getMessageSize (message)\n"
        "{\n"
        "    const mainGroupLengths = (3 << 0) | (3 << 2) | (3 << 4) | (3 << 6)\n"
        "                           | (2 << 8) | (2 << 10) | (3 << 12);\n"
        "\n"
        "    const lastGroupLengths = (1 <<  0) | (2 <<  2) | (3 <<  4) | (2 <<  6)\n"
        "                           | (1 <<  8) | (1 << 10) | (1 << 12) | (1 << 14)\n"
        "                           | (1 << 16) | (1 << 18) | (1 << 20) | (1 << 22)\n"
        "                           | (1 << 24) | (1 << 26) | (1 << 28) | (1 << 30);\n"
        "\n"
        "    const firstByte = getByte0 (message);\n"
        "    const group = (firstByte >> 4) & 7;\n"
        "\n"
        "    return (group != 7 ? (mainGroupLengths >> (2 * group))\n"
        "                       : (lastGroupLengths >> (2 * (firstByte & 15)))) & 3;\n"
        "}\n"
        "\n"
        "export function isNoteOn  (message)                         { return isVoiceMessage (message, 0x90) && getVelocity (message) != 0; }\n"
        "export function isNoteOff (message)                         { return isVoiceMessage (message, 0x80) || (isVoiceMessage (message, 0x90) && getVelocity (message) == 0); }\n"
        "\n"
        "export function getNoteNumber (message)                     { return getByte1 (message); }\n"
        "export function getVelocity (message)                       { return getByte2 (message); }\n"
        "\n"
        "export function isProgramChange (message)                   { return isVoiceMessage (message, 0xc0); }\n"
        "export function getProgramChangeNumber (message)            { return getByte1 (message); }\n"
        "export function isPitchWheel (message)                      { return isVoiceMessage (message, 0xe0); }\n"
        "export function getPitchWheelValue (message)                { return get14BitValue (message); }\n"
        "export function isAftertouch (message)                      { return isVoiceMessage (message, 0xa0); }\n"
        "export function getAfterTouchValue (message)                { return getByte2 (message); }\n"
        "export function isChannelPressure (message)                 { return isVoiceMessage (message, 0xd0); }\n"
        "export function getChannelPressureValue (message)           { return getByte1 (message); }\n"
        "export function isController (message)                      { return isVoiceMessage (message, 0xb0); }\n"
        "export function getControllerNumber (message)               { return getByte1 (message); }\n"
        "export function getControllerValue (message)                { return getByte2 (message); }\n"
        "export function isControllerNumber (message, number)        { return getByte1 (message) == number && isController (message); }\n"
        "export function isAllNotesOff (message)                     { return isControllerNumber (message, 123); }\n"
        "export function isAllSoundOff (message)                     { return isControllerNumber (message, 120); }\n"
        "export function isQuarterFrame (message)                    { return getByte0 (message) == 0xf1; }\n"
        "export function isClock (message)                           { return getByte0 (message) == 0xf8; }\n"
        "export function isStart (message)                           { return getByte0 (message) == 0xfa; }\n"
        "export function isContinue (message)                        { return getByte0 (message) == 0xfb; }\n"
        "export function isStop (message)                            { return getByte0 (message) == 0xfc; }\n"
        "export function isActiveSense (message)                     { return getByte0 (message) == 0xfe; }\n"
        "export function isMetaEvent (message)                       { return getByte0 (message) == 0xff; }\n"
        "export function isSongPositionPointer (message)             { return getByte0 (message) == 0xf2; }\n"
        "export function getSongPositionPointerValue (message)       { return get14BitValue (message); }\n"
        "\n"
        "export function getChromaticScaleIndex (note)               { return (note % 12) & 0xf; }\n"
        "export function getOctaveNumber (note, octaveForMiddleC)    { return ((Math.floor (note / 12) + (octaveForMiddleC ? octaveForMiddleC : 3)) & 0xff) - 5; }\n"
        "export function getNoteName (note)                          { const names = [\"C\", \"C#\", \"D\", \"Eb\", \"E\", \"F\", \"F#\", \"G\", \"G#\", \"A\", \"Bb\", \"B\"]; return names[getChromaticScaleIndex (note)]; }\n"
        "export function getNoteNameWithSharps (note)                { const names = [\"C\", \"C#\", \"D\", \"Eb\", \"E\", \"F\", \"F#\", \"G\", \"G#\", \"A\", \"Bb\", \"B\"]; return names[getChromaticScaleIndex (note)]; }\n"
        "export function getNoteNameWithFlats (note)                 { const names = [\"C\", \"Db\", \"D\", \"Eb\", \"E\", \"F\", \"Gb\", \"G\", \"Ab\", \"A\", \"Bb\", \"B\"]; return names[getChromaticScaleIndex (note)]; }\n"
        "export function getNoteNameWithOctaveNumber (note)          { return getNoteName (note) + getOctaveNumber (note); }\n"
        "export function isNatural (note)                            { const nats = [true, false, true, false, true, true, false, true, false, true, false, true]; return nats[getChromaticScaleIndex (note)]; }\n"
        "export function isAccidental (note)                         { return ! isNatural (note); }\n"
        "\n"
        "export function printHexMIDIData (message)\n"
        "{\n"
        "    const numBytes = getMessageSize (message);\n"
        "\n"
        "    if (numBytes == 0)\n"
        "        return \"[empty]\";\n"
        "\n"
        "    let s = \"\";\n"
        "\n"
        "    for (let i = 0; i < numBytes; ++i)\n"
        "    {\n"
        "        if (i != 0)  s += ' ';\n"
        "\n"
        "        const byte = message >> (16 - 8 * i) & 0xff;\n"
        "        s += \"0123456789abcdef\"[byte >> 4];\n"
        "        s += \"0123456789abcdef\"[byte & 15];\n"
        "    }\n"
        "\n"
        "    return s;\n"
        "}\n"
        "\n"
        "export function getMIDIDescription (message)\n"
        "{\n"
        "    const channelText = \" Channel \" + getChannel1to16 (message);\n"
        "    function getNote (m)   { const s = getNoteNameWithOctaveNumber (getNoteNumber (message)); return s.length < 4 ? s + \" \" : s; };\n"
        "\n"
        "    if (isNoteOn (message))                return \"Note-On:  \"   + getNote (message) + channelText + \"  Velocity \" + getVelocity (message);\n"
        "    if (isNoteOff (message))               return \"Note-Off: \"   + getNote (message) + channelText + \"  Velocity \" + getVelocity (message);\n"
        "    if (isAftertouch (message))            return \"Aftertouch: \" + getNote (message) + channelText +  \": \" + getAfterTouchValue (message);\n"
        "    if (isPitchWheel (message))            return \"Pitch wheel: \" + getPitchWheelValue (message) + ' ' + channelText;\n"
        "    if (isChannelPressure (message))       return \"Channel pressure: \" + getChannelPressureValue (message) + ' ' + channelText;\n"
        "    if (isController (message))            return \"Controller:\" + channelText + \": \" + getControllerName (getControllerNumber (message)) + \" = \" + getControllerValue (message);\n"
        "    if (isProgramChange (message))         return \"Program change: \" + getProgramChangeNumber (message) + ' ' + channelText;\n"
        "    if (isAllNotesOff (message))           return \"All notes off:\" + channelText;\n"
        "    if (isAllSoundOff (message))           return \"All sound off:\" + channelText;\n"
        "    if (isQuarterFrame (message))          return \"Quarter-frame\";\n"
        "    if (isClock (message))                 return \"Clock\";\n"
        "    if (isStart (message))                 return \"Start\";\n"
        "    if (isContinue (message))              return \"Continue\";\n"
        "    if (isStop (message))                  return \"Stop\";\n"
        "    if (isMetaEvent (message))             return \"Meta-event: type \" + getByte1 (message);\n"
        "    if (isSongPositionPointer (message))   return \"Song Position: \" + getSongPositionPointerValue (message);\n"
        "\n"
        "    return printHexMIDIData (message);\n"
        "}\n"
        "\n"
        "export function getControllerName (controllerNumber)\n"
        "{\n"
        "    if (controllerNumber < 128)\n"
        "    {\n"
        "        const controllerNames = [\n"
        "            \"Bank Select\",                  \"Modulation Wheel (coarse)\",      \"Breath controller (coarse)\",       undefined,\n"
        "            \"Foot Pedal (coarse)\",          \"Portamento Time (coarse)\",       \"Data Entry (coarse)\",              \"Volume (coarse)\",\n"
        "            \"Balance (coarse)\",             undefined,                        \"Pan position (coarse)\",            \"Expression (coarse)\",\n"
        "            \"Effect Control 1 (coarse)\",    \"Effect Control 2 (coarse)\",      undefined,                          undefined,\n"
        "            \"General Purpose Slider 1\",     \"General Purpose Slider 2\",       \"General Purpose Slider 3\",         \"General Purpose Slider 4\",\n"
        "            undefined,                      undefined,                        undefined,                          undefined,\n"
        "            undefined,                      undefined,                        undefined,                          undefined,\n"
        "            undefined,                      undefined,                        undefined,                          undefined,\n"
        "            \"Bank Select (fine)\",           \"Modulation Wheel (fine)\",        \"Breath controller (fine)\",         undefined,\n"
        "            \"Foot Pedal (fine)\",            \"Portamento Time (fine)\",         \"Data Entry (fine)\",                \"Volume (fine)\",\n"
        "            \"Balance (fine)\",               undefined,                        \"Pan position (fine)\",              \"Expression (fine)\",\n"
        "            \"Effect Control 1 (fine)\",      \"Effect Control 2 (fine)\",        undefined,                          undefined,\n"
        "            undefined,                      undefined,                        undefined,                          undefined,\n"
        "            undefined,                      undefined,                        undefined,                          undefined,\n"
        "            undefined,                      undefined,                        undefined,                          undefined,\n"
        "            undefined,                      undefined,                        undefined,                          undefined,\n"
        "            \"Hold Pedal\",                   \"Portamento\",                     \"Sustenuto Pedal\",                  \"Soft Pedal\",\n"
        "            \"Legato Pedal\",                 \"Hold 2 Pedal\",                   \"Sound Variation\",                  \"Sound Timbre\",\n"
        "            \"Sound Release Time\",           \"Sound Attack Time\",              \"Sound Brightness\",                 \"Sound Control 6\",\n"
        "            \"Sound Control 7\",              \"Sound Control 8\",                \"Sound Control 9\",                  \"Sound Control 10\",\n"
        "            \"General Purpose Button 1\",     \"General Purpose Button 2\",       \"General Purpose Button 3\",         \"General Purpose Button 4\",\n"
        "            undefined,                      undefined,                        undefined,                          undefined,\n"
        "            undefined,                      undefined,                        undefined,                          \"Reverb Level\",\n"
        "            \"Tremolo Level\",                \"Chorus Level\",                   \"Celeste Level\",                    \"Phaser Level\",\n"
        "            \"Data Button increment\",        \"Data Button decrement\",          \"Non-registered Parameter (fine)\",  \"Non-registered Parameter (coarse)\",\n"
        "            \"Registered Parameter (fine)\",  \"Registered Parameter (coarse)\",  undefined,                          undefined,\n"
        "            undefined,                      undefined,                        undefined,                          undefined,\n"
        "            undefined,                      undefined,                        undefined,                          undefined,\n"
        "            undefined,                      undefined,                        undefined,                          undefined,\n"
        "            undefined,                      undefined,                        undefined,                          undefined,\n"
        "            \"All Sound Off\",                \"All Controllers Off\",            \"Local Keyboard\",                   \"All Notes Off\",\n"
        "            \"Omni Mode Off\",                \"Omni Mode On\",                   \"Mono Operation\",                   \"Poly Operation\"\n"
        "        ];\n"
        "\n"
        "        const name = controllerNames[controllerNumber];\n"
        "\n"
        "        if (name)\n"
        "            return name;\n"
        "    }\n"
        "\n"
        "    return controllerNumber.toString();\n"
        "}\n";
    static constexpr const char* cmaj_api_cmajparametercontrols_js =
        "//\n"
        "//     ,ad888ba,                              88\n"
        "//    d8\"'    \"8b\n"
        "//   d8            88,dba,,adba,   ,aPP8A.A8  88\n"
        "//   Y8,           88    88    88  88     88  88\n"
        "//    Y8a.   .a8P  88    88    88  88,   ,88  88     (C)2024 Cmajor Software Ltd\n"
        "//     '\"Y888Y\"'   88    88    88  '\"8bbP\"Y8  88     https://cmajor.dev\n"
        "//                                           ,88\n"
        "//                                        888P\"\n"
        "//\n"
        "//  This file may be used under the terms of the ISC license:\n"
        "//\n"
        "//  Permission to use, copy, modify, and/or distribute this software for any purpose with or\n"
        "//  without fee is hereby granted, provided that the above copyright notice and this permission\n"
        "//  notice appear in all copies. THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL\n"
        "//  WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY\n"
        "//  AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR\n"
        "//  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,\n"
        "//  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n"
        "//  CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\n"
        "\n"
        "import { PatchConnection } from \"./cmaj-patch-connection.js\";\n"
        "\n"
        "\n"
        "//==============================================================================\n"
        "/** A base class for parameter controls, which automatically connects to a\n"
        " *  PatchConnection to monitor a parameter and provides methods to modify it.\n"
        " */\n"
        "export class ParameterControlBase  extends HTMLElement\n"
        "{\n"
        "    constructor()\n"
        "    {\n"
        "        super();\n"
        "\n"
        "        // prevent any clicks from focusing on this element\n"
        "        this.onmousedown = e => e.stopPropagation();\n"
        "    }\n"
        "\n"
        "    /** Attaches the control to a given PatchConnection and endpoint.\n"
        "     *\n"
        "     * @param {PatchConnection} patchConnection - the connection to connect to, or pass\n"
        "     *                                            undefined to disconnect the control.\n"
        "     * @param {Object} endpointInfo - the endpoint details, as provided by a PatchConnection\n"
        "     *                                in its status callback.\n"
        "     */\n"
        "    setEndpoint (patchConnection, endpointInfo)\n"
        "    {\n"
        "        this.detachListener();\n"
        "\n"
        "        this.patchConnection = patchConnection;\n"
        "        this.endpointInfo = endpointInfo;\n"
        "        this.defaultValue = endpointInfo.annotation?.init || endpointInfo.defaultValue || 0;\n"
        "\n"
        "        if (this.isConnected)\n"
        "            this.attachListener();\n"
        "    }\n"
        "\n"
        "    /** Override this method in a child class, and it will be called when the parameter value changes,\n"
        "     *  so you can update the GUI appropriately.\n"
        "     */\n"
        "    valueChanged (newValue) {}\n"
        "\n"
        "    /** Your GUI can call this when it wants to change the parameter value. */\n"
        "    setValue (value)     { this.patchConnection?.sendEventOrValue (this.endpointInfo.endpointID, value); }\n"
        "\n"
        "    /** Call this before your GUI begins a modification gesture.\n"
        "     *  You might for example call this if the user begins a mouse-drag operation.\n"
        "     */\n"
        "    beginGesture()       { this.patchConnection?.sendParameterGestureStart (this.endpointInfo.endpointID); }\n"
        "\n"
        "    /** Call this after your GUI finishes a modification gesture */\n"
        "    endGesture()         { this.patchConnection?.sendParameterGestureEnd (this.endpointInfo.endpointID); }\n"
        "\n"
        "    /** This calls setValue(), but sandwiches it between some start/end gesture calls.\n"
        "     *  You should use this to make sure a DAW correctly records automatiion for individual value changes\n"
        "     *  that are not part of a gesture.\n"
        "     */\n"
        "    setValueAsGesture (value)\n"
        "    {\n"
        "        this.beginGesture();\n"
        "        this.setValue (value);\n"
        "        this.endGesture();\n"
        "    }\n"
        "\n"
        "    /** Resets the parameter to its default value */\n"
        "    resetToDefault()\n"
        "    {\n"
        "        if (this.defaultValue !== null)\n"
        "            this.setValueAsGesture (this.defaultValue);\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    /** @private */\n"
        "    connectedCallback()\n"
        "    {\n"
        "        this.attachListener();\n"
        "    }\n"
        "\n"
        "    /** @protected */\n"
        "    disconnectedCallback()\n"
        "    {\n"
        "        this.detachListener();\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    detachListener()\n"
        "    {\n"
        "        if (this.listener)\n"
        "        {\n"
        "            this.patchConnection?.removeParameterListener?.(this.listener.endpointID, this.listener);\n"
        "            this.listener = undefined;\n"
        "        }\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    attachListener()\n"
        "    {\n"
        "        if (this.patchConnection && this.endpointInfo)\n"
        "        {\n"
        "            this.detachListener();\n"
        "\n"
        "            this.listener = newValue => this.valueChanged (newValue);\n"
        "            this.listener.endpointID = this.endpointInfo.endpointID;\n"
        "\n"
        "            this.patchConnection.addParameterListener (this.endpointInfo.endpointID, this.listener);\n"
        "            this.patchConnection.requestParameterValue (this.endpointInfo.endpointID);\n"
        "        }\n"
        "    }\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "/** A simple rotary parameter knob control. */\n"
        "export class Knob  extends ParameterControlBase\n"
        "{\n"
        "    constructor (patchConnection, endpointInfo)\n"
        "    {\n"
        "        super();\n"
        "        this.setEndpoint (patchConnection, endpointInfo);\n"
        "    }\n"
        "\n"
        "    setEndpoint (patchConnection, endpointInfo)\n"
        "    {\n"
        "        super.setEndpoint (patchConnection, endpointInfo);\n"
        "\n"
        "        this.innerHTML = \"\";\n"
        "        this.className = \"knob-container\";\n"
        "        const min = endpointInfo?.annotation?.min || 0;\n"
        "        const max = endpointInfo?.annotation?.max || 1;\n"
        "        const mid = endpointInfo?.annotation?.mid || undefined;\n"
        "\n"
        "        const createSvgElement = tag => window.document.createElementNS (\"http://www.w3.org/2000/svg\", tag);\n"
        "\n"
        "        const svg = createSvgElement (\"svg\");\n"
        "        svg.setAttribute (\"viewBox\", \"0 0 100 100\");\n"
        "\n"
        "        const trackBackground = createSvgElement (\"path\");\n"
        "        trackBackground.setAttribute (\"d\", \"M20,76 A 40 40 0 1 1 80 76\");\n"
        "        trackBackground.classList.add (\"knob-path\");\n"
        "        trackBackground.classList.add (\"knob-track-background\");\n"
        "\n"
        "        const maxKnobRotation = 132;\n"
        "        const isBipolar = min + max === 0;\n"
        "        const dashLength = isBipolar ? 251.5 : 184;\n"
        "        const valueOffset = isBipolar ? 0 : 132;\n"
        "        this.getDashOffset = val => dashLength - 184 / (maxKnobRotation * 2) * (val + valueOffset);\n"
        "\n"
        "        this.trackValue = createSvgElement (\"path\");\n"
        "\n"
        "        this.trackValue.setAttribute (\"d\", isBipolar ? \"M50.01,10 A 40 40 0 1 1 50 10\"\n"
        "                                                     : \"M20,76 A 40 40 0 1 1 80 76\");\n"
        "        this.trackValue.setAttribute (\"stroke-dasharray\", dashLength);\n"
        "        this.trackValue.classList.add (\"knob-path\");\n"
        "        this.trackValue.classList.add (\"knob-track-value\");\n"
        "\n"
        "        this.dial = document.createElement (\"div\");\n"
        "        this.dial.className = \"knob-dial\";\n"
        "\n"
        "        const dialTick = document.createElement (\"div\");\n"
        "        dialTick.className = \"knob-dial-tick\";\n"
        "        this.dial.appendChild (dialTick);\n"
        "\n"
        "        svg.appendChild (trackBackground);\n"
        "        svg.appendChild (this.trackValue);\n"
        "\n"
        "        this.appendChild (svg);\n"
        "        this.appendChild (this.dial);\n"
        "\n"
        "        const remap = (source, sourceFrom, sourceTo, targetFrom, targetTo) =>\n"
        "                        (targetFrom + (source - sourceFrom) * (targetTo - targetFrom) / (sourceTo - sourceFrom));\n"
        "\n"
        "        const toValue = (knobRotation) =>\n"
        "        {\n"
        "            if (mid > min && mid < max)\n"
        "            {\n"
        "                const normalisedKnob = remap (knobRotation, -maxKnobRotation, maxKnobRotation, 0, 1);\n"
        "                const range = max - min;\n"
        "                const power = Math.log ((mid - min) / (range)) / Math.log (0.5);\n"
        "\n"
        "                return min + range * Math.pow (normalisedKnob, power);\n"
        "            }\n"
        "            else\n"
        "            {\n"
        "                return remap (knobRotation, -maxKnobRotation, maxKnobRotation, min, max);\n"
        "            }\n"
        "        };\n"
        "\n"
        "        this.toRotation = (value) =>\n"
        "        {\n"
        "            if (mid > min && mid < max)\n"
        "            {\n"
        "                const range = max - min;\n"
        "                const power = Math.log ((mid - min) / (range)) / Math.log (0.5);\n"
        "\n"
        "                const normalisedKnob = Math.pow ((value - min) / range, 1 / power);\n"
        "\n"
        "                return remap (normalisedKnob, 0, 1, -maxKnobRotation, maxKnobRotation);\n"
        "            }\n"
        "            else\n"
        "            {\n"
        "                return remap (value, min, max, -maxKnobRotation, maxKnobRotation);\n"
        "            }\n"
        "        };\n"
        "\n"
        "        this.rotation = this.toRotation (this.defaultValue);\n"
        "        this.setRotation (this.rotation, true);\n"
        "\n"
        "        const onMouseMove = (event) =>\n"
        "        {\n"
        "            event.preventDefault(); // avoid scrolling whilst dragging\n"
        "\n"
        "            const nextRotation = (rotation, delta) =>\n"
        "            {\n"
        "                const clamp = (v, min, max) => Math.min (Math.max (v, min), max);\n"
        "                return clamp (rotation - delta, -maxKnobRotation, maxKnobRotation);\n"
        "            };\n"
        "\n"
        "            const workaroundBrowserIncorrectlyCalculatingMovementY = event.movementY === event.screenY;\n"
        "            const movementY = workaroundBrowserIncorrectlyCalculatingMovementY ? event.screenY - this.previousScreenY\n"
        "                                                                               : event.movementY;\n"
        "            this.previousScreenY = event.screenY;\n"
        "\n"
        "            const speedMultiplier = event.shiftKey ? 0.25 : 1.5;\n"
        "            this.accumulatedRotation = nextRotation (this.accumulatedRotation, movementY * speedMultiplier);\n"
        "            this.setValue (toValue (this.accumulatedRotation));\n"
        "        };\n"
        "\n"
        "        const onMouseUp = (event) =>\n"
        "        {\n"
        "            this.previousScreenY = undefined;\n"
        "            this.accumulatedRotation = undefined;\n"
        "            window.removeEventListener (\"mousemove\", onMouseMove);\n"
        "            window.removeEventListener (\"mouseup\", onMouseUp);\n"
        "            this.endGesture();\n"
        "        };\n"
        "\n"
        "        const onMouseDown = (event) =>\n"
        "        {\n"
        "            this.previousScreenY = event.screenY;\n"
        "            this.accumulatedRotation = this.rotation;\n"
        "            this.beginGesture();\n"
        "            window.addEventListener (\"mousemove\", onMouseMove);\n"
        "            window.addEventListener (\"mouseup\", onMouseUp);\n"
        "            event.preventDefault();\n"
        "        };\n"
        "\n"
        "        const onTouchStart = (event) =>\n"
        "        {\n"
        "            this.previousClientY = event.changedTouches[0].clientY;\n"
        "            this.accumulatedRotation = this.rotation;\n"
        "            this.touchIdentifier = event.changedTouches[0].identifier;\n"
        "            this.beginGesture();\n"
        "            window.addEventListener (\"touchmove\", onTouchMove);\n"
        "            window.addEventListener (\"touchend\", onTouchEnd);\n"
        "            event.preventDefault();\n"
        "        };\n"
        "\n"
        "        const onTouchMove = (event) =>\n"
        "        {\n"
        "            for (const touch of event.changedTouches)\n"
        "            {\n"
        "                if (touch.identifier == this.touchIdentifier)\n"
        "                {\n"
        "                    const nextRotation = (rotation, delta) =>\n"
        "                    {\n"
        "                        const clamp = (v, min, max) => Math.min (Math.max (v, min), max);\n"
        "                        return clamp (rotation - delta, -maxKnobRotation, maxKnobRotation);\n"
        "                    };\n"
        "\n"
        "                    const movementY = touch.clientY - this.previousClientY;\n"
        "                    this.previousClientY = touch.clientY;\n"
        "\n"
        "                    const speedMultiplier = event.shiftKey ? 0.25 : 1.5;\n"
        "                    this.accumulatedRotation = nextRotation (this.accumulatedRotation, movementY * speedMultiplier);\n"
        "                    this.setValue (toValue (this.accumulatedRotation));\n"
        "                }\n"
        "            }\n"
        "        };\n"
        "\n"
        "        const onTouchEnd = (event) =>\n"
        "        {\n"
        "            this.previousClientY = undefined;\n"
        "            this.accumulatedRotation = undefined;\n"
        "            window.removeEventListener (\"touchmove\", onTouchMove);\n"
        "            window.removeEventListener (\"touchend\", onTouchEnd);\n"
        "            this.endGesture();\n"
        "        };\n"
        "\n"
        "        this.addEventListener (\"mousedown\", onMouseDown);\n"
        "        this.addEventListener (\"dblclick\", () => this.resetToDefault());\n"
        "        this.addEventListener ('touchstart', onTouchStart);\n"
        "    }\n"
        "\n"
        "    /** Returns true if this type of control is suitable for the given endpoint info */\n"
        "    static canBeUsedFor (endpointInfo)\n"
        "    {\n"
        "        return endpointInfo.purpose === \"parameter\";\n"
        "    }\n"
        "\n"
        "    /** @override */\n"
        "    valueChanged (newValue)       { this.setRotation (this.toRotation (newValue), false); }\n"
        "\n"
        "    /** Returns a string version of the given value */\n"
        "    getDisplayValue (v)           { return toFloatDisplayValueWithUnit (v, this.endpointInfo); }\n"
        "\n"
        "    /** @private */\n"
        "    setRotation (degrees, force)\n"
        "    {\n"
        "        if (force || this.rotation !== degrees)\n"
        "        {\n"
        "            this.rotation = degrees;\n"
        "            this.trackValue.setAttribute (\"stroke-dashoffset\", this.getDashOffset (this.rotation));\n"
        "            this.dial.style.transform = `translate(-50%,-50%) rotate(${degrees}deg)`;\n"
        "        }\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    static getCSS()\n"
        "    {\n"
        "        return `\n"
        "        .knob-container {\n"
        "            --knob-track-background-color: var(--background);\n"
        "            --knob-track-value-color: var(--foreground);\n"
        "\n"
        "            --knob-dial-border-color: var(--foreground);\n"
        "            --knob-dial-background-color: var(--background);\n"
        "            --knob-dial-tick-color: var(--foreground);\n"
        "\n"
        "            position: relative;\n"
        "            display: inline-block;\n"
        "            height: 5rem;\n"
        "            width: 5rem;\n"
        "            margin: 0;\n"
        "            padding: 0;\n"
        "        }\n"
        "\n"
        "        .knob-path {\n"
        "            fill: none;\n"
        "            stroke-linecap: round;\n"
        "            stroke-width: 0.15rem;\n"
        "        }\n"
        "\n"
        "        .knob-track-background {\n"
        "            stroke: var(--knob-track-background-color);\n"
        "        }\n"
        "\n"
        "        .knob-track-value {\n"
        "            stroke: var(--knob-track-value-color);\n"
        "        }\n"
        "\n"
        "        .knob-dial {\n"
        "            position: absolute;\n"
        "            text-align: center;\n"
        "            height: 60%;\n"
        "            width: 60%;\n"
        "            top: 50%;\n"
        "            left: 50%;\n"
        "            border: 0.15rem solid var(--knob-dial-border-color);\n"
        "            border-radius: 100%;\n"
        "            box-sizing: border-box;\n"
        "            transform: translate(-50%,-50%);\n"
        "            background-color: var(--knob-dial-background-color);\n"
        "        }\n"
        "\n"
        "        .knob-dial-tick {\n"
        "            position: absolute;\n"
        "            display: inline-block;\n"
        "\n"
        "            height: 1rem;\n"
        "            width: 0.15rem;\n"
        "            background-color: var(--knob-dial-tick-color);\n"
        "        }`;\n"
        "    }\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "/** A boolean switch control */\n"
        "export class Switch  extends ParameterControlBase\n"
        "{\n"
        "    constructor (patchConnection, endpointInfo)\n"
        "    {\n"
        "        super();\n"
        "        this.setEndpoint (patchConnection, endpointInfo);\n"
        "    }\n"
        "\n"
        "    setEndpoint (patchConnection, endpointInfo)\n"
        "    {\n"
        "        super.setEndpoint (patchConnection, endpointInfo);\n"
        "\n"
        "        const outer = document.createElement (\"div\");\n"
        "        outer.classList = \"switch-outline\";\n"
        "\n"
        "        const inner = document.createElement (\"div\");\n"
        "        inner.classList = \"switch-thumb\";\n"
        "\n"
        "        this.innerHTML = \"\";\n"
        "        this.currentValue = this.defaultValue > 0.5;\n"
        "        this.valueChanged (this.currentValue);\n"
        "        this.classList.add (\"switch-container\");\n"
        "\n"
        "        outer.appendChild (inner);\n"
        "        this.appendChild (outer);\n"
        "        this.addEventListener (\"click\", () => this.setValueAsGesture (this.currentValue ? 0 : 1.0));\n"
        "    }\n"
        "\n"
        "    /** Returns true if this type of control is suitable for the given endpoint info */\n"
        "    static canBeUsedFor (endpointInfo)\n"
        "    {\n"
        "        return endpointInfo.purpose === \"parameter\"\n"
        "                && endpointInfo.annotation?.boolean;\n"
        "    }\n"
        "\n"
        "    /** @override */\n"
        "    valueChanged (newValue)\n"
        "    {\n"
        "        const b = newValue > 0.5;\n"
        "        this.currentValue = b;\n"
        "        this.classList.remove (! b ? \"switch-on\" : \"switch-off\");\n"
        "        this.classList.add (b ? \"switch-on\" : \"switch-off\");\n"
        "    }\n"
        "\n"
        "    /** Returns a string version of the given value */\n"
        "    getDisplayValue (v)   { return `${v > 0.5 ? \"On\" : \"Off\"}`; }\n"
        "\n"
        "    /** @private */\n"
        "    static getCSS()\n"
        "    {\n"
        "        return `\n"
        "        .switch-container {\n"
        "            --switch-outline-color: var(--foreground);\n"
        "            --switch-thumb-color: var(--foreground);\n"
        "            --switch-on-background-color: var(--background);\n"
        "            --switch-off-background-color: var(--background);\n"
        "\n"
        "            position: relative;\n"
        "            display: flex;\n"
        "            align-items: center;\n"
        "            justify-content: center;\n"
        "            height: 100%;\n"
        "            width: 100%;\n"
        "            margin: 0;\n"
        "            padding: 0;\n"
        "        }\n"
        "\n"
        "        .switch-outline {\n"
        "            position: relative;\n"
        "            display: inline-block;\n"
        "            height: 1.5rem;\n"
        "            width: 2.5rem;\n"
        "            border-radius: 1rem;\n"
        "            border: var(--switch-outline-color) solid 0.15rem;\n"
        "            transition: background-color 0.1s cubic-bezier(0.5, 0, 0.2, 1);\n"
        "        }\n"
        "\n"
        "        .switch-thumb {\n"
        "            position: absolute;\n"
        "            top: 50%;\n"
        "            left: 50%;\n"
        "            transform: translate(-50%,-50%);\n"
        "            height: 0.9rem;\n"
        "            width:  0.9rem;\n"
        "            background-color: var(--switch-thumb-color);\n"
        "            border-radius: 100%;\n"
        "            transition: left 0.1s cubic-bezier(0.5, 0, 0.2, 1);\n"
        "        }\n"
        "\n"
        "        .switch-off .switch-thumb {\n"
        "            left: 25%;\n"
        "            background: none;\n"
        "            border: var(--switch-thumb-color) solid 0.1rem;\n"
        "            height: 0.8rem;\n"
        "            width: 0.8rem;\n"
        "        }\n"
        "        .switch-on .switch-thumb {\n"
        "            left: 75%;\n"
        "        }\n"
        "\n"
        "        .switch-off .switch-outline {\n"
        "            background-color: var(--switch-on-background-color);\n"
        "        }\n"
        "        .switch-on .switch-outline {\n"
        "            background-color: var(--switch-off-background-color);\n"
        "        }`;\n"
        "    }\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "function toFloatDisplayValueWithUnit (v, endpointInfo)\n"
        "{\n"
        "    return `${v.toFixed (2)} ${endpointInfo.annotation?.unit ?\? \"\"}`;\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "/** A control that allows an item to be selected from a drop-down list of options */\n"
        "export class Options  extends ParameterControlBase\n"
        "{\n"
        "    constructor (patchConnection, endpointInfo)\n"
        "    {\n"
        "        super();\n"
        "        this.setEndpoint (patchConnection, endpointInfo);\n"
        "    }\n"
        "\n"
        "    setEndpoint (patchConnection, endpointInfo)\n"
        "    {\n"
        "        super.setEndpoint (patchConnection, endpointInfo);\n"
        "\n"
        "        const toValue = (min, step, index) => min + (step * index);\n"
        "        const toStepCount = count => count > 0 ? count - 1 : 1;\n"
        "\n"
        "        const { min, max, options } = (() =>\n"
        "        {\n"
        "            if (Options.hasTextOptions (endpointInfo))\n"
        "            {\n"
        "                const optionList = endpointInfo.annotation.text.split (\"|\");\n"
        "                const stepCount = toStepCount (optionList.length);\n"
        "                let min = 0, max = stepCount, step = 1;\n"
        "\n"
        "                if (endpointInfo.annotation.min != null && endpointInfo.annotation.max != null)\n"
        "                {\n"
        "                    min = endpointInfo.annotation.min;\n"
        "                    max = endpointInfo.annotation.max;\n"
        "                    step = (max - min) / stepCount;\n"
        "                }\n"
        "\n"
        "                const options = optionList.map ((text, index) => ({ value: toValue (min, step, index), text }));\n"
        "\n"
        "                return { min, max, options };\n"
        "            }\n"
        "\n"
        "            if (Options.isExplicitlyDiscrete (endpointInfo))\n"
        "            {\n"
        "                const step = endpointInfo.annotation.step;\n"
        "\n"
        "                const min = endpointInfo.annotation?.min || 0;\n"
        "                const max = endpointInfo.annotation?.max || 1;\n"
        "\n"
        "                const numDiscreteOptions = (((max - min) / step) | 0) + 1;\n"
        "\n"
        "                const options = new Array (numDiscreteOptions);\n"
        "                for (let i = 0; i < numDiscreteOptions; ++i)\n"
        "                {\n"
        "                    const value = toValue (min, step, i);\n"
        "                    options[i] = { value, text: toFloatDisplayValueWithUnit (value, endpointInfo) };\n"
        "                }\n"
        "\n"
        "                return { min, max, options };\n"
        "            }\n"
        "        })();\n"
        "\n"
        "        this.options = options;\n"
        "\n"
        "        const stepCount = toStepCount (this.options.length);\n"
        "        const normalise = value => (value - min) / (max - min);\n"
        "        this.toIndex = value => Math.min (stepCount, normalise (value) * this.options.length) | 0;\n"
        "\n"
        "        this.innerHTML = \"\";\n"
        "\n"
        "        this.select = document.createElement (\"select\");\n"
        "\n"
        "        for (const option of this.options)\n"
        "        {\n"
        "            const optionElement = document.createElement (\"option\");\n"
        "            optionElement.innerText = option.text;\n"
        "            this.select.appendChild (optionElement);\n"
        "        }\n"
        "\n"
        "        this.selectedIndex = this.toIndex (this.defaultValue);\n"
        "\n"
        "        this.select.addEventListener (\"change\", (e) =>\n"
        "        {\n"
        "            const newIndex = e.target.selectedIndex;\n"
        "\n"
        "            // prevent local state change. the caller will update us when the backend actually applies the update\n"
        "            e.target.selectedIndex = this.selectedIndex;\n"
        "\n"
        "            this.setValueAsGesture (this.options[newIndex].value)\n"
        "        });\n"
        "\n"
        "        this.valueChanged (this.selectedIndex);\n"
        "\n"
        "        this.className = \"select-container\";\n"
        "        this.appendChild (this.select);\n"
        "\n"
        "        const icon = document.createElement (\"span\");\n"
        "        icon.className = \"select-icon\";\n"
        "        this.appendChild (icon);\n"
        "    }\n"
        "\n"
        "    /** Returns true if this type of control is suitable for the given endpoint info */\n"
        "    static canBeUsedFor (endpointInfo)\n"
        "    {\n"
        "        return endpointInfo.purpose === \"parameter\"\n"
        "                && (this.hasTextOptions (endpointInfo) || this.isExplicitlyDiscrete (endpointInfo));\n"
        "    }\n"
        "\n"
        "    /** @override */\n"
        "    valueChanged (newValue)\n"
        "    {\n"
        "        const index = this.toIndex (newValue);\n"
        "        this.selectedIndex = index;\n"
        "        this.select.selectedIndex = index;\n"
        "    }\n"
        "\n"
        "    /** Returns a string version of the given value */\n"
        "    getDisplayValue (v)    { return this.options[this.toIndex(v)].text; }\n"
        "\n"
        "    /** @private */\n"
        "    static hasTextOptions (endpointInfo)\n"
        "    {\n"
        "        return endpointInfo.annotation?.text?.split?.(\"|\").length > 1\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    static isExplicitlyDiscrete (endpointInfo)\n"
        "    {\n"
        "        return endpointInfo.annotation?.discrete && endpointInfo.annotation?.step > 0;\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    static getCSS()\n"
        "    {\n"
        "        return `\n"
        "        .select-container {\n"
        "            position: relative;\n"
        "            display: block;\n"
        "            font-size: 0.8rem;\n"
        "            width: 100%;\n"
        "            color: var(--foreground);\n"
        "            border: 0.15rem solid var(--foreground);\n"
        "            border-radius: 0.6rem;\n"
        "            margin: 0;\n"
        "            padding: 0;\n"
        "        }\n"
        "\n"
        "        select {\n"
        "            background: none;\n"
        "            appearance: none;\n"
        "            -webkit-appearance: none;\n"
        "            font-family: inherit;\n"
        "            font-size: 0.8rem;\n"
        "\n"
        "            overflow: hidden;\n"
        "            text-overflow: ellipsis;\n"
        "\n"
        "            padding: 0 1.5rem 0 0.6rem;\n"
        "\n"
        "            outline: none;\n"
        "            color: var(--foreground);\n"
        "            height: 2rem;\n"
        "            box-sizing: border-box;\n"
        "            margin: 0;\n"
        "            border: none;\n"
        "\n"
        "            width: 100%;\n"
        "        }\n"
        "\n"
        "        select option {\n"
        "            background: var(--background);\n"
        "            color: var(--foreground);\n"
        "        }\n"
        "\n"
        "        .select-icon {\n"
        "            position: absolute;\n"
        "            right: 0.3rem;\n"
        "            top: 0.5rem;\n"
        "            pointer-events: none;\n"
        "            background-color: var(--foreground);\n"
        "            width: 1.4em;\n"
        "            height: 1.4em;\n"
        "            mask: url(\"data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24'%3E%3Cpath d='M17,9.17a1,1,0,0,0-1.41,0L12,12.71,8.46,9.17a1,1,0,0,0-1.41,0,1,1,0,0,0,0,1.42l4.24,4.24a1,1,0,0,0,1.42,0L17,10.59A1,1,0,0,0,17,9.17Z'/%3E%3C/svg%3E\");\n"
        "            mask-repeat: no-repeat;\n"
        "            -webkit-mask: url(\"data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24'%3E%3Cpath d='M17,9.17a1,1,0,0,0-1.41,0L12,12.71,8.46,9.17a1,1,0,0,0-1.41,0,1,1,0,0,0,0,1.42l4.24,4.24a1,1,0,0,0,1.42,0L17,10.59A1,1,0,0,0,17,9.17Z'/%3E%3C/svg%3E\");\n"
        "            -webkit-mask-repeat: no-repeat;\n"
        "        }`;\n"
        "    }\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "/** A control which wraps a child control, adding a label and value display box below it */\n"
        "export class LabelledControlHolder  extends ParameterControlBase\n"
        "{\n"
        "    constructor (patchConnection, endpointInfo, childControl)\n"
        "    {\n"
        "        super();\n"
        "        this.childControl = childControl;\n"
        "        this.setEndpoint (patchConnection, endpointInfo);\n"
        "    }\n"
        "\n"
        "    setEndpoint (patchConnection, endpointInfo)\n"
        "    {\n"
        "        super.setEndpoint (patchConnection, endpointInfo);\n"
        "\n"
        "        this.innerHTML = \"\";\n"
        "        this.className = \"labelled-control\";\n"
        "\n"
        "        const centeredControl = document.createElement (\"div\");\n"
        "        centeredControl.className = \"labelled-control-centered-control\";\n"
        "\n"
        "        centeredControl.appendChild (this.childControl);\n"
        "\n"
        "        const titleValueHoverContainer = document.createElement (\"div\");\n"
        "        titleValueHoverContainer.className = \"labelled-control-label-container\";\n"
        "\n"
        "        const nameText = document.createElement (\"div\");\n"
        "        nameText.classList.add (\"labelled-control-name\");\n"
        "        nameText.innerText = endpointInfo.annotation?.name || endpointInfo.name || endpointInfo.endpointID || \"\";\n"
        "\n"
        "        this.valueText = document.createElement (\"div\");\n"
        "        this.valueText.classList.add (\"labelled-control-value\");\n"
        "\n"
        "        titleValueHoverContainer.appendChild (nameText);\n"
        "        titleValueHoverContainer.appendChild (this.valueText);\n"
        "\n"
        "        this.appendChild (centeredControl);\n"
        "        this.appendChild (titleValueHoverContainer);\n"
        "    }\n"
        "\n"
        "    /** @override */\n"
        "    valueChanged (newValue)\n"
        "    {\n"
        "        this.valueText.innerText = this.childControl?.getDisplayValue (newValue);\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    static getCSS()\n"
        "    {\n"
        "        return `\n"
        "        .labelled-control {\n"
        "            --labelled-control-font-color: var(--foreground);\n"
        "            --labelled-control-font-size: 0.8rem;\n"
        "\n"
        "            position: relative;\n"
        "            display: inline-block;\n"
        "            margin: 0 0.4rem 0.4rem;\n"
        "            vertical-align: top;\n"
        "            text-align: left;\n"
        "            padding: 0;\n"
        "        }\n"
        "\n"
        "        .labelled-control-centered-control {\n"
        "            position: relative;\n"
        "            display: flex;\n"
        "            align-items: center;\n"
        "            justify-content: center;\n"
        "\n"
        "            width: 5.5rem;\n"
        "            height: 5rem;\n"
        "        }\n"
        "\n"
        "        .labelled-control-label-container {\n"
        "            position: relative;\n"
        "            display: block;\n"
        "            max-width: 5.5rem;\n"
        "            margin: -0.4rem auto 0.4rem;\n"
        "            text-align: center;\n"
        "            font-size: var(--labelled-control-font-size);\n"
        "            color: var(--labelled-control-font-color);\n"
        "            cursor: default;\n"
        "        }\n"
        "\n"
        "        .labelled-control-name {\n"
        "            overflow: hidden;\n"
        "            text-overflow: ellipsis;\n"
        "        }\n"
        "\n"
        "        .labelled-control-value {\n"
        "            position: absolute;\n"
        "            top: 0;\n"
        "            left: 0;\n"
        "            right: 0;\n"
        "            overflow: hidden;\n"
        "            text-overflow: ellipsis;\n"
        "            opacity: 0;\n"
        "        }\n"
        "\n"
        "        .labelled-control:hover .labelled-control-name,\n"
        "        .labelled-control:active .labelled-control-name {\n"
        "            opacity: 0;\n"
        "        }\n"
        "        .labelled-control:hover .labelled-control-value,\n"
        "        .labelled-control:active .labelled-control-value {\n"
        "            opacity: 1;\n"
        "        }`;\n"
        "    }\n"
        "}\n"
        "\n"
        "if (! window.customElements.get (\"cmaj-knob-control\"))             window.customElements.define (\"cmaj-knob-control\", Knob);\n"
        "if (! window.customElements.get (\"cmaj-switch-control\"))           window.customElements.define (\"cmaj-switch-control\", Switch);\n"
        "if (! window.customElements.get (\"cmaj-options-control\"))          window.customElements.define (\"cmaj-options-control\", Options);\n"
        "if (! window.customElements.get (\"cmaj-labelled-control-holder\"))  window.customElements.define (\"cmaj-labelled-control-holder\", LabelledControlHolder);\n"
        "\n"
        "\n"
        "//==============================================================================\n"
        "/** Fetches all the CSS for the controls defined in this module */\n"
        "export function getAllCSS()\n"
        "{\n"
        "    return `\n"
        "        ${Options.getCSS()}\n"
        "        ${Knob.getCSS()}\n"
        "        ${Switch.getCSS()}\n"
        "        ${LabelledControlHolder.getCSS()}`;\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "/** Creates a suitable control for the given endpoint.\n"
        " *\n"
        " *  @param {PatchConnection} patchConnection - the connection to connect to\n"
        " *  @param {Object} endpointInfo - the endpoint details, as provided by a PatchConnection\n"
        " *                                 in its status callback.\n"
        "*/\n"
        "export function createControl (patchConnection, endpointInfo)\n"
        "{\n"
        "    if (Switch.canBeUsedFor (endpointInfo))\n"
        "        return new (window.customElements.get (\"cmaj-switch-control\")) (patchConnection, endpointInfo);\n"
        "\n"
        "    if (Options.canBeUsedFor (endpointInfo))\n"
        "        return new (window.customElements.get (\"cmaj-options-control\")) (patchConnection, endpointInfo);\n"
        "\n"
        "    if (Knob.canBeUsedFor (endpointInfo))\n"
        "        return new (window.customElements.get (\"cmaj-knob-control\")) (patchConnection, endpointInfo);\n"
        "\n"
        "    return undefined;\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "/** Creates a suitable labelled control for the given endpoint.\n"
        " *\n"
        " *  @param {PatchConnection} patchConnection - the connection to connect to\n"
        " *  @param {Object} endpointInfo - the endpoint details, as provided by a PatchConnection\n"
        " *                                 in its status callback.\n"
        "*/\n"
        "export function createLabelledControl (patchConnection, endpointInfo)\n"
        "{\n"
        "    const control = createControl (patchConnection, endpointInfo);\n"
        "\n"
        "    if (control)\n"
        "        return new (window.customElements.get (\"cmaj-labelled-control-holder\")) (patchConnection, endpointInfo, control);\n"
        "\n"
        "    return undefined;\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "/** Takes a patch connection and its current status object, and tries to create\n"
        " *  a control for the given endpoint ID.\n"
        " *\n"
        " *  @param {PatchConnection} patchConnection - the connection to connect to\n"
        " *  @param {Object} status - the connection's current status\n"
        " *  @param {string} endpointID - the endpoint you'd like to control\n"
        " */\n"
        "export function createLabelledControlForEndpointID (patchConnection, status, endpointID)\n"
        "{\n"
        "    for (const endpointInfo of status?.details?.inputs)\n"
        "        if (endpointInfo.endpointID == endpointID)\n"
        "            return createLabelledControl (patchConnection, endpointInfo);\n"
        "\n"
        "    return undefined;\n"
        "}\n";
    static constexpr const char* cmaj_api_cmajpatchview_js =
        "//\n"
        "//     ,ad888ba,                              88\n"
        "//    d8\"'    \"8b\n"
        "//   d8            88,dba,,adba,   ,aPP8A.A8  88\n"
        "//   Y8,           88    88    88  88     88  88\n"
        "//    Y8a.   .a8P  88    88    88  88,   ,88  88     (C)2024 Cmajor Software Ltd\n"
        "//     '\"Y888Y\"'   88    88    88  '\"8bbP\"Y8  88     https://cmajor.dev\n"
        "//                                           ,88\n"
        "//                                        888P\"\n"
        "//\n"
        "//  This file may be used under the terms of the ISC license:\n"
        "//\n"
        "//  Permission to use, copy, modify, and/or distribute this software for any purpose with or\n"
        "//  without fee is hereby granted, provided that the above copyright notice and this permission\n"
        "//  notice appear in all copies. THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL\n"
        "//  WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY\n"
        "//  AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR\n"
        "//  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,\n"
        "//  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n"
        "//  CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\n"
        "\n"
        "import { PatchConnection } from \"./cmaj-patch-connection.js\"\n"
        "\n"
        "//==============================================================================\n"
        "/** Returns a list of types of view that can be created for this patch.\n"
        " */\n"
        "export function getAvailableViewTypes (patchConnection)\n"
        "{\n"
        "    if (! patchConnection)\n"
        "        return [];\n"
        "\n"
        "    if (patchConnection.manifest?.view?.src)\n"
        "        return [\"custom\", \"generic\"];\n"
        "\n"
        "    return [\"generic\"];\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "/** Creates and returns a HTMLElement view which can be shown to control this patch.\n"
        " *\n"
        " *  If no preferredType argument is supplied, this will return either a custom patch-specific\n"
        " *  view (if the manifest specifies one), or a generic view if not. The preferredType argument\n"
        " *  can be used to choose one of the types of view returned by getAvailableViewTypes().\n"
        " *\n"
        " *  @param {PatchConnection} patchConnection - the connection to use\n"
        " *  @param {string} preferredType - the name of the type of view to open, e.g. \"generic\"\n"
        " *                                  or the name of one of the views in the manifest\n"
        " *  @returns {HTMLElement} a HTMLElement that can be displayed as the patch GUI\n"
        " */\n"
        "export async function createPatchView (patchConnection, preferredType)\n"
        "{\n"
        "    if (patchConnection?.manifest)\n"
        "    {\n"
        "        let view = patchConnection.manifest.view;\n"
        "\n"
        "        if (view && preferredType === \"generic\")\n"
        "            if (view.src)\n"
        "                view = undefined;\n"
        "\n"
        "        const viewModuleURL = view?.src ? patchConnection.getResourceAddress (view.src) : \"./cmaj-generic-patch-view.js\";\n"
        "        const viewModule = await import (viewModuleURL);\n"
        "        const patchView = await viewModule?.default (patchConnection);\n"
        "\n"
        "        if (patchView)\n"
        "        {\n"
        "            patchView.style.display = \"block\";\n"
        "\n"
        "            if (view?.width > 10)\n"
        "                patchView.style.width = view.width + \"px\";\n"
        "            else\n"
        "                patchView.style.width = undefined;\n"
        "\n"
        "            if (view?.height > 10)\n"
        "                patchView.style.height = view.height + \"px\";\n"
        "            else\n"
        "                patchView.style.height = undefined;\n"
        "\n"
        "            return patchView;\n"
        "        }\n"
        "    }\n"
        "\n"
        "    return undefined;\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "/** If a patch view declares itself to be scalable, this will attempt to scale it to fit\n"
        " *  into a given parent element.\n"
        " *\n"
        " *  @param {HTMLElement} view - the patch view\n"
        " *  @param {HTMLElement} parentToScale - the patch view's direct parent element, to which\n"
        " *                                       the scale factor will be applied\n"
        " *  @param {HTMLElement} parentContainerToFitTo - an outer parent of the view, whose bounds\n"
        " *                                                the view will be made to fit\n"
        " */\n"
        "export function scalePatchViewToFit (view, parentToScale, parentContainerToFitTo)\n"
        "{\n"
        "    function getClientSize (view)\n"
        "    {\n"
        "        const clientStyle = getComputedStyle (view);\n"
        "\n"
        "        return {\n"
        "            width:  view.clientHeight - parseFloat (clientStyle.paddingTop)  - parseFloat (clientStyle.paddingBottom),\n"
        "            height: view.clientWidth  - parseFloat (clientStyle.paddingLeft) - parseFloat (clientStyle.paddingRight)\n"
        "        };\n"
        "    }\n"
        "\n"
        "    const scaleLimits = view.getScaleFactorLimits?.();\n"
        "\n"
        "    if (scaleLimits && (scaleLimits.minScale || scaleLimits.maxScale) && parentContainerToFitTo)\n"
        "    {\n"
        "        const minScale = scaleLimits.minScale || 0.25;\n"
        "        const maxScale = scaleLimits.maxScale || 5.0;\n"
        "\n"
        "        const targetSize = getClientSize (parentContainerToFitTo);\n"
        "        const clientSize = getClientSize (view);\n"
        "\n"
        "        const scaleW = targetSize.width / clientSize.width;\n"
        "        const scaleH = targetSize.height / clientSize.height;\n"
        "\n"
        "        const scale = Math.min (maxScale, Math.max (minScale, Math.min (scaleW, scaleH)));\n"
        "\n"
        "        parentToScale.style.transform = `scale(${scale})`;\n"
        "    }\n"
        "    else\n"
        "    {\n"
        "        parentToScale.style.transform = \"none\";\n"
        "    }\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "class PatchViewHolder extends HTMLElement\n"
        "{\n"
        "    constructor (view)\n"
        "    {\n"
        "        super();\n"
        "        this.view = view;\n"
        "        this.style = `display: block; position: relative; width: 100%; height: 100%; overflow: visible; transform-origin: 0% 0%;`;\n"
        "    }\n"
        "\n"
        "    connectedCallback()\n"
        "    {\n"
        "        this.appendChild (this.view);\n"
        "        this.resizeObserver = new ResizeObserver (() => scalePatchViewToFit (this.view, this, this.parentElement));\n"
        "        this.resizeObserver.observe (this.parentElement);\n"
        "        scalePatchViewToFit (this.view, this, this.parentElement);\n"
        "    }\n"
        "\n"
        "    disconnectedCallback()\n"
        "    {\n"
        "        this.resizeObserver = undefined;\n"
        "        this.innerHTML = \"\";\n"
        "    }\n"
        "}\n"
        "\n"
        "//==============================================================================\n"
        "/** Creates and returns a HTMLElement view which can be shown to control this patch.\n"
        " *\n"
        " *  Unlike createPatchView(), this will return a holder element that handles scaling\n"
        " *  and resizing, and which follows changes to the size of the parent that you\n"
        " *  append it to.\n"
        " *\n"
        " *  If no preferredType argument is supplied, this will return either a custom patch-specific\n"
        " *  view (if the manifest specifies one), or a generic view if not. The preferredType argument\n"
        " *  can be used to choose one of the types of view returned by getAvailableViewTypes().\n"
        " *\n"
        " *  @param {PatchConnection} patchConnection - the connection to use\n"
        " *  @param {string} preferredType - the name of the type of view to open, e.g. \"generic\"\n"
        " *                                  or the name of one of the views in the manifest\n"
        " *  @returns {HTMLElement} a HTMLElement that can be displayed as the patch GUI\n"
        " */\n"
        "export async function createPatchViewHolder (patchConnection, preferredType)\n"
        "{\n"
        "    const view = await createPatchView (patchConnection, preferredType);\n"
        "\n"
        "    if (view)\n"
        "    {\n"
        "        const patchViewHolderName = \"cmaj-patch-view-holder\";\n"
        "\n"
        "        if (! window.customElements.get (patchViewHolderName)) window.customElements.define (patchViewHolderName, PatchViewHolder);\n"
        "\n"
        "        return new (window.customElements.get (patchViewHolderName)) (view);\n"
        "    }\n"
        "}\n";
    static constexpr const char* cmaj_api_cmajpianokeyboard_js =
        "//\n"
        "//     ,ad888ba,                              88\n"
        "//    d8\"'    \"8b\n"
        "//   d8            88,dba,,adba,   ,aPP8A.A8  88     The Cmajor Toolkit\n"
        "//   Y8,           88    88    88  88     88  88\n"
        "//    Y8a.   .a8P  88    88    88  88,   ,88  88     (C)2024 Cmajor Software Ltd\n"
        "//     '\"Y888Y\"'   88    88    88  '\"8bbP\"Y8  88     https://cmajor.dev\n"
        "//                                           ,88\n"
        "//                                        888P\"\n"
        "//\n"
        "//  The Cmajor project is subject to commercial or open-source licensing.\n"
        "//  You may use it under the terms of the GPLv3 (see www.gnu.org/licenses), or\n"
        "//  visit https://cmajor.dev to learn about our commercial licence options.\n"
        "//\n"
        "//  CMAJOR IS PROVIDED \"AS IS\" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER\n"
        "//  EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE\n"
        "//  DISCLAIMED.\n"
        "\n"
        "import * as midi from \"./cmaj-midi-helpers.js\"\n"
        "\n"
        "/**\n"
        " *  An general-purpose on-screen piano keyboard component that allows clicks or\n"
        " *  key-presses to be used to play things.\n"
        " *\n"
        " *  To receive events, you can attach \"note-down\" and \"note-up\" event listeners via\n"
        " *  the standard HTMLElement/EventTarget event system, e.g.\n"
        " *\n"
        " *  myKeyboardElement.addEventListener(\"note-down\", (note) => { ...handle note on... });\n"
        " *  myKeyboardElement.addEventListener(\"note-up\",   (note) => { ...handle note off... });\n"
        " *\n"
        " *  The `note` object will contain a `note` property with the MIDI note number.\n"
        " *  (And obviously you can remove them with removeEventListener)\n"
        " *\n"
        " *  Or, if you're connecting the keyboard to a PatchConnection, you can use the helper\n"
        " *  method attachToPatchConnection() to create and attach some suitable listeners.\n"
        " *\n"
        " */\n"
        "export default class PianoKeyboard extends HTMLElement\n"
        "{\n"
        "    constructor ({ naturalNoteWidth,\n"
        "                   accidentalWidth,\n"
        "                   accidentalPercentageHeight,\n"
        "                   naturalNoteBorder,\n"
        "                   accidentalNoteBorder,\n"
        "                   pressedNoteColour } = {})\n"
        "    {\n"
        "        super();\n"
        "\n"
        "        this.naturalWidth = naturalNoteWidth || 20;\n"
        "        this.accidentalWidth = accidentalWidth || 12;\n"
        "        this.accidentalPercentageHeight = accidentalPercentageHeight || 66;\n"
        "        this.naturalBorder = naturalNoteBorder || \"2px solid #333\";\n"
        "        this.accidentalBorder = accidentalNoteBorder || \"2px solid #333\";\n"
        "        this.pressedColour = pressedNoteColour || \"#8ad\";\n"
        "\n"
        "        this.root = this.attachShadow({ mode: \"open\" });\n"
        "\n"
        "        this.root.addEventListener (\"mousedown\",   (event) => this.handleMouse (event, true, false) );\n"
        "        this.root.addEventListener (\"mouseup\",     (event) => this.handleMouse (event, false, true) );\n"
        "        this.root.addEventListener (\"mousemove\",   (event) => this.handleMouse (event, false, false) );\n"
        "        this.root.addEventListener (\"mouseenter\",  (event) => this.handleMouse (event, false, false) );\n"
        "        this.root.addEventListener (\"mouseout\",    (event) => this.handleMouse (event, false, false) );\n"
        "\n"
        "        this.addEventListener (\"keydown\",  (event) => this.handleKey (event, true));\n"
        "        this.addEventListener (\"keyup\",    (event) => this.handleKey (event, false));\n"
        "        this.addEventListener (\"focusout\", (event) => this.allNotesOff());\n"
        "\n"
        "        this.currentDraggedNote = -1;\n"
        "        this.currentExternalNotesOn = new Set();\n"
        "        this.currentKeyboardNotes = new Set();\n"
        "        this.currentPlayedNotes = new Set();\n"
        "        this.currentDisplayedNotes = new Set();\n"
        "        this.notes = [];\n"
        "        this.modifierKeys = 0;\n"
        "        this.currentTouches = new Map();\n"
        "\n"
        "        this.refreshHTML();\n"
        "\n"
        "        for (let child of this.root.children)\n"
        "        {\n"
        "            child.addEventListener (\"touchstart\", (event) => this.touchStart (event), {passive:false} );\n"
        "            child.addEventListener (\"touchend\",   (event) => this.touchEnd (event) );\n"
        "        }\n"
        "    }\n"
        "\n"
        "    static get observedAttributes()\n"
        "    {\n"
        "        return [\"root-note\", \"note-count\", \"key-map\"];\n"
        "    }\n"
        "\n"
        "    get config()\n"
        "    {\n"
        "        return {\n"
        "            rootNote: parseInt(this.getAttribute(\"root-note\") || \"36\"),\n"
        "            numNotes: parseInt(this.getAttribute(\"note-count\") || \"61\"),\n"
        "            keymap: this.getAttribute(\"key-map\") || \"KeyA KeyW KeyS KeyE KeyD KeyF KeyT KeyG KeyY KeyH KeyU KeyJ KeyK KeyO KeyL KeyP Semicolon\",\n"
        "        };\n"
        "    }\n"
        "\n"
        "    /** This attaches suitable listeners to make this keyboard control the given MIDI\n"
        "     *  endpoint of a PatchConnection object. Use detachPatchConnection() to remove\n"
        "     *  a connection later on.\n"
        "     *\n"
        "     *  @param {PatchConnection} patchConnection\n"
        "     *  @param {string} midiInputEndpointID\n"
        "     */\n"
        "    attachToPatchConnection (patchConnection, midiInputEndpointID)\n"
        "    {\n"
        "        const velocity = 100;\n"
        "\n"
        "        const callbacks = {\n"
        "            noteDown: e => patchConnection.sendMIDIInputEvent (midiInputEndpointID, 0x900000 | (e.detail.note << 8) | velocity),\n"
        "            noteUp:   e => patchConnection.sendMIDIInputEvent (midiInputEndpointID, 0x800000 | (e.detail.note << 8) | velocity),\n"
        "            midiIn:   e => this.handleExternalMIDI (e.message),\n"
        "            midiInputEndpointID\n"
        "        };\n"
        "\n"
        "        if (! this.callbacks)\n"
        "            this.callbacks = new Map();\n"
        "\n"
        "        this.callbacks.set (patchConnection, callbacks);\n"
        "\n"
        "        this.addEventListener (\"note-down\", callbacks.noteDown);\n"
        "        this.addEventListener (\"note-up\",   callbacks.noteUp);\n"
        "        patchConnection.addEndpointListener (midiInputEndpointID, callbacks.midiIn);\n"
        "    }\n"
        "\n"
        "    /** This removes the connection to a PatchConnection object that was previously attached\n"
        "     *  with attachToPatchConnection().\n"
        "     *\n"
        "     *  @param {PatchConnection} patchConnection\n"
        "     */\n"
        "    detachPatchConnection (patchConnection)\n"
        "    {\n"
        "        const callbacks = this.callbacks.get (patchConnection);\n"
        "\n"
        "        if (callbacks)\n"
        "        {\n"
        "            this.removeEventListener (\"note-down\", callbacks.noteDown);\n"
        "            this.removeEventListener (\"note-up\",   callbacks.noteUp);\n"
        "            patchConnection.removeEndpointListener (callbacks.midiInputEndpointID, callbacks.midiIn);\n"
        "        }\n"
        "\n"
        "        this.callbacks[patchConnection] = undefined;\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    /** Can be overridden to return the color to use for a note index */\n"
        "    getNoteColour (note)    { return undefined; }\n"
        "\n"
        "    /** Can be overridden to return the text label to draw on a note index */\n"
        "    getNoteLabel (note)     { return midi.getChromaticScaleIndex (note) == 0 ? midi.getNoteNameWithOctaveNumber (note) : \"\"; }\n"
        "\n"
        "    /** Clients should call this to deliver a MIDI message, which the keyboard will use to\n"
        "     *  highlight the notes that are currently playing.\n"
        "     */\n"
        "    handleExternalMIDI (message)\n"
        "    {\n"
        "        if (midi.isNoteOn (message))\n"
        "        {\n"
        "            const note = midi.getNoteNumber (message);\n"
        "            this.currentExternalNotesOn.add (note);\n"
        "            this.refreshActiveNoteElements();\n"
        "        }\n"
        "        else if (midi.isNoteOff (message))\n"
        "        {\n"
        "            const note = midi.getNoteNumber (message);\n"
        "            this.currentExternalNotesOn.delete (note);\n"
        "            this.refreshActiveNoteElements();\n"
        "        }\n"
        "    }\n"
        "\n"
        "    /** This method will be called when the user plays a note. The default behaviour is\n"
        "     *  to dispath an event, but you could override this if you needed to.\n"
        "    */\n"
        "    sendNoteOn (note)   { this.dispatchEvent (new CustomEvent('note-down', { detail: { note: note }})); }\n"
        "\n"
        "    /** This method will be called when the user releases a note. The default behaviour is\n"
        "     *  to dispath an event, but you could override this if you needed to.\n"
        "    */\n"
        "    sendNoteOff (note)  { this.dispatchEvent (new CustomEvent('note-up',   { detail: { note: note } })); }\n"
        "\n"
        "    /** Clients can call this to force all the notes to turn off, e.g. in a \"panic\". */\n"
        "    allNotesOff()\n"
        "    {\n"
        "        this.setDraggedNote (-1);\n"
        "        this.modifierKeys = 0;\n"
        "\n"
        "        for (let note of this.currentKeyboardNotes.values())\n"
        "            this.removeKeyboardNote (note);\n"
        "\n"
        "        this.currentExternalNotesOn.clear();\n"
        "        this.refreshActiveNoteElements();\n"
        "    }\n"
        "\n"
        "    setDraggedNote (newNote)\n"
        "    {\n"
        "        if (newNote != this.currentDraggedNote)\n"
        "        {\n"
        "            if (this.currentDraggedNote >= 0)\n"
        "                this.sendNoteOff (this.currentDraggedNote);\n"
        "\n"
        "            this.currentDraggedNote = newNote;\n"
        "\n"
        "            if (this.currentDraggedNote >= 0)\n"
        "                this.sendNoteOn (this.currentDraggedNote);\n"
        "\n"
        "            this.refreshActiveNoteElements();\n"
        "        }\n"
        "    }\n"
        "\n"
        "    addKeyboardNote (note)\n"
        "    {\n"
        "        if (! this.currentKeyboardNotes.has (note))\n"
        "        {\n"
        "            this.sendNoteOn (note);\n"
        "            this.currentKeyboardNotes.add (note);\n"
        "            this.refreshActiveNoteElements();\n"
        "        }\n"
        "    }\n"
        "\n"
        "    removeKeyboardNote (note)\n"
        "    {\n"
        "        if (this.currentKeyboardNotes.has (note))\n"
        "        {\n"
        "            this.sendNoteOff (note);\n"
        "            this.currentKeyboardNotes.delete (note);\n"
        "            this.refreshActiveNoteElements();\n"
        "        }\n"
        "    }\n"
        "\n"
        "    isNoteActive (note)\n"
        "    {\n"
        "        return note == this.currentDraggedNote\n"
        "            || this.currentExternalNotesOn.has (note)\n"
        "            || this.currentKeyboardNotes.has (note);\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    /** @private */\n"
        "    touchEnd (event)\n"
        "    {\n"
        "        for (const touch of event.changedTouches)\n"
        "        {\n"
        "            const note = this.currentTouches.get (touch.identifier);\n"
        "            this.currentTouches.delete (touch.identifier);\n"
        "            this.removeKeyboardNote (note);\n"
        "        }\n"
        "\n"
        "        event.preventDefault();\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    touchStart (event)\n"
        "    {\n"
        "        for (const touch of event.changedTouches)\n"
        "        {\n"
        "            const note = touch.target.id.substring (4);\n"
        "            this.currentTouches.set (touch.identifier, note);\n"
        "            this.addKeyboardNote (note);\n"
        "        }\n"
        "\n"
        "        event.preventDefault();\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    handleMouse (event, isDown, isUp)\n"
        "    {\n"
        "        if (isDown)\n"
        "            this.isDragging = true;\n"
        "\n"
        "        if (this.isDragging)\n"
        "        {\n"
        "            let newActiveNote = -1;\n"
        "\n"
        "            if (event.buttons != 0 && event.type != \"mouseout\")\n"
        "            {\n"
        "                const note = event.target.id.substring (4);\n"
        "\n"
        "                if (note !== undefined)\n"
        "                    newActiveNote = parseInt (note);\n"
        "            }\n"
        "\n"
        "            this.setDraggedNote (newActiveNote);\n"
        "\n"
        "            if (! isDown)\n"
        "                event.preventDefault();\n"
        "        }\n"
        "\n"
        "        if (isUp)\n"
        "            this.isDragging = false;\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    handleKey (event, isDown)\n"
        "    {\n"
        "        if (event.key == \"Meta\" || event.key == \"Alt\" || event.key == \"Control\" || event.key == \"Shift\")\n"
        "        {\n"
        "            this.modifierKeys += isDown ? 1 : -1;\n"
        "            return;\n"
        "        }\n"
        "\n"
        "        if (this.modifierKeys != 0)\n"
        "            return;\n"
        "\n"
        "        const config = this.config;\n"
        "        const index = config.keymap.split (\" \").indexOf (event.code);\n"
        "\n"
        "        if (index >= 0)\n"
        "        {\n"
        "            const note = Math.floor ((config.rootNote + (config.numNotes / 4) + 11) / 12) * 12 + index;\n"
        "\n"
        "            if (isDown)\n"
        "                this.addKeyboardNote (note);\n"
        "            else\n"
        "                this.removeKeyboardNote (note);\n"
        "\n"
        "            event.preventDefault();\n"
        "        }\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    refreshHTML()\n"
        "    {\n"
        "        this.root.innerHTML = `<style>${this.getCSS()}</style>${this.getNoteElements()}`;\n"
        "\n"
        "        for (let i = 0; i < 128; ++i)\n"
        "        {\n"
        "            const elem = this.shadowRoot.getElementById (`note${i.toString()}`);\n"
        "            this.notes.push ({ note: i, element: elem });\n"
        "        }\n"
        "\n"
        "        this.style.maxWidth = window.getComputedStyle (this).scrollWidth;\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    refreshActiveNoteElements()\n"
        "    {\n"
        "        for (let note of this.notes)\n"
        "        {\n"
        "            if (note.element)\n"
        "            {\n"
        "                if (this.isNoteActive (note.note))\n"
        "                    note.element.classList.add (\"active\");\n"
        "                else\n"
        "                    note.element.classList.remove (\"active\");\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    getAccidentalOffset (note)\n"
        "    {\n"
        "        let index = midi.getChromaticScaleIndex (note);\n"
        "\n"
        "        let negativeOffset = -this.accidentalWidth / 16;\n"
        "        let positiveOffset = 3 * this.accidentalWidth / 16;\n"
        "\n"
        "        const accOffset = this.naturalWidth - (this.accidentalWidth / 2);\n"
        "        const offsets = [ 0, negativeOffset, 0, positiveOffset, 0, 0, negativeOffset, 0, 0, 0, positiveOffset, 0 ];\n"
        "\n"
        "        return accOffset + offsets[index];\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    getNoteElements()\n"
        "    {\n"
        "        const config = this.config;\n"
        "        let naturals = \"\", accidentals = \"\";\n"
        "        let x = 0;\n"
        "\n"
        "        for (let i = 0; i < config.numNotes; ++i)\n"
        "        {\n"
        "            const note = config.rootNote + i;\n"
        "            const name = this.getNoteLabel (note);\n"
        "\n"
        "            if (midi.isNatural (note))\n"
        "            {\n"
        "                naturals += `<div class=\"natural-note note\" id=\"note${note}\" style=\" left: ${x + 1}px\"><p>${name}</p></div>`;\n"
        "            }\n"
        "            else\n"
        "            {\n"
        "                let accidentalOffset = this.getAccidentalOffset (note);\n"
        "                accidentals += `<div class=\"accidental-note note\" id=\"note${note}\" style=\"left: ${x + accidentalOffset}px\"></div>`;\n"
        "            }\n"
        "\n"
        "            if (midi.isNatural (note + 1) || i == config.numNotes - 1)\n"
        "                x += this.naturalWidth;\n"
        "        }\n"
        "\n"
        "        this.style.maxWidth = (x + 1) + \"px\";\n"
        "\n"
        "        return `<div tabindex=\"0\" class=\"note-holder\" style=\"width: ${x + 1}px;\">\n"
        "                ${naturals}\n"
        "                ${accidentals}\n"
        "                </div>`;\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    getCSS()\n"
        "    {\n"
        "        let extraColours = \"\";\n"
        "        const config = this.config;\n"
        "\n"
        "        for (let i = 0; i < config.numNotes; ++i)\n"
        "        {\n"
        "            const note = config.rootNote + i;\n"
        "            const colourOverride = this.getNoteColour (note);\n"
        "\n"
        "            if (colourOverride)\n"
        "                extraColours += `#note${note}:not(.active) { background: ${colourOverride}; }`;\n"
        "        }\n"
        "\n"
        "        return `\n"
        "            * {\n"
        "                box-sizing: border-box;\n"
        "                user-select: none;\n"
        "                -webkit-user-select: none;\n"
        "                -moz-user-select: none;\n"
        "                -ms-user-select: none;\n"
        "                margin: 0;\n"
        "                padding: 0;\n"
        "            }\n"
        "\n"
        "            :host {\n"
        "                display: block;\n"
        "                overflow: auto;\n"
        "                position: relative;\n"
        "            }\n"
        "\n"
        "            .natural-note {\n"
        "                position: absolute;\n"
        "                border: ${this.naturalBorder};\n"
        "                background: #fff;\n"
        "                width: ${this.naturalWidth}px;\n"
        "                height: 100%;\n"
        "\n"
        "                display: flex;\n"
        "                align-items: end;\n"
        "                justify-content: center;\n"
        "            }\n"
        "\n"
        "            p {\n"
        "                pointer-events: none;\n"
        "                text-align: center;\n"
        "                font-size: 0.7rem;\n"
        "                color: grey;\n"
        "            }\n"
        "\n"
        "            .accidental-note {\n"
        "                position: absolute;\n"
        "                top: 0;\n"
        "                border: ${this.accidentalBorder};\n"
        "                background: #333;\n"
        "                width: ${this.accidentalWidth}px;\n"
        "                height: ${this.accidentalPercentageHeight}%;\n"
        "            }\n"
        "\n"
        "            .note-holder {\n"
        "                position: relative;\n"
        "                height: 100%;\n"
        "            }\n"
        "\n"
        "            .active {\n"
        "                background: ${this.pressedColour};\n"
        "            }\n"
        "\n"
        "            ${extraColours}\n"
        "            `\n"
        "    }\n"
        "}\n";
    static constexpr const char* cmaj_api_cmajserversession_js =
        "//\n"
        "//     ,ad888ba,                              88\n"
        "//    d8\"'    \"8b\n"
        "//   d8            88,dba,,adba,   ,aPP8A.A8  88\n"
        "//   Y8,           88    88    88  88     88  88\n"
        "//    Y8a.   .a8P  88    88    88  88,   ,88  88     (C)2024 Cmajor Software Ltd\n"
        "//     '\"Y888Y\"'   88    88    88  '\"8bbP\"Y8  88     https://cmajor.dev\n"
        "//                                           ,88\n"
        "//                                        888P\"\n"
        "//\n"
        "//  This file may be used under the terms of the ISC license:\n"
        "//\n"
        "//  Permission to use, copy, modify, and/or distribute this software for any purpose with or\n"
        "//  without fee is hereby granted, provided that the above copyright notice and this permission\n"
        "//  notice appear in all copies. THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL\n"
        "//  WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY\n"
        "//  AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR\n"
        "//  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,\n"
        "//  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN\n"
        "//  CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\n"
        "\n"
        "import { PatchConnection } from \"./cmaj-patch-connection.js\"\n"
        "import { EventListenerList } from \"./cmaj-event-listener-list.js\"\n"
        "\n"
        "\n"
        "//==============================================================================\n"
        "/*\n"
        " *  This class provides the API and manages the communication protocol between\n"
        " *  a javascript application and a Cmajor session running on some kind of server\n"
        " *  (which may be local or remote).\n"
        " *\n"
        " *  This is an abstract base class: some kind of transport layer will create a\n"
        " *  subclass of ServerSession which a client application can then use to control\n"
        " *  and interact with the server.\n"
        " */\n"
        "export class ServerSession   extends EventListenerList\n"
        "{\n"
        "    /** A server session must be given a unique sessionID.\n"
        "     * @param {string} sessionID - this must be a unique string which is safe for\n"
        "     *                             use as an identifier or filename\n"
        "    */\n"
        "    constructor (sessionID)\n"
        "    {\n"
        "        super();\n"
        "\n"
        "        this.sessionID = sessionID;\n"
        "        this.activePatchConnections = new Set();\n"
        "        this.status = { connected: false, loaded: false };\n"
        "        this.lastServerMessageTime = Date.now();\n"
        "        this.checkForServerTimer = setInterval (() => this.checkServerStillExists(), 2000);\n"
        "    }\n"
        "\n"
        "    /** Call `dispose()` when this session is no longer needed and should be released. */\n"
        "    dispose()\n"
        "    {\n"
        "        if (this.checkForServerTimer)\n"
        "        {\n"
        "            clearInterval (this.checkForServerTimer);\n"
        "            this.checkForServerTimer = undefined;\n"
        "        }\n"
        "\n"
        "        this.status = { connected: false, loaded: false };\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    // Session status methods:\n"
        "\n"
        "    /** Attaches a listener function which will be called when the session status changes.\n"
        "     *  The listener will be called with an argument object containing lots of properties\n"
        "     *  describing the state, including any errors, loaded patch manifest, etc.\n"
        "     */\n"
        "    addStatusListener (listener)                        { this.addEventListener    (\"session_status\", listener); }\n"
        "\n"
        "    /** Removes a listener that was previously added by `addStatusListener()`\n"
        "     */\n"
        "    removeStatusListener (listener)                     { this.removeEventListener (\"session_status\", listener); }\n"
        "\n"
        "    /** Asks the server to asynchronously send a status update message with the latest status.\n"
        "     */\n"
        "    requestSessionStatus()                              { this.sendMessageToServer ({ type: \"req_session_status\" }); }\n"
        "\n"
        "    /** Returns the session's last known status object. */\n"
        "    getCurrentStatus()                                  { return this.status; }\n"
        "\n"
        "    //==============================================================================\n"
        "    // Patch loading:\n"
        "\n"
        "    /** Asks the server to load the specified patch into our session.\n"
        "     */\n"
        "    loadPatch (patchFileToLoad)\n"
        "    {\n"
        "        this.currentPatchLocation = patchFileToLoad;\n"
        "        this.sendMessageToServer ({ type: \"load_patch\", file: patchFileToLoad });\n"
        "    }\n"
        "\n"
        "    /** Asynchronously returns a list of patches that it has access to.\n"
        "     *  The return value is an array of manifest objects describing each of the patches.\n"
        "     */\n"
        "    async requestAvailablePatchList()\n"
        "    {\n"
        "        return await this.sendMessageToServerWithReply ({ type: \"req_patchlist\" });\n"
        "    }\n"
        "\n"
        "    /** Creates and returns a new PatchConnection object which can be used to control the\n"
        "     *  patch that this session has loaded.\n"
        "     */\n"
        "    createPatchConnection()\n"
        "    {\n"
        "        class ServerPatchConnection  extends PatchConnection\n"
        "        {\n"
        "            constructor (session)\n"
        "            {\n"
        "                super();\n"
        "                this.session = session;\n"
        "                this.manifest = session.status?.manifest;\n"
        "                this.session.activePatchConnections.add (this);\n"
        "            }\n"
        "\n"
        "            dispose()\n"
        "            {\n"
        "                this.session.activePatchConnections.delete (this);\n"
        "                this.session = undefined;\n"
        "            }\n"
        "\n"
        "            sendMessageToServer (message)\n"
        "            {\n"
        "                this.session?.sendMessageToServer (message);\n"
        "            }\n"
        "\n"
        "            getResourceAddress (path)\n"
        "            {\n"
        "                if (! this.session?.status?.httpRootURL)\n"
        "                    return undefined;\n"
        "\n"
        "                return this.session.status.httpRootURL\n"
        "                        + (path.startsWith (\"/\") ? path.substr (1) : path);\n"
        "            }\n"
        "        }\n"
        "\n"
        "        return new ServerPatchConnection (this);\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    // Audio input source handling:\n"
        "\n"
        "    /**\n"
        "     *  Sets a custom audio input source for a particular endpoint.\n"
        "     *\n"
        "     *  When a source is changed, a callback is sent to any audio input mode listeners (see\n"
        "     *  `addAudioInputModeListener()`)\n"
        "     *\n"
        "     *  @param {Object} endpointID\n"
        "     *  @param {boolean} shouldMute - if true, the endpoint will be muted\n"
        "     *  @param {Uint8Array | Array} fileDataToPlay - if this is some kind of array containing\n"
        "     *  binary data that can be parsed as an audio file, then it will be sent across for the\n"
        "     *  server to play as a looped input sample.\n"
        "     */\n"
        "    setAudioInputSource (endpointID, shouldMute, fileDataToPlay)\n"
        "    {\n"
        "        const loopFile = \"_audio_source_\" + endpointID;\n"
        "\n"
        "        if (fileDataToPlay)\n"
        "        {\n"
        "            this.registerFile (loopFile,\n"
        "            {\n"
        "               size: fileDataToPlay.byteLength,\n"
        "               read: (start, length) => { return new Blob ([fileDataToPlay.slice (start, start + length)]); }\n"
        "            });\n"
        "\n"
        "            this.sendMessageToServer ({ type: \"set_custom_audio_input\",\n"
        "                                        endpoint: endpointID,\n"
        "                                        file: loopFile });\n"
        "        }\n"
        "        else\n"
        "        {\n"
        "            this.removeFile (loopFile);\n"
        "\n"
        "            this.sendMessageToServer ({ type: \"set_custom_audio_input\",\n"
        "                                        endpoint: endpointID,\n"
        "                                        mute: !! shouldMute });\n"
        "        }\n"
        "    }\n"
        "\n"
        "    /** Attaches a listener function to be told when the input source for a particular\n"
        "     *  endpoint is changed by a call to `setAudioInputSource()`.\n"
        "     */\n"
        "    addAudioInputModeListener (endpointID, listener)    { this.addEventListener    (\"audio_input_mode_\" + endpointID, listener); }\n"
        "\n"
        "    /** Removes a listener previously added with `addAudioInputModeListener()` */\n"
        "    removeAudioInputModeListener (endpointID, listener) { this.removeEventListener (\"audio_input_mode_\" + endpointID, listener); }\n"
        "\n"
        "    /** Asks the server to send an update with the latest status to any audio mode listeners that\n"
        "     *  are attached to the given endpoint.\n"
        "     *  @param {string} endpointID\n"
        "     */\n"
        "    requestAudioInputMode (endpointID)                  { this.sendMessageToServer ({ type: \"req_audio_input_mode\", endpoint: endpointID }); }\n"
        "\n"
        "    //==============================================================================\n"
        "    // Audio device methods:\n"
        "\n"
        "    /** Enables or disables audio playback.\n"
        "     *  When playback state changes, a status update is sent to any status listeners.\n"
        "     * @param {boolean} shouldBeActive\n"
        "     */\n"
        "    setAudioPlaybackActive (shouldBeActive)             { this.sendMessageToServer ({ type: \"set_audio_playback_active\", active: shouldBeActive }); }\n"
        "\n"
        "    /** Asks the server to apply a new set of audio device properties.\n"
        "     *  The properties object uses the same format as the object that is passed to the listeners\n"
        "     *  (see `addAudioDevicePropertiesListener()`).\n"
        "     */\n"
        "    setAudioDeviceProperties (newProperties)            { this.sendMessageToServer ({ type: \"set_audio_device_props\", properties: newProperties }); }\n"
        "\n"
        "    /** Attaches a listener function which will be called when the audio device properties are\n"
        "     *  changed.\n"
        "     *\n"
        "     *  You can remove the listener when it's no longer needed with `removeAudioDevicePropertiesListener()`.\n"
        "     *\n"
        "     *  @param listener - this callback will receive an argument object containing all the\n"
        "     *                    details about the device.\n"
        "     */\n"
        "    addAudioDevicePropertiesListener (listener)         { this.addEventListener    (\"audio_device_properties\", listener); }\n"
        "\n"
        "    /** Removes a listener that was added with `addAudioDevicePropertiesListener()` */\n"
        "    removeAudioDevicePropertiesListener (listener)      { this.removeEventListener (\"audio_device_properties\", listener); }\n"
        "\n"
        "    /** Causes an asynchronous callback to any audio device listeners that are registered. */\n"
        "    requestAudioDeviceProperties()                      { this.sendMessageToServer ({ type: \"req_audio_device_props\" }); }\n"
        "\n"
        "    //==============================================================================\n"
        "    /** Asks the server to asynchronously generate some code from the currently loaded patch.\n"
        "     *\n"
        "     *  @param {string} codeType - this must be one of the strings that are listed in the\n"
        "     *                             status's `codeGenTargets` property. For example, \"cpp\"\n"
        "     *                             would request a C++ version of the patch.\n"
        "     *  @param {Object} [extraOptions] - this optionally provides target-specific properties.\n"
        "     *  @returns an object containing the code, errors and other metadata about the patch.\n"
        "     */\n"
        "    async requestGeneratedCode (codeType, extraOptions)\n"
        "    {\n"
        "        return await this.sendMessageToServerWithReply ({ type: \"req_codegen\",\n"
        "                                                          codeType: codeType,\n"
        "                                                          options: extraOptions, });\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    // File change monitoring:\n"
        "\n"
        "    /** Attaches a listener to be told when a file change is detected in the currently-loaded\n"
        "     *  patch. The function will be called with an object that gives rough details about the\n"
        "     *  type of change, i.e. whether it's a manifest or asset file, or a cmajor file, but it\n"
        "     *  won't provide any information about exactly which files are involved.\n"
        "     */\n"
        "    addFileChangeListener (listener)                    { this.addEventListener    (\"patch_source_changed\", listener); }\n"
        "\n"
        "    /** Removes a listener that was previously added with `addFileChangeListener()`.\n"
        "     */\n"
        "    removeFileChangeListener (listener)                 { this.removeEventListener (\"patch_source_changed\", listener); }\n"
        "\n"
        "    //==============================================================================\n"
        "    // CPU level monitoring methods:\n"
        "\n"
        "    /** Attaches a listener function which will be sent messages containing CPU info.\n"
        "     *  To remove the listener, call `removeCPUListener()`. To change the rate of these\n"
        "     *  messages, use `setCPULevelUpdateRate()`.\n"
        "     */\n"
        "    addCPUListener (listener)                       { this.addEventListener    (\"cpu_info\", listener); this.updateCPULevelUpdateRate(); }\n"
        "\n"
        "    /** Removes a listener that was previously attached with `addCPUListener()`. */\n"
        "    removeCPUListener (listener)                    { this.removeEventListener (\"cpu_info\", listener); this.updateCPULevelUpdateRate(); }\n"
        "\n"
        "    /** Changes the frequency at which CPU level update messages are sent to listeners. */\n"
        "    setCPULevelUpdateRate (framesPerUpdate)         { this.cpuFramesPerUpdate = framesPerUpdate; this.updateCPULevelUpdateRate(); }\n"
        "\n"
        "    /** Attaches a listener to be told when a file change is detected in the currently-loaded\n"
        "     *  patch. The function will be called with an object that gives rough details about the\n"
        "     *  type of change, i.e. whether it's a manifest or asset file, or a cmajor file, but it\n"
        "     *  won't provide any information about exactly which files are involved.\n"
        "     */\n"
        "    addInfiniteLoopListener (listener)              { this.addEventListener    (\"infinite_loop_detected\", listener); }\n"
        "\n"
        "    /** Removes a listener that was previously added with `addFileChangeListener()`. */\n"
        "    removeInfiniteLoopListener (listener)           { this.removeEventListener (\"infinite_loop_detected\", listener); }\n"
        "\n"
        "    //==============================================================================\n"
        "    /** Registers a virtual file with the server, under the given name.\n"
        "     *\n"
        "     *  @param {string} filename - the full path name of the file\n"
        "     *  @param {Object} contentProvider - this object must have a property called `size` which is a\n"
        "     *            constant size in bytes for the file, and a method `read (offset, size)` which\n"
        "     *            returns an array (or UInt8Array) of bytes for the data in a given chunk of the file.\n"
        "     *            The server may repeatedly call this method at any time until `removeFile()` is\n"
        "     *            called to deregister the file.\n"
        "     */\n"
        "    registerFile (filename, contentProvider)\n"
        "    {\n"
        "        if (! this.files)\n"
        "            this.files = new Map();\n"
        "\n"
        "        this.files.set (filename, contentProvider);\n"
        "\n"
        "        this.sendMessageToServer ({ type: \"register_file\",\n"
        "                                    filename: filename,\n"
        "                                    size: contentProvider.size });\n"
        "    }\n"
        "\n"
        "    /** Removes a file that was previously registered with `registerFile()`. */\n"
        "    removeFile (filename)\n"
        "    {\n"
        "        this.sendMessageToServer ({ type: \"remove_file\",\n"
        "                                    filename: filename });\n"
        "        this.files?.delete (filename);\n"
        "    }\n"
        "\n"
        "    //==============================================================================\n"
        "    // Private methods from this point...\n"
        "\n"
        "    /** An implementation subclass must call this when the session first connects\n"
        "     *  @private\n"
        "     */\n"
        "    handleSessionConnection()\n"
        "    {\n"
        "        if (! this.status.connected)\n"
        "        {\n"
        "            this.requestSessionStatus();\n"
        "            this.requestAudioDeviceProperties();\n"
        "\n"
        "            if (this.currentPatchLocation)\n"
        "            {\n"
        "                this.loadPatch (this.currentPatchLocation);\n"
        "                this.currentPatchLocation = undefined;\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "\n"
        "    /** An implementation subclass must call this when a message arrives\n"
        "     *  @private\n"
        "     */\n"
        "    handleMessageFromServer (msg)\n"
        "    {\n"
        "        this.lastServerMessageTime = Date.now();\n"
        "        const type = msg.type;\n"
        "        const message = msg.message;\n"
        "\n"
        "        switch (type)\n"
        "        {\n"
        "            case \"cpu_info\":\n"
        "            case \"audio_device_properties\":\n"
        "            case \"patch_source_changed\":\n"
        "            case \"infinite_loop_detected\":\n"
        "                this.dispatchEvent (type, message);\n"
        "                break;\n"
        "\n"
        "            case \"session_status\":\n"
        "                message.connected = true;\n"
        "                this.setNewStatus (message);\n"
        "                break;\n"
        "\n"
        "            case \"req_file_read\":\n"
        "                this.handleFileReadRequest (message);\n"
        "                break;\n"
        "\n"
        "            case \"ping\":\n"
        "                this.sendMessageToServer ({ type: \"ping\" });\n"
        "                break;\n"
        "\n"
        "            default:\n"
        "                if (type.startsWith (\"audio_input_mode_\") || type.startsWith (\"reply_\"))\n"
        "                {\n"
        "                    this.dispatchEvent (type, message);\n"
        "                    break;\n"
        "                }\n"
        "\n"
        "                for (const c of this.activePatchConnections)\n"
        "                    c.deliverMessageFromServer (msg);\n"
        "\n"
        "                break;\n"
        "        }\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    checkServerStillExists()\n"
        "    {\n"
        "        if (Date.now() > this.lastServerMessageTime + 10000)\n"
        "            this.setNewStatus ({\n"
        "                connected: false,\n"
        "                loaded: false,\n"
        "                status: \"Cannot connect to the Cmajor server\"\n"
        "            });\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    setNewStatus (newStatus)\n"
        "    {\n"
        "        this.status = newStatus;\n"
        "        this.dispatchEvent (\"session_status\", this.status);\n"
        "        this.updateCPULevelUpdateRate();\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    updateCPULevelUpdateRate()\n"
        "    {\n"
        "        const rate = this.getNumListenersForType (\"cpu_info\") > 0 ? (this.cpuFramesPerUpdate || 15000) : 0;\n"
        "        this.sendMessageToServer ({ type: \"set_cpu_info_rate\",\n"
        "                                    framesPerCallback: rate });\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    handleFileReadRequest (request)\n"
        "    {\n"
        "        const contentProvider = this.files?.get (request?.file);\n"
        "\n"
        "        if (contentProvider && request.offset !== null && request.size != 0)\n"
        "        {\n"
        "            const data = contentProvider.read (request.offset, request.size);\n"
        "            const reader = new FileReader();\n"
        "\n"
        "            reader.onloadend = (e) =>\n"
        "            {\n"
        "                const base64 = e.target?.result?.split?.(\",\", 2)[1];\n"
        "\n"
        "                if (base64)\n"
        "                    this.sendMessageToServer ({ type: \"file_content\",\n"
        "                                                file: request.file,\n"
        "                                                data: base64,\n"
        "                                                start: request.offset });\n"
        "            };\n"
        "\n"
        "            reader.readAsDataURL (data);\n"
        "        }\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    sendMessageToServerWithReply (message)\n"
        "    {\n"
        "        return new Promise ((resolve, reject) =>\n"
        "        {\n"
        "            const replyType = \"reply_\" + message.type + \"_\" + this.createRandomID();\n"
        "            this.addSingleUseListener (replyType, resolve);\n"
        "            this.sendMessageToServer ({ ...message, replyType });\n"
        "        });\n"
        "    }\n"
        "\n"
        "    /** @private */\n"
        "    createRandomID()\n"
        "    {\n"
        "        return (Math.floor (Math.random() * 100000000)).toString();\n"
        "    }\n"
        "}\n";


    static constexpr std::array files =
    {
        File { "cmaj_api/cmaj-patch-connection.js", std::string_view (cmaj_api_cmajpatchconnection_js, 13131) },
        File { "VCS.cmajorpatch", std::string_view (VCS_cmajorpatch, 420) },
        File { "cmaj_api/assets/cmajor-logo.svg", std::string_view (cmaj_api_assets_cmajorlogo_svg, 2913) },
        File { "cmaj_api/cmaj-audio-worklet-helper.js", std::string_view (cmaj_api_cmajaudioworklethelper_js, 28203) },
        File { "cmaj_api/cmaj-event-listener-list.js", std::string_view (cmaj_api_cmajeventlistenerlist_js, 3474) },
        File { "cmaj_api/cmaj-generic-patch-view.js", std::string_view (cmaj_api_cmajgenericpatchview_js, 6912) },
        File { "cmaj_api/cmaj-midi-helpers.js", std::string_view (cmaj_api_cmajmidihelpers_js, 13253) },
        File { "cmaj_api/cmaj-parameter-controls.js", std::string_view (cmaj_api_cmajparametercontrols_js, 30756) },
        File { "cmaj_api/cmaj-patch-view.js", std::string_view (cmaj_api_cmajpatchview_js, 7388) },
        File { "cmaj_api/cmaj-piano-keyboard.js", std::string_view (cmaj_api_cmajpianokeyboard_js, 15557) },
        File { "cmaj_api/cmaj-server-session.js", std::string_view (cmaj_api_cmajserversession_js, 18553) }
    };

};



// native faceplate (replaces the generic Cmajor UI). See VCSNative.h.
#include "VCSNative.h"

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JWVCSPlugin (std::make_shared<cmaj::Patch>());
}

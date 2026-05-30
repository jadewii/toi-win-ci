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

// Auto-generated Cmajor code for patch 'JWMEM'

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
/// Auto-generated C++ class for the 'JWMEM' processor
///

#if ! (defined (__cplusplus) && (__cplusplus >= 201703L))
 #error "This code requires that your compiler is set to use C++17 or later!"
#endif

namespace performer
{
    struct JWMEM
    {
        JWMEM() = default;
        ~JWMEM() = default;

        static constexpr std::string_view name = "JWMEM";

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
        static constexpr uint32_t numInputEndpoints  = 40;
        static constexpr uint32_t numOutputEndpoints = 2;

        static constexpr uint32_t maxFramesPerBlock  = 512;
        static constexpr uint32_t eventBufferSize    = 32;
        static constexpr uint32_t maxOutputEventSize = 8;
        static constexpr double   latency            = 0.000000;

        enum class EndpointHandles
        {
            midiIn    = 1 ,
            o1Wave    = 2 ,
            o1Oct     = 3 ,
            o1Lvl     = 4 ,
            o2Wave    = 5 ,
            o2Oct     = 6 ,
            o2Tune    = 7 ,
            o2Lvl     = 8 ,
            sync      = 9 ,
            o3Wave    = 10,
            o3Oct     = 11,
            o3Tune    = 12,
            o3Lvl     = 13,
            pw        = 14,
            pwm       = 15,
            xmod      = 16,
            noiseLvl  = 17,
            drift     = 18,
            drive     = 19,
            unison    = 20,
            uniDetune = 21,
            glide     = 22,
            cutoff    = 23,
            reso      = 24,
            fEnv      = 25,
            fKeyTrack = 26,
            a1        = 27,
            d1        = 28,
            s1        = 29,
            r1        = 30,
            a2        = 31,
            d2        = 32,
            s2        = 33,
            r2        = 34,
            lfoRate   = 35,
            lfoShape  = 36,
            lfoPitch  = 37,
            lfoFilter = 38,
            volume    = 39,
            tune      = 40,
            audioOut  = 41,
            noteOut   = 42
        };

        static constexpr uint32_t getEndpointHandleForName (std::string_view endpointName)
        {
            if (endpointName == "midiIn")     return static_cast<uint32_t> (EndpointHandles::midiIn);
            if (endpointName == "o1Wave")     return static_cast<uint32_t> (EndpointHandles::o1Wave);
            if (endpointName == "o1Oct")      return static_cast<uint32_t> (EndpointHandles::o1Oct);
            if (endpointName == "o1Lvl")      return static_cast<uint32_t> (EndpointHandles::o1Lvl);
            if (endpointName == "o2Wave")     return static_cast<uint32_t> (EndpointHandles::o2Wave);
            if (endpointName == "o2Oct")      return static_cast<uint32_t> (EndpointHandles::o2Oct);
            if (endpointName == "o2Tune")     return static_cast<uint32_t> (EndpointHandles::o2Tune);
            if (endpointName == "o2Lvl")      return static_cast<uint32_t> (EndpointHandles::o2Lvl);
            if (endpointName == "sync")       return static_cast<uint32_t> (EndpointHandles::sync);
            if (endpointName == "o3Wave")     return static_cast<uint32_t> (EndpointHandles::o3Wave);
            if (endpointName == "o3Oct")      return static_cast<uint32_t> (EndpointHandles::o3Oct);
            if (endpointName == "o3Tune")     return static_cast<uint32_t> (EndpointHandles::o3Tune);
            if (endpointName == "o3Lvl")      return static_cast<uint32_t> (EndpointHandles::o3Lvl);
            if (endpointName == "pw")         return static_cast<uint32_t> (EndpointHandles::pw);
            if (endpointName == "pwm")        return static_cast<uint32_t> (EndpointHandles::pwm);
            if (endpointName == "xmod")       return static_cast<uint32_t> (EndpointHandles::xmod);
            if (endpointName == "noiseLvl")   return static_cast<uint32_t> (EndpointHandles::noiseLvl);
            if (endpointName == "drift")      return static_cast<uint32_t> (EndpointHandles::drift);
            if (endpointName == "drive")      return static_cast<uint32_t> (EndpointHandles::drive);
            if (endpointName == "unison")     return static_cast<uint32_t> (EndpointHandles::unison);
            if (endpointName == "uniDetune")  return static_cast<uint32_t> (EndpointHandles::uniDetune);
            if (endpointName == "glide")      return static_cast<uint32_t> (EndpointHandles::glide);
            if (endpointName == "cutoff")     return static_cast<uint32_t> (EndpointHandles::cutoff);
            if (endpointName == "reso")       return static_cast<uint32_t> (EndpointHandles::reso);
            if (endpointName == "fEnv")       return static_cast<uint32_t> (EndpointHandles::fEnv);
            if (endpointName == "fKeyTrack")  return static_cast<uint32_t> (EndpointHandles::fKeyTrack);
            if (endpointName == "a1")         return static_cast<uint32_t> (EndpointHandles::a1);
            if (endpointName == "d1")         return static_cast<uint32_t> (EndpointHandles::d1);
            if (endpointName == "s1")         return static_cast<uint32_t> (EndpointHandles::s1);
            if (endpointName == "r1")         return static_cast<uint32_t> (EndpointHandles::r1);
            if (endpointName == "a2")         return static_cast<uint32_t> (EndpointHandles::a2);
            if (endpointName == "d2")         return static_cast<uint32_t> (EndpointHandles::d2);
            if (endpointName == "s2")         return static_cast<uint32_t> (EndpointHandles::s2);
            if (endpointName == "r2")         return static_cast<uint32_t> (EndpointHandles::r2);
            if (endpointName == "lfoRate")    return static_cast<uint32_t> (EndpointHandles::lfoRate);
            if (endpointName == "lfoShape")   return static_cast<uint32_t> (EndpointHandles::lfoShape);
            if (endpointName == "lfoPitch")   return static_cast<uint32_t> (EndpointHandles::lfoPitch);
            if (endpointName == "lfoFilter")  return static_cast<uint32_t> (EndpointHandles::lfoFilter);
            if (endpointName == "volume")     return static_cast<uint32_t> (EndpointHandles::volume);
            if (endpointName == "tune")       return static_cast<uint32_t> (EndpointHandles::tune);
            if (endpointName == "audioOut")   return static_cast<uint32_t> (EndpointHandles::audioOut);
            if (endpointName == "noteOut")    return static_cast<uint32_t> (EndpointHandles::noteOut);
            return 0;
        }

        static constexpr EndpointInfo inputEndpoints[] =
        {
            { 1,   "midiIn",     EndpointType::event },
            { 2,   "o1Wave",     EndpointType::event },
            { 3,   "o1Oct",      EndpointType::event },
            { 4,   "o1Lvl",      EndpointType::event },
            { 5,   "o2Wave",     EndpointType::event },
            { 6,   "o2Oct",      EndpointType::event },
            { 7,   "o2Tune",     EndpointType::event },
            { 8,   "o2Lvl",      EndpointType::event },
            { 9,   "sync",       EndpointType::event },
            { 10,  "o3Wave",     EndpointType::event },
            { 11,  "o3Oct",      EndpointType::event },
            { 12,  "o3Tune",     EndpointType::event },
            { 13,  "o3Lvl",      EndpointType::event },
            { 14,  "pw",         EndpointType::event },
            { 15,  "pwm",        EndpointType::event },
            { 16,  "xmod",       EndpointType::event },
            { 17,  "noiseLvl",   EndpointType::event },
            { 18,  "drift",      EndpointType::event },
            { 19,  "drive",      EndpointType::event },
            { 20,  "unison",     EndpointType::event },
            { 21,  "uniDetune",  EndpointType::event },
            { 22,  "glide",      EndpointType::event },
            { 23,  "cutoff",     EndpointType::event },
            { 24,  "reso",       EndpointType::event },
            { 25,  "fEnv",       EndpointType::event },
            { 26,  "fKeyTrack",  EndpointType::event },
            { 27,  "a1",         EndpointType::event },
            { 28,  "d1",         EndpointType::event },
            { 29,  "s1",         EndpointType::event },
            { 30,  "r1",         EndpointType::event },
            { 31,  "a2",         EndpointType::event },
            { 32,  "d2",         EndpointType::event },
            { 33,  "s2",         EndpointType::event },
            { 34,  "r2",         EndpointType::event },
            { 35,  "lfoRate",    EndpointType::event },
            { 36,  "lfoShape",   EndpointType::event },
            { 37,  "lfoPitch",   EndpointType::event },
            { 38,  "lfoFilter",  EndpointType::event },
            { 39,  "volume",     EndpointType::event },
            { 40,  "tune",       EndpointType::event }
        };

        static constexpr EndpointInfo outputEndpoints[] =
        {
            { 41,  "audioOut",  EndpointType::stream },
            { 42,  "noteOut",   EndpointType::event  }
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
            inputEndpoints[39]
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
            inputEndpoints[39]
        };

        static constexpr const char* programDetailsJSON =
                "{\n"
                "  \"mainProcessor\": \"JWMEM\",\n"
                "  \"inputs\": [\n"
                "    {\n"
                "      \"endpointID\": \"midiIn\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"object\",\n"
                "        \"class\": \"Message\",\n"
                "        \"members\": {\n"
                "          \"message\": {\n"
                "            \"type\": \"int32\"\n"
                "          }\n"
                "        }\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"MIDI in\"\n"
                "      },\n"
                "      \"purpose\": \"midi in\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"o1Wave\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"VCO1 Wave\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.0\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"o1Oct\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"VCO1 Oct\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.5\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"o1Lvl\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"VCO1 Level\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.8\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"o2Wave\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"VCO2 Wave\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.0\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"o2Oct\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"VCO2 Oct\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.5\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"o2Tune\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"VCO2 Tune\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.5\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"o2Lvl\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"VCO2 Level\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.7\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"sync\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Sync\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.0\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"o3Wave\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"VCO3 Wave\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.0\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"o3Oct\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"VCO3 Oct\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.5\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"o3Tune\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"VCO3 Tune\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.5\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"o3Lvl\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"VCO3 Level\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.5\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"pw\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Pulse Width\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.5\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"pwm\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"PWM\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.0\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"xmod\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"X-Mod\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.0\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"noiseLvl\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Noise\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.0\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"drift\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Drift\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.25\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"drive\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Drive\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.3\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"unison\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Unison\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.0\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"uniDetune\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Uni Detune\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.4\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"glide\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Glide\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.0\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"cutoff\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Cutoff\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.55\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"reso\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Resonance\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.18\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"fEnv\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Filter Env\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.45\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"fKeyTrack\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Key Track\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.3\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"a1\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"F Atk\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.02\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"d1\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"F Dec\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.5\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"s1\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"F Sus\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.4\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"r1\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"F Rel\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.3\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"a2\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"A Atk\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.02\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"d2\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"A Dec\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.5\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"s2\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"A Sus\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.8\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"r2\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"A Rel\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.35\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"lfoRate\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"LFO Rate\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.3\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"lfoShape\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"LFO Shape\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.0\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"lfoPitch\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"LFO Pitch\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.0\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"lfoFilter\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"LFO Filter\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.0\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"volume\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Volume\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.8\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"tune\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"float32\"\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Master Tune\",\n"
                "        \"min\": 0.0,\n"
                "        \"max\": 1,\n"
                "        \"init\": 0.5\n"
                "      },\n"
                "      \"purpose\": \"parameter\"\n"
                "    }\n"
                "  ],\n"
                "  \"outputs\": [\n"
                "    {\n"
                "      \"endpointID\": \"audioOut\",\n"
                "      \"endpointType\": \"stream\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"vector\",\n"
                "        \"element\": {\n"
                "          \"type\": \"float32\"\n"
                "        },\n"
                "        \"size\": 2\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Audio out\"\n"
                "      },\n"
                "      \"purpose\": \"audio out\",\n"
                "      \"numAudioChannels\": 2\n"
                "    },\n"
                "    {\n"
                "      \"endpointID\": \"noteOut\",\n"
                "      \"endpointType\": \"event\",\n"
                "      \"dataType\": {\n"
                "        \"type\": \"object\",\n"
                "        \"class\": \"NoteEvent\",\n"
                "        \"members\": {\n"
                "          \"pitch\": {\n"
                "            \"type\": \"int32\"\n"
                "          },\n"
                "          \"on\": {\n"
                "            \"type\": \"int32\"\n"
                "          }\n"
                "        }\n"
                "      },\n"
                "      \"annotation\": {\n"
                "        \"name\": \"Note out\"\n"
                "      }\n"
                "    }\n"
                "  ]\n"
                "}";

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
            float o1Wave = {};
            float o1Oct = {};
            float o1Lvl = {};
            float o2Wave = {};
            float o2Oct = {};
            float o2Tune = {};
            float o2Lvl = {};
            float sync = {};
            float o3Wave = {};
            float o3Oct = {};
            float o3Tune = {};
            float o3Lvl = {};
            float pw = {};
            float pwm = {};
            float xmod = {};
            float noiseLvl = {};
            float drift = {};
            float drive = {};
            float unison = {};
            float uniDetune = {};
            float glide = {};
            float cutoff = {};
            float reso = {};
            float fEnv = {};
            float fKeyTrack = {};
            float a1 = {};
            float d1 = {};
            float s1 = {};
            float r1 = {};
            float a2 = {};
            float d2 = {};
            float s2 = {};
            float r2 = {};
            float lfoRate = {};
            float lfoShape = {};
            float lfoPitch = {};
            float lfoFilter = {};
            float volume = {};
            float tune = {};
        };

        struct _MEMVoice_1_State
        {
            plugincorp_Params params;
            bool active = {};
            float freqTarget = {};
            float glideCur = {};
            float vel = {};
            Array<float, 9> ph;
            Array<float, 3> driftCur;
            Array<float, 3> driftTgt;
            float driftClk = {};
            float lfoPh = {};
            float vDet = {};
            float xmodPrev = {};
            int32_t rngc = {};
            float ls1 = {};
            float ls2 = {};
            float ls3 = {};
            float ls4 = {};
            float lz4 = {};
            int32_t e1Stage = {};
            int32_t e2Stage = {};
            float e1 = {};
            float e2 = {};
            float dcx = {};
            float dcy = {};
            int32_t _instanceIndex = {};
            float sr = {};
            float invSr = {};
            float ny = {};
            int32_t _resumeIndex = {};
        };

        struct std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_VoiceState
        {
            bool isActive = {};
            bool isReleasing = {};
            int32_t channel = {};
            int32_t age = {};
            float pitch = {};
        };

        struct std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State
        {
            Array<std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_VoiceState, 6> voiceState;
            int32_t nextActiveTime = {};
            int32_t nextInactiveTime = {};
            bool mpeMasterSustainActive = {};
            int64_t perChannelSustainActive = {};
        };

        struct _ParamsProcessor_1_State
        {
            plugincorp_Params params;
        };

        struct std_midi_MPEConverter_1_State
        {
        };

        struct _JWMEM_State
        {
            int32_t _sessionID = {};
            double _frequency = {};
            Array<_MEMVoice_1_State, 6> voices;
            std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State voiceAllocator;
            _ParamsProcessor_1_State paramsProcessor;
            std_midi_MPEConverter_1_State mpe;
            std_midi_MPEConverter_1_State noteTap;
        };

        struct plugincorp_NoteEvent
        {
            int32_t pitch = {};
            int32_t on = {};
        };

        struct JWMEM_eventValue_noteOut
        {
            int32_t frame = {};
            int32_t type = {};
            plugincorp_NoteEvent value_0;
        };

        struct JWMEM_State
        {
            int32_t _currentFrame = {};
            _JWMEM_State _state;
            int32_t noteOut_eventCount = {};
            Array<JWMEM_eventValue_noteOut, 32> noteOut;
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

        struct JWMEM_IO
        {
            Array<Vector<float, 2>, 512> audioOut;
        };

        struct _JWMEM_IO
        {
            Vector<float, 2> audioOut;
        };

        struct _MEMVoice_1_IO
        {
            Vector<float, 2> voiceOut;
        };

        struct std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO
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
        using std_intrinsics_T_10 = float;

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
            if (endpointHandle == 41) { std::memcpy (reinterpret_cast<char*> (dest), std::addressof (cmajIO.audioOut), 8 * numFramesToCopy); std::memset (reinterpret_cast<char*> (std::addressof (cmajIO.audioOut)), 0, 8 * numFramesToCopy); return; }
            throw std::runtime_error ("Unknown stream endpointHandle:" + std::to_string (endpointHandle));
        }

        uint32_t getNumOutputEvents (EndpointHandle endpointHandle)
        {
            if (endpointHandle == 42) return (uint32_t) cmajState.noteOut_eventCount;
            throw std::runtime_error ("Unknown event endpointHandle:" + std::to_string (endpointHandle));
            return {};
        }

        void resetOutputEventCount (EndpointHandle endpointHandle)
        {
            if (endpointHandle == 42) { cmajState.noteOut_eventCount = 0; return; }
        }

        uint32_t getOutputEventType (EndpointHandle endpointHandle, uint32_t index)
        {
            if (endpointHandle == 42) return (uint32_t) cmajState.noteOut[(IndexType) index].type;
            throw std::runtime_error ("Unknown event endpointHandle:" + std::to_string (endpointHandle));
            return {};
        }

        static uint32_t getOutputEventDataSize (EndpointHandle endpointHandle, uint32_t typeIndex)
        {
            (void) endpointHandle; (void) typeIndex;

            if (endpointHandle == 42 && typeIndex == 0) return 8;
            throw std::runtime_error ("Unknown event endpointHandle:" + std::to_string (endpointHandle));
            return 0;
        }

        uint32_t readOutputEvent (EndpointHandle endpointHandle, uint32_t index, unsigned char* dest)
        {
            if (endpointHandle == 42)
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

        void addEvent_o1Wave (float event)
        {
            _sendEvent_o1Wave (cmajState, event);
        }

        void addEvent_o1Oct (float event)
        {
            _sendEvent_o1Oct (cmajState, event);
        }

        void addEvent_o1Lvl (float event)
        {
            _sendEvent_o1Lvl (cmajState, event);
        }

        void addEvent_o2Wave (float event)
        {
            _sendEvent_o2Wave (cmajState, event);
        }

        void addEvent_o2Oct (float event)
        {
            _sendEvent_o2Oct (cmajState, event);
        }

        void addEvent_o2Tune (float event)
        {
            _sendEvent_o2Tune (cmajState, event);
        }

        void addEvent_o2Lvl (float event)
        {
            _sendEvent_o2Lvl (cmajState, event);
        }

        void addEvent_sync (float event)
        {
            _sendEvent_sync (cmajState, event);
        }

        void addEvent_o3Wave (float event)
        {
            _sendEvent_o3Wave (cmajState, event);
        }

        void addEvent_o3Oct (float event)
        {
            _sendEvent_o3Oct (cmajState, event);
        }

        void addEvent_o3Tune (float event)
        {
            _sendEvent_o3Tune (cmajState, event);
        }

        void addEvent_o3Lvl (float event)
        {
            _sendEvent_o3Lvl (cmajState, event);
        }

        void addEvent_pw (float event)
        {
            _sendEvent_pw (cmajState, event);
        }

        void addEvent_pwm (float event)
        {
            _sendEvent_pwm (cmajState, event);
        }

        void addEvent_xmod (float event)
        {
            _sendEvent_xmod (cmajState, event);
        }

        void addEvent_noiseLvl (float event)
        {
            _sendEvent_noiseLvl (cmajState, event);
        }

        void addEvent_drift (float event)
        {
            _sendEvent_drift (cmajState, event);
        }

        void addEvent_drive (float event)
        {
            _sendEvent_drive (cmajState, event);
        }

        void addEvent_unison (float event)
        {
            _sendEvent_unison (cmajState, event);
        }

        void addEvent_uniDetune (float event)
        {
            _sendEvent_uniDetune (cmajState, event);
        }

        void addEvent_glide (float event)
        {
            _sendEvent_glide (cmajState, event);
        }

        void addEvent_cutoff (float event)
        {
            _sendEvent_cutoff (cmajState, event);
        }

        void addEvent_reso (float event)
        {
            _sendEvent_reso (cmajState, event);
        }

        void addEvent_fEnv (float event)
        {
            _sendEvent_fEnv (cmajState, event);
        }

        void addEvent_fKeyTrack (float event)
        {
            _sendEvent_fKeyTrack (cmajState, event);
        }

        void addEvent_a1 (float event)
        {
            _sendEvent_a1 (cmajState, event);
        }

        void addEvent_d1 (float event)
        {
            _sendEvent_d1 (cmajState, event);
        }

        void addEvent_s1 (float event)
        {
            _sendEvent_s1 (cmajState, event);
        }

        void addEvent_r1 (float event)
        {
            _sendEvent_r1 (cmajState, event);
        }

        void addEvent_a2 (float event)
        {
            _sendEvent_a2 (cmajState, event);
        }

        void addEvent_d2 (float event)
        {
            _sendEvent_d2 (cmajState, event);
        }

        void addEvent_s2 (float event)
        {
            _sendEvent_s2 (cmajState, event);
        }

        void addEvent_r2 (float event)
        {
            _sendEvent_r2 (cmajState, event);
        }

        void addEvent_lfoRate (float event)
        {
            _sendEvent_lfoRate (cmajState, event);
        }

        void addEvent_lfoShape (float event)
        {
            _sendEvent_lfoShape (cmajState, event);
        }

        void addEvent_lfoPitch (float event)
        {
            _sendEvent_lfoPitch (cmajState, event);
        }

        void addEvent_lfoFilter (float event)
        {
            _sendEvent_lfoFilter (cmajState, event);
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
                return addEvent_o1Wave (value);
            }

            if (endpointHandle == 3)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o1Oct (value);
            }

            if (endpointHandle == 4)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o1Lvl (value);
            }

            if (endpointHandle == 5)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o2Wave (value);
            }

            if (endpointHandle == 6)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o2Oct (value);
            }

            if (endpointHandle == 7)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o2Tune (value);
            }

            if (endpointHandle == 8)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o2Lvl (value);
            }

            if (endpointHandle == 9)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_sync (value);
            }

            if (endpointHandle == 10)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o3Wave (value);
            }

            if (endpointHandle == 11)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o3Oct (value);
            }

            if (endpointHandle == 12)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o3Tune (value);
            }

            if (endpointHandle == 13)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_o3Lvl (value);
            }

            if (endpointHandle == 14)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_pw (value);
            }

            if (endpointHandle == 15)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_pwm (value);
            }

            if (endpointHandle == 16)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_xmod (value);
            }

            if (endpointHandle == 17)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_noiseLvl (value);
            }

            if (endpointHandle == 18)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_drift (value);
            }

            if (endpointHandle == 19)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_drive (value);
            }

            if (endpointHandle == 20)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_unison (value);
            }

            if (endpointHandle == 21)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_uniDetune (value);
            }

            if (endpointHandle == 22)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_glide (value);
            }

            if (endpointHandle == 23)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_cutoff (value);
            }

            if (endpointHandle == 24)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_reso (value);
            }

            if (endpointHandle == 25)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_fEnv (value);
            }

            if (endpointHandle == 26)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_fKeyTrack (value);
            }

            if (endpointHandle == 27)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_a1 (value);
            }

            if (endpointHandle == 28)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_d1 (value);
            }

            if (endpointHandle == 29)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_s1 (value);
            }

            if (endpointHandle == 30)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_r1 (value);
            }

            if (endpointHandle == 31)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_a2 (value);
            }

            if (endpointHandle == 32)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_d2 (value);
            }

            if (endpointHandle == 33)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_s2 (value);
            }

            if (endpointHandle == 34)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_r2 (value);
            }

            if (endpointHandle == 35)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_lfoRate (value);
            }

            if (endpointHandle == 36)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_lfoShape (value);
            }

            if (endpointHandle == 37)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_lfoPitch (value);
            }

            if (endpointHandle == 38)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_lfoFilter (value);
            }

            if (endpointHandle == 39)
            {
                float value;
                memcpy (&value, eventData, 4);
                eventData += 4;
                return addEvent_volume (value);
            }

            if (endpointHandle == 40)
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
        JWMEM_State cmajState = {};
        JWMEM_IO cmajIO = {};

        //==============================================================================
        void _sendEvent_midiIn (JWMEM_State& _state, std_midi_Message value) noexcept
        {
            _JWMEM__midiIn (_state._state, value);
        }

        void _JWMEM__midiIn (_JWMEM_State& _state, std_midi_Message value) noexcept
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
            _JWMEM___forwardEvent (state_upcast_struct_JWMEM_State_struc_TbuSFb(_state), value);
            _JWMEM___forwardEvent_5 (state_upcast_struct_JWMEM_State_struc_TbuSFb(_state), value);
        }

        void _JWMEM___forwardEvent (_JWMEM_State& _state, std_notes_NoteOn value) noexcept
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
            _JWMEM___forwardEvent_3 (state_upcast_struct_JWMEM_State_struc_vOYz4d(_state), value);
        }

        void _JWMEM___forwardEvent_3 (_JWMEM_State& _state, plugincorp_NoteEvent value) noexcept
        {
            _JWMEM___writeEvent_noteOut (_state, value);
        }

        void _JWMEM___writeEvent_noteOut (_JWMEM_State& _state, const plugincorp_NoteEvent& value) noexcept
        {
            JWMEM___writeEvent_noteOut (state_upcast_struct_JWMEM_State_struct_ikJt3(_state), value);
        }

        void JWMEM___writeEvent_noteOut (JWMEM_State& _state, const plugincorp_NoteEvent& value) noexcept
        {
            JWMEM___writeEvent_noteOut_0 (_state, value);
        }

        void JWMEM___writeEvent_noteOut_0 (JWMEM_State& _state, const plugincorp_NoteEvent& value) noexcept
        {
            if (_state.noteOut_eventCount < int32_t {32})
            {
                _state.noteOut[_state.noteOut_eventCount].frame = _state._currentFrame;
                _state.noteOut[_state.noteOut_eventCount].type = int32_t {0};
                _state.noteOut[_state.noteOut_eventCount].value_0 = value;
            }
            ++_state.noteOut_eventCount;
        }

        void _JWMEM___forwardEvent_5 (_JWMEM_State& _state, std_notes_NoteOn value) noexcept
        {
            std__voices__VoiceAllocator__eventIn (_state.voiceAllocator, value);
        }

        void std__voices__VoiceAllocator__eventIn (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, std_notes_NoteOn noteOn) noexcept
        {
            int32_t  oldest;
            std_notes_NoteOff  _temp;
            std_notes_NoteOff  _temp_0;

            oldest = std__voices__VoiceAllocator__findOldestIndex (_state);
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

        int32_t std__voices__VoiceAllocator__findOldestIndex (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state) noexcept
        {
            int32_t  index;
            int32_t  oldest;
            int32_t  i;
            int32_t  age;

            {
                index = {};
                oldest = _state.voiceState[int32_t {0}].age;
                {
                    i = int32_t {1};
                    for (;;)
                    {
                        if (i >= int32_t {6})
                        {
                            break;
                        }
                        age = _state.voiceState[i].age;
                        if (age < oldest)
                        {
                            index = i;
                            oldest = age;
                        }
                        {
                            ++i;
                        }
                    }
                }
                return index;
            }
        }

        void std__voices__VoiceAllocator___writeEvent_voiceEventOut (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, int32_t index, const std_notes_NoteOff& value) noexcept
        {
            _JWMEM___forwardEvent_12 (state_upcast_struct_JWMEM_State_struc_0g8Qwb(_state), index, value);
        }

        void _JWMEM___forwardEvent_12 (_JWMEM_State& _state, int32_t index, std_notes_NoteOff value) noexcept
        {
            MEMVoice__eventsIn (_state.voices[index], value);
        }

        void MEMVoice__eventsIn (_MEMVoice_1_State& _state, std_notes_NoteOff e) noexcept
        {
            _state.e1Stage = int32_t {3};
            _state.e2Stage = int32_t {3};
        }

        void std__voices__VoiceAllocator__start (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_VoiceState& this_, int32_t channel, float pitch) noexcept
        {
            this_.isActive = true;
            this_.isReleasing = false;
            this_.channel = channel;
            this_.pitch = pitch;
            ++_state.nextActiveTime;
            this_.age = _state.nextActiveTime;
        }

        void std__voices__VoiceAllocator___writeEvent_voiceEventOut_0 (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, int32_t index, const std_notes_NoteOn& value) noexcept
        {
            _JWMEM___forwardEvent_11 (state_upcast_struct_JWMEM_State_struc_0g8Qwb(_state), index, value);
        }

        void _JWMEM___forwardEvent_11 (_JWMEM_State& _state, int32_t index, std_notes_NoteOn value) noexcept
        {
            MEMVoice__eventsIn_0 (_state.voices[index], value);
        }

        void MEMVoice__eventsIn_0 (_MEMVoice_1_State& _state, std_notes_NoteOn e) noexcept
        {
            _state.freqTarget = std__notes__noteToFrequency (e.pitch);
            _state.vel = e.velocity;
            if (! _state.active)
            {
                _state.glideCur = _state.freqTarget;
            }
            _state.active = true;
            _state.e1Stage = int32_t {0};
            _state.e2Stage = int32_t {0};
            _state.vDet = MEMVoice__rnd (_state);
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

        float MEMVoice__rnd (_MEMVoice_1_State& _state) noexcept
        {
            float  s;

            ++_state.rngc;
            s = intrinsics::sin ((static_cast<float> (_state.rngc) * 12.9898f) + 78.233f) * 43758.547f;
            return ((s - intrinsics::floor (s)) * 2.0f) - 1.0f;
        }

        float std__intrinsics__sin (float n) noexcept
        {
            {
                return 0.0f;
            }
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
            _JWMEM___forwardEvent_2 (state_upcast_struct_JWMEM_State_struc_TbuSFb(_state), value);
            _JWMEM___forwardEvent_6 (state_upcast_struct_JWMEM_State_struc_TbuSFb(_state), value);
        }

        void _JWMEM___forwardEvent_2 (_JWMEM_State& _state, std_notes_NoteOff value) noexcept
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

        void _JWMEM___forwardEvent_6 (_JWMEM_State& _state, std_notes_NoteOff value) noexcept
        {
            std__voices__VoiceAllocator__eventIn_0 (_state.voiceAllocator, value);
        }

        void std__voices__VoiceAllocator__eventIn_0 (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, std_notes_NoteOff noteOff) noexcept
        {
            int32_t  i;

            {
                i = {};
                for (;;)
                {
                    if (i >= int32_t {6})
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
                            std__voices__VoiceAllocator___writeEvent_voiceEventOut (_state, std__intrinsics___wrap_6 (i), noteOff);
                            std__voices__VoiceAllocator__free (_state, _state.voiceState[i]);
                        }
                    }
                    {
                        ++i;
                    }
                }
            }
        }

        bool std__voices__VoiceAllocator__isSustainActive (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, int32_t channel) noexcept
        {
            return _state.mpeMasterSustainActive ? true : ((_state.perChannelSustainActive & (int64_t {1L} << static_cast<int64_t> (channel))) != static_cast<int64_t> (int32_t {0}));
        }

        int32_t std__intrinsics___wrap_6 (int32_t n) noexcept
        {
            int32_t  x;

            x = intrinsics::modulo (n, int32_t {6});
            return (x < int32_t {0}) ? (x + int32_t {6}) : x;
        }

        void std__voices__VoiceAllocator__free (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_VoiceState& this_) noexcept
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
            _JWMEM___forwardEvent_7 (state_upcast_struct_JWMEM_State_struc_TbuSFb(_state), value);
        }

        void _JWMEM___forwardEvent_7 (_JWMEM_State& _state, std_notes_PitchBend value) noexcept
        {
            std__voices__VoiceAllocator__eventIn_1 (_state.voiceAllocator, value);
        }

        void std__voices__VoiceAllocator__eventIn_1 (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, std_notes_PitchBend bend) noexcept
        {
            int32_t  i;

            {
                i = {};
                for (;;)
                {
                    if (i >= int32_t {6})
                    {
                        break;
                    }
                    if (_state.voiceState[i].channel == bend.channel)
                    {
                        std__voices__VoiceAllocator___writeEvent_voiceEventOut_1 (_state, std__intrinsics___wrap_6 (i), bend);
                    }
                    {
                        ++i;
                    }
                }
            }
        }

        void std__voices__VoiceAllocator___writeEvent_voiceEventOut_1 (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, int32_t index, const std_notes_PitchBend& value) noexcept
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
            _JWMEM___forwardEvent_9 (state_upcast_struct_JWMEM_State_struc_TbuSFb(_state), value);
        }

        void _JWMEM___forwardEvent_9 (_JWMEM_State& _state, std_notes_Pressure value) noexcept
        {
            std__voices__VoiceAllocator__eventIn_2 (_state.voiceAllocator, value);
        }

        void std__voices__VoiceAllocator__eventIn_2 (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, std_notes_Pressure pressure) noexcept
        {
            int32_t  i;

            {
                i = {};
                for (;;)
                {
                    if (i >= int32_t {6})
                    {
                        break;
                    }
                    if (_state.voiceState[i].channel == pressure.channel)
                    {
                        std__voices__VoiceAllocator___writeEvent_voiceEventOut_2 (_state, std__intrinsics___wrap_6 (i), pressure);
                    }
                    {
                        ++i;
                    }
                }
            }
        }

        void std__voices__VoiceAllocator___writeEvent_voiceEventOut_2 (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, int32_t index, const std_notes_Pressure& value) noexcept
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
            _JWMEM___forwardEvent_8 (state_upcast_struct_JWMEM_State_struc_TbuSFb(_state), value);
        }

        void _JWMEM___forwardEvent_8 (_JWMEM_State& _state, std_notes_Slide value) noexcept
        {
            std__voices__VoiceAllocator__eventIn_3 (_state.voiceAllocator, value);
        }

        void std__voices__VoiceAllocator__eventIn_3 (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, std_notes_Slide slide) noexcept
        {
            int32_t  i;

            {
                i = {};
                for (;;)
                {
                    if (i >= int32_t {6})
                    {
                        break;
                    }
                    if (_state.voiceState[i].channel == slide.channel)
                    {
                        std__voices__VoiceAllocator___writeEvent_voiceEventOut_3 (_state, std__intrinsics___wrap_6 (i), slide);
                    }
                    {
                        ++i;
                    }
                }
            }
        }

        void std__voices__VoiceAllocator___writeEvent_voiceEventOut_3 (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, int32_t index, const std_notes_Slide& value) noexcept
        {
        }

        float std__midi__getFloatControllerValue (const std_midi_Message& this_) noexcept
        {
            return static_cast<float> (this_.message & int32_t {127}) * 0.007874016f;
        }

        void std__midi__MPEConverter___writeEvent_eventOut_4 (std_midi_MPEConverter_1_State& _state, const std_notes_Control& value) noexcept
        {
            _JWMEM___forwardEvent_10 (state_upcast_struct_JWMEM_State_struc_TbuSFb(_state), value);
        }

        void _JWMEM___forwardEvent_10 (_JWMEM_State& _state, std_notes_Control value) noexcept
        {
            std__voices__VoiceAllocator__eventIn_4 (_state.voiceAllocator, value);
        }

        void std__voices__VoiceAllocator__eventIn_4 (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, std_notes_Control control) noexcept
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
                            if (i >= int32_t {6})
                            {
                                break;
                            }
                            if (((isMPEMasterChannel ? true : (_state.voiceState[i].channel == control.channel)) ? _state.voiceState[i].isActive : false) ? _state.voiceState[i].isReleasing : false)
                            {
                                _temp.channel = _state.voiceState[i].channel;
                                _temp.pitch = _state.voiceState[i].pitch;
                                _temp.velocity = 0.0f;
                                _temp_0 = _temp;
                                std__voices__VoiceAllocator___writeEvent_voiceEventOut (_state, std__intrinsics___wrap_6 (i), _temp_0);
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
                        if (i_0 >= int32_t {6})
                        {
                            break;
                        }
                        if (_state.voiceState[i_0].channel == control.channel)
                        {
                            std__voices__VoiceAllocator___writeEvent_voiceEventOut_4 (_state, std__intrinsics___wrap_6 (i_0), control);
                        }
                        {
                            ++i_0;
                        }
                    }
                }
            }
        }

        void std__voices__VoiceAllocator__setChannelSustain (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, int32_t channel, bool active) noexcept
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

        void std__voices__VoiceAllocator___writeEvent_voiceEventOut_4 (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, int32_t index, const std_notes_Control& value) noexcept
        {
        }

        void _sendEvent_o1Wave (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__o1Wave (_state._state, value);
        }

        void _JWMEM__o1Wave (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__o1Wave (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o1Wave (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.o1Wave = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void ParamsProcessor___writeEvent_paramsOut (_ParamsProcessor_1_State& _state, const plugincorp_Params& value) noexcept
        {
            _JWMEM___forwardEvent_4 (state_upcast_struct_JWMEM_State_struc_7qVQj(_state), value);
        }

        void _JWMEM___forwardEvent_4 (_JWMEM_State& _state, plugincorp_Params value) noexcept
        {
            int32_t  i;

            {
                i = {};
                for (;;)
                {
                    if (i >= int32_t {6})
                    {
                        break;
                    }
                    MEMVoice__paramsIn (_state.voices[i], value);
                    {
                        ++i;
                    }
                }
            }
        }

        void MEMVoice__paramsIn (_MEMVoice_1_State& _state, plugincorp_Params p) noexcept
        {
            _state.params = p;
        }

        void _sendEvent_o1Oct (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__o1Oct (_state._state, value);
        }

        void _JWMEM__o1Oct (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__o1Oct (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o1Oct (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.o1Oct = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o1Lvl (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__o1Lvl (_state._state, value);
        }

        void _JWMEM__o1Lvl (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__o1Lvl (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o1Lvl (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.o1Lvl = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o2Wave (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__o2Wave (_state._state, value);
        }

        void _JWMEM__o2Wave (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__o2Wave (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o2Wave (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.o2Wave = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o2Oct (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__o2Oct (_state._state, value);
        }

        void _JWMEM__o2Oct (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__o2Oct (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o2Oct (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.o2Oct = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o2Tune (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__o2Tune (_state._state, value);
        }

        void _JWMEM__o2Tune (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__o2Tune (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o2Tune (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.o2Tune = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o2Lvl (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__o2Lvl (_state._state, value);
        }

        void _JWMEM__o2Lvl (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__o2Lvl (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o2Lvl (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.o2Lvl = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_sync (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__sync (_state._state, value);
        }

        void _JWMEM__sync (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__sync (_state.paramsProcessor, value);
        }

        void ParamsProcessor__sync (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.sync = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o3Wave (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__o3Wave (_state._state, value);
        }

        void _JWMEM__o3Wave (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__o3Wave (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o3Wave (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.o3Wave = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o3Oct (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__o3Oct (_state._state, value);
        }

        void _JWMEM__o3Oct (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__o3Oct (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o3Oct (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.o3Oct = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o3Tune (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__o3Tune (_state._state, value);
        }

        void _JWMEM__o3Tune (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__o3Tune (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o3Tune (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.o3Tune = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_o3Lvl (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__o3Lvl (_state._state, value);
        }

        void _JWMEM__o3Lvl (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__o3Lvl (_state.paramsProcessor, value);
        }

        void ParamsProcessor__o3Lvl (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.o3Lvl = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_pw (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__pw (_state._state, value);
        }

        void _JWMEM__pw (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__pw (_state.paramsProcessor, value);
        }

        void ParamsProcessor__pw (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.pw = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_pwm (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__pwm (_state._state, value);
        }

        void _JWMEM__pwm (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__pwm (_state.paramsProcessor, value);
        }

        void ParamsProcessor__pwm (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.pwm = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_xmod (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__xmod (_state._state, value);
        }

        void _JWMEM__xmod (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__xmod (_state.paramsProcessor, value);
        }

        void ParamsProcessor__xmod (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.xmod = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_noiseLvl (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__noiseLvl (_state._state, value);
        }

        void _JWMEM__noiseLvl (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__noiseLvl (_state.paramsProcessor, value);
        }

        void ParamsProcessor__noiseLvl (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.noiseLvl = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_drift (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__drift (_state._state, value);
        }

        void _JWMEM__drift (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__drift (_state.paramsProcessor, value);
        }

        void ParamsProcessor__drift (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.drift = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_drive (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__drive (_state._state, value);
        }

        void _JWMEM__drive (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__drive (_state.paramsProcessor, value);
        }

        void ParamsProcessor__drive (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.drive = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_unison (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__unison (_state._state, value);
        }

        void _JWMEM__unison (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__unison (_state.paramsProcessor, value);
        }

        void ParamsProcessor__unison (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.unison = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_uniDetune (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__uniDetune (_state._state, value);
        }

        void _JWMEM__uniDetune (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__uniDetune (_state.paramsProcessor, value);
        }

        void ParamsProcessor__uniDetune (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.uniDetune = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_glide (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__glide (_state._state, value);
        }

        void _JWMEM__glide (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__glide (_state.paramsProcessor, value);
        }

        void ParamsProcessor__glide (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.glide = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_cutoff (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__cutoff (_state._state, value);
        }

        void _JWMEM__cutoff (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__cutoff (_state.paramsProcessor, value);
        }

        void ParamsProcessor__cutoff (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.cutoff = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_reso (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__reso (_state._state, value);
        }

        void _JWMEM__reso (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__reso (_state.paramsProcessor, value);
        }

        void ParamsProcessor__reso (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.reso = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_fEnv (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__fEnv (_state._state, value);
        }

        void _JWMEM__fEnv (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__fEnv (_state.paramsProcessor, value);
        }

        void ParamsProcessor__fEnv (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.fEnv = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_fKeyTrack (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__fKeyTrack (_state._state, value);
        }

        void _JWMEM__fKeyTrack (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__fKeyTrack (_state.paramsProcessor, value);
        }

        void ParamsProcessor__fKeyTrack (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.fKeyTrack = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_a1 (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__a1 (_state._state, value);
        }

        void _JWMEM__a1 (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__a1 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__a1 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.a1 = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_d1 (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__d1 (_state._state, value);
        }

        void _JWMEM__d1 (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__d1 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__d1 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.d1 = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_s1 (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__s1 (_state._state, value);
        }

        void _JWMEM__s1 (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__s1 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__s1 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.s1 = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_r1 (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__r1 (_state._state, value);
        }

        void _JWMEM__r1 (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__r1 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__r1 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.r1 = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_a2 (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__a2 (_state._state, value);
        }

        void _JWMEM__a2 (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__a2 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__a2 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.a2 = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_d2 (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__d2 (_state._state, value);
        }

        void _JWMEM__d2 (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__d2 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__d2 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.d2 = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_s2 (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__s2 (_state._state, value);
        }

        void _JWMEM__s2 (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__s2 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__s2 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.s2 = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_r2 (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__r2 (_state._state, value);
        }

        void _JWMEM__r2 (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__r2 (_state.paramsProcessor, value);
        }

        void ParamsProcessor__r2 (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.r2 = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_lfoRate (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__lfoRate (_state._state, value);
        }

        void _JWMEM__lfoRate (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__lfoRate (_state.paramsProcessor, value);
        }

        void ParamsProcessor__lfoRate (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.lfoRate = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_lfoShape (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__lfoShape (_state._state, value);
        }

        void _JWMEM__lfoShape (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__lfoShape (_state.paramsProcessor, value);
        }

        void ParamsProcessor__lfoShape (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.lfoShape = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_lfoPitch (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__lfoPitch (_state._state, value);
        }

        void _JWMEM__lfoPitch (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__lfoPitch (_state.paramsProcessor, value);
        }

        void ParamsProcessor__lfoPitch (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.lfoPitch = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_lfoFilter (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__lfoFilter (_state._state, value);
        }

        void _JWMEM__lfoFilter (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__lfoFilter (_state.paramsProcessor, value);
        }

        void ParamsProcessor__lfoFilter (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.lfoFilter = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_volume (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__volume (_state._state, value);
        }

        void _JWMEM__volume (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__volume (_state.paramsProcessor, value);
        }

        void ParamsProcessor__volume (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.volume = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _sendEvent_tune (JWMEM_State& _state, float value) noexcept
        {
            _JWMEM__tune (_state._state, value);
        }

        void _JWMEM__tune (_JWMEM_State& _state, float value) noexcept
        {
            ParamsProcessor__tune (_state.paramsProcessor, value);
        }

        void ParamsProcessor__tune (_ParamsProcessor_1_State& _state, float v) noexcept
        {
            _state.params.tune = v;
            ParamsProcessor___writeEvent_paramsOut (_state, _state.params);
        }

        void _initialise (JWMEM_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
        {
            _JWMEM___initialise (_state._state, processorID, sessionID, frequency);
        }

        void _JWMEM___initialise (_JWMEM_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
        {
            int32_t  i;

            g__sessionID = sessionID;
            g__frequency = frequency;
            {
                i = {};
                for (;;)
                {
                    if (i >= int32_t {6})
                    {
                        break;
                    }
                    _state.voices[i]._instanceIndex = i;
                    MEMVoice___initialise (_state.voices[i], processorID, sessionID, frequency);
                    {
                        ++i;
                    }
                }
            }
            std__voices__VoiceAllocator___initialise (_state.voiceAllocator, processorID, sessionID, frequency);
            ParamsProcessor___initialise (_state.paramsProcessor, processorID, sessionID, frequency);
            _initialise_0 (_state.mpe, processorID, sessionID, frequency);
            _initialise_1 (_state.noteTap, processorID, sessionID, frequency);
        }

        void MEMVoice___initialise (_MEMVoice_1_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
        {
            g__sessionID = sessionID;
            g__frequency = frequency;
            _state.rngc = int32_t {11};
            _state.freqTarget = 220.0f;
            _state.vel = 0.0f;
            _state.active = false;
            _state.glideCur = 220.0f;
            _state.e1Stage = int32_t {-1};
            _state.e2Stage = int32_t {-1};
            _state.vDet = 0.0f;
            _state.lfoPh = 0.0f;
            _state.driftClk = 0.0f;
            _state.xmodPrev = 0.0f;
            _state.e1 = 0.0f;
            _state.e2 = 0.0f;
            _state.lz4 = 0.0f;
            _state.ls1 = 0.0f;
            _state.ls2 = 0.0f;
            _state.ls3 = 0.0f;
            _state.ls4 = 0.0f;
            _state.dcx = 0.0f;
            _state.dcy = 0.0f;
        }

        void std__voices__VoiceAllocator___initialise (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
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
            _state.params = plugincorp_Params { 0.0f, 0.5f, 0.8f, 0.0f, 0.5f, 0.5f, 0.7f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.25f, 0.3f, 0.0f, 0.4f, 0.0f, 0.55f, 0.18f, 0.45f, 0.3f, 0.02f, 0.5f, 0.4f, 0.3f, 0.02f, 0.5f, 0.8f, 0.35f, 0.3f, 0.0f, 0.0f, 0.0f, 0.8f, 0.5f };
        }

        void _initialise_0 (std_midi_MPEConverter_1_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
        {
        }

        void _initialise_1 (std_midi_MPEConverter_1_State& _state, int32_t& processorID, int32_t sessionID, double frequency) noexcept
        {
        }

        void _advance (JWMEM_State& _state, JWMEM_IO& _io, int32_t _frames) noexcept
        {
            _JWMEM_IO  ioCopy;

            for (;;)
            {
                if (_state._currentFrame == _frames)
                {
                    break;
                }
                ioCopy = _JWMEM_IO {};
                main (_state._state, ioCopy);
                _io.audioOut[_state._currentFrame] = ioCopy.audioOut;
                ++_state._currentFrame;
            }
            _state._currentFrame = int32_t {0};
        }

        void main (_JWMEM_State& _state, _JWMEM_IO& _io) noexcept
        {
            Array<_MEMVoice_1_IO, 6>  voices_io;
            std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO  voiceAllocator_io;
            std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO  paramsProcessor_io;
            std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO  mpe_io;
            std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO  noteTap_io;
            int32_t  i;
            Array<Vector<float, 2>, 6>  _temp;
            Array<Vector<float, 2>, 6>  v;
            int32_t  i_0;

            voices_io = Array<_MEMVoice_1_IO, 6> {};
            voiceAllocator_io = std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO {};
            paramsProcessor_io = std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO {};
            mpe_io = std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO {};
            noteTap_io = std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO {};
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
            {
                i = {};
                for (;;)
                {
                    if (i >= int32_t {6})
                    {
                        break;
                    }
                    MEMVoice__main (_state.voices[i], voices_io[i]);
                    {
                        ++i;
                    }
                }
            }
            {
            }
            main_3 (_state.noteTap, noteTap_io);
            {
                _temp[int32_t {0}] = voices_io[int32_t {0}].voiceOut;
                _temp[int32_t {1}] = voices_io[int32_t {1}].voiceOut;
                _temp[int32_t {2}] = voices_io[int32_t {2}].voiceOut;
                _temp[int32_t {3}] = voices_io[int32_t {3}].voiceOut;
                _temp[int32_t {4}] = voices_io[int32_t {4}].voiceOut;
                _temp[int32_t {5}] = voices_io[int32_t {5}].voiceOut;
                v = _temp;
                {
                    i_0 = {};
                    for (;;)
                    {
                        if (i_0 >= int32_t {6})
                        {
                            break;
                        }
                        _io.audioOut = (_io.audioOut + v[i_0]);
                        {
                            ++i_0;
                        }
                    }
                }
            }
        }

        void main_0 (_ParamsProcessor_1_State& _state, std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO& _io) noexcept
        {
        }

        void main_1 (std_midi_MPEConverter_1_State& _state, std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO& _io) noexcept
        {
        }

        void main_2 (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& _state, std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO& _io) noexcept
        {
        }

        void MEMVoice__main (_MEMVoice_1_State& _state, _MEMVoice_1_IO& _io) noexcept
        {
            int32_t  i;
            float  outL;
            float  outR;
            float  masterTune;
            float  coef;
            float  baseFreq;
            float  lfoHz;
            float  lsin;
            float  ltri;
            float  lsq;
            float  lfo;
            float  m;
            float  m_0;
            int32_t  i_0;
            int32_t  i_1;
            int32_t  t;
            float  driftAmt;
            float  oct1;
            float  oct2;
            float  oct3;
            float  det2;
            float  det3;
            bool  uniOn;
            float  perVoice;
            float  xmodFM;
            Array<float, 3>  vf;
            Array<float, 3>  vw;
            Array<float, 3>  vl;
            float  pwEff;
            float  spread;
            float  uniGate;
            float  mixSig;
            bool  wrapped0;
            bool  doSync;
            int32_t  v;
            int32_t  cp;
            int32_t  idx;
            float  det;
            float  inc;
            float  p;
            float  raw;
            float  g;
            float  a1r;
            float  d1r;
            float  r1r;
            float  a2r;
            float  d2r;
            float  r2r;
            float  kbd;
            float  fcOct;
            float  fcHz;
            float  g_0;
            float  G;
            float  kfb;
            float  x0;
            float  v1;
            float  y1;
            float  v2;
            float  y2;
            float  v3;
            float  y3;
            float  v4;
            float  y4;
            float  yb;
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
            _state.ny = (_state.sr * 0.49f);
            {
                i = {};
                for (;;)
                {
                    if (i >= int32_t {3})
                    {
                        break;
                    }
                    _state.driftTgt[i] = MEMVoice__rnd (_state);
                    _state.driftCur[i] = (MEMVoice__rnd (_state) * 0.3f);
                    {
                        ++i;
                    }
                }
            }
            _branch0_0:
            {
                for (;;)
                {
                    outL = 0.0f;
                    outR = 0.0f;
                    if (_state.active)
                    {
                        masterTune = intrinsics::pow (2.0f, (_state.params.tune - 0.5f) * 0.16f);
                        if (_state.params.glide < 0.01f)
                        {
                            _state.glideCur = _state.freqTarget;
                        }
                        else
                        {
                            coef = 1.0f / ((((_state.params.glide * _state.params.glide) * 0.5f) * _state.sr) + 1.0f);
                            _state.glideCur = (_state.glideCur + ((_state.freqTarget - _state.glideCur) * coef));
                        }
                        baseFreq = _state.glideCur * masterTune;
                        lfoHz = 0.05f + ((_state.params.lfoRate * _state.params.lfoRate) * 14.0f);
                        _state.lfoPh = (_state.lfoPh + (lfoHz * _state.invSr));
                        if (_state.lfoPh >= 1.0f)
                        {
                            _state.lfoPh = (_state.lfoPh - 1.0f);
                        }
                        lsin = intrinsics::sin (_state.lfoPh * 6.2831855f);
                        ltri = (_state.lfoPh < 0.5f) ? ((4.0f * _state.lfoPh) - 1.0f) : (3.0f - (4.0f * _state.lfoPh));
                        lsq = (_state.lfoPh < 0.5f) ? 1.0f : -1.0f;
                        lfo = lsin;
                        if (_state.params.lfoShape < 0.5f)
                        {
                            m = _state.params.lfoShape * 2.0f;
                            lfo = ((lsin * (1.0f - m)) + (ltri * m));
                        }
                        else
                        {
                            m_0 = (_state.params.lfoShape - 0.5f) * 2.0f;
                            lfo = ((ltri * (1.0f - m_0)) + (lsq * m_0));
                        }
                        _state.driftClk = (_state.driftClk + (3.0f * _state.invSr));
                        if (_state.driftClk >= 1.0f)
                        {
                            _state.driftClk = (_state.driftClk - 1.0f);
                            {
                                i_0 = {};
                                for (;;)
                                {
                                    if (i_0 >= int32_t {3})
                                    {
                                        break;
                                    }
                                    _state.driftTgt[i_0] = MEMVoice__rnd (_state);
                                    {
                                        ++i_0;
                                    }
                                }
                            }
                        }
                        {
                            i_1 = {};
                            for (;;)
                            {
                                if (i_1 >= int32_t {3})
                                {
                                    break;
                                }
                                {
                                    t = i_1;
                                    _state.driftCur[t] = (_state.driftCur[t] + ((_state.driftTgt[i_1] - _state.driftCur[i_1]) * (6.0f * _state.invSr)));
                                }
                                {
                                    ++i_1;
                                }
                            }
                        }
                        driftAmt = _state.params.drift * 0.06f;
                        oct1 = static_cast<float> (static_cast<int32_t> (intrinsics::floor ((_state.params.o1Oct * 4.0f) + 0.5f)) - int32_t {2});
                        oct2 = static_cast<float> (static_cast<int32_t> (intrinsics::floor ((_state.params.o2Oct * 4.0f) + 0.5f)) - int32_t {2});
                        oct3 = static_cast<float> (static_cast<int32_t> (intrinsics::floor ((_state.params.o3Oct * 4.0f) + 0.5f)) - int32_t {2});
                        det2 = (_state.params.o2Tune - 0.5f) * 2.0f;
                        det3 = (_state.params.o3Tune - 0.5f) * 2.0f;
                        uniOn = _state.params.unison >= 0.5f;
                        perVoice = _state.vDet * (uniOn ? (_state.params.uniDetune * 0.02f) : 0.0015f);
                        xmodFM = (_state.xmodPrev * _state.params.xmod) * 2.0f;
                        vf = Array<float, 3> {};
                        vf[int32_t {0}] = intrinsics::clamp (baseFreq * intrinsics::pow (2.0f, (((oct1 + (_state.driftCur[int32_t {0}] * driftAmt)) + perVoice) + xmodFM) + ((lfo * _state.params.lfoPitch) * 0.5f)), 0.0f, _state.ny);
                        vf[int32_t {1}] = intrinsics::clamp (baseFreq * intrinsics::pow (2.0f, (((oct2 + (det2 / 12.0f)) + (_state.driftCur[int32_t {1}] * driftAmt)) + perVoice) + ((lfo * _state.params.lfoPitch) * 0.5f)), 0.0f, _state.ny);
                        vf[int32_t {2}] = intrinsics::clamp (baseFreq * intrinsics::pow (2.0f, (((oct3 + (det3 / 12.0f)) + (_state.driftCur[int32_t {2}] * driftAmt)) + perVoice) + ((lfo * _state.params.lfoPitch) * 0.5f)), 0.0f, _state.ny);
                        vw = Array<float, 3> {};
                        vw[int32_t {0}] = _state.params.o1Wave;
                        vw[int32_t {1}] = _state.params.o2Wave;
                        vw[int32_t {2}] = _state.params.o3Wave;
                        vl = Array<float, 3> {};
                        vl[int32_t {0}] = _state.params.o1Lvl;
                        vl[int32_t {1}] = _state.params.o2Lvl;
                        vl[int32_t {2}] = _state.params.o3Lvl;
                        pwEff = intrinsics::clamp (_state.params.pw + ((lfo * _state.params.pwm) * 0.45f), 0.05f, 0.95f);
                        spread = uniOn ? (_state.params.uniDetune * 0.05f) : 0.0f;
                        uniGate = uniOn ? 0.7f : 0.0f;
                        mixSig = 0.0f;
                        wrapped0 = false;
                        doSync = _state.params.sync >= 0.5f;
                        {
                            v = {};
                            for (;;)
                            {
                                if (v >= int32_t {3})
                                {
                                    break;
                                }
                                {
                                    cp = {};
                                    for (;;)
                                    {
                                        if (cp >= int32_t {3})
                                        {
                                            break;
                                        }
                                        idx = std__intrinsics___wrap_9 ((v * int32_t {3}) + cp);
                                        if (((v == int32_t {1}) && doSync) && wrapped0)
                                        {
                                            _state.ph[idx] = 0.0f;
                                        }
                                        det = (cp == int32_t {0}) ? 1.0f : ((cp == int32_t {1}) ? (1.0f + spread) : (1.0f - spread));
                                        inc = intrinsics::clamp (vf[v] * det, 0.0f, _state.ny) * _state.invSr;
                                        p = _state.ph[idx];
                                        p = (p + inc);
                                        if (p >= 1.0f)
                                        {
                                            p = (p - 1.0f);
                                            if ((v == int32_t {0}) ? (cp == int32_t {0}) : false)
                                            {
                                                wrapped0 = true;
                                            }
                                        }
                                        _state.ph[idx] = p;
                                        raw = MEMVoice__vcoWave (p, inc, vw[v], pwEff);
                                        g = (cp == int32_t {0}) ? 1.0f : uniGate;
                                        mixSig = (mixSig + ((raw * vl[v]) * g));
                                        if ((v == int32_t {2}) ? (cp == int32_t {0}) : false)
                                        {
                                            _state.xmodPrev = raw;
                                        }
                                        {
                                            ++cp;
                                        }
                                    }
                                }
                                {
                                    ++v;
                                }
                            }
                        }
                        mixSig = (mixSig + ((MEMVoice__rnd (_state) * _state.params.noiseLvl) * 0.6f));
                        mixSig = (intrinsics::tanh (mixSig * (1.0f + (_state.params.drive * 3.0f))) * 0.7f);
                        a1r = 1.0f / (intrinsics::max (0.0008f, 0.003f + ((_state.params.a1 * _state.params.a1) * 7.0f)) * _state.sr);
                        d1r = 1.0f / (intrinsics::max (0.0008f, 0.008f + ((_state.params.d1 * _state.params.d1) * 10.0f)) * _state.sr);
                        r1r = 1.0f / (intrinsics::max (0.0008f, 0.008f + ((_state.params.r1 * _state.params.r1) * 10.0f)) * _state.sr);
                        if (_state.e1Stage == int32_t {0})
                        {
                            _state.e1 = (_state.e1 + a1r);
                            if (_state.e1 >= 1.0f)
                            {
                                _state.e1 = 1.0f;
                                _state.e1Stage = int32_t {1};
                            }
                        }
                        else
                        {
                            if (_state.e1Stage == int32_t {1})
                            {
                                _state.e1 = (_state.e1 - d1r);
                                if (_state.e1 <= _state.params.s1)
                                {
                                    _state.e1 = _state.params.s1;
                                    _state.e1Stage = int32_t {2};
                                }
                            }
                            else
                            {
                                if (_state.e1Stage == int32_t {2})
                                {
                                    _state.e1 = _state.params.s1;
                                }
                                else
                                {
                                    if (_state.e1Stage == int32_t {3})
                                    {
                                        _state.e1 = (_state.e1 - r1r);
                                        if (_state.e1 <= 0.0f)
                                        {
                                            _state.e1 = 0.0f;
                                            _state.e1Stage = int32_t {-1};
                                        }
                                    }
                                }
                            }
                        }
                        a2r = 1.0f / (intrinsics::max (0.0008f, 0.003f + ((_state.params.a2 * _state.params.a2) * 7.0f)) * _state.sr);
                        d2r = 1.0f / (intrinsics::max (0.0008f, 0.008f + ((_state.params.d2 * _state.params.d2) * 10.0f)) * _state.sr);
                        r2r = 1.0f / (intrinsics::max (0.0008f, 0.008f + ((_state.params.r2 * _state.params.r2) * 10.0f)) * _state.sr);
                        if (_state.e2Stage == int32_t {0})
                        {
                            _state.e2 = (_state.e2 + a2r);
                            if (_state.e2 >= 1.0f)
                            {
                                _state.e2 = 1.0f;
                                _state.e2Stage = int32_t {1};
                            }
                        }
                        else
                        {
                            if (_state.e2Stage == int32_t {1})
                            {
                                _state.e2 = (_state.e2 - d2r);
                                if (_state.e2 <= _state.params.s2)
                                {
                                    _state.e2 = _state.params.s2;
                                    _state.e2Stage = int32_t {2};
                                }
                            }
                            else
                            {
                                if (_state.e2Stage == int32_t {2})
                                {
                                    _state.e2 = _state.params.s2;
                                }
                                else
                                {
                                    if (_state.e2Stage == int32_t {3})
                                    {
                                        _state.e2 = (_state.e2 - r2r);
                                        if (_state.e2 <= 0.0f)
                                        {
                                            _state.e2 = 0.0f;
                                            _state.e2Stage = int32_t {-1};
                                            _state.active = false;
                                        }
                                    }
                                }
                            }
                        }
                        kbd = MEMVoice__log2f (baseFreq / 261.63f) * _state.params.fKeyTrack;
                        fcOct = (((_state.params.cutoff * 10.0f) + ((_state.e1 * _state.params.fEnv) * 5.0f)) + kbd) + ((lfo * _state.params.lfoFilter) * 4.0f);
                        fcHz = intrinsics::clamp (20.0f * intrinsics::pow (2.0f, fcOct), 20.0f, _state.sr * 0.45f);
                        g_0 = intrinsics::tan ((3.1415927f * fcHz) * _state.invSr);
                        G = g_0 / (1.0f + g_0);
                        kfb = _state.params.reso * 4.2f;
                        x0 = mixSig - (kfb * intrinsics::tanh (_state.lz4 * 0.8f));
                        v1 = (x0 - _state.ls1) * G;
                        y1 = v1 + _state.ls1;
                        _state.ls1 = (y1 + v1);
                        v2 = (y1 - _state.ls2) * G;
                        y2 = v2 + _state.ls2;
                        _state.ls2 = (y2 + v2);
                        v3 = (y2 - _state.ls3) * G;
                        y3 = v3 + _state.ls3;
                        _state.ls3 = (y3 + v3);
                        v4 = (y3 - _state.ls4) * G;
                        y4 = v4 + _state.ls4;
                        _state.ls4 = (y4 + v4);
                        _state.lz4 = y4;
                        yb = (y4 - _state.dcx) + (0.9985f * _state.dcy);
                        _state.dcx = y4;
                        _state.dcy = yb;
                        amp = ((yb * _state.e2) * (0.4f + (0.6f * _state.vel))) * (0.4f + (_state.params.volume * 1.1f));
                        o = intrinsics::tanh (amp * 1.3f);
                        outL = o;
                        outR = o;
                        if (((outL != outL) ? true : (outL > 2.0f)) ? true : (outL < -2.0f))
                        {
                            outL = 0.0f;
                            outR = 0.0f;
                            _state.ls1 = 0.0f;
                            _state.ls2 = 0.0f;
                            _state.ls3 = 0.0f;
                            _state.ls4 = 0.0f;
                            _state.lz4 = 0.0f;
                            _state.dcx = 0.0f;
                            _state.dcy = 0.0f;
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

        float std__intrinsics__clamp (float value, float minimum, float maximum) noexcept
        {
            return (value > maximum) ? maximum : ((value < minimum) ? minimum : value);
        }

        int32_t std__intrinsics___wrap_9 (int32_t n) noexcept
        {
            int32_t  x;

            x = intrinsics::modulo (n, int32_t {9});
            return (x < int32_t {0}) ? (x + int32_t {9}) : x;
        }

        float MEMVoice__vcoWave (float p, float inc, float wave, float pwv) noexcept
        {
            float  saw;
            float  tri;
            float  p2;
            float  saw2;
            float  pulse;
            float  t;
            float  t_0;

            saw = ((2.0f * p) - 1.0f) - toi__dsp__polyBlep (p, inc);
            tri = (2.0f * intrinsics::abs ((2.0f * p) - 1.0f)) - 1.0f;
            p2 = p + intrinsics::clamp (pwv, 0.05f, 0.95f);
            if (p2 >= 1.0f)
            {
                p2 = (p2 - 1.0f);
            }
            saw2 = ((2.0f * p2) - 1.0f) - toi__dsp__polyBlep (p2, inc);
            pulse = saw - saw2;
            if (wave < 0.5f)
            {
                t = wave * 2.0f;
                return (saw * (1.0f - t)) + (tri * t);
            }
            else
            {
                t_0 = (wave - 0.5f) * 2.0f;
                return (tri * (1.0f - t_0)) + (pulse * t_0);
            }
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

        float std__intrinsics__abs (float n) noexcept
        {
            {
                return (n < static_cast<float> (int32_t {0})) ? (- n) : n;
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

        float std__intrinsics__max (float v1, float v2) noexcept
        {
            {
                return (v1 > v2) ? v1 : v2;
            }
        }

        float MEMVoice__log2f (float x) noexcept
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

        void main_3 (std_midi_MPEConverter_1_State& _state, std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_IO& _io) noexcept
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
        static _JWMEM_State& state_upcast_struct_JWMEM_State_struc_0g8Qwb (std_voices_std_voices_VoiceAllocator_specialised_lf0wne_1_State& child) { return *reinterpret_cast<_JWMEM_State*> (reinterpret_cast<char*> (std::addressof (child)) - (OFFSETOF (_JWMEM_State, voiceAllocator))); }
        static _JWMEM_State& state_upcast_struct_JWMEM_State_struc_vOYz4d (std_midi_MPEConverter_1_State& child) { return *reinterpret_cast<_JWMEM_State*> (reinterpret_cast<char*> (std::addressof (child)) - (OFFSETOF (_JWMEM_State, noteTap))); }
        static _JWMEM_State& state_upcast_struct_JWMEM_State_struc_7qVQj (_ParamsProcessor_1_State& child) { return *reinterpret_cast<_JWMEM_State*> (reinterpret_cast<char*> (std::addressof (child)) - (OFFSETOF (_JWMEM_State, paramsProcessor))); }
        static JWMEM_State& state_upcast_struct_JWMEM_State_struct_ikJt3 (_JWMEM_State& child) { return *reinterpret_cast<JWMEM_State*> (reinterpret_cast<char*> (std::addressof (child)) - (OFFSETOF (JWMEM_State, _state))); }
        static _JWMEM_State& state_upcast_struct_JWMEM_State_struc_TbuSFb (std_midi_MPEConverter_1_State& child) { return *reinterpret_cast<_JWMEM_State*> (reinterpret_cast<char*> (std::addressof (child)) - (OFFSETOF (_JWMEM_State, mpe))); }

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



struct JWMEM
{
    using PerformerClass = performer::JWMEM;
    static constexpr auto filename = "MEM.cmajorpatch";

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
    static constexpr const char* MEM_cmajorpatch =
        "{\n"
        "  \"CmajorVersion\": 1,\n"
        "  \"ID\": \"com.plugincorp.jwmem\",\n"
        "  \"version\": \"0.1\",\n"
        "  \"name\": \"JW-MEM\",\n"
        "  \"description\": \"TOI JW-MEM - monster-fat 6-voice analog poly by plugin corp\",\n"
        "  \"category\": \"instrument\",\n"
        "  \"manufacturer\": \"TOI\",\n"
        "  \"isInstrument\": true,\n"
        "  \"manufacturerCode\": \"Plgc\",\n"
        "  \"pluginCode\": \"Jmem\",\n"
        "  \"source\": [\n"
        "    \"../_dsp/toi_dsp.cmajor\",\n"
        "    \"MEM.cmajor\"\n"
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
        File { "MEM.cmajorpatch", std::string_view (MEM_cmajorpatch, 373) },
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



// native faceplate (replaces the generic Cmajor UI). See MEMNative.h.
#include "MEMNative.h"

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JWMEMPlugin (std::make_shared<cmaj::Patch>());
}

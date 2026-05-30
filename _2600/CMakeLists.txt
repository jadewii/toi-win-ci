
cmake_minimum_required(VERSION 3.16)

project(
    JW2600
    VERSION 0.1
    LANGUAGES CXX C
)

OPTION (WEBKIT2_GTK_VERSION "Which version of webkit to use")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
set(JUCE_ENABLE_MODULE_SOURCE_GROUPS ON)



if (JUCE_PATH)
    add_subdirectory(${JUCE_PATH} juce)
else()
    message (FATAL_ERROR "You must define the JUCE_PATH variable to point to your local JUCE folder")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")
endif()

if (MSVC)
    add_compile_options (/Zc:__cplusplus)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    if (NOT WEBKIT2_GTK_VERSION)
        find_package (PkgConfig REQUIRED)

        pkg_check_modules (package_to_be_found webkit2gtk-4.1 QUIET)

        if(package_to_be_found_FOUND)
            set (WEBKIT2_GTK_VERSION "webkit2gtk-4.1")
        else()
            set (WEBKIT2_GTK_VERSION "webkit2gtk-4.0")
        endif()
    endif()

    message ("Using webkit ${WEBKIT2_GTK_VERSION}")
endif()

juce_add_plugin(JW2600
    FORMATS Standalone AU VST3
    DESCRIPTION "TOI JW-2600 - semi-modular mono synthesizer by plugin corp"
    PRODUCT_NAME "JW-2600"
    BUNDLE_ID "com.plugincorp.jw2600"
    PLUGIN_CODE "J260"
    PLUGIN_MANUFACTURER_CODE "Plgc"
    COMPANY_NAME "TOI"
    COMPANY_WEBSITE ""
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    MICROPHONE_PERMISSION_ENABLED FALSE
    IS_SYNTH TRUE
    
)

juce_generate_juce_header(JW2600)

add_compile_definitions (
    $<$<CONFIG:Debug>:DEBUG=1>
    $<$<CONFIG:Debug>:CMAJ_ENABLE_ALLOCATION_CHECKER=1>
    CMAJ_ENABLE_WEBVIEW_DEV_TOOLS=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_USE_CURL=0
    CMAJOR_DLL=1
)

file(GLOB_RECURSE HEADERS
    ../_shared/include/*.h
)

target_sources(JW2600 PRIVATE
    cmajor_plugin.cpp
    ${HEADERS}
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${HEADERS})

target_compile_features(JW2600 PRIVATE cxx_std_17)

target_include_directories(JW2600 PRIVATE ../_shared/include ../_shared/include/choc)

target_link_libraries(JW2600
    PRIVATE
        juce::juce_audio_utils
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules (GTK3 REQUIRED gtk+-3.0 IMPORTED_TARGET)
    pkg_check_modules (WEBKIT2 REQUIRED ${WEBKIT2_GTK_VERSION} IMPORTED_TARGET)
    target_link_libraries (JW2600 PUBLIC ${GTK3_LIBRARIES} ${WEBKIT2_LIBRARIES})
    target_include_directories(JW2600 PRIVATE ${GTK3_INCLUDE_DIRS} ${WEBKIT2_INCLUDE_DIRS})
endif()

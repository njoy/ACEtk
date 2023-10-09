cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( Catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2
    GIT_TAG         3f0283de7a9c43200033da996ff9093be3ac84dc # tag: v3.3.2
    )

FetchContent_Declare( disco
    GIT_REPOSITORY  https://github.com/njoy/disco
    GIT_TAG         2606933a854bb0269c4ec37143e1236797e27838
    )

FetchContent_Declare( Log
    GIT_REPOSITORY  https://github.com/njoy/Log
    GIT_TAG         52962b7796afe37ef1d8f7edb4bf9ecb1b868d15
    )

FetchContent_Declare( pybind11
    GIT_REPOSITORY  https://github.com/pybind/pybind11
    GIT_TAG         5b0a6fc2017fcc176545afe3e09c9f9885283242 # tag: v2.10.4
    )

FetchContent_Declare( range-v3
    GIT_REPOSITORY  https://github.com/ericniebler/range-v3
    GIT_TAG         4989f3e9ff2efee1852942bb9328ef121369ba02 # tag: 0.11.0
    )

FetchContent_Declare( spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog
    GIT_TAG         a51b4856377a71f81b6d74b9af459305c4c644f8
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    disco
    Log
    pybind11
    range-v3
    spdlog
    )

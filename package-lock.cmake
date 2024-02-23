# CPM Package Lock
# This file should be committed to version control

# SFML
CPMDeclarePackage(SFML
  VERSION 3.0.0
  GIT_TAG 23c26f9b70e3ba5ab605f0235be6e6db8eade708
  GITHUB_REPOSITORY SFML/SFML
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
  OPTIONS
    "SFML_BUILD_WINDOW ON"
    "SFML_BUILD_GRAPHICS ON"
    "SFML_BUILD_AUDIO OFF"
    "SFML_BUILD_NETWORK OFF"
)
# flecs
CPMDeclarePackage(flecs
  NAME flecs
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
#  URL
#    "https://github.com/SanderMertens/flecs/archive/refs/tags/v3.2.11.tar.gz"
#    "URL_HASH"
#    "SHA3_256=6ae1ead882dc7a3684937ff43cc3d0aa9760d6b9e66a6372a657e13809c0f284"
  GITHUB_REPOSITORY SanderMertens/flecs
  GIT_TAG fd1e7dc71d0abfc205297a270458e36a3c6d578f
  OPTIONS
    "FLECS_STATIC ON"
    "FLECS_SHARED OFF"
    "FLECS_PIC OFF"
    "FLECS_TESTS OFF"
)
# cpp-fast-pimpl
CPMDeclarePackage(cpp-fast-pimpl
  VERSION 2.0.1
  GITHUB_REPOSITORY alexv-ds/cpp-fast-pimpl
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
  OPTIONS
    "FPIMPL_INSTALL OFF"
)
# spdlog
CPMDeclarePackage(spdlog
  NAME spdlog
  VERSION 1.13.0
  URL
    "https://github.com/gabime/spdlog/archive/refs/tags/v1.13.0.tar.gz"
    "URL_HASH"
    "SHA3_256=5207d1b63e3c1466d30b3e28a0d7accfccad6eca283df8c04999dde9fdf3de68"
  OPTIONS
    "SPDLOG_ENABLE_PCH ON"
    "SPDLOG_USE_STD_FORMAT ON"
)


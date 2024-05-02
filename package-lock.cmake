# CPM Package Lock
# This file should be committed to version control

# SFML
CPMDeclarePackage(SFML
  VERSION 3.0.0
  NAME SFML
  URL "https://github.com/SFML/SFML/archive/59447dd8e50c9e354bc8730862b99bdfab2eaeb1.tar.gz"
  URL_HASH "SHA3_256=2a7b98fe7604ebb7a02aab5bbf1b4238954b2d0da3cf5424ccb2c308ca2fa2c9"
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
  URL "https://github.com/alexv-ds/flecs/archive/ea6dc1ae19124e8acc8c49686155ce8f7200e79c.tar.gz"
  URL_HASH "SHA3_256=70da5684dc83e6c3da20c37f9fa2734dd427ce0a952c502c84d922514eb25669"
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


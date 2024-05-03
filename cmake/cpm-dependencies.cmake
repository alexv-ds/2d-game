include(cmake/get_cpm.cmake)

CPMAddPackage(
  NAME EABase
  URL "https://github.com/electronicarts/EABase/archive/521cb053d9320636f53226ffc616216cf532f0ef.tar.gz"
  URL_HASH "SHA3_256=e508facd55e1d94c640a20cd2fa5b59e2e6226de2e6ee4a754a3877637a49801"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
)

CPMAddPackage(
  NAME EASTL
  URL "https://github.com/electronicarts/EASTL/archive/05f4b4aef33f2f3ded08f19fa97f5a27ff35ff9f.tar.gz"
  URL_HASH "SHA3_256=214a22bbc62fe6102a5f5ef119d151eb9caaeb3b1fe9a0b30197e13fbbc04387"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
)

CPMAddPackage(
  NAME glm
  URL "https://github.com/g-truc/glm/archive/refs/tags/1.0.1.tar.gz"
  URL_HASH "SHA3_256=9384d631dd1fdbf0e48b57c5f1f6868fe3a6da30c3c910a9bfce338a8af683dc"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
)

CPMAddPackage(
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

CPMAddPackage(
  NAME flecs
  URL "https://github.com/alexv-ds/flecs/archive/964bd3fbe62fcbe4ae1a7e520f3e5c811d5a1a4a.tar.gz"
  URL_HASH "SHA3_256=cefa0c9264cd80ea8fa58ca53d452212faa366c42b171e81b1deac268b66f172"
  SYSTEM YES
  EXCLUDE_FROM_ALL YES
  OPTIONS
  "FLECS_STATIC ON"
  "FLECS_SHARED OFF"
  "FLECS_PIC OFF"
  "FLECS_TESTS OFF"
)

CPMAddPackage(
  NAME spdlog
  URL "https://github.com/gabime/spdlog/archive/refs/tags/v1.13.0.tar.gz"
  URL_HASH "SHA3_256=5207d1b63e3c1466d30b3e28a0d7accfccad6eca283df8c04999dde9fdf3de68"
  OPTIONS
  "SPDLOG_ENABLE_PCH ON"
  "SPDLOG_USE_STD_FORMAT ON"
)

if (BUILD_TESTING)
  CPMAddPackage(
    NAME Catch2
    URL "https://github.com/catchorg/Catch2/archive/refs/tags/v3.5.4.tar.gz"
    URL_HASH "SHA3_256=6908501ace10bca5ece01a972e4834777f3b3cb5e14b391cec015caeb5470eff"
    OPTIONS
    "CATCH_INSTALL_DOCS OFF"
    "CATCH_INSTALL_EXTRAS OFF"
    "CATCH_ENABLE_REPRODUCIBLE_BUILD OFF"
  )
  list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")
endif ()
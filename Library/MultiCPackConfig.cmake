include("release/CPackConfig.cmake")
# All configuration files contain debug instructions
set(CPACK_INSTALL_CMAKE_PROJECTS
    "debug;Library;ALL;/"
    "release;Library;ALL;/"
    )

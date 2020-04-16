if( ${CMAKE_SYSTEM_NAME} MATCHES "SunOS" )
    set( CPACK_GENERATOR "TGZ" )
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    set( CPACK_GENERATOR "TGZ" )
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
    execute_process(COMMAND "/usr/bin/lsb_release" "-is"
            TIMEOUT 4
            OUTPUT_VARIABLE LINUX_DISTRO
            ERROR_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE)
    if (${LINUX_DISTRO} MATCHES "RedHatEnterpriseServer")
        message( STATUS "Detected a Linux Red Hat machine")
        set( CPACK_GENERATOR "DEB;TGZ;RPM")
    elseif (${LINUX_DISTRO} MATCHES "Debian")
        message( STATUS "Detected a Linux Debian machine")
        set( CPACK_GENERATOR "DEB;TGZ" )
    else (${LINUX_DISTRO} MATCHES "RedHatEnterpriseServer")
        message( STATUS "Detected a Linux machine")
        set( CPACK_GENERATOR "DEB;TGZ" )
    endif()
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    set( CPACK_GENERATOR "NSIS;ZIP" )
    set( CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.md")
endif()

# Packaging common
set( CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "Libraries and applications for the GNSS processing GPSTk toolkit.")
set( CPACK_PACKAGE_VENDOR "ARL:UT SGL" )
set( CPACK_PACKAGE_CONTACT "Bryan Parsons <bparsons@arlut.utexas.edu>" )
set( CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md" )
set( CPACK_PACKAGE_VERSION ${GPSTK_VERSION})
set( CPACK_PACKAGE_VERSION_MAJOR "${GPSTK_VERSION_MAJOR}" )
set( CPACK_PACKAGE_VERSION_MINOR "${GPSTK_VERSION_MINOR}" )
set( CPACK_PACKAGE_VERSION_PATCH "${GPSTK_VERSION_PATCH}" )
set( CPACK_PACKAGE_RELEASE ${GPSTK_RELEASE})
set( CPACK_INCLUDE_TOPLEVEL_DIRECTORY "OFF" )
set( CPACK_PACKAGE_INSTALL_DIRECTORY "gpstk")
set( CPACK_TOPLEVEL_TAG "gpstk" )
set( CPACK_INCLUDE_TOPLEVEL_DIRECTORY "OFF")

# RPM specific
set(CPACK_RPM_COMPONENT_INSTALL ON)
#set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/install/post_install_script.sh")
#set(CPACK_RPM_POST_UNINSTALL_SCRIPT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/install/post_uninstall_script.sh")
set(CPACK_RPM_PACKAGE_RELEASE ${PACKAGE_RELEASE})
set(CPACK_RPM_CHANGELOG_FILE ${CHANGELOG_INCLUDE})
set(CPACK_RPM_PACKAGE_LICENSE GPL)
set(CPACK_RPM_PACKAGE_GROUP "System Environment/Base")
set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION ${CPACK_PACKAGING_INSTALL_PREFIX})
set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION /usr/local)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CPACK_RPM_PACKAGE_ARCHITECTURE x86_64)
else()
    set(CPACK_RPM_PACKAGE_ARCHITECTURE i586)
endif()

set(CPACK_RPM_LIB_FILE_NAME     "${CPACK_PACKAGE_NAME}-lib-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CPACK_RPM_PACKAGE_ARCHITECTURE}.rpm")

set(CPACK_RPM_DEVEL_FILE_NAME "${CPACK_PACKAGE_NAME}-devel-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CPACK_RPM_PACKAGE_ARCHITECTURE}.rpm")
set(CPACK_RPM_DEVEL_PACKAGE_REQUIRES "${CPACK_PACKAGE_NAME}-lib = ${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}")

set(CPACK_RPM_BIN_FILE_NAME     "${CPACK_PACKAGE_NAME}-bin-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CPACK_RPM_PACKAGE_ARCHITECTURE}.rpm")
set(CPACK_RPM_BIN_PACKAGE_REQUIRES "${CPACK_PACKAGE_NAME}-lib = ${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}")


# DEB related
set(CPACK_DEBIAN_DEVEL_PACKAGE_DEPENDS "${CPACK_PACKAGE_NAME}-lib (${CPACK_PACKAGE_VERSION})")
set(CPACK_DEBIAN_BIN_PACKAGE_DEPENDS "${CPACK_PACKAGE_NAME}-lib (${CPACK_PACKAGE_VERSION})")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_DEBUG ON)
set(CPACK_DEBIAN_PACKAGE_RELEASE ${PACKAGE_RELEASE})
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEB_COMPONENT_INSTALL ON)

# Prevents unstripped-binary-or-object Lintian errors.
#SET(CPACK_STRIP_FILES "1")

include( CPack )
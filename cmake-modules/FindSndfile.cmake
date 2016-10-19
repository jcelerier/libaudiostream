# - Find sndfile
# Find the native sndfile includes and libraries
#
#  SNDFILE_INCLUDE_DIR - where to find sndfile.h, etc.
#  SNDFILE_LIBRARIES   - List of libraries when using libsndfile.
#  SNDFILE_FOUND       - True if libsndfile found.

if(NO_LIBSNDFILE)
	set(SNDFILE_FOUND False)
	set(SNDFILE_INCLUDE_DIR "nowhere")  # for onceonly check above
	set(SNDFILE_LIBRARIES "")
	add_definitions("-DNO_LIBSNDFILE")
elseif (SNDFILE_INCLUDE_DIR AND SNDFILE_LIBRARY)
	set(SNDFILE_LIBRARIES ${SNDFILE_LIBRARY})
	set(SNDFILE_FOUND TRUE)
else()
	find_path(SNDFILE_INCLUDE_DIR sndfile.h
		PATHS 
		  "$ENV{ProgramFiles}/Mega-Nerd/libsndfile/include"
		  "${SNDFILE_INCLUDE_DIR_HINT}"
	)

	find_library(SNDFILE_LIBRARY NAMES sndfile sndfile-1 libsndfile libsndfile-1
		PATHS 
		  "$ENV{ProgramFiles}/Mega-Nerd/libsndfile/lib"
		  "${SNDFILE_LIB_DIR_HINT}"
	)

	find_library(OGG_LIBRARY NAMES ogg
		PATHS 
		  "$ENV{ProgramFiles}/Mega-Nerd/libsndfile/lib"
		  "${SNDFILE_LIB_DIR_HINT}"
	)

	find_library(VORBIS_LIBRARY NAMES vorbis
		PATHS 
		  "$ENV{ProgramFiles}/Mega-Nerd/libsndfile/lib"
		  "${SNDFILE_LIB_DIR_HINT}"
	)

	find_library(VORBIS_ENCODE_LIBRARY NAMES vorbisenc
		PATHS 
		  "$ENV{ProgramFiles}/Mega-Nerd/libsndfile/lib"
		  "${SNDFILE_LIB_DIR_HINT}"
	)

	find_library(FLAC_LIBRARY NAMES flac
		PATHS 
		  "$ENV{ProgramFiles}/Mega-Nerd/libsndfile/lib"
		  "${SNDFILE_LIB_DIR_HINT}"
	)

	# Handle the QUIETLY and REQUIRED arguments and set SNDFILE_FOUND to TRUE if
	# all listed variables are TRUE.
	include(FindPackageHandleStandardArgs)
	find_package_handle_standard_args(Sndfile DEFAULT_MSG
		SNDFILE_LIBRARY SNDFILE_INCLUDE_DIR)

	if(SNDFILE_FOUND)
		set(SNDFILE_LIBRARIES ${SNDFILE_LIBRARY})
		if(OGG_LIBRARY)
		  set(SNDFILE_LIBRARIES ${OGG_LIBRARY} ${SNDFILE_LIBRARIES})
		endif()
		if(VORBIS_LIBRARY)
		  set(SNDFILE_LIBRARIES ${VORBIS_LIBRARY} ${SNDFILE_LIBRARIES})
		endif()
		if(VORBIS_ENCODE_LIBRARY)
		  set(SNDFILE_LIBRARIES ${VORBIS_ENCODE_LIBRARY} ${SNDFILE_LIBRARIES})
		endif()
		if(FLAC_LIBRARY)
		  set(SNDFILE_LIBRARIES ${FLAC_LIBRARY} ${SNDFILE_LIBRARIES})
		endif()
	else()
		set(SNDFILE_LIBRARIES)
	endif()

endif()

# fallback
if (APPLE AND NOT SNDFILE_FOUND)
	set(SNDFILE_FOUND TRUE)
	set(SNDFILE_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../src)
	set(SNDFILE_LIBRARIES ${CMAKE_CURRENT_LIST_DIR}/../macosx/libsndfile.a)
endif()
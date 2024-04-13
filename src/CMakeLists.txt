set(LIB_NAME e559) 

set(SOURCES
  # add your source files
  TVDCTrackingMergeProcessor.cc
  TVDCGeometryConverter.cc
  TVDCClusterizationSizeSelectableProcessor.cc
  TTimingChargeMultiHitMappingProcessor.cc
  TTimingTrefValidator.cc
  TOpticsData.cc
  TOpticsCalibrationProcessor.cc
  )

set(HEADERS
  # add your source files
  TVDCTrackingMergeProcessor.h
  TVDCGeometryConverter.h
  TVDCClusterizationSizeSelectableProcessor.h  
  TTimingChargeMultiHitMappingProcessor.h
  TTimingTrefValidator.h
  TOpticsData.h
  TOpticsCalibrationProcessor.h
  )

add_library(${LIB_NAME} SHARED ${SOURCES})


target_include_directories(${LIB_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${LIB_NAME}
    PRIVATE
        artemis::catcore
        artemis::catloop
        artemis::artcont
        artemis::catcmd
        artemis::catmc
        artemis::artdecoder
        artemis::artridf
        artemis::artrdf
        artemis::arthist
        artemis::artparam
        artemis::artshare
        artemis::CAT
        ${YAML_CPP_LIBRARIES}
)
      
ROOT_GENERATE_DICTIONARY(G__${LIB_NAME}
    ${HEADERS}
    LINKDEF "linkdef_user.h"
    MODULE ${LIB_NAME}
)

set_target_properties(
    ${LIB_NAME}
    PROPERTIES
        PUBLIC_HEADER "${headers}"
)

install(TARGETS ${LIB_NAME}
    EXPORT e559
    INCLUDES DESTINATION include
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    LIBRARY DESTINATION lib
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${LIB_NAME}_rdict.pcm
    DESTINATION lib
)

if(NOT ${CHEMKIT_WITH_GRAPHICS})
  return()
endif()

find_package(Chemkit COMPONENTS gui REQUIRED)
include_directories(${CHEMKIT_INCLUDE_DIRS})

find_package(Qt4 4.6 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
set(QT_USE_QTOPENGL TRUE)
include(${QT_USE_FILE})

# disable Qt keywords
add_definitions("-DQT_NO_KEYWORDS")

find_package(OpenGL REQUIRED)

set(HEADERS
  graphicsatomitem.h
  graphicsbonditem.h
  graphicsboundingbox.h
  graphicscamera.h
  graphicscylinder.h
  graphicscylinderitem.h
  graphics.h
  graphicsisosurfaceitem.h
  graphicsitem.h
  graphicslight.h
  graphicsmaterial.h
  graphicsmolecularsurfaceitem.h
  graphicsmoleculeitem.h
  graphicsmoleculewireframeitem.h
  graphicsnavigationtool.h
  graphicsnucleicaciditem.h
  graphicsoverlay.h
  graphicspainter.h
  graphicsproteincoilitem.h
  graphicsproteinhelixitem.h
  graphicsproteinitem.h
  graphicsproteinsheetitem.h
  graphicspymolsurfaceitem.h
  graphicsray.h
  graphicsringitem.h
  graphicsscene.h
  graphicssphere.h
  graphicssphereitem.h
  graphicstool.h
  graphicstransform.h
  graphicsvertexbuffer.h
  graphicsview.h
)

set(SOURCES
  graphicsatomitem.cpp
  graphicsbonditem.cpp
  graphicscamera.cpp
  graphics.cpp
  graphicscylinder.cpp
  graphicscylinderitem.cpp
  graphicsisosurfaceitem.cpp
  graphicsitem.cpp
  graphicslight.cpp
  graphicsmaterial.cpp
  graphicsmolecularsurfaceitem.cpp
  graphicsmoleculeitem.cpp
  graphicsmoleculewireframeitem.cpp
  graphicsnavigationtool.cpp
  graphicsnucleicaciditem.cpp
  graphicsoverlay.cpp
  graphicspainter.cpp
  graphicsproteincoilitem.cpp
  graphicsproteinhelixitem.cpp
  graphicsproteinitem.cpp
  graphicsproteinsheetitem.cpp
  graphicspymolsurfaceitem.cpp
  graphicsray.cpp
  graphicsringitem.cpp
  graphicsscene.cpp
  graphicssphere.cpp
  graphicssphereitem.cpp
  graphicstool.cpp
  graphicstransform.cpp
  graphicsvertexbuffer.cpp
  graphicsview.cpp
)

set(MOC_HEADERS
  graphicsoverlay.h
  graphicsview.h
)

qt4_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})
qt4_add_resources(RCC_SOURCES shaders.qrc)

# add external mskit source files
aux_source_directory(../3rdparty/mskit/ MSKIT_SOURCES)

add_definitions(
  -DCHEMKIT_GRAPHICS_LIBRARY
)

add_chemkit_library(chemkit-graphics ${SOURCES} ${MOC_SOURCES} ${RCC_SOURCES} ${MSKIT_SOURCES})
target_link_libraries(chemkit-graphics ${CHEMKIT_LIBRARIES} ${QT_LIBRARIES} ${OPENGL_LIBRARIES})

# install header files
install(FILES ${HEADERS} DESTINATION include/chemkit/)

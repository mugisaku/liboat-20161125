BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -I.. -Werror -Wno-unused-result


ifeq ($(opt),1)
  CXXFLAGS += -march=i686 -Os -fomit-frame-pointer
  LDFLAGS  += -s
else
  CXXFLAGS += -g
endif



CXXFLAGS += -I$(BASE_DIR)/$(DIR_PREFIX)/include
LDFLAGS  += -L$(BASE_DIR)/$(DIR_PREFIX)/lib -lstdc++


LDFLAGS   += -lstdc++  -L.
LIBS       =           -lSDL2main -lSDL2
MINGW_LIBS = -lmingw32 -lSDL2main -lSDL2  -mwindows  -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc

ifeq ($(mingw),1)
  EXE_EXT = .exe
  DIR_PREFIX = i686-w64-mingw32
  CMD_PREFIX = $(DIR_PREFIX)-
  LDFLAGS += $(MINGW_LIBS) -static
else
  LDFLAGS += $(LIBS)
endif




ifeq ($(emcc),1)
  CXX      = CCACHE_DIR=/tmp/ccachedir ccache emcc
  CXXFLAGS = -std=gnu++11 -I. -I.. -Werror -Wno-unused-result -Os -s USE_SDL=2
  EXE_EXT  = .html
  LDFLAGS  = 
else ifeq ($(ccache),1)
  CXX = CCACHE_DIR=/tmp/ccachedir ccache $(CMD_PREFIX)g++ #clang++ -Qunused-arguments
else
  CXX = $(CMD_PREFIX)g++
endif



STRIP = $(CMD_PREFIX)strip
AR    = $(CMD_PREFIX)ar


ifeq ($(delay),1)
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS)  $< -o $@
	sleep 1
endif


OBJ =                     \
  mg_core.o               \
  mg_core__edit.o         \
  mg_colorselector.o      \
  mg_motionselector.o     \
  mg_framepositioner.o    \
  mg_canvas.o             \
  mg_widget__manager.o    \
  mg_widget__tool.o       \
  mg_widget__edit.o       \
  mg_patterntable.o       \
  mg_patterndisplay.o     \
  mg_animationdisplay.o   \


.PHONY: all clean


all: $(OBJ)


clean:
	rm -f $(OBJ)




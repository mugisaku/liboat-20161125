BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -Werror -Wno-unused-result


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
  CXXFLAGS = -std=gnu++11 -I. -Werror -Wno-unused-result -Os -s USE_SDL=2
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


LIBOAT  = liboat.a


OAT_OBJ +=                 \
  oat.o                    \
  oat_font.o               \
  oat_color.o              \
  oat_box.o                \
  oat_widget.o             \
  oat_widget_render.o      \
  oat_iconmodule.o         \
  oat_icon.o               \
  oat_image.o              \
  oat_image_directcolor.o  \
  oat_image_indexcolor.o   \
  oat_canvas.o             \
  oat_canvas_transform.o   \
  oat_canvas_draw.o        \
  oat_canvas_draw_line.o   \
  oat_canvas_fill_area.o   \
  oat_text.o               \
  oat_dial.o               \
  oat_buttonmodule.o       \
  oat_button.o             \
  oat_table.o              \
  oat_checkform.o          \
  oat_master.o             \


.PHONY: all clean FORCE


all: $(LIBOAT) aicone$(EXE_EXT) correct$(EXE_EXT) edfont$(EXE_EXT) edsnd$(EXE_EXT)

clean:
	rm -f $(OAT_OBJ) $(LIBOAT)
	rm -f aicone$(EXE_EXT)
	rm -f correct$(EXE_EXT)
	rm -f edfont$(EXE_EXT)
	rm -f edsnd$(EXE_EXT)
	make -C fcfont clean
	make -C pwg clean


objects: $(OAT_OBJ)


$(LIBOAT): $(OAT_OBJ)
	$(AR) -crs $@ $(OAT_OBJ)
ifeq ($(opt),1)
	$(STRIP) --strip-unneeded  $@
endif




aicone$(EXE_EXT): aicone.cpp $(OAT_OBJ)
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS)  -o $@

correct$(EXE_EXT): correct.cpp space.cpp $(OAT_OBJ)
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS)  -o $@

edfont$(EXE_EXT): edfont.cpp FCFONT $(OAT_OBJ)
	$(CXX) edfont.cpp $(OAT_OBJ) fcfont/*.o $(CXXFLAGS) $(LDFLAGS)  -o $@

edsnd$(EXE_EXT): edsnd.cpp PWG $(OAT_OBJ)
	$(CXX) edsnd.cpp $(OAT_OBJ) pwg/*.o $(CXXFLAGS) -I/usr/include/SDL2 $(LDFLAGS) -o $@




FCFONT: FORCE
	make -C fcfont


PWG: FORCE
	make -C pwg


FORCE:
.PHONY: FORCE FCFONT PWG





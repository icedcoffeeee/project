SHELL = powershell

OUT_DIR = build
OUT_EXE = ${OUT_DIR}/example.exe
INCLUDES = /Iimgui /Iimgui/backends /IC:/tools/opencv/build/include
SOURCES = *.cpp imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_win32.cpp imgui/imgui*.cpp
LIBS = /LIBPATH:C:/tools/opencv/build/x64/vc16/lib /LIBPATH:C:/tools/opencv/build/x64/vc16/bin opengl32.lib opencv_world4100.lib
MULTI = $(if $(findstring R, $(MAKEFLAGS)),/MT,/MD)

CMD = cl
FLAGS = /nologo /Zi ${MULTI} /EHsc /std:c++17 /utf-8 ${INCLUDES} /D UNICODE /D _UNICODE ${SOURCES} /Fe${OUT_EXE} /Fo${OUT_DIR}/ /link ${LIBS}
RUN = $(if $(findstring r, $(MAKEFLAGS)),./${OUT_EXE},${BLANK})

.PHONY: all
all: app.cpp
	if (-not (Test-Path ${OUT_DIR})){ mkdir ${OUT_DIR} }
	${CMD} ${FLAGS}
	${RUN}

.PHONY: clean
clean:
	rm -Recurse -Force ${OUT_DIR},*.pdb

COMMA :=,
BLANK :=

config:
	@echo -e "CompileFlags:" > .clangd
	@echo -e " Compiler:" >> .clangd
	@echo -e "    $(CMD)" >> .clangd
	@echo -e -n "  Add: [" >> .clangd
	@echo -e "$(foreach flag, $(FLAGS),\n    $(flag)$(COMMA))" >> .clangd
	@echo -e "  ]" >> .clangd

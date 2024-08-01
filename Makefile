SHELL = powershell

OUT_DIR = build
OUT_EXE = ${OUT_DIR}/example.exe
INCLUDES = /I. /Iimgui /Iimgui/backends /IC:/tools/opencv/build/include
SOURCES = *.cpp imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_win32.cpp imgui/imgui*.cpp
LIBS = /LIBPATH:C:/tools/opencv/build/x64/vc16/lib /LIBPATH:C:/tools/opencv/build/x64/vc16/bin opengl32.lib opencv_world4100.lib
MULTI = $(if $(findstring R, $(MAKEFLAGS)),/MT,/MD)

CMD = cl
FLAGS = /nologo /Zi ${MULTI} /EHsc /std:c++17 /utf-8 ${INCLUDES} /D UNICODE /D _UNICODE ${SOURCES} /Fe${OUT_EXE} /Fo${OUT_DIR}/ /link ${LIBS}
RUN = $(if $(findstring r, $(MAKEFLAGS)),./${OUT_EXE},${BLANK})

.PHONY: all
all:
	@echo "Compiling..."
	@echo "run with -r to open after compilation."
	@echo "run with -R to compile in release mode."
	@echo "run with `config` to generate .clangd."
	@if (-not (Test-Path ${OUT_DIR})){ mkdir ${OUT_DIR} }
	${CMD} ${FLAGS}
	${RUN}

.PHONY: clean
clean:
	rm -Recurse -Force ${OUT_DIR},*.pdb

COMMA :=,
BLANK :=

config:
	@echo "CompileFlags:" > conf
	@echo "  Compiler:" >> conf
	@echo "    $(CMD)" >> conf
	@echo "  Add: [" >> conf
	$(foreach flag, $(FLAGS),@echo "    $(flag)$(COMMA)") >> conf
	@echo "  ]" >> conf
	Get-Content .\conf | Set-Content -Encoding utf8 .clangd
	rm .\conf

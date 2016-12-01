# main directories
SRC=src
TEST=test
FIXTURE=fixture

## individual project names

# sub projects (code)
AI=ai
BUILD=build
CORE=core
GAMES=games
GEOMETRY=geometry
GOAL=goal
GUI=gui
GUICORE=guicore
LANG=lang
MAIN=main
MISC=misc
SDLWRAP=sdlwrap
SIMULATOR=simulator
SOUND=sound
UI=ui
EF2=ef2

# sub projects (fixtures)
AI_FIXTURE=aifixture
BUILD_FIXTURE=buildfixture
CORE_FIXTURE=corefixture
GEOMETRY_FIXTURE=geometryfixture
GOAL_FIXTURE=goalfixture
LANG_FIXTURE=langfixture
MISC_FIXTURE=miscfixture
SIMULATOR_FIXTURE=simulatorfixture
SDLWRAP_FIXTURE=sdlwrapfixture
GUICORE_FIXTURE=guicorefixture
GUI_FIXTURE=guifixture
UI_FIXTURE=uifixture
MAIN_FIXTURE=mainfixture

# sub projects (tests)
AI_TEST=aitest
BUILD_TEST=buildtest
CORE_TEST=coretest
GEOMETRY_TEST=geometrytest
GOAL_TEST=goaltest
LANG_TEST=langtest
MISC_TEST=misctest
SIMULATOR_TEST=simulatortest
SDLWRAP_TEST=sdlwraptest
GUICORE_TEST=guicoretest
GUI_TEST=guitest
UI_TEST=uitest
MAIN_TEST=maintest


## directories

# sub projects (code)
AI_DIR=$(SRC)/$(AI)
BUILD_DIR=$(SRC)/$(BUILD)
CORE_DIR=$(SRC)/$(CORE)
GAMES_DIR=$(SRC)/$(GAMES)
GEOMETRY_DIR=$(SRC)/$(GEOMETRY)
GOAL_DIR=$(SRC)/$(GOAL)
GUI_DIR=$(SRC)/$(GUI)
GUICORE_DIR=$(SRC)/$(GUICORE)
LANG_DIR=$(SRC)/$(LANG)
MAIN_DIR=$(SRC)/$(MAIN)
MISC_DIR=$(SRC)/$(MISC)
SDLWRAP_DIR=$(SRC)/$(SDLWRAP)
SIMULATOR_DIR=$(SRC)/$(SIMULATOR)
SOUND_DIR=$(SRC)/$(SOUND)
UI_DIR=$(SRC)/$(UI)

# sub projects (fixtures)
AI_FIXTURE_DIR=$(FIXTURE)/$(AI_FIXTURE)
BUILD_FIXTURE_DIR=$(FIXTURE)/$(BUILD_FIXTURE)
CORE_FIXTURE_DIR=$(FIXTURE)/$(CORE_FIXTURE)
GEOMETRY_FIXTURE_DIR=$(FIXTURE)/$(GEOMETRY_FIXTURE)
GOAL_FIXTURE_DIR=$(FIXTURE)/$(GOAL_FIXTURE)
LANG_FIXTURE_DIR=$(FIXTURE)/$(LANG_FIXTURE)
MISC_FIXTURE_DIR=$(FIXTURE)/$(MISC_FIXTURE)
SIMULATOR_FIXTURE_DIR=$(FIXTURE)/$(SIMULATOR_FIXTURE)
SDLWRAP_FIXTURE_DIR=$(FIXTURE)/$(SDLWRAP_FIXTURE)
GUICORE_FIXTURE_DIR=$(FIXTURE)/$(GUICORE_FIXTURE)
GUI_FIXTURE_DIR=$(FIXTURE)/$(GUI_FIXTURE)
UI_FIXTURE_DIR=$(FIXTURE)/$(UI_FIXTURE)
MAIN_FIXTURE_DIR=$(FIXTURE)/$(MAIN_FIXTURE)


# sub projects (tests)
AI_TEST_DIR=$(TEST)/$(AI_TEST)
BUILD_TEST_DIR=$(TEST)/$(BUILD_TEST)
CORE_TEST_DIR=$(TEST)/$(CORE_TEST)
GEOMETRY_TEST_DIR=$(TEST)/$(GEOMETRY_TEST)
GOAL_TEST_DIR=$(TEST)/$(GOAL_TEST)
LANG_TEST_DIR=$(TEST)/$(LANG_TEST)
MISC_TEST_DIR=$(TEST)/$(MISC_TEST)
SIMULATOR_TEST_DIR=$(TEST)/$(SIMULATOR_TEST)
SDLWRAP_TEST_DIR=$(TEST)/$(SDLWRAP_TEST)
GUICORE_TEST_DIR=$(TEST)/$(GUICORE_TEST)
GUI_TEST_DIR=$(TEST)/$(GUI_TEST)
UI_TEST_DIR=$(TEST)/$(UI_TEST)
MAIN_TEST_DIR=$(TEST)/$(MAIN_TEST)

BOOST_INCLUDES = -isystem /var/source/boost_1_44_0
LIBRARIES = -lSDL -lSDLmain -L/var/source/boost_1_44_0/stage/lib -lboost_serialization -lboost_program_options -lboost_thread -lboost_system -lboost_log -lboost_date_time -lboost_filesystem -lboost_signals -L/usr/local/lib -lSDL_ttf -lSDL_image -lSDL_mixer -lboost_unit_test_framework
#-lboost_unit_test_framework

PROJECT_INCLUDES = $(INCLUDES) -I $(SRC) -I $(TEST) -I $(FIXTURE)

#LD_FLAGS=-static
CPPFLAGS =
CXXFLAGS = $(LIBRARIES) $(BOOST_INCLUDES) $(PROJECT_INCLUDES) -g -ansi -pedantic-errors -W -Wall -Wmissing-braces -Wredundant-decls -Wundef -Wunused -Wconversion -Woverloaded-virtual -Wmissing-noreturn -Wdisabled-optimization -Wsign-promo -Wwrite-strings -Wlong-long -Woverloaded-virtual -Wfloat-equal -Wreturn-type -Wparentheses -Wchar-subscripts -Wimplicit  -Wtrigraphs  -Wendif-labels -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Winline -Wold-style-cast -Wswitch-enum -Wswitch -Wswitch-default -Wno-unknown-pragmas -O0 -ftest-coverage -fprofile-arcs
#-Weffc++
#-Wunreachable-code
#-Wshadow
#-Waggregate-return
#-Wpadded

#FLAGS = -O3 -pipe -ftracer -ffast-math -march=pentium4 -fmerge-all-constants --param max-crossjump-edges=2000 --param max-gcse-memory=209715200 --param max-gcse-passes=40 --param max-pending-list-length=1000 --param max-delay-slot-insn-search=2000 --param max-delay-slot-live-search=4000 -ffast-math -enable-stack-protector

CXX = g++ 
COVERAGE = gcov


.SUFFIXES: .o .cpp

# VERY IMPORTANT: sequence is important! first is the library that is dependant on the latter libraries

# --- TEST DEPS --- 
AI_TEST_DEPS = $(AI_TEST_DIR)/$(AI_TEST).a $(AI_FIXTURE_DIR)/$(AI_FIXTURE).a $(AI_DIR)/$(AI).a

BUILD_TEST_DEPS = $(BUILD_TEST_DIR)/$(BUILD_TEST).a $(BUILD_FIXTURE_DIR)/$(BUILD_FIXTURE).a $(BUILD_DIR)/$(BUILD).a

CORE_TEST_DEPS = $(CORE_TEST_DIR)/$(CORE_TEST).a $(CORE_FIXTURE_DIR)/$(CORE_FIXTURE).a $(CORE_DIR)/$(CORE).a $(GEOMETRY_DIR)/$(GEOMETRY).a $(GAMES_DIR)/$(GAMES).a $(MISC_DIR)/$(MISC).a

GEOMETRY_TEST_DEPS = $(GEOMETRY_TEST_DIR)/$(GEOMETRY_TEST).a $(GEOMETRY_DIR)/$(GEOMETRY).a $(GEOMETRY_FIXTURE_DIR)/$(GEOMETRY_FIXTURE).a $(MISC_DIR)/$(MISC).a 

GOAL_TEST_DEPS = $(GOAL_TEST_DIR)/$(GOAL_TEST).a $(GOAL_FIXTURE_DIR)/$(GOAL_FIXTURE).a $(GOAL_DIR)/$(GOAL).a $(GAMES_DIR)/$(GAMES).a $(CORE_FIXTURE_DIR)/$(CORE_FIXTURE).a $(CORE_DIR)/$(CORE).a $(GEOMETRY_DIR)/$(GEOMETRY).a $(MISC_DIR)/$(MISC).a

LANG_TEST_DEPS = $(LANG_TEST_DIR)/$(LANG_TEST).a $(LANG_FIXTURE_DIR)/$(LANG_FIXTURE).a $(LANG_DIR)/$(LANG).a $(MISC_DIR)/$(MISC).a

MISC_TEST_DEPS = $(MISC_TEST_DIR)/$(MISC_TEST).a $(MISC_FIXTURE_DIR)/$(MISC_FIXTURE).a $(MISC_DIR)/$(MISC).a

SIMULATOR_TEST_DEPS = $(SIMULATOR_TEST_DIR)/$(SIMULATOR_TEST).a $(SIMULATOR_FIXTURE_DIR)/$(SIMULATOR_FIXTURE).a $(SIMULATOR_DIR)/$(SIMULATOR).a $(MISC_DIR)/$(MISC).a $(GEOMETRY_DIR)/$(GEOMETRY).a $(CORE_DIR)/$(CORE).a $(GOAL_DIR)/$(GOAL).a

GUICORE_TEST_DEPS = $(GUICORE_TEST_DIR)/$(GUICORE_TEST).a $(GUICORE_FIXTURE_DIR)/$(GUICORE_FIXTURE).a $(GUICORE_DIR)/$(GUICORE).a $(SDLWRAP_FIXTURE_DIR)/$(SDLWRAP_FIXTURE).a $(SDLWRAP_DIR)/$(SDLWRAP).a $(GEOMETRY_DIR)/$(GEOMETRY).a $(MISC_DIR)/$(MISC).a

SDLWRAP_TEST_DEPS = $(SDLWRAP_TEST_DIR)/$(SDLWRAP_TEST).a $(SDLWRAP_FIXTURE_DIR)/$(SDLWRAP_FIXTURE).a $(SDLWRAP_DIR)/$(SDLWRAP).a $(GUICORE_DIR)/$(GUICORE).a $(GEOMETRY_DIR)/$(GEOMETRY).a $(MISC_DIR)/$(MISC).a

GUI_TEST_DEPS = $(GUI_TEST_DIR)/$(GUI_TEST).a $(GUI_FIXTURE_DIR)/$(GUI_FIXTURE).a $(GUI_DIR)/$(GUI).a $(GUICORE_FIXTURE_DIR)/$(GUICORE_FIXTURE).a $(SDLWRAP_DIR)/$(SDLWRAP).a $(GUICORE_DIR)/$(GUICORE).a $(LANG_DIR)/$(LANG).a $(GEOMETRY_DIR)/$(GEOMETRY).a $(MISC_DIR)/$(MISC).a 

UI_TEST_DEPS = $(UI_TEST_DIR)/$(UI_TEST).a $(UI_FIXTURE_DIR)/$(UI_FIXTURE).a $(UI_DIR)/$(UI).a $(GUI_DIR)/$(GUI).a $(SDLWRAP_DIR)/$(SDLWRAP).a $(GUICORE_DIR)/$(GUICORE).a $(MISC_DIR)/$(MISC).a $(GEOMETRY_DIR)/$(GEOMETRY).a

MAIN_TEST_DEPS = $(MAIN_TEST_DIR)/$(MAIN_TEST).a $(MAIN_FIXTURE_DIR)/$(MAIN_FIXTURE).a $(MAIN_DIR)/$(MAIN).a $(GUI_DIR)/$(GUI).a $(SDLWRAP_DIR)/$(SDLWRAP).a $(GUICORE_FIXTURE_DIR)/$(GUICORE_FIXTURE).a $(GUICORE_DIR)/$(GUICORE).a $(LANG_FIXTURE_DIR)/$(LANG_FIXTURE).a $(LANG_DIR)/$(LANG).a $(MISC_DIR)/$(MISC).a $(GEOMETRY_DIR)/$(GEOMETRY).a


# --- TEST TARGETS ---
AI_TEST_TARGETS = $(AI_TEST) $(AI_FIXTURE) $(AI)

BUILD_TEST_TARGETS = $(BUILD_TEST) $(BUILD_FIXTURE) $(BUILD)

CORE_TEST_TARGETS = $(CORE_TEST) $(CORE_FIXTURE) $(CORE) $(MISC) $(GEOMETRY) $(GAMES)

GEOMETRY_TEST_TARGETS = $(GEOMETRY_TEST) $(GEOMETRY) $(GEOMETRY_FIXTURE) $(MISC)

GOAL_TEST_TARGETS = $(GOAL_TEST) $(GOAL) $(GOAL_FIXTURE) $(CORE) $(MISC) $(GEOMETRY) $(CORE_FIXTURE) $(CORE_TEST) $(GAMES)

LANG_TEST_TARGETS = $(LANG) $(LANG_FIXTURE) $(LANG_TEST) $(MISC)

MISC_TEST_TARGETS = $(MISC_TEST) $(MISC) $(MISC_FIXTURE)

SIMULATOR_TEST_TARGETS = $(SIMULATOR_TEST) $(SIMULATOR) $(SIMULATOR_FIXTURE) $(MISC) $(GEOMETRY) $(CORE) $(GOAL) $(BUILD) $(AI)

GUICORE_TEST_TARGETS = $(GUICORE_TEST) $(GUICORE_FIXTURE) $(SDLWRAP_FIXTURE) $(SDLWRAP) $(GUICORE) $(MISC) $(GEOMETRY)

SDLWRAP_TEST_TARGETS = $(SDLWRAP_TEST) $(SDLWRAP_FIXTURE) $(SDLWRAP) $(GUICORE) $(MISC) $(GEOMETRY)

GUI_TEST_TARGETS = $(GUI_TEST) $(GUI_FIXTURE) $(GUI) $(SDLWRAP) $(GUICORE_FIXTURE) $(GUICORE) $(LANG) $(MISC) $(GEOMETRY)

UI_TEST_TARGETS = $(UI_TEST) $(UI_FIXTURE) $(UI) $(GUI) $(SDLWRAP) $(GUICORE) $(MISC) $(GEOMETRY)

MAIN_TEST_TARGETS = $(MAIN_TEST) $(MAIN_FIXTURE) $(MAIN) $(GUI) $(SDLWRAP) $(GUICORE_FIXTURE) $(GUICORE) $(LANG_FIXTURE) $(LANG) $(MISC) $(GEOMETRY)


# --- Link programs ---

$(AI_TEST).bin : $(AI_TEST_TARGETS) $(AI_TEST_DEPS)
	$(CXX) $(AI_TEST_DEPS) $(CXXFLAGS) -o $(AI_TEST_DIR)/$(AI_TEST).bin

$(BUILD_TEST).bin : $(BUILD_TEST_TARGETS) $(BUILD_TEST_DEPS)
	$(CXX) $(BUILD_TEST_DEPS) $(CXXFLAGS) -o $(BUILD_TEST_DIR)/$(BUILD_TEST).bin

$(CORE_TEST).bin: $(CORE_TEST_TARGETS) $(CORE_TEST_DEPS)
	$(CXX) $(CORE_TEST_DEPS) $(CXXFLAGS) -o $(CORE_TEST_DIR)/$(CORE_TEST).bin

$(GEOMETRY_TEST).bin : $(GEOMETRY_TEST_TARGETS) $(GEOMETRY_TEST_DEPS)
	$(CXX) $(GEOMETRY_TEST_DEPS) $(CXXFLAGS) -o $(GEOMETRY_TEST_DIR)/$(GEOMETRY_TEST).bin

$(GOAL_TEST).bin : $(GOAL_TEST_TARGETS) $(GOAL_TEST_DEPS)
	$(CXX) $(GOAL_TEST_DEPS) $(CXXFLAGS) -o $(GOAL_TEST_DIR)/$(GOAL_TEST).bin

$(LANG_TEST).bin : $(LANG_TEST_TARGETS) $(LANG_TEST_DEPS)
	$(CXX) $(LANG_TEST_DEPS) $(CXXFLAGS) -o $(LANG_TEST_DIR)/$(LANG_TEST).bin

$(MISC_TEST).bin : $(MISC_TEST_TARGETS) $(MISC_TEST_DEPS)
	$(CXX) $(MISC_TEST_DEPS) $(CXXFLAGS) -o $(MISC_TEST_DIR)/$(MISC_TEST).bin

$(SIMULATOR_TEST).bin : $(SIMULATOR_TEST_TARGETS) $(SIMULATOR_TEST_DEPS)
	$(CXX) $(SIMULATOR_TEST_DEPS) $(CXXFLAGS) -o $(SIMULATOR_TEST_DIR)/$(SIMULATOR_TEST).bin
	
$(SDLWRAP_TEST).bin : $(SDLWRAP_TEST_TARGETS) $(SDLWRAP_TEST_DEPS)
	$(CXX) $(SDLWRAP_TEST_DEPS) $(CXXFLAGS) -o $(SDLWRAP_TEST_DIR)/$(SDLWRAP_TEST).bin

$(GUICORE_TEST).bin : $(GUICORE_TEST_TARGETS) $(GUICORE_TEST_DEPS)
	$(CXX) $(GUICORE_TEST_DEPS) $(CXXFLAGS) -o $(GUICORE_TEST_DIR)/$(GUICORE_TEST).bin

$(GUI_TEST).bin : $(GUI_TEST_TARGETS) $(GUI_TEST_DEPS)
	$(CXX) $(GUI_TEST_DEPS) $(CXXFLAGS) -o $(GUI_TEST_DIR)/$(GUI_TEST).bin

$(UI_TEST).bin : $(UI_TEST_TARGETS) $(UI_TEST_DEPS)
	$(CXX) $(UI_TEST_DEPS) $(CXXFLAGS) -o $(UI_TEST_DIR)/$(UI_TEST).bin

$(MAIN_TEST).bin : $(MAIN_TEST_TARGETS) $(MAIN_TEST_DEPS)
	$(CXX) $(MAIN_TEST_DEPS) $(CXXFLAGS) -o $(MAIN_TEST_DIR)/$(MAIN_TEST).bin


ALL_TESTS = trace_lang.info trace_geometry.info trace_misc.info trace_core.info trace_goal.info trace_sdlwrap.info trace_guicore.info trace_gui.info trace_main.info
#trace_ai.info trace_build.info trace_simulator.info trace_ui.info

all_tests: $(ALL_TESTS)


trace_lang.info:
	@lcov --zerocounters --directory .
	@$(LANG_TEST_DIR)/$(LANG_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_lang
	@lcov --extract $@ \*src\*  --output-file $@ ;

trace_geometry.info:
	@lcov --zerocounters --directory .
	@$(GEOMETRY_TEST_DIR)/$(GEOMETRY_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_geometry
	@lcov --extract $@ \*src\*  --output-file $@ ;

trace_misc.info:
	@lcov --zerocounters --directory .
	@$(MISC_TEST_DIR)/$(MISC_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_misc
	@lcov --extract $@ \*src\*  --output-file $@ ;

trace_core.info:
	@lcov --zerocounters --directory .
	@$(CORE_TEST_DIR)/$(CORE_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_core
	@lcov --extract $@ \*src\*  --output-file $@ ;

trace_goal.info:
	@lcov --zerocounters --directory .
	@$(GOAL_TEST_DIR)/$(GOAL_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_goal
	@lcov --extract $@ \*src\*  --output-file $@ ;

trace_ai.info:
	@lcov --zerocounters --directory .
	@$(AI_TEST_DIR)/$(AI_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_ai
	@lcov --extract $@ \*src\*  --output-file $@ ;

trace_build.info:
	@lcov --zerocounters --directory .
	@$(BUILD_TEST_DIR)/$(BUILD_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_build
	@lcov --extract $@ \*src\*  --output-file $@ ;

trace_simulator.info:
	@lcov --zerocounters --directory .
	@$(SIMULATOR_TEST_DIR)/$(SIMULATOR_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_simulator
	@lcov --extract $@ \*src\*  --output-file $@ ;

trace_sdlwrap.info:
	@lcov --zerocounters --directory .
	@$(SDLWRAP_TEST_DIR)/$(SDLWRAP_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_sdlwrap
	@lcov --extract $@ \*src\*  --output-file $@ ;

trace_guicore.info:
	@lcov --zerocounters --directory .
	@$(GUICORE_TEST_DIR)/$(GUICORE_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_guicore
	@lcov --extract $@ \*src\*  --output-file $@ ;

trace_gui.info:
	@lcov --zerocounters --directory .
	@$(GUI_TEST_DIR)/$(GUI_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_gui
	@lcov --extract $@ \*src\*  --output-file $@ ;

trace_ui.info:
	@lcov --zerocounters --directory .
	@$(UI_TEST_DIR)/$(UI_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_ui
	@lcov --extract $@ \*src\*  --output-file $@ ;

trace_main.info:
	@lcov --zerocounters --directory .
	@$(MAIN_TEST_DIR)/$(MAIN_TEST).bin
	@lcov --capture --directory . --output-file $@ --test-name my_test_main
	@lcov --extract $@ \*src\*  --output-file $@ ;


GENPNG = genpng
USE_GENPNG := $(shell $(GENPNG) --help >/dev/null 2>/dev/null; echo $$?)
ifeq ($(USE_GENPNG),0)
	FRAMES := --frames
else
	FRAMES :=
endif

output: 
	@LC_ALL=en_US
	@export LC_ALL
	@rm /var/www/coverage/* -rf
	@genhtml $(ALL_TESTS) --output-directory /var/www/coverage --title "Evolution Forge 2 Coverage" --show-details --description-file descriptions $(FRAMES) --legend
	@doxygen Doxyfile
	@rm /var/www/doxygen/* -rf
	@cp -r html/* /var/www/doxygen
       	
descriptions: descriptions.txt
	@gendesc descriptions.txt -o descriptions

# Compiling targets
$(AI):
	@cd $(AI_DIR) ; make $(AI) ;

$(BUILD):
	@cd $(BUILD_DIR) ; make $(BUILD) ;

$(CORE):
	@cd $(CORE_DIR) ; make $(CORE) ;

$(GAMES):
	@cd $(GAMES_DIR) ; make $(GAMES) ;

$(GEOMETRY):
	@cd $(GEOMETRY_DIR) ; make $(GEOMETRY) ;

$(GOAL):
	@cd $(GOAL_DIR) ; make $(GOAL) ;

$(GUI):
	@cd $(GUI_DIR) ; make $(GUI) ;

$(GUICORE):
	@cd $(GUICORE_DIR) ; make $(GUICORE) ;

$(LANG):
	@cd $(LANG_DIR) ; make $(LANG) ;

$(MAIN):
	@cd $(MAIN_DIR) ; make $(MAIN) ;

$(MISC):
	@cd $(MISC_DIR) ; make $(MISC) ;

$(SDLWRAP):
	@cd $(SDLWRAP_DIR) ; make $(SDLWRAP) ;

$(SIMULATOR):
	@cd $(SIMULATOR_DIR) ; make $(SIMULATOR) ;

$(SOUND):
	@cd $(SOUND_DIR) ; make $(SOUND) ;

$(UI):
	@cd $(UI_DIR) ; make $(UI) ;

$(AI_FIXTURE):
	@cd $(AI_FIXTURE_DIR) ; make $(AI_FIXTURE) ;

$(BUILD_FIXTURE):
	@cd $(BUILD_FIXTURE_DIR) ; make $(BUILD_FIXTURE) ;

$(CORE_FIXTURE):
	@cd $(CORE_FIXTURE_DIR) ; make $(CORE_FIXTURE) ;

$(GEOMETRY_FIXTURE):
	@cd $(GEOMETRY_FIXTURE_DIR) ; make $(GEOMETRY_FIXTURE) ;

$(GOAL_FIXTURE):
	@cd $(GOAL_FIXTURE_DIR) ; make $(GOAL_FIXTURE) ;

$(LANG_FIXTURE):
	@cd $(LANG_FIXTURE_DIR) ; make $(LANG_FIXTURE) ;

$(MISC_FIXTURE):
	@cd $(MISC_FIXTURE_DIR) ; make $(MISC_FIXTURE) ;

$(SIMULATOR_FIXTURE):
	@cd $(SIMULATOR_FIXTURE_DIR) ; make $(SIMULATOR_FIXTURE) ;

$(SDLWRAP_FIXTURE):
	@cd $(SDLWRAP_FIXTURE_DIR) ; make $(SDLWRAP_FIXTURE) ;

$(GUICORE_FIXTURE):
	@cd $(GUICORE_FIXTURE_DIR) ; make $(GUICORE_FIXTURE) ;

$(GUI_FIXTURE):
	@cd $(GUI_FIXTURE_DIR) ; make $(GUI_FIXTURE) ;

$(UI_FIXTURE):
	@cd $(UI_FIXTURE_DIR) ; make $(UI_FIXTURE) ;

$(MAIN_FIXTURE):
	@cd $(MAIN_FIXTURE_DIR) ; make $(MAIN_FIXTURE) ;


$(AI_TEST):
	@cd $(AI_TEST_DIR) ; make $(AI_TEST) ;

$(BUILD_TEST):
	@cd $(BUILD_TEST_DIR) ; make $(BUILD_TEST) ;

$(CORE_TEST):
	@cd $(CORE_TEST_DIR) ; make $(CORE_TEST) ;

$(GEOMETRY_TEST):
	@cd $(GEOMETRY_TEST_DIR) ; make $(GEOMETRY_TEST) ;

$(GOAL_TEST):
	@cd $(GOAL_TEST_DIR) ; make $(GOAL_TEST) ;

$(LANG_TEST):
	@cd $(LANG_TEST_DIR) ; make $(LANG_TEST) ;

$(MISC_TEST):
	@cd $(MISC_TEST_DIR) ; make $(MISC_TEST) ;

$(SIMULATOR_TEST):
	@cd $(SIMULATOR_TEST_DIR) ; make $(SIMULATOR_TEST) ;

$(SDLWRAP_TEST):
	@cd $(SDLWRAP_TEST_DIR) ; make $(SDLWRAP_TEST) ;

$(GUICORE_TEST):
	@cd $(GUICORE_TEST_DIR) ; make $(GUICORE_TEST) ;

$(GUI_TEST):
	@cd $(GUI_TEST_DIR) ; make $(GUI_TEST) ;

$(UI_TEST):
	@cd $(UI_TEST_DIR) ; make $(UI_TEST) ;

$(MAIN_TEST):
	@cd $(MAIN_TEST_DIR) ; make $(MAIN_TEST) ;

clean:
	@cd $(AI_DIR) ; make clean
	@cd $(BUILD_DIR) ; make clean
	@cd $(CORE_DIR) ; make clean
	@cd $(GAMES_DIR) ; make clean
	@cd $(GEOMETRY_DIR) ; make clean
	@cd $(GOAL_DIR) ; make clean
	@cd $(GUI_DIR) ; make clean
	@cd $(GUICORE_DIR) ; make clean
	@cd $(LANG_DIR) ; make clean
	@cd $(MAIN_DIR) ; make clean
	@cd $(MISC_DIR) ; make clean
	@cd $(SDLWRAP_DIR) ; make clean
	@cd $(SIMULATOR_DIR) ; make clean
	@cd $(SOUND_DIR) ; make clean
	@cd $(UI_DIR) ; make clean
	@cd $(AI_FIXTURE_DIR) ; make clean
	@cd $(BUILD_FIXTURE_DIR) ; make clean
	@cd $(CORE_FIXTURE_DIR) ; make clean
	@cd $(GEOMETRY_FIXTURE_DIR) ; make clean
	@cd $(GOAL_FIXTURE_DIR) ; make clean
	@cd $(LANG_FIXTURE_DIR) ; make clean
	@cd $(MISC_FIXTURE_DIR) ; make clean
	@cd $(SIMULATOR_FIXTURE_DIR) ; make clean
	@cd $(SDLWRAP_FIXTURE_DIR) ; make clean
	@cd $(GUICORE_FIXTURE_DIR) ; make clean
	@cd $(GUI_FIXTURE_DIR) ; make clean
	@cd $(UI_FIXTURE_DIR) ; make clean
	@cd $(MAIN_FIXTURE_DIR) ; make clean	
	@cd $(AI_TEST_DIR) ; make clean
	@cd $(BUILD_TEST_DIR) ; make clean
	@cd $(CORE_TEST_DIR) ; make clean
	@cd $(GEOMETRY_TEST_DIR) ; make clean
	@cd $(GOAL_TEST_DIR) ; make clean
	@cd $(LANG_TEST_DIR) ; make clean
	@cd $(MISC_TEST_DIR) ; make clean
	@cd $(SIMULATOR_TEST_DIR) ; make clean
	@cd $(SDLWRAP_TEST_DIR) ; make clean
	@cd $(GUICORE_TEST_DIR) ; make clean
	@cd $(GUI_TEST_DIR) ; make clean
	@cd $(UI_TEST_DIR) ; make clean
	@cd $(MAIN_TEST_DIR) ; make clean
	@find . -name \*.gcov -type f -delete
	@find . -name \*.gcda -type f -delete
	@find . -name \*.gcno -type f -delete
	@rm -vf *.info	
	@echo "done."

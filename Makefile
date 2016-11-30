SRC=src
TEST=test
FIXTURE=fixture

GOAL=$(SRC)/goal
AI=$(SRC)/ai
CORE=$(SRC)/core
GAME=$(SRC)/game
MISC=$(SRC)/misc
GAMES=$(SRC)/games
DATABASE=$(SRC)/database

GOAL_TEST=$(TEST)/goaltest
CORE_TEST=$(TEST)/coretest
GAMES_TEST=$(TEST)/gamestest

MISC_FIXTURE=$(FIXTURE)/miscfixture
CORE_FIXTURE=$(FIXTURE)/corefixture
GOAL_FIXTURE=$(FIXTURE)/goalfixture

CORE_OBJ=$(CORE)/unittype.o $(CORE)/distance.o $(CORE)/units.o $(CORE)/unitresourcetype.o $(CORE)/unit.o $(CORE)/rules.o $(CORE)/race.o $(CORE)/player.o $(CORE)/path.o $(CORE)/map.o $(CORE)/location.o $(CORE)/government.o $(CORE)/game.o
CORE_CPP=$(CORE)/unittype.cpp $(CORE)/distance.cpp $(CORE)/units.cpp $(CORE)/unitresourcetype.cpp $(CORE)/unit.cpp $(CORE)/rules.cpp $(CORE)/race.cpp $(CORE)/player.cpp $(CORE)/path.cpp $(CORE)/map.cpp $(CORE)/location.cpp $(CORE)/government.cpp $(CORE)/game.cpp
CORE_CPP_NAMES=unittype.cpp distance.cpp units.cpp unitresourcetype.cpp unit.cpp rules.cpp race.cpp player.cpp path.cpp map.cpp location.cpp government.cpp game.cpp

CORE_FIXTURE_OBJ=$(CORE_FIXTURE)/distance_fixture.o $(CORE_FIXTURE)/coordinate_fixture.o $(CORE_FIXTURE)/game_fixture.o $(CORE_FIXTURE)/government_fixture.o $(CORE_FIXTURE)/location_fixture.o $(CORE_FIXTURE)/map_fixture.o $(CORE_FIXTURE)/path_fixture.o $(CORE_FIXTURE)/player_fixture.o $(CORE_FIXTURE)/race_fixture.o $(CORE_FIXTURE)/rules_fixture.o $(CORE_FIXTURE)/unit_fixture.o $(CORE_FIXTURE)/unitresourcetype_fixture.o $(CORE_FIXTURE)/units_fixture.o $(CORE_FIXTURE)/unittype_fixture.o

CORE_FIXTURE_CPP=$(CORE_FIXTURE)/distance_fixture.cpp $(CORE_FIXTURE)/coordinate_fixture.cpp $(CORE_FIXTURE)/game_fixture.cpp $(CORE_FIXTURE)/government_fixture.cpp $(CORE_FIXTURE)/location_fixture.cpp $(CORE_FIXTURE)/map_fixture.cpp $(CORE_FIXTURE)/path_fixture.cpp $(CORE_FIXTURE)/player_fixture.cpp $(CORE_FIXTURE)/race_fixture.cpp $(CORE_FIXTURE)/rules_fixture.cpp $(CORE_FIXTURE)/unit_fixture.cpp $(CORE_FIXTURE)/unitresourcetype_fixture.cpp $(CORE_FIXTURE)/units_fixture.cpp $(CORE_FIXTURE)/unittype_fixture.cpp

CORE_TEST_CPP=$(CORE_TEST)/coordinate_test.cpp $(CORE_TEST)/distance_test.cpp  $(CORE_TEST)/government_test.cpp $(CORE_TEST)/location_test.cpp $(CORE_TEST)/race_test.cpp $(CORE_TEST)/unit_test.cpp $(CORE_TEST)/unitresourcetype_test.cpp $(CORE_TEST)/path_test.cpp $(CORE_TEST)/unittype_test.cpp $(CORE_TEST)/units_test.cpp $(CORE_TEST)/map_test.cpp $(CORE_TEST)/rules_test.cpp $(CORE_TEST)/game_test.cpp  $(CORE_TEST)/player_test.cpp 

# TODO test_main separat falls wirklich eine gemeinsame gcov Op durchgefuehrt werden soll

GOAL_OBJ=$(GOAL)/processedgoal.o $(GOAL)/processedgoalentry.o $(GOAL)/goalentry.o $(GOAL)/goal.o
GOAL_CPP=$(GOAL)/processedgoal.cpp $(GOAL)/processedgoalentry.cpp $(GOAL)/goalentry.cpp $(GOAL)/goal.cpp
GOAL_CPP_NAMES=processedgoal.cpp processedgoalentry.cpp goalentry.cpp goal.cpp

GOAL_FIXTURE_OBJ=$(GOAL_FIXTURE)/processedgoal_fixture.o $(GOAL_FIXTURE)/processedgoalentry_fixture.o $(GOAL_FIXTURE)/goal_fixture.o $(GOAL_FIXTURE)/goalentry_fixture.o
GOAL_FIXTURE_CPP=$(GOAL_FIXTURE)/processedgoal_fixture.cpp $(GOAL_FIXTURE)/processedgoalentry_fixture.cpp  $(GOAL_FIXTURE)/goal_fixture.cpp $(GOAL_FIXTURE)/goalentry_fixture.cpp

GOAL_TEST_CPP=$(GOAL_TEST)/processedgoal_test.cpp $(GOAL_TEST)/processedgoalentry_test.cpp $(GOAL_TEST)/goal_test.cpp $(GOAL_TEST)/goalentry_test.cpp

MISC_FIXTURE_OBJ=$(MISC_FIXTURE)/random_fixture.o
MISC_FIXTURE_CPP=$(MISC_FIXTURE)/random_fixture.cpp

GAMES_OBJ=$(GAMES)/broodwar.o
GAMES_CPP=$(GAMES)/broodwar.cpp

DATABASE_OBJ=$(DATABASE)/globalstorage.o
DATABASE_CPP=$(DATABASE)/globalstorage.cpp
DATABASE_CPP_NAMES=globalstorage.cpp

PROJECT_INCLUDES = -I $(MISC) -I $(CORE) -I $(CORE_FIXTURE) -I $(GOAL) -I $(GOAL_FIXTURE) -I $(GAMES) -I $(MISC_FIXTURE) -I $(DATABASE)

CPPFLAGS =
CXXFLAGS = $(PROJECT_INCLUDES) -ansi -pedantic-errors -W -Wall -Wmissing-braces -Wredundant-decls -Wundef -Wunused -Wconversion -Woverloaded-virtual -Wmissing-noreturn -Wdisabled-optimization -Wsign-promo -Wwrite-strings -Wlong-long -Woverloaded-virtual -Wfloat-equal -Wreturn-type -Wparentheses -Wchar-subscripts -Wimplicit  -Wtrigraphs  -Wendif-labels -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Winline -Wold-style-cast -Wswitch-enum -Wswitch -Wswitch-default -Wno-unknown-pragmas  
#-Weffc++
#-Wunreachable-code
#-Wshadow
#-Waggregate-return
#-Wpadded

#FLAGS = -O3 -pipe -ftracer -ffast-math -march=pentium4 -fmerge-all-constants --param max-crossjump-edges=2000 --param max-gcse-memory=209715200 --param max-gcse-passes=40 --param max-pending-list-length=1000 --param max-delay-slot-insn-search=2000 --param max-delay-slot-live-search=4000 -ffast-math -enable-stack-protector

CXX = g++ 
COVERAGE = gcov

# -isystem surpresses BOOST warnings
INCLUDES = -isystem /var/source/boost_1_44_0 -lboost_serialization -lboost_unit_test_framework -lboost_program_options -lboost_thread

.SUFFIXES: .o .cpp
coretest:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TEST)/test_main.cpp $(CORE_TEST_CPP) $(CORE_CPP) $(GAMES_CPP) $(CORE_FIXTURE_CPP) $(MISC_FIXTURE_CPP) $(DATABASE_CPP) -o coretest
	@./coretest --build_info=yes --random=1 --show_progress=yes
goaltest:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TEST)/test_main.cpp $(GOAL_TEST_CPP) $(CORE_CPP) $(GOAL_CPP) $(GAMES_CPP) $(CORE_FIXTURE_CPP) $(GOAL_FIXTURE_CPP) $(MISC_FIXTURE_CPP) $(DATABASE_CPP) -o goaltest
	@./goaltest --build_info=yes --random=1 --show_progress=yes

gcov:
	$(CXX) -O0 -ftest-coverage -fprofile-arcs $(PROJECT_INCLUDES) $(INCLUDES) $(TEST)/test_main.cpp $(CORE_TEST_CPP) $(GOAL_TEST_CPP) $(CORE_CPP) $(GOAL_CPP) $(GAMES_CPP) $(CORE_FIXTURE_CPP) $(GOAL_FIXTURE_CPP) $(MISC_FIXTURE_CPP) $(DATABASE_CPP) -o rungcovtest 
	@./rungcovtest
	@if test -e coverage.txt; \
	then mv coverage.txt coverage.txt.old; \
	fi
	@for entry in $(CORE_CPP) ; do \
		gcov $$entry | grep "File '$$entry'" -A 1 >> coverage.txt; \
	done
	@for entry in $(GOAL_CPP) ; do \
		gcov $$entry | grep "File '$$entry'" -A 1 >> coverage.txt; \
	done	
	@for entry in $(DATABASE_CPP) ; do \
		gcov $$entry | grep "File '$$entry'" -A 1 >> coverage.txt; \
	done	
	@for entry in $(CORE_CPP_NAMES) ; do \
		cp $$entry.gcov /var/www/unittest/gcov; \
	done
	@for entry in $(GOAL_CPP_NAMES) ; do \
		cp $$entry.gcov /var/www/unittest/gcov; \
	done
	@for entry in $(DATABASE_CPP_NAMES) ; do \
		cp $$entry.gcov /var/www/unittest/gcov; \
	done
	@./transform coverage.txt
	@cp coverage.html /var/www/unittest

transform:
	$(CXX) transform.cpp -o transform

#createrulesxml:
#	$(CXX) $(INCLUDES) Games/createRulesXML.cpp core.a games.a -o createRulesXML -I Games
	

#release: 
#	$(CXX) $(CXXFLAGS) $(INCLUDES) core.a goal.a games.a

miscfixture: obj/miscfixture.a($(MISC_FIXTURE_OBJ))
corefixture: obj/corefixture.a($(CORE_FIXTURE_OBJ))
goalfixture: obj/goalfixture.a($(GOAL_FIXTURE_OBJ))
core: obj/core.a($(CORE_OBJ))
goal: obj/goal.a($(GOAL_OBJ))
games: obj/games.a($(GAMES_OBJ))

clean:
	@rm -vf obj/*
	@rm -vf coretest
	@rm -vf goaltest
	@rm -vf rungcovtest
	@rm -vf *.gcov
	@rm -vf *.gcda
	@rm -vf *.gcno
	@echo "done."

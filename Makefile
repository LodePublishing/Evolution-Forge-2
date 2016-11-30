GOAL=src/goal
BROODWAR=src/broodwar
AI=src/ai
CORE=src/core
GAME=src/game
MISC=src/misc
GAMES=src/games

CORE_TEST=test/coretest
GAMES_TEST=test/gamestest

CORE_FIXTURE=fixture/corefixture

CORE_OBJ=$(CORE)/unittype.o $(CORE)/units.o $(CORE)/unitresourcetype.o $(CORE)/unit.o $(CORE)/rules.o $(CORE)/race.o $(CORE)/player.o $(CORE)/path.o $(CORE)/map.o $(CORE)/location.o $(CORE)/government.o $(CORE)/goalentry.o $(CORE)/goal.o $(CORE)/game.o $(CORE)/distance.o $(CORE)/coordinate.o

CORE_CPP=$(CORE)/unittype.cpp $(CORE)/units.cpp $(CORE)/unitresourcetype.cpp $(CORE)/unit.cpp $(CORE)/rules.cpp $(CORE)/race.cpp $(CORE)/player.cpp $(CORE)/path.cpp $(CORE)/map.cpp $(CORE)/location.cpp $(CORE)/government.cpp $(CORE)/goalentry.cpp $(CORE)/goal.cpp $(CORE)/game.cpp $(CORE)/distance.cpp $(CORE)/coordinate.cpp

CORE_CPP_NAMES=unittype.cpp units.cpp unitresourcetype.cpp unit.cpp rules.cpp race.cpp player.cpp path.cpp map.cpp location.cpp government.cpp goalentry.cpp goal.cpp game.cpp distance.cpp coordinate.cpp

CORE_FIXTURE_OBJ=$(CORE_FIXTURE)/distance_fixture.o $(CORE_FIXTURE)/coordinate_fixture.o $(CORE_FIXTURE)/game_fixture.o $(CORE_FIXTURE)/goal_fixture.o $(CORE_FIXTURE)/goalentry_fixture.o $(CORE_FIXTURE)/government_fixture.o $(CORE_FIXTURE)/location_fixture.o $(CORE_FIXTURE)/map_fixture.o $(CORE_FIXTURE)/path_fixture.o $(CORE_FIXTURE)/player_fixture.o $(CORE_FIXTURE)/race_fixture.o $(CORE_FIXTURE)/rules_fixture.o $(CORE_FIXTURE)/unit_fixture.o $(CORE_FIXTURE)/unitresourcetype_fixture.o $(CORE_FIXTURE)/units_fixture.o $(CORE_FIXTURE)/unittype_fixture.o

GAMES_OBJ=$(GAMES)/gamedata.o $(GAMES)/broodwar.o

GOAL_OBJ=$(GOAL)/processedgoal.o $(GOAL)/processedgoalentry.o

CORETEST_CPP=$(CORE_TEST)/test_main.cpp $(CORE_TEST)/coordinate_test.cpp $(CORE_TEST)/distance_test.cpp $(CORE_TEST)/goal_test.cpp $(CORE_TEST)/goalentry_test.cpp $(CORE_TEST)/government_test.cpp $(CORE_TEST)/location_test.cpp $(CORE_TEST)/race_test.cpp $(CORE_TEST)/unit_test.cpp $(CORE_TEST)/unitresourcetype_test.cpp $(CORE_TEST)/path_test.cpp $(CORE_TEST)/unittype_test.cpp $(CORE_TEST)/units_test.cpp $(CORE_TEST)/map_test.cpp $(CORE_TEST)/rules_test.cpp $(CORE_TEST)/game_test.cpp  $(CORE_TEST)/player_test.cpp 

CPPFLAGS =
CXXFLAGS = -g -ansi -pedantic-errors -Wall -W -Wmissing-braces -Wredundant-decls -Wundef -Wunused -Wconversion -Woverloaded-virtual -Wmissing-noreturn -Wdisabled-optimization -Wsign-promo -Wwrite-strings -Wlong-long -Woverloaded-virtual -Wfloat-equal -Wreturn-type -Wparentheses -Wchar-subscripts -Wimplicit  -Wtrigraphs  -Wendif-labels -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Weffc++ -Winline -Wold-style-cast -Wswitch-enum -Wpadded -Waggregate-return -Wswitch -Wswitch-default -I $(MISC) -I $(CORE) -I $(CORE_FIXTURE) 
#-Wunreachable-code 
#-Wshadow

#FLAGS = -O3 -pipe -ftracer -ffast-math -march=pentium4 -fmerge-all-constants --param max-crossjump-edges=2000 --param max-gcse-memory=209715200 --param max-gcse-passes=40 --param max-pending-list-length=1000 --param max-delay-slot-insn-search=2000 --param max-delay-slot-live-search=4000 -ffast-math -enable-stack-protector

CXX = g++ 
COVERAGE = gcov

# -isystem surpresses BOOST warnings
INCLUDES = -isystem /var/source/boost_1_44_0 -lboost_serialization -lboost_unit_test_framework

.SUFFIXES: .o .cpp
coretest:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(CORETEST_CPP) obj/core.a obj/corefixture.a -o coretest
	@./coretest --build_info=yes --random=1 --show_progress=yes

gcov:
	$(CXX) -O0 -ftest-coverage -fprofile-arcs -I $(MISC) -I $(CORE) -I $(CORE_FIXTURE) $(INCLUDES) $(CORETEST_CPP) $(CORE_CPP) obj/corefixture.a -o rungcovtest 
	@./rungcovtest
	@if test -e coverage.txt; \
	then mv coverage.txt coverage.txt.old; \
	fi
	@for entry in $(CORE_CPP) ; do \
		gcov $$entry | grep "File '$$entry'" -A 1 >> coverage.txt; \
	done
	@for entry in $(CORE_CPP_NAMES) ; do \
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

corefixture: obj/corefixture.a($(CORE_FIXTURE_OBJ))
core: obj/core.a($(CORE_OBJ))
goal: obj/goal.a($(GOAL_OBJ))
games: obj/games.a($(GAMES_OBJ))

clean:
	@rm -vf obj/*
	@rm -vf coretest
	@rm -vf rungcovtest
	@rm -vf *.gcov
	@rm -vf *.gcda
	@rm -vf *.gcno
	@echo "done."

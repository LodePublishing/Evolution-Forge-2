GOAL=src/goal
BROODWAR=src/broodwar
AI=src/ai
CORE=src/core
GAME=src/game
MISC=src/misc
GAMES=src/games

GOAL_TEST=test/goaltest
CORE_TEST=test/coretest
GAMES_TEST=test/gamestest

MISC_FIXTURE=fixture/miscfixture
CORE_FIXTURE=fixture/corefixture
GOAL_FIXTURE=fixture/goalfixture

CORE_OBJ=$(CORE)/unittype.o $(CORE)/units.o $(CORE)/unitresourcetype.o $(CORE)/unit.o $(CORE)/rules.o $(CORE)/race.o $(CORE)/player.o $(CORE)/path.o $(CORE)/map.o $(CORE)/location.o $(CORE)/government.o $(CORE)/goalentry.o $(CORE)/goal.o $(CORE)/game.o $(CORE)/distance.o $(CORE)/globalstorage.o

CORE_CPP=$(CORE)/unittype.cpp $(CORE)/units.cpp $(CORE)/unitresourcetype.cpp $(CORE)/unit.cpp $(CORE)/rules.cpp $(CORE)/race.cpp $(CORE)/player.cpp $(CORE)/path.cpp $(CORE)/map.cpp $(CORE)/location.cpp $(CORE)/government.cpp $(CORE)/goalentry.cpp $(CORE)/goal.cpp $(CORE)/game.cpp $(CORE)/distance.cpp $(CORE)/globalstorage.cpp

CORE_CPP_NAMES=unittype.cpp units.cpp unitresourcetype.cpp unit.cpp rules.cpp race.cpp player.cpp path.cpp map.cpp location.cpp government.cpp goalentry.cpp goal.cpp game.cpp distance.cpp globalstorage.cpp

CORE_FIXTURE_OBJ=$(CORE_FIXTURE)/distance_fixture.o $(CORE_FIXTURE)/coordinate_fixture.o $(CORE_FIXTURE)/game_fixture.o $(CORE_FIXTURE)/goal_fixture.o $(CORE_FIXTURE)/goalentry_fixture.o $(CORE_FIXTURE)/government_fixture.o $(CORE_FIXTURE)/location_fixture.o $(CORE_FIXTURE)/map_fixture.o $(CORE_FIXTURE)/path_fixture.o $(CORE_FIXTURE)/player_fixture.o $(CORE_FIXTURE)/race_fixture.o $(CORE_FIXTURE)/rules_fixture.o $(CORE_FIXTURE)/unit_fixture.o $(CORE_FIXTURE)/unitresourcetype_fixture.o $(CORE_FIXTURE)/units_fixture.o $(CORE_FIXTURE)/unittype_fixture.o

COREFIXTURE_CPP=$(CORE_FIXTURE)/distance_fixture.cpp $(CORE_FIXTURE)/coordinate_fixture.cpp $(CORE_FIXTURE)/game_fixture.cpp $(CORE_FIXTURE)/goal_fixture.cpp $(CORE_FIXTURE)/goalentry_fixture.cpp $(CORE_FIXTURE)/government_fixture.cpp $(CORE_FIXTURE)/location_fixture.cpp $(CORE_FIXTURE)/map_fixture.cpp $(CORE_FIXTURE)/path_fixture.cpp $(CORE_FIXTURE)/player_fixture.cpp $(CORE_FIXTURE)/race_fixture.cpp $(CORE_FIXTURE)/rules_fixture.cpp $(CORE_FIXTURE)/unit_fixture.cpp $(CORE_FIXTURE)/unitresourcetype_fixture.cpp $(CORE_FIXTURE)/units_fixture.cpp $(CORE_FIXTURE)/unittype_fixture.cpp

CORETEST_CPP=$(CORE_TEST)/test_main.cpp $(CORE_TEST)/coordinate_test.cpp $(CORE_TEST)/distance_test.cpp $(CORE_TEST)/goal_test.cpp $(CORE_TEST)/goalentry_test.cpp $(CORE_TEST)/government_test.cpp $(CORE_TEST)/location_test.cpp $(CORE_TEST)/race_test.cpp $(CORE_TEST)/unit_test.cpp $(CORE_TEST)/unitresourcetype_test.cpp $(CORE_TEST)/path_test.cpp $(CORE_TEST)/unittype_test.cpp $(CORE_TEST)/units_test.cpp $(CORE_TEST)/map_test.cpp $(CORE_TEST)/rules_test.cpp $(CORE_TEST)/game_test.cpp  $(CORE_TEST)/player_test.cpp 

# TODO test_main separat falls wirklich eine gemeinsame gcov Op durchgefuehrt werden soll

GOAL_OBJ=$(GOAL)/processedgoal.o $(GOAL)/processedgoalentry.o

GOAL_CPP=$(GOAL)/processedgoal.cpp $(GOAL)/processedgoalentry.cpp

GOAL_CPP_NAMES=processedgoal.cpp processedgoalentry.cpp

GOAL_FIXTURE_OBJ=$(GOAL_FIXTURE)/processedgoal_fixture.o $(GOAL_FIXTURE)/processedgoalentry_fixture.o

GOALFIXTURE_CPP=$(GOAL_FIXTURE)/processedgoal_fixture.cpp $(GOAL_FIXTURE)/processedgoalentry_fixture.cpp

MISC_FIXTURE_OBJ=$(MISC_FIXTURE)/random_fixture.o

MISCFIXTURE_CPP=$(MISC_FIXTURE)/random_fixture.cpp

GOALTEST_CPP=$(GOAL_TEST)/processedgoal_test.cpp $(GOAL_TEST)/processedgoalentry_test.cpp

GAMES_OBJ=$(GAMES)/broodwar.o

GAMES_CPP=$(GAMES)/broodwar.cpp

PROJECT_INCLUDES = -I $(MISC) -I $(CORE) -I $(CORE_FIXTURE) -I $(GOAL) -I $(GOAL_FIXTURE) -I $(GAMES) -I $(MISC_FIXTURE)

CPPFLAGS =
CXXFLAGS = $(PROJECT_INCLUDES) -ansi -pedantic-errors -W -Wall -Wmissing-braces -Wredundant-decls -Wundef -Wunused -Wconversion -Woverloaded-virtual -Wmissing-noreturn -Wdisabled-optimization -Wsign-promo -Wwrite-strings -Wlong-long -Woverloaded-virtual -Wfloat-equal -Wreturn-type -Wparentheses -Wchar-subscripts -Wimplicit  -Wtrigraphs  -Wendif-labels -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Weffc++ -Winline -Wold-style-cast -Wswitch-enum -Wswitch -Wswitch-default -Wno-unknown-pragmas
#-Wunreachable-code
#-Wshadow
#-Waggregate-return
#-Wpadded

#FLAGS = -O3 -pipe -ftracer -ffast-math -march=pentium4 -fmerge-all-constants --param max-crossjump-edges=2000 --param max-gcse-memory=209715200 --param max-gcse-passes=40 --param max-pending-list-length=1000 --param max-delay-slot-insn-search=2000 --param max-delay-slot-live-search=4000 -ffast-math -enable-stack-protector

CXX = g++ 
COVERAGE = gcov

# -isystem surpresses BOOST warnings
INCLUDES = -isystem /var/source/boost_1_44_0 -lboost_serialization -lboost_unit_test_framework

.SUFFIXES: .o .cpp
coretest:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(CORETEST_CPP) $(CORE_CPP) $(COREFIXTURE_CPP) $(MISCFIXTURE_CPP) -o coretest
	@./coretest --build_info=yes --random=1 --show_progress=yes
goaltest:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(GOAL_TEST)/test_main.cpp $(GOALTEST_CPP) $(CORE_CPP) $(GOAL_CPP) $(GAMES_CPP) $(COREFIXTURE_CPP) $(GOALFIXTURE_CPP) $(MISCFIXTURE_CPP) -o goaltest
	@./goaltest --build_info=yes --random=1 --show_progress=yes

gcov:
	$(CXX) -O0 -ftest-coverage -fprofile-arcs $(PROJECT_INCLUDES) $(INCLUDES) $(CORETEST_CPP) $(GOALTEST_CPP) $(CORE_CPP) $(GOAL_CPP) $(GAMES_CPP) $(COREFIXTURE_CPP) $(GOALFIXTURE_CPP) $(MISCFIXTURE_CPP) -o rungcovtest 
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
	@for entry in $(CORE_CPP_NAMES) ; do \
		cp $$entry.gcov /var/www/unittest/gcov; \
	done
	@for entry in $(GOAL_CPP_NAMES) ; do \
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

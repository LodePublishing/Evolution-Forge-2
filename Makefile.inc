# main directories
SRC=src
TEST=test
FIXTURE=fixture

BOOST_INCLUDES = -isystem /var/source/boost_1_44_0
SDL_INCLUDES = -isystem /var/source/SDL-1.2.14/include -isystem /var/source/SDL_image-1.2.10 -isystem /var/source/SDL_ttf-2.0.10
PROJECT_INCLUDES = -I $(SRC) -I $(TEST) -I $(FIXTURE)

CXXFLAGS = -g -O0 -ftest-coverage -fprofile-arcs $(INCLUDES) $(SDL_INCLUDES) $(BOOST_INCLUDES) -ansi -pedantic-errors -W -Wall -Wmissing-braces -Wredundant-decls -Wundef -Wunused -Wconversion -Woverloaded-virtual -Wmissing-noreturn -Wdisabled-optimization -Wsign-promo -Wwrite-strings -Wlong-long -Woverloaded-virtual -Wfloat-equal -Wreturn-type -Wparentheses -Wchar-subscripts -Wimplicit  -Wtrigraphs  -Wendif-labels -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Winline -Wold-style-cast -Wswitch-enum -Wswitch -Wswitch-default -Wno-unknown-pragmas  

$(PROG): $(PROG).a($(OBJS))

clean:
	@rm -vf *.o ${PROG}
	@rm -vf *.a
	@rm -vf *.bin

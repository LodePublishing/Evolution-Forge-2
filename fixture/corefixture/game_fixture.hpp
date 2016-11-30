#ifndef _COREFIXTURE_GAMEFIXTURE_HPP
#define _COREFIXTURE_GAMEFIXTURE_HPP

#pragma warning(push, 0)  
#include <boost/smart_ptr.hpp>
#pragma warning(pop)

#include <game.hpp>

struct Game_Fixture
{
	const unsigned int test_startingTime;

	const boost::shared_ptr<Units> test_units;
	const boost::shared_ptr<Unit> test_unit1;
	const boost::shared_ptr<Unit> test_unit2;
	const boost::shared_ptr<Unit> test_unit3;
	
	const boost::shared_ptr<Game> test_game;

	const std::string test_filename_xml;
	const std::string test_filename;

	Game_Fixture();
	~Game_Fixture();
};

#endif // _COREFIXTURE_GAMEFIXTURE_HPP

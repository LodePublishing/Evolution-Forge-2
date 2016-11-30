#include <boost/assign/list_of.hpp>
#include <list>

int main() {
	using namespace std;
	using namespace boost;
	list<list<int> > myList(assign::list_of(assign::list_of(1))(assign::list_of(1)));
	list<list<int> > myList(assign::list_of(assign::list_of(1)));
}
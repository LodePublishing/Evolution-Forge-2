#ifndef MISC_SINGLETON_HPP
#define MISC_SINGLETON_HPP

#pragma warning(push, 0)
#include <boost/utility.hpp>
#include <boost/thread/once.hpp>
#include <boost/scoped_ptr.hpp>
#pragma warning(pop)
// Warning: If T's constructor throws, instance() will return a null reference.

template<class T>
class Singleton : private boost::noncopyable
{

public:
    static T& instance()
    {
        boost::call_once(init, flag);
        return *t;
    }

    static void init() // never throws
    {
        t.reset(new T());
    }

protected:
    virtual ~Singleton() {}
    Singleton() {}	

private:
	static boost::scoped_ptr<T> t;
    static boost::once_flag flag;
};

template<class T> boost::scoped_ptr<T> Singleton<T>::t(0);
template<class T> boost::once_flag Singleton<T>::flag = BOOST_ONCE_INIT;

#endif
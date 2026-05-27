#include <boost/test/unit_test.hpp>
#include <motors_yanmar_4lv150/Dummy.hpp>

using namespace motors_yanmar_4lv150;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    motors_yanmar_4lv150::DummyClass dummy;
    dummy.welcome();
}

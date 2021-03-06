#include <boost/log/trivial.hpp>
#include <quickmsg/publisher.hpp>
#include <quickmsg/publisher_wrap.h>

using namespace quickmsg;

extern "C" {

  qm_publisher_t
  qm_publisher_new (const char* topic, wait_mode_t wait_mode)
  {
    BOOST_LOG_TRIVIAL(debug) <<" Creating publisher with topic "<<topic<<std::endl;
    Publisher* pub = new Publisher(topic, wait_mode == qm_wait);
    return reinterpret_cast<qm_publisher_t>(pub);
  } 

  void 
  qm_publisher_destroy(qm_publisher_t self_p)
  {
    Publisher* pub = reinterpret_cast<Publisher*>(self_p);
    delete pub;
  }

  void 
  qm_publish(qm_publisher_t self_p, const char* msg)
  {
    Publisher* pub = reinterpret_cast<Publisher*>(self_p);
    pub->publish(msg);
  }
}

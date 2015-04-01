#include <quickmsg/client.hpp>

namespace quickmsg {

  void client_handler(const MessagePtr& msg, void* args)
  {
    static_cast<Client*>(args)->handle_response(msg);
  }

  Client::Client(const std::string& srv_name) : 
    srv_name_(srv_name)
  {
    wait_for_response_=false;
    // create the group node
    std::string name("C/");
    node_ = new GroupNode(name + srv_name);
    node_->join(srv_name_);
    node_->async_spin();
    std::cout << "waiting for server" << std::endl;
    node_->wait_join(srv_name_); // wait for service
    std::cout << "server joined group" << std::endl;
    node_->register_whispers(&client_handler, (void*)this);
  }

  Client::~Client()
  {
    node_->leave(srv_name_);
    node_->stop();
    delete node_;
  }
  
  void
  Client::call_srv(const std::string& req, double timeout_s)
  {
    wait_for_response_ = true;
    node_->shout(srv_name_, req);
    double start_t = clock();
    while ( wait_for_response_.load() && !interrupted() &&
            ((clock()-start_t) / (double)CLOCKS_PER_SEC) < timeout_s )
    {
      sleep(1);
    }
  }

  void 
  Client::handle_response(const MessagePtr& resp)
  {
    std::cout << "received response\n" << resp->msg << std::endl;
    wait_for_response_ = false;
  }

  bool
  Client::interrupted()
  {
    return node_->interrupted();
  }

  void 
  Client::spin()
  {
    node_->spin();
  }

  ServiceReplyPtr
  Client::call(const std::string& msg)
  {
    return boost::make_shared<ServiceReply>();
  }

}

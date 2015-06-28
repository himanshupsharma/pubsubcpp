#ifndef __PUBSUB_H__
#define __PUBSUB_H__

#include <iostream>

namespace PubSub {

class Observer;
typedef std::function<void(std::string)> Callback;
std::shared_ptr<Observer> subscribe(std::string type, Callback cb);
void publish(std::string type, std::string payload);

}

#endif //__PUBSUB_H__

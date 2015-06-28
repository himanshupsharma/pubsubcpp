#include "pubsub.hpp"

#include <deque>
#include <map>

namespace PubSub {
//class Observer;
//typedef std::function<void(std::string)> Callback;
//static std::shared_ptr<Observer> subscribe(std::string type, Callback cb);
//static void publish(std::string type, std::string payload);

class PubSubImpl;

/**********************************************/
class Observer {
public:
	Observer(std::string type, Callback cb);
	~Observer();

	void trigger(const std::string& payload);

private:
	std::string m_type;
	Callback m_cb;
};

/**********************************************/
class PubSubImpl {
public:
	void subscribe(std::string type, Observer* observer);
	void unsubscribe(std::string type, Observer* observer);
	void publish(std::string type, std::string payload);
	static PubSubImpl& instance();
private:
	PubSubImpl() {}

	typedef std::deque<Observer*> ObserverQueue;
	std::map<std::string, ObserverQueue> observerMap;
};

/**********************************************/
Observer::Observer(std::string type, Callback cb)
	: m_type(type)
	, m_cb(cb)
{
	PubSubImpl::instance().subscribe(type, this);
}

Observer::~Observer()
{
	PubSubImpl::instance().unsubscribe(m_type, this);
}

void Observer::trigger(const std::string& payload)
{
	m_cb(payload);
}

/**********************************************/
PubSubImpl& PubSubImpl::instance()
{
	static PubSubImpl obj;
	return obj;
}

void PubSubImpl::subscribe(std::string type, Observer* observer)
{
	if(observerMap.find(type) == observerMap.end())
		observerMap[type] = std::deque<Observer*>();
	observerMap[type].push_back(observer);
}

void PubSubImpl::unsubscribe(std::string type, Observer* observer)
{
	if(observerMap.find(type) == observerMap.end())
		return;
	for(auto it = observerMap[type].begin(); it != observerMap[type].end(); ++it) {
		//Remove observer from queue
		if(observer == *it) {
			observerMap[type].erase(it);
			break;
		}
	}
}

void PubSubImpl::publish(std::string type, std::string payload)
{
	if(observerMap.find(type) == observerMap.end())
		return;
	for(auto it = observerMap[type].begin(); it != observerMap[type].end(); ++it) {
		(*it)->trigger(payload);
	}
}

/**********************************************/

std::shared_ptr<Observer> subscribe(std::string type, Callback cb)
{
	return std::make_shared<Observer>(type, cb);
	
}

void publish(std::string type, std::string payload)
{
	PubSubImpl::instance().publish(type, payload);
}

}

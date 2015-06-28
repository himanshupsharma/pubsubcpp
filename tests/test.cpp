#include "pubsub.hpp"
#include "gtest/gtest.h"

using namespace std;

TEST(PubSubTest, Basic) {
	std::string receivedData("");
	auto cb = [&](std::string data) {
		receivedData = data;
	};
	std::shared_ptr<PubSub::Observer> obj;
	EXPECT_EQ(obj, nullptr);
	obj = PubSub::subscribe("type1",  cb);

	EXPECT_NE(obj, nullptr);
	PubSub::publish("type1", "payload1");
	EXPECT_EQ(receivedData, "payload1");
}

TEST(PubSubTest, TwoObservers) {
	auto count(0);
	auto cb = [&](std::string data) {
		EXPECT_EQ(data, "payload1");
		++count;
	};

	//First Observer
	std::shared_ptr<PubSub::Observer> obj1;
	EXPECT_EQ(obj1, nullptr);
	obj1 = PubSub::subscribe("type1",  cb);
	EXPECT_NE(obj1, nullptr);

	//Second Observer
	std::shared_ptr<PubSub::Observer> obj2;
	EXPECT_EQ(obj2, nullptr);
	obj2 = PubSub::subscribe("type1",  cb);
	EXPECT_NE(obj2, nullptr);

	PubSub::publish("type1", "payload1");
	EXPECT_EQ(count, 2);

	//Destroy first observer
	obj1.reset();
	count = 0;
	PubSub::publish("type1", "payload1");
	EXPECT_EQ(count, 1);

	//Destroy second observer
	obj2.reset();
	count = 0;
	PubSub::publish("type1", "payload1");
	EXPECT_EQ(count, 0);
}

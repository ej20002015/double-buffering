#include <iostream>
#include <thread>

#include "MessageRepository.h"

std::atomic<bool> read = true;

template<size_t N>
void readTopic(const MessageRepository<N>& messageRepository, const std::string& topic)
{
	while (read.load())
	{
		const auto message = messageRepository.readMessage(topic);
		if (message)
		{
			std::cout << "Topic: " << topic << " Message: " << message->get() << std::endl;
		}
		else
		{
			std::cout << "No message for topic: " << topic << std::endl;
		}
	}
}

int main()
{
	static constexpr auto TOPIC_NUM = 2;
    static constexpr auto MSG   = "Hello";
	static constexpr auto MSG_2 = "World";


	MessageRepository<TOPIC_NUM> messageRepository;
	std::thread t1(readTopic<TOPIC_NUM>, std::ref(messageRepository), "topic");

	std::this_thread::sleep_for(std::chrono::milliseconds(20));

	messageRepository.writeMessage("topic", reinterpret_cast<const uint8_t*>(MSG),   std::strlen(MSG));
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	messageRepository.writeMessage("topic", reinterpret_cast<const uint8_t*>(MSG_2), std::strlen(MSG_2));

	std::this_thread::sleep_for(std::chrono::milliseconds(1));

	read.store(false);
	t1.join();

    return 0;
}


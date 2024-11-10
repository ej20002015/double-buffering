#pragma once

#include "Buffer.h"
#include "DoubleBuffer.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <exception>
#include <array>

using Message = Buffer;

template<size_t N>
class MessageRepository
{
public:
	MessageRepository() = default;

	void writeMessage(const std::string& topic, const uint8_t* payload, const size_t size)
	{
		size_t index = 0;
		const auto it = m_topicToMessageIndex.find(topic);
		if (it != m_topicToMessageIndex.end())
			index = it->second;
		else
		{
			if (m_nextMessageIndex >= m_messages.size())
				throw std::exception("No more space for topics");
			index = m_nextMessageIndex++;
			m_topicToMessageIndex.emplace(std::make_pair(topic, index));
		}

		m_messages[index].write(std::make_shared<Message>(payload, size));
	}

	std::shared_ptr<Message> readMessage(const std::string& topic) const
	{
		const auto it = m_topicToMessageIndex.find(topic);
		if (it != m_topicToMessageIndex.end())
			return m_messages[it->second].read();

		return nullptr;
	}

private:
	std::array<DoubleBuffer<std::shared_ptr<Message>>, N> m_messages;
	std::unordered_map<std::string, size_t> m_topicToMessageIndex;
	size_t m_nextMessageIndex = 0;
};
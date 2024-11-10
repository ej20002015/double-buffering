#pragma once

#include <stdint.h>
#include <memory>

class Buffer
{
public:
	Buffer(const uint8_t* data, const size_t size)
		: m_data(new uint8_t[size]), m_size(size)
	{
		memcpy(m_data, data, size);
	}

	Buffer(const Buffer&) = delete;
	Buffer& operator=(const Buffer&) = delete;

	Buffer(Buffer&& other) = delete;
	Buffer& operator=(Buffer&& other) = delete;

	~Buffer()
	{
		delete[] m_data;
	}

	void setData(const uint8_t* data, const size_t size)
	{
		m_data = new uint8_t[size];
		memcpy(m_data, data, size);
		m_size = size;
	}

	const uint8_t* const get() const
	{
		return m_data;
	}

	size_t size() const
	{
		return m_size;
	}

private:
	uint8_t* m_data = nullptr;
	size_t m_size = 0;
};
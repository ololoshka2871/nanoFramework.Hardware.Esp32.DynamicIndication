#include <algorithm>

#include "DataBus.h"

using namespace nanoFramework::Hardware::Esp32::DynamicIndication;

DataBus::DataBus(CLR_RT_TypedArray_INT32 &pins)
	: pinsNumbers(pins.GetSize()), invert(false)
{
	auto it = pinsNumbers.begin();
	std::size_t i = 0;
	for (; it != pinsNumbers.end(); ++it, ++i)
	{
		auto pn = static_cast<gpio_num_t>(pins.GetValue(i));
		*it = pn;
		gpio_reset_pin(pn);
		gpio_set_direction(pn, GPIO_MODE_OUTPUT);
		gpio_set_pull_mode(pn, GPIO_FLOATING);
	}
	setData(0);
}

DataBus::~DataBus() {
	std::for_each(pinsNumbers.cbegin(), pinsNumbers.cend(), [](gpio_num_t pn) {
		gpio_reset_pin(pn);
	});
}

void DataBus::setData(uint32_t data)
{
	for (std::size_t i = 0; i < pinsNumbers.size(); ++i)
	{
		auto pn = pinsNumbers[i];
		gpio_set_level(pn, (((data & 1u << i) != 0) ^ invert));
	}
}

uint32_t DataBus::getData() const
{
	uint32_t res = 0;
	for (std::size_t i = 0; i < pinsNumbers.size(); ++i)
	{
		auto pn = pinsNumbers[i];
		if (gpio_get_level(pn) ^ invert)
		{
			res |= 1u << i;
		}
	}
	return res;
}

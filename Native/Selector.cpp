#include "Selector.h"

using namespace nanoFramework::Hardware::Esp32::DynamicIndication;

Selector::Selector(std::unique_ptr<IDataBus> &&selectorbus) : bus(std::move(selectorbus)), channel(0) 
{
	setEnabled(false);
}

Selector::~Selector() {
	setEnabled(false);
}

uint32_t Selector::next_element() {
	channel = (channel + 1) % bus->width();
	bus->setData(1u << channel);
	return channel;
}

void Selector::setEnabled(bool setEnabled) {
	bus->setData(setEnabled ? 1u << channel : 0);
}

bool Selector::isEnabled() const {
	return !!bus->getData();
}
#ifndef _NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_SELECTOR_H_
#define _NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_SELECTOR_H_

#include <memory>

#include "ISelector.h"
#include "IDataBus.h"

namespace nanoFramework
{
    namespace Hardware
    {
        namespace Esp32
        {
            namespace DynamicIndication
            { 
                /*
				struct Selector : public ISelector
				{
					Selector(std::unique_ptr<IDataBus> &&selectorbus);
                    ~Selector() override;

					uint32_t next_element() override;

					void setEnabled(bool setEnabled = true) override;
					bool isEnabled() const override;

                    uint32_t element_count() const override { return bus->width(); }

				private:
					std::unique_ptr<IDataBus> bus;
                    uint8_t channel;
				};
                */

                template<typename T>
                struct _Selector
                {
                    using bus_type = T;
                    using data_type = typename bus_type::data_type;

                    _Selector(std::shared_ptr<bus_type> &selectorBus) :
                        selectorBus(selectorBus), channel(0) {}

                    _Selector(const _Selector&) = delete;
                    
                    ~_Selector() { setEnabled(false); }

                    static constexpr data_type one() { return data_type(1); }

					uint32_t next_element() {
                        channel = (channel + 1) % selectorBus->width();
                        selectorBus->setData(one() << channel);
                        return channel;
                    }

					void setEnabled(bool setEnabled = true) {
                        selectorBus->setData(setEnabled ? one() << channel : 0);
                    }

					bool isEnabled() const { return !!selectorBus->getData(); }

                    uint32_t group_count() const { return selectorBus->width(); }

				private:
					std::shared_ptr<bus_type> selectorBus;
                    uint8_t channel;
                };
            }
        }
    }
}
#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_SELECTOR_H_

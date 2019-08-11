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
            }
        }
    }
}
#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_SELECTOR_H_

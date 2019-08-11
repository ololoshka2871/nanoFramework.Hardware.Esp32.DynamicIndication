#ifndef _NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_ISELECTOR_H_
#define _NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_ISELECTOR_H_

#include <cstdint>

namespace nanoFramework
{
    namespace Hardware
    {
        namespace Esp32
        {
            namespace DynamicIndication
            {
				struct ISelector
				{
					virtual uint32_t next_element() = 0;
                    virtual uint32_t element_count() const = 0;
					virtual void setEnabled(bool setEnabled = true) = 0;
					virtual bool isEnabled() const = 0;

                    virtual ~ISelector() {}
				};                    
            }
        }
    }
}
#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_ISELECTOR_H_

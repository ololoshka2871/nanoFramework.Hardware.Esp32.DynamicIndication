#ifndef _NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_IDATABUS_H_
#define _NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_IDATABUS_H_

namespace nanoFramework
{
    namespace Hardware
    {
        namespace Esp32
        {
            namespace DynamicIndication
            {
				struct IDataBus {
					virtual void setData(uint32_t data) = 0;
					virtual uint32_t getData() const = 0;
					virtual int width() const = 0;

                    virtual void setInverted(bool inverted) = 0;
                    virtual bool isInverted() const = 0;

                    virtual ~IDataBus() {}
				};
            }
        }
    }
}
#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_IDATABUS_H_

#ifndef _NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_DATABUS_H_
#define _NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_DATABUS_H_

#include <vector>

#include "nanoCLR_Interop.h"

#include "IDataBus.h"

namespace nanoFramework
{
    namespace Hardware
    {
        namespace Esp32
        {
            namespace DynamicIndication
            {			
				struct DataBus : public IDataBus {
					DataBus(CLR_RT_TypedArray_INT32& pins);
                    ~DataBus() override;

					void setData(uint32_t data) override;
					virtual uint32_t getData() const override;

					int width() const { return pinsNumbers.size(); }

                    void setInverted(bool inverted) override { invert = inverted; }
                    bool isInverted() const override { return invert; }

                private:
                    std::vector<gpio_num_t> pinsNumbers;
                    bool invert;
				};
            }
        }
    }
}

#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_DATABUS_H_

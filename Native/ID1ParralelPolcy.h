#ifndef _ID1_PARRALEL_POLICU_H_
#define _ID1_PARRALEL_POLICU_H_

#include <memory>

#include "IDataBus.h"

#include "IDisplayPolcy.h"

namespace nanoFramework
{
    namespace Hardware
    {
        namespace Esp32
        {
            namespace DynamicIndication
            {
                struct ID1ParralelPolicy : IDisplayPolcy {
                    ID1ParralelPolicy(std::unique_ptr<IDataBus> &&databus, const uint32_t group_count);

                    void setData(const std::vector<uint32_t> &data, uint32_t group) override;

                    static const uint32_t bits_pre_channel = 4;

                private:
                    std::unique_ptr<IDataBus> databus;
                    const uint32_t channels_pre_data_bus;
                    const uint32_t group_count;
                };
            }
        }
    }
}

#endif /* _ID1_PARRALEL_POLICU_H_ */
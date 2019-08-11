#ifndef _IDATA_POLICY_H_
#define _IDATA_POLICY_H_

#include <vector>

namespace nanoFramework
{
    namespace Hardware
    {
        namespace Esp32
        {
            namespace DynamicIndication
            {
                struct IDisplayPolcy {
                    virtual void setData(const std::vector<uint32_t> &data, uint32_t group) = 0;
                };
            }
        }
    }
}

#endif /* _IDATA_POLICY_H_ */
#ifndef _NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_CONTROLLER_H_
#define _NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_CONTROLLER_H_

#include "nanoCLR_Interop.h"

#include <map>

#include "NativeState.h"
#include "DataBus.h"
#include "Selector.h"
#include "ic74141ParralelPolcy.h"

namespace nanoFramework
{
    namespace Hardware
    {
        namespace Esp32
        {
            namespace DynamicIndication
            {
                struct Controller
                {
                    // release native context and linked resources such timer and pins
                    static void NativeDispose(CLR_RT_HeapBlock* pMngObj, HRESULT &hr);
                    // init new native context and link it to managed.
                    static void NativeInit(CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_INT32 &param0,
                        CLR_RT_TypedArray_INT32 &param1, signed int param2, HRESULT &hr);
                    // return if displaing enabled
                    static bool NativeIsEnabled(CLR_RT_HeapBlock* pMngObj, HRESULT &hr);
                    // set enable state to native part
                    static void NativeSetEnabled(CLR_RT_HeapBlock* pMngObj, bool param0, HRESULT &hr);
                    // set raw data to display
                    static void NativeSetData(CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT32 &param0, HRESULT &hr);
                    // set refrash interval for native part
                    static void NativeSetUpdateInterval(CLR_RT_HeapBlock* pMngObj, unsigned int param0, HRESULT &hr);
                    // get current update refrash rate
                    static unsigned int NativeGetUpdateInterval(CLR_RT_HeapBlock* pMngObj, HRESULT &hr);

                    using selector_t = _Selector<_DataBus<uint8_t>>;
                    using display_policy_t = ic7414ParralelPolicy<_DataBus<uint16_t>>;

                private:
                     static std::map<CLR_RT_HeapBlock *, _NativeState<selector_t, display_policy_t>> stateMap;
                };
            }
        }
    }
}

#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_CONTROLLER_H_

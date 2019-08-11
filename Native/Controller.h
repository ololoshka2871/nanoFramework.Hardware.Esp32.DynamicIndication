#ifndef _NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_CONTROLLER_H_
#define _NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_CONTROLLER_H_

#include <map>
#include <vector>
#include <memory>

#include "nanoCLR_Interop.h"

#include "make_unique_c11.h"
#include "ISelector.h"
#include "IDisplayPolcy.h"
#include "IDataBus.h"

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
                    struct NativeState {
                        NativeState(CLR_RT_TypedArray_INT32 &dataPins,
                            CLR_RT_TypedArray_INT32 &selectorPins, int indicators_count);   
                        ~NativeState();

                        bool setEnabled(bool enabled = true);
                        bool isEnabled() const { return selector->isEnabled(); }

                        void setUpdateInterval(uint32_t interval_us);
                        uint32_t getUpdateInterval() const  { return update_interval_us; }

                        void setData(CLR_RT_TypedArray_UINT32 &data);
                        bool Test1(CLR_RT_TypedArray_UINT32& testData) const;
                        
                    private:
                        std::unique_ptr<ISelector> selector;
                        std::unique_ptr<IDisplayPolcy> displayPolicy;
                        std::vector<uint32_t> m_data;
                        uint32_t update_interval_us;
                        int timer_idx;
                        int indicators_count;

                        bool EnableTimer();
                        bool DisableTimer();
                        void NextGroup();
                        void register_timer();
                        void unregister_timer();

                        static void timer_cb(void* arg);
                    };

                    static std::map<CLR_RT_HeapBlock*, NativeState> stateMap;

                    static void NativeDispose( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                    static void NativeInit( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_INT32 &param0,
                        CLR_RT_TypedArray_INT32 &param1, signed int param2, HRESULT &hr );
                    static bool NativeIsEnabled( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                    static void NativeSetEnabled( CLR_RT_HeapBlock* pMngObj, bool param0, HRESULT &hr );
                    static void NativeSetData( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT32 &param0, HRESULT &hr );
                    static void NativeSetUpdateInterval( CLR_RT_HeapBlock* pMngObj, unsigned int param0, HRESULT &hr );
                    static unsigned int NativeGetUpdateInterval( CLR_RT_HeapBlock* pMngObj, HRESULT &hr );
                    static bool NativeTest1( CLR_RT_HeapBlock* pMngObj, CLR_RT_TypedArray_UINT32 &param0, HRESULT &hr );
                };
            }
        }
    }
}

#endif  //_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_NANOFRAMEWORK_HARDWARE_ESP32_DYNAMICINDICATION_CONTROLLER_H_

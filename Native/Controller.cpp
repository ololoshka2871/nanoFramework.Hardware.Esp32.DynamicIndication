#include "nanoFramework_Hardware_Esp32_DynamicIndication.h"

#include "Controller.h"

using namespace nanoFramework::Hardware::Esp32::DynamicIndication;

//std::map<CLR_RT_HeapBlock *, Controller::NativeState> Controller::stateMap;

std::map<CLR_RT_HeapBlock *, _NativeState<Controller::selector_t, 
    Controller::display_policy_t>> Controller::stateMap;
    

void Controller::NativeDispose(CLR_RT_HeapBlock *pMngObj, HRESULT &hr)
{
    if (stateMap.find(pMngObj) == stateMap.end())
    {
        hr = CLR_E_OBJECT_DISPOSED;
    }
    else
    {
        stateMap.erase(pMngObj);
    }
}

void Controller::NativeInit(CLR_RT_HeapBlock *pMngObj, CLR_RT_TypedArray_INT32 &param0,
    CLR_RT_TypedArray_INT32 &param1, signed int param2, HRESULT &hr)
{
    if (stateMap.find(pMngObj) == stateMap.end())
    {
        auto a = std::make_shared<typename Controller::display_policy_t::bus_type>(param0);
        auto b = std::make_shared<typename Controller::selector_t::bus_type>(param1);
        
        auto c = new _NativeState<Controller::selector_t, Controller::display_policy_t>(a, b, param2);
       /*
        stateMap.emplace(std::piecewise_construct,
                         std::forward_as_tuple(pMngObj),
                         std::forward_as_tuple(
                             std::make_shared<typename Controller::display_policy_t::bus_type>(param0),
                             std::make_shared<typename Controller::selector_t::bus_type>(param1),
                             param2
                        ));
                        */
    }
    else
    {
        hr = CLR_E_BUSY;
    }
}

bool Controller::NativeIsEnabled(CLR_RT_HeapBlock *pMngObj, HRESULT &hr)
{
    auto pNativeThis = stateMap.find(pMngObj);
    if (pNativeThis == stateMap.end())
    {
        hr = CLR_E_OBJECT_DISPOSED;
        return false;
    }
    return pNativeThis->second.isEnabled();
}

void Controller::NativeSetEnabled(CLR_RT_HeapBlock *pMngObj, bool param0, HRESULT &hr)
{
    auto pNativeThis = stateMap.find(pMngObj);
    if (pNativeThis == stateMap.end())
    {
        hr = CLR_E_OBJECT_DISPOSED;
        return;
    }
    if (!(pNativeThis->second.setEnabled(param0)))
        hr = CLR_E_BUSY;
}

void Controller::NativeSetData(CLR_RT_HeapBlock *pMngObj, CLR_RT_TypedArray_UINT32 &param0, HRESULT &hr)
{
    auto pNativeThis = stateMap.find(pMngObj);
    if (pNativeThis == stateMap.end())
    {
        hr = CLR_E_OBJECT_DISPOSED;
        return;
    }
    pNativeThis->second.setData(param0);
}

void Controller::NativeSetUpdateInterval(CLR_RT_HeapBlock *pMngObj, unsigned int param0, HRESULT &hr)
{
    auto pNativeThis = stateMap.find(pMngObj);
    if (pNativeThis == stateMap.end())
    {
        hr = CLR_E_OBJECT_DISPOSED;
        return;
    }
    pNativeThis->second.setUpdateInterval(param0);
}

unsigned int Controller::NativeGetUpdateInterval(CLR_RT_HeapBlock *pMngObj, HRESULT &hr)
{
    auto pNativeThis = stateMap.find(pMngObj);
    if (pNativeThis == stateMap.end())
    {
        hr = CLR_E_OBJECT_DISPOSED;
        return 0;
    }
    return pNativeThis->second.getUpdateInterval();
}

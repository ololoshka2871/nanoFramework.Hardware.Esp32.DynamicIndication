#include "nanoFramework_Hardware_Esp32_DynamicIndication.h"
#include "Controller.h"

#include "DataBus.h"
#include "Selector.h"
#include "ic74141ParralelPolcy.h"

#include <cstring>

using namespace nanoFramework::Hardware::Esp32::DynamicIndication;

// from targets/FreeRTOS_ESP32/ESP32_WROOM_32/nanoCLR/nanoFramework.Hardware.ESP32/nanoFramework_hardware_esp32_native_Hardware_Esp32_HighResTimer.cpp
#define MAX_HRTIMERS 10
extern esp_timer_handle_t hrtimers[MAX_HRTIMERS];

static int FindNextTimerIndex()
{
    for (int index = 0; index < MAX_HRTIMERS; index++)
    {
        if (hrtimers[index] == 0)
            return index;
    }

    return -1;
}

Controller::NativeState::NativeState(
    CLR_RT_TypedArray_INT32 &dataPins,
    CLR_RT_TypedArray_INT32 &selectorPins, int indicators_count)
    : selector(new Selector{std::make_unique<DataBus>(selectorPins)}),
      displayPolicy(new ID1ParralelPolicy{std::make_unique<DataBus>(dataPins), selector->element_count()}),
      m_data(indicators_count),
      update_interval_us(1000),
      indicators_count(indicators_count)
{
    register_timer();
}

Controller::NativeState::~NativeState()
{
    if (timer_idx < 0)
        return;

    if (isEnabled())
        setEnabled(false);

    unregister_timer();
}

bool Controller::NativeState::setEnabled(bool enabled)
{
    if (enabled != selector->isEnabled())
    {
        auto res = enabled ? EnableTimer() : DisableTimer();
        selector->setEnabled(enabled);
        selector->next_element();
        return res;
    }
    return true;
}

void Controller::NativeState::setData(CLR_RT_TypedArray_UINT32 &data)
{
    auto src = data.GetBuffer();
    auto size = std::min(data.GetSize(), m_data.size());
    std::copy(src, src + size, m_data.begin());
}

void Controller::NativeState::setUpdateInterval(uint32_t interval_us)
{
    update_interval_us = interval_us;
    if (isEnabled())
    {
        EnableTimer();
    }
}

bool Controller::NativeState::EnableTimer()
{
    if (isEnabled())
        DisableTimer();

    if (timer_idx < 0)
        return false;

    return esp_timer_start_periodic(hrtimers[timer_idx], update_interval_us) == ESP_OK;
}

bool Controller::NativeState::DisableTimer()
{
    if (timer_idx < 0)
        return false;

    return esp_timer_stop(hrtimers[timer_idx]) == ESP_OK;
}

void Controller::NativeState::timer_cb(void *arg)
{
    auto _this = static_cast<Controller::NativeState *>(arg);
    _this->NextGroup();
}

void Controller::NativeState::NextGroup()
{
    displayPolicy->setData(m_data, selector->next_element());
}

void Controller::NativeState::register_timer()
{
    timer_idx = FindNextTimerIndex();
    if (timer_idx < 0)
        return;

    esp_timer_handle_t newTimerHandle;
    esp_timer_create_args_t timer_args{timer_cb, this, ESP_TIMER_TASK, "Dynamic_updater_timer"};
    esp_err_t err = esp_timer_create(&timer_args, &newTimerHandle);
    if (err != ESP_OK)
        return;

    hrtimers[timer_idx] = newTimerHandle;
}

void Controller::NativeState::unregister_timer()
{
    esp_timer_delete(hrtimers[timer_idx]);
    hrtimers[timer_idx] = 0;
}

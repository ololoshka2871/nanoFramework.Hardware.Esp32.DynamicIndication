#include "ID1ParralelPolcy.h"

using namespace nanoFramework::Hardware::Esp32::DynamicIndication;

ID1ParralelPolicy::ID1ParralelPolicy(std::unique_ptr<IDataBus> &&databus, const uint32_t group_count) 
    : databus(std::move(databus)),
      channels_pre_data_bus(this->databus->width() / bits_pre_channel),
      group_count(group_count)  {}

void ID1ParralelPolicy::setData(const std::vector<uint32_t> &data, uint32_t group) {
    uint32_t v = 0;
    for (uint ch = 0; ch < channels_pre_data_bus; ++ch) {
        auto d = data[group +  ch * group_count];
        v |= d << (bits_pre_channel * ch);
    }
    databus->setData(v);
}
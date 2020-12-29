#include "Processor.h"

Processor::Processor() {

}

Processor::~Processor() {
    for (Command* &i : command) {
        delete i;
        i = nullptr;
    }
}

data_t Processor::get_from_mem(const address_t &addr) const noexcept {
    return memory.get_data(addr);
}

void Processor::push_to_mem(const data_t &data, const address_t &addr) noexcept {
    memory.push(data, addr);
}

void Processor::load_curr_cmd() noexcept {
    cmd = memory.get_data(psw.get_IP()).cmd;
}

void Processor::reset() noexcept {
    psw.reset_flags();
    psw.set_IP(0);
}

void Processor::run() noexcept {
    load_curr_cmd();    // - Загрузка первой команды
    while (cmd.code != stop) {

    }
}
#pragma once

#include "IEventsHandler.hpp"
#include "Logger/ILogger.hpp"
#include "Ports/IBtsPort.hpp"
#include "Ports/IUserPort.hpp"
#include "Ports/ITimerPort.hpp"
#include "SmsRepository.hpp"
#include "Messages/PhoneNumber.hpp"



#include <memory>

namespace ue
{

struct Context
{
    common::ILogger& logger;
    IBtsPort& bts;
    IUserPort& user;
    ITimerPort& timer;
    std::unique_ptr<IEventsHandler> state{};
    SmsRepository smsRepository;
    common::PhoneNumber myPhoneNumber;



    template <typename State, typename ...Arg>
    void setState(Arg&& ...arg)
    {
        state = std::make_unique<State>(*this, std::forward<Arg>(arg)...);
    }
};

}

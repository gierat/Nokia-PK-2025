#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectingState : public BaseState
{
public:
    ConnectingState(Context& context, common::BtsId btsId);
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleTimeout() override;
    void handleDisconnectedFromBts() override;

private:
    common::BtsId btsId;
};

}

#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"


namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}

void ConnectedState::handleDisconnectedFromBts()
{
    context.user.showNotConnected();
    context.setState<NotConnectedState>();
}

}

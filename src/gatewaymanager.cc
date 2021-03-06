#include "gateway.h"

#include <boost/make_shared.hpp>

#include "gatewaymanager.h"
#include "socketgateway.h"

GatewayManager::GatewayManager(const Config &config, command::Channel *commands_channel_in) {
  if (config.gateway.socket) {
    gateways.push_back(boost::make_shared<SocketGateway>(config, commands_channel_in));
  }
}

void GatewayManager::processEvents(const boost::shared_ptr<event::BaseEvent> &event) {
  for (std::vector<boost::shared_ptr<Gateway> >::iterator it = gateways.begin(); it != gateways.end(); ++it) {
    (*it)->processEvent(event);
  }
}

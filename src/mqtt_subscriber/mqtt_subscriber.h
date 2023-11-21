#pragma once

#include <string>

#include "mqtt/async_client.h"

class MqttCallback : public virtual mqtt::callback
{
public:
  void connection_lost(const std::string &cause);
  void message_arrived(mqtt::const_message_ptr msg);
  void delivery_complete(mqtt::delivery_token_ptr token);
  std::string getReceivedMessage() const;
  void clearReceivedMessage();

private:
  std::string received_message;
};

class MqttSubscriber
{
public:
  void run();
  MqttSubscriber();
  mqtt::async_client &get_client();

private:
  mqtt::async_client client;
};

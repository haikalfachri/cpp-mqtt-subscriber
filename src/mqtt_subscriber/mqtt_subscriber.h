#pragma once

#include <string>

#include "mqtt/async_client.h"

class MqttCallback : public virtual mqtt::callback {
  public:
    void connection_lost(const std::string& cause) override
    void message_arrived(mqtt::const_message_ptr msg) override
    void delivery_complete(mqtt::delivery_token_ptr token) override 
    std::string getReceivedMessage() const
    void clearReceivedMessage()

  private:
    std::string received_message;
};

class MqttSubscriber {
  public:
    MqttSubscriber(std::string address, std::string clientId);
    void run(std::string topic);

  private:
    mqtt::async_client client;
    MyCallback callback;
    std::string topic;
};

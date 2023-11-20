#include "mqtt_subscriber.h"

#include <iostream>

#include "mqtt/async_client.h"

void connection_lost(const std::string& cause) override {
    std::cout << "Connection lost: " << cause << std::endl;
}

void message_arrived(mqtt::const_message_ptr msg) override {
    std::cout << "Message received: " << msg->to_string() << std::endl;
    received_message = msg->to_string();
}

void delivery_complete(mqtt::delivery_token_ptr token) override {}

std::string getReceivedMessage() const {
    return received_message;
}

void clearReceivedMessage() {
    received_message.clear();
}

MqttSubscriber::MqttSubscriber(std::string address, std::string clientId) : client(address, clientId) {}

void MqttSubscriber::run(std::string topic) {
    try {
        MqttCallback callback;
        client.set_callback(callback);
        mqtt::const_message_ptr msg;

        connOpts.set_keep_alive_interval(20);
        connOpts.set_clean_session(true);

        MqttCallback callback;
        client.set_callback(callback);
        
        mqtt::token_ptr conn_token = client.connect(conn_opts);
        conn_token->wait();

        if (!conn_token->is_complete()) {
            std::cerr << "Unable to connect to MQTT server" << std::endl;
            return 1;
        }

        std::cout << "Connected to MQTT server" << std::endl;

        client.subscribe(TOPIC, 0);

        std::cout << "Subscribed to topic: " << TOPIC << std::endl;

        while (true) {
            std::string received_msg = callback.getReceivedMessage();
            if (!received_msg.empty()) {
                std::cout << "Received message: " << received_msg << std::endl;
                callback.clearReceivedMessage();
            }
        }
    } catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }
}

#include "mqtt_subscriber.h"

#include <iostream>

#include "../globals/globals.h"
#include "mqtt/async_client.h"

using namespace std;

void MqttCallback::connection_lost(const string &cause) {
    cout << "Connection lost: " << cause << endl;
}

void MqttCallback::message_arrived(mqtt::const_message_ptr msg) {
    if (msg->get_topic() == env_reader->get("TOPIC")) {
        cout << "Message received: " << msg->to_string() << endl;
        received_message = msg->to_string();
    }
}

void MqttCallback::delivery_complete(mqtt::delivery_token_ptr token) {}

string MqttCallback::getReceivedMessage() const {
    return this->received_message;
}

void MqttCallback::clearReceivedMessage() {
    received_message.clear();
}

MqttSubscriber::MqttSubscriber()
    : client("tcp://" + env_reader->get("SERVER_ADDRESS") + ":" + env_reader->get("SERVER_PORT"),
             env_reader->get("CLIENT_ID")) {}

mqtt::async_client &MqttSubscriber::get_client() {
    return this->client;
}

void MqttSubscriber::run() {
    mqtt::async_client &client = this->get_client();

    mqtt::connect_options conn_opts;
    conn_opts.set_keep_alive_interval(20);
    conn_opts.set_clean_session(true);

    MqttCallback callback;
    client.set_callback(callback);
    try {
        mqtt::token_ptr conn_token = client.connect(conn_opts);
        conn_token->wait();

        if (!conn_token->is_complete()) {
            cerr << "Unable to connect to MQTT server" << endl;
            return;
        }

        cout << "Connected to MQTT server" << endl;

        client.subscribe(env_reader->get("TOPIC"), stoi(env_reader->get("QOS")));

        cout << "Subscribed to topic: " << env_reader->get("TOPIC") << endl;

        while (true) {
        }
    } catch (const mqtt::exception &exc) {
        cerr << "Error: " << exc.what() << endl;
        return;
    }
}

#include <iostream>

#include "./globals/globals.h"
#include "./mqtt_subscriber/mqtt_subscriber.h"

using namespace std;

EnvReader *env_reader;
MqttSubscriber *mqtt_subscriber;

int main(int argc, char *argv[]) {
    env_reader = new EnvReader("../../.env");
    mqtt_subscriber = new MqttSubscriber();
    mqtt_subscriber->run();
    return 0;
}
#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

#include <chrono>

enum class TrafficLightPhase {
    red,
    green
};

class Vehicle;

template <class T>
class MessageQueue
{
public:
    void send(T&& phase);
    T receive();

private:
    std::deque<TrafficLightPhase> _queue;
    std::mutex _mutex;
    std::condition_variable _condition;
    
};

class TrafficLight : public TrafficObject
{
public:
    TrafficLight();
    ~TrafficLight();

    void waitForGreen();
    void simulate();

    TrafficLightPhase getCurrentPhase();

private:
    void cycleThroughPhases();

    TrafficLightPhase _currentPhase;
    MessageQueue<TrafficLightPhase> _messageQueue;
    std::condition_variable _condition;
    std::mutex _mutex;
};

#endif
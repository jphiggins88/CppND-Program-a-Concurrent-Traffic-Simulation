#include <iostream>
#include <random>
#include "TrafficLight.h"


unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);
// Specify min/max of 4.0sec/6.0sec
std::uniform_real_distribution<double> distribution(4.0, 6.0);

/* Implementation of class "MessageQueue" */

 
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function.
    std::unique_lock<std::mutex> unique_lock(_mutex);

    _condition.wait(unique_lock, [this] { return !_queue.empty(); });
    T message = std::move(_queue.front());

    _queue.pop_front();

    return message;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
    std::lock_guard<std::mutex> lock(_mutex);

    _queue.clear();
    _queue.emplace_back(std::move(msg));

    _condition.notify_one();
}


/* Implementation of class "TrafficLight" */

 
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

TrafficLight::~TrafficLight() {}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
    while (true) {
        TrafficLightPhase phase = _messageQueue.receive();

        if (phase == TrafficLightPhase::green)
            return;
    }
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // "cycleThroughPhases“ will be started in a thread when "simulate“ is called.
    // Using the thread queue in the base class.
    // "This" allows a thread to be started by any external code that calls simulate().
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    double random_duration_sec = distribution(generator);
    
    // Start timer
    auto start = std::chrono::system_clock::now();
    double elapsed;


    while (true)
    {
        elapsed = (std::chrono::system_clock::now() - start).count();

        if (elapsed >= (random_duration_sec * 1000000000))    // convert random_duration_sec to nanoseconds to match elapsed units
        {
            _currentPhase = (_currentPhase == TrafficLightPhase::green) ? _currentPhase = TrafficLightPhase::red : _currentPhase = TrafficLightPhase::green;

            // Send update message to message queue using move semantics.
            _messageQueue.send(std::move(_currentPhase));

            start = std::chrono::system_clock::now();
            random_duration_sec = distribution(generator); 
        }
        
        // wait 1 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

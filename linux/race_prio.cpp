// compileren met
// c++ -o race_prio race_prio.cpp -lpthread

#include <string>
#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <unistd.h> // for sleep()

using namespace std;

class Car
{
public:
    // Things that pertain to cars
    string name;
    double distPerRev;
    double position;
    bool brake;

    // Things that pertain to real time computer simulations
    int priority;
    pthread_t threadId;

    // Constructor
    Car(string name, double distPerRev, int priority) : name(name), distPerRev(distPerRev), priority(priority)
    {
        position = 0.0;
        brake = true;
        threadId = 0;
    }

    // Drive the car
    static void *drive(void *carrish)
    {                              // Thread function MUST be static and have void parameter
        Car *car = (Car *)carrish; // Convert void to actual type
        while (!car->brake)
        {
            car->position += car->distPerRev; // Update position with distance per revolution
        }
        return NULL;
    }

    // Start the car
    void start()
    {
        pthread_attr_t threadAttributes;
        struct sched_param schedulingParameters;

        pthread_attr_init(&threadAttributes); // Initialize thread attributes

        // Set round robin scheduling
        pthread_attr_setschedpolicy(&threadAttributes, SCHED_RR);

        // Get current scheduling parameters from thread attributes
        pthread_attr_getschedparam(&threadAttributes, &schedulingParameters);

        // Modify priority field of scheduling parameters
        schedulingParameters.sched_priority = priority; // replace xxx with desired priority

        // Store new scheduling parameters in thread attributes
        pthread_attr_setschedparam(&threadAttributes, &schedulingParameters);

        brake = false;
        pthread_create(&threadId, &threadAttributes, drive, this); // Create thread with right priority
    };

    // Stop the car
    void finish()
    {
        brake = true;
        pthread_join(threadId, NULL);
    }
};

// ============ Create two cars and have them race against each other

int main()
{
    // Get min and max priority values
    int schedMin = sched_get_priority_min(SCHED_RR);
    int schedMax = sched_get_priority_max(SCHED_RR);
    cout << "min: " << schedMin << endl
         << "max: " << schedMax << endl;

    // Make two cars
    Car electricCar("Tesla", 0.001, schedMin);    // Minimum priority
    Car combustionCar("Jaguar", 0.001, schedMax); // Maximum priority

    // Start their threads
    electricCar.start();
    combustionCar.start();

    cout << "Race started" << endl;

    // Report how they're doing
    cout << fixed;
    cout.precision(1);
    for (int sampleIndex = 0; sampleIndex < 10; sampleIndex++)
    {
        cout << "Index: " << sampleIndex << '\t' << electricCar.name << " pos: " << electricCar.position << '\t' << combustionCar.name << " pos: " << combustionCar.position << endl;
        sleep(1);
    }

    // Wait for their threads to end
    electricCar.finish();
    combustionCar.finish();

    cout << "Race finished. " << (electricCar.position > combustionCar.position ? electricCar.name : combustionCar.name) << " wins!" << endl;

    return 0;
}
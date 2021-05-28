//
//  main.cpp
//  laylaylom
//
//  Created by Berkin Divrikli on 27.05.2021.
//
/*
                                                           Homework7
 Name:              Berkin
 Surname:           Divrikli
 ID:                28004
 
 
 Purpose: Purpose of this homework is to learn the basics of threads. Also manipulating threads. I needed to take some precautions on multitreading objects, which might occur at the same time.
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "HW7DynIntQueue.h"

using namespace std;

//declaring the random function (copy paste from pdf)
int random_range(const int & min, const int & max) {
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

mutex CoutMutex, fil, pack;  // declaring mutexes one for each queues and one for printing statements.

int total, filint, pacint; //global variable to count the loops.

//this function is made to assign the tasks of producer thread. Loop turns according to the input.
void producer(HW7DynIntQueue & filling, int min, int max){

    for (int id = 1; id < total + 1; id++) {
        int time = random_range(min, max);
        this_thread::sleep_for (chrono::seconds(time));
        fil.lock();
        filling.enqueue(id);
        fil.unlock();
        CoutMutex.lock();
        localtime_s(ptm, &tt);
        cout << "Producer has enqueued a new box "<< id << " to filling queue (filling queue size is "<< filling.getCurrentSize() << "): "<< put_time(ptm,"%X") << endl;
        CoutMutex.unlock();
    }
}

//this function is made to assign the tasks of filler threads. first of all it checks if the producer filled the filling queue with an object if it does. program firstly dequeues the item from filling list. and then fills the packing list.
void filler(HW7DynIntQueue & filling, HW7DynIntQueue & packaging, int min, int max, int workerno){
    time_t tt;
    struct tm *ptm = new struct tm;
    while (filint != 0) {
        int id;
        fil.lock();
        bool checkONe;
        if (filling.isEmpty() == false) {
            filling.dequeue(id);
            filint--;
            checkONe == true;
        }
        fil.unlock();
        if (checkONe == true) {
            CoutMutex.lock();
            tt = chrono::system_clock::to_time_t (chrono::system_clock::now());
            cout << "Filler " << workerno << " started filling the box " << id << " (filling queue size is " << filling.getCurrentSize() << "): " << put_time(ptm,"%X") << endl;
            CoutMutex.unlock();
            int time = random_range(min, max);
            this_thread::sleep_for (chrono::seconds(time));
            CoutMutex.lock();
            tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
            localtime_s(ptm, &tt);
            cout << "Filler " << workerno << " started filling the box " << id << " (filling queue size is " << filling.getCurrentSize() << "): " << put_time(ptm,"%X") << endl;
            CoutMutex.unlock();
            pack.lock();
            packaging.enqueue(id);
            pack.unlock();
            CoutMutex.lock();
            tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
            localtime_s(ptm, &tt);
            cout << "Packager " << workerno << " started packaging the box " << id << " (packaging queue size is " << packaging.getCurrentSize() << "): " << put_time(ptm,"%X") << endl;
            CoutMutex.unlock();
        }
        
    }

}



//this function is made to assign the tasks of packer threads. first of all it checks if the filler filled the packing queue with an object if it does, program firstly dequeues the item from filling list. and then fills the packing list with that item.
void packer(HW7DynIntQueue & packaging, int min, int max, int workerno){
    time_t tt;
    struct tm *ptm = new struct tm;
    while (pacint != 0) {
        int id;
        bool checkTwo;
        pack.lock();
        if (packaging.isEmpty() == false) {
            packaging.dequeue(id);
            checkTwo = true;
            pacint--;
            
        }
        pack.unlock();
        if (checkTwo == true) {
            CoutMutex.lock();
            tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
            localtime_s(ptm, &tt);
            cout << "Packager " << workerno << " started packaging the box " << id << " (packaging queue size is " << packaging.getCurrentSize() << "): " << put_time(ptm,"%X") << endl;
            CoutMutex.unlock();
            int time = random_range(min, max);
            this_thread::sleep_for (chrono::seconds(time));
            CoutMutex.lock();
            tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
            localtime_s(ptm, &tt);
            cout << "Packager " << workerno << " finished packaging the box " << id << ": " << put_time(ptm,"%X") << endl;
            CoutMutex.unlock();
        }
    }
}


int main() {
    int total_box_count, min_production, max_production, min_filling_time, max_filling_time, min_packaging_time, max_packaging_time;
    
//    getting the inputs
    cout << "Please enter the total number of items: ";
    cin >> total_box_count;
    cout << "Please enter the min-max waiting time range of producer:" << endl;
    cout << "Min: ";
    cin >> min_production;
    cout << "Max: ";
    cin >> max_production;
    cout << "Please enter the min-max waiting time range of filler workers:" << endl;
    cout << "Min: ";
    cin >> min_filling_time;
    cout << "Max: ";
    cin >> max_filling_time;
    cout << "Please enter the min-max waiting time range of packager workers:" << endl;
    cout << "Min: ";
    cin >> min_packaging_time;
    cout << "Max: ";
    cin >> max_packaging_time;
    
    total = total_box_count;
    filint = total_box_count;
    pacint = total_box_count;
    
    HW7DynIntQueue filling, packaging;
    
//  assigning the time function
    time_t tt;
    struct tm *ptm = new struct tm;
    tt = chrono::system_clock::to_time_t (chrono::system_clock::now());
    localtime_s(ptm, &tt);
    cout << "Simulation starts " << put_time(ptm,"%X") << endl;
    
    thread production;
    thread fillersOne, fillersTwo;
    thread packerOne, packerTwo;
    
    
    production = thread(&producer, ref(filling), min_production, max_production);
    fillersOne = thread(&filler, ref(filling), ref(packaging), min_filling_time, max_filling_time, 1);
    fillersTwo = thread(&filler, ref(filling), ref(packaging), min_filling_time, max_filling_time, 2);
    packerOne = thread(&packer,ref(packaging), min_packaging_time, max_packaging_time, 1);
    packerTwo = thread(&packer,ref(packaging), min_packaging_time, max_packaging_time, 2);
    
//    assigning the threads
    production.join();
    fillersOne.join();
    fillersTwo.join();
    packerOne.join();
    packerTwo.join();
    
    
    tt = chrono::system_clock::to_time_t (chrono::system_clock::now());
    localtime_s(ptm, &tt);
    cout << "End of the simulation ends: " << put_time(ptm,"%X") << endl;
    
    return 0;
}

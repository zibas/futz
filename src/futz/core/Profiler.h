#ifndef PROFILER_H_
#define PROFILER_H_
#include <string>
#include <stack>
#include <map>

using namespace std;

    class Profiler{
        public:
            bool enabled;
            stack<string> labels;
            stack<string> finishedLabels;
            map<string, double> durations;
            map<string, double> starts;
            map<string, int> counts;


        Profiler(){
            enabled = false;
        }
        void Start(string);
        void End();
        void Print();
    };

#endif

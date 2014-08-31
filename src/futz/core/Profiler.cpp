#include "../Futz.h"
#include <iostream>

void Profiler::Start(string label){
    if(enabled){
        Futz* futz = Futz::Instance();
        labels.push(label);
        starts[label] = futz->time.InstantTotalElapsedSeconds();
        if(counts.find(label) == counts.end()){
            counts[label] = 1;
        } else {
            counts[label]++;
        }
    }
}

void Profiler::End(){
	if (enabled){
		Futz* futz = Futz::Instance();
		if (!labels.empty()){
			string label = labels.top();

			if (durations.find(label) == durations.end()){
				durations[label] = futz->time.InstantTotalElapsedSeconds() - starts[label];
				finishedLabels.push(label);
			}
			else {
				durations[label] += futz->time.InstantTotalElapsedSeconds() - starts[label];
			}

			labels.pop();
		}
    }
}


void Profiler::Print(){
    if(enabled){
        string label;
        while(!finishedLabels.empty()){
            label = finishedLabels.top();
            finishedLabels.pop();

            printf("%s:\n\tavg:%f\ttot:%f\tcount:%d\n",label.c_str(),durations[label]/counts[label],durations[label],counts[label]);
            durations.erase(label);
            counts.erase(label);
    }
}
}

#include "Futz.h"
#include "TimeKeeper.h"
#include <stdio.h>

#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;
TimeKeeper::TimeKeeper() {
	statisticsPeriod = 5;
	nextStatisticsDue = statisticsPeriod;
	fps = ups = 0;
	frames  = 0;
	updates = 0;
	delta = 0;
#ifdef _WIN32
	start = clock();
	last = clock();
#else
	totalElapsedSeconds = 0;
	gettimeofday(&start, NULL);
	gettimeofday(&last, NULL);
#endif
}


TimeKeeper::~TimeKeeper() {}

void TimeKeeper::UpdateTotal(){
#ifdef _WIN32
	lastTotalElapsedSeconds = totalElapsedSeconds;
	totalElapsedSeconds = ((double)(last - start)) / CLOCKS_PER_SEC;
	last = clock();
#else
	struct timeval now;
	long seconds, useconds;    
	lastTotalElapsedSeconds = totalElapsedSeconds;
	gettimeofday(&now, NULL);
	seconds  = now.tv_sec  - start.tv_sec;
	useconds = now.tv_usec - start.tv_usec;
	totalElapsedSeconds = (((seconds) * 1000 + useconds/1000.0) + 0.5)/1000;
	gettimeofday(&last, NULL);
#endif
}


double TimeKeeper::InstantTotalElapsedSeconds(){
#ifdef _WIN32
    //TODO: UNTESTED
	return (((double)(clock() - start)) / CLOCKS_PER_SEC);
#else
	struct timeval now;
	long seconds, useconds;    
	gettimeofday(&now, NULL);
	seconds  = now.tv_sec  - start.tv_sec;
	useconds = now.tv_usec - start.tv_usec;
	return ((((seconds) * 1000 + useconds/1000.0) + 0.5)/1000);
#endif

}

void TimeKeeper::UpdateLoop(){
    UpdateTotal();

	delta = totalElapsedSeconds - lastTotalElapsedSeconds;

	if(totalElapsedSeconds >= nextStatisticsDue){
		double period = statisticsPeriod + (totalElapsedSeconds - nextStatisticsDue);
		fps = frames/period;
		ups = updates/period;
		Print();
		frames = updates = 0;
		nextStatisticsDue += statisticsPeriod;
	}

	updates++;
}

void TimeKeeper::RenderLoop(){
	frames++;
}

void TimeKeeper::Print(){
	Futz* futz = Futz::Instance();
	stringstream  stats;
	stats <<  "FPS: " << setprecision(5) << fps;
	stats <<  "\tUPS: " << setprecision(5) << ups;
	stats <<  "\tPolys: " << futz->scene.PolyCount();
	stats <<  "\tObjects: " << futz->scene.NodeCount();
	stats <<  "\tTotal: " << totalElapsedSeconds;
	stats <<  "\tDelta: " << delta;
//	stats <<  "\tTimerStack: " << timerStack.size();
	Futz::Log(stats.str());
 //   for ( timerMapIterator=timerMap.begin() ; timerMapIterator != timerMap.end(); timerMapIterator++ )
 //            cout << (*timerMapIterator).first << " => " << (*timerMapIterator).second << endl;
//	printf("Total Seconds: %f\n",totalElapsedSeconds);
//	printf("Elapsed Seconds: %f\n",delta);
//	
    futz->profiler.Print();

}


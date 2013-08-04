#ifndef TIMEKEEPER_H_
#define TIMEKEEPER_H_
#ifdef _WIN32 
#include <time.h>
#else
#include <sys/time.h>
#endif 
#include <stdio.h>

using namespace std;
class TimeKeeper {
private:
	double statisticsPeriod;
	double nextStatisticsDue; 

	double fps;
	double ups;

	int frames;
	int updates;



#ifdef _WIN32
	clock_t start;
	clock_t last;
#else
	timeval start; 
	timeval last; 
#endif
	
public:
	double lastTotalElapsedSeconds; 
	double totalElapsedSeconds; 
	double delta; //seconds since last update

	TimeKeeper();
    void UpdateTotal();
	void UpdateLoop();
	void RenderLoop();
	void Print();
    double InstantTotalElapsedSeconds();
	virtual ~TimeKeeper();

};

#endif /* TIMEKEEPER_H_ */

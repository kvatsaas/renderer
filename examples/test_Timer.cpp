/*
 *  test_Timer.cpp
 *
 *  Created by Pete Willemsen on 10/6/09.
 *  Copyright 2009 Department of Computer Science, University of Minnesota-Duluth. All rights reserved.
 *
 * This file is part of SIVE Lab library (libsive).
 *
 */

#include <io.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <iostream>
#include <cmath>
#include <vector>

#include "Random.h"
#include "Timer.h"

void localSleepFunction(long stime)
{
#ifdef WIN32
  // From http://filipivianna.blogspot.com/2010/07/usleep-on-windows-win32.html
  __int64 time1 = 0, time2 = 0, sysFreq = 0;

  QueryPerformanceCounter((LARGE_INTEGER *)&time1);
  QueryPerformanceFrequency((LARGE_INTEGER *)&sysFreq);
  do{
    QueryPerformanceCounter((LARGE_INTEGER *)&time2);
    
    //  }while((((time2-time1)*1.0)/sysFreq)<waitTime);
  }while( (time2-time1) < stime);
#else
  usleep( stime );
#endif
}


using namespace sivelab;

int main(int argc, char *argv[])
{
  Random prng;

  std::vector<long> sleepTimes;

  for (int i=1; i<=10; i++)
    sleepTimes.push_back( i*10000 );

  for (int i=0; i<10; i++)
    sleepTimes.push_back( (int)floor(prng.uniform() * 10000) );

  long avgDiff = 0;

  Timer t0;
  for (unsigned int i=0; i<sleepTimes.size(); i++)
    {
      Timer_t startTime = t0.tic();
      localSleepFunction( sleepTimes[i] );
      Timer_t endTime = t0.tic();
      Timer_t diffTime = t0.deltau(startTime, endTime);
      std::cout << "Low-res timer result after usleeping for " << sleepTimes[i] << " microseconds --> result = " << diffTime << " us [diff = " << diffTime - sleepTimes[i] << "]" << std::endl;
      avgDiff += (diffTime - sleepTimes[i]);
    }
  avgDiff /= sleepTimes.size();
  std::cout << "Average difference between specified usleep and measured time: " << avgDiff << " us (" << avgDiff/1000000.0 << " s)" << std::endl << std::endl;
  if (avgDiff > 150)
    std::cerr << "FAILURE on the Timer!  Differences are too great!" << std::endl;

  avgDiff = 0;
  Timer t1(true);
  for (unsigned int i=0; i<sleepTimes.size(); i++)
    {
      Timer_t startTime = t1.tic();
      localSleepFunction( sleepTimes[i] );
      Timer_t endTime = t1.tic();
      Timer_t diffTime = t1.deltau(startTime, endTime);
      std::cout << "High-res timer result after usleeping for " << sleepTimes[i] << " microseconds --> result = " << diffTime << " us [diff = " << diffTime - sleepTimes[i] << "]" << std::endl;
      avgDiff += (diffTime - sleepTimes[i]);
    }
  avgDiff /= sleepTimes.size();
  std::cout << "Average difference between specified usleep and measured time: " << avgDiff << " us (" << avgDiff/1000000.0 << " s)" << std::endl << std::endl;
  if (avgDiff > 150)
    std::cerr << "FAILURE on the Timer!  Differences are too great!" << std::endl;
}

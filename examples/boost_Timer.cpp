/*
 *  test_Timer.cpp
 *
 *  Created by Pete Willemsen on 10/6/09.
 *  Copyright 2009 Department of Computer Science, University of Minnesota-Duluth. All rights reserved.
 *
 * This file is part of SIVE Lab library (libsive).
 *
 */

#include <iostream>
#include <cmath>
#include <vector>

#include <boost/thread/thread.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

#include "Random.h"

int main(int argc, char *argv[])
{
  boost::posix_time::ptime t(boost::posix_time::microsec_clock::local_time());
  std::cout << "ptime: " << t << std::endl;

  sivelab::Random prng;

  std::vector<long> sleepTimes;

  for (int i=1; i<=10; i++)
    sleepTimes.push_back( i*100 );

  for (int i=0; i<10; i++)
    sleepTimes.push_back( (int)floor(prng.uniform() * 100) );

  long avgDiff = 0;
  for (unsigned int i=0; i<sleepTimes.size(); i++)
    {
      boost::posix_time::ptime t1 = boost::posix_time::microsec_clock::local_time();
      boost::this_thread::sleep(boost::posix_time::microseconds( sleepTimes[i] ));
      boost::posix_time::ptime t2 = boost::posix_time::microsec_clock::local_time();

      boost::posix_time::time_duration diff = t2 - t1;

      std::cout << "Timer result after usleeping for " << sleepTimes[i] << " microseconds --> result = " 
		<< diff.total_milliseconds() << " us [diff = " << diff.total_milliseconds() - sleepTimes[i] << "]" << std::endl;
      avgDiff += (diff.total_milliseconds() - sleepTimes[i]);
    }

  avgDiff /= sleepTimes.size();
  std::cout << "Average difference between specified usleep and measured time: " << avgDiff << " us" << std::endl;

  exit(EXIT_SUCCESS);
}

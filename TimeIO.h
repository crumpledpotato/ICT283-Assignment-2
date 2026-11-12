#ifndef TIMEIO_H
#define TIMEIO_H

#include "Time.h"

/**
 * @author  Marcus
 * @version 1.0
 * @date 07/10/2026
 */

#include <iostream>

using namespace std;

/**
 * @brief Displays a Time object
 *
 * @param os The output stream
 * @param time The Time object to display
 * @return The output stream
 */
ostream& operator << (ostream& os, const Time & time);

#endif

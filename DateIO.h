#ifndef DATEIO_H
#define DATEIO_H

#include "Date.h"

/**
 * @author  Marcus
 * @version 1.0
 * @date 28/10/2026
 */

#include <iostream>

/**
 * @brief Displays a Date object
 *
 * @param os The output stream
 * @param date The Date object to display
 * @return The output stream
 */
std::ostream& operator << (std::ostream& os, const Date & date);

#endif

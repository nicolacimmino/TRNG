
// Probo is a minimal unit test framework for Ardiuno projects. Providing boilerplate code
// for basic assertions to build your tests upon.
// You will only need to include this header file in your tests project.
//
//  Copyright (C) 2019 Nicola Cimmino
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef __PROBO_H__
#define __PROBO_H__

Stream *proboOutputStream = NULL;

bool proboHaltOnError;

/**
 * Initialise Probo.
 * We provide here a reference to an output stream (e.g. Serial) and some basic config.
 */
void proboInit(Stream *outputStream, bool haltOnError = true)
{
    proboOutputStream = outputStream;
    proboHaltOnError = haltOnError;
}

/**
 * Test failure.
 */
void proboFailed()
{
    proboOutputStream->println("ERROR");
    while (proboHaltOnError)
    {
        delay(1000);
    }
}

/**
 * Test success.
 */
void proboPassed()
{
    proboOutputStream->println("OK");
}

/**
 * Print an info message.
 */
void proboInfo(const char *message)
{
    proboOutputStream->println(message);
}

/**
 * Assert condition to be true.
 */
void proboAssert(bool condition, const char *message)
{
    if (!condition)
    {
        proboOutputStream->print("Failed asserting: ");
        proboOutputStream->println(message);
        proboFailed();
    }

    proboOutputStream->print(message);
    proboOutputStream->println(" OK");
}

/**
 * Get a very simple checksum (sum of the ASCIIs) of the given string.
 * This is used proboAssertMaxIterations to keep track of iterations
 * for the same message.
 * Note: this is a bit weak as string like "Test 12" and "Test 21"
 * will have the same checksum. But then, what are the chances of
 * "Test 12" and "Test 21" being run one after the other and both
 * assert on maxIterations....
 */
uint32_t getStringSimpleChecksum(const char *message)
{
    uint16_t ix = 0;
    uint32_t checksum = 0;
    while (message[ix] != 0)
    {
        checksum += message[ix];
        ix++;
    }

    return checksum;
}

/**
 * Assert that we should call this assert maximum maxIterations times.
 * Calling this function with a new message resets the counter.
 */
void proboAssertMaxIterations(unsigned int maxIterations, const char *message, bool quiet = false)
{
    static uint32_t lastMessageChecksum = 0;
    static unsigned int iterations = 0;

    if (getStringSimpleChecksum(message) != lastMessageChecksum)
    {
        iterations = 0;
        lastMessageChecksum = getStringSimpleChecksum(message);
    }

    iterations++;

    if (!quiet)
    {
        proboOutputStream->print(message);
        proboOutputStream->print(" ");
        proboOutputStream->print(iterations);
        proboOutputStream->print("/");
        proboOutputStream->println(maxIterations);
    }

    if (iterations > maxIterations)
    {
        proboOutputStream->print("Failed asserting max iterations: ");
        proboOutputStream->println(message);
        proboFailed();
    }
}

#endif
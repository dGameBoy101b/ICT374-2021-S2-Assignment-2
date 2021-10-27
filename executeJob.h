/* File: executeJob.h
 * Date: 16 October 2021
 * Author: Orlando Molina Santos, ID: 33302151
 * Purpose: Provides functions to execute jobs from a command line.
 */

#include "job.h"

/* Executes a job from the command line.
 * job: Job struct representing the job to be executed.
 * Returns int: 0 if error, 1 on success
 */
int ExecuteJob(const struct Job *job);

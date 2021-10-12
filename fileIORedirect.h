/* File: fileIORedirect.h
 * Author: Orlando Molina Santos, ID: 33302151
 * Date: 28 September 2021
 * Purpose: Provides functions to redirect input and output.
 */

/* Redirects the input of a process from stdin.
 * inputFileName: the name of the input file to redirect to.
 * Returns: 0 if error, 1 on success
 */
int RedirectStdin(const char *inputFileName);

/* Redirects the output of a process from stdout.
 * outputFileName: the name of the output file to redirect to.
 * Returns: 0 if error, 1 on success.
 */
int RedirectStdout(const char *outputFileName);


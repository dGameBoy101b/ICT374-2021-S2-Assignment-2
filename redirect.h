/* File: redirect.h
 * Author: Orlando Molina Santos
 * Date: 28 September 2021
 * Purpse: Provides functions to redirect input and output.
 */

/* Redirects the input of a process from stdin.
 * inputFileName: the name of the input file to redirect to.
 * Returns: -1 if error, otherwise the file descriptor of the new input.
 */
int RedirectInput(char *inputFileName);

/* Redirects the output of a process from stdout.
 * outputFileName: the name of the outptu file to redirect to.
 * Returns: -1 if error, otherwise the file descriptor of the new output.
 */
int RedirectOutput(char *outputFileName);


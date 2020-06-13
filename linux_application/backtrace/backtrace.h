#define _GNU_SOURCE

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <dlfcn.h>
#include <gnu/lib-names.h>

#define STACK_FRAMES_BUFFERSIZE (int)128

static void * STACK_FRAMES_BUFFER[128];
static void * OFFSET_FRAMES_BUFFER[128];
static char   EXECUTION_FILENAME[32] = "Mainboard_Software";


/*-----------------------------------------------------------------------------------*/
/*
 * Function will attempt to backtrace the signal cause by collecting the last called addresses.
 * The addresses will then be translated into readable stings by addr2line
 */

static void PrintBacktrace(void)
{
    const char errorString[] = "Offset cannot be resolved: No offset present?\n\0?";
    char       printArray[100] = {0};
    size_t     bufferEntries;
    char **    stackFrameStrings;
    size_t     frameIterator;

    //backtrace the last calls
    bufferEntries = backtrace(STACK_FRAMES_BUFFER, STACK_FRAMES_BUFFERSIZE);
    stackFrameStrings = backtrace_symbols(STACK_FRAMES_BUFFER, (int)bufferEntries);

    //print the number of obtained frames
    sprintf(printArray,"\nObtained %zd stack frames.\n\r", bufferEntries);
    (void)write(STDERR_FILENO, printArray, strlen(printArray));

    //iterate over addresses and print the stings
    for (frameIterator = 0; frameIterator < bufferEntries; frameIterator++) {
#if __x86_64__
        //calculate the offset on x86_64 and print the file and line number with addr2line
        OFFSET_FRAMES_BUFFER[frameIterator] = CalculateOffset(stackFrameStrings[frameIterator]);
        if(OFFSET_FRAMES_BUFFER[frameIterator] == NULL) {
            (void)write(STDERR_FILENO, errorString, strlen(errorString));
        } else {
            Addr2LinePrint(OFFSET_FRAMES_BUFFER[frameIterator]);
        }
#endif
#if __arm__
        //the address itself can be used on ARM for a call to addr2line
        Addr2LinePrint(STACK_FRAMES_BUFFER[frameIterator]);
#endif
    }
    free (stackFrameStrings);
}

/*-----------------------------------------------------------------------------------*/
/*
 * Use add2line on the obtained addresses to get a readable sting
 */
static void Addr2LinePrint(void const * const addr)
{
    char addr2lineCmd[512] = {0};

    //have addr2line map the address to the relent line in the code
    (void)sprintf(addr2lineCmd,"addr2line -C -i -f -p -s -a -e ./%s %p ", EXECUTION_FILENAME, addr);

    //This will print a nicely formatted string specifying the function and source line of the address
    (void)system(addr2lineCmd);
}
/*-----------------------------------------------------------------------------------*/
/*
 * Pass a string which was returned by a call to backtrace_symbols() to get the total offset
 * which might be decoded as (symbol + offset). This function will return the calculated offset
 * as void pointer, this pointer can be passed to addr2line in a following call.
 */
void *  CalculateOffset(char * stackFrameString)
{
    void *     objectFile;
    void *     address;
    void *     offset = NULL;
    char       symbolString[75] = {'\0'};
    char       offsetString[25] = {'\0'};
    char *      dlErrorSting;
    int        checkSscanf = EOF;
    int        checkDladdr = 0;
    Dl_info    symbolInformation;

    //parse the string obtained by backtrace_symbols() to get the symbol and offset
    parseStrings(stackFrameString, symbolString, offsetString);

    //convert the offset from a string to a pointer
    checkSscanf = sscanf(offsetString, "%p",&offset);

    //check if a symbol string was created,yes, convert symbol string to offset
    if(symbolString[0] != '\0') {
        //open the object (if NULL the executable itself)
        objectFile = dlopen(NULL, RTLD_LAZY);
        //check for error
        if(!objectFile) {
            dlErrorSting = dlerror();
            (void)write(STDERR_FILENO, dlErrorSting, strlen(dlErrorSting));
        }
        //convert sting to a address
        address = dlsym(objectFile, symbolString);
        //check for error
        if(address == NULL) {
            dlErrorSting = dlerror();
            (void)write(STDERR_FILENO, dlErrorSting, strlen(dlErrorSting));
        }
        //extract the symbolic information pointed by address
        checkDladdr = dladdr(address, &symbolInformation);

        if(checkDladdr != 0) {
            //calculate total offset of the symbol
            offset = (symbolInformation.dli_saddr - symbolInformation.dli_fbase) + offset;
            //close the object
            dlclose(objectFile);
        } else {
            dlErrorSting = dlerror();
            (void)write(STDERR_FILENO, dlErrorSting, strlen(dlErrorSting));
        }
    }

    return checkSscanf != EOF ? offset : NULL;
}
/*-----------------------------------------------------------------------------------*/
/*
 * Parse a string which was returned from backtrace_symbols() to get the symbol name
 * and the offset.
 */

void parseStrings(char * stackFrameString, char * symbolString, char * offsetString)
{
    char *        symbolStart = NULL;
    char *        offsetStart = NULL;
    char *        offsetEnd = NULL;
    unsigned char stringIterator = 0;

    //iterate over the string and search for special characters
    for(char * iteratorPointer = stackFrameString; *iteratorPointer; iteratorPointer++) {
        //The '(' char indicates the beginning of the symbol
        if(*iteratorPointer == '(') {
            symbolStart = iteratorPointer;
        }
        //The '+' char indicates the beginning of the offset
        else if(*iteratorPointer == '+') {
            offsetStart = iteratorPointer;
        }
        //The ')' char indicates the end of the offset
        else if(*iteratorPointer == ')') {
            offsetEnd = iteratorPointer;
        }

    }
    //Copy the symbol string into an array pointed by symbolString
    for(char * symbolPointer = symbolStart+1; symbolPointer != offsetStart; symbolPointer++) {
        symbolString[stringIterator] = *symbolPointer;
        ++stringIterator;
    }
    //Reset string iterator for the new array which will be filled
    stringIterator = 0;
    //Copy the offset string into an array pointed by offsetString
    for(char * offsetPointer = offsetStart+1; offsetPointer != offsetEnd; offsetPointer++) {
        offsetString[stringIterator] = *offsetPointer;
        ++stringIterator;
    }
}
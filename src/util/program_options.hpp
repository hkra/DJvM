#pragma once

#include <memory>

/*
 * A singleton class used for accessing program options passed via the command
 * line. It should be initialzied only once using the public static method 
 * <code>parse()</code>.
 */
class ProgramOptions
{
public:
    
    /*
     * No copy
     */
    ProgramOptions(const ProgramOptions &) = delete;
    
    /*
     * No copy
     */
    ProgramOptions & operator=(const ProgramOptions &) = delete;
    
    /*
     * Parse command line arguments and store environment variables. Call only
     * once at the beginning of the program, passing in args from <code>main()</code>.
     */
    static void parse(int argc, char * argv, char * env[]);
    
private:
    
    ProgramOptions();
};
#pragma once

#include <stdio.h>


enum LogPriorityLevel { TRACE, DEBUG, INFO, WARN, ERROR, FATAL  };


class Logger{

    private:
        static LogPriorityLevel LoggingPriority;


    public:

        static void setLoggingPriority(LogPriorityLevel newPriority){
            LoggingPriority = newPriority;
        }

        //Logging for TRACE level priority, takes a format string and a variable number of args using variadic template
        template<typename... Args>
        static void Trace(const char* message, Args... args){
            
            if(LoggingPriority <= TRACE){
                printf("[TRACE]:\t");
                printf(message, args);
                printf('\n');
            }

        }

                
        //Logging for DEBUG level priority, takes a format string and a variable number of args using variadic template
        template<typename... Args>
        static void Debug(const char* message, Args... args){
            
            if(LoggingPriority <= DEBUG){
                printf("[DEBUG]:\t");
                printf(message, args);
                printf('\n');
            }

        }




    

};
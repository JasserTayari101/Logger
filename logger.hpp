#pragma once

#include <stdio.h>

//used for log timestamps
#include <ctime>

enum LogPriorityLevel { TRACE, DEBUG, INFO, WARN, ERROR, FATAL  };


class Logger{

    private:
        static LogPriorityLevel LoggingPriority;
        
        static const char* filepath;
        static FILE* file;

    public:

        static void SetLoggingPriority(LogPriorityLevel newPriority){
            LoggingPriority = newPriority;
        }

        //used when user enable file logging
        static void EnableFileOutput(){

            filepath = "logs/log.txt";  

            enable_file_output();

        }

        static void EnableFileOutput(const char* newFilePath){

            filepath = newFilePath;

            enable_file_output();

        }


        static void DisableFileOutput(){
            free_file();
        }

        //Logging for TRACE level priority, takes a format string and a variable number of args using variadic template
        template<typename... Args>
        static void Trace(const char* message, Args... args){
            log("TRACE",TRACE, message, args...);
        }

                
        //Logging for DEBUG level priority, takes a format string and a variable number of args using variadic template
        template<typename... Args>
        static void Debug(const char* message, Args... args){
            log("DEBUG", DEBUG, message, args...);    
        }

    private:
        
        template<typename... Args>
        static void log(const char* logPrefix, LogPriorityLevel priority, const char* message, Args... args){
            if(LoggingPriority <= priority){
                //get current time and format it

                std::time_t current_time = std::time(0);
                std::tm* timestamp = std::localtime(&current_time);

                char buffer[80];
                strftime(buffer,80,"%c", timestamp);


                //log to console
                printf("%s\t", buffer);
                printf("[%s]\t", logPrefix);
                printf(message, args...);
                printf("\n");

                //log to file if enabled

                if(file){
                    fprintf(file, "%s\t", buffer);
                    fprintf(file,"[%s]\t", logPrefix);
                    fprintf(file,message, args...);
                    fprintf(file,"\n");
                }

            }
        }


        static void enable_file_output(){
            if(file!=0)
                fclose(file);

            file = fopen(filepath, "a");

            if(file == 0)
                printf("Logger: Failed top open file at %s\n", filepath);

        }

        static void free_file(){
            fclose(file);

            file = 0;
        }


};


LogPriorityLevel Logger::LoggingPriority = TRACE;

const char* Logger::filepath = 0;

FILE* Logger::file = 0;
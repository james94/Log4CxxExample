#include <iostream>
#include <thread>
#include <unistd.h>
#include <memory>

// include log4cxx header files.
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"

using namespace log4cxx;
using namespace log4cxx::helpers;

// Log4cxx conversion pattern "%-4r [%t] %-5p %c %x - %m%n" will output:
// 176 [main] INFO org.foo.Bar - Located nearest gas station.

class ThreadManager {
public:
    ThreadManager() {}
    ~ThreadManager();

    void task1();
    void task2();
    void start(std::string taskName);

private:
    std::vector<std::thread*> threadPtrVec;
    log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("TestLog4Cxx");
};

ThreadManager::~ThreadManager() {
    for(int i = 0; i < threadPtrVec.size(); i++) {
        delete threadPtrVec[i];
    }
}

void ThreadManager::task1() {

    while(true) {
        LOG4CXX_ERROR(logger, "Logging from task1() " << "in Huntsville, AL");
        usleep(1000000);
    }
}

void ThreadManager::task2() {

    while(true) {
        LOG4CXX_DEBUG(logger, "Logging from task2() " << "in Huntsville, AL");
        usleep(1000000);
    }
}

void ThreadManager::start(std::string taskName) {
    std::thread* thread;
    if(taskName == "task1") {
        thread = new std::thread( [this]{ task1(); } );
    }
    else if(taskName == "task2") {
        thread = new std::thread( [this]{ task2(); } );
    }
    thread->detach(); // allows thread to execute independently from the calling thread
    threadPtrVec.push_back(thread);
}

std::unique_ptr<ThreadManager> threadManager;

int main(int argc, char **argv) {
    // Set up a simple configuration that logs on the console
    int result = EXIT_SUCCESS;
    try {

        if(argc > 1) {
            PropertyConfigurator::configure(argv[1]);
        }
        else {
            BasicConfigurator::configure();
        }

        // Calling getLogger with same name always returns a reference to same logger obj
        log4cxx::LoggerPtr logger = log4cxx::Logger::getLogger("TestLog4Cxx");

        LOG4CXX_INFO(logger, "Entering application");

        threadManager = std::make_unique<ThreadManager>();

        threadManager->start("task1");
        threadManager->start("task2");

        while(true) {
            LOG4CXX_INFO(logger, "Logging from main() " << "in Huntsville, AL");
            usleep(1000000);
        }

    }
    catch(Exception&) {
        result = EXIT_FAILURE;
    }

    return result;
}

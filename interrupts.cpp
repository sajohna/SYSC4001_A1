/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */

#include<interrupts.hpp>

int main(int argc, char** argv) {

    //vectors is a C++ std::vector of strings that contain the address of the ISR
    //delays  is a C++ std::vector of ints that contain the delays of each device
    //the index of these elemens is the device number, starting from 0
    auto [vectors, delays] = parse_args(argc, argv);
    std::ifstream input_file(argv[1]);

    std::string trace;      //!< string to store single line of trace file
    std::string execution;  //!< string to accumulate the execution output

    /******************ADD YOUR VARIABLES HERE*************************/
    std::pair<std::string, int> boilerplate;
    long int time = 0;
    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/
        std::cout << "testing compilation" << std::endl;
        if (!activity.compare("CPU")){
            execution += std::to_string(time) + ", " + std::to_string(duration_intr) + ", CPU burst\n";
            time += duration_intr;

        } else if (!activity.compare("SYSCALL")){
            boilerplate = intr_boilerplate(time, duration_intr, 10, vectors);
            execution += std::get<0>(boilerplate);
            time = std::get<1>(boilerplate);

            execution += std::to_string(time) + ", " + std::to_string(delays[duration_intr]) + ", execute I/O\n";
            time += delays[duration_intr];

            execution += std::to_string(time) + ", " + std::to_string(1) + ", execute IRET\n";
            time ++;

            execution += std::to_string(time) + ", " + std::to_string(1) + ", switch out of kernel mode\n";
            time++;

            execution += std::to_string(time) + ", " + std::to_string(10) + ", context reloaded\n";
            time += 10;
        } else{
            int random = (rand() % 50) + 1;
            execution += std::to_string(time) + ", " + std::to_string(random) + ", end of I/O " +std::to_string(duration_intr) +": interrupt \n";
            time += random;
        }

        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}

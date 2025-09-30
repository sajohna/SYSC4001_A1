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
    int time = 0;
    int device_number = 0;
    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);

        /******************ADD YOUR SIMULATION CODE HERE*************************/
        //for cpu
        
        //for syscall and end_io
        boilerplate = intr_boilerplate(time, duration_intr, 10, vectors);
        execution += std::get<0>(boilerplate);
        time += std::get<1>(boilerplate);

        //for cpu
        

        execution += std::to_string(time) + ", " + std::to_string(duration_intr) + ", call device driver\n";
        time += duration_intr;

        execution += "...\n";
        time += delays[device_number];

        execution += std::to_string(time) + ", " + std::to_string(1) + ", IRET // IRET after " + std::to_string(delays[device_number]) +"ms\n";
        time ++;

        device_number ++;
        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}

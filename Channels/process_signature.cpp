#include <stlab/channel.hpp>

using process_state_scheduled = 
	std::pair<process_state, std::chrono::system_clock::time_point>;

struct process_signature 
{
    void await(T... val);

    U yield();

    process_state_scheduled state() const;

    void close();                       // optional

    void set_error(std::exception_ptr); // optional
};
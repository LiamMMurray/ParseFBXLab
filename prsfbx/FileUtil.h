#pragma once
#include <fstream>
#include <string>
#define PRENOOP  // pre-processor no-op

struct file_context
{
       private:
        file_context(){};
        static file_context* singleton;

       public:
        static file_context* get() { return singleton; }
        std::string          data_in;
        std::string          data_out;

        void write_file(std::string name)
        {
                std::fstream fstream;
                fstream.open(name, std::ios_base::in | std::ios_base::ate);

                if (fstream.tellp() > 0)
                {
                        std::cout << "this will overwrite an existing "
                                     "file, continue? y/n\n";
                        std::string answer;
                        std::cin >> answer;
                        if (answer == "n" || answer == "q")
                                /*early exit*/
                                return;
                        else if (answer != "y")
                                /*non-valid answer*/
                                write_file(name);
                }

                fstream.close();
                fstream.open(name, std::ios_base::out | std::ios_base::trunc);

                fstream.write(file_context::get()->data_out.c_str(),
                              file_context::get()->data_out.size());

                fstream.close();
        }
};
file_context* file_context::singleton = new file_context();

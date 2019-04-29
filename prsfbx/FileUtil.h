#pragma once
#include <ShlObj_core.h>
#include <Windows.h>
#include <fstream>
#include <string>

struct file_context
{
      private:
        file_context(){};
        static file_context *singleton;

      public:
        static file_context *get() { return singleton; }
        std::string          data_in;
        std::string          data_out;

        // write file relative to current executing process
        void write_file(std::string filepath_and_filename)
        {
                auto        split_filepath_and_filename = split_directory_and_file_name(filepath_and_filename);
                std::string file_path                   = split_filepath_and_filename.first;
                std::string file_name                   = split_filepath_and_filename.second;

                create_dir(file_path);

                std::fstream fstream;
                fstream.open(filepath_and_filename, std::ios_base::in | std::ios_base::ate);
                std::cout << "writing file\n";
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
                                write_file(filepath_and_filename);
                }

                fstream.close();
                fstream.open(filepath_and_filename, std::ios_base::out | std::ios_base::trunc);

                fstream.write(file_context::get()->data_out.c_str(), file_context::get()->data_out.size());
                std::cout << "wrote file\n";
                fstream.close();
        }
        // creates directory and all sub directories relative to current executing directory
        void create_dir(std::string dir)
        {
                std::string full_path = get_current_dir() + dir;
                int         error     = SHCreateDirectoryExA(NULL, full_path.c_str(), NULL);
        }
        // gets directory of the executing process
        std::string get_current_dir()
        {
                char        str_buffer[MAX_PATH];
                DWORD       str_size = GetModuleFileNameA(NULL, str_buffer, MAX_PATH);
                std::string output   = std::string(str_buffer);
                size_t      path_end = output.find_last_of("\\");
                output               = output.substr(0, path_end + 1);
                return output;
        }
        // gets directory, and file-name from a executable-relative file path and file-name
        std::pair<std::string, std::string> split_directory_and_file_name(std::string path_and_file_name)
        {
                size_t file_path_end = path_and_file_name.find_last_of('\\');
                if (file_path_end == std::string::npos)
                        return std::make_pair("", path_and_file_name);
                else
                        return std::make_pair(path_and_file_name.substr(0, file_path_end + 1),
                                              path_and_file_name.substr(file_path_end + 1, path_and_file_name.size()));
        }
};
file_context *file_context::singleton = new file_context();

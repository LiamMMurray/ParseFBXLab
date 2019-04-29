#pragma once
#include <iostream>
enum CMD
{
        null,
        help,
        cmp
};

struct command_line
{
       private:
        command_line(){};
        static command_line* singleton;

       public:
        static command_line* get() { return singleton; }
        // displays generic help info
        void help() { help(CMD::null); }
        // displays help info for a specific string command
        void help(const char* cmd)
        {
                if (strcmp(cmd, "cmp") == 0)
                        help(CMD::cmp);
                else if (strcmp(cmd, "help") == 0)
                        help(CMD::help);
                else
                {
                        std::cout << cmd << " not a valid command\n";
                        help();
                }
        }
        // displays help info for the command line arg entered
        // after help or generic help info if no arg was entered
        // after help command
        void help(int argc, char* argv[])
        {
                if (argc >= 3)
                        command_line::get()->help(argv[2]);
                else
                        command_line::get()->help();
        }
        // displays help info for a specific command
        void help(CMD cmd)
        {
                switch (cmd)
                {
                        case CMD::null:
                                std::cout
                                    // clang-format off
                                    << "these are common prsfbx commands"
                                       "\n\n"
                                    << "\tcmp\t\t\tcompiles an fbx file into vertex binary file\n "
                                       "\thelp\t\t\tdisplays help info for a specified command or generic help\n";
									//clang-format on
                                break;
                        case CMD::cmp:
                                std::cout
                                    << "[-i "
                                       "<input-file-name>]  "
                                       "[-o "
                                       "<output-file-name>]";
								break;
                        case CMD::help:
							std::cout << "[<command>]";
                                break;
                }
        }
        // compiles a file of line seperated strings into a
        // string-guid pair binary file
        void cmp(int argc, char* argv[])
        {
                if (argc <= 2)
                {
                        std::cout << "nothing specified, "
                                     "nothing compiled\n";
                        help(CMD::cmp);
                }

				// TODO: add functionality to compile command
        }

		bool args_contain(const char* arg, int argc, char* argv[])
		{
				for (int i = 0; i < argc; i++)
				{
						if (strcmp(arg, argv[i]) == 0)
								return true;
				}
				return false;
		}
};
command_line* command_line::singleton = new command_line();

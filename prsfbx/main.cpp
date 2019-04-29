#include "CommandLineUtil.h"
#include "FileUtil.h"

int main(int argc, char* argv[])
{
        if (argc == 1)
        {
                command_line_context::get()->help();
                /*early exit*/
                return 0;
        }

        if (strcmp(argv[1], "help") == 0)
        {
                command_line_context::get()->help(argc, argv);
        }

        if (strcmp(argv[1], "cmp") == 0)
        {
                command_line_context::get()->cmp(argc, argv);
        }
}

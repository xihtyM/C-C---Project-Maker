#include "include/builder.hh"

int main(
    int argc,
    char *argv[]
) {
    if (argc < 2)
    {
        std::cerr << "Invalid syntax: please type " << argv[0] << " -h for help.\n";
        return 1;
    }

    //
    // Turn argv into a vector of strings
    // mainly for convenience, also because
    // parse_args accepts a vector of strings
    // on most recent update.
    //

    std::vector<std::string> argvec(argv, argv + argc);

    std::unique_ptr<ARGS> args = parse_args(argvec);

    //
    // Either there was a bad allocation for the
    // unique_ptr, or -h flag was used, and the
    // `HELP_TEXT` was just printed.
    //
    // UPDATE: if the user inputs multiple names
    // for the project, this will also be null.
    //

    if (!args)
    {
        return 0;
    }

    //
    // As `create_project` returns true on success,
    // use this to return EXIT_SUCCESS if it is ran
    // to completion. Otherwise return EXIT_FAILURE.
    //

    return (create_project(
        args->project_name,
        args->is_cpp) ? EXIT_SUCCESS : EXIT_FAILURE);
}

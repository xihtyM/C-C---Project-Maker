#include "../include/builder.hh"

std::unique_ptr<ARGS> parse_args(
    std::vector<std::string> args
) {
    std::unique_ptr<ARGS> args_struct(new ARGS);
    
    args_struct->is_cpp = false;
    args_struct->project_name = std::string();

    // skip module name
    for (size_t index = 1; index < args.size(); index++)
    {
        if (args[index] == "-h")
        {
            std::cout << HELP_TEXT;
            return std::unique_ptr<ARGS>(null);
        }
        else if (args[index] == "-c")
        {
            args_struct->is_cpp = true;
        }
        else
        {
            //
            // If the project name has already been declared,
            // return null as an error and print error message.
            //

            if (args_struct->project_name != std::string())
            {
                std::cerr << "cannot declare multiple project names.\n";
                return std::unique_ptr<ARGS>(null);
            }

            args_struct->project_name = args[index];
        }
    }

    return args_struct;
}

bool create_project(
    std::string name,
    bool is_cpp
) {

    //
    // Try to create directories for the project.
    // - If failed, just print the reason.
    //

    namespace fs = std::filesystem;

    if (!fs::create_directory(name))
    {
        std::cerr << "Error: Directory could not be created: \""
                  << name << "\"\n";
        return false;
    }

    fs::current_path(name);

    if (!fs::create_directory("impl")
      | !fs::create_directory("include"))
    {
        std::cerr << "Error: Directories could not be created: \""
                  << name << "/impl\" and/or \""
                  << name << "/include\"\n.";
        return false;
    }

    //
    // Create name.h and main.c files,
    // as they are commonly used like
    // this.
    //

    const char *main_filename = "main.c";

    if (is_cpp)
    {
        main_filename = "main.cc";
    }

    std::ofstream main(main_filename);
    
    if (is_cpp)
    {
        main << "#include \"include/" << name << ".hh\"\n";
    }
    else
    {
        main << "#include \"include/" << name << ".h\"\n";
    }

    main << MAIN_CODE;

    main.close();

    std::string main_header_filename("include/");
    main_header_filename += name;
    main_header_filename += ".h";

    if (is_cpp)
    {
        main_header_filename += 'h';
    }

    std::ofstream main_header(main_header_filename);

    main_header << "#pragma once\n";

    main_header.close();

    //
    // Make build.py
    //

    std::ofstream build_py("build.py");

    if (is_cpp)
    {
        build_py << "COMPILER = \"g++\"\n"
                 << "MAIN_FILE = \"\\\"main.cc\\\"\"\n";
    }
    else
    {
        build_py << "COMPILER = \"gcc\"\n"
                 << "MAIN_FILE = \"\\\"main.c\\\"\"\n";
    }

    build_py << BUILD_PY << name << "\")\n";

    build_py.close();


    return true;
}

#include "local_project.hpp"

LocalProject::LocalProject()
    : Project(fs::path("."))
{}

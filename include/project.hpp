#include <dummy/core/project.hpp>

class Project : public Dummy::Core::Project {
public:
    Project(const std::string&);
    void load();
};

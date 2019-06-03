#include <iostream>

#include "screen/screen.hpp"
#include "model/model.hpp"

namespace Model {

Model::Model()
{}

Model::~Model() {
    std::cerr << "Model destructor." << std::endl;
}

} // namespace Model

#pragma once

#include <map>
#include <string>
#include "model/model.hpp"

namespace Graphics {
    class Living;
}

namespace Model {

class PlayingModel : public Model {
public:
    using Livings =
        std::map<std::string, std::shared_ptr<Graphics::Living>>;
    PlayingModel();
    virtual ~PlayingModel();
    const Livings& livings() const {
        return m_livings;
    }

    void addLiving(const std::string&, std::shared_ptr<Graphics::Living>);
    void removeLiving(const std::string&);
    std::shared_ptr<Graphics::Living>
    getLiving(const std::string& name) {
        return m_livings[name];
    }
private:
    Livings m_livings;
};

} // namespace Model

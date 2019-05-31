#include "graphics/living.hpp"
#include "graphics/living_state/state.hpp"

namespace Graphics {
namespace LivingState {

State::State(Graphics::Living& living) :
    m_living(living)
{
}


} // namespace LivingState
} // namespace Graphics

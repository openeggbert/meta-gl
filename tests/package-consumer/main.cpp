#include <metagl/metagl.hpp>

#include <type_traits>

int main()
{
    static_assert(metagl::GlBitfield<metagl::ClearBufferBit>);
    static_assert(!std::is_convertible_v<metagl::TextureId, metagl::BufferId>);

    const auto mask =
        metagl::ClearBufferBit::Color | metagl::ClearBufferBit::Depth;
    return static_cast<metagl::GLbitfield>(mask) == 0 ? 1 : 0;
}

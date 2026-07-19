#include <metagl/metagl.hpp>

#include <type_traits>

int main()
{
    // Compile-time checks (inline / header-only)
    static_assert(metagl::GlBitfield<metagl::ClearBufferBit>);
    static_assert(!std::is_convertible_v<metagl::TextureId, metagl::BufferId>);

    const auto mask =
        metagl::ClearBufferBit::Color | metagl::ClearBufferBit::Depth;
    if (static_cast<metagl::GLbitfield>(mask) == 0)
        return 1;

    // R12: call out-of-line symbols from the installed library to verify linking.
    // GetContextStatus() and GetContextGeneration() are non-inline functions
    // compiled into Context.cpp; they work without an active GL context.
    const auto status = metagl::GetContextStatus();
    if (status != metagl::ContextStatus::NotCreated)
        return 2;

    const auto generation = metagl::GetContextGeneration();
    if (generation != 0)
        return 3;

    const auto info = metagl::GetContextInfo();
    if (info.api != metagl::ApiKind::Unknown)
        return 4;

    return 0;
}

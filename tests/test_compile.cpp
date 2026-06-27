#include <metagl/metagl.hpp>
#include <type_traits>

using namespace metagl;

// =============================================================================
// I2 — Template dispatch: verify all typed overloads resolve at compile time.
// Note: requires-expressions with local declarations are not allowed in C++23
// simple requirements; use the parameter form (requires(T* p){...}) instead.
// =============================================================================

// glGetUniform<T>
static_assert(requires(float* p)        { glGetUniform(ProgramId{}, UniformLocation{}, p); });
static_assert(requires(int* p)          { glGetUniform(ProgramId{}, UniformLocation{}, p); });
static_assert(requires(unsigned int* p) { glGetUniform(ProgramId{}, UniformLocation{}, p); });

// glGetnUniform<T>
static_assert(requires(float* p)        { glGetnUniform(ProgramId{}, UniformLocation{}, 4, p); });
static_assert(requires(int* p)          { glGetnUniform(ProgramId{}, UniformLocation{}, 4, p); });
static_assert(requires(unsigned int* p) { glGetnUniform(ProgramId{}, UniformLocation{}, 4, p); });

// glTexParameter<T>
static_assert(requires { glTexParameter(TextureTarget::Texture2D, TextureParameter::MinFilter, 0.0f); });
static_assert(requires { glTexParameter(TextureTarget::Texture2D, TextureParameter::MinFilter, 0); });

// glSamplerParameter<T>
static_assert(requires { glSamplerParameter(SamplerId{}, SamplerParameter::MinFilter, 0.0f); });
static_assert(requires { glSamplerParameter(SamplerId{}, SamplerParameter::MinFilter, 0); });

// glClearBuffer<T>
static_assert(requires(float* v)        { glClearBuffer(ClearBuffer::Color, 0, v); });
static_assert(requires(int* v)          { glClearBuffer(ClearBuffer::Color, 0, v); });
static_assert(requires(unsigned int* v) { glClearBuffer(ClearBuffer::Color, 0, v); });

// glGetVertexAttrib<T>
static_assert(requires(float* v)        { glGetVertexAttrib(AttribLocation{}, VertexAttribParameter::CurrentVertexAttrib, v); });
static_assert(requires(int* v)          { glGetVertexAttrib(AttribLocation{}, VertexAttribParameter::CurrentVertexAttrib, v); });
static_assert(requires(unsigned int* v) { glGetVertexAttrib(AttribLocation{}, VertexAttribParameter::CurrentVertexAttrib, v); });

// =============================================================================
// I3 — Bitfield operators: operator| / & / ~ must return the original enum type
// =============================================================================

static_assert(std::is_same_v<decltype(ClearBufferBit::Color | ClearBufferBit::Depth),     ClearBufferBit>);
static_assert(std::is_same_v<decltype(ClearBufferBit::Color & ClearBufferBit::Depth),     ClearBufferBit>);
static_assert(std::is_same_v<decltype(~ClearBufferBit::Color),                             ClearBufferBit>);

static_assert(std::is_same_v<decltype(MapBufferAccessMask::Read | MapBufferAccessMask::Write),   MapBufferAccessMask>);
static_assert(std::is_same_v<decltype(ShaderStageMask::Vertex   | ShaderStageMask::Fragment),    ShaderStageMask>);
static_assert(std::is_same_v<decltype(MemoryBarrierMask::VertexAttribArray | MemoryBarrierMask::ElementArray), MemoryBarrierMask>);
static_assert(std::is_same_v<decltype(ContextFlagMask::Debug | ContextFlagMask::RobustAccess),   ContextFlagMask>);

// =============================================================================
// I2 — Concept membership checks
// =============================================================================

// GlHandle: satisfied by handle structs, not plain scalars
static_assert(GlHandle<TextureId>);
static_assert(GlHandle<BufferId>);
static_assert(GlHandle<ShaderId>);
static_assert(GlHandle<ProgramId>);
static_assert(!GlHandle<int>);
static_assert(!GlHandle<float>);
static_assert(!GlHandle<GLuint>);  // raw uint has no .value member

// GlBitfield: satisfied by GLbitfield-backed enum classes
static_assert(GlBitfield<ClearBufferBit>);
static_assert(GlBitfield<MapBufferAccessMask>);
static_assert(GlBitfield<ShaderStageMask>);
static_assert(GlBitfield<MemoryBarrierMask>);
static_assert(GlBitfield<ContextFlagMask>);
static_assert(!GlBitfield<int>);

// SpanCompatible: trivially copyable + standard layout
static_assert(SpanCompatible<float>);
static_assert(SpanCompatible<int>);
static_assert(SpanCompatible<TextureId>);

// =============================================================================
// I4 — Handle type isolation: distinct handle types must not be interchangeable
// =============================================================================

// No implicit conversion between any two distinct handle types
static_assert(!std::is_convertible_v<ShaderId,   ProgramId>);
static_assert(!std::is_convertible_v<ProgramId,  ShaderId>);
static_assert(!std::is_convertible_v<TextureId,  BufferId>);
static_assert(!std::is_convertible_v<BufferId,   TextureId>);
static_assert(!std::is_convertible_v<TextureId,  FramebufferId>);
static_assert(!std::is_convertible_v<SamplerId,  VertexArrayId>);
static_assert(!std::is_convertible_v<QueryId,    TransformFeedbackId>);

// No implicit construction of one handle type from another
static_assert(!std::is_constructible_v<ShaderId,   ProgramId>);
static_assert(!std::is_constructible_v<TextureId,  BufferId>);
static_assert(!std::is_constructible_v<FramebufferId, RenderbufferId>);

// UniformLocation (GLint) and AttribLocation (GLuint) are distinct structs
static_assert(!std::is_convertible_v<UniformLocation, AttribLocation>);
static_assert(!std::is_convertible_v<AttribLocation,  UniformLocation>);

// Plain GLuint does not satisfy GlHandle — it has no .value member
static_assert(!GlHandle<GLuint>);
static_assert(!GlHandle<unsigned int>);

// Handle types do not satisfy GlEnum or GlBitfield
static_assert(!GlEnum<TextureId>);
static_assert(!GlBitfield<BufferId>);

int main() { return 0; }

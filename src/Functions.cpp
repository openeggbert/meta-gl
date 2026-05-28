#include "metagl/metagl.hpp"

#include <type_traits>

namespace metagl::detail
{
    template <typename Enum>
    constexpr GLenum to_gl_enum(Enum value) noexcept
    {
        return static_cast<GLenum>(value);
    }

    template <typename Enum>
    constexpr GLbitfield to_gl_bitfield(Enum value) noexcept
    {
        return static_cast<GLbitfield>(value);
    }

    struct GlTable
    {
        bool initialized = false;

        PFNGLENABLEPROC Enable = nullptr;
        PFNGLDISABLEPROC Disable = nullptr;
        PFNGLENABLEIPROC Enablei = nullptr;
        PFNGLDISABLEIPROC Disablei = nullptr;
        PFNGLISENABLEDPROC IsEnabled = nullptr;
        PFNGLISENABLEDIPROC IsEnabledi = nullptr;
        PFNGLBLENDFUNCPROC BlendFunc = nullptr;
        PFNGLBLENDFUNCSEPARATEPROC BlendFuncSeparate = nullptr;
        PFNGLBLENDFUNCIPROC BlendFunci = nullptr;
        PFNGLBLENDFUNCSEPARATEIPROC BlendFuncSeparatei = nullptr;
        PFNGLBLENDEQUATIONPROC BlendEquation = nullptr;
        PFNGLBLENDEQUATIONSEPARATEPROC BlendEquationSeparate = nullptr;
        PFNGLBLENDEQUATIONIPROC BlendEquationi = nullptr;
        PFNGLBLENDEQUATIONSEPARATEIPROC BlendEquationSeparatei = nullptr;
        PFNGLBLENDCOLORPROC BlendColor = nullptr;
        PFNGLBLENDBARRIERPROC BlendBarrier = nullptr;
        PFNGLCOLORMASKPROC ColorMask = nullptr;
        PFNGLCOLORMASKIPROC ColorMaski = nullptr;
        PFNGLDEPTHFUNCPROC DepthFunc = nullptr;
        PFNGLDEPTHMASKPROC DepthMask = nullptr;
        PFNGLDEPTHRANGEFPROC DepthRangef = nullptr;
        PFNGLSTENCILFUNCPROC StencilFunc = nullptr;
        PFNGLSTENCILFUNCSEPARATEPROC StencilFuncSeparate = nullptr;
        PFNGLSTENCILOPPROC StencilOp = nullptr;
        PFNGLSTENCILOPSEPARATEPROC StencilOpSeparate = nullptr;
        PFNGLSTENCILMASKPROC StencilMask = nullptr;
        PFNGLSTENCILMASKSEPARATEPROC StencilMaskSeparate = nullptr;
        PFNGLSCISSORPROC Scissor = nullptr;
        PFNGLVIEWPORTPROC Viewport = nullptr;
        PFNGLCULLFACEPROC CullFace = nullptr;
        PFNGLFRONTFACEPROC FrontFace = nullptr;
        PFNGLLINEWIDTHPROC LineWidth = nullptr;
        PFNGLPOLYGONOFFSETPROC PolygonOffset = nullptr;
        PFNGLSAMPLECOVERAGEPROC SampleCoverage = nullptr;
        PFNGLSAMPLEMASKIPROC SampleMaski = nullptr;
        PFNGLMINSAMPLESHADINGPROC MinSampleShading = nullptr;
        PFNGLHINTPROC Hint = nullptr;
        PFNGLPIXELSTOREIPROC PixelStorei = nullptr;
        PFNGLFINISHPROC Finish = nullptr;
        PFNGLFLUSHPROC Flush = nullptr;
        PFNGLGETERRORPROC GetError = nullptr;
        PFNGLGETBOOLEANVPROC GetBooleanv = nullptr;
        PFNGLGETINTEGERVPROC GetIntegerv = nullptr;
        PFNGLGETFLOATVPROC GetFloatv = nullptr;
        PFNGLGETINTEGER64VPROC GetInteger64v = nullptr;
        PFNGLGETINTEGERI_VPROC GetIntegeri_v = nullptr;
        PFNGLGETINTEGER64I_VPROC GetInteger64i_v = nullptr;
        PFNGLGETBOOLEANI_VPROC GetBooleani_v = nullptr;
        PFNGLGETSTRINGPROC GetString = nullptr;
        PFNGLGETSTRINGIPROC GetStringi = nullptr;
        PFNGLGETPOINTERVPROC GetPointerv = nullptr;
        PFNGLGENBUFFERSPROC GenBuffers = nullptr;
        PFNGLDELETEBUFFERSPROC DeleteBuffers = nullptr;
        PFNGLBINDBUFFERPROC BindBuffer = nullptr;
        PFNGLBINDBUFFERBASEPROC BindBufferBase = nullptr;
        PFNGLBINDBUFFERRANGEPROC BindBufferRange = nullptr;
        PFNGLBUFFERDATAPROC BufferData = nullptr;
        PFNGLBUFFERSUBDATAPROC BufferSubData = nullptr;
        PFNGLCOPYBUFFERSUBDATAPROC CopyBufferSubData = nullptr;
        PFNGLMAPBUFFERRANGEPROC MapBufferRange = nullptr;
        PFNGLFLUSHMAPPEDBUFFERRANGEPROC FlushMappedBufferRange = nullptr;
        PFNGLUNMAPBUFFERPROC UnmapBuffer = nullptr;
        PFNGLISBUFFERPROC IsBuffer = nullptr;
        PFNGLGETBUFFERPARAMETERIVPROC GetBufferParameteriv = nullptr;
        PFNGLGETBUFFERPARAMETERI64VPROC GetBufferParameteri64v = nullptr;
        PFNGLGETBUFFERPOINTERVPROC GetBufferPointerv = nullptr;
        PFNGLGENVERTEXARRAYSPROC GenVertexArrays = nullptr;
        PFNGLDELETEVERTEXARRAYSPROC DeleteVertexArrays = nullptr;
        PFNGLBINDVERTEXARRAYPROC BindVertexArray = nullptr;
        PFNGLISVERTEXARRAYPROC IsVertexArray = nullptr;
        PFNGLENABLEVERTEXATTRIBARRAYPROC EnableVertexAttribArray = nullptr;
        PFNGLDISABLEVERTEXATTRIBARRAYPROC DisableVertexAttribArray = nullptr;
        PFNGLVERTEXATTRIBPOINTERPROC VertexAttribPointer = nullptr;
        PFNGLVERTEXATTRIBIPOINTERPROC VertexAttribIPointer = nullptr;
        PFNGLVERTEXATTRIBDIVISORPROC VertexAttribDivisor = nullptr;
        PFNGLVERTEXATTRIB1FPROC VertexAttrib1f = nullptr;
        PFNGLVERTEXATTRIB2FPROC VertexAttrib2f = nullptr;
        PFNGLVERTEXATTRIB3FPROC VertexAttrib3f = nullptr;
        PFNGLVERTEXATTRIB4FPROC VertexAttrib4f = nullptr;
        PFNGLVERTEXATTRIB1FVPROC VertexAttrib1fv = nullptr;
        PFNGLVERTEXATTRIB2FVPROC VertexAttrib2fv = nullptr;
        PFNGLVERTEXATTRIB3FVPROC VertexAttrib3fv = nullptr;
        PFNGLVERTEXATTRIB4FVPROC VertexAttrib4fv = nullptr;
        PFNGLVERTEXATTRIBI4IPROC VertexAttribI4i = nullptr;
        PFNGLVERTEXATTRIBI4UIPROC VertexAttribI4ui = nullptr;
        PFNGLVERTEXATTRIBI4IVPROC VertexAttribI4iv = nullptr;
        PFNGLVERTEXATTRIBI4UIVPROC VertexAttribI4uiv = nullptr;
        PFNGLGETVERTEXATTRIBFVPROC GetVertexAttribfv = nullptr;
        PFNGLGETVERTEXATTRIBIVPROC GetVertexAttribiv = nullptr;
        PFNGLGETVERTEXATTRIBIIVPROC GetVertexAttribIiv = nullptr;
        PFNGLGETVERTEXATTRIBIUIVPROC GetVertexAttribIuiv = nullptr;
        PFNGLGETVERTEXATTRIBPOINTERVPROC GetVertexAttribPointerv = nullptr;
        PFNGLVERTEXATTRIBFORMATPROC VertexAttribFormat = nullptr;
        PFNGLVERTEXATTRIBIFORMATPROC VertexAttribIFormat = nullptr;
        PFNGLVERTEXATTRIBBINDINGPROC VertexAttribBinding = nullptr;
        PFNGLBINDVERTEXBUFFERPROC BindVertexBuffer = nullptr;
        PFNGLVERTEXBINDINGDIVISORPROC VertexBindingDivisor = nullptr;
        PFNGLDRAWARRAYSPROC DrawArrays = nullptr;
        PFNGLDRAWARRAYSINSTANCEDPROC DrawArraysInstanced = nullptr;
        PFNGLDRAWARRAYSINDIRECTPROC DrawArraysIndirect = nullptr;
        PFNGLDRAWELEMENTSPROC DrawElements = nullptr;
        PFNGLDRAWELEMENTSINSTANCEDPROC DrawElementsInstanced = nullptr;
        PFNGLDRAWRANGEELEMENTSPROC DrawRangeElements = nullptr;
        PFNGLDRAWELEMENTSBASEVERTEXPROC DrawElementsBaseVertex = nullptr;
        PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC DrawElementsInstancedBaseVertex = nullptr;
        PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC DrawRangeElementsBaseVertex = nullptr;
        PFNGLDRAWELEMENTSINDIRECTPROC DrawElementsIndirect = nullptr;
        PFNGLDRAWBUFFERSPROC DrawBuffers = nullptr;
        PFNGLREADBUFFERPROC ReadBuffer = nullptr;
        PFNGLREADPIXELSPROC ReadPixels = nullptr;
        PFNGLREADNPIXELSPROC ReadnPixels = nullptr;
        PFNGLCLEARPROC Clear = nullptr;
        PFNGLCLEARCOLORPROC ClearColor = nullptr;
        PFNGLCLEARDEPTHFPROC ClearDepthf = nullptr;
        PFNGLCLEARSTENCILPROC ClearStencil = nullptr;
        PFNGLCLEARBUFFERFVPROC ClearBufferfv = nullptr;
        PFNGLCLEARBUFFERIVPROC ClearBufferiv = nullptr;
        PFNGLCLEARBUFFERUIVPROC ClearBufferuiv = nullptr;
        PFNGLCLEARBUFFERFIPROC ClearBufferfi = nullptr;
        PFNGLCREATESHADERPROC CreateShader = nullptr;
        PFNGLDELETESHADERPROC DeleteShader = nullptr;
        PFNGLSHADERSOURCEPROC ShaderSource = nullptr;
        PFNGLCOMPILESHADERPROC CompileShader = nullptr;
        PFNGLSHADERBINARYPROC ShaderBinary = nullptr;
        PFNGLRELEASESHADERCOMPILERPROC ReleaseShaderCompiler = nullptr;
        PFNGLGETSHADERIVPROC GetShaderiv = nullptr;
        PFNGLGETSHADERINFOLOGPROC GetShaderInfoLog = nullptr;
        PFNGLGETSHADERSOURCEPROC GetShaderSource = nullptr;
        PFNGLGETSHADERPRECISIONFORMATPROC GetShaderPrecisionFormat = nullptr;
        PFNGLISSHADERPROC IsShader = nullptr;
        PFNGLCREATEPROGRAMPROC CreateProgram = nullptr;
        PFNGLDELETEPROGRAMPROC DeleteProgram = nullptr;
        PFNGLATTACHSHADERPROC AttachShader = nullptr;
        PFNGLDETACHSHADERPROC DetachShader = nullptr;
        PFNGLLINKPROGRAMPROC LinkProgram = nullptr;
        PFNGLUSEPROGRAMPROC UseProgram = nullptr;
        PFNGLVALIDATEPROGRAMPROC ValidateProgram = nullptr;
        PFNGLGETPROGRAMIVPROC GetProgramiv = nullptr;
        PFNGLGETPROGRAMINFOLOGPROC GetProgramInfoLog = nullptr;
        PFNGLISPROGRAMPROC IsProgram = nullptr;
        PFNGLGETATTACHEDSHADERSPROC GetAttachedShaders = nullptr;
        PFNGLBINDATTRIBLOCATIONPROC BindAttribLocation = nullptr;
        PFNGLGETATTRIBLOCATIONPROC GetAttribLocation = nullptr;
        PFNGLGETACTIVEATTRIBPROC GetActiveAttrib = nullptr;
        PFNGLGETPROGRAMBINARYPROC GetProgramBinary = nullptr;
        PFNGLPROGRAMBINARYPROC ProgramBinary = nullptr;
        PFNGLPROGRAMPARAMETERIPROC ProgramParameteri = nullptr;
        PFNGLGETFRAGDATALOCATIONPROC GetFragDataLocation = nullptr;
        PFNGLGETPROGRAMINTERFACEIVPROC GetProgramInterfaceiv = nullptr;
        PFNGLGETPROGRAMRESOURCEINDEXPROC GetProgramResourceIndex = nullptr;
        PFNGLGETPROGRAMRESOURCENAMEPROC GetProgramResourceName = nullptr;
        PFNGLGETPROGRAMRESOURCEIVPROC GetProgramResourceiv = nullptr;
        PFNGLGETPROGRAMRESOURCELOCATIONPROC GetProgramResourceLocation = nullptr;
        PFNGLGETUNIFORMLOCATIONPROC GetUniformLocation = nullptr;
        PFNGLGETACTIVEUNIFORMPROC GetActiveUniform = nullptr;
        PFNGLGETACTIVEUNIFORMSIVPROC GetActiveUniformsiv = nullptr;
        PFNGLGETUNIFORMINDICESPROC GetUniformIndices = nullptr;
        PFNGLGETUNIFORMBLOCKINDEXPROC GetUniformBlockIndex = nullptr;
        PFNGLGETACTIVEUNIFORMBLOCKIVPROC GetActiveUniformBlockiv = nullptr;
        PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC GetActiveUniformBlockName = nullptr;
        PFNGLUNIFORMBLOCKBINDINGPROC UniformBlockBinding = nullptr;
        PFNGLUNIFORM1FPROC Uniform1f = nullptr;
        PFNGLUNIFORM2FPROC Uniform2f = nullptr;
        PFNGLUNIFORM3FPROC Uniform3f = nullptr;
        PFNGLUNIFORM4FPROC Uniform4f = nullptr;
        PFNGLUNIFORM1FVPROC Uniform1fv = nullptr;
        PFNGLUNIFORM2FVPROC Uniform2fv = nullptr;
        PFNGLUNIFORM3FVPROC Uniform3fv = nullptr;
        PFNGLUNIFORM4FVPROC Uniform4fv = nullptr;
        PFNGLUNIFORM1IPROC Uniform1i = nullptr;
        PFNGLUNIFORM2IPROC Uniform2i = nullptr;
        PFNGLUNIFORM3IPROC Uniform3i = nullptr;
        PFNGLUNIFORM4IPROC Uniform4i = nullptr;
        PFNGLUNIFORM1IVPROC Uniform1iv = nullptr;
        PFNGLUNIFORM2IVPROC Uniform2iv = nullptr;
        PFNGLUNIFORM3IVPROC Uniform3iv = nullptr;
        PFNGLUNIFORM4IVPROC Uniform4iv = nullptr;
        PFNGLUNIFORM1UIPROC Uniform1ui = nullptr;
        PFNGLUNIFORM2UIPROC Uniform2ui = nullptr;
        PFNGLUNIFORM3UIPROC Uniform3ui = nullptr;
        PFNGLUNIFORM4UIPROC Uniform4ui = nullptr;
        PFNGLUNIFORM1UIVPROC Uniform1uiv = nullptr;
        PFNGLUNIFORM2UIVPROC Uniform2uiv = nullptr;
        PFNGLUNIFORM3UIVPROC Uniform3uiv = nullptr;
        PFNGLUNIFORM4UIVPROC Uniform4uiv = nullptr;
        PFNGLUNIFORMMATRIX2FVPROC UniformMatrix2fv = nullptr;
        PFNGLUNIFORMMATRIX3FVPROC UniformMatrix3fv = nullptr;
        PFNGLUNIFORMMATRIX4FVPROC UniformMatrix4fv = nullptr;
        PFNGLUNIFORMMATRIX2X3FVPROC UniformMatrix2x3fv = nullptr;
        PFNGLUNIFORMMATRIX2X4FVPROC UniformMatrix2x4fv = nullptr;
        PFNGLUNIFORMMATRIX3X2FVPROC UniformMatrix3x2fv = nullptr;
        PFNGLUNIFORMMATRIX3X4FVPROC UniformMatrix3x4fv = nullptr;
        PFNGLUNIFORMMATRIX4X2FVPROC UniformMatrix4x2fv = nullptr;
        PFNGLUNIFORMMATRIX4X3FVPROC UniformMatrix4x3fv = nullptr;
        PFNGLGETUNIFORMFVPROC GetUniformfv = nullptr;
        PFNGLGETUNIFORMIVPROC GetUniformiv = nullptr;
        PFNGLGETUNIFORMUIVPROC GetUniformuiv = nullptr;
        PFNGLGETNUNIFORMFVPROC GetnUniformfv = nullptr;
        PFNGLGETNUNIFORMIVPROC GetnUniformiv = nullptr;
        PFNGLGETNUNIFORMUIVPROC GetnUniformuiv = nullptr;
        PFNGLPROGRAMUNIFORM1FPROC ProgramUniform1f = nullptr;
        PFNGLPROGRAMUNIFORM2FPROC ProgramUniform2f = nullptr;
        PFNGLPROGRAMUNIFORM3FPROC ProgramUniform3f = nullptr;
        PFNGLPROGRAMUNIFORM4FPROC ProgramUniform4f = nullptr;
        PFNGLPROGRAMUNIFORM1FVPROC ProgramUniform1fv = nullptr;
        PFNGLPROGRAMUNIFORM2FVPROC ProgramUniform2fv = nullptr;
        PFNGLPROGRAMUNIFORM3FVPROC ProgramUniform3fv = nullptr;
        PFNGLPROGRAMUNIFORM4FVPROC ProgramUniform4fv = nullptr;
        PFNGLPROGRAMUNIFORM1IPROC ProgramUniform1i = nullptr;
        PFNGLPROGRAMUNIFORM2IPROC ProgramUniform2i = nullptr;
        PFNGLPROGRAMUNIFORM3IPROC ProgramUniform3i = nullptr;
        PFNGLPROGRAMUNIFORM4IPROC ProgramUniform4i = nullptr;
        PFNGLPROGRAMUNIFORM1IVPROC ProgramUniform1iv = nullptr;
        PFNGLPROGRAMUNIFORM2IVPROC ProgramUniform2iv = nullptr;
        PFNGLPROGRAMUNIFORM3IVPROC ProgramUniform3iv = nullptr;
        PFNGLPROGRAMUNIFORM4IVPROC ProgramUniform4iv = nullptr;
        PFNGLPROGRAMUNIFORM1UIPROC ProgramUniform1ui = nullptr;
        PFNGLPROGRAMUNIFORM2UIPROC ProgramUniform2ui = nullptr;
        PFNGLPROGRAMUNIFORM3UIPROC ProgramUniform3ui = nullptr;
        PFNGLPROGRAMUNIFORM4UIPROC ProgramUniform4ui = nullptr;
        PFNGLPROGRAMUNIFORM1UIVPROC ProgramUniform1uiv = nullptr;
        PFNGLPROGRAMUNIFORM2UIVPROC ProgramUniform2uiv = nullptr;
        PFNGLPROGRAMUNIFORM3UIVPROC ProgramUniform3uiv = nullptr;
        PFNGLPROGRAMUNIFORM4UIVPROC ProgramUniform4uiv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX2FVPROC ProgramUniformMatrix2fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX3FVPROC ProgramUniformMatrix3fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX4FVPROC ProgramUniformMatrix4fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC ProgramUniformMatrix2x3fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC ProgramUniformMatrix2x4fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC ProgramUniformMatrix3x2fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC ProgramUniformMatrix3x4fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC ProgramUniformMatrix4x2fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC ProgramUniformMatrix4x3fv = nullptr;
        PFNGLGENTEXTURESPROC GenTextures = nullptr;
        PFNGLDELETETEXTURESPROC DeleteTextures = nullptr;
        PFNGLBINDTEXTUREPROC BindTexture = nullptr;
        PFNGLACTIVETEXTUREPROC ActiveTexture = nullptr;
        PFNGLISTEXTUREPROC IsTexture = nullptr;
        PFNGLTEXIMAGE2DPROC TexImage2D = nullptr;
        PFNGLTEXIMAGE3DPROC TexImage3D = nullptr;
        PFNGLTEXSUBIMAGE2DPROC TexSubImage2D = nullptr;
        PFNGLTEXSUBIMAGE3DPROC TexSubImage3D = nullptr;
        PFNGLTEXSTORAGE2DPROC TexStorage2D = nullptr;
        PFNGLTEXSTORAGE3DPROC TexStorage3D = nullptr;
        PFNGLTEXSTORAGE2DMULTISAMPLEPROC TexStorage2DMultisample = nullptr;
        PFNGLTEXSTORAGE3DMULTISAMPLEPROC TexStorage3DMultisample = nullptr;
        PFNGLCOMPRESSEDTEXIMAGE2DPROC CompressedTexImage2D = nullptr;
        PFNGLCOMPRESSEDTEXIMAGE3DPROC CompressedTexImage3D = nullptr;
        PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC CompressedTexSubImage2D = nullptr;
        PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC CompressedTexSubImage3D = nullptr;
        PFNGLCOPYTEXIMAGE2DPROC CopyTexImage2D = nullptr;
        PFNGLCOPYTEXSUBIMAGE2DPROC CopyTexSubImage2D = nullptr;
        PFNGLCOPYTEXSUBIMAGE3DPROC CopyTexSubImage3D = nullptr;
        PFNGLCOPYIMAGESUBDATAPROC CopyImageSubData = nullptr;
        PFNGLGENERATEMIPMAPPROC GenerateMipmap = nullptr;
        PFNGLTEXPARAMETERFPROC TexParameterf = nullptr;
        PFNGLTEXPARAMETERIPROC TexParameteri = nullptr;
        PFNGLTEXPARAMETERFVPROC TexParameterfv = nullptr;
        PFNGLTEXPARAMETERIVPROC TexParameteriv = nullptr;
        PFNGLTEXPARAMETERIIVPROC TexParameterIiv = nullptr;
        PFNGLTEXPARAMETERIUIVPROC TexParameterIuiv = nullptr;
        PFNGLGETTEXPARAMETERFVPROC GetTexParameterfv = nullptr;
        PFNGLGETTEXPARAMETERIVPROC GetTexParameteriv = nullptr;
        PFNGLGETTEXPARAMETERIIVPROC GetTexParameterIiv = nullptr;
        PFNGLGETTEXPARAMETERIUIVPROC GetTexParameterIuiv = nullptr;
        PFNGLGETTEXLEVELPARAMETERIVPROC GetTexLevelParameteriv = nullptr;
        PFNGLGETTEXLEVELPARAMETERFVPROC GetTexLevelParameterfv = nullptr;
        PFNGLTEXBUFFERPROC TexBuffer = nullptr;
        PFNGLTEXBUFFERRANGEPROC TexBufferRange = nullptr;
        PFNGLGETMULTISAMPLEFVPROC GetMultisamplefv = nullptr;
        PFNGLGETINTERNALFORMATIVPROC GetInternalformativ = nullptr;
        PFNGLBINDIMAGETEXTUREPROC BindImageTexture = nullptr;
        PFNGLGENSAMPLERSPROC GenSamplers = nullptr;
        PFNGLDELETESAMPLERSPROC DeleteSamplers = nullptr;
        PFNGLBINDSAMPLERPROC BindSampler = nullptr;
        PFNGLISSAMPLERPROC IsSampler = nullptr;
        PFNGLSAMPLERPARAMETERFPROC SamplerParameterf = nullptr;
        PFNGLSAMPLERPARAMETERIPROC SamplerParameteri = nullptr;
        PFNGLSAMPLERPARAMETERFVPROC SamplerParameterfv = nullptr;
        PFNGLSAMPLERPARAMETERIVPROC SamplerParameteriv = nullptr;
        PFNGLSAMPLERPARAMETERIIVPROC SamplerParameterIiv = nullptr;
        PFNGLSAMPLERPARAMETERIUIVPROC SamplerParameterIuiv = nullptr;
        PFNGLGETSAMPLERPARAMETERFVPROC GetSamplerParameterfv = nullptr;
        PFNGLGETSAMPLERPARAMETERIVPROC GetSamplerParameteriv = nullptr;
        PFNGLGETSAMPLERPARAMETERIIVPROC GetSamplerParameterIiv = nullptr;
        PFNGLGETSAMPLERPARAMETERIUIVPROC GetSamplerParameterIuiv = nullptr;
        PFNGLGENFRAMEBUFFERSPROC GenFramebuffers = nullptr;
        PFNGLDELETEFRAMEBUFFERSPROC DeleteFramebuffers = nullptr;
        PFNGLBINDFRAMEBUFFERPROC BindFramebuffer = nullptr;
        PFNGLISFRAMEBUFFERPROC IsFramebuffer = nullptr;
        PFNGLCHECKFRAMEBUFFERSTATUSPROC CheckFramebufferStatus = nullptr;
        PFNGLFRAMEBUFFERTEXTURE2DPROC FramebufferTexture2D = nullptr;
        PFNGLFRAMEBUFFERTEXTURELAYERPROC FramebufferTextureLayer = nullptr;
        PFNGLFRAMEBUFFERTEXTUREPROC FramebufferTexture = nullptr;
        PFNGLFRAMEBUFFERRENDERBUFFERPROC FramebufferRenderbuffer = nullptr;
        PFNGLFRAMEBUFFERPARAMETERIPROC FramebufferParameteri = nullptr;
        PFNGLGETFRAMEBUFFERPARAMETERIVPROC GetFramebufferParameteriv = nullptr;
        PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC GetFramebufferAttachmentParameteriv = nullptr;
        PFNGLBLITFRAMEBUFFERPROC BlitFramebuffer = nullptr;
        PFNGLINVALIDATEFRAMEBUFFERPROC InvalidateFramebuffer = nullptr;
        PFNGLINVALIDATESUBFRAMEBUFFERPROC InvalidateSubFramebuffer = nullptr;
        PFNGLGENRENDERBUFFERSPROC GenRenderbuffers = nullptr;
        PFNGLDELETERENDERBUFFERSPROC DeleteRenderbuffers = nullptr;
        PFNGLBINDRENDERBUFFERPROC BindRenderbuffer = nullptr;
        PFNGLISRENDERBUFFERPROC IsRenderbuffer = nullptr;
        PFNGLRENDERBUFFERSTORAGEPROC RenderbufferStorage = nullptr;
        PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC RenderbufferStorageMultisample = nullptr;
        PFNGLGETRENDERBUFFERPARAMETERIVPROC GetRenderbufferParameteriv = nullptr;
        PFNGLGENTRANSFORMFEEDBACKSPROC GenTransformFeedbacks = nullptr;
        PFNGLDELETETRANSFORMFEEDBACKSPROC DeleteTransformFeedbacks = nullptr;
        PFNGLBINDTRANSFORMFEEDBACKPROC BindTransformFeedback = nullptr;
        PFNGLISTRANSFORMFEEDBACKPROC IsTransformFeedback = nullptr;
        PFNGLBEGINTRANSFORMFEEDBACKPROC BeginTransformFeedback = nullptr;
        PFNGLENDTRANSFORMFEEDBACKPROC EndTransformFeedback = nullptr;
        PFNGLPAUSETRANSFORMFEEDBACKPROC PauseTransformFeedback = nullptr;
        PFNGLRESUMETRANSFORMFEEDBACKPROC ResumeTransformFeedback = nullptr;
        PFNGLTRANSFORMFEEDBACKVARYINGSPROC TransformFeedbackVaryings = nullptr;
        PFNGLGETTRANSFORMFEEDBACKVARYINGPROC GetTransformFeedbackVarying = nullptr;
        PFNGLGENQUERIESPROC GenQueries = nullptr;
        PFNGLDELETEQUERIESPROC DeleteQueries = nullptr;
        PFNGLISQUERYPROC IsQuery = nullptr;
        PFNGLBEGINQUERYPROC BeginQuery = nullptr;
        PFNGLENDQUERYPROC EndQuery = nullptr;
        PFNGLGETQUERYIVPROC GetQueryiv = nullptr;
        PFNGLGETQUERYOBJECTUIVPROC GetQueryObjectuiv = nullptr;
        PFNGLFENCESYNCPROC FenceSync = nullptr;
        PFNGLDELETESYNCPROC DeleteSync = nullptr;
        PFNGLISSYNCPROC IsSync = nullptr;
        PFNGLCLIENTWAITSYNCPROC ClientWaitSync = nullptr;
        PFNGLWAITSYNCPROC WaitSync = nullptr;
        PFNGLGETSYNCIVPROC GetSynciv = nullptr;
        PFNGLDISPATCHCOMPUTEPROC DispatchCompute = nullptr;
        PFNGLDISPATCHCOMPUTEINDIRECTPROC DispatchComputeIndirect = nullptr;
        PFNGLMEMORYBARRIERPROC MemoryBarrier = nullptr;
        PFNGLMEMORYBARRIERBYREGIONPROC MemoryBarrierByRegion = nullptr;
        PFNGLGENPROGRAMPIPELINESPROC GenProgramPipelines = nullptr;
        PFNGLDELETEPROGRAMPIPELINESPROC DeleteProgramPipelines = nullptr;
        PFNGLBINDPROGRAMPIPELINEPROC BindProgramPipeline = nullptr;
        PFNGLISPROGRAMPIPELINEPROC IsProgramPipeline = nullptr;
        PFNGLUSEPROGRAMSTAGESPROC UseProgramStages = nullptr;
        PFNGLACTIVESHADERPROGRAMPROC ActiveShaderProgram = nullptr;
        PFNGLCREATESHADERPROGRAMVPROC CreateShaderProgramv = nullptr;
        PFNGLVALIDATEPROGRAMPIPELINEPROC ValidateProgramPipeline = nullptr;
        PFNGLGETPROGRAMPIPELINEIVPROC GetProgramPipelineiv = nullptr;
        PFNGLGETPROGRAMPIPELINEINFOLOGPROC GetProgramPipelineInfoLog = nullptr;
        PFNGLPATCHPARAMETERIPROC PatchParameteri = nullptr;
        PFNGLPRIMITIVEBOUNDINGBOXPROC PrimitiveBoundingBox = nullptr;
        PFNGLDEBUGMESSAGECALLBACKPROC DebugMessageCallback = nullptr;
        PFNGLDEBUGMESSAGECONTROLPROC DebugMessageControl = nullptr;
        PFNGLDEBUGMESSAGEINSERTPROC DebugMessageInsert = nullptr;
        PFNGLGETDEBUGMESSAGELOGPROC GetDebugMessageLog = nullptr;
        PFNGLPUSHDEBUGGROUPPROC PushDebugGroup = nullptr;
        PFNGLPOPDEBUGGROUPPROC PopDebugGroup = nullptr;
        PFNGLOBJECTLABELPROC ObjectLabel = nullptr;
        PFNGLOBJECTPTRLABELPROC ObjectPtrLabel = nullptr;
        PFNGLGETOBJECTLABELPROC GetObjectLabel = nullptr;
        PFNGLGETOBJECTPTRLABELPROC GetObjectPtrLabel = nullptr;
        PFNGLGETGRAPHICSRESETSTATUSPROC GetGraphicsResetStatus = nullptr;
    };

    static GlTable g_gl;

    template <typename T>
    static T load(GlGetProcAddressFn loader, const char* name)
    {
        return reinterpret_cast<T>(loader(name));
    }

    static bool all_loaded(const GlTable& gl)
    {
        return
            gl.Enable != nullptr &&
            gl.Disable != nullptr &&
            gl.Enablei != nullptr &&
            gl.Disablei != nullptr &&
            gl.IsEnabled != nullptr &&
            gl.IsEnabledi != nullptr &&
            gl.BlendFunc != nullptr &&
            gl.BlendFuncSeparate != nullptr &&
            gl.BlendFunci != nullptr &&
            gl.BlendFuncSeparatei != nullptr &&
            gl.BlendEquation != nullptr &&
            gl.BlendEquationSeparate != nullptr &&
            gl.BlendEquationi != nullptr &&
            gl.BlendEquationSeparatei != nullptr &&
            gl.BlendColor != nullptr &&
            gl.BlendBarrier != nullptr &&
            gl.ColorMask != nullptr &&
            gl.ColorMaski != nullptr &&
            gl.DepthFunc != nullptr &&
            gl.DepthMask != nullptr &&
            gl.DepthRangef != nullptr &&
            gl.StencilFunc != nullptr &&
            gl.StencilFuncSeparate != nullptr &&
            gl.StencilOp != nullptr &&
            gl.StencilOpSeparate != nullptr &&
            gl.StencilMask != nullptr &&
            gl.StencilMaskSeparate != nullptr &&
            gl.Scissor != nullptr &&
            gl.Viewport != nullptr &&
            gl.CullFace != nullptr &&
            gl.FrontFace != nullptr &&
            gl.LineWidth != nullptr &&
            gl.PolygonOffset != nullptr &&
            gl.SampleCoverage != nullptr &&
            gl.SampleMaski != nullptr &&
            gl.MinSampleShading != nullptr &&
            gl.Hint != nullptr &&
            gl.PixelStorei != nullptr &&
            gl.Finish != nullptr &&
            gl.Flush != nullptr &&
            gl.GetError != nullptr &&
            gl.GetBooleanv != nullptr &&
            gl.GetIntegerv != nullptr &&
            gl.GetFloatv != nullptr &&
            gl.GetInteger64v != nullptr &&
            gl.GetIntegeri_v != nullptr &&
            gl.GetInteger64i_v != nullptr &&
            gl.GetBooleani_v != nullptr &&
            gl.GetString != nullptr &&
            gl.GetStringi != nullptr &&
            gl.GetPointerv != nullptr &&
            gl.GenBuffers != nullptr &&
            gl.DeleteBuffers != nullptr &&
            gl.BindBuffer != nullptr &&
            gl.BindBufferBase != nullptr &&
            gl.BindBufferRange != nullptr &&
            gl.BufferData != nullptr &&
            gl.BufferSubData != nullptr &&
            gl.CopyBufferSubData != nullptr &&
            gl.MapBufferRange != nullptr &&
            gl.FlushMappedBufferRange != nullptr &&
            gl.UnmapBuffer != nullptr &&
            gl.IsBuffer != nullptr &&
            gl.GetBufferParameteriv != nullptr &&
            gl.GetBufferParameteri64v != nullptr &&
            gl.GetBufferPointerv != nullptr &&
            gl.GenVertexArrays != nullptr &&
            gl.DeleteVertexArrays != nullptr &&
            gl.BindVertexArray != nullptr &&
            gl.IsVertexArray != nullptr &&
            gl.EnableVertexAttribArray != nullptr &&
            gl.DisableVertexAttribArray != nullptr &&
            gl.VertexAttribPointer != nullptr &&
            gl.VertexAttribIPointer != nullptr &&
            gl.VertexAttribDivisor != nullptr &&
            gl.VertexAttrib1f != nullptr &&
            gl.VertexAttrib2f != nullptr &&
            gl.VertexAttrib3f != nullptr &&
            gl.VertexAttrib4f != nullptr &&
            gl.VertexAttrib1fv != nullptr &&
            gl.VertexAttrib2fv != nullptr &&
            gl.VertexAttrib3fv != nullptr &&
            gl.VertexAttrib4fv != nullptr &&
            gl.VertexAttribI4i != nullptr &&
            gl.VertexAttribI4ui != nullptr &&
            gl.VertexAttribI4iv != nullptr &&
            gl.VertexAttribI4uiv != nullptr &&
            gl.GetVertexAttribfv != nullptr &&
            gl.GetVertexAttribiv != nullptr &&
            gl.GetVertexAttribIiv != nullptr &&
            gl.GetVertexAttribIuiv != nullptr &&
            gl.GetVertexAttribPointerv != nullptr &&
            gl.VertexAttribFormat != nullptr &&
            gl.VertexAttribIFormat != nullptr &&
            gl.VertexAttribBinding != nullptr &&
            gl.BindVertexBuffer != nullptr &&
            gl.VertexBindingDivisor != nullptr &&
            gl.DrawArrays != nullptr &&
            gl.DrawArraysInstanced != nullptr &&
            gl.DrawArraysIndirect != nullptr &&
            gl.DrawElements != nullptr &&
            gl.DrawElementsInstanced != nullptr &&
            gl.DrawRangeElements != nullptr &&
            gl.DrawElementsBaseVertex != nullptr &&
            gl.DrawElementsInstancedBaseVertex != nullptr &&
            gl.DrawRangeElementsBaseVertex != nullptr &&
            gl.DrawElementsIndirect != nullptr &&
            gl.DrawBuffers != nullptr &&
            gl.ReadBuffer != nullptr &&
            gl.ReadPixels != nullptr &&
            gl.ReadnPixels != nullptr &&
            gl.Clear != nullptr &&
            gl.ClearColor != nullptr &&
            gl.ClearDepthf != nullptr &&
            gl.ClearStencil != nullptr &&
            gl.ClearBufferfv != nullptr &&
            gl.ClearBufferiv != nullptr &&
            gl.ClearBufferuiv != nullptr &&
            gl.ClearBufferfi != nullptr &&
            gl.CreateShader != nullptr &&
            gl.DeleteShader != nullptr &&
            gl.ShaderSource != nullptr &&
            gl.CompileShader != nullptr &&
            gl.ShaderBinary != nullptr &&
            gl.ReleaseShaderCompiler != nullptr &&
            gl.GetShaderiv != nullptr &&
            gl.GetShaderInfoLog != nullptr &&
            gl.GetShaderSource != nullptr &&
            gl.GetShaderPrecisionFormat != nullptr &&
            gl.IsShader != nullptr &&
            gl.CreateProgram != nullptr &&
            gl.DeleteProgram != nullptr &&
            gl.AttachShader != nullptr &&
            gl.DetachShader != nullptr &&
            gl.LinkProgram != nullptr &&
            gl.UseProgram != nullptr &&
            gl.ValidateProgram != nullptr &&
            gl.GetProgramiv != nullptr &&
            gl.GetProgramInfoLog != nullptr &&
            gl.IsProgram != nullptr &&
            gl.GetAttachedShaders != nullptr &&
            gl.BindAttribLocation != nullptr &&
            gl.GetAttribLocation != nullptr &&
            gl.GetActiveAttrib != nullptr &&
            gl.GetProgramBinary != nullptr &&
            gl.ProgramBinary != nullptr &&
            gl.ProgramParameteri != nullptr &&
            gl.GetFragDataLocation != nullptr &&
            gl.GetProgramInterfaceiv != nullptr &&
            gl.GetProgramResourceIndex != nullptr &&
            gl.GetProgramResourceName != nullptr &&
            gl.GetProgramResourceiv != nullptr &&
            gl.GetProgramResourceLocation != nullptr &&
            gl.GetUniformLocation != nullptr &&
            gl.GetActiveUniform != nullptr &&
            gl.GetActiveUniformsiv != nullptr &&
            gl.GetUniformIndices != nullptr &&
            gl.GetUniformBlockIndex != nullptr &&
            gl.GetActiveUniformBlockiv != nullptr &&
            gl.GetActiveUniformBlockName != nullptr &&
            gl.UniformBlockBinding != nullptr &&
            gl.Uniform1f != nullptr &&
            gl.Uniform2f != nullptr &&
            gl.Uniform3f != nullptr &&
            gl.Uniform4f != nullptr &&
            gl.Uniform1fv != nullptr &&
            gl.Uniform2fv != nullptr &&
            gl.Uniform3fv != nullptr &&
            gl.Uniform4fv != nullptr &&
            gl.Uniform1i != nullptr &&
            gl.Uniform2i != nullptr &&
            gl.Uniform3i != nullptr &&
            gl.Uniform4i != nullptr &&
            gl.Uniform1iv != nullptr &&
            gl.Uniform2iv != nullptr &&
            gl.Uniform3iv != nullptr &&
            gl.Uniform4iv != nullptr &&
            gl.Uniform1ui != nullptr &&
            gl.Uniform2ui != nullptr &&
            gl.Uniform3ui != nullptr &&
            gl.Uniform4ui != nullptr &&
            gl.Uniform1uiv != nullptr &&
            gl.Uniform2uiv != nullptr &&
            gl.Uniform3uiv != nullptr &&
            gl.Uniform4uiv != nullptr &&
            gl.UniformMatrix2fv != nullptr &&
            gl.UniformMatrix3fv != nullptr &&
            gl.UniformMatrix4fv != nullptr &&
            gl.UniformMatrix2x3fv != nullptr &&
            gl.UniformMatrix2x4fv != nullptr &&
            gl.UniformMatrix3x2fv != nullptr &&
            gl.UniformMatrix3x4fv != nullptr &&
            gl.UniformMatrix4x2fv != nullptr &&
            gl.UniformMatrix4x3fv != nullptr &&
            gl.GetUniformfv != nullptr &&
            gl.GetUniformiv != nullptr &&
            gl.GetUniformuiv != nullptr &&
            gl.GetnUniformfv != nullptr &&
            gl.GetnUniformiv != nullptr &&
            gl.GetnUniformuiv != nullptr &&
            gl.ProgramUniform1f != nullptr &&
            gl.ProgramUniform2f != nullptr &&
            gl.ProgramUniform3f != nullptr &&
            gl.ProgramUniform4f != nullptr &&
            gl.ProgramUniform1fv != nullptr &&
            gl.ProgramUniform2fv != nullptr &&
            gl.ProgramUniform3fv != nullptr &&
            gl.ProgramUniform4fv != nullptr &&
            gl.ProgramUniform1i != nullptr &&
            gl.ProgramUniform2i != nullptr &&
            gl.ProgramUniform3i != nullptr &&
            gl.ProgramUniform4i != nullptr &&
            gl.ProgramUniform1iv != nullptr &&
            gl.ProgramUniform2iv != nullptr &&
            gl.ProgramUniform3iv != nullptr &&
            gl.ProgramUniform4iv != nullptr &&
            gl.ProgramUniform1ui != nullptr &&
            gl.ProgramUniform2ui != nullptr &&
            gl.ProgramUniform3ui != nullptr &&
            gl.ProgramUniform4ui != nullptr &&
            gl.ProgramUniform1uiv != nullptr &&
            gl.ProgramUniform2uiv != nullptr &&
            gl.ProgramUniform3uiv != nullptr &&
            gl.ProgramUniform4uiv != nullptr &&
            gl.ProgramUniformMatrix2fv != nullptr &&
            gl.ProgramUniformMatrix3fv != nullptr &&
            gl.ProgramUniformMatrix4fv != nullptr &&
            gl.ProgramUniformMatrix2x3fv != nullptr &&
            gl.ProgramUniformMatrix2x4fv != nullptr &&
            gl.ProgramUniformMatrix3x2fv != nullptr &&
            gl.ProgramUniformMatrix3x4fv != nullptr &&
            gl.ProgramUniformMatrix4x2fv != nullptr &&
            gl.ProgramUniformMatrix4x3fv != nullptr &&
            gl.GenTextures != nullptr &&
            gl.DeleteTextures != nullptr &&
            gl.BindTexture != nullptr &&
            gl.ActiveTexture != nullptr &&
            gl.IsTexture != nullptr &&
            gl.TexImage2D != nullptr &&
            gl.TexImage3D != nullptr &&
            gl.TexSubImage2D != nullptr &&
            gl.TexSubImage3D != nullptr &&
            gl.TexStorage2D != nullptr &&
            gl.TexStorage3D != nullptr &&
            gl.TexStorage2DMultisample != nullptr &&
            gl.TexStorage3DMultisample != nullptr &&
            gl.CompressedTexImage2D != nullptr &&
            gl.CompressedTexImage3D != nullptr &&
            gl.CompressedTexSubImage2D != nullptr &&
            gl.CompressedTexSubImage3D != nullptr &&
            gl.CopyTexImage2D != nullptr &&
            gl.CopyTexSubImage2D != nullptr &&
            gl.CopyTexSubImage3D != nullptr &&
            gl.CopyImageSubData != nullptr &&
            gl.GenerateMipmap != nullptr &&
            gl.TexParameterf != nullptr &&
            gl.TexParameteri != nullptr &&
            gl.TexParameterfv != nullptr &&
            gl.TexParameteriv != nullptr &&
            gl.TexParameterIiv != nullptr &&
            gl.TexParameterIuiv != nullptr &&
            gl.GetTexParameterfv != nullptr &&
            gl.GetTexParameteriv != nullptr &&
            gl.GetTexParameterIiv != nullptr &&
            gl.GetTexParameterIuiv != nullptr &&
            gl.GetTexLevelParameteriv != nullptr &&
            gl.GetTexLevelParameterfv != nullptr &&
            gl.TexBuffer != nullptr &&
            gl.TexBufferRange != nullptr &&
            gl.GetMultisamplefv != nullptr &&
            gl.GetInternalformativ != nullptr &&
            gl.BindImageTexture != nullptr &&
            gl.GenSamplers != nullptr &&
            gl.DeleteSamplers != nullptr &&
            gl.BindSampler != nullptr &&
            gl.IsSampler != nullptr &&
            gl.SamplerParameterf != nullptr &&
            gl.SamplerParameteri != nullptr &&
            gl.SamplerParameterfv != nullptr &&
            gl.SamplerParameteriv != nullptr &&
            gl.SamplerParameterIiv != nullptr &&
            gl.SamplerParameterIuiv != nullptr &&
            gl.GetSamplerParameterfv != nullptr &&
            gl.GetSamplerParameteriv != nullptr &&
            gl.GetSamplerParameterIiv != nullptr &&
            gl.GetSamplerParameterIuiv != nullptr &&
            gl.GenFramebuffers != nullptr &&
            gl.DeleteFramebuffers != nullptr &&
            gl.BindFramebuffer != nullptr &&
            gl.IsFramebuffer != nullptr &&
            gl.CheckFramebufferStatus != nullptr &&
            gl.FramebufferTexture2D != nullptr &&
            gl.FramebufferTextureLayer != nullptr &&
            gl.FramebufferTexture != nullptr &&
            gl.FramebufferRenderbuffer != nullptr &&
            gl.FramebufferParameteri != nullptr &&
            gl.GetFramebufferParameteriv != nullptr &&
            gl.GetFramebufferAttachmentParameteriv != nullptr &&
            gl.BlitFramebuffer != nullptr &&
            gl.InvalidateFramebuffer != nullptr &&
            gl.InvalidateSubFramebuffer != nullptr &&
            gl.GenRenderbuffers != nullptr &&
            gl.DeleteRenderbuffers != nullptr &&
            gl.BindRenderbuffer != nullptr &&
            gl.IsRenderbuffer != nullptr &&
            gl.RenderbufferStorage != nullptr &&
            gl.RenderbufferStorageMultisample != nullptr &&
            gl.GetRenderbufferParameteriv != nullptr &&
            gl.GenTransformFeedbacks != nullptr &&
            gl.DeleteTransformFeedbacks != nullptr &&
            gl.BindTransformFeedback != nullptr &&
            gl.IsTransformFeedback != nullptr &&
            gl.BeginTransformFeedback != nullptr &&
            gl.EndTransformFeedback != nullptr &&
            gl.PauseTransformFeedback != nullptr &&
            gl.ResumeTransformFeedback != nullptr &&
            gl.TransformFeedbackVaryings != nullptr &&
            gl.GetTransformFeedbackVarying != nullptr &&
            gl.GenQueries != nullptr &&
            gl.DeleteQueries != nullptr &&
            gl.IsQuery != nullptr &&
            gl.BeginQuery != nullptr &&
            gl.EndQuery != nullptr &&
            gl.GetQueryiv != nullptr &&
            gl.GetQueryObjectuiv != nullptr &&
            gl.FenceSync != nullptr &&
            gl.DeleteSync != nullptr &&
            gl.IsSync != nullptr &&
            gl.ClientWaitSync != nullptr &&
            gl.WaitSync != nullptr &&
            gl.GetSynciv != nullptr &&
            gl.DispatchCompute != nullptr &&
            gl.DispatchComputeIndirect != nullptr &&
            gl.MemoryBarrier != nullptr &&
            gl.MemoryBarrierByRegion != nullptr &&
            gl.GenProgramPipelines != nullptr &&
            gl.DeleteProgramPipelines != nullptr &&
            gl.BindProgramPipeline != nullptr &&
            gl.IsProgramPipeline != nullptr &&
            gl.UseProgramStages != nullptr &&
            gl.ActiveShaderProgram != nullptr &&
            gl.CreateShaderProgramv != nullptr &&
            gl.ValidateProgramPipeline != nullptr &&
            gl.GetProgramPipelineiv != nullptr &&
            gl.GetProgramPipelineInfoLog != nullptr &&
            gl.PatchParameteri != nullptr &&
            gl.PrimitiveBoundingBox != nullptr &&
            gl.DebugMessageCallback != nullptr &&
            gl.DebugMessageControl != nullptr &&
            gl.DebugMessageInsert != nullptr &&
            gl.GetDebugMessageLog != nullptr &&
            gl.PushDebugGroup != nullptr &&
            gl.PopDebugGroup != nullptr &&
            gl.ObjectLabel != nullptr &&
            gl.ObjectPtrLabel != nullptr &&
            gl.GetObjectLabel != nullptr &&
            gl.GetObjectPtrLabel != nullptr &&
            gl.GetGraphicsResetStatus != nullptr;
    }
}

namespace metagl
{
    bool Initialize(GlGetProcAddressFn loader)
    {
        if (loader == nullptr) return false;

        auto& gl = detail::g_gl;

        gl.Enable = detail::load<PFNGLENABLEPROC>(loader, "glEnable");
        gl.Disable = detail::load<PFNGLDISABLEPROC>(loader, "glDisable");
        gl.Enablei = detail::load<PFNGLENABLEIPROC>(loader, "glEnablei");
        gl.Disablei = detail::load<PFNGLDISABLEIPROC>(loader, "glDisablei");
        gl.IsEnabled = detail::load<PFNGLISENABLEDPROC>(loader, "glIsEnabled");
        gl.IsEnabledi = detail::load<PFNGLISENABLEDIPROC>(loader, "glIsEnabledi");
        gl.BlendFunc = detail::load<PFNGLBLENDFUNCPROC>(loader, "glBlendFunc");
        gl.BlendFuncSeparate = detail::load<PFNGLBLENDFUNCSEPARATEPROC>(loader, "glBlendFuncSeparate");
        gl.BlendFunci = detail::load<PFNGLBLENDFUNCIPROC>(loader, "glBlendFunci");
        gl.BlendFuncSeparatei = detail::load<PFNGLBLENDFUNCSEPARATEIPROC>(loader, "glBlendFuncSeparatei");
        gl.BlendEquation = detail::load<PFNGLBLENDEQUATIONPROC>(loader, "glBlendEquation");
        gl.BlendEquationSeparate = detail::load<PFNGLBLENDEQUATIONSEPARATEPROC>(loader, "glBlendEquationSeparate");
        gl.BlendEquationi = detail::load<PFNGLBLENDEQUATIONIPROC>(loader, "glBlendEquationi");
        gl.BlendEquationSeparatei = detail::load<PFNGLBLENDEQUATIONSEPARATEIPROC>(loader, "glBlendEquationSeparatei");
        gl.BlendColor = detail::load<PFNGLBLENDCOLORPROC>(loader, "glBlendColor");
        gl.BlendBarrier = detail::load<PFNGLBLENDBARRIERPROC>(loader, "glBlendBarrier");
        gl.ColorMask = detail::load<PFNGLCOLORMASKPROC>(loader, "glColorMask");
        gl.ColorMaski = detail::load<PFNGLCOLORMASKIPROC>(loader, "glColorMaski");
        gl.DepthFunc = detail::load<PFNGLDEPTHFUNCPROC>(loader, "glDepthFunc");
        gl.DepthMask = detail::load<PFNGLDEPTHMASKPROC>(loader, "glDepthMask");
        gl.DepthRangef = detail::load<PFNGLDEPTHRANGEFPROC>(loader, "glDepthRangef");
        gl.StencilFunc = detail::load<PFNGLSTENCILFUNCPROC>(loader, "glStencilFunc");
        gl.StencilFuncSeparate = detail::load<PFNGLSTENCILFUNCSEPARATEPROC>(loader, "glStencilFuncSeparate");
        gl.StencilOp = detail::load<PFNGLSTENCILOPPROC>(loader, "glStencilOp");
        gl.StencilOpSeparate = detail::load<PFNGLSTENCILOPSEPARATEPROC>(loader, "glStencilOpSeparate");
        gl.StencilMask = detail::load<PFNGLSTENCILMASKPROC>(loader, "glStencilMask");
        gl.StencilMaskSeparate = detail::load<PFNGLSTENCILMASKSEPARATEPROC>(loader, "glStencilMaskSeparate");
        gl.Scissor = detail::load<PFNGLSCISSORPROC>(loader, "glScissor");
        gl.Viewport = detail::load<PFNGLVIEWPORTPROC>(loader, "glViewport");
        gl.CullFace = detail::load<PFNGLCULLFACEPROC>(loader, "glCullFace");
        gl.FrontFace = detail::load<PFNGLFRONTFACEPROC>(loader, "glFrontFace");
        gl.LineWidth = detail::load<PFNGLLINEWIDTHPROC>(loader, "glLineWidth");
        gl.PolygonOffset = detail::load<PFNGLPOLYGONOFFSETPROC>(loader, "glPolygonOffset");
        gl.SampleCoverage = detail::load<PFNGLSAMPLECOVERAGEPROC>(loader, "glSampleCoverage");
        gl.SampleMaski = detail::load<PFNGLSAMPLEMASKIPROC>(loader, "glSampleMaski");
        gl.MinSampleShading = detail::load<PFNGLMINSAMPLESHADINGPROC>(loader, "glMinSampleShading");
        gl.Hint = detail::load<PFNGLHINTPROC>(loader, "glHint");
        gl.PixelStorei = detail::load<PFNGLPIXELSTOREIPROC>(loader, "glPixelStorei");
        gl.Finish = detail::load<PFNGLFINISHPROC>(loader, "glFinish");
        gl.Flush = detail::load<PFNGLFLUSHPROC>(loader, "glFlush");
        gl.GetError = detail::load<PFNGLGETERRORPROC>(loader, "glGetError");
        gl.GetBooleanv = detail::load<PFNGLGETBOOLEANVPROC>(loader, "glGetBooleanv");
        gl.GetIntegerv = detail::load<PFNGLGETINTEGERVPROC>(loader, "glGetIntegerv");
        gl.GetFloatv = detail::load<PFNGLGETFLOATVPROC>(loader, "glGetFloatv");
        gl.GetInteger64v = detail::load<PFNGLGETINTEGER64VPROC>(loader, "glGetInteger64v");
        gl.GetIntegeri_v = detail::load<PFNGLGETINTEGERI_VPROC>(loader, "glGetIntegeri_v");
        gl.GetInteger64i_v = detail::load<PFNGLGETINTEGER64I_VPROC>(loader, "glGetInteger64i_v");
        gl.GetBooleani_v = detail::load<PFNGLGETBOOLEANI_VPROC>(loader, "glGetBooleani_v");
        gl.GetString = detail::load<PFNGLGETSTRINGPROC>(loader, "glGetString");
        gl.GetStringi = detail::load<PFNGLGETSTRINGIPROC>(loader, "glGetStringi");
        gl.GetPointerv = detail::load<PFNGLGETPOINTERVPROC>(loader, "glGetPointerv");
        gl.GenBuffers = detail::load<PFNGLGENBUFFERSPROC>(loader, "glGenBuffers");
        gl.DeleteBuffers = detail::load<PFNGLDELETEBUFFERSPROC>(loader, "glDeleteBuffers");
        gl.BindBuffer = detail::load<PFNGLBINDBUFFERPROC>(loader, "glBindBuffer");
        gl.BindBufferBase = detail::load<PFNGLBINDBUFFERBASEPROC>(loader, "glBindBufferBase");
        gl.BindBufferRange = detail::load<PFNGLBINDBUFFERRANGEPROC>(loader, "glBindBufferRange");
        gl.BufferData = detail::load<PFNGLBUFFERDATAPROC>(loader, "glBufferData");
        gl.BufferSubData = detail::load<PFNGLBUFFERSUBDATAPROC>(loader, "glBufferSubData");
        gl.CopyBufferSubData = detail::load<PFNGLCOPYBUFFERSUBDATAPROC>(loader, "glCopyBufferSubData");
        gl.MapBufferRange = detail::load<PFNGLMAPBUFFERRANGEPROC>(loader, "glMapBufferRange");
        gl.FlushMappedBufferRange = detail::load<PFNGLFLUSHMAPPEDBUFFERRANGEPROC>(loader, "glFlushMappedBufferRange");
        gl.UnmapBuffer = detail::load<PFNGLUNMAPBUFFERPROC>(loader, "glUnmapBuffer");
        gl.IsBuffer = detail::load<PFNGLISBUFFERPROC>(loader, "glIsBuffer");
        gl.GetBufferParameteriv = detail::load<PFNGLGETBUFFERPARAMETERIVPROC>(loader, "glGetBufferParameteriv");
        gl.GetBufferParameteri64v = detail::load<PFNGLGETBUFFERPARAMETERI64VPROC>(loader, "glGetBufferParameteri64v");
        gl.GetBufferPointerv = detail::load<PFNGLGETBUFFERPOINTERVPROC>(loader, "glGetBufferPointerv");
        gl.GenVertexArrays = detail::load<PFNGLGENVERTEXARRAYSPROC>(loader, "glGenVertexArrays");
        gl.DeleteVertexArrays = detail::load<PFNGLDELETEVERTEXARRAYSPROC>(loader, "glDeleteVertexArrays");
        gl.BindVertexArray = detail::load<PFNGLBINDVERTEXARRAYPROC>(loader, "glBindVertexArray");
        gl.IsVertexArray = detail::load<PFNGLISVERTEXARRAYPROC>(loader, "glIsVertexArray");
        gl.EnableVertexAttribArray = detail::load<PFNGLENABLEVERTEXATTRIBARRAYPROC>(loader, "glEnableVertexAttribArray");
        gl.DisableVertexAttribArray = detail::load<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(loader, "glDisableVertexAttribArray");
        gl.VertexAttribPointer = detail::load<PFNGLVERTEXATTRIBPOINTERPROC>(loader, "glVertexAttribPointer");
        gl.VertexAttribIPointer = detail::load<PFNGLVERTEXATTRIBIPOINTERPROC>(loader, "glVertexAttribIPointer");
        gl.VertexAttribDivisor = detail::load<PFNGLVERTEXATTRIBDIVISORPROC>(loader, "glVertexAttribDivisor");
        gl.VertexAttrib1f = detail::load<PFNGLVERTEXATTRIB1FPROC>(loader, "glVertexAttrib1f");
        gl.VertexAttrib2f = detail::load<PFNGLVERTEXATTRIB2FPROC>(loader, "glVertexAttrib2f");
        gl.VertexAttrib3f = detail::load<PFNGLVERTEXATTRIB3FPROC>(loader, "glVertexAttrib3f");
        gl.VertexAttrib4f = detail::load<PFNGLVERTEXATTRIB4FPROC>(loader, "glVertexAttrib4f");
        gl.VertexAttrib1fv = detail::load<PFNGLVERTEXATTRIB1FVPROC>(loader, "glVertexAttrib1fv");
        gl.VertexAttrib2fv = detail::load<PFNGLVERTEXATTRIB2FVPROC>(loader, "glVertexAttrib2fv");
        gl.VertexAttrib3fv = detail::load<PFNGLVERTEXATTRIB3FVPROC>(loader, "glVertexAttrib3fv");
        gl.VertexAttrib4fv = detail::load<PFNGLVERTEXATTRIB4FVPROC>(loader, "glVertexAttrib4fv");
        gl.VertexAttribI4i = detail::load<PFNGLVERTEXATTRIBI4IPROC>(loader, "glVertexAttribI4i");
        gl.VertexAttribI4ui = detail::load<PFNGLVERTEXATTRIBI4UIPROC>(loader, "glVertexAttribI4ui");
        gl.VertexAttribI4iv = detail::load<PFNGLVERTEXATTRIBI4IVPROC>(loader, "glVertexAttribI4iv");
        gl.VertexAttribI4uiv = detail::load<PFNGLVERTEXATTRIBI4UIVPROC>(loader, "glVertexAttribI4uiv");
        gl.GetVertexAttribfv = detail::load<PFNGLGETVERTEXATTRIBFVPROC>(loader, "glGetVertexAttribfv");
        gl.GetVertexAttribiv = detail::load<PFNGLGETVERTEXATTRIBIVPROC>(loader, "glGetVertexAttribiv");
        gl.GetVertexAttribIiv = detail::load<PFNGLGETVERTEXATTRIBIIVPROC>(loader, "glGetVertexAttribIiv");
        gl.GetVertexAttribIuiv = detail::load<PFNGLGETVERTEXATTRIBIUIVPROC>(loader, "glGetVertexAttribIuiv");
        gl.GetVertexAttribPointerv = detail::load<PFNGLGETVERTEXATTRIBPOINTERVPROC>(loader, "glGetVertexAttribPointerv");
        gl.VertexAttribFormat = detail::load<PFNGLVERTEXATTRIBFORMATPROC>(loader, "glVertexAttribFormat");
        gl.VertexAttribIFormat = detail::load<PFNGLVERTEXATTRIBIFORMATPROC>(loader, "glVertexAttribIFormat");
        gl.VertexAttribBinding = detail::load<PFNGLVERTEXATTRIBBINDINGPROC>(loader, "glVertexAttribBinding");
        gl.BindVertexBuffer = detail::load<PFNGLBINDVERTEXBUFFERPROC>(loader, "glBindVertexBuffer");
        gl.VertexBindingDivisor = detail::load<PFNGLVERTEXBINDINGDIVISORPROC>(loader, "glVertexBindingDivisor");
        gl.DrawArrays = detail::load<PFNGLDRAWARRAYSPROC>(loader, "glDrawArrays");
        gl.DrawArraysInstanced = detail::load<PFNGLDRAWARRAYSINSTANCEDPROC>(loader, "glDrawArraysInstanced");
        gl.DrawArraysIndirect = detail::load<PFNGLDRAWARRAYSINDIRECTPROC>(loader, "glDrawArraysIndirect");
        gl.DrawElements = detail::load<PFNGLDRAWELEMENTSPROC>(loader, "glDrawElements");
        gl.DrawElementsInstanced = detail::load<PFNGLDRAWELEMENTSINSTANCEDPROC>(loader, "glDrawElementsInstanced");
        gl.DrawRangeElements = detail::load<PFNGLDRAWRANGEELEMENTSPROC>(loader, "glDrawRangeElements");
        gl.DrawElementsBaseVertex = detail::load<PFNGLDRAWELEMENTSBASEVERTEXPROC>(loader, "glDrawElementsBaseVertex");
        gl.DrawElementsInstancedBaseVertex = detail::load<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC>(loader, "glDrawElementsInstancedBaseVertex");
        gl.DrawRangeElementsBaseVertex = detail::load<PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC>(loader, "glDrawRangeElementsBaseVertex");
        gl.DrawElementsIndirect = detail::load<PFNGLDRAWELEMENTSINDIRECTPROC>(loader, "glDrawElementsIndirect");
        gl.DrawBuffers = detail::load<PFNGLDRAWBUFFERSPROC>(loader, "glDrawBuffers");
        gl.ReadBuffer = detail::load<PFNGLREADBUFFERPROC>(loader, "glReadBuffer");
        gl.ReadPixels = detail::load<PFNGLREADPIXELSPROC>(loader, "glReadPixels");
        gl.ReadnPixels = detail::load<PFNGLREADNPIXELSPROC>(loader, "glReadnPixels");
        gl.Clear = detail::load<PFNGLCLEARPROC>(loader, "glClear");
        gl.ClearColor = detail::load<PFNGLCLEARCOLORPROC>(loader, "glClearColor");
        gl.ClearDepthf = detail::load<PFNGLCLEARDEPTHFPROC>(loader, "glClearDepthf");
        gl.ClearStencil = detail::load<PFNGLCLEARSTENCILPROC>(loader, "glClearStencil");
        gl.ClearBufferfv = detail::load<PFNGLCLEARBUFFERFVPROC>(loader, "glClearBufferfv");
        gl.ClearBufferiv = detail::load<PFNGLCLEARBUFFERIVPROC>(loader, "glClearBufferiv");
        gl.ClearBufferuiv = detail::load<PFNGLCLEARBUFFERUIVPROC>(loader, "glClearBufferuiv");
        gl.ClearBufferfi = detail::load<PFNGLCLEARBUFFERFIPROC>(loader, "glClearBufferfi");
        gl.CreateShader = detail::load<PFNGLCREATESHADERPROC>(loader, "glCreateShader");
        gl.DeleteShader = detail::load<PFNGLDELETESHADERPROC>(loader, "glDeleteShader");
        gl.ShaderSource = detail::load<PFNGLSHADERSOURCEPROC>(loader, "glShaderSource");
        gl.CompileShader = detail::load<PFNGLCOMPILESHADERPROC>(loader, "glCompileShader");
        gl.ShaderBinary = detail::load<PFNGLSHADERBINARYPROC>(loader, "glShaderBinary");
        gl.ReleaseShaderCompiler = detail::load<PFNGLRELEASESHADERCOMPILERPROC>(loader, "glReleaseShaderCompiler");
        gl.GetShaderiv = detail::load<PFNGLGETSHADERIVPROC>(loader, "glGetShaderiv");
        gl.GetShaderInfoLog = detail::load<PFNGLGETSHADERINFOLOGPROC>(loader, "glGetShaderInfoLog");
        gl.GetShaderSource = detail::load<PFNGLGETSHADERSOURCEPROC>(loader, "glGetShaderSource");
        gl.GetShaderPrecisionFormat = detail::load<PFNGLGETSHADERPRECISIONFORMATPROC>(loader, "glGetShaderPrecisionFormat");
        gl.IsShader = detail::load<PFNGLISSHADERPROC>(loader, "glIsShader");
        gl.CreateProgram = detail::load<PFNGLCREATEPROGRAMPROC>(loader, "glCreateProgram");
        gl.DeleteProgram = detail::load<PFNGLDELETEPROGRAMPROC>(loader, "glDeleteProgram");
        gl.AttachShader = detail::load<PFNGLATTACHSHADERPROC>(loader, "glAttachShader");
        gl.DetachShader = detail::load<PFNGLDETACHSHADERPROC>(loader, "glDetachShader");
        gl.LinkProgram = detail::load<PFNGLLINKPROGRAMPROC>(loader, "glLinkProgram");
        gl.UseProgram = detail::load<PFNGLUSEPROGRAMPROC>(loader, "glUseProgram");
        gl.ValidateProgram = detail::load<PFNGLVALIDATEPROGRAMPROC>(loader, "glValidateProgram");
        gl.GetProgramiv = detail::load<PFNGLGETPROGRAMIVPROC>(loader, "glGetProgramiv");
        gl.GetProgramInfoLog = detail::load<PFNGLGETPROGRAMINFOLOGPROC>(loader, "glGetProgramInfoLog");
        gl.IsProgram = detail::load<PFNGLISPROGRAMPROC>(loader, "glIsProgram");
        gl.GetAttachedShaders = detail::load<PFNGLGETATTACHEDSHADERSPROC>(loader, "glGetAttachedShaders");
        gl.BindAttribLocation = detail::load<PFNGLBINDATTRIBLOCATIONPROC>(loader, "glBindAttribLocation");
        gl.GetAttribLocation = detail::load<PFNGLGETATTRIBLOCATIONPROC>(loader, "glGetAttribLocation");
        gl.GetActiveAttrib = detail::load<PFNGLGETACTIVEATTRIBPROC>(loader, "glGetActiveAttrib");
        gl.GetProgramBinary = detail::load<PFNGLGETPROGRAMBINARYPROC>(loader, "glGetProgramBinary");
        gl.ProgramBinary = detail::load<PFNGLPROGRAMBINARYPROC>(loader, "glProgramBinary");
        gl.ProgramParameteri = detail::load<PFNGLPROGRAMPARAMETERIPROC>(loader, "glProgramParameteri");
        gl.GetFragDataLocation = detail::load<PFNGLGETFRAGDATALOCATIONPROC>(loader, "glGetFragDataLocation");
        gl.GetProgramInterfaceiv = detail::load<PFNGLGETPROGRAMINTERFACEIVPROC>(loader, "glGetProgramInterfaceiv");
        gl.GetProgramResourceIndex = detail::load<PFNGLGETPROGRAMRESOURCEINDEXPROC>(loader, "glGetProgramResourceIndex");
        gl.GetProgramResourceName = detail::load<PFNGLGETPROGRAMRESOURCENAMEPROC>(loader, "glGetProgramResourceName");
        gl.GetProgramResourceiv = detail::load<PFNGLGETPROGRAMRESOURCEIVPROC>(loader, "glGetProgramResourceiv");
        gl.GetProgramResourceLocation = detail::load<PFNGLGETPROGRAMRESOURCELOCATIONPROC>(loader, "glGetProgramResourceLocation");
        gl.GetUniformLocation = detail::load<PFNGLGETUNIFORMLOCATIONPROC>(loader, "glGetUniformLocation");
        gl.GetActiveUniform = detail::load<PFNGLGETACTIVEUNIFORMPROC>(loader, "glGetActiveUniform");
        gl.GetActiveUniformsiv = detail::load<PFNGLGETACTIVEUNIFORMSIVPROC>(loader, "glGetActiveUniformsiv");
        gl.GetUniformIndices = detail::load<PFNGLGETUNIFORMINDICESPROC>(loader, "glGetUniformIndices");
        gl.GetUniformBlockIndex = detail::load<PFNGLGETUNIFORMBLOCKINDEXPROC>(loader, "glGetUniformBlockIndex");
        gl.GetActiveUniformBlockiv = detail::load<PFNGLGETACTIVEUNIFORMBLOCKIVPROC>(loader, "glGetActiveUniformBlockiv");
        gl.GetActiveUniformBlockName = detail::load<PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC>(loader, "glGetActiveUniformBlockName");
        gl.UniformBlockBinding = detail::load<PFNGLUNIFORMBLOCKBINDINGPROC>(loader, "glUniformBlockBinding");
        gl.Uniform1f = detail::load<PFNGLUNIFORM1FPROC>(loader, "glUniform1f");
        gl.Uniform2f = detail::load<PFNGLUNIFORM2FPROC>(loader, "glUniform2f");
        gl.Uniform3f = detail::load<PFNGLUNIFORM3FPROC>(loader, "glUniform3f");
        gl.Uniform4f = detail::load<PFNGLUNIFORM4FPROC>(loader, "glUniform4f");
        gl.Uniform1fv = detail::load<PFNGLUNIFORM1FVPROC>(loader, "glUniform1fv");
        gl.Uniform2fv = detail::load<PFNGLUNIFORM2FVPROC>(loader, "glUniform2fv");
        gl.Uniform3fv = detail::load<PFNGLUNIFORM3FVPROC>(loader, "glUniform3fv");
        gl.Uniform4fv = detail::load<PFNGLUNIFORM4FVPROC>(loader, "glUniform4fv");
        gl.Uniform1i = detail::load<PFNGLUNIFORM1IPROC>(loader, "glUniform1i");
        gl.Uniform2i = detail::load<PFNGLUNIFORM2IPROC>(loader, "glUniform2i");
        gl.Uniform3i = detail::load<PFNGLUNIFORM3IPROC>(loader, "glUniform3i");
        gl.Uniform4i = detail::load<PFNGLUNIFORM4IPROC>(loader, "glUniform4i");
        gl.Uniform1iv = detail::load<PFNGLUNIFORM1IVPROC>(loader, "glUniform1iv");
        gl.Uniform2iv = detail::load<PFNGLUNIFORM2IVPROC>(loader, "glUniform2iv");
        gl.Uniform3iv = detail::load<PFNGLUNIFORM3IVPROC>(loader, "glUniform3iv");
        gl.Uniform4iv = detail::load<PFNGLUNIFORM4IVPROC>(loader, "glUniform4iv");
        gl.Uniform1ui = detail::load<PFNGLUNIFORM1UIPROC>(loader, "glUniform1ui");
        gl.Uniform2ui = detail::load<PFNGLUNIFORM2UIPROC>(loader, "glUniform2ui");
        gl.Uniform3ui = detail::load<PFNGLUNIFORM3UIPROC>(loader, "glUniform3ui");
        gl.Uniform4ui = detail::load<PFNGLUNIFORM4UIPROC>(loader, "glUniform4ui");
        gl.Uniform1uiv = detail::load<PFNGLUNIFORM1UIVPROC>(loader, "glUniform1uiv");
        gl.Uniform2uiv = detail::load<PFNGLUNIFORM2UIVPROC>(loader, "glUniform2uiv");
        gl.Uniform3uiv = detail::load<PFNGLUNIFORM3UIVPROC>(loader, "glUniform3uiv");
        gl.Uniform4uiv = detail::load<PFNGLUNIFORM4UIVPROC>(loader, "glUniform4uiv");
        gl.UniformMatrix2fv = detail::load<PFNGLUNIFORMMATRIX2FVPROC>(loader, "glUniformMatrix2fv");
        gl.UniformMatrix3fv = detail::load<PFNGLUNIFORMMATRIX3FVPROC>(loader, "glUniformMatrix3fv");
        gl.UniformMatrix4fv = detail::load<PFNGLUNIFORMMATRIX4FVPROC>(loader, "glUniformMatrix4fv");
        gl.UniformMatrix2x3fv = detail::load<PFNGLUNIFORMMATRIX2X3FVPROC>(loader, "glUniformMatrix2x3fv");
        gl.UniformMatrix2x4fv = detail::load<PFNGLUNIFORMMATRIX2X4FVPROC>(loader, "glUniformMatrix2x4fv");
        gl.UniformMatrix3x2fv = detail::load<PFNGLUNIFORMMATRIX3X2FVPROC>(loader, "glUniformMatrix3x2fv");
        gl.UniformMatrix3x4fv = detail::load<PFNGLUNIFORMMATRIX3X4FVPROC>(loader, "glUniformMatrix3x4fv");
        gl.UniformMatrix4x2fv = detail::load<PFNGLUNIFORMMATRIX4X2FVPROC>(loader, "glUniformMatrix4x2fv");
        gl.UniformMatrix4x3fv = detail::load<PFNGLUNIFORMMATRIX4X3FVPROC>(loader, "glUniformMatrix4x3fv");
        gl.GetUniformfv = detail::load<PFNGLGETUNIFORMFVPROC>(loader, "glGetUniformfv");
        gl.GetUniformiv = detail::load<PFNGLGETUNIFORMIVPROC>(loader, "glGetUniformiv");
        gl.GetUniformuiv = detail::load<PFNGLGETUNIFORMUIVPROC>(loader, "glGetUniformuiv");
        gl.GetnUniformfv = detail::load<PFNGLGETNUNIFORMFVPROC>(loader, "glGetnUniformfv");
        gl.GetnUniformiv = detail::load<PFNGLGETNUNIFORMIVPROC>(loader, "glGetnUniformiv");
        gl.GetnUniformuiv = detail::load<PFNGLGETNUNIFORMUIVPROC>(loader, "glGetnUniformuiv");
        gl.ProgramUniform1f = detail::load<PFNGLPROGRAMUNIFORM1FPROC>(loader, "glProgramUniform1f");
        gl.ProgramUniform2f = detail::load<PFNGLPROGRAMUNIFORM2FPROC>(loader, "glProgramUniform2f");
        gl.ProgramUniform3f = detail::load<PFNGLPROGRAMUNIFORM3FPROC>(loader, "glProgramUniform3f");
        gl.ProgramUniform4f = detail::load<PFNGLPROGRAMUNIFORM4FPROC>(loader, "glProgramUniform4f");
        gl.ProgramUniform1fv = detail::load<PFNGLPROGRAMUNIFORM1FVPROC>(loader, "glProgramUniform1fv");
        gl.ProgramUniform2fv = detail::load<PFNGLPROGRAMUNIFORM2FVPROC>(loader, "glProgramUniform2fv");
        gl.ProgramUniform3fv = detail::load<PFNGLPROGRAMUNIFORM3FVPROC>(loader, "glProgramUniform3fv");
        gl.ProgramUniform4fv = detail::load<PFNGLPROGRAMUNIFORM4FVPROC>(loader, "glProgramUniform4fv");
        gl.ProgramUniform1i = detail::load<PFNGLPROGRAMUNIFORM1IPROC>(loader, "glProgramUniform1i");
        gl.ProgramUniform2i = detail::load<PFNGLPROGRAMUNIFORM2IPROC>(loader, "glProgramUniform2i");
        gl.ProgramUniform3i = detail::load<PFNGLPROGRAMUNIFORM3IPROC>(loader, "glProgramUniform3i");
        gl.ProgramUniform4i = detail::load<PFNGLPROGRAMUNIFORM4IPROC>(loader, "glProgramUniform4i");
        gl.ProgramUniform1iv = detail::load<PFNGLPROGRAMUNIFORM1IVPROC>(loader, "glProgramUniform1iv");
        gl.ProgramUniform2iv = detail::load<PFNGLPROGRAMUNIFORM2IVPROC>(loader, "glProgramUniform2iv");
        gl.ProgramUniform3iv = detail::load<PFNGLPROGRAMUNIFORM3IVPROC>(loader, "glProgramUniform3iv");
        gl.ProgramUniform4iv = detail::load<PFNGLPROGRAMUNIFORM4IVPROC>(loader, "glProgramUniform4iv");
        gl.ProgramUniform1ui = detail::load<PFNGLPROGRAMUNIFORM1UIPROC>(loader, "glProgramUniform1ui");
        gl.ProgramUniform2ui = detail::load<PFNGLPROGRAMUNIFORM2UIPROC>(loader, "glProgramUniform2ui");
        gl.ProgramUniform3ui = detail::load<PFNGLPROGRAMUNIFORM3UIPROC>(loader, "glProgramUniform3ui");
        gl.ProgramUniform4ui = detail::load<PFNGLPROGRAMUNIFORM4UIPROC>(loader, "glProgramUniform4ui");
        gl.ProgramUniform1uiv = detail::load<PFNGLPROGRAMUNIFORM1UIVPROC>(loader, "glProgramUniform1uiv");
        gl.ProgramUniform2uiv = detail::load<PFNGLPROGRAMUNIFORM2UIVPROC>(loader, "glProgramUniform2uiv");
        gl.ProgramUniform3uiv = detail::load<PFNGLPROGRAMUNIFORM3UIVPROC>(loader, "glProgramUniform3uiv");
        gl.ProgramUniform4uiv = detail::load<PFNGLPROGRAMUNIFORM4UIVPROC>(loader, "glProgramUniform4uiv");
        gl.ProgramUniformMatrix2fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX2FVPROC>(loader, "glProgramUniformMatrix2fv");
        gl.ProgramUniformMatrix3fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX3FVPROC>(loader, "glProgramUniformMatrix3fv");
        gl.ProgramUniformMatrix4fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX4FVPROC>(loader, "glProgramUniformMatrix4fv");
        gl.ProgramUniformMatrix2x3fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC>(loader, "glProgramUniformMatrix2x3fv");
        gl.ProgramUniformMatrix2x4fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC>(loader, "glProgramUniformMatrix2x4fv");
        gl.ProgramUniformMatrix3x2fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC>(loader, "glProgramUniformMatrix3x2fv");
        gl.ProgramUniformMatrix3x4fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC>(loader, "glProgramUniformMatrix3x4fv");
        gl.ProgramUniformMatrix4x2fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC>(loader, "glProgramUniformMatrix4x2fv");
        gl.ProgramUniformMatrix4x3fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC>(loader, "glProgramUniformMatrix4x3fv");
        gl.GenTextures = detail::load<PFNGLGENTEXTURESPROC>(loader, "glGenTextures");
        gl.DeleteTextures = detail::load<PFNGLDELETETEXTURESPROC>(loader, "glDeleteTextures");
        gl.BindTexture = detail::load<PFNGLBINDTEXTUREPROC>(loader, "glBindTexture");
        gl.ActiveTexture = detail::load<PFNGLACTIVETEXTUREPROC>(loader, "glActiveTexture");
        gl.IsTexture = detail::load<PFNGLISTEXTUREPROC>(loader, "glIsTexture");
        gl.TexImage2D = detail::load<PFNGLTEXIMAGE2DPROC>(loader, "glTexImage2D");
        gl.TexImage3D = detail::load<PFNGLTEXIMAGE3DPROC>(loader, "glTexImage3D");
        gl.TexSubImage2D = detail::load<PFNGLTEXSUBIMAGE2DPROC>(loader, "glTexSubImage2D");
        gl.TexSubImage3D = detail::load<PFNGLTEXSUBIMAGE3DPROC>(loader, "glTexSubImage3D");
        gl.TexStorage2D = detail::load<PFNGLTEXSTORAGE2DPROC>(loader, "glTexStorage2D");
        gl.TexStorage3D = detail::load<PFNGLTEXSTORAGE3DPROC>(loader, "glTexStorage3D");
        gl.TexStorage2DMultisample = detail::load<PFNGLTEXSTORAGE2DMULTISAMPLEPROC>(loader, "glTexStorage2DMultisample");
        gl.TexStorage3DMultisample = detail::load<PFNGLTEXSTORAGE3DMULTISAMPLEPROC>(loader, "glTexStorage3DMultisample");
        gl.CompressedTexImage2D = detail::load<PFNGLCOMPRESSEDTEXIMAGE2DPROC>(loader, "glCompressedTexImage2D");
        gl.CompressedTexImage3D = detail::load<PFNGLCOMPRESSEDTEXIMAGE3DPROC>(loader, "glCompressedTexImage3D");
        gl.CompressedTexSubImage2D = detail::load<PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC>(loader, "glCompressedTexSubImage2D");
        gl.CompressedTexSubImage3D = detail::load<PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC>(loader, "glCompressedTexSubImage3D");
        gl.CopyTexImage2D = detail::load<PFNGLCOPYTEXIMAGE2DPROC>(loader, "glCopyTexImage2D");
        gl.CopyTexSubImage2D = detail::load<PFNGLCOPYTEXSUBIMAGE2DPROC>(loader, "glCopyTexSubImage2D");
        gl.CopyTexSubImage3D = detail::load<PFNGLCOPYTEXSUBIMAGE3DPROC>(loader, "glCopyTexSubImage3D");
        gl.CopyImageSubData = detail::load<PFNGLCOPYIMAGESUBDATAPROC>(loader, "glCopyImageSubData");
        gl.GenerateMipmap = detail::load<PFNGLGENERATEMIPMAPPROC>(loader, "glGenerateMipmap");
        gl.TexParameterf = detail::load<PFNGLTEXPARAMETERFPROC>(loader, "glTexParameterf");
        gl.TexParameteri = detail::load<PFNGLTEXPARAMETERIPROC>(loader, "glTexParameteri");
        gl.TexParameterfv = detail::load<PFNGLTEXPARAMETERFVPROC>(loader, "glTexParameterfv");
        gl.TexParameteriv = detail::load<PFNGLTEXPARAMETERIVPROC>(loader, "glTexParameteriv");
        gl.TexParameterIiv = detail::load<PFNGLTEXPARAMETERIIVPROC>(loader, "glTexParameterIiv");
        gl.TexParameterIuiv = detail::load<PFNGLTEXPARAMETERIUIVPROC>(loader, "glTexParameterIuiv");
        gl.GetTexParameterfv = detail::load<PFNGLGETTEXPARAMETERFVPROC>(loader, "glGetTexParameterfv");
        gl.GetTexParameteriv = detail::load<PFNGLGETTEXPARAMETERIVPROC>(loader, "glGetTexParameteriv");
        gl.GetTexParameterIiv = detail::load<PFNGLGETTEXPARAMETERIIVPROC>(loader, "glGetTexParameterIiv");
        gl.GetTexParameterIuiv = detail::load<PFNGLGETTEXPARAMETERIUIVPROC>(loader, "glGetTexParameterIuiv");
        gl.GetTexLevelParameteriv = detail::load<PFNGLGETTEXLEVELPARAMETERIVPROC>(loader, "glGetTexLevelParameteriv");
        gl.GetTexLevelParameterfv = detail::load<PFNGLGETTEXLEVELPARAMETERFVPROC>(loader, "glGetTexLevelParameterfv");
        gl.TexBuffer = detail::load<PFNGLTEXBUFFERPROC>(loader, "glTexBuffer");
        gl.TexBufferRange = detail::load<PFNGLTEXBUFFERRANGEPROC>(loader, "glTexBufferRange");
        gl.GetMultisamplefv = detail::load<PFNGLGETMULTISAMPLEFVPROC>(loader, "glGetMultisamplefv");
        gl.GetInternalformativ = detail::load<PFNGLGETINTERNALFORMATIVPROC>(loader, "glGetInternalformativ");
        gl.BindImageTexture = detail::load<PFNGLBINDIMAGETEXTUREPROC>(loader, "glBindImageTexture");
        gl.GenSamplers = detail::load<PFNGLGENSAMPLERSPROC>(loader, "glGenSamplers");
        gl.DeleteSamplers = detail::load<PFNGLDELETESAMPLERSPROC>(loader, "glDeleteSamplers");
        gl.BindSampler = detail::load<PFNGLBINDSAMPLERPROC>(loader, "glBindSampler");
        gl.IsSampler = detail::load<PFNGLISSAMPLERPROC>(loader, "glIsSampler");
        gl.SamplerParameterf = detail::load<PFNGLSAMPLERPARAMETERFPROC>(loader, "glSamplerParameterf");
        gl.SamplerParameteri = detail::load<PFNGLSAMPLERPARAMETERIPROC>(loader, "glSamplerParameteri");
        gl.SamplerParameterfv = detail::load<PFNGLSAMPLERPARAMETERFVPROC>(loader, "glSamplerParameterfv");
        gl.SamplerParameteriv = detail::load<PFNGLSAMPLERPARAMETERIVPROC>(loader, "glSamplerParameteriv");
        gl.SamplerParameterIiv = detail::load<PFNGLSAMPLERPARAMETERIIVPROC>(loader, "glSamplerParameterIiv");
        gl.SamplerParameterIuiv = detail::load<PFNGLSAMPLERPARAMETERIUIVPROC>(loader, "glSamplerParameterIuiv");
        gl.GetSamplerParameterfv = detail::load<PFNGLGETSAMPLERPARAMETERFVPROC>(loader, "glGetSamplerParameterfv");
        gl.GetSamplerParameteriv = detail::load<PFNGLGETSAMPLERPARAMETERIVPROC>(loader, "glGetSamplerParameteriv");
        gl.GetSamplerParameterIiv = detail::load<PFNGLGETSAMPLERPARAMETERIIVPROC>(loader, "glGetSamplerParameterIiv");
        gl.GetSamplerParameterIuiv = detail::load<PFNGLGETSAMPLERPARAMETERIUIVPROC>(loader, "glGetSamplerParameterIuiv");
        gl.GenFramebuffers = detail::load<PFNGLGENFRAMEBUFFERSPROC>(loader, "glGenFramebuffers");
        gl.DeleteFramebuffers = detail::load<PFNGLDELETEFRAMEBUFFERSPROC>(loader, "glDeleteFramebuffers");
        gl.BindFramebuffer = detail::load<PFNGLBINDFRAMEBUFFERPROC>(loader, "glBindFramebuffer");
        gl.IsFramebuffer = detail::load<PFNGLISFRAMEBUFFERPROC>(loader, "glIsFramebuffer");
        gl.CheckFramebufferStatus = detail::load<PFNGLCHECKFRAMEBUFFERSTATUSPROC>(loader, "glCheckFramebufferStatus");
        gl.FramebufferTexture2D = detail::load<PFNGLFRAMEBUFFERTEXTURE2DPROC>(loader, "glFramebufferTexture2D");
        gl.FramebufferTextureLayer = detail::load<PFNGLFRAMEBUFFERTEXTURELAYERPROC>(loader, "glFramebufferTextureLayer");
        gl.FramebufferTexture = detail::load<PFNGLFRAMEBUFFERTEXTUREPROC>(loader, "glFramebufferTexture");
        gl.FramebufferRenderbuffer = detail::load<PFNGLFRAMEBUFFERRENDERBUFFERPROC>(loader, "glFramebufferRenderbuffer");
        gl.FramebufferParameteri = detail::load<PFNGLFRAMEBUFFERPARAMETERIPROC>(loader, "glFramebufferParameteri");
        gl.GetFramebufferParameteriv = detail::load<PFNGLGETFRAMEBUFFERPARAMETERIVPROC>(loader, "glGetFramebufferParameteriv");
        gl.GetFramebufferAttachmentParameteriv = detail::load<PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC>(loader, "glGetFramebufferAttachmentParameteriv");
        gl.BlitFramebuffer = detail::load<PFNGLBLITFRAMEBUFFERPROC>(loader, "glBlitFramebuffer");
        gl.InvalidateFramebuffer = detail::load<PFNGLINVALIDATEFRAMEBUFFERPROC>(loader, "glInvalidateFramebuffer");
        gl.InvalidateSubFramebuffer = detail::load<PFNGLINVALIDATESUBFRAMEBUFFERPROC>(loader, "glInvalidateSubFramebuffer");
        gl.GenRenderbuffers = detail::load<PFNGLGENRENDERBUFFERSPROC>(loader, "glGenRenderbuffers");
        gl.DeleteRenderbuffers = detail::load<PFNGLDELETERENDERBUFFERSPROC>(loader, "glDeleteRenderbuffers");
        gl.BindRenderbuffer = detail::load<PFNGLBINDRENDERBUFFERPROC>(loader, "glBindRenderbuffer");
        gl.IsRenderbuffer = detail::load<PFNGLISRENDERBUFFERPROC>(loader, "glIsRenderbuffer");
        gl.RenderbufferStorage = detail::load<PFNGLRENDERBUFFERSTORAGEPROC>(loader, "glRenderbufferStorage");
        gl.RenderbufferStorageMultisample = detail::load<PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC>(loader, "glRenderbufferStorageMultisample");
        gl.GetRenderbufferParameteriv = detail::load<PFNGLGETRENDERBUFFERPARAMETERIVPROC>(loader, "glGetRenderbufferParameteriv");
        gl.GenTransformFeedbacks = detail::load<PFNGLGENTRANSFORMFEEDBACKSPROC>(loader, "glGenTransformFeedbacks");
        gl.DeleteTransformFeedbacks = detail::load<PFNGLDELETETRANSFORMFEEDBACKSPROC>(loader, "glDeleteTransformFeedbacks");
        gl.BindTransformFeedback = detail::load<PFNGLBINDTRANSFORMFEEDBACKPROC>(loader, "glBindTransformFeedback");
        gl.IsTransformFeedback = detail::load<PFNGLISTRANSFORMFEEDBACKPROC>(loader, "glIsTransformFeedback");
        gl.BeginTransformFeedback = detail::load<PFNGLBEGINTRANSFORMFEEDBACKPROC>(loader, "glBeginTransformFeedback");
        gl.EndTransformFeedback = detail::load<PFNGLENDTRANSFORMFEEDBACKPROC>(loader, "glEndTransformFeedback");
        gl.PauseTransformFeedback = detail::load<PFNGLPAUSETRANSFORMFEEDBACKPROC>(loader, "glPauseTransformFeedback");
        gl.ResumeTransformFeedback = detail::load<PFNGLRESUMETRANSFORMFEEDBACKPROC>(loader, "glResumeTransformFeedback");
        gl.TransformFeedbackVaryings = detail::load<PFNGLTRANSFORMFEEDBACKVARYINGSPROC>(loader, "glTransformFeedbackVaryings");
        gl.GetTransformFeedbackVarying = detail::load<PFNGLGETTRANSFORMFEEDBACKVARYINGPROC>(loader, "glGetTransformFeedbackVarying");
        gl.GenQueries = detail::load<PFNGLGENQUERIESPROC>(loader, "glGenQueries");
        gl.DeleteQueries = detail::load<PFNGLDELETEQUERIESPROC>(loader, "glDeleteQueries");
        gl.IsQuery = detail::load<PFNGLISQUERYPROC>(loader, "glIsQuery");
        gl.BeginQuery = detail::load<PFNGLBEGINQUERYPROC>(loader, "glBeginQuery");
        gl.EndQuery = detail::load<PFNGLENDQUERYPROC>(loader, "glEndQuery");
        gl.GetQueryiv = detail::load<PFNGLGETQUERYIVPROC>(loader, "glGetQueryiv");
        gl.GetQueryObjectuiv = detail::load<PFNGLGETQUERYOBJECTUIVPROC>(loader, "glGetQueryObjectuiv");
        gl.FenceSync = detail::load<PFNGLFENCESYNCPROC>(loader, "glFenceSync");
        gl.DeleteSync = detail::load<PFNGLDELETESYNCPROC>(loader, "glDeleteSync");
        gl.IsSync = detail::load<PFNGLISSYNCPROC>(loader, "glIsSync");
        gl.ClientWaitSync = detail::load<PFNGLCLIENTWAITSYNCPROC>(loader, "glClientWaitSync");
        gl.WaitSync = detail::load<PFNGLWAITSYNCPROC>(loader, "glWaitSync");
        gl.GetSynciv = detail::load<PFNGLGETSYNCIVPROC>(loader, "glGetSynciv");
        gl.DispatchCompute = detail::load<PFNGLDISPATCHCOMPUTEPROC>(loader, "glDispatchCompute");
        gl.DispatchComputeIndirect = detail::load<PFNGLDISPATCHCOMPUTEINDIRECTPROC>(loader, "glDispatchComputeIndirect");
        gl.MemoryBarrier = detail::load<PFNGLMEMORYBARRIERPROC>(loader, "glMemoryBarrier");
        gl.MemoryBarrierByRegion = detail::load<PFNGLMEMORYBARRIERBYREGIONPROC>(loader, "glMemoryBarrierByRegion");
        gl.GenProgramPipelines = detail::load<PFNGLGENPROGRAMPIPELINESPROC>(loader, "glGenProgramPipelines");
        gl.DeleteProgramPipelines = detail::load<PFNGLDELETEPROGRAMPIPELINESPROC>(loader, "glDeleteProgramPipelines");
        gl.BindProgramPipeline = detail::load<PFNGLBINDPROGRAMPIPELINEPROC>(loader, "glBindProgramPipeline");
        gl.IsProgramPipeline = detail::load<PFNGLISPROGRAMPIPELINEPROC>(loader, "glIsProgramPipeline");
        gl.UseProgramStages = detail::load<PFNGLUSEPROGRAMSTAGESPROC>(loader, "glUseProgramStages");
        gl.ActiveShaderProgram = detail::load<PFNGLACTIVESHADERPROGRAMPROC>(loader, "glActiveShaderProgram");
        gl.CreateShaderProgramv = detail::load<PFNGLCREATESHADERPROGRAMVPROC>(loader, "glCreateShaderProgramv");
        gl.ValidateProgramPipeline = detail::load<PFNGLVALIDATEPROGRAMPIPELINEPROC>(loader, "glValidateProgramPipeline");
        gl.GetProgramPipelineiv = detail::load<PFNGLGETPROGRAMPIPELINEIVPROC>(loader, "glGetProgramPipelineiv");
        gl.GetProgramPipelineInfoLog = detail::load<PFNGLGETPROGRAMPIPELINEINFOLOGPROC>(loader, "glGetProgramPipelineInfoLog");
        gl.PatchParameteri = detail::load<PFNGLPATCHPARAMETERIPROC>(loader, "glPatchParameteri");
        gl.PrimitiveBoundingBox = detail::load<PFNGLPRIMITIVEBOUNDINGBOXPROC>(loader, "glPrimitiveBoundingBox");
        gl.DebugMessageCallback = detail::load<PFNGLDEBUGMESSAGECALLBACKPROC>(loader, "glDebugMessageCallback");
        gl.DebugMessageControl = detail::load<PFNGLDEBUGMESSAGECONTROLPROC>(loader, "glDebugMessageControl");
        gl.DebugMessageInsert = detail::load<PFNGLDEBUGMESSAGEINSERTPROC>(loader, "glDebugMessageInsert");
        gl.GetDebugMessageLog = detail::load<PFNGLGETDEBUGMESSAGELOGPROC>(loader, "glGetDebugMessageLog");
        gl.PushDebugGroup = detail::load<PFNGLPUSHDEBUGGROUPPROC>(loader, "glPushDebugGroup");
        gl.PopDebugGroup = detail::load<PFNGLPOPDEBUGGROUPPROC>(loader, "glPopDebugGroup");
        gl.ObjectLabel = detail::load<PFNGLOBJECTLABELPROC>(loader, "glObjectLabel");
        gl.ObjectPtrLabel = detail::load<PFNGLOBJECTPTRLABELPROC>(loader, "glObjectPtrLabel");
        gl.GetObjectLabel = detail::load<PFNGLGETOBJECTLABELPROC>(loader, "glGetObjectLabel");
        gl.GetObjectPtrLabel = detail::load<PFNGLGETOBJECTPTRLABELPROC>(loader, "glGetObjectPtrLabel");
        gl.GetGraphicsResetStatus = detail::load<PFNGLGETGRAPHICSRESETSTATUSPROC>(loader, "glGetGraphicsResetStatus");

        gl.initialized = detail::all_loaded(gl);
        return gl.initialized;
    }

    bool IsInitialized()
    {
        return detail::g_gl.initialized;
    }

    // #1
    void glEnable(Capability cap)
    {
        detail::g_gl.Enable(detail::to_gl_enum(cap));
    }

    // #2
    void glDisable(Capability cap)
    {
        detail::g_gl.Disable(detail::to_gl_enum(cap));
    }

    // #3
    void glEnablei(Capability target, GLuint index)
    {
        detail::g_gl.Enablei(detail::to_gl_enum(target), index);
    }

    // #4
    void glDisablei(Capability target, GLuint index)
    {
        detail::g_gl.Disablei(detail::to_gl_enum(target), index);
    }

    // #5
    GLboolean glIsEnabled(Capability cap)
    {
        return detail::g_gl.IsEnabled(detail::to_gl_enum(cap));
    }

    // #6
    GLboolean glIsEnabledi(Capability target, GLuint index)
    {
        return detail::g_gl.IsEnabledi(detail::to_gl_enum(target), index);
    }

    // #7
    void glBlendFunc(BlendFactor sfactor, BlendFactor dfactor)
    {
        detail::g_gl.BlendFunc(detail::to_gl_enum(sfactor), detail::to_gl_enum(dfactor));
    }

    // #8
    void glBlendFuncSeparate(BlendFactor sfactorRGB, BlendFactor dfactorRGB, BlendFactor sfactorAlpha, BlendFactor dfactorAlpha)
    {
        detail::g_gl.BlendFuncSeparate(detail::to_gl_enum(sfactorRGB), detail::to_gl_enum(dfactorRGB), detail::to_gl_enum(sfactorAlpha), detail::to_gl_enum(dfactorAlpha));
    }

    // #9
    void glBlendFunci(GLuint buf, BlendFactor src, BlendFactor dst)
    {
        detail::g_gl.BlendFunci(buf, detail::to_gl_enum(src), detail::to_gl_enum(dst));
    }

    // #10
    void glBlendFuncSeparatei(GLuint buf, BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha)
    {
        detail::g_gl.BlendFuncSeparatei(buf, detail::to_gl_enum(srcRGB), detail::to_gl_enum(dstRGB), detail::to_gl_enum(srcAlpha), detail::to_gl_enum(dstAlpha));
    }

    // #11
    void glBlendEquation(BlendEquation mode)
    {
        detail::g_gl.BlendEquation(detail::to_gl_enum(mode));
    }

    // #12
    void glBlendEquationSeparate(BlendEquation modeRGB, BlendEquation modeAlpha)
    {
        detail::g_gl.BlendEquationSeparate(detail::to_gl_enum(modeRGB), detail::to_gl_enum(modeAlpha));
    }

    // #13
    void glBlendEquationi(GLuint buf, BlendEquation mode)
    {
        detail::g_gl.BlendEquationi(buf, detail::to_gl_enum(mode));
    }

    // #14
    void glBlendEquationSeparatei(GLuint buf, BlendEquation modeRGB, BlendEquation modeAlpha)
    {
        detail::g_gl.BlendEquationSeparatei(buf, detail::to_gl_enum(modeRGB), detail::to_gl_enum(modeAlpha));
    }

    // #15
    void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        detail::g_gl.BlendColor(red, green, blue, alpha);
    }

    // #16
    void glBlendBarrier(void)
    {
        detail::g_gl.BlendBarrier();
    }

    // #17
    void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
    {
        detail::g_gl.ColorMask(red, green, blue, alpha);
    }

    // #18
    void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
    {
        detail::g_gl.ColorMaski(index, r, g, b, a);
    }

    // #19
    void glDepthFunc(CompareFunc func)
    {
        detail::g_gl.DepthFunc(detail::to_gl_enum(func));
    }

    // #20
    void glDepthMask(GLboolean flag)
    {
        detail::g_gl.DepthMask(flag);
    }

    // #21
    void glDepthRangef(GLfloat n, GLfloat f)
    {
        detail::g_gl.DepthRangef(n, f);
    }

    // #22
    void glStencilFunc(CompareFunc func, GLint ref, GLuint mask)
    {
        detail::g_gl.StencilFunc(detail::to_gl_enum(func), ref, mask);
    }

    // #23
    void glStencilFuncSeparate(CullFace face, CompareFunc func, GLint ref, GLuint mask)
    {
        detail::g_gl.StencilFuncSeparate(detail::to_gl_enum(face), detail::to_gl_enum(func), ref, mask);
    }

    // #24
    void glStencilOp(StencilOp fail, StencilOp zfail, StencilOp zpass)
    {
        detail::g_gl.StencilOp(detail::to_gl_enum(fail), detail::to_gl_enum(zfail), detail::to_gl_enum(zpass));
    }

    // #25
    void glStencilOpSeparate(CullFace face, StencilOp sfail, StencilOp dpfail, StencilOp dppass)
    {
        detail::g_gl.StencilOpSeparate(detail::to_gl_enum(face), detail::to_gl_enum(sfail), detail::to_gl_enum(dpfail), detail::to_gl_enum(dppass));
    }

    // #26
    void glStencilMask(GLuint mask)
    {
        detail::g_gl.StencilMask(mask);
    }

    // #27
    void glStencilMaskSeparate(CullFace face, GLuint mask)
    {
        detail::g_gl.StencilMaskSeparate(detail::to_gl_enum(face), mask);
    }

    // #28
    void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
    {
        detail::g_gl.Scissor(x, y, width, height);
    }

    // #29
    void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
    {
        detail::g_gl.Viewport(x, y, width, height);
    }

    // #30
    void glCullFace(CullFace mode)
    {
        detail::g_gl.CullFace(detail::to_gl_enum(mode));
    }

    // #31
    void glFrontFace(FrontFace mode)
    {
        detail::g_gl.FrontFace(detail::to_gl_enum(mode));
    }

    // #32
    void glLineWidth(GLfloat width)
    {
        detail::g_gl.LineWidth(width);
    }

    // #33
    void glPolygonOffset(GLfloat factor, GLfloat units)
    {
        detail::g_gl.PolygonOffset(factor, units);
    }

    // #34
    void glSampleCoverage(GLfloat value, GLboolean invert)
    {
        detail::g_gl.SampleCoverage(value, invert);
    }

    // #35
    void glSampleMaski(GLuint maskNumber, GLbitfield mask)
    {
        detail::g_gl.SampleMaski(maskNumber, mask);
    }

    // #36
    void glMinSampleShading(GLfloat value)
    {
        detail::g_gl.MinSampleShading(value);
    }

    // #37
    void glHint(HintTarget target, HintMode mode)
    {
        detail::g_gl.Hint(detail::to_gl_enum(target), detail::to_gl_enum(mode));
    }

    // #38
    void glPixelStorei(PixelStoreParam pname, GLint param)
    {
        detail::g_gl.PixelStorei(detail::to_gl_enum(pname), param);
    }

    // #39
    void glFinish(void)
    {
        detail::g_gl.Finish();
    }

    // #40
    void glFlush(void)
    {
        detail::g_gl.Flush();
    }

    // #41
    ErrorCode glGetError(void)
    {
        return static_cast<ErrorCode>(detail::g_gl.GetError());
    }

    // #42
    void glGetBooleanv(GetParameter pname, GLboolean * data)
    {
        detail::g_gl.GetBooleanv(detail::to_gl_enum(pname), data);
    }

    // #43
    void glGetIntegerv(GetParameter pname, GLint * data)
    {
        detail::g_gl.GetIntegerv(detail::to_gl_enum(pname), data);
    }

    // #44
    void glGetFloatv(GetParameter pname, GLfloat * data)
    {
        detail::g_gl.GetFloatv(detail::to_gl_enum(pname), data);
    }

    // #45
    void glGetInteger64v(GetParameter pname, GLint64 * data)
    {
        detail::g_gl.GetInteger64v(detail::to_gl_enum(pname), data);
    }

    // #46
    void glGetIntegeri_v(GetParameter target, GLuint index, GLint * data)
    {
        detail::g_gl.GetIntegeri_v(detail::to_gl_enum(target), index, data);
    }

    // #47
    void glGetInteger64i_v(GetParameter target, GLuint index, GLint64 * data)
    {
        detail::g_gl.GetInteger64i_v(detail::to_gl_enum(target), index, data);
    }

    // #48
    void glGetBooleani_v(GetParameter target, GLuint index, GLboolean * data)
    {
        detail::g_gl.GetBooleani_v(detail::to_gl_enum(target), index, data);
    }

    // #49
    const GLubyte* glGetString(StringName name)
    {
        return detail::g_gl.GetString(detail::to_gl_enum(name));
    }

    // #50
    const GLubyte* glGetStringi(StringName name, GLuint index)
    {
        return detail::g_gl.GetStringi(detail::to_gl_enum(name), index);
    }

    // #51
    void glGetPointerv(GetPointerParameter pname, void ** params)
    {
        detail::g_gl.GetPointerv(detail::to_gl_enum(pname), params);
    }

    // #52
    void glGenBuffers(GLsizei n, GLuint * buffers)
    {
        detail::g_gl.GenBuffers(n, buffers);
    }

    // #53
    void glDeleteBuffers(GLsizei n, const GLuint * buffers)
    {
        detail::g_gl.DeleteBuffers(n, buffers);
    }

    // #54
    void glBindBuffer(BufferTarget target, GLuint buffer)
    {
        detail::g_gl.BindBuffer(detail::to_gl_enum(target), buffer);
    }

    // #55
    void glBindBufferBase(BufferTarget target, GLuint index, GLuint buffer)
    {
        detail::g_gl.BindBufferBase(detail::to_gl_enum(target), index, buffer);
    }

    // #56
    void glBindBufferRange(BufferTarget target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
    {
        detail::g_gl.BindBufferRange(detail::to_gl_enum(target), index, buffer, offset, size);
    }

    // #57
    void glBufferData(BufferTarget target, GLsizeiptr size, const void * data, BufferUsage usage)
    {
        detail::g_gl.BufferData(detail::to_gl_enum(target), size, data, detail::to_gl_enum(usage));
    }

    // #58
    void glBufferSubData(BufferTarget target, GLintptr offset, GLsizeiptr size, const void * data)
    {
        detail::g_gl.BufferSubData(detail::to_gl_enum(target), offset, size, data);
    }

    // #59
    void glCopyBufferSubData(BufferTarget readTarget, BufferTarget writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
    {
        detail::g_gl.CopyBufferSubData(detail::to_gl_enum(readTarget), detail::to_gl_enum(writeTarget), readOffset, writeOffset, size);
    }

    // #60
    void* glMapBufferRange(BufferTarget target, GLintptr offset, GLsizeiptr length, MapBufferAccessMask access)
    {
        return detail::g_gl.MapBufferRange(detail::to_gl_enum(target), offset, length, detail::to_gl_bitfield(access));
    }

    // #61
    void glFlushMappedBufferRange(BufferTarget target, GLintptr offset, GLsizeiptr length)
    {
        detail::g_gl.FlushMappedBufferRange(detail::to_gl_enum(target), offset, length);
    }

    // #62
    GLboolean glUnmapBuffer(BufferTarget target)
    {
        return detail::g_gl.UnmapBuffer(detail::to_gl_enum(target));
    }

    // #63
    GLboolean glIsBuffer(GLuint buffer)
    {
        return detail::g_gl.IsBuffer(buffer);
    }

    // #64
    void glGetBufferParameteriv(BufferTarget target, BufferParameter pname, GLint * params)
    {
        detail::g_gl.GetBufferParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #65
    void glGetBufferParameteri64v(BufferTarget target, BufferParameter pname, GLint64 * params)
    {
        detail::g_gl.GetBufferParameteri64v(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #66
    void glGetBufferPointerv(BufferTarget target, BufferParameter pname, void ** params)
    {
        detail::g_gl.GetBufferPointerv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #67
    void glGenVertexArrays(GLsizei n, GLuint * arrays)
    {
        detail::g_gl.GenVertexArrays(n, arrays);
    }

    // #68
    void glDeleteVertexArrays(GLsizei n, const GLuint * arrays)
    {
        detail::g_gl.DeleteVertexArrays(n, arrays);
    }

    // #69
    void glBindVertexArray(GLuint array)
    {
        detail::g_gl.BindVertexArray(array);
    }

    // #70
    GLboolean glIsVertexArray(GLuint array)
    {
        return detail::g_gl.IsVertexArray(array);
    }

    // #71
    void glEnableVertexAttribArray(GLuint index)
    {
        detail::g_gl.EnableVertexAttribArray(index);
    }

    // #72
    void glDisableVertexAttribArray(GLuint index)
    {
        detail::g_gl.DisableVertexAttribArray(index);
    }

    // #73
    void glVertexAttribPointer(GLuint index, GLint size, DataType type, GLboolean normalized, GLsizei stride, const void * pointer)
    {
        detail::g_gl.VertexAttribPointer(index, size, detail::to_gl_enum(type), normalized, stride, pointer);
    }

    // #74
    void glVertexAttribIPointer(GLuint index, GLint size, DataType type, GLsizei stride, const void * pointer)
    {
        detail::g_gl.VertexAttribIPointer(index, size, detail::to_gl_enum(type), stride, pointer);
    }

    // #75
    void glVertexAttribDivisor(GLuint index, GLuint divisor)
    {
        detail::g_gl.VertexAttribDivisor(index, divisor);
    }

    // #76
    void glVertexAttrib1f(GLuint index, GLfloat x)
    {
        detail::g_gl.VertexAttrib1f(index, x);
    }

    // #77
    void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
    {
        detail::g_gl.VertexAttrib2f(index, x, y);
    }

    // #78
    void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
    {
        detail::g_gl.VertexAttrib3f(index, x, y, z);
    }

    // #79
    void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
        detail::g_gl.VertexAttrib4f(index, x, y, z, w);
    }

    // #80
    void glVertexAttrib1fv(GLuint index, const GLfloat * v)
    {
        detail::g_gl.VertexAttrib1fv(index, v);
    }

    // #81
    void glVertexAttrib2fv(GLuint index, const GLfloat * v)
    {
        detail::g_gl.VertexAttrib2fv(index, v);
    }

    // #82
    void glVertexAttrib3fv(GLuint index, const GLfloat * v)
    {
        detail::g_gl.VertexAttrib3fv(index, v);
    }

    // #83
    void glVertexAttrib4fv(GLuint index, const GLfloat * v)
    {
        detail::g_gl.VertexAttrib4fv(index, v);
    }

    // #84
    void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
    {
        detail::g_gl.VertexAttribI4i(index, x, y, z, w);
    }

    // #85
    void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
    {
        detail::g_gl.VertexAttribI4ui(index, x, y, z, w);
    }

    // #86
    void glVertexAttribI4iv(GLuint index, const GLint * v)
    {
        detail::g_gl.VertexAttribI4iv(index, v);
    }

    // #87
    void glVertexAttribI4uiv(GLuint index, const GLuint * v)
    {
        detail::g_gl.VertexAttribI4uiv(index, v);
    }

    // #88
    void glGetVertexAttribfv(GLuint index, VertexAttribParameter pname, GLfloat * params)
    {
        detail::g_gl.GetVertexAttribfv(index, detail::to_gl_enum(pname), params);
    }

    // #89
    void glGetVertexAttribiv(GLuint index, VertexAttribParameter pname, GLint * params)
    {
        detail::g_gl.GetVertexAttribiv(index, detail::to_gl_enum(pname), params);
    }

    // #90
    void glGetVertexAttribIiv(GLuint index, VertexAttribParameter pname, GLint * params)
    {
        detail::g_gl.GetVertexAttribIiv(index, detail::to_gl_enum(pname), params);
    }

    // #91
    void glGetVertexAttribIuiv(GLuint index, VertexAttribParameter pname, GLuint * params)
    {
        detail::g_gl.GetVertexAttribIuiv(index, detail::to_gl_enum(pname), params);
    }

    // #92
    void glGetVertexAttribPointerv(GLuint index, VertexAttribParameter pname, void ** pointer)
    {
        detail::g_gl.GetVertexAttribPointerv(index, detail::to_gl_enum(pname), pointer);
    }

    // #93
    void glVertexAttribFormat(GLuint attribindex, GLint size, DataType type, GLboolean normalized, GLuint relativeoffset)
    {
        detail::g_gl.VertexAttribFormat(attribindex, size, detail::to_gl_enum(type), normalized, relativeoffset);
    }

    // #94
    void glVertexAttribIFormat(GLuint attribindex, GLint size, DataType type, GLuint relativeoffset)
    {
        detail::g_gl.VertexAttribIFormat(attribindex, size, detail::to_gl_enum(type), relativeoffset);
    }

    // #95
    void glVertexAttribBinding(GLuint attribindex, GLuint bindingindex)
    {
        detail::g_gl.VertexAttribBinding(attribindex, bindingindex);
    }

    // #96
    void glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
    {
        detail::g_gl.BindVertexBuffer(bindingindex, buffer, offset, stride);
    }

    // #97
    void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor)
    {
        detail::g_gl.VertexBindingDivisor(bindingindex, divisor);
    }

    // #98
    void glDrawArrays(PrimitiveType mode, GLint first, GLsizei count)
    {
        detail::g_gl.DrawArrays(detail::to_gl_enum(mode), first, count);
    }

    // #99
    void glDrawArraysInstanced(PrimitiveType mode, GLint first, GLsizei count, GLsizei instancecount)
    {
        detail::g_gl.DrawArraysInstanced(detail::to_gl_enum(mode), first, count, instancecount);
    }

    // #100
    void glDrawArraysIndirect(PrimitiveType mode, const void * indirect)
    {
        detail::g_gl.DrawArraysIndirect(detail::to_gl_enum(mode), indirect);
    }

    // #101
    void glDrawElements(PrimitiveType mode, GLsizei count, DataType type, const void * indices)
    {
        detail::g_gl.DrawElements(detail::to_gl_enum(mode), count, detail::to_gl_enum(type), indices);
    }

    // #102
    void glDrawElementsInstanced(PrimitiveType mode, GLsizei count, DataType type, const void * indices, GLsizei instancecount)
    {
        detail::g_gl.DrawElementsInstanced(detail::to_gl_enum(mode), count, detail::to_gl_enum(type), indices, instancecount);
    }

    // #103
    void glDrawRangeElements(PrimitiveType mode, GLuint start, GLuint end, GLsizei count, DataType type, const void * indices)
    {
        detail::g_gl.DrawRangeElements(detail::to_gl_enum(mode), start, end, count, detail::to_gl_enum(type), indices);
    }

    // #104
    void glDrawElementsBaseVertex(PrimitiveType mode, GLsizei count, DataType type, const void * indices, GLint basevertex)
    {
        detail::g_gl.DrawElementsBaseVertex(detail::to_gl_enum(mode), count, detail::to_gl_enum(type), indices, basevertex);
    }

    // #105
    void glDrawElementsInstancedBaseVertex(PrimitiveType mode, GLsizei count, DataType type, const void * indices, GLsizei instancecount, GLint basevertex)
    {
        detail::g_gl.DrawElementsInstancedBaseVertex(detail::to_gl_enum(mode), count, detail::to_gl_enum(type), indices, instancecount, basevertex);
    }

    // #106
    void glDrawRangeElementsBaseVertex(PrimitiveType mode, GLuint start, GLuint end, GLsizei count, DataType type, const void * indices, GLint basevertex)
    {
        detail::g_gl.DrawRangeElementsBaseVertex(detail::to_gl_enum(mode), start, end, count, detail::to_gl_enum(type), indices, basevertex);
    }

    // #107
    void glDrawElementsIndirect(PrimitiveType mode, DataType type, const void * indirect)
    {
        detail::g_gl.DrawElementsIndirect(detail::to_gl_enum(mode), detail::to_gl_enum(type), indirect);
    }

    // #108
    void glDrawBuffers(GLsizei n, const DrawBuffer * bufs)
    {
        detail::g_gl.DrawBuffers(n, reinterpret_cast<const GLenum *>(bufs));
    }

    // #109
    void glReadBuffer(ReadBuffer src)
    {
        detail::g_gl.ReadBuffer(detail::to_gl_enum(src));
    }

    // #110
    void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, PixelFormat format, PixelType type, void * pixels)
    {
        detail::g_gl.ReadPixels(x, y, width, height, detail::to_gl_enum(format), detail::to_gl_enum(type), pixels);
    }

    // #111
    void glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, PixelFormat format, PixelType type, GLsizei bufSize, void * data)
    {
        detail::g_gl.ReadnPixels(x, y, width, height, detail::to_gl_enum(format), detail::to_gl_enum(type), bufSize, data);
    }

    // #112
    void glClear(ClearBufferBit mask)
    {
        detail::g_gl.Clear(detail::to_gl_bitfield(mask));
    }

    // #113
    void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        detail::g_gl.ClearColor(red, green, blue, alpha);
    }

    // #114
    void glClearDepthf(GLfloat d)
    {
        detail::g_gl.ClearDepthf(d);
    }

    // #115
    void glClearStencil(GLint s)
    {
        detail::g_gl.ClearStencil(s);
    }

    // #116
    void glClearBufferfv(ClearBuffer buffer, GLint drawbuffer, const GLfloat * value)
    {
        detail::g_gl.ClearBufferfv(detail::to_gl_enum(buffer), drawbuffer, value);
    }

    // #117
    void glClearBufferiv(ClearBuffer buffer, GLint drawbuffer, const GLint * value)
    {
        detail::g_gl.ClearBufferiv(detail::to_gl_enum(buffer), drawbuffer, value);
    }

    // #118
    void glClearBufferuiv(ClearBuffer buffer, GLint drawbuffer, const GLuint * value)
    {
        detail::g_gl.ClearBufferuiv(detail::to_gl_enum(buffer), drawbuffer, value);
    }

    // #119
    void glClearBufferfi(ClearBuffer buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
    {
        detail::g_gl.ClearBufferfi(detail::to_gl_enum(buffer), drawbuffer, depth, stencil);
    }

    // #120
    GLuint glCreateShader(ShaderType type)
    {
        return detail::g_gl.CreateShader(detail::to_gl_enum(type));
    }

    // #121
    void glDeleteShader(GLuint shader)
    {
        detail::g_gl.DeleteShader(shader);
    }

    // #122
    void glShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length)
    {
        detail::g_gl.ShaderSource(shader, count, string, length);
    }

    // #123
    void glCompileShader(GLuint shader)
    {
        detail::g_gl.CompileShader(shader);
    }

    // #124
    void glShaderBinary(GLsizei count, const GLuint * shaders, ShaderBinaryFormat binaryFormat, const void * binary, GLsizei length)
    {
        detail::g_gl.ShaderBinary(count, shaders, detail::to_gl_enum(binaryFormat), binary, length);
    }

    // #125
    void glReleaseShaderCompiler(void)
    {
        detail::g_gl.ReleaseShaderCompiler();
    }

    // #126
    void glGetShaderiv(GLuint shader, ShaderParameter pname, GLint * params)
    {
        detail::g_gl.GetShaderiv(shader, detail::to_gl_enum(pname), params);
    }

    // #127
    void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
    {
        detail::g_gl.GetShaderInfoLog(shader, bufSize, length, infoLog);
    }

    // #128
    void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source)
    {
        detail::g_gl.GetShaderSource(shader, bufSize, length, source);
    }

    // #129
    void glGetShaderPrecisionFormat(ShaderType shadertype, PrecisionType precisiontype, GLint * range, GLint * precision)
    {
        detail::g_gl.GetShaderPrecisionFormat(detail::to_gl_enum(shadertype), detail::to_gl_enum(precisiontype), range, precision);
    }

    // #130
    GLboolean glIsShader(GLuint shader)
    {
        return detail::g_gl.IsShader(shader);
    }

    // #131
    GLuint glCreateProgram(void)
    {
        return detail::g_gl.CreateProgram();
    }

    // #132
    void glDeleteProgram(GLuint program)
    {
        detail::g_gl.DeleteProgram(program);
    }

    // #133
    void glAttachShader(GLuint program, GLuint shader)
    {
        detail::g_gl.AttachShader(program, shader);
    }

    // #134
    void glDetachShader(GLuint program, GLuint shader)
    {
        detail::g_gl.DetachShader(program, shader);
    }

    // #135
    void glLinkProgram(GLuint program)
    {
        detail::g_gl.LinkProgram(program);
    }

    // #136
    void glUseProgram(GLuint program)
    {
        detail::g_gl.UseProgram(program);
    }

    // #137
    void glValidateProgram(GLuint program)
    {
        detail::g_gl.ValidateProgram(program);
    }

    // #138
    void glGetProgramiv(GLuint program, ProgramParameter pname, GLint * params)
    {
        detail::g_gl.GetProgramiv(program, detail::to_gl_enum(pname), params);
    }

    // #139
    void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
    {
        detail::g_gl.GetProgramInfoLog(program, bufSize, length, infoLog);
    }

    // #140
    GLboolean glIsProgram(GLuint program)
    {
        return detail::g_gl.IsProgram(program);
    }

    // #141
    void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders)
    {
        detail::g_gl.GetAttachedShaders(program, maxCount, count, shaders);
    }

    // #142
    void glBindAttribLocation(GLuint program, GLuint index, const GLchar * name)
    {
        detail::g_gl.BindAttribLocation(program, index, name);
    }

    // #143
    GLint glGetAttribLocation(GLuint program, const GLchar * name)
    {
        return detail::g_gl.GetAttribLocation(program, name);
    }

    // #144
    void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, UniformType * type, GLchar * name)
    {
        detail::g_gl.GetActiveAttrib(program, index, bufSize, length, size, reinterpret_cast<GLenum *>(type), name);
    }

    // #145
    void glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, ProgramBinaryFormat * binaryFormat, void * binary)
    {
        detail::g_gl.GetProgramBinary(program, bufSize, length, reinterpret_cast<GLenum *>(binaryFormat), binary);
    }

    // #146
    void glProgramBinary(GLuint program, ProgramBinaryFormat binaryFormat, const void * binary, GLsizei length)
    {
        detail::g_gl.ProgramBinary(program, detail::to_gl_enum(binaryFormat), binary, length);
    }

    // #147
    void glProgramParameteri(GLuint program, ProgramParameter pname, GLint value)
    {
        detail::g_gl.ProgramParameteri(program, detail::to_gl_enum(pname), value);
    }

    // #148
    GLint glGetFragDataLocation(GLuint program, const GLchar * name)
    {
        return detail::g_gl.GetFragDataLocation(program, name);
    }

    // #149
    void glGetProgramInterfaceiv(GLuint program, ProgramInterface programInterface, ProgramInterfaceParameter pname, GLint * params)
    {
        detail::g_gl.GetProgramInterfaceiv(program, detail::to_gl_enum(programInterface), detail::to_gl_enum(pname), params);
    }

    // #150
    GLuint glGetProgramResourceIndex(GLuint program, ProgramInterface programInterface, const GLchar * name)
    {
        return detail::g_gl.GetProgramResourceIndex(program, detail::to_gl_enum(programInterface), name);
    }

    // #151
    void glGetProgramResourceName(GLuint program, ProgramInterface programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name)
    {
        detail::g_gl.GetProgramResourceName(program, detail::to_gl_enum(programInterface), index, bufSize, length, name);
    }

    // #152
    void glGetProgramResourceiv(GLuint program, ProgramInterface programInterface, GLuint index, GLsizei propCount, const ProgramResourceProperty * props, GLsizei count, GLsizei * length, GLint * params)
    {
        detail::g_gl.GetProgramResourceiv(program, detail::to_gl_enum(programInterface), index, propCount, reinterpret_cast<const GLenum *>(props), count, length, params);
    }

    // #153
    GLint glGetProgramResourceLocation(GLuint program, ProgramInterface programInterface, const GLchar * name)
    {
        return detail::g_gl.GetProgramResourceLocation(program, detail::to_gl_enum(programInterface), name);
    }

    // #154
    GLint glGetUniformLocation(GLuint program, const GLchar * name)
    {
        return detail::g_gl.GetUniformLocation(program, name);
    }

    // #155
    void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, UniformType * type, GLchar * name)
    {
        detail::g_gl.GetActiveUniform(program, index, bufSize, length, size, reinterpret_cast<GLenum *>(type), name);
    }

    // #156
    void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, UniformParameter pname, GLint * params)
    {
        detail::g_gl.GetActiveUniformsiv(program, uniformCount, uniformIndices, detail::to_gl_enum(pname), params);
    }

    // #157
    void glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices)
    {
        detail::g_gl.GetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
    }

    // #158
    GLuint glGetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName)
    {
        return detail::g_gl.GetUniformBlockIndex(program, uniformBlockName);
    }

    // #159
    void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, UniformBlockParameter pname, GLint * params)
    {
        detail::g_gl.GetActiveUniformBlockiv(program, uniformBlockIndex, detail::to_gl_enum(pname), params);
    }

    // #160
    void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName)
    {
        detail::g_gl.GetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
    }

    // #161
    void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
    {
        detail::g_gl.UniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
    }

    // #162
    void glUniform1f(GLint location, GLfloat v0)
    {
        detail::g_gl.Uniform1f(location, v0);
    }

    // #163
    void glUniform2f(GLint location, GLfloat v0, GLfloat v1)
    {
        detail::g_gl.Uniform2f(location, v0, v1);
    }

    // #164
    void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
    {
        detail::g_gl.Uniform3f(location, v0, v1, v2);
    }

    // #165
    void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
    {
        detail::g_gl.Uniform4f(location, v0, v1, v2, v3);
    }

    // #166
    void glUniform1fv(GLint location, GLsizei count, const GLfloat * value)
    {
        detail::g_gl.Uniform1fv(location, count, value);
    }

    // #167
    void glUniform2fv(GLint location, GLsizei count, const GLfloat * value)
    {
        detail::g_gl.Uniform2fv(location, count, value);
    }

    // #168
    void glUniform3fv(GLint location, GLsizei count, const GLfloat * value)
    {
        detail::g_gl.Uniform3fv(location, count, value);
    }

    // #169
    void glUniform4fv(GLint location, GLsizei count, const GLfloat * value)
    {
        detail::g_gl.Uniform4fv(location, count, value);
    }

    // #170
    void glUniform1i(GLint location, GLint v0)
    {
        detail::g_gl.Uniform1i(location, v0);
    }

    // #171
    void glUniform2i(GLint location, GLint v0, GLint v1)
    {
        detail::g_gl.Uniform2i(location, v0, v1);
    }

    // #172
    void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
    {
        detail::g_gl.Uniform3i(location, v0, v1, v2);
    }

    // #173
    void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
    {
        detail::g_gl.Uniform4i(location, v0, v1, v2, v3);
    }

    // #174
    void glUniform1iv(GLint location, GLsizei count, const GLint * value)
    {
        detail::g_gl.Uniform1iv(location, count, value);
    }

    // #175
    void glUniform2iv(GLint location, GLsizei count, const GLint * value)
    {
        detail::g_gl.Uniform2iv(location, count, value);
    }

    // #176
    void glUniform3iv(GLint location, GLsizei count, const GLint * value)
    {
        detail::g_gl.Uniform3iv(location, count, value);
    }

    // #177
    void glUniform4iv(GLint location, GLsizei count, const GLint * value)
    {
        detail::g_gl.Uniform4iv(location, count, value);
    }

    // #178
    void glUniform1ui(GLint location, GLuint v0)
    {
        detail::g_gl.Uniform1ui(location, v0);
    }

    // #179
    void glUniform2ui(GLint location, GLuint v0, GLuint v1)
    {
        detail::g_gl.Uniform2ui(location, v0, v1);
    }

    // #180
    void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
    {
        detail::g_gl.Uniform3ui(location, v0, v1, v2);
    }

    // #181
    void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
    {
        detail::g_gl.Uniform4ui(location, v0, v1, v2, v3);
    }

    // #182
    void glUniform1uiv(GLint location, GLsizei count, const GLuint * value)
    {
        detail::g_gl.Uniform1uiv(location, count, value);
    }

    // #183
    void glUniform2uiv(GLint location, GLsizei count, const GLuint * value)
    {
        detail::g_gl.Uniform2uiv(location, count, value);
    }

    // #184
    void glUniform3uiv(GLint location, GLsizei count, const GLuint * value)
    {
        detail::g_gl.Uniform3uiv(location, count, value);
    }

    // #185
    void glUniform4uiv(GLint location, GLsizei count, const GLuint * value)
    {
        detail::g_gl.Uniform4uiv(location, count, value);
    }

    // #186
    void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.UniformMatrix2fv(location, count, transpose, value);
    }

    // #187
    void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.UniformMatrix3fv(location, count, transpose, value);
    }

    // #188
    void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.UniformMatrix4fv(location, count, transpose, value);
    }

    // #189
    void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.UniformMatrix2x3fv(location, count, transpose, value);
    }

    // #190
    void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.UniformMatrix2x4fv(location, count, transpose, value);
    }

    // #191
    void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.UniformMatrix3x2fv(location, count, transpose, value);
    }

    // #192
    void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.UniformMatrix3x4fv(location, count, transpose, value);
    }

    // #193
    void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.UniformMatrix4x2fv(location, count, transpose, value);
    }

    // #194
    void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.UniformMatrix4x3fv(location, count, transpose, value);
    }

    // #195
    void glGetUniformfv(GLuint program, GLint location, GLfloat * params)
    {
        detail::g_gl.GetUniformfv(program, location, params);
    }

    // #196
    void glGetUniformiv(GLuint program, GLint location, GLint * params)
    {
        detail::g_gl.GetUniformiv(program, location, params);
    }

    // #197
    void glGetUniformuiv(GLuint program, GLint location, GLuint * params)
    {
        detail::g_gl.GetUniformuiv(program, location, params);
    }

    // #198
    void glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat * params)
    {
        detail::g_gl.GetnUniformfv(program, location, bufSize, params);
    }

    // #199
    void glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint * params)
    {
        detail::g_gl.GetnUniformiv(program, location, bufSize, params);
    }

    // #200
    void glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint * params)
    {
        detail::g_gl.GetnUniformuiv(program, location, bufSize, params);
    }

    // #201
    void glProgramUniform1f(GLuint program, GLint location, GLfloat v0)
    {
        detail::g_gl.ProgramUniform1f(program, location, v0);
    }

    // #202
    void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
    {
        detail::g_gl.ProgramUniform2f(program, location, v0, v1);
    }

    // #203
    void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
    {
        detail::g_gl.ProgramUniform3f(program, location, v0, v1, v2);
    }

    // #204
    void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
    {
        detail::g_gl.ProgramUniform4f(program, location, v0, v1, v2, v3);
    }

    // #205
    void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
    {
        detail::g_gl.ProgramUniform1fv(program, location, count, value);
    }

    // #206
    void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
    {
        detail::g_gl.ProgramUniform2fv(program, location, count, value);
    }

    // #207
    void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
    {
        detail::g_gl.ProgramUniform3fv(program, location, count, value);
    }

    // #208
    void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
    {
        detail::g_gl.ProgramUniform4fv(program, location, count, value);
    }

    // #209
    void glProgramUniform1i(GLuint program, GLint location, GLint v0)
    {
        detail::g_gl.ProgramUniform1i(program, location, v0);
    }

    // #210
    void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
    {
        detail::g_gl.ProgramUniform2i(program, location, v0, v1);
    }

    // #211
    void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
    {
        detail::g_gl.ProgramUniform3i(program, location, v0, v1, v2);
    }

    // #212
    void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
    {
        detail::g_gl.ProgramUniform4i(program, location, v0, v1, v2, v3);
    }

    // #213
    void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint * value)
    {
        detail::g_gl.ProgramUniform1iv(program, location, count, value);
    }

    // #214
    void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint * value)
    {
        detail::g_gl.ProgramUniform2iv(program, location, count, value);
    }

    // #215
    void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint * value)
    {
        detail::g_gl.ProgramUniform3iv(program, location, count, value);
    }

    // #216
    void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint * value)
    {
        detail::g_gl.ProgramUniform4iv(program, location, count, value);
    }

    // #217
    void glProgramUniform1ui(GLuint program, GLint location, GLuint v0)
    {
        detail::g_gl.ProgramUniform1ui(program, location, v0);
    }

    // #218
    void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
    {
        detail::g_gl.ProgramUniform2ui(program, location, v0, v1);
    }

    // #219
    void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
    {
        detail::g_gl.ProgramUniform3ui(program, location, v0, v1, v2);
    }

    // #220
    void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
    {
        detail::g_gl.ProgramUniform4ui(program, location, v0, v1, v2, v3);
    }

    // #221
    void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
    {
        detail::g_gl.ProgramUniform1uiv(program, location, count, value);
    }

    // #222
    void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
    {
        detail::g_gl.ProgramUniform2uiv(program, location, count, value);
    }

    // #223
    void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
    {
        detail::g_gl.ProgramUniform3uiv(program, location, count, value);
    }

    // #224
    void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
    {
        detail::g_gl.ProgramUniform4uiv(program, location, count, value);
    }

    // #225
    void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.ProgramUniformMatrix2fv(program, location, count, transpose, value);
    }

    // #226
    void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.ProgramUniformMatrix3fv(program, location, count, transpose, value);
    }

    // #227
    void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.ProgramUniformMatrix4fv(program, location, count, transpose, value);
    }

    // #228
    void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.ProgramUniformMatrix2x3fv(program, location, count, transpose, value);
    }

    // #229
    void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.ProgramUniformMatrix2x4fv(program, location, count, transpose, value);
    }

    // #230
    void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.ProgramUniformMatrix3x2fv(program, location, count, transpose, value);
    }

    // #231
    void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.ProgramUniformMatrix3x4fv(program, location, count, transpose, value);
    }

    // #232
    void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.ProgramUniformMatrix4x2fv(program, location, count, transpose, value);
    }

    // #233
    void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        detail::g_gl.ProgramUniformMatrix4x3fv(program, location, count, transpose, value);
    }

    // #234
    void glGenTextures(GLsizei n, GLuint * textures)
    {
        detail::g_gl.GenTextures(n, textures);
    }

    // #235
    void glDeleteTextures(GLsizei n, const GLuint * textures)
    {
        detail::g_gl.DeleteTextures(n, textures);
    }

    // #236
    void glBindTexture(TextureTarget target, GLuint texture)
    {
        detail::g_gl.BindTexture(detail::to_gl_enum(target), texture);
    }

    // #237
    void glActiveTexture(TextureUnit texture)
    {
        detail::g_gl.ActiveTexture(detail::to_gl_enum(texture));
    }

    // #238
    GLboolean glIsTexture(GLuint texture)
    {
        return detail::g_gl.IsTexture(texture);
    }

    // #239
    void glTexImage2D(TextureTarget target, GLint level, InternalFormat internalformat, GLsizei width, GLsizei height, GLint border, PixelFormat format, PixelType type, const void * pixels)
    {
        detail::g_gl.TexImage2D(detail::to_gl_enum(target), level, static_cast<GLint>(detail::to_gl_enum(internalformat)), width, height, border, detail::to_gl_enum(format), detail::to_gl_enum(type), pixels);
    }

    // #240
    void glTexImage3D(TextureTarget target, GLint level, InternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, PixelFormat format, PixelType type, const void * pixels)
    {
        detail::g_gl.TexImage3D(detail::to_gl_enum(target), level, static_cast<GLint>(detail::to_gl_enum(internalformat)), width, height, depth, border, detail::to_gl_enum(format), detail::to_gl_enum(type), pixels);
    }

    // #241
    void glTexSubImage2D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, PixelFormat format, PixelType type, const void * pixels)
    {
        detail::g_gl.TexSubImage2D(detail::to_gl_enum(target), level, xoffset, yoffset, width, height, detail::to_gl_enum(format), detail::to_gl_enum(type), pixels);
    }

    // #242
    void glTexSubImage3D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, PixelFormat format, PixelType type, const void * pixels)
    {
        detail::g_gl.TexSubImage3D(detail::to_gl_enum(target), level, xoffset, yoffset, zoffset, width, height, depth, detail::to_gl_enum(format), detail::to_gl_enum(type), pixels);
    }

    // #243
    void glTexStorage2D(TextureTarget target, GLsizei levels, InternalFormat internalformat, GLsizei width, GLsizei height)
    {
        detail::g_gl.TexStorage2D(detail::to_gl_enum(target), levels, detail::to_gl_enum(internalformat), width, height);
    }

    // #244
    void glTexStorage3D(TextureTarget target, GLsizei levels, InternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth)
    {
        detail::g_gl.TexStorage3D(detail::to_gl_enum(target), levels, detail::to_gl_enum(internalformat), width, height, depth);
    }

    // #245
    void glTexStorage2DMultisample(TextureTarget target, GLsizei samples, InternalFormat internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
    {
        detail::g_gl.TexStorage2DMultisample(detail::to_gl_enum(target), samples, detail::to_gl_enum(internalformat), width, height, fixedsamplelocations);
    }

    // #246
    void glTexStorage3DMultisample(TextureTarget target, GLsizei samples, InternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
    {
        detail::g_gl.TexStorage3DMultisample(detail::to_gl_enum(target), samples, detail::to_gl_enum(internalformat), width, height, depth, fixedsamplelocations);
    }

    // #247
    void glCompressedTexImage2D(TextureTarget target, GLint level, CompressedInternalFormat internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data)
    {
        detail::g_gl.CompressedTexImage2D(detail::to_gl_enum(target), level, detail::to_gl_enum(internalformat), width, height, border, imageSize, data);
    }

    // #248
    void glCompressedTexImage3D(TextureTarget target, GLint level, CompressedInternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data)
    {
        detail::g_gl.CompressedTexImage3D(detail::to_gl_enum(target), level, detail::to_gl_enum(internalformat), width, height, depth, border, imageSize, data);
    }

    // #249
    void glCompressedTexSubImage2D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, CompressedInternalFormat format, GLsizei imageSize, const void * data)
    {
        detail::g_gl.CompressedTexSubImage2D(detail::to_gl_enum(target), level, xoffset, yoffset, width, height, detail::to_gl_enum(format), imageSize, data);
    }

    // #250
    void glCompressedTexSubImage3D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, CompressedInternalFormat format, GLsizei imageSize, const void * data)
    {
        detail::g_gl.CompressedTexSubImage3D(detail::to_gl_enum(target), level, xoffset, yoffset, zoffset, width, height, depth, detail::to_gl_enum(format), imageSize, data);
    }

    // #251
    void glCopyTexImage2D(TextureTarget target, GLint level, InternalFormat internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
    {
        detail::g_gl.CopyTexImage2D(detail::to_gl_enum(target), level, detail::to_gl_enum(internalformat), x, y, width, height, border);
    }

    // #252
    void glCopyTexSubImage2D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
    {
        detail::g_gl.CopyTexSubImage2D(detail::to_gl_enum(target), level, xoffset, yoffset, x, y, width, height);
    }

    // #253
    void glCopyTexSubImage3D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
    {
        detail::g_gl.CopyTexSubImage3D(detail::to_gl_enum(target), level, xoffset, yoffset, zoffset, x, y, width, height);
    }

    // #254
    void glCopyImageSubData(GLuint srcName, TextureTarget srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, TextureTarget dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
    {
        detail::g_gl.CopyImageSubData(srcName, detail::to_gl_enum(srcTarget), srcLevel, srcX, srcY, srcZ, dstName, detail::to_gl_enum(dstTarget), dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
    }

    // #255
    void glGenerateMipmap(TextureTarget target)
    {
        detail::g_gl.GenerateMipmap(detail::to_gl_enum(target));
    }

    // #256
    void glTexParameterf(TextureTarget target, TextureParameter pname, GLfloat param)
    {
        detail::g_gl.TexParameterf(detail::to_gl_enum(target), detail::to_gl_enum(pname), param);
    }

    // #257
    void glTexParameteri(TextureTarget target, TextureParameter pname, GLint param)
    {
        detail::g_gl.TexParameteri(detail::to_gl_enum(target), detail::to_gl_enum(pname), param);
    }

    // #258
    void glTexParameterfv(TextureTarget target, TextureParameter pname, const GLfloat * params)
    {
        detail::g_gl.TexParameterfv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #259
    void glTexParameteriv(TextureTarget target, TextureParameter pname, const GLint * params)
    {
        detail::g_gl.TexParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #260
    void glTexParameterIiv(TextureTarget target, TextureParameter pname, const GLint * params)
    {
        detail::g_gl.TexParameterIiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #261
    void glTexParameterIuiv(TextureTarget target, TextureParameter pname, const GLuint * params)
    {
        detail::g_gl.TexParameterIuiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #262
    void glGetTexParameterfv(TextureTarget target, TextureParameter pname, GLfloat * params)
    {
        detail::g_gl.GetTexParameterfv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #263
    void glGetTexParameteriv(TextureTarget target, TextureParameter pname, GLint * params)
    {
        detail::g_gl.GetTexParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #264
    void glGetTexParameterIiv(TextureTarget target, TextureParameter pname, GLint * params)
    {
        detail::g_gl.GetTexParameterIiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #265
    void glGetTexParameterIuiv(TextureTarget target, TextureParameter pname, GLuint * params)
    {
        detail::g_gl.GetTexParameterIuiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #266
    void glGetTexLevelParameteriv(TextureTarget target, GLint level, TextureLevelParameter pname, GLint * params)
    {
        detail::g_gl.GetTexLevelParameteriv(detail::to_gl_enum(target), level, detail::to_gl_enum(pname), params);
    }

    // #267
    void glGetTexLevelParameterfv(TextureTarget target, GLint level, TextureLevelParameter pname, GLfloat * params)
    {
        detail::g_gl.GetTexLevelParameterfv(detail::to_gl_enum(target), level, detail::to_gl_enum(pname), params);
    }

    // #268
    void glTexBuffer(TextureTarget target, InternalFormat internalformat, GLuint buffer)
    {
        detail::g_gl.TexBuffer(detail::to_gl_enum(target), detail::to_gl_enum(internalformat), buffer);
    }

    // #269
    void glTexBufferRange(TextureTarget target, InternalFormat internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
    {
        detail::g_gl.TexBufferRange(detail::to_gl_enum(target), detail::to_gl_enum(internalformat), buffer, offset, size);
    }

    // #270
    void glGetMultisamplefv(MultisampleParameter pname, GLuint index, GLfloat * val)
    {
        detail::g_gl.GetMultisamplefv(detail::to_gl_enum(pname), index, val);
    }

    // #271
    void glGetInternalformativ(InternalFormatTarget target, InternalFormat internalformat, InternalFormatParameter pname, GLsizei count, GLint * params)
    {
        detail::g_gl.GetInternalformativ(detail::to_gl_enum(target), detail::to_gl_enum(internalformat), detail::to_gl_enum(pname), count, params);
    }

    // #272
    void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, ImageAccess access, InternalFormat format)
    {
        detail::g_gl.BindImageTexture(unit, texture, level, layered, layer, detail::to_gl_enum(access), detail::to_gl_enum(format));
    }

    // #273
    void glGenSamplers(GLsizei count, GLuint * samplers)
    {
        detail::g_gl.GenSamplers(count, samplers);
    }

    // #274
    void glDeleteSamplers(GLsizei count, const GLuint * samplers)
    {
        detail::g_gl.DeleteSamplers(count, samplers);
    }

    // #275
    void glBindSampler(GLuint unit, GLuint sampler)
    {
        detail::g_gl.BindSampler(unit, sampler);
    }

    // #276
    GLboolean glIsSampler(GLuint sampler)
    {
        return detail::g_gl.IsSampler(sampler);
    }

    // #277
    void glSamplerParameterf(GLuint sampler, TextureParameter pname, GLfloat param)
    {
        detail::g_gl.SamplerParameterf(sampler, detail::to_gl_enum(pname), param);
    }

    // #278
    void glSamplerParameteri(GLuint sampler, TextureParameter pname, GLint param)
    {
        detail::g_gl.SamplerParameteri(sampler, detail::to_gl_enum(pname), param);
    }

    // #279
    void glSamplerParameterfv(GLuint sampler, TextureParameter pname, const GLfloat * param)
    {
        detail::g_gl.SamplerParameterfv(sampler, detail::to_gl_enum(pname), param);
    }

    // #280
    void glSamplerParameteriv(GLuint sampler, TextureParameter pname, const GLint * param)
    {
        detail::g_gl.SamplerParameteriv(sampler, detail::to_gl_enum(pname), param);
    }

    // #281
    void glSamplerParameterIiv(GLuint sampler, TextureParameter pname, const GLint * param)
    {
        detail::g_gl.SamplerParameterIiv(sampler, detail::to_gl_enum(pname), param);
    }

    // #282
    void glSamplerParameterIuiv(GLuint sampler, TextureParameter pname, const GLuint * param)
    {
        detail::g_gl.SamplerParameterIuiv(sampler, detail::to_gl_enum(pname), param);
    }

    // #283
    void glGetSamplerParameterfv(GLuint sampler, TextureParameter pname, GLfloat * params)
    {
        detail::g_gl.GetSamplerParameterfv(sampler, detail::to_gl_enum(pname), params);
    }

    // #284
    void glGetSamplerParameteriv(GLuint sampler, TextureParameter pname, GLint * params)
    {
        detail::g_gl.GetSamplerParameteriv(sampler, detail::to_gl_enum(pname), params);
    }

    // #285
    void glGetSamplerParameterIiv(GLuint sampler, TextureParameter pname, GLint * params)
    {
        detail::g_gl.GetSamplerParameterIiv(sampler, detail::to_gl_enum(pname), params);
    }

    // #286
    void glGetSamplerParameterIuiv(GLuint sampler, TextureParameter pname, GLuint * params)
    {
        detail::g_gl.GetSamplerParameterIuiv(sampler, detail::to_gl_enum(pname), params);
    }

    // #287
    void glGenFramebuffers(GLsizei n, GLuint * framebuffers)
    {
        detail::g_gl.GenFramebuffers(n, framebuffers);
    }

    // #288
    void glDeleteFramebuffers(GLsizei n, const GLuint * framebuffers)
    {
        detail::g_gl.DeleteFramebuffers(n, framebuffers);
    }

    // #289
    void glBindFramebuffer(FramebufferTarget target, GLuint framebuffer)
    {
        detail::g_gl.BindFramebuffer(detail::to_gl_enum(target), framebuffer);
    }

    // #290
    GLboolean glIsFramebuffer(GLuint framebuffer)
    {
        return detail::g_gl.IsFramebuffer(framebuffer);
    }

    // #291
    FramebufferStatus glCheckFramebufferStatus(FramebufferTarget target)
    {
        return static_cast<FramebufferStatus>(detail::g_gl.CheckFramebufferStatus(detail::to_gl_enum(target)));
    }

    // #292
    void glFramebufferTexture2D(FramebufferTarget target, FramebufferAttachment attachment, TextureTarget textarget, GLuint texture, GLint level)
    {
        detail::g_gl.FramebufferTexture2D(detail::to_gl_enum(target), detail::to_gl_enum(attachment), detail::to_gl_enum(textarget), texture, level);
    }

    // #293
    void glFramebufferTextureLayer(FramebufferTarget target, FramebufferAttachment attachment, GLuint texture, GLint level, GLint layer)
    {
        detail::g_gl.FramebufferTextureLayer(detail::to_gl_enum(target), detail::to_gl_enum(attachment), texture, level, layer);
    }

    // #294
    void glFramebufferTexture(FramebufferTarget target, FramebufferAttachment attachment, GLuint texture, GLint level)
    {
        detail::g_gl.FramebufferTexture(detail::to_gl_enum(target), detail::to_gl_enum(attachment), texture, level);
    }

    // #295
    void glFramebufferRenderbuffer(FramebufferTarget target, FramebufferAttachment attachment, RenderbufferTarget renderbuffertarget, GLuint renderbuffer)
    {
        detail::g_gl.FramebufferRenderbuffer(detail::to_gl_enum(target), detail::to_gl_enum(attachment), detail::to_gl_enum(renderbuffertarget), renderbuffer);
    }

    // #296
    void glFramebufferParameteri(FramebufferTarget target, FramebufferDefaultParameter pname, GLint param)
    {
        detail::g_gl.FramebufferParameteri(detail::to_gl_enum(target), detail::to_gl_enum(pname), param);
    }

    // #297
    void glGetFramebufferParameteriv(FramebufferTarget target, FramebufferDefaultParameter pname, GLint * params)
    {
        detail::g_gl.GetFramebufferParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #298
    void glGetFramebufferAttachmentParameteriv(FramebufferTarget target, FramebufferAttachment attachment, FramebufferAttachmentParameter pname, GLint * params)
    {
        detail::g_gl.GetFramebufferAttachmentParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(attachment), detail::to_gl_enum(pname), params);
    }

    // #299
    void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, ClearBufferBit mask, TextureFilter filter)
    {
        detail::g_gl.BlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, detail::to_gl_bitfield(mask), detail::to_gl_enum(filter));
    }

    // #300
    void glInvalidateFramebuffer(FramebufferTarget target, GLsizei numAttachments, const FramebufferAttachment * attachments)
    {
        detail::g_gl.InvalidateFramebuffer(detail::to_gl_enum(target), numAttachments, reinterpret_cast<const GLenum *>(attachments));
    }

    // #301
    void glInvalidateSubFramebuffer(FramebufferTarget target, GLsizei numAttachments, const FramebufferAttachment * attachments, GLint x, GLint y, GLsizei width, GLsizei height)
    {
        detail::g_gl.InvalidateSubFramebuffer(detail::to_gl_enum(target), numAttachments, reinterpret_cast<const GLenum *>(attachments), x, y, width, height);
    }

    // #302
    void glGenRenderbuffers(GLsizei n, GLuint * renderbuffers)
    {
        detail::g_gl.GenRenderbuffers(n, renderbuffers);
    }

    // #303
    void glDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers)
    {
        detail::g_gl.DeleteRenderbuffers(n, renderbuffers);
    }

    // #304
    void glBindRenderbuffer(RenderbufferTarget target, GLuint renderbuffer)
    {
        detail::g_gl.BindRenderbuffer(detail::to_gl_enum(target), renderbuffer);
    }

    // #305
    GLboolean glIsRenderbuffer(GLuint renderbuffer)
    {
        return detail::g_gl.IsRenderbuffer(renderbuffer);
    }

    // #306
    void glRenderbufferStorage(RenderbufferTarget target, InternalFormat internalformat, GLsizei width, GLsizei height)
    {
        detail::g_gl.RenderbufferStorage(detail::to_gl_enum(target), detail::to_gl_enum(internalformat), width, height);
    }

    // #307
    void glRenderbufferStorageMultisample(RenderbufferTarget target, GLsizei samples, InternalFormat internalformat, GLsizei width, GLsizei height)
    {
        detail::g_gl.RenderbufferStorageMultisample(detail::to_gl_enum(target), samples, detail::to_gl_enum(internalformat), width, height);
    }

    // #308
    void glGetRenderbufferParameteriv(RenderbufferTarget target, RenderbufferParameter pname, GLint * params)
    {
        detail::g_gl.GetRenderbufferParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #309
    void glGenTransformFeedbacks(GLsizei n, GLuint * ids)
    {
        detail::g_gl.GenTransformFeedbacks(n, ids);
    }

    // #310
    void glDeleteTransformFeedbacks(GLsizei n, const GLuint * ids)
    {
        detail::g_gl.DeleteTransformFeedbacks(n, ids);
    }

    // #311
    void glBindTransformFeedback(TransformFeedbackTarget target, GLuint id)
    {
        detail::g_gl.BindTransformFeedback(detail::to_gl_enum(target), id);
    }

    // #312
    GLboolean glIsTransformFeedback(GLuint id)
    {
        return detail::g_gl.IsTransformFeedback(id);
    }

    // #313
    void glBeginTransformFeedback(PrimitiveType primitiveMode)
    {
        detail::g_gl.BeginTransformFeedback(detail::to_gl_enum(primitiveMode));
    }

    // #314
    void glEndTransformFeedback(void)
    {
        detail::g_gl.EndTransformFeedback();
    }

    // #315
    void glPauseTransformFeedback(void)
    {
        detail::g_gl.PauseTransformFeedback();
    }

    // #316
    void glResumeTransformFeedback(void)
    {
        detail::g_gl.ResumeTransformFeedback();
    }

    // #317
    void glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, TransformFeedbackBufferMode bufferMode)
    {
        detail::g_gl.TransformFeedbackVaryings(program, count, varyings, detail::to_gl_enum(bufferMode));
    }

    // #318
    void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, UniformType * type, GLchar * name)
    {
        detail::g_gl.GetTransformFeedbackVarying(program, index, bufSize, length, size, reinterpret_cast<GLenum *>(type), name);
    }

    // #319
    void glGenQueries(GLsizei n, GLuint * ids)
    {
        detail::g_gl.GenQueries(n, ids);
    }

    // #320
    void glDeleteQueries(GLsizei n, const GLuint * ids)
    {
        detail::g_gl.DeleteQueries(n, ids);
    }

    // #321
    GLboolean glIsQuery(GLuint id)
    {
        return detail::g_gl.IsQuery(id);
    }

    // #322
    void glBeginQuery(QueryTarget target, GLuint id)
    {
        detail::g_gl.BeginQuery(detail::to_gl_enum(target), id);
    }

    // #323
    void glEndQuery(QueryTarget target)
    {
        detail::g_gl.EndQuery(detail::to_gl_enum(target));
    }

    // #324
    void glGetQueryiv(QueryTarget target, QueryParameter pname, GLint * params)
    {
        detail::g_gl.GetQueryiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
    }

    // #325
    void glGetQueryObjectuiv(GLuint id, QueryObjectParameter pname, GLuint * params)
    {
        detail::g_gl.GetQueryObjectuiv(id, detail::to_gl_enum(pname), params);
    }

    // #326
    GLsync glFenceSync(SyncCondition condition, SyncFlag flags)
    {
        return detail::g_gl.FenceSync(detail::to_gl_enum(condition), detail::to_gl_bitfield(flags));
    }

    // #327
    void glDeleteSync(GLsync sync)
    {
        detail::g_gl.DeleteSync(sync);
    }

    // #328
    GLboolean glIsSync(GLsync sync)
    {
        return detail::g_gl.IsSync(sync);
    }

    // #329
    SyncWaitResult glClientWaitSync(GLsync sync, SyncFlushMask flags, GLuint64 timeout)
    {
        return static_cast<SyncWaitResult>(detail::g_gl.ClientWaitSync(sync, detail::to_gl_bitfield(flags), timeout));
    }

    // #330
    void glWaitSync(GLsync sync, SyncFlag flags, GLuint64 timeout)
    {
        detail::g_gl.WaitSync(sync, detail::to_gl_bitfield(flags), timeout);
    }

    // #331
    void glGetSynciv(GLsync sync, SyncParameter pname, GLsizei count, GLsizei * length, GLint * values)
    {
        detail::g_gl.GetSynciv(sync, detail::to_gl_enum(pname), count, length, values);
    }

    // #332
    void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
    {
        detail::g_gl.DispatchCompute(num_groups_x, num_groups_y, num_groups_z);
    }

    // #333
    void glDispatchComputeIndirect(GLintptr indirect)
    {
        detail::g_gl.DispatchComputeIndirect(indirect);
    }

    // #334
    void glMemoryBarrier(MemoryBarrierMask barriers)
    {
        detail::g_gl.MemoryBarrier(detail::to_gl_bitfield(barriers));
    }

    // #335
    void glMemoryBarrierByRegion(MemoryBarrierMask barriers)
    {
        detail::g_gl.MemoryBarrierByRegion(detail::to_gl_bitfield(barriers));
    }

    // #336
    void glGenProgramPipelines(GLsizei n, GLuint * pipelines)
    {
        detail::g_gl.GenProgramPipelines(n, pipelines);
    }

    // #337
    void glDeleteProgramPipelines(GLsizei n, const GLuint * pipelines)
    {
        detail::g_gl.DeleteProgramPipelines(n, pipelines);
    }

    // #338
    void glBindProgramPipeline(GLuint pipeline)
    {
        detail::g_gl.BindProgramPipeline(pipeline);
    }

    // #339
    GLboolean glIsProgramPipeline(GLuint pipeline)
    {
        return detail::g_gl.IsProgramPipeline(pipeline);
    }

    // #340
    void glUseProgramStages(GLuint pipeline, ShaderStageMask stages, GLuint program)
    {
        detail::g_gl.UseProgramStages(pipeline, detail::to_gl_bitfield(stages), program);
    }

    // #341
    void glActiveShaderProgram(GLuint pipeline, GLuint program)
    {
        detail::g_gl.ActiveShaderProgram(pipeline, program);
    }

    // #342
    GLuint glCreateShaderProgramv(ShaderType type, GLsizei count, const GLchar *const* strings)
    {
        return detail::g_gl.CreateShaderProgramv(detail::to_gl_enum(type), count, strings);
    }

    // #343
    void glValidateProgramPipeline(GLuint pipeline)
    {
        detail::g_gl.ValidateProgramPipeline(pipeline);
    }

    // #344
    void glGetProgramPipelineiv(GLuint pipeline, ProgramPipelineParameter pname, GLint * params)
    {
        detail::g_gl.GetProgramPipelineiv(pipeline, detail::to_gl_enum(pname), params);
    }

    // #345
    void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
    {
        detail::g_gl.GetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
    }

    // #346
    void glPatchParameteri(TessellationParameter pname, GLint value)
    {
        detail::g_gl.PatchParameteri(detail::to_gl_enum(pname), value);
    }

    // #347
    void glPrimitiveBoundingBox(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW)
    {
        detail::g_gl.PrimitiveBoundingBox(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
    }

    // #348
    void glDebugMessageCallback(GLDEBUGPROC callback, const void * userParam)
    {
        detail::g_gl.DebugMessageCallback(callback, userParam);
    }

    // #349
    void glDebugMessageControl(DebugSource source, DebugType type, DebugSeverity severity, GLsizei count, const GLuint * ids, GLboolean enabled)
    {
        detail::g_gl.DebugMessageControl(detail::to_gl_enum(source), detail::to_gl_enum(type), detail::to_gl_enum(severity), count, ids, enabled);
    }

    // #350
    void glDebugMessageInsert(DebugSource source, DebugType type, GLuint id, DebugSeverity severity, GLsizei length, const GLchar * buf)
    {
        detail::g_gl.DebugMessageInsert(detail::to_gl_enum(source), detail::to_gl_enum(type), id, detail::to_gl_enum(severity), length, buf);
    }

    // #351
    GLuint glGetDebugMessageLog(GLuint count, GLsizei bufSize, DebugSource * sources, DebugType * types, GLuint * ids, DebugSeverity * severities, GLsizei * lengths, GLchar * messageLog)
    {
        return detail::g_gl.GetDebugMessageLog(count, bufSize, reinterpret_cast<GLenum *>(sources), reinterpret_cast<GLenum *>(types), ids, reinterpret_cast<GLenum *>(severities), lengths, messageLog);
    }

    // #352
    void glPushDebugGroup(DebugSource source, GLuint id, GLsizei length, const GLchar * message)
    {
        detail::g_gl.PushDebugGroup(detail::to_gl_enum(source), id, length, message);
    }

    // #353
    void glPopDebugGroup(void)
    {
        detail::g_gl.PopDebugGroup();
    }

    // #354
    void glObjectLabel(DebugObjectLabel identifier, GLuint name, GLsizei length, const GLchar * label)
    {
        detail::g_gl.ObjectLabel(detail::to_gl_enum(identifier), name, length, label);
    }

    // #355
    void glObjectPtrLabel(const void * ptr, GLsizei length, const GLchar * label)
    {
        detail::g_gl.ObjectPtrLabel(ptr, length, label);
    }

    // #356
    void glGetObjectLabel(DebugObjectLabel identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label)
    {
        detail::g_gl.GetObjectLabel(detail::to_gl_enum(identifier), name, bufSize, length, label);
    }

    // #357
    void glGetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label)
    {
        detail::g_gl.GetObjectPtrLabel(ptr, bufSize, length, label);
    }

    // #358
    GraphicsResetStatus glGetGraphicsResetStatus(void)
    {
        return static_cast<GraphicsResetStatus>(detail::g_gl.GetGraphicsResetStatus());
    }

}

#pragma once
#include <cstddef>
#include <cstdint>
#include <glad/glad.h>
#include <memory>
#include <misc/assert.h>
#include <misc/misc.h>
#include <render/OpenGL/bufferopengl.h>
#include <render/OpenGL/renderinstanceopengl.h>
#include <render/OpenGL/scopedbindgl.h>
#include <render/renderinstance.h>
#include <render/vertexarrayobject.h>
#include <render/vertexlayout.h>

namespace Render
{
    class VertexArrayObjectOpenGL final : public BindableGL, public VertexArrayObject
    {
        using super = VertexArrayObject;

    public:
        VertexArrayObjectOpenGL(RenderInstanceOpenGL& renderInstance,
                                std::vector<size_t> bufferSizeCounts,
                                std::vector<NonNullConstPtr<VertexLayout>> bindings,
                                size_t indexBufferSizeInElements);
        virtual ~VertexArrayObjectOpenGL();

        virtual Buffer* getVertexBuffer(size_t index) override { return mBuffers[index].get(); }
        virtual Buffer* getIndexBuffer() override { return mIndexBuffer.get(); }

        virtual void bind(std::optional<GLenum> binding = std::nullopt) override;
        virtual void unbind(std::optional<GLenum> binding = std::nullopt) override;

    private:
        static GLint setupAttributes(GLint locationIndex, BufferOpenGL& buffer, const VertexLayout& layout);

    private:
        std::vector<std::unique_ptr<BufferOpenGL>> mBuffers;
        std::unique_ptr<BufferOpenGL> mIndexBuffer;
        GLuint mVaoId;
    };
}

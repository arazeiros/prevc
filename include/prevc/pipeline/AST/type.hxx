
#ifndef PREVC_PIPELINE_AST_TYPE_HXX
#define PREVC_PIPELINE_AST_TYPE_HXX

#include <prevc/pipeline/AST/node.hxx>
#include <prevc/pipeline/semantic_analysis/type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief The type node in an AST.
             * */
            class Type: public Node
            {
            public:
                /**
                 * \brief Create an AST type node at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the node in the source code.
                 * */
                Type(Pipeline* pipeline, util::Location&& location);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Type() = default;

                /**
                 * \brief Returns the semantic type representing this type.
                 * \return The semantic type representing this type.
                 *
                 * First time this function is called the semantic type is generated
                 * and cached. Every next call will return the cached type.
                 * */
                const semantic_analysis::Type* get_semantic_type() noexcept;

                /**
                 * \brief Returns a string semantic representation of this type.
                 * \return The semantic representation.
                 * */
                virtual util::String to_semantic_string() const noexcept = 0;

            protected:
                /**
                 * \brief Generate and returns the semantic type representing this type.
                 * \return The semantic type representing this type.
                 * */
                virtual const semantic_analysis::Type* generate_semantic_type() const noexcept = 0;

            private:
                /**
                 * \brief The cached semantic type that represent this type.
                 *
                 * NULL if the type was not cached yet.
                 * */
                const semantic_analysis::Type* semantic_type;
            };
        }
    }
}

#endif

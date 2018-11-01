
#ifndef PREVC_PIPELINE_AST_NAMEDTYPE_HXX
#define PREVC_PIPELINE_AST_NAMEDTYPE_HXX

#include <prevc/pipeline/AST/type.hxx>
#include <prevc/pipeline/AST/type-declaration.hxx>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief The named-type node in an AST.
             * */
            class NamedType: public Type
            {
            public:
                /**
                 * \brief Create an AST named-type node at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the node in the source code.
                 * \param name The name of the type.
                 * */
                NamedType(Pipeline* pipeline, util::Location&& location, const util::String& name);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~NamedType() = default;

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Returns a string representation of this named-type.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

                /**
                 * \brief Returns a string semantic representation of this type.
                 * \return The semantic representation.
                 * */
                virtual util::String to_semantic_string() const noexcept override;

            protected:
                /**
                 * \brief Generate and returns the semantic type representing this type.
                 * \return The semantic type representing this type.
                 * */
                virtual const semantic_analysis::Type* generate_semantic_type() const noexcept override;

            private:
                /**
                 * \brief The name of the type.
                 * */
                const util::String name;

                /**
                 * \brief Stores the declaration referenced by this type name.
                 * Calculated during semantic analysis.
                 * */
                TypeDeclaration* declaration;
            };
        }
    }
}

#endif

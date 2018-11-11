
#ifndef PREVC_PIPELINE_AST_TYPEDECLARATION_HXX
#define PREVC_PIPELINE_AST_TYPEDECLARATION_HXX

#include <prevc/pipeline/AST/declaration.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a type-declaration in the AST.
             * */
            class TypeDeclaration: public Declaration
            {
            public:
                /**
                 * \brief Create an AST type-declaration at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the type-declaration in the source code.
                 * \param name The type-declaration name.
                 * \param type The type-declaration type.
                 * */
                TypeDeclaration(Pipeline* pipeline, util::Location&& location, const util::String& name, Type* type);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~TypeDeclaration() = default;

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Generate the fake link-type.
                 * \return The semantic type of this expression.
                 * */
                virtual const semantic_analysis::Type* generate_semantic_type() override;

                /**
                 * \brief Generate the real semantic type of this expression.
                 * \return The semantic type of this expression.
                 * */
                const semantic_analysis::Type* generate_real_semantic_type();

                /**
                 * \brief Returns a string representation of this type-declaration.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;
            };
        }
    }
}

#endif

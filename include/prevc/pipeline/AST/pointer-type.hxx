
#ifndef PREVC_PIPELINE_AST_POINTERTYPE_HXX
#define PREVC_PIPELINE_AST_POINTERTYPE_HXX

#include <prevc/pipeline/AST/type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief The pointer-type node in an AST.
             * */
            class PointerType: public Type
            {
            public:
                /**
                 * \brief Create an AST pointer-type node at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the node in the source code.
                 * \param type The type of the pointer.
                 * */
                PointerType(Pipeline* pipeline, util::Location&& location, Type* type);

                /**
                 * \brief Release used resources.
                 * */
                virtual ~PointerType();

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Returns a string representation of this pointer-type.
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
                 * \brief The type of the pointer.
                 * */
                Type* type;
            };
        }
    }
}

#endif

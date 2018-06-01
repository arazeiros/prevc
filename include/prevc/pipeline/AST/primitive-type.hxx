
#ifndef PREVC_PIPELINE_AST_PRIMITIVETYPE_HXX
#define PREVC_PIPELINE_AST_PRIMITIVETYPE_HXX

#include <prevc/pipeline/AST/type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief The primitive type node in an AST.
             * */
            class PrimitiveType: public Type
            {
            public:
                /**
                 * \brief Enumeration of possible primitive type names.
                 * */
                enum class Name
                {
                    VOID,
                    BOOL,
                    CHAR,
                    INT
                };

                /**
                 * The name of the primitive type.
                 * */
                const Name name;

                /**
                 * \brief Create an AST primitive type node at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the node in the source code.
                 * \param name THe name of the primitive type.
                 * */
                PrimitiveType(Pipeline* pipeline, util::Location&& location, Name name);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~PrimitiveType() = default;

                /**
                 * \brief Returns a string representation of this primitive type.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;
            };

            /**
             * \brief Returns the C-string representation of a specified type name.
             * \param name The specified type name.
             * \return The C-string representation.
             * */
            constexpr static const char* to_string(const PrimitiveType::Name& name)
            {
                switch (name)
                {
                    case PrimitiveType::Name::INT:  return "INT";
                    case PrimitiveType::Name::CHAR: return "CHAR";
                    case PrimitiveType::Name::BOOL: return "BOOL";

                    default:
                        prevc::InternalError::raise("not known type name");
                }
            }
        }
    }
}

#endif

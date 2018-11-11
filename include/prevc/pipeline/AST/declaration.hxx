
#ifndef PREVC_PIPELINE_AST_DECLARATION_HXX
#define PREVC_PIPELINE_AST_DECLARATION_HXX

#include <prevc/pipeline/AST/node.hxx>
#include <prevc/pipeline/AST/type.hxx>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            class ComponentAccess;
            class Declarations;
            class FunctionCall;
            class NamedType;
            class RecordType;
            class VariableName;

            /**
             * \brief Represent a declaration in the AST.
             * */
            class Declaration: public Node
            {
                friend ComponentAccess;
                friend Declarations;
                friend FunctionCall;
                friend NamedType;
                friend RecordType;
                friend VariableName;

            public:
                /**
                 * \brief Enumeration of declaration kinds.
                 * */
                enum class Kind
                {
                    Function,
                    Type,
                    Variable
                };

                /**
                 * \brief The kind of the declaration.
                 * */
                const Kind kind;

                /**
                 * \brief The declaration name.
                 * */
                const util::String name;

                /**
                 * \brief Create an AST declaration at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the declaration in the source code.
                 * \param kind The kind of the declaration.
                 * \param name The declaration name.
                 * \param type The declaration type.
                 * */
                Declaration(Pipeline* pipeline, util::Location&& location, Kind kind, const util::String& name, Type* type);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~Declaration();

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Returns the semantic type of this expression.
                 * \return The semantic type of this expression.
                 *
                 * Before this method can be called, the call to `check_semantics()` have to be done.
                 * */
                const semantic_analysis::Type* get_semantic_type();

                /**
                 * \brief Generate the semantic type of this expression.
                 * \return The semantic type of this expression.
                 * */
                virtual const semantic_analysis::Type* generate_semantic_type();

            protected:
                /**
                 * \brief The declaration type.
                 * */
                Type* type;

                /**
                 * \brief The semantic-type of the declaration.
                 *
                 * Calculated during `check_semantics()`.
                 * */
                const semantic_analysis::Type* semantic_type;
            };
        }
    }
}

#endif

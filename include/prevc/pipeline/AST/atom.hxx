
#ifndef PREVC_PIPELINE_AST_ATOM_HXX
#define PREVC_PIPELINE_AST_ATOM_HXX

#include <prevc/error.hxx>
#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief An atom in the AST.
             * */
            class Atom: public Expression
            {
            public:
                /**
                 * \brief The enumeration of all possible atom types.
                 * */
                enum class Type
                {
                    INTEGER,
                    BOOLEAN,
                    CHARACTER,
                    VOID,
                    POINTER
                };

                /**
                 * \brief Create an atom node.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the atom in the source code.
                 * \param type The type of the atom.
                 * \param lexeme The lexeme of the node.
                 * */
                Atom(Pipeline* pipeline, util::Location&& location, Type type, const util::String& lexeme);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~Atom();

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Generate the IR code for this atom expression.
                 * \param builder The builder of the IR block containing this atom expression.
                 * \return The IR value representing this atom expression.
                 * */
                virtual llvm::Value* generate_IR(llvm::IRBuilder<>* builder) override;

                /**
                 * \brief Evaluate the expression as an integer (if possible).
                 * \return Returns the evaluated integer.
                 * */
                virtual std::optional<std::int64_t> evaluate_as_integer() const noexcept override;

                /**
                 * \brief Returns the semantic type of this expression.
                 * \return The semantic type of this expression.
                 *
                 * Before this method can be called, the call to `check_semantics()` have to be done.
                 * */
                virtual const semantic_analysis::Type* get_semantic_type() override;

                /**
                 * \brief Returns a string representation of this atom.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The type of the atom.
                 * */
                Type type;

                /**
                 * \brief The lexeme of the atom.
                 * */
                util::String lexeme;
            };

            /**
             * \brief Returns the C-string representation of a specified atom type.
             * \param operator_ The specified atom type.
             * \return The C-string representation.
             * */
            constexpr static const char* to_string(const Atom::Type& type)
            {
                switch (type)
                {
                    case Atom::Type::INTEGER:   return "INTEGER";
                    case Atom::Type::BOOLEAN:   return "BOOLEAN";
                    case Atom::Type::CHARACTER: return "CHARACTER";
                    case Atom::Type::VOID:      return "VOID";
                    case Atom::Type::POINTER:   return "POINTER";

                    default:
                        prevc::InternalError::raise("token not recognized");
                }
            }
        }
    }
}

#endif

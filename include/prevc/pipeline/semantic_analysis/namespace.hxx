
#ifndef PREVC_PIPELINE_SEMANTICANALYSIS_NAMESPACE_HXX
#define PREVC_PIPELINE_SEMANTICANALYSIS_NAMESPACE_HXX

#include <map>
#include <optional>
#include <vector>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            class Declaration;
        }

        namespace semantic_analysis
        {
            /**
             * \brief Represent a Prev namespace.
             * */
            class Namespace
            {
            public:
                /**
                 * \brief Create a new namespace.
                 *
                 * */
                Namespace();

                /**
                 * \brief Release used resources.
                 * */
                virtual ~Namespace();

                /**
                 * \brief Pushes a new scope in the namespace.
                 * */
                void push_scope();

                /**
                 * \brief Pops the current (last) scope from the namespace.
                 * */
                void pop_scope();

                /**
                 * \brief Insert a declaration in the current scope.
                 * \param declaration The declaration to insert.
                 * \return True un success, false if the name of the declaration is already used in the current scope.
                 * */
                bool insert_declaration(AST::Declaration* declaration);

                /**
                 * \brief Find the first declaration (in the higher possible scope) that matches the given name and
                 * returns it (if possible).
                 * \param name The name to match.
                 * \return The first declaration that matches the given name.
                 * */
                std::optional<AST::Declaration*> find_declaration(const util::String& name);

            private:
                /**
                 * \brief Defines the Scope type.
                 * Contains the declarations of a single scope.
                 * */
                typedef std::map<util::String, AST::Declaration*> Scope;

                /**
                 * \brief The stack of scopes in the namespace.
                 * */
                std::vector<Scope> scopes;
            };
        }
    }
}

#endif

#include <prevc/pipeline/semantic_analysis/namespace.hxx>
#include <prevc/pipeline/AST/declaration.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            Namespace::Namespace()
            {
                // The first scope. The zero scope.
                push_scope();
            }

            Namespace::~Namespace()
            {
                while (!scopes.empty())
                    pop_scope();
            }

            void Namespace::push_scope()
            {
                scopes.emplace_back(Scope());
            }

            void Namespace::pop_scope()
            {
                scopes.pop_back();
            }

            bool Namespace::insert_declaration(prevc::pipeline::AST::Declaration* declaration)
            {
                auto   iterator         = scopes.back().insert(std::make_pair(declaration->name, declaration));
                bool   already_inserted = !iterator.second;
                bool   success          = !already_inserted;
                return success;
            }

            std::optional<AST::Declaration*> Namespace::find_declaration(const prevc::util::String& name)
            {
                for (auto scope = scopes.rbegin(), end = scopes.rend(); scope != end; ++scope)
                {
                    auto position = scope->find(name);

                    if (position == scope->end())
                        continue;

                    return position->second;
                }

                return {};
            }
        }
    }
}

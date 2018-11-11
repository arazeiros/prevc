#include <prevc/pipeline/AST/declarations.hxx>
#include <prevc/pipeline/AST/type-declaration.hxx>
#include <utility>
#include <prevc/pipeline/semantic_analysis/link-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Declarations::Declarations(Pipeline* pipeline, util::Location&& location, std::vector<Declaration*>&& declarations):
                CollectionNode(pipeline, std::move(location), std::move(declarations))
            {

            }

            void Declarations::check_semantics()
            {
                for (auto& declaration: *this)
                {
                    if (declaration->kind == Declaration::Kind::Type)
                    {
                        auto type_declaration = (AST::TypeDeclaration*) declaration;

                        pipeline->type_system->get_or_insert(type_declaration->name,
                            [&] () { return (semantic_analysis::LinkType*) type_declaration->get_semantic_type(); });
                    }
                }

                for (auto& declaration: *this)
                {
                    if (declaration->kind == Declaration::Kind::Type)
                    {
                        auto type_declaration = (AST::TypeDeclaration*) declaration;
                        pipeline->current_checking_declaration = type_declaration;
                        auto semantic_type = (semantic_analysis::LinkType*) type_declaration->get_semantic_type();
                        type_declaration->check_semantics();
                        semantic_type->set_real(type_declaration->generate_real_semantic_type());
                        pipeline->current_checking_declaration = nullptr;
                    }
                    else
                    {
                        declaration->check_semantics();
                    }
                }

                for (auto& declaration: *this)
                {
                    if (declaration->kind == Declaration::Kind::Type)
                    {
                        auto type_declaration = (AST::TypeDeclaration*) declaration;
                        auto semantic_type = (semantic_analysis::LinkType*) type_declaration->get_semantic_type();
                        semantic_type->compress();
                    }
                }
            }
        }
    }
}

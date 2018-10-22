#include <prevc/pipeline/AST/record-type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            RecordType::RecordType(Pipeline* pipeline, util::Location&& location, Components* components):
                Type(pipeline, std::move(location)),
                components(components),
                local_namespace(nullptr)
            {

            }

            RecordType::~RecordType()
            {
                delete components;

                if (local_namespace != nullptr)
                    delete local_namespace;
            }

            void RecordType::check_semantics()
            {
                local_namespace = new semantic_analysis::Namespace;

                for (auto& component : *components)
                {
                    if (local_namespace->insert_declaration(component))
                        continue;

                    auto  duplicate = local_namespace->find_declaration(component->name).value();
                    auto& location  = duplicate->location;

                    CompileTimeError::raise(pipeline->file_name, component->location,
                            util::String::format("record component `%s` already declared (at %d:%d)",
                                    component->name.c_str(), location.line_0, location.column_0));
                }

                components->check_semantics();
            }

            util::String RecordType::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "record-type", "location": %s, "components": %s})",
                        location.to_string().c_str(),
                        components->to_string().c_str());
            }
        }
    }
}

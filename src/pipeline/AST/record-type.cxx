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
                components(components)
            {

            }

            RecordType::~RecordType()
            {
                delete components;
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

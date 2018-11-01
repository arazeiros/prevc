#include <prevc/pipeline/semantic_analysis/record-type.hxx>
#include <sstream>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            static inline util::String to_semantic_string(const std::vector<std::pair<util::String, const Type*>>& subs)
            {
                std::stringstream stream;
                stream << "rec (";
                stream << subs.at(0).first.c_str() << ": " << subs.at(0).second->to_string().c_str();

                for (size_t i = 1; i < subs.size(); ++i)
                    stream << ", " << subs.at(i).first.c_str() << ": " << subs.at(i).second->to_string().c_str();

                stream << ")";
                return util::String(stream.str());
            }

            RecordType::RecordType(std::vector<std::pair<util::String, const Type*>>&& subs):
                Type(to_semantic_string(subs), Type::Kind::RECORD),
                subs(subs)
            {

            }

            std::optional<const Type*> RecordType::get_type_of(const util::String& component_name) const noexcept
            {
                for (auto& pair : subs)
                    if (pair.first == component_name)
                        return pair.second;

                return {};
            }

            util::String RecordType::to_string() const noexcept
            {
                return id;
            }
        }
    }
}

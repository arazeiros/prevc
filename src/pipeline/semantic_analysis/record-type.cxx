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
                ConcreteType(to_semantic_string(subs), Type::Kind::RECORD),
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

            bool RecordType::equals(const Type* other) const noexcept
            {
                if (!other->is_record())
                    return false;

                auto other_type = other->as_record();

                if (this == other_type)
                    return true;

                auto size = this->subs.size();

                if (size != other_type->subs.size())
                    return false;

                for (size_t i = 0; i < size; ++i)
                    if (!this->subs.at(i).second->equals(other_type->subs.at(i).second))
                        return false;

                return true;
            }

            util::String RecordType::to_string() const noexcept
            {
                return get_id();
            }
        }
    }
}

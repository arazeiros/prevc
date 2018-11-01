#include <prevc/pipeline/semantic_analysis/record-type.hxx>
#include <sstream>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            static inline util::String to_semantic_string(const std::vector<const Type*>& subs)
            {
                std::stringstream stream;
                stream << "rec (";
                stream << subs[0]->to_string().c_str();

                for (size_t i = 1; i < subs.size(); ++i)
                    stream << ", " << subs[i]->to_string().c_str();

                stream << ")";
                return util::String(stream.str());
            }

            RecordType::RecordType(std::vector<const Type*>&& subs):
                Type(to_semantic_string(subs), Type::Kind::RECORD),
                subs(subs)
            {

            }

            util::String RecordType::to_string() const noexcept
            {
                return id;
            }
        }
    }
}

#include <prevc/pipeline/semantic_analysis/link-type.hxx>
#include <prevc/pipeline/semantic_analysis/concrete-type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            LinkType::LinkType(util::String&& id):
                id(std::move(id)),
                real(nullptr)
            {

            }

            LinkType::~LinkType()
            {
                delete dynamic_cast<const ConcreteType*>(this->real);
            }

            void LinkType::set_real(const prevc::pipeline::semantic_analysis::Type *real) noexcept
            {
                this->real = real;
            }

            const util::String& LinkType::get_id() const noexcept
            {
                return id;
            }

            Type::Kind LinkType::get_kind() const noexcept
            {
                return this->real->get_kind();
            }

            const AtomType* LinkType::as_atom() const
            {
                return this->real->as_atom();
            }

            const ArrayType* LinkType::as_array() const
            {
                return this->real->as_array();
            }

            const RecordType* LinkType::as_record() const
            {
                return this->real->as_record();
            }

            const PointerType* LinkType::as_pointer() const
            {
                return this->real->as_pointer();
            }

            bool LinkType::equals(const Type* other) const noexcept
            {
                return this->real->equals(other);
            }

            util::String LinkType::to_string() const noexcept
            {
                return real != nullptr ? real->to_string() : this->id;
            }
        }
    }
}

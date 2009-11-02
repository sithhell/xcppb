
#ifndef XCPPB_EVENT_GENERIC_HPP
#define XCPPB_EVENT_GENERIC_HPP

namespace xcppb
{

namespace event
{

class generic
{
	public:

	private:
		uint8_t response_type;
		//uint8_t pad;
		uint16_t sequence;
		//uint32_t pad[7];
		uint32_t full_sequence;
};


} // end namespace event

} // end namespace xcppb

#endif


#ifndef XCPPB_PROTOCOL_REQUEST_HPP
#define XCPPB_PROTOCOL_REQUEST_HPP

namespace xcppb 
{

class protocol_request
{
	public:
		enum reply {
			NO_REPLY,
			EXPECT_REPLY
		};

		protocol_request( reply expect_repl, const std::vector<char>& d )
			: expect_reply_( expect_repl == EXPECT_REPLY ),
			  data_( d )
		{}

		const std::vector<char>& data() const
		{
			return data_;
		}

		bool expect_reply() const
		{
			return expect_reply_;
		}

	private:
		bool expect_reply_;
		std::vector<char> data_;
};

} // end namespace xcppb

#endif

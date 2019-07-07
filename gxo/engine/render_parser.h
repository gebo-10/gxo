#ifndef GXO_RENDER_PARSER_H
#define GXO_RENDER_PARSER_H
#include"pipeline.h"
namespace gxo {
	class RenderParser
	{
	public:
		std::stack<Pipeline> pipeline_stack;
		RenderParser()
		{
			
		}

		~RenderParser()
		{
		}

	private:

	};

}
#endif


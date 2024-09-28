#include "ColorPCH.h"
#include "RenderCommand.h"

namespace Color
{
	void RenderCommand::InitInstRendererAPI()
	{
		if (!s_RendererAPI)
		{
			s_RendererAPI = RendererAPI::Create();
		}
	}
}

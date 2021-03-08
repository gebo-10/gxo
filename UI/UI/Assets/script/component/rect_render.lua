RectRender = RectRender or BaseClass(Component)
function RectRender:__init()
	--每个render实现优化
	self.pre_render_command={}
	self.post_render_command={}
end

function RectRender:RenderBegin(node)
	--log("RectRender:RenderBegin")
	local rect=node._rect
	render:draw_rect(rect.x,rect.y,rect.w,rect.h,rect.x)
	--log(rect.x,rect.y,rect.w,rect.h,rect.x)
	if node.image ~= nil then
		render:draw_image(node.image.src,rect.x,rect.y,rect.w,rect.h)
	end
	if node.text ~= nil then
		render:draw_text(node.text.text,rect.x,rect.y+rect.h)
	end
end

function RectRender:RenderEnd()

end
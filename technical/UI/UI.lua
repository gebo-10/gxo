--[[
node={
	name="xxx",
	active=true,
	children={},
	parent=node,--weak

	pre_render_command={},
	post_render_command={},

	component={
		rect={x,y,w,h},
		layout={stretch={},anchor={},width,float,OnLayout,},

		event={
			OnClick=function,
			OnCatch=function,
			OnBubble=function,
		},

		MeshRender={OnRender,},
		Image={},
		Text={},
		Layer={},--cache image rendertarget renderpass
		renderpass={}

	},

}
]]
UI={
	dpi=100,
	point_focus=nil,
	key_focus=nil,
	root=nil,
}

EventProcessType={
	None=1,
	KeyFocus=2,
	PointFocus=3,
	Point=4,
}

Event={
	None={id=0,process=EventProcessType.None,name="None"},

	KeyDown={id=0,process=EventProcessType.None,name="KeyDown"},
	KeyUp={id=0,process=EventProcessType.None,name="KeyUp"},
	KeyFocusIn={id=0,process=EventProcessType.None,name="None"},
	KeyFocusOut={id=0,process=EventProcessType.None,name="None"},
	KeyEvent={id=0,process=EventProcessType.None,name="None"},

	Click={id=0,process=EventProcessType.None,name="None"},
	DoubleClick={id=0,process=EventProcessType.None,name="None"},
	PointIn={id=0,process=EventProcessType.None,name="None"},
	PointOut={id=0,process=EventProcessType.None,name="None"},
	PointEvent={id=0,process=EventProcessType.None,name="None"},

	Scroll={id=0,process=EventProcessType.None,name="Scroll"},
}

Input={
	type=Event.None,--表示当前没有事件
}

-- UI.DepthItr=1
-- UI.FlatItr=2
-- function UI.NodeList(node,type) --不同类型遍历
-- 	local list = {}
-- 	local depth_itr=function(node)
-- 		if node==nil or node.active==false then return end
-- 		for i,v in ipairs(node.children) do
-- 			itr(v)
-- 			table.insert(list,node)
-- 		end
-- 	end
-- 	local flat_itr=function(node)
-- 		table.insert(list,node)
-- 		for i,v in ipairs(node.children) do
-- 			table.insert(list,v)
-- 			itr(v)
-- 		end
-- 	end


-- 	if type==UI.DepthItr then
-- 		depth_itr(node)
-- 	else
-- 		flat_itr(node)
-- 	end
-- 	return list
-- end
----------------------------------------------------------------------
function UI.IsIn(node,x,y)
	local rect=node.component.rect
	if rect == nil then return true end --没有继承父节点 直接 in
	if x< rect.x then return false end
	if y< rect.y then return false end
	if x> rect.x+rect.w then return false end
	if y> rect.y+rect.h then return false end
	return true
end

function UI.FindNode(node,x,y)--ray octree btree gpupick
	local nodes={}

	local itr=function(node)
		if node==nil or node.active==false then return end
		if not UI.IsIn(node,x,y) then
			return
		end
		if node.component.event ~= nil then
			table.insert(nodes,node)
		end
		for i,v in ipairs(node.children) do
			itr(v)
		end
	end
	itr(UI.root)

	return nodes

end

function UI.ChangePointFocus(node)
	if UI.point_focus == nil then return end
	if UI.point_focus== node then return end
	UI.point_focus.event.OnPointOut(UI.point_focus)
	UI.point_focus= node
end

function UI.Event()
	local process={
		[EventProcessType.None]=function()
			return nil
		end,
		[EventProcessType.KeyFocus]=function()
			return UI.key_focus.event["On"..Input.type.name](UI.key_focus)
		end,
		[EventProcessType.PointFocus]=function()
			return UI.point_focus.event["On"..Input.type.name](UI.point_focus)
		end,
		[EventProcessType.Point]=function()
			local nodes=UI.FindNode(UI.root,x,y)
			if #nodes==0 then return end
			
			for i=1,#nodes-1 do
				node.event["OnCatch"](node,Input.type.name)  --catch 可以判断返回以截取
			end

			nodes[#nodes-1].event["On"..Input.type.name](node)
			
			for i=#nodes-1,1 do
				node.event["OnBubble"](node,Input.type.name)  --bubble 可以判断返回以截取
			end
			UI.ChangePointFocus(nodes[#nodes-1])
			return
		end,
	}
	process[Input.type.process]()
end

-------------------------------------------------------------------------
function UI.DefaultLayoutBegin()
end
function UI.DefaultLayoutEnd()
end
function UI.Layout()
	local pre=function(node)
		for k,comp in pairs(node.component) do
			local layout=comp.OnLayoutBegin or  UI.DefaultLayoutBegin
			layout(v)
		end
	end
	local post=function(node)
		for k,comp in pairs(node.component) do
			local layout=comp.OnLayoutEnd or  UI.DefaultLayoutEnd
			layout(v)
		end
	end
	local itr=function(node)
		if node==nil or node.active==false then return end
		pre(node)
		for i,v in ipairs(node.children) do
			itr(v)
		end
		post(node)
	end
	itr(UI.root)
end
-------------------------------------------------------------------------
function UI.DefaultRenderBegin()

end
function UI.DefaultRenderEnd()
end
-- --生成渲染命令
-- function UI.RenderCommand()
-- 	local nodes=UI.NodeList(UI.root,UI.DepthItr)
-- 	for i,node in ipairs(nodes) do
-- 		for k,comp in pairs(node.component) do
-- 			local render=comp.OnRender or  UI.DefaultRender
-- 			render(v)
-- 		end
-- 	end
-- end

--渲染各个target Layer view
function UI.Render()
	local pre=function(node)
		for k,comp in pairs(node.component) do
			local render=comp.OnRenderBegin or  UI.DefaultRenderBegin
			render(v)
		end
	end
	local post=function(node)
		for k,comp in pairs(node.component) do
			local render=comp.OnRenderEnd or  UI.DefaultRenderEnd
			render(v)
		end
	end
	local itr=function(node)
		if node==nil or node.active==false then return end
		pre(node)
		for i,v in ipairs(node.children) do
			itr(v)
		end
		post(node)
	end
	itr(UI.root)
end


------------------------------------------------------------------------------------
--混合图层 最后输出
function UI.Compose()
	local compose=function (node )
		if node.component.Layer ~= nil then
			--todo draw target
		end
	end
	local itr=function(node)
		if node==nil or node.active==false then return end
		compose(node)
		for i,v in ipairs(node.children) do
			itr(v)
		end
	end
	itr(UI.root)
end
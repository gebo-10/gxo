--[[
node={
	name="xxx",
	active=true,
	children={},
	parent=node,--weak
	render_command={},
	component={
		rect={stretch={},anchor={},},
		layout={width,float,OnLayout,},
		MeshRender={OnRender,},
		Image={},
		Text={},
		Layer={},--cache image rendertarget
		renderpass={}

	},
	OnClick=function,
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

UI.DepthItr=1
UI.FlatItr=2
function UI.NodeList(node,type) --不同类型遍历
	local list = {}
	local depth_itr=function(node)
		if node==nil or node.active==false then return end
		for i,v in ipairs(node.children) do
			itr(v)
			table.insert(list,node)
		end
	end
	local flat_itr=function(node)
		table.insert(list,node)
		for i,v in ipairs(node.children) do
			table.insert(list,v)
			itr(v)
		end
	end


	if type==UI.DepthItr then
		depth_itr(node)
	else
		flat_itr(node)
	end
	return list
end
----------------------------------------------------------------------

function UI.FindNode(node,x,y)--ray octree btree gpupick

end

function UI.Event()
	local process={
		[EventProcessType.None]=function()
			return nil
		end,
		[EventProcessType.KeyFocus]=function()
			return UI.key_focus
		end,
		[EventProcessType.PointFocus]=function()
			return UI.point_focus
		end,
		[EventProcessType.Point]=function()
			return UI.FindNode(UI.root,x,y)
		end,
	}
	local select_node=process[Input.type.process]()
	if not select_node then return end
	for k,v in pairs(select_node.component) do
		v["On"..Input.type.name](select_node)
	end
	
end

-------------------------------------------------------------------------
function UI.DefaultLayout()


end

function UI.Layout()
	local nodes=UI.NodeList(UI.root,UI.DepthItr)
	for i,node in ipairs(nodes) do
		for k,comp in pairs(node.component) do
			local layout=comp.OnLayout or  UI.DefaultLayout
			layout(v)
		end
	end
end
-------------------------------------------------------------------------
function UI.DefaultRender()


end

--生成渲染命令
function UI.RenderCommand()
	local nodes=UI.NodeList(UI.root,UI.DepthItr)
	for i,node in ipairs(nodes) do
		for k,comp in pairs(node.component) do
			local render=comp.OnRender or  UI.DefaultRender
			render(v)
		end
	end
end

--渲染各个target Layer view
function UI.Render()
	local nodes=UI.NodeList(UI.root,UI.FlatItr)
	for i,node in ipairs(nodes) do
		for j,cmd in ipairs(node.render_command) do
			submit(cmd) 	
		end 
	end
end


------------------------------------------------------------------------------------
--混合图层 最后输出
function UI.Compose()


end
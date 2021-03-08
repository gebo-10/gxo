--[[
Node={
	name="xxx",
	id=0,
	active=true,
	children={},
	parent=node,--weak

	
	rect={x,y,w,h},
	transform=mat3
	scale={x=0,y=0}
	rotation={x=0,y=0,z=0}

	layout={stretch={},anchor={},width,float,OnLayout,}, -- anchor layout
	--layout={width  height  },--rect layout

	EventTarget=true,
	-- OnClick=function,
	-- OnCatch=function,
	-- OnBubble=function,
	-- OnHover=function,
	-- OnPointIn
	-- OnPointout

	
	Layer={visible=true,rendertarget},--cache rendertarget
	render={
		pre_render_command={},
		post_render_command={},
		renderpass=iamge,text,myrenderpass,selfrender filter 配置组件 调用组件渲染
	}

	-- MeshRender={OnRender,},
	-- Image={OnRender},
	-- Text={OnRender},
}
]]
UI={
	dpi=100,
	point_focus=nil,
	key_focus=nil,
	hover_nodes=nil,
	root=nil,
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

-- function UI.ChangePointFocus(node)
-- 	if UI.point_focus == nil then return end
-- 	if UI.point_focus== node then return end
-- 	--UI.point_focus.event.OnPointOut(UI.point_focus)
-- 	UI.RunEventHandle(UI.point_focus,"OnPoint")
-- 	UI.point_focus= node
-- end


-------------------------------------------------------------------------

-------------------------------------------------------------------------


------------------------------------------------------------------------------------
UI.root=UI.NewNode()
	UI.root.name="root"
	UI.root.component.rect={x=0,y=0,w=640,h=480}
	UI.root.component.event={}

	local n1=UI.NewNode()
	UI.AddNode(UI.root,n1)
	n1.name="n1"
	n1.component.rect={x=0,y=0,w=100,h=200}
	n1.component.event={
		OnPointMove=function ()
			print("In")
		end
	}

	local n2=UI.NewNode()
	n2.name="n2"
	n2.component.rect={x=200,y=300,w=100,h=200}
	n2.component.event={
		OnPointMove=function ()
			--print("In2")
		end,
		OnPointOut=function ()
			print("OnPointOut2")
		end,
		OnPointIn=function ()
			print("OnPointIn2")
		end,
		OnCatch=function ( )
			print("OnCatch2")
		end,
		OnBubble=function ( )
			print("OnBubble2")
		end
	}
	UI.AddNode(UI.root,n2)

	local n4=UI.NewNode()
	n4.name="n4"
	UI.AddNode(n2,n4)

	local n3=UI.NewNode()
	n3.name="n3"
	n3.component.rect={x=210,y=310,w=50,h=50}
	n3.component.event={
		OnPointMove=function ()
			--print("In3")
		end,
		OnPointOut=function ()
			print("OnPointOut3")
			n3.component.image=nil
		end,
		OnPointIn=function ()
			print("OnPointIn3")
			n3.component.image={
				OnRenderBegin=function ()
					render:draw_image("image/1.png",210,310,50,50)
				end,
			}
		end,
		OnPointDown=function ()
			print("OnPointDown3")
		end,
		OnPointUp=function ()
			print("OnPointUp3")
		end,
		OnClick=function ()
			print("OnClick3")
		end,
		OnDoubleClick=function ()
			print("OnDoubleClick3")
		end,
	}
	
	UI.AddNode(n4,n3)
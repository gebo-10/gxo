--[[
Node={
	name="xxx",
	id=0,
	active=true,
	__children={},
	__parent=node,--weak
	

	layout={stretch={},anchor={},width,float,OnLayout,}, -- anchor layout
	--layout={width  height  },--rect layout

	event={
		-- OnClick=function,
		-- OnCatch=function,
		-- OnBubble=function,
		-- OnHover=function,
		-- OnPointIn
		-- OnPointout
	}

	
	animation={} 
	
	Layer={visible=true,rendertarget},--cache rendertarget
	render={
		clipchild=true,
		pre_render_command={},
		post_render_command={},
		renderpass=iamge,text,myrenderpass,selfrender filter 配置组件 调用组件渲染
	}
	

	-- Mesh={OnRender,},
	-- Image={OnRender},
	-- Text={OnRender},
}
]]
--改写node的baseclass 吧————index 用于寻找子元素
Node = Node or BaseClass()
function Node:__init()
	self.name="Node"
	self.id=0
	self.active=true
	self._children={}
	self._parent=nil--weak
	self._rect={x=0,y=0,w=0,h=0}
	self._transform=nil
end

function Node:AddComponent(name,comp)
	self[name]=comp
end

function Node:RemoveComponent(name)
	self[name]=nil
end

function Node:GetAllComponent()
	local comps={}
	for k,v in pairs(self) do
		if type(v)=="table" and v.enable~=nil then
			table.insert( comps,v )
		end
	end
	return comps
end


function Node:AddChild(node)
	--所有父节点 dirty
	table.insert(self._children,node)
	node._parent=self
end
function Node:RemoveChild(node)
	--所有父节点 dirty
	local get=false
	for i,v in ipairs(self._children) do
		if node==v then
			get=true
		end
	end
	if get then 
		log("ERROR: Node:RemoveChild can find node")
		return
	end
	table.remove(self._children,node)
	node._parent=nil
end

-- function Node:SetDirty()
-- 	--上级view dirty
-- end

-- function Node:OnLayoutBegin()

-- end
-- function Node:OnLayoutEnd()

-- end

-- function Node:OnRenderBegin()
	
-- end
-- function Node:OnRenderEnd()

-- end

-- function Node:OnEvent()
	
-- end
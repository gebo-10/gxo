EventProcessType={
	None=1,
	KeyFocus=2,
	PointFocus=3,
	Point=4,
}

Event={
	None={id=0,process=EventProcessType.None,name="None"},

	KeyDown={id=1,process=EventProcessType.None,name="KeyDown"},
	KeyUp={id=2,process=EventProcessType.None,name="KeyUp"},
	KeyFocusIn={id=3,process=EventProcessType.None,name="KeyFocusIn"},
	KeyFocusOut={id=4,process=EventProcessType.None,name="KeyFocusOut"},

	PointDown={id=5,process=EventProcessType.Point,name="PointDown"},
	PointUp={id=6,process=EventProcessType.Point,name="PointUp"},
	Click={id=7,process=EventProcessType.Point,name="Click"},
	DoubleClick={id=8,process=EventProcessType.Point,name="DoubleClick"},
	PointMove={id=9,process=EventProcessType.Point,name="PointMove"},
	PointIn={id=10,process=EventProcessType.None,name="PointIn"},
	PointOut={id=11,process=EventProcessType.None,name="PointOut"},

	--PointGetFocus={id=12,process=EventProcessType.None,name="PointGetFocus"},
	--PointLostFocus={id=13,process=EventProcessType.None,name="PointLostFocus"},

	Scroll={id=12,process=EventProcessType.None,name="Scroll"},
}

Input={
	type=Event.None,--表示当前没有事件
}

EventSystem = EventSystem or BaseClass()
function EventSystem:__init()
	self.event_queue={}
	self.hover_nodes={}
	self.point_focus=nil
	self.key_focus=nil
end

function EventSystem:AddEvent()

end

function EventSystem:RunEventHandle(node,name,...)
	--print(name)
	local event=node.event
	if event and event[name] then
		event[name](node,...)
	end
end

function EventSystem:Hover(nodes)
	-- for i,v in ipairs(nodes) do
	-- 	print("nnnnnnnnnnnnnn",v.name)
	-- end
	local d1,d2=Util.Diff(self.hover_nodes,nodes)
	for i,v in ipairs(d1) do
		self:RunEventHandle(v,"OnPointOut")
	end

	for i,v in ipairs(d2) do
		self:RunEventHandle(v,"OnPointIn")
	end
	self.hover_nodes=nodes
end

function EventSystem:Event()
	local process={
		[EventProcessType.None]=function()
			return nil
		end,
		[EventProcessType.KeyFocus]=function()
			return self.key_focus.event["On"..Input.type.name](self.key_focus)
		end,
		[EventProcessType.PointFocus]=function()
			return self.point_focus.event["On"..Input.type.name](self.point_focus)
		end,
		[EventProcessType.Point]=function()
			local nodes=UI.tree:FindNode(Input.x,Input.y)

			if #nodes==0 then return end
			--print(#nodes)
			--catch 可以判断返回以截取
			for i=1,#nodes-1 do
				self:RunEventHandle(nodes[i],"OnCatch",Input.type.name)
			end
			--log(Input.type.name)
			self:RunEventHandle(nodes[#nodes],"On"..Input.type.name)

			--bubble 可以判断返回以截取
			
			for i=#nodes-1,1,-1 do
				self:RunEventHandle(nodes[i],"OnBubble",Input.type.name)
			end
			

			--point 焦点事件 有hover 不需要focus
			--UI.ChangePointFocus(nodes[#nodes])

			--point hover事件
			if Input.type.name=="PointMove" then
				self:Hover(nodes)
			end
			return
		end,
	}
	process[Input.type.process]()
	Input.type=Event.None
end

RenderSystem = RenderSystem or BaseClass()
function RenderSystem:__init()
	
end

--渲染各个target Layer view
function RenderSystem:Render(root)
	local pre=function(node)
		if node.render== nil then return end
		node.render:RenderBegin(node)
	end
	local post=function(node)
		if node.render== nil then return end
		node.render:RenderEnd(node)
	end
	local itr=nil
	itr=function(node)
		if node==nil or node.active==false then return end
		pre(node)
		for i,v in ipairs(node._children) do
			itr(v)
		end
		post(node)
	end
	itr(root)
end

------------------------------------------------------------------------------------
--混合图层 最后输出
function RenderSystem:Compose()
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
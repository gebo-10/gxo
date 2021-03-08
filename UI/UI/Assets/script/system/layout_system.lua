LayoutSystem = LayoutSystem or BaseClass()
function LayoutSystem:__init()
	
end

function LayoutSystem:Layout(root)
	local pre=function(node)
		if node._parent==nil then return end
		if node.lauout~= nil then
			node._rect=node._parent._rect
			node._transform=nil
		end
		return node.layout:LayoutBegin(node)
	end
	local post=function(node)
		
	end
	local itr
	itr=function(node)
		if node==nil or node.active==false then return end
		pre(node)
		for i,v in ipairs(node._children) do
			itr(v)
		end
		--post(node)
	end
	itr(root)
end
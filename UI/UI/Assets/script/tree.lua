Tree = Tree or BaseClass()
function Tree:__init()
	self.root=Node.New()
	self.node_list={} --weak
end

function Tree:CreateNode()
	local node=Node.New()
	table.insert(self.node_list,node)
	return node
end

function Tree:DestoryNode(node)

end

----------------------------------------------------------------------
function Tree:IsIn(node,x,y)
	local rect=node._rect
	--print(x,y)
	--print_lua_table(rect)
	if rect== nil then return true end --没有继承父节点 直接 in
	if x< rect.x then return false end
	if y< rect.y then return false end
	if x> rect.x+rect.w then return false end
	if y> rect.y+rect.h then return false end
	--print("find")
	return true
end

function Tree:FindNode(x,y)--ray octree btree gpupick
	local nodes={}

	local itr=nil
	itr=function(node)
		if node==nil or node.active==false then return end
		if not self:IsIn(node,x,y) then
			return
		end
		if node.event ~= nil then
			table.insert(nodes,node)
		end
		for i,v in ipairs(node._children) do
			itr(v)
		end
	end
	itr(self.root)

	return nodes

end
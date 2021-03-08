AnchorLayout = AnchorLayout or BaseClass(Component)
function AnchorLayout:__init()
	self.anchor_min={x=0.5,y=0.5}
	self.anchor_max={x=0.5,y=0.5}
	self.offset_min={x=0,y=0}
	self.offset_max={x=0,y=0}
	self.pivot={x=0.5,y=0.5}
	self.scale={x=0,y=0}
	self.rotation={x=0,y=0,z=0}
end


function AnchorLayout:GetRect(parent_rect)
	local x= parent_rect.x+(parent_rect.w*self.anchor_min.x)+self.offset_min.x
	local y= parent_rect.y+(parent_rect.h*self.anchor_min.y)+self.offset_min.y

	local x2= parent_rect.x+(parent_rect.w*self.anchor_max.x)-self.offset_max.x
	local y2= parent_rect.y+(parent_rect.h*self.anchor_max.y)-self.offset_max.y
	return {x=x,y=y,w=x2-x,h=y2-y}
end



function AnchorLayout:GetTransform(parent_trasnform)

end

function AnchorLayout:LayoutBegin(node)
	node._rect=self:GetRect(node._parent._rect)
	node._transform=nil
end

function AnchorLayout:LayoutEnd(node)

end
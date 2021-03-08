print("LuaStart---------------------------")
require "script.UI"
function InitUi()
	UI:Init()
	local  root=UI.tree.root
	root._rect={x=0,y=0,w=640,h=480}
	root.render=RectRender.New()
	root.event={}

	local n1=UI.tree:CreateNode()
	n1.name="n1"
	n1.render=RectRender.New()

	n1.layout=AnchorLayout.New()
	n1.layout.anchor_min={x=0,y=0}
	n1.layout.anchor_max={x=1,y=1}

	n1.layout.offset_min={x=100,y=20}
	n1.layout.offset_max={x=10,y=100}
	root:AddChild(n1)


	local n2=UI.tree:CreateNode()
	n2.name="n2"
	n2.render=RectRender.New()

	n2.layout=AnchorLayout.New()
	n2.layout.anchor_min={x=0,y=0}
	n2.layout.anchor_max={x=1,y=1}

	n2.layout.offset_min={x=10,y=20}
	n2.layout.offset_max={x=0,y=10}
	n1:AddChild(n2)

	n2.event={
		OnPointMove=function ()
			--print("In3")
		end,
		OnPointOut=function ()
			print("OnPointOut3")
			n2.image=nil
		end,
		OnPointIn=function ()
			print("OnPointIn3")
			n2.image={
				src="image/1.png",
			}
			n2.text={
				text="xxxxx",
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

end
InitUi()
function Update()
	UI:Update()
end

function OnPointMove(x,y)
	--print(x,y)
	Input.type=Event.PointMove
	Input.x=x
	Input.y=y
end
-- PointActinType={
-- 	GLFW_RELEASE=0,
-- 	GLFW_PRESS=1,
-- 	GLFW_REPEAT=3,
-- }
function OnMouseButton(button,action,mode,x,y)
	--print(x,y)
	if action==1 then
		Input.type=Event.PointDown
	elseif action==0 then
		Input.type=Event.PointUp
	elseif action==9 then
		Input.type=Event.Click
	elseif action==10 then
		Input.type=Event.DoubleClick
	end
	
	Input.x=x
	Input.y=y
end


function OnSize(x,y )
	UI.tree.root._rect={x=0,y=0,w=x,h=y}
end
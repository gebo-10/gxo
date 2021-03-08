require('script.util.util')
require("script.base.baseclass")
require('script.base.node')

require('script.component.component')
require('script.component.anchor_layout')
require('script.component.rect_render')

require('script.system.event_system')
require('script.system.layout_system')
require('script.system.logic_system')
require('script.system.render_system')

require('script.tree')
UI={
	dpi=100,

	tree=nil,

	layout_system=nil,
	event_system=nil,
	render_system=nil,
	logic_system=nil,
}

function UI:Init( )
	self.tree=Tree.New()
	self.event_system=EventSystem.New()
	self.logic_system=LogicSystem.New()
	self.layout_system=LayoutSystem.New()
	self.render_system=RenderSystem.New()
end

function UI:Update( )
	self.event_system:Event()
	self.logic_system:Update()
	self.layout_system:Layout(self.tree.root)
	self.render_system:Render(self.tree.root)
end
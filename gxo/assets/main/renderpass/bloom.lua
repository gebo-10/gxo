GPUType={
	Int=1,
	Float=2,
	Sample2d=3,
	Matrix=4,
}

CahcheType={
	In=1,
	Tmp=2,
	Static=3,
	Dynamic=3,
}

ResourceType={
	Texture=1,
	RenderTexture=2
	Matrix=3,
}

VertType={
	Plane=1,
	Scene=2,
	--Translate,Opcation, custom vert={xxx},index={xxx}
}

RendetTargetType={
	Texture=1,
	RenderTarget=2,
}

ColorFormat={
	RGBA=1,
	RGB16F=2,
}
--------------------------------------------------------------------------------
BloomMaterial={
	shader={vs="", fs="",gs=nil},
	uniform={
		mvp={type=GPUType.Matrix},
		time={type=GPUType.Float,default=0},
		texture={type=GPUType.Sample2d,default=0}
	},
}

BlurMaterial={
	shader={vs="", fs="",gs=nil},
	uniform={
		time={type=GPUType.Float,default=0},
		texture={type=GPUType.Sample2d,default=0}
	},
}

HdrPass={
	in={},
	out={type=RendetTargetType.Screen,}--RenderTarget,
	material=BloomMaterial,
}

BlurPass={
	vert={type=VertType.Plane}
	in={
		texture="texture1",
	},
	out={
		type=RenderTarget,
		width=100,
		height=100,
		msaa=true,
		texture={"texture2"}
	},
	material=BloomMaterial,
	depth_test=true,
	sctilon_test=false,
	blend=true,
}

BloomRenderPass={
	resource={
		MVP={cache=CahcheType.In,type=ResourceType.Matrix},
		texture1={cache=CahcheType.In,type=ResourceType.Texture,msaa=true},
		texture2={cache=CahcheType.Tmp,type=ResourceType.RenderTexture,width=100,height=100,format=ColorFormat.RGBA},
	},
	pass={
		[1]=BloomHdrPass,
		[2]=BlurPass,
	},

}
--[[
system pass
clearpass

]]
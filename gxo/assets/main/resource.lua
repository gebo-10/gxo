Resource={
	Name="main",
	SubResource={
		{"main1","main2"},
	},
	Shader={
		{
			name="Default",
			vs="shader/default.vert.glsl",
			fs="shader/default.frag.glsl",
			uniform={
				{"time",0},
				{"mvp",2},
			},
		},
	},

	Texture={
		{
			name="1",
			image="texture/1.jpeg",
			min_filter=0,
			mag_filter=0,
			mipmip=0,
			warp_mode=0,
			anisotropy=0,

			cache_type=0,
			memery_type=0,
		},

	},
	RenderTarget={
		{
			name="target1",
			width=500,
			height=500,

			cache_type=0,
			memery_type=0,
		},
	},
	Material={
		{
			name="Default",
			shader="main/shader/Default",
			uniform={
				{"time",0},
				{"mvp",2},
			},
		},
	},
	Mesh={
		{

		},
	},
	Script={
		{

		},
	},
	Font={
		{

		},
	},
}
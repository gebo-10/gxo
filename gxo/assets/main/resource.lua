GPUDataType={
	GPU_BYTE=0,
	GPU_SHORT=1,
	GPU_USHORT=2,
	GPU_INT=3,
	GPU_UINT=4,
	GPU_HALF_FLOAT=5,
	GPU_FLOAT=6,
	GPU_VEC2=7,
	GPU_VEC3=8,
	GPU_VEC4=9,
	GPU_MAT3=10,
	GPU_MAT4=11,
	GPU_SAMPLE2D =12
}

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
		},
		{
			name="Texture",
			vs="shader/texture.vert.glsl",
			fs="shader/texture.frag.glsl",
		},
	},

	Texture={
		{
			name="1",
			image="texture/1.jpeg",
			width=640,
			height=510;
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
				--{"time",GPUDataType.GPU_FLOAT,0},
				--{"mvp",GPUDataType.GPU_MAT4,1},
			},
		},
		{
			name="Texture",
			shader="main/shader/Texture",
			uniform={
				{"texture0",GPUDataType.GPU_SAMPLE2D,"main/texture/1"},
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
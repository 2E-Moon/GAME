//==============================================================
// �O���[�o���ϐ�
//==============================================================
// �ϊ��s��
float4x4 mW;		// ���[���h�s��
float4x4 mV;		// �r���[�s��
float4x4 mP;		// �ˉe�s��

// �}�e���A���֌W
float4	Diffuse = float4(1, 1, 1, 1);	// ��{�F
float	Ambient = 0.3;				// �����̋���
float4	Specular = float4(1, 1, 1, 1);	// ���ːF
float	Power = 50;					// ���ːF�̗�

texture MeshTex;	// �}�e���A���̃e�N�X�`��
sampler MeshSmp = sampler_state {	// MeshTex�p�T���v��
	Texture = <MeshTex>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

// ���C�g�p
float3 LightDir;	// ���C�g�̕���

// �J�����p
float3 CamPos;		// ���_�̈ʒu

// �g�D�[���p
texture ToonTex;	// �A�e�p�e�N�X�`��
sampler ToonSmp = sampler_state {	// ToonTex�p�T���v��
	Texture = <ToonTex>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

//==============================================================
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^�p�\����
//==============================================================
struct VS_OUT {
	float4 Pos		: POSITION;		// 2D���W
	float2 MeshUV	: TEXCOORD0;	// �e�N�X�`��UV

	float3 wPos		: TEXCOORD1;	// 3D���W
	float3 wN		: TEXCOORD2;	// �@��
};

//==============================================================
// ���_�V�F�[�_
//	�E���_���P�����Ă���̂ŁA������������s�N�Z���V�F�[�_�ɓn���B
//==============================================================
VS_OUT VS(
	float4 pos : POSITION,				// ���W
	float3 normal : NORMAL,				// �@��
	float2 mesh_uv : TEXCOORD0			// �e�N�X�`��UV
	) {
	VS_OUT Out = (VS_OUT)0;		// �s�N�Z���f�[�^�ɓn���f�[�^�p�\����

	// ���_���W
	Out.Pos = mul(pos, mW);
	Out.wPos = Out.Pos.xyz;	// 3D��Ԃł̍��W�ɂȂ�
	Out.Pos = mul(Out.Pos, mV);	// 3D�J�������W�n�ł̍��W�ɂȂ�
	Out.Pos = mul(Out.Pos, mP);	// 2D��Ԃł̍��W�ɂȂ�

	// �e�N�X�`�����W
	Out.MeshUV = mesh_uv;

	// �@��
	float3 w_normal = normalize(mul(normal, (float3x3)mW));	// ���[���h�n�ɕϊ�
		Out.wN = w_normal;

	return Out;
}


//==================================================================
// �s�N�Z���V�F�[�_
//	�E�s�N�Z���̐F�����肵�A���̐F��Ԃ�(R,G,B,A��float4�^)
//==================================================================
float4 PS(VS_OUT In) : COLOR0
{
	// �@���𐳋K��
	float3 w_normal = normalize(In.wN);

	//================================================
	// ���C�e�B���O(�����o�[�g�Ɩ�)
	//================================================
	float LPow = dot(-LightDir, w_normal);	// ���̋��� -1�`1
	LPow = max(0, LPow);	// 0�`1

	//================================================
	// �g�D�[���e�N�X�`�����疾�邳�擾
	//================================================
	float4 ToonCol = tex2D(ToonSmp, float2(LPow + Ambient, 0));

	//================================================
	// �X�y�L����
	//================================================
	float3 vCam = normalize(CamPos - In.wPos);		// ��(�J����)�ւ̕���
	float3 vRef = LightDir + 2.0f * dot(w_normal, -LightDir) * w_normal;
	float SpePow = pow(max(0, dot(vCam, vRef)), Power);
	float4 Spe = Specular * SpePow;

	//================================================
	// ���f���F�Z�o
	//================================================
	// �ŏI�I�ȃ��f���̐F������ϐ�
	float4 Col = tex2D(MeshSmp, In.MeshUV);	// �܂��̓e�N�X�`���F������

	//================================================
	// �ގ��F����
	//================================================
	Col *= Diffuse;

	//================================================
	// ���C�e�B���O�K�p
	//================================================
	// ���C�g�̓�����̋���+����
	Col.rgb *= ToonCol.rgb;// min(1, LPow + Ambient);

	//================================================
	// �F���o��
	//================================================
	return Col + Spe;
}

//==============================================================
// �e�N�j�b�N
//==============================================================
technique Tech {
	pass P0 {
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}

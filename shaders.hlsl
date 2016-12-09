struct VIn {
	float4 position : POSITION;
	float4 normal : NORMAL;
	float4 tangent : TANGENT;
	float2 texcoord : TEXCOORD;
	float4 colour : COLOR;
};

struct VOut
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
	float4 colour : COLOR;
	float3 Vdir : VDIR;
	float3 Ldir : LDIR;
	float3 t : TANGENT;
};

cbuffer uniforms
{
	float4x4 MVP;
	float4x4 MV;
	float4x4 ITMV;
	float4 diffuse;
	float4 specular;
	float4 Vpos;
	float4 Lpos;
};

VOut VShader(VIn input)
{
	VOut output;

	float4 transformedPos = mul(input.position, MVP);

	output.position = transformedPos;
	float4 normal = mul(input.normal, ITMV);
	output.normal = normal.xyz;
	output.texcoord = input.texcoord;
	output.colour = input.colour;

	float3 tangent = mul(input.tangent, ITMV).xyz;
	output.t = tangent;
	
	float3 binormal = cross(normal.xyz, tangent.xyz);

	float3x3 TBN = float3x3(tangent,
							binormal,
							normal.xyz);



	float4 calculatedVpos = mul(input.position, MV);
	output.Vdir = mul(-calculatedVpos.xyz, TBN);
	output.Ldir = mul(Lpos - calculatedVpos, TBN);

	return output;
}

Texture2D textures[3];

SamplerState samplerState;

float4 PShader(VOut input) : SV_TARGET
{
	float3 l = normalize(input.Ldir);
	float3 v = normalize(input.Vdir);

	float3 h = normalize(v + l);

	float4 diffTexel = textures[0].Sample(samplerState, input.texcoord);
	float4 specTexel = textures[1].Sample(samplerState, input.texcoord);
	float4 normTexel = textures[2].Sample(samplerState, input.texcoord);

	float3 n = normalize(normTexel.xyz * 2.0 - 1.0);

	float specLight = pow(max(dot(n, h), 0.0), specular.a);
	float diffLight = max(dot(n, l), 0.0);

	float4 ambient = diffTexel * diffuse * 0.2;
	float4 diffColor = diffTexel * diffuse * diffLight;
	float4 specColor = float4(specTexel * specular.xyz * specLight, 0.0);

	return diffColor + specColor + ambient;
}
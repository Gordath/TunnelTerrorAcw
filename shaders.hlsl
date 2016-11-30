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
	output.normal = mul(input.normal, ITMV);
	output.texcoord = input.texcoord;
	output.colour = input.colour;

	float4 calculatedVpos = mul(input.position, MV);
	output.Vdir = -calculatedVpos.xyz;
	output.Ldir = Lpos - calculatedVpos;

	return output;
}

float4 PShader(VOut input) : SV_TARGET
{
	float3 n = normalize(input.normal);
	float3 l = normalize(input.Ldir);
	float3 v = normalize(input.Vdir);

	float3 h = normalize(v + l);

	float specLight = pow(max(dot(n, h), 0.0), specular.a);
	float diffLight = max(dot(n, l), 0.0);
    
	float4 diffColor = diffuse * diffLight;//float4(n + 1, 1.0) * diffLight;
	float4 specColor = float4(specular.xyz * specLight, 1.0);

	return diffColor + specColor;
}
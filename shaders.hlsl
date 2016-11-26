struct VOut
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 texcoord : TEXCOORD;
	float4 colour : COLOR;
};

cbuffer uniforms
{
	float4x4 MVM;
	float4 globalColour;

};

VOut VShader(float4 position : POSITION,
	         float3 normal : NORMAL,
	         float3 tangent : TANGENT,
			 float2 texcoord : TEXCOORD,
	         float4 colour : COLOR)
{
	VOut output;

	float4 transformedPos = mul(position, MVM);

	output.position = transformedPos;
	// pass the normal after we calculate the inverse transpose of the matrix;
	output.normal = normal;
	output.texcoord = texcoord;
	output.colour = colour;

	return output;
}


float4 PShader(float4 position : SV_POSITION,
			   float3 normal : NORMAL,
			   float2 texcoord : TEXCOORD,
			   float4 color : COLOR) : SV_TARGET
{
	return color * globalColour;
}
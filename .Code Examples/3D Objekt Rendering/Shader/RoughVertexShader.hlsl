struct Input
{
    float4 inPosition : POSITION;
    float4 inColor : COLOR;
    float2 inTexture : TEXCOORD;
    float3 inNormal : NORMAL;
    float3 inTangent : TANGENT;
    float3 inBinormal : BINORMAL;
};

/*****************************************************************************/
//Vertex-Ausgabe-Struktur
/*****************************************************************************/
struct Output
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
    float3 viewDirection : TEXCOORD1;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};
/*****************************************************************************/

/*****************************************************************************/
//per Object (Matrix-Constant-Buffer)
/*****************************************************************************/
cbuffer ObjMatrixCB
{
    float4x4 wvpMatrix;
    float4x4 worldMatrix;
    float4 cameraPosition;
};
/*****************************************************************************/

/*****************************************************************************/
// Vertex-Shader
/*****************************************************************************/
Output main(Input input)
{
    float fOne = 1.0;
    
    /*-----------------------------------------------------------------------*/
    //Ausgabe
    /*-----------------------------------------------------------------------*/
    Output output;
    
    
    //eingegebene Position wird mit WVP-Matrix multipliziert
    output.position = mul(input.inPosition, wvpMatrix);
    
    //ausgegebene Farbe ist eingegebene Farbe
    output.color = input.inColor;
    
    //ausgegebene Textur ist eingegebene Textur
    output.uv = input.inTexture;
    
    //eingegebene Normal mit World-Matrix multiplizieren
    output.normal = mul(float4(input.inNormal, fOne), worldMatrix);
    output.tangent = mul(float4(input.inTangent, fOne), worldMatrix);
    output.binormal = mul(float4(input.inBinormal, fOne), worldMatrix);
    output.viewDirection = cameraPosition.xyz - mul(worldMatrix, input.inPosition).xyz;
    /*-----------------------------------------------------------------------*/
    
    return output;
}
/*****************************************************************************/
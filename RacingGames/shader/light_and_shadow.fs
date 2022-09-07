#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
// #define NR_POINT_LIGHTS 4  
#define MAX_NR_POINT_LIGHTS 4  
uniform PointLight pointLights[MAX_NR_POINT_LIGHTS];
uniform int numPointLight;

// uniform vec3 lightPos;
uniform vec3 lightDirection;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // 透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // 映射到[0,1]区间
    projCoords = projCoords * 0.5 + 0.5;
    // 从光的角度得到指向当前片元的路径上的最近的深度值（使用[0,1]区间fragPosLight坐标）
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // 从光的角度得到当前片元的深度
    float currentDepth = projCoords.z;
    
    // 计算偏差
    vec3 normal = normalize(fs_in.Normal);
    float bias = max(0.001 * (1.0 - dot(normal, lightDirection)), 0.00001);
    
    // 检测当前frag是否在阴影中
    // float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    // PCF 优化锯齿阴影边缘
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    
    // 当片元深度超过1.0时，不绘制阴影，避免远处全是阴影的现象
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

// 计算定点光在确定位置的光照颜色
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // 计算漫反射强度
    float diff = max(dot(normal, lightDir), 0.0);
    // 计算镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    float spec = 0.0;
    // 计算衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance +
                 light.quadratic * (distance * distance));
    // 将各个分量合并
    vec3 ambient  = light.ambient  * vec3(texture(diffuseTexture, fs_in.TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(diffuseTexture, fs_in.TexCoords));
    vec3 specular = light.specular * spec;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main()
{
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.8);

    // ambient 环境光
    vec3 ambient = 0.3 * color;
    
    // diffuse 漫反射
    float diff = max(dot(lightDirection, normal), 0.0);
    vec3 diffuse = diff * color;  // 贴图颜色越深，漫反射越弱
    
    // specular 镜面反射
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDirection, normal);
    
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDirection + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;
    
    // 计算阴影
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    for(int i = 0; i < numPointLight; i++)
        lighting += CalcPointLight(pointLights[i], normal, fs_in.FragPos, viewDir);
    
    FragColor = vec4(lighting, 1.0);
}

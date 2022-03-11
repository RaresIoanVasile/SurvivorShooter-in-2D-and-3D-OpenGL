#pragma once

#include "utils/glm_utils.h"


namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        
        return glm::transpose(
            glm::mat3(1.f, 0.f, translateX,
                0.f, 1.f, translateY,
                0.f, 0.f, 1.f)
        );

    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        
        return glm::transpose(
            glm::mat3(scaleX, 0.f, 0.f,
                0.f, scaleY, 0.f,
                0.f, 0.f, 1.f)
        );

    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        
        float coss = cos(radians);
        float sinn = sin(radians);
        return glm::transpose(
            glm::mat3(coss, -sinn, 0.f,
                sinn, coss, 0.f,
                0.f, 0.f, 1.f)
        );
    }
}   // namespace transform2D

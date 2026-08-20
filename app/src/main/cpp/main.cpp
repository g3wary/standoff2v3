// language: C++, target: Android ARM64
#include <jni.h>
#include <cmath>
#include <cstdint>

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Matrix4x4 { float m[16]; };

namespace offsets {
    namespace base { inline uint64_t player_manager() { return 180740496; } }
    namespace manager { inline int local() { return 0x70; } inline int list() { return 0x28; } inline int list_size() { return 0x20; } }
    namespace list { inline int buffer() { return 0x18; } inline int entry() { return 0x30; } inline int stride() { return 0x18; } }
    namespace player { inline int team() { return 0x79; } inline int movement_controller() { return 0x98; } inline int main_camera() { return 0xE8; } }
    namespace transform { inline int data() { return 0xB0; } inline int position() { return 0x44; } }
    namespace camera { inline int transform() { return 0x20; } inline int ptr() { return 0x10; } inline int matrix() { return 0xF0; } }
    namespace aim { inline int aim_controller() { return 0x80; } inline int aim_pitch() { return 0x18; } inline int aim_yaw() { return 0x1C; } }
}

bool WorldToScreen(const Vector3& world_pos, const Matrix4x4& view_matrix, int width, int height, Vector2& screen_pos) {
    float w = view_matrix.m[3] * world_pos.x + view_matrix.m[7] * world_pos.y + view_matrix.m[11] * world_pos.z + view_matrix.m[15];
    if (w < 0.01f) return false;

    float x = view_matrix.m[0] * world_pos.x + view_matrix.m[4] * world_pos.y + view_matrix.m[8] * world_pos.z + view_matrix.m[12];
    float y = view_matrix.m[1] * world_pos.x + view_matrix.m[5] * world_pos.y + view_matrix.m[9] * world_pos.z + view_matrix.m[13];

    screen_pos.x = (width / 2.0f) + (width / 2.0f) * (x / w);
    screen_pos.y = (height / 2.0f) - (height / 2.0f) * (y / w);
    return true;
}

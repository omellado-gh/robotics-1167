#include <graphics.h>

#include <config.h>

#include <raymath.h>

void draw_background(Color *screen, Color color) {
    for (size_t x = 0; x < SCREEN_WIDTH; ++x) {
        for (size_t y = 0; y < SCREEN_HEIGHT; ++y) {
            screen[y * SCREEN_WIDTH + x] = color;
        }
    }
}

void draw_rectangle(Color *screen, rectangle_t rec, Color color) {
    float angle = rec.rotation * DEG2RAD; // Grados a radianes
    float cos_theta = cosf(angle);
    float sin_theta = sinf(angle);

    // Mitades del ancho y alto
    float hw = (float)rec.width / 2.0f;
    float hh = (float)rec.height / 2.0f;

    // 1. Calcular las esquinas rotadas (coordenadas absolutas)
    float corners[4][2] = {{-hw, -hh}, {hw, -hh}, {hw, hh}, {-hw, hh}};
    
    for (int i = 0; i < 4; i++) {
        float dx = corners[i][0];
        float dy = corners[i][1];
        rec.corners[i].x = rec.x.x + (dx * cos_theta - dy * sin_theta);
        rec.corners[i].y = rec.x.y + (dx * sin_theta + dy * cos_theta);
    }

    // 2. Calcular el bounding box del rectángulo rotado
    float min_x = rec.corners[0].x, max_x = rec.corners[0].x;
    float min_y = rec.corners[0].y, max_y = rec.corners[0].y;
    for (int i = 1; i < 4; i++) {
        if (rec.corners[i].x < min_x) min_x = rec.corners[i].x;
        if (rec.corners[i].x > max_x) max_x = rec.corners[i].x;
        if (rec.corners[i].y < min_y) min_y = rec.corners[i].y;
        if (rec.corners[i].y > max_y) max_y = rec.corners[i].y;
    }


    // 3. Iterar sobre todos los píxeles del bounding box
    for (int x = (int)floor(min_x); x <= (int)ceil(max_x); x++) {
        for (int y = (int)floor(min_y); y <= (int)ceil(max_y); y++) {

			if (x <= 0 || y <= 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
				continue;

            // Convertir a coordenadas relativas al centro
            float dx = (float)x - rec.x.x;
            float dy = (float)y - rec.x.y;

            // Aplicar rotación inversa (para mapear al rectángulo original)
            float orig_x = dx * cos_theta + dy * sin_theta;
            float orig_y = -dx * sin_theta + dy * cos_theta;

            // Verificar si está dentro del rectángulo original
            if (orig_x >= -hw && orig_x <= hw && orig_y >= -hh && orig_y <= hh) {
                screen[y * SCREEN_WIDTH + x] = color; // Dibujar el píxel
            }
        }
    }
}

void draw_object(object_t object) {
    object.model.transform = MatrixMultiply(MatrixRotateXYZ(object.rotation), object.model.transform);
    DrawModel(object.model, object.position, 1.0f, object.color);
}

void draw_cube(cube_t cube) {
    draw_object(cube.object);
}

void draw_cylinder(cylinder_t cylinder) {
    draw_object(cylinder.object);
}

void draw_sphere(sphere_t sphere) {
    draw_object(sphere.object);
}
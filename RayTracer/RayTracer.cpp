#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>

#include "Ray.h"
#include "Sphere.h"
#include "Vector3.h"
#include "World.h"


static void emptyArray(sf::Uint8* pixels, int width, int height)
{
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            pixels[4 * (j * width + i)] = 255;
            pixels[4 * (j * width + i) + 1] = 0;
            pixels[4 * (j * width + i) + 2] = 0;
            pixels[4 * (j * width + i) + 3] = 255;
        }
    }
}

static void writeColor(sf::Uint8* pixels, int x, int y, int width, Vector3 color)
{
    pixels[4 * (y * width + x)] = static_cast<int>(255.999 *color.x()) ;
    pixels[4 * (y * width + x) + 1] = static_cast<int>(255.999 * color.y());
    pixels[4 * (y * width + x) + 2] = static_cast<int>(255.999 * color.z());
    pixels[4 * (y * width + x) + 3] = 255;
}

int main()
{
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1280;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
	
    sf::RenderWindow window(sf::VideoMode(image_width, image_height), "RayTracer");
    auto* pixels = new sf::Uint8[image_width * image_height * 4];
    emptyArray(pixels, image_width, image_height);
 
    sf::Texture texture;
	if (!texture.create(image_width, image_height))
        return -1;

    sf::Sprite sprite(texture);
    window.setFramerateLimit(60);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Vector3(0, 0, 1);
    auto horizontal = Vector3(viewport_width, 0, 0);
    auto vertical = Vector3(0, viewport_height, 0);
    auto upper_left_corner = origin - horizontal / 2 + vertical / 2 - Vector3(0, 0, focal_length);

    World world;
    world.AddObject(std::make_shared<Sphere>(Vector3(0, 0, -1), 0.5));
    world.AddObject(std::make_shared<Sphere>(Vector3(0, -100.5, -1), 100));
	   
    auto start = std::chrono::high_resolution_clock::now();
	
    for (int j = 0; j < image_height; ++j) {
        std::cerr << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);
            Ray r(origin, upper_left_corner + u * horizontal - v * vertical - origin);
            Vector3 pixel_color = r.Cast(world);
            
            writeColor(pixels, i, j, image_width, pixel_color);
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    
    std::cerr << duration.count() << std::endl;

	
    texture.update(pixels);
	
    while (window.isOpen())
    {
        sf::Event event;
    	
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    	
        window.clear();

        window.draw(sprite);

        window.display();
    }

    return 0;
}




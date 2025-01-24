#include <gtest/gtest.h>
#include <unistd.h>
#include "../include/cache2.h"  

// Test para verificar el constructor y la capacidad
TEST(CacheMemoryTest, ConstructorAndCapacity) {
    CacheMemory<int> cache(3);  // 2^3 - 1 = 7
    EXPECT_EQ(cache.capacity, 7);
    EXPECT_EQ(cache.count, 0);
}

// Test para verificar el método `push` y `get`
TEST(CacheMemoryTest, PushAndGet) {
    CacheMemory<int> cache(3);  // Capacidad: 7

    // Insertamos un dato
    dato<int> d1 = {1, 100};
    cache.push(d1);

    // Verificamos que el dato se haya guardado correctamente
    auto result = cache.get(1);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->id, 1);
    EXPECT_EQ(result->val, 100);

    // Insertamos más datos
    dato<int> d2 = {2, 200};
    dato<int> d3 = {3, 300};
    cache.push(d2);
    cache.push(d3);

    EXPECT_EQ(cache.count, 3);
    EXPECT_EQ(cache.get(2)->val, 200);
    EXPECT_EQ(cache.get(3)->val, 300);
}

// Test para verificar el reemplazo cuando se supera la capacidad
TEST(CacheMemoryTest, Replacement) {
    CacheMemory<int> cache(2);  // Capacidad: 3 (2^2 - 1)

    cache.push({1, 100});
    usleep(1000000);
    cache.push({2, 200});
    usleep(1000000);
    cache.push({3, 300});
    usleep(2000000);

    // Añadimos un cuarto elemento, debería reemplazar al más antiguo
    cache.push({4, 400});

    EXPECT_FALSE(cache.get(1).has_value());  // Elemento más antiguo eliminado
    EXPECT_TRUE(cache.get(4).has_value());  // Nuevo elemento insertado
    EXPECT_EQ(cache.get(4)->val, 400);
}
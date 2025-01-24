#include <gtest/gtest.h>
#include "../include/b-tree.h"


// Prueba para verificar que un valor no insertado no está en el árbol
TEST(BTreeTest, SearchNonExistentValue) {
    BTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    // Verificar que el valor 30 no esté en el árbol
    EXPECT_FALSE(tree.search(30));
}

// Prueba de división (split) de nodos al insertar más de Max_size valores
TEST(BTreeTest, NodeSplitOnInsert) {
    BTree tree;

    // Insertar valores para forzar una división en el nodo raíz
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(15);
    tree.insert(30);

    // Como el árbol es pequeño, verificamos si los valores están en el árbol
    EXPECT_TRUE(tree.search(10));
    EXPECT_TRUE(tree.search(20));
    EXPECT_TRUE(tree.search(5));
    EXPECT_TRUE(tree.search(6));
    EXPECT_TRUE(tree.search(15));
    EXPECT_TRUE(tree.search(30));
}

TEST(BTreeTest, LevelBtree2) {
    BTree tree;

    // Insertar valores para verificar los niveles
    for(int i= 1; i <= 16; i++){
        tree.insert(i);
    }

    EXPECT_EQ(tree.getLevel(16),2);
    
    tree.insert(17);

    EXPECT_EQ(tree.getLevel(17),3);
}

TEST(BTreeTest, LevelBtree3) {
    BTree tree;

    // Insertar valores para verificar los niveles
    for(int i= 1; i <= 52; i++){
        tree.insert(i);
    }

    EXPECT_EQ(tree.getLevel(52),3);
    
    tree.insert(53);

    EXPECT_EQ(tree.getLevel(53),4);
}

TEST(BTreeTest, LevelBtree4) {
    BTree tree;

    // Insertar valores para verificar los niveles
    for(int i= 1; i <= 160; i++){
        tree.insert(i);
    }

    EXPECT_EQ(tree.getLevel(160),4);
    
    tree.insert(161);

    EXPECT_EQ(tree.getLevel(161),5);
}

TEST(BTreeTest, LevelBtree5) {
    BTree tree;

    // Insertar valores para verificar los niveles
    for(int i= 1; i <= 484; i++){
        tree.insert(i);
    }

    EXPECT_EQ(tree.getLevel(484),5);
    
    tree.insert(485);

    EXPECT_EQ(tree.getLevel(485),6);
}

TEST(BTreeTest, LevelBtree6) {
    BTree tree;

    // Insertar valores para verificar los niveles
    for(int i= 1; i <= 1456; i++){
        tree.insert(i);
    }

    EXPECT_EQ(tree.getLevel(1456),6);
    
    tree.insert(1457);

    EXPECT_EQ(tree.getLevel(1457),7);
}
